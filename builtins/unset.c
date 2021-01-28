#include "minishell.h"

int ft_unset(char *argv[], t_arg_main *arg_main)
{
    if (argv[1])
        arg_delete(arg_main, argv[1]);
	return (0);
}