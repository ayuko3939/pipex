/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohasega <yohasega@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 14:50:07 by yohasega          #+#    #+#             */
/*   Updated: 2024/08/03 13:05:27 by yohasega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_command(char *cmdstring, char **envp, t_pipe *data)
{
	if (*cmdstring == '~')
		(*data).cmdstr = replace_homepath(cmdstring, envp);
	else
		(*data).cmdstr = ft_strdup(cmdstring);
	if ((*data).cmdstr == NULL)
		error_exit("Error : malloc data.cmdstring");
	(*data).cmd = ft_split((*data).cmdstr, ' ');
	if ((*data).cmd == NULL)
		error_exit("Error : malloc data.cmdstring");
	if (*(*data).cmdstr == '.' || *(*data).cmdstr == '/')
		(*data).path = ft_strdup((*data).cmd[0]);
	else
		(*data).path = get_path(envp, (*data).cmd[0], data);
	if (access((*data).path, X_OK) != 0 && (*(*data).cmdstr == '.'
			|| *(*data).cmdstr == '/'))
	{
		cleanup(data);
		error_exit(strerror(2));
	}
	if (execve((*data).path, (*data).cmd, NULL) == -1)
		execve_error(data);
}

void	first_process(char **av, char **envp, t_pipe *data)
{
	pid_t	pid;

	if (pipe((*data).pfd) == -1)
		error_exit(strerror(errno));
	pid = fork();
	if (pid == -1)
		error_exit(strerror(errno));
	else if (pid == 0)
	{
		close((*data).pfd[0]);
		open_files(av[1], 0, data);
		if (dup2((*data).fd_in, STDIN_FILENO) == -1)
			error_exit(strerror(errno));
		close((*data).fd_in);
		if (dup2((*data).pfd[1], STDOUT_FILENO) == -1)
			error_exit(strerror(errno));
		close((*data).pfd[1]);
		execute_command(av[2], envp, data);
	}
	else
		close((*data).pfd[1]);
}

void	second_process(char **av, char **envp, t_pipe *data)
{
	(*data).pid = fork();
	if ((*data).pid == -1)
		error_exit(strerror(errno));
	else if ((*data).pid == 0)
	{
		open_files(av[4], 1, data);
		if (dup2((*data).pfd[0], STDIN_FILENO) == -1)
			error_exit(strerror(errno));
		close((*data).pfd[0]);
		if (dup2((*data).fd_out, STDOUT_FILENO) == -1)
			error_exit(strerror(errno));
		close((*data).fd_out);
		execute_command(av[3], envp, data);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_pipe	data;

	if (ac < 5)
	{
		ft_putstr_fd("\033[31m", 2);
		ft_putstr_fd("Invalid argument\n", 2);
		ft_putstr_fd("ex) ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2\n", 2);
		ft_putstr_fd("\033[0m", 2);
		exit(EXIT_FAILURE);
	}
	init_data(&data);
	first_process(av, envp, &data);
	second_process(av, envp, &data);
	waitpid(data.pid, &data.status, 0);
	waitpid(-1, NULL, 0);
	cleanup(&data);
	return (0);
}

	// if (WIFEXITED(data.status))
	// 	exit(WEXITSTATUS(data.status));