
NAME = cr

CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address -I.

MAKE = make -C

DIR = ./

PATH_SRC = ./srcs/

PATH_OP = ./op/

SRCS = $(PATH_SRC)main.c\
      $(PATH_SRC)tool.c\
      $(PATH_SRC)tools2.c\
      $(PATH_SRC)tools3.c\
      $(PATH_SRC)exit.c\
      $(PATH_SRC)option.c\
      $(PATH_SRC)vm.c\
      $(PATH_SRC)parsing.c\
      $(PATH_SRC)ft_dump.c\
      $(PATH_SRC)itoabase.c\
      $(PATH_SRC)itoabase2.c\
	  $(PATH_SRC)convert.c\
	  $(PATH_SRC)op.c\
	  $(PATH_OP)fork.c\
	  $(PATH_OP)add.c\
	  $(PATH_OP)aff.c\
	  $(PATH_OP)and.c\
	  $(PATH_OP)ld.c\
	  $(PATH_OP)ldi.c\
	  $(PATH_OP)lfork.c\
	  $(PATH_OP)live.c\
	  $(PATH_OP)lld.c\
	  $(PATH_OP)lldi.c\
	  $(PATH_OP)or.c\
	  $(PATH_OP)st.c\
	  $(PATH_OP)sti.c\
	  $(PATH_OP)sub.c\
	  $(PATH_OP)xor.c\
	  $(PATH_OP)zjmp.c\

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
	rm -f op/*.o

fclean: clean
	rm -f $(NAME)
	rm -f libft/libft.a

re: fclean all

.PHONY : all lib clean fclean re
