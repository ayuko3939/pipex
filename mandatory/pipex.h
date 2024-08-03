/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohasega <yohasega@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 12:30:33 by yohasega          #+#    #+#             */
/*   Updated: 2024/08/01 16:07:38 by yohasega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_pipe
{
	int		pfd[2];
	pid_t	pid;
	int		fd_in;
	int		fd_out;
	char	**pathlist;
	char	*path;
	char	**cmd;
	char	*cmdstr;
	int		status;
}			t_pipe;

// -+-+-+-+-+-+-+-+-+-+- pipex -+-+-+-+-+-+-+-+-+-+-

void		execute_command(char *cmdstring, char **envp, t_pipe *data);
void		first_process(char **av, char **envp, t_pipe *data);
void		second_process(char **av, char **envp, t_pipe *data);

// -+-+-+-+-+-+-+-+-+-+- utils -+-+-+-+-+-+-+-+-+-+-

void		error_exit(char *str);
void		execve_error(t_pipe *data);
void		cleanup(t_pipe *data);
void		init_data(t_pipe *data);
void		open_files(char *file, int mode, t_pipe *data);

// -+-+-+-+-+-+-+-+-+-+- parse -+-+-+-+-+-+-+-+-+-+-

char		*free_all(char **str);
char		*replace_homepath(char *cmdstr, char **envp);
char		*get_fullpath(char *path, char d, char *cmd);
char		*get_path(char **envp, char *cmd, t_pipe *data);

#endif