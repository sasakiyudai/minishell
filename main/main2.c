#include "minishell.h"

char		*g_signal;
t_arg_main	*g_arg_main;

void	command_main_free(char ***cmd_split, char ***tmp_cmd_split)
{
	int i;

	i = -1;
	while (cmd_split[++i])
		split_free_all(cmd_split[i]);
	free(cmd_split);
	i = -1;
	while (tmp_cmd_split[++i])
		free(tmp_cmd_split[i]);
	free(tmp_cmd_split);
}

