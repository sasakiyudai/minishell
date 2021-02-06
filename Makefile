NAME = minishell
CL = clang 
CC = gcc
CFLAGS = -Wall -Werror -Wextra -I libft/ -I includes/
SANI = -fsanitize=address
LEAK = -fsanitize=leak
SRCS = pipe/pipe.c pipe/is_x.c pipe/utils_a.c pipe/main.c builtins/cd.c\
		builtins/echo.c builtins/export.c builtins/pwd.c builtins/unset.c \
		builtins/env.c read_command.c get_exec_path.c argument.c\
		main.c quotes.c make_strb.c syntax_check.c builtins/exit.c pipe/utils_b.c\
		utils_c.c quote.c make_strb_two.c
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

sani:  $(OBJS)
	make -C libft/
	$(CC) $(CFLAGS) $(SANI) -o $(NAME) $(OBJS) -L libft -lft

leak: $(OBJS)
	make -C libft/
	$(CL) $(CFLAGS) $(LEAK) -o $(NAME) $(OBJS) -L libft -lft


.PHONY: clean fclean re
