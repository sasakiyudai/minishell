#include "minishell.h"

int ft_env(t_arg_main *arg_main)
{
	int i;
	int j;
	char **env;

	i = 0;
	env = arg_list_get(arg_main);
	while (env[i])
	{
		j = 0;
		while (env[i][j])
			if (env[i][j++] == -1)
				break;
		printf("%s\n", env[i++]);
	}
	return (0);
}
