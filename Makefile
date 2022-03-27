NAME=pipex

CC=gcc

SRCS= pipex.c ft_split.c tools.c childs.c

FLAGS=-Wall -Wextra -Werror 



all: $(NAME)

$(NAME):
	$(CC) $(FLAGS) $(SRCS) -o $(NAME)

clean:
	rm -rf $(NAME)

fclean: clean
	rm -rf $(NAME)

re: fclean all