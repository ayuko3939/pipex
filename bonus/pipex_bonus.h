/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohasega <yohasega@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 12:30:33 by yohasega          #+#    #+#             */
/*   Updated: 2024/08/01 16:18:11 by yohasega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../get_next_line/get_next_line.h"
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
	int		here_doc;
	int		start;
	int		nm_cmd;
	int		status;
}			t_pipe;

// -+-+-+-+-+-+-+-+-+-+- pipex -+-+-+-+-+-+-+-+-+-+-

void		execute_command(char *cmdstring, char **envp, t_pipe *data);
void		first_process(char **av, char **envp, t_pipe *data);
void		middle_process(char *cmdstring, char **envp, t_pipe *data);
void		last_process(int ac, char **av, char **envp, t_pipe *data);

// -+-+-+-+-+-+-+-+-+- here_doc -+-+-+-+-+-+-+-+-+-+

int			input_here_doc(char *end);

// -+-+-+-+-+-+-+-+-+-+- utils -+-+-+-+-+-+-+-+-+-+-

void		check_args(int ac, char **av);
void		error_exit(char *str);
void		execve_error(t_pipe *data);
void		wait_all(t_pipe data);
int			open_file(char *file, int mode);

// -+-+-+-+-+-+-+-+-+-+- parse -+-+-+-+-+-+-+-+-+-+-

char		*free_all(char **str);
char		*replace_homepath(char *cmdstr, char **envp);
char		*get_fullpath(char *path, char d, char *cmd);
char		*get_path(char **envp, char *cmd, t_pipe *data);

// -+-+-+-+-+-+-+-+-+ data_manage +-+-+-+-+-+-+-+-+-

void		init_data(t_pipe *data, int ac, char **av);
void		cleanup(t_pipe *data);
void		delete_tempfile(t_pipe data);

#endif