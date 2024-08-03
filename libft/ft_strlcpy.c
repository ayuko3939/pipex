/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohasega <yohasega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 17:00:13 by yohasega          #+#    #+#             */
/*   Updated: 2024/05/09 19:01:28 by yohasega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
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
	return (ft_strlen(src));
}

// int	main(void)
// {
// 	char	name1[21] = "Johnnys Entertainment";
// 	char	name2[21] = "Johnnys Entertainment";
// 	char	name3[6] = "STARTO";

// 	printf("Before : %s\n", name1);
// 	ft_strlcpy(name1, name3, (sizeof(name1) / sizeof(char)));
// 	printf("%zu\n", strlcpy(name2, name3, (sizeof(name1) / sizeof(char))));
// 	printf("ft_strlcpy : %s\n", name1);
// 	printf("   strlcpy : %s\n", name2);
// 	return (0);
// }