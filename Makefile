NAME = minishell
CL = clang 
CC = gcc
CFLAGS = -Wall -Werror -Wextra -I libft/ -I includes/
SANI = -fsanitize=address
LEAK = -fsanitize=leak
SRCS = pipe/pipe.c pipe/is_x.c pipe/utils_a.c pipe/main.c builtins/cd.c\
		builtins/echo.c builtins/export.c builtins/pwd.c builtins/unset.c \
		builtins/env.c read_all.c get_exec_path.c syntax_check/syntax_check.c\
		syntax_check/syntax_check_process.c quotes.c make_strb.c  builtins/exit.c pipe/utils_b.c\
		quote.c make_strb_two.c utils/utils.c utils/utils2.c utils/utils_c.c\
		argument/arg_utils.c argument/arg_utils2.c argument/arglist_get.c\
		argument/arglist_initialize.c argument/arglist_manage.c split_command.c\
		main/ini.c main/main.c main/main2.c main/make_strb.c main/command_array.c\
		pipe/utils_c.c pipe/utils_d.c builtins/export2.c
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
