/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohasega <yohasega@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 12:12:24 by yohasega          #+#    #+#             */
/*   Updated: 2024/08/01 16:13:52 by yohasega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_exit(char *str)
{
	ft_putstr_fd("\033[31m", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	ft_putstr_fd("\033[0m", 2);
	exit(EXIT_FAILURE);
}

void	execve_error(t_pipe *data)
{
	if ((*data).fd_in != -1)
		close((*data).fd_in);
	if ((*data).fd_out != -1)
		close((*data).fd_out);
	cleanup(data);
	error_exit("command not found");
}

void	cleanup(t_pipe *data)
{
	if ((*data).pathlist)
	{
		free_all((*data).pathlist);
		(*data).pathlist = NULL;
	}
	if ((*data).path)
	{
		free((*data).path);
		(*data).path = NULL;
	}
	if ((*data).cmd)
	{
		free_all((*data).cmd);
		(*data).cmd = NULL;
	}
	if ((*data).cmdstr)
	{
		free((*data).cmdstr);
		(*data).cmdstr = NULL;
	}
}

void	init_data(t_pipe *data)
{
	(*data).fd_in = -1;
	(*data).fd_out = -1;
	(*data).pathlist = NULL;
	(*data).path = NULL;
	(*data).cmd = NULL;
	(*data).cmdstr = NULL;
	(*data).status = EXIT_SUCCESS;
	(*data).pid = -1;
}

void	open_files(char *file, int mode, t_pipe *data)
{
	if (mode == 0)
	{
		if (access(file, F_OK) == 0 && access(file, R_OK) == -1)
			error_exit(strerror(errno));
		(*data).fd_in = open(file, O_RDONLY);
		if ((*data).fd_in == -1)
			error_exit(strerror(errno));
	}
	else if (mode == 1)
	{
		if (access(file, F_OK) == 0 && access(file, (W_OK | R_OK)) == -1)
			error_exit(strerror(errno));
		(*data).fd_out = open(file, (O_RDWR | O_CREAT | O_TRUNC), 0644);
		if ((*data).fd_out == -1)
		{
			close((*data).fd_in);
			error_exit(strerror(errno));
		}
	}
}
