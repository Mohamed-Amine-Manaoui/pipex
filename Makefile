CC = cc

CFLAGS = -Wall -Werror -Wextra -fsanitize=address -g3

SRC = pipex.c ft_malloc.c pipex_utils.c valid_paths.c pipex_utils2.c

OBJ = $(SRC:.c=.o)

NAME = pipex

all : $(NAME)

%.o: %.c
	$(CC) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)
re: fclean all clean
