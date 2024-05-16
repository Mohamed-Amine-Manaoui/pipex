CC = cc

CFLAGS = -Wall -Werror -Wextra

SRC = mandatory/pipex.c ft_malloc.c mandatory/pipex_utils.c mandatory/valid_paths.c mandatory/pipex_utils2.c mandatory/child_first.c mandatory/child_second.c mandatory/pipex_utils3.c mandatory/pipex_utils4.c mandatory/pipex_utils5.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c

SRCB = bonus/pipex_bonus.c bonus/child_first_bonus.c bonus/child_second_bonus.c bonus/child_n_bonus.c ft_malloc.c mandatory/pipex_utils.c mandatory/valid_paths.c mandatory/pipex_utils2.c  mandatory/pipex_utils3.c mandatory/pipex_utils4.c mandatory/pipex_utils5.c bonus/pipex_utils_bonus.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c bonus/here_doc_bonus.c

OBJB = $(SRCB:.c=.o)

OBJ = $(SRC:.c=.o)


NAME = pipex

NAME_BONUS = pipex_bonus

all : $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

bonus: $(OBJB)
	$(CC) $(CFLAGS) $(OBJB) -o $(NAME_BONUS)

clean:
	rm -rf $(OBJ) $(OBJB)

fclean: clean
	rm -rf $(NAME) $(NAME_BONUS)
re: fclean all clean
