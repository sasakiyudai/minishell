#include "minishell.h"

int ft_env(t_arg_main *arg_main)
{
    int i;
	char **env;

	env = arg_list_get(arg_main, 0);
    i = 0;
    while (env[i])
        printf("%s\n", env[i++]);
    return (0);
}
