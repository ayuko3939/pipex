# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yohasega <yohasega@student.42.jp>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/01 20:37:00 by yohasega          #+#    #+#              #
#    Updated: 2024/08/01 20:37:02 by yohasega         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

M_SRCS = mandatory/pipex.c mandatory/pipex_utils.c mandatory/parse.c
B_SRCS = bonus/pipex_bonus.c bonus/pipex_utils.c bonus/parse.c \
         bonus/data_manage.c bonus/here_doc.c
G_SRCS = get_next_line/get_next_line.c get_next_line/get_next_line_utils.c

M_OBJS = $(M_SRCS:.c=.o)
B_OBJS = $(B_SRCS:.c=.o)
G_OBJS = $(G_SRCS:.c=.o)
LIBFT = libft/libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address

.PHONY: all clean fclean re bonus

all: $(NAME)

$(NAME): $(M_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(M_OBJS) $(LIBFT) -o $(NAME)

bonus: $(B_OBJS) $(G_OBJS) $(LIBFT)
	@if [ ! -e $(NAME) ]; then \
		$(CC) $(CFLAGS) $(B_OBJS) $(G_OBJS) $(LIBFT) -o $(NAME); \
	fi

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C libft

clean:
	rm -f $(M_OBJS) $(B_OBJS) $(G_OBJS)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all
