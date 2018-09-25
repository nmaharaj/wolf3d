TAG = gcc
NAME = wolf3d
FLAG = -Wall -Werror -Wextra 
INC_LIB = -I ./libft/ -L ./libft/ -lft
data = -I minilibx -L. -lmlx -framework OpenGL -framework AppKit
SRC = wolf.c

all: $(NAME)

$(NAME):
	$(TAG) $(FLAG) $(SRC) -o $(NAME) $(data) $(INC_LIB)
	
clean:
	rm -f *.o
fclean: clean
	rm -f wolf3d
	
re: fclean all