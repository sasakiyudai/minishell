#include <stdlib.h>
#include "minishell.h"

#define MALLOC_FAIL 1
#define EXIT 2
#define INI_FAIL MALLOC_FAIL + EXIT

/*
char **make_command_array_splitpipe(char *cmd)
{
	char **cmd_split;

	if (!(cmd = separate_redirect(cmd)))
		return (NULL);
	if (!(cmd_split = split_command(cmd, '|')))
	{
		free(cmd);
		return (NULL);
	}
}
*/

void	print_error(int i)
{

}

char ***make_command_array_malloc(char **tmp)
{
	int cnt;
	char ***ret;

	cnt = 0;
	while (tmp[cnt])
		cnt++;
	if (!(ret = (char ***)malloc(sizeof (char **) * (cnt + 1))))
	{
		print_error(MALLOC_FAIL);
		split_free_all(tmp);
		return (NULL);
	}
	return (ret);
}

void	command_array_free(char ***cmd)
{
	int i;

	i = -1;
	while (cmd[++i])
		split_fre_all(cmd[i]);
	free(cmd);
}

char ***make_command_array(char *cmd)
{
	char **tmp;
	char ***ret;
	int i;

	if (!(tmp = make_command_array_splitpipe(cmd)))
		return (NULL);
	if (!(ret = make_command_array_malloc(tmp)))
		return (NULL);
	i = -1;
	while (tmp[++i])
		if (!(ret[i] = split_command(tmp[i], ' ')))
		{
			command_array_free(ret);
			return (NULL);
		}
	ret[i] = NULL;
	return (ret);
}

void command_main(t_all *all, char *cmd_raw)
{
	char ***cmd_split;
	int process_num;

	if (!(cmd_split = make_command_array(cmd_raw)))
		return;
	int i = -1;
	while (cmd_split[++i])
	{
		int j = -1;
		while (cmd[i][++j])
			printf("%s\n", cmd[i][j]);
	}
}

int ini(t_all *all)
{
	if (!(arg_main_ini(&(all->arg_main))))
	{
		error(INI_FAIL);
		return (-1);
	}
}

int main(void)
{
	char *cmd_all;
	char **cmd_split;
	char **tmp_cmd_split;
	t_all all;

	if (ini(&all))
		while (1)
		{
			while (!(cmd_all = read_all(0)))
				error(MALLOC_FAIL);
			if (!(cmd_split = split_command(cmd_all, ';')))
				error(MALLOC_FAIL);
			else
			{
				tmp_cmd_split = cmd_split;
				while (*cmd_split)
				{
					command_main(*cmd_split);
					cmd_split++;
				}
				split_free_all(tmp_cmd_split);
			}
			free(cmd_all);	
		}

}
