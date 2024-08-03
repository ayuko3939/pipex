/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohasega <yohasega@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 12:12:24 by yohasega          #+#    #+#             */
/*   Updated: 2024/08/01 16:17:44 by yohasega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	check_args(int ac, char **av)
{
	if (ac < 5)
	{
		ft_putstr_fd("\033[31m", 2);
		ft_putstr_fd("Invalid argument\n", 2);
		ft_putstr_fd("ex) ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2\n",
			2);
		ft_putstr_fd("\033[0m", 2);
		exit(EXIT_FAILURE);
	}
	if ((ft_strncmp(av[1], "here_doc", 9) == 0) && (ac < 6))
	{
		ft_putstr_fd("\033[31m", 2);
		ft_putstr_fd("Invalid argument\n", 2);
		ft_putstr_fd("ex) ./pipex file1 cmd1 cmd2 file2\n", 2);
		ft_putstr_fd("ex) ./pipex here_doc LIMITER cmd cmd1 file\n", 2);
		ft_putstr_fd("\033[0m", 2);
		exit(EXIT_FAILURE);
	}
}

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

void	wait_all(t_pipe data)
{
	int	i;

	i = 0;
	waitpid(data.pid, &data.status, 0);
	while (i < data.nm_cmd - 1)
	{
		waitpid(-1, NULL, 0);
		i++;
	}
}

int	open_file(char *file, int mode)
{
	int	fd;

	fd = -1;
	if (mode == 0)
	{
		if (access(file, F_OK) == 0 && access(file, R_OK) == -1)
			error_exit(strerror(errno));
		fd = open(file, O_RDONLY);
	}
	else if (mode == 1)
	{
		if (access(file, F_OK) == 0 && access(file, (W_OK | R_OK)) == -1)
			error_exit(strerror(errno));
		fd = open(file, (O_RDWR | O_CREAT | O_TRUNC), 0644);
	}
	else if (mode == 2)
	{
		if (access(file, F_OK) == 0 && access(file, (R_OK | W_OK)) == -1)
			error_exit(strerror(errno));
		fd = open(file, (O_RDWR | O_CREAT | O_APPEND), 0644);
	}
	return (fd);
}
