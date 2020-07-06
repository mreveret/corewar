# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: machoffa <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/27 14:18:33 by machoffa          #+#    #+#              #
#    Updated: 2019/10/19 12:24:18 by machoffa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = libftprintf.a
INCLUDE = ft_printf.h
CC = gcc
FLAGS = -Wall -Wextra -Werror -Ofast
SRC = precisions_flags.c \
		  ft_printf.c \
		  type_s.c \
		  type_c.c \
		  type_d.c \
		  type_u.c \
		  type_f.c \
		  type_pourcent.c \
		  options.c \
		  tools.c \
		  bonus.c \
		  bonustab.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

%.o: %.c
		@gcc $(FLAGS) -c $< -o $@

clean :
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
