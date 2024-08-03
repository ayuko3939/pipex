/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_manage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohasega <yohasega@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 12:12:24 by yohasega          #+#    #+#             */
/*   Updated: 2024/08/01 16:26:55 by yohasega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	init_data(t_pipe *data, int ac, char **av)
{
	(*data).pid = -1;
	(*data).fd_in = -1;
	(*data).fd_out = -1;
	(*data).pathlist = NULL;
	(*data).path = NULL;
	(*data).cmd = NULL;
	(*data).cmdstr = NULL;
	(*data).status = EXIT_SUCCESS;
	(*data).here_doc = 0;
	if (ft_strncmp(av[1], "here_doc", 9) == 0)
		(*data).here_doc = 1;
	(*data).start = 2;
	if ((*data).here_doc)
		(*data).start = 3;
	(*data).nm_cmd = ac - (*data).start - 1;
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

void	delete_tempfile(t_pipe data)
{
	if (data.here_doc)
	{
		if (unlink(".tempfile") == -1)
			error_exit(strerror(errno));
	}
}
