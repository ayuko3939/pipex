/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohasega <yohasega@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:52:16 by yohasega          #+#    #+#             */
/*   Updated: 2024/07/19 17:18:20 by yohasega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// new ft_strlen (add : NULLguard)
size_t	ft_strlen_gnl(const char *str)
{
	size_t	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

// return (int) ver
// (0)NG  (1)OK
int	ft_strchr_gnl(const char *s, int c)
{
	int	len;

	len = 0;
	c = (char)c;
	if (s == NULL)
		return (0);
	while (s[len] != 0)
	{
		if (s[len] == c)
			return (1);
		len++;
	}
	if (c == '\0')
		return (1);
	return (0);
}

size_t	ft_strlcpy_gnl(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (i < dstsize - 1 && src[i] && dstsize)
	{
		dst[i] = src[i];
		i++;
	}
	if (dstsize != 0)
		dst[i] = '\0';
	return (1);
}

// malloc ver
char	*ft_substr_gnl(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	len_s;

	if (s == 0 || len == 0 || ft_strlen_gnl(s) < start)
	{
		substr = (char *)malloc(sizeof(char) * 1);
		if (substr == NULL)
			return (NULL);
		substr[0] = '\0';
		return ((char *)substr);
	}
	s = s + start;
	len_s = ft_strlen_gnl(s);
	if (len_s < len)
		len = len_s;
	substr = (char *)malloc(sizeof(char) * (len + 1));
	if (substr == NULL)
		return (NULL);
	ft_strlcpy_gnl(substr, s, len + 1);
	return (substr);
}

// (0)NG  (1)OK
int	ft_strjoin_gnl(char **s1, char *s2)
{
	char	*new_str;
	size_t	len_s1;
	size_t	len_s2;

	if (s2 == NULL)
		return (1);
	len_s1 = ft_strlen_gnl(*s1);
	len_s2 = ft_strlen_gnl(s2);
	new_str = (char *)malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (new_str == NULL)
	{
		free_nullset(s1);
		free_nullset(&s2);
		return (0);
	}
	ft_strlcpy_gnl((void *)new_str, (void *)*s1, len_s1 + 1);
	ft_strlcpy_gnl((void *)new_str + len_s1, (void *)s2, len_s2 + 1);
	free(*s1);
	*s1 = new_str;
	return (1);
}
