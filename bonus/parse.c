/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohasega <yohasega@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 14:41:41 by yohasega          #+#    #+#             */
/*   Updated: 2024/08/01 16:03:04 by yohasega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*free_all(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	str = NULL;
	return (NULL);
}

char	*replace_homepath(char *cmdstr, char **envp)
{
	char	*path;

	while (*envp && ft_strncmp(*envp, "HOME=", 5) != 0)
		envp++;
	path = ft_strjoin(*envp + 5, cmdstr + 1);
	if (path == NULL)
		return (NULL);
	return (path);
}

char	*get_fullpath(char *path, char d, char *cmd)
{
	int		len_p;
	int		len_c;
	char	*fullpath;

	len_p = ft_strlen(path);
	len_c = ft_strlen(cmd);
	fullpath = (char *)malloc(sizeof(char) * (len_p + 1 + len_c) + 1);
	if (fullpath == NULL)
		return (NULL);
	ft_memcpy(fullpath, path, len_p);
	fullpath[len_p] = d;
	ft_memcpy(fullpath + (len_p + 1), cmd, len_c);
	fullpath[len_p + 1 + len_c] = '\0';
	return (fullpath);
}

char	*get_path(char **envp, char *cmd, t_pipe *data)
{
	int	i;

	while (*envp && ft_strncmp(*envp, "PATH=", 5) != 0)
		envp++;
	if (*envp == NULL)
		return (NULL);
	(*data).pathlist = ft_split(*envp + 5, ':');
	if ((*data).pathlist == NULL)
		return (NULL);
	i = 0;
	while ((*data).pathlist[i])
	{
		(*data).path = get_fullpath((*data).pathlist[i], '/', cmd);
		if (access((*data).path, X_OK) == 0)
			return ((*data).path);
		free((*data).path);
		i++;
	}
	return (NULL);
}
