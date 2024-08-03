/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohasega <yohasega@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:22:11 by yohasega          #+#    #+#             */
/*   Updated: 2024/07/29 10:06:22 by yohasega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdint.h> //SIZE_MAX
# include <unistd.h> //ft_putstr_fd
# include <stdlib.h> //malloc

// -+-+-+-+-+-+-+-+- Part1 -+-+-+-+-+-+-+-+-

size_t	ft_strlen(const char *str);
void	*ft_memcpy(void *dst, const void *src, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strdup(const char *s1);

// -+-+-+-+-+-+-+-+- Part2 -+-+-+-+-+-+-+-+-

char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char *s, char c);
void	ft_putstr_fd(char *s, int fd);

#endif