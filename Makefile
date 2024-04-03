CC = cc

CFLAGS = -Wall -Werror -Wextra

SRC = pipex.c ft_malloc.c

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
