NAME = libft.a
CC = gcc
FLAGS = -Wall -Werror -Wextra
SRC = ft_putstr		\
	  ft_putchar	\
	  ft_putendl	\
	  ft_putnbr		\
	  ft_putnbrendl	\
	  ft_strlen		\
	  get_next_line	\
	  ft_bzero		\
	  ft_strsplit	\
	  ft_strnew		\
	  ft_error		\
	  ft_atoi		\
	  ft_strchr		\
	  ft_strclr		\
	  ft_strdel		\
	  ft_strjoin	\
	  ft_strncpy
SRCS = $(addsuffix .c, $(SRC))
OBJ = $(addsuffix .o, $(SRC))

$(NAME): $(OBJ)
	@$(CC) $(FLAGS) -c $(SRCS)
	@ar rc $(NAME) $(OBJ)
	@echo "Libft compiled !"

all: $(NAME)

clean:
	@rm -f $(OBJ)
	@echo "Lib objects cleaned"

fclean: clean
	@rm -f $(NAME)
	@echo "Lib cleaned"

re: fclean all
