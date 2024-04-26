CC = cc

CFLAGS = -Wall -Werror -Wextra -fsanitize=address 

SRC = pipex.c ft_malloc.c pipex_utils.c valid_paths.c

OBJ = $(SRC:.c=.o)

NAME = pipex

all : $(NAME)

%.o: %.c
	$(CC) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)
re: fclean all clean
