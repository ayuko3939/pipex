/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohasega <yohasega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 17:33:01 by yohasega          #+#    #+#             */
/*   Updated: 2024/05/09 13:30:29 by yohasega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (s == NULL)
		return ;
	write(fd, s, ft_strlen(s));
}

// int main(void)
// {
//     int filds = 1;
//     char *str = "Snow Man";
//     ft_putstr_fd(str, filds);
//     return (0);
// }

// ccw ft_putstr_fd.c ft_strlen.c