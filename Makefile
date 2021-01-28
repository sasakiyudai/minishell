NAME = minishell
CC = gcc
CFLAGS = -Wall -Werror -Wextra -I libft/ -I includes/
SRCS = pipe/pipe.c pipe/is_x.c pipe/utils_a.c pipe/main.c print_error.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	make -C libft/
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L libft -lft

clean:
	make clean -C libft/
	rm -f $(OBJS)

fclean:
	make fclean -C libft/
	rm -f $(OBJS)
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re