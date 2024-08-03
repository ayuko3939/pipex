/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohasega <yohasega@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 15:17:27 by yohasega          #+#    #+#             */
/*   Updated: 2024/07/29 15:25:41 by yohasega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	input_here_doc(char *end)
{
	char	*input;
	int		tempfd;
	int		len;

	tempfd = open_file(".tempfile", 1);
	len = ft_strlen(end);
	while (1)
	{
		input = get_next_line(STDIN_FILENO);
		if (ft_strncmp(input, end, len) == 0 && input[len] == '\n')
		{
			free(input);
			break ;
		}
		ft_putstr_fd(input, tempfd);
		free(input);
		input = NULL;
	}
	close(tempfd);
	tempfd = open_file(".tempfile", 0);
	return (tempfd);
}
