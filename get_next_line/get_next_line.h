/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohasega <yohasega@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:50:23 by yohasega          #+#    #+#             */
/*   Updated: 2024/07/19 17:21:39 by yohasega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

# include <stdlib.h>
# include <unistd.h>

char	*free_nullset(char **str);
int		read_from_fd(int fd, char **temp);
char	*get_newline(char *str);
int		remove_line_from_temp(char **str);
char	*get_next_line(int fd);

size_t	ft_strlen_gnl(const char *str);
int		ft_strchr_gnl(const char *s, int c);
size_t	ft_strlcpy_gnl(char *dst, const char *src, size_t dstsize);
char	*ft_substr_gnl(char const *s, unsigned int start, size_t len);
int		ft_strjoin_gnl(char **s1, char *s2);

#endif
