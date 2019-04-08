NAME = fdf
CC = cc
FLAGS = -Werror -Wall -Wextra
FMWRK = -framework OpenGL -framework AppKit
SRC = main				\
	  draw_segment		\
	  parse_file		\
	  print_grid		\
	  inputs_outputs	\
	  utils				\
	  displays			\
	  colors
LIB = minilibx_macos/libmlx.a
LIBFT_A = libft/libft.a
SRCS = $(addsuffix .c, $(SRC))
OBJ = $(addsuffix .o, $(SRC))

all: $(NAME)

$(NAME): $(LIB) $(LIBFT_A) $(OBJ)
	@$(CC) $(FLAGS) $(SRCS) $(LIB) $(LIBFT_A) $(FMWRK) -o $(NAME)
	@echo "FdF compiled !"

$(LIBFT_A):
	@make --directory libft

$(LIB):
	@make --directory minilibx_macos

clean:
	@rm -f $(OBJ)
	@make clean --directory libft
	@echo "FdF objects cleaned"

fclean: clean
	@rm -f $(NAME)
	@make clean --directory minilibx_macos
	@make fclean --directory libft
	@echo "FdF cleaned"

re: fclean all

.PHONY: all clean fclean re
