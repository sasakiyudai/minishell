#include "minishell.h"

int ft_env(t_arg_main *arg_main)
{
    int i;
// arg_list_getでenvs作成
    i = 0;
    while (env[i])
        printf("%s\n", env[i++]);
    return (0);
}