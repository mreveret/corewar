# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: machoffa <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/22 13:13:16 by machoffa          #+#    #+#              #
#    Updated: 2020/03/11 18:21:42 by mreveret         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cr

CFLAGS = -Wall -Wextra -Werror -I.

MAKE = make -C

DIR = ./

PATH_SRC = ./srcs/

SRCS = $(PATH_SRC)main.c \
      $(PATH_SRC)tool.c \
      $(PATH_SRC)ft_dump.c \
      $(PATH_SRC)itoabase.c \
      $(PATH_SRC)itoabase2.c \

OBJS = $(SRCS:.c=.o)

LIBFT_PATH = ./libft/

all: lib $(NAME)

lib:
	$(MAKE) ./libft

$(NAME): $(OBJS)
	make -C $(LIBFT_PATH)
	gcc $(CFLAGS) $(SRCS) -L./libft -lft -o $(NAME)

%.o: %.c ./corewar.h ./Makefile ./libft/libft.h
	gcc -o $@ -c $< $(CFLAGS)

clean:
	rm -f srcs/*.o
	rm -f libft/*.o

fclean: clean
	rm -f $(NAME)
	rm -f libft/libft.a

re: fclean all

.PHONY : all lib clean fclean re
