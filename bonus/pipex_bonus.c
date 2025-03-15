/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohasega <yohasega@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 14:50:07 by yohasega          #+#    #+#             */
/*   Updated: 2025/03/15 18:11:28 by yohasega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
	{
		if (!access((*data).cmd[0], F_OK) && access((*data).cmd[0], X_OK))
			error_exit(strerror(errno));
		if (execve((*data).cmd[0], (*data).cmd, NULL) == -1)
		{
			cleanup(data);
			error_exit(strerror(2));
		}
	}
	(*data).path = get_path(envp, (*data).cmd[0], data);
	if ((*data).path == NULL)
		execve_error(data);
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
		if (dup2((*data).pfd[1], STDOUT_FILENO) == -1)
			error_exit(strerror(errno));
		close((*data).pfd[1]);
		if ((*data).here_doc)
			(*data).fd_in = input_here_doc(av[2]);
		else
			(*data).fd_in = open_file(av[1], 0);
		if ((*data).fd_in == -1)
			error_exit(strerror(errno));
		if (dup2((*data).fd_in, STDIN_FILENO) == -1)
			error_exit(strerror(errno));
		close((*data).fd_in);
		execute_command(av[(*data).start], envp, data);
	}
	close((*data).pfd[1]);
}

void	middle_process(char *cmdstring, char **envp, t_pipe *data)
{
	pid_t	pid;

	if (dup2((*data).pfd[0], STDIN_FILENO) == -1)
		error_exit(strerror(errno));
	close((*data).pfd[0]);
	if (pipe((*data).pfd) == -1)
		error_exit(strerror(errno));
	pid = fork();
	if (pid == -1)
		error_exit(strerror(errno));
	else if (pid == 0)
	{
		close((*data).pfd[0]);
		if (dup2((*data).pfd[1], STDOUT_FILENO) == -1)
			error_exit(strerror(errno));
		close((*data).pfd[1]);
		execute_command(cmdstring, envp, data);
	}
	close((*data).pfd[1]);
}

void	last_process(int ac, char **av, char **envp, t_pipe *data)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		error_exit(strerror(errno));
	else if (pid == 0)
	{
		if (dup2((*data).pfd[0], STDIN_FILENO) == -1)
			error_exit(strerror(errno));
		close((*data).pfd[0]);
		if ((*data).here_doc)
			(*data).fd_out = open_file(av[ac - 1], 2);
		else
			(*data).fd_out = open_file(av[ac - 1], 1);
		if ((*data).fd_out == -1)
		{
			close((*data).fd_in);
			error_exit(strerror(errno));
		}
		if (dup2((*data).fd_out, STDOUT_FILENO) == -1)
			error_exit(strerror(errno));
		close((*data).fd_out);
		execute_command(av[ac - 2], envp, data);
	}
	(*data).pid = pid;
}

int	main(int ac, char **av, char **envp)
{
	t_pipe	data;
	int		i;

	check_args(ac, av);
	init_data(&data, ac, av);
	first_process(av, envp, &data);
	i = 1;
	while (i < data.nm_cmd - 1)
	{
		middle_process(av[data.start + i], envp, &data);
		i++;
	}
	last_process(ac, av, envp, &data);
	wait_all(data);
	cleanup(&data);
	delete_tempfile(data);
	return (0);
}

	// if (WIFEXITED(data.status))
	// 	exit(WEXITSTATUS(data.status));