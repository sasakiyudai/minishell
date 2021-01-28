#include "minishell.h"
#define MALLOC_FAIL 1
#define EXIT 2
#define INI_FAIL MALLOC_FAIL + EXIT

typedef int t_all;

char	**split_command(char *s, char c);

void	print_error(int i)
{
	i++;
}

char **make_command_array_splitpipe(char *cmd)
{
	char **cmd_split;

//	if (!(cmd = separate_redirect(cmd)))
//		return (NULL);
	if (!(cmd_split = split_command(cmd, '|')))
	{
		free(cmd);
		return (NULL);
	}
	return (cmd_split);
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
		split_free_all(cmd[i]);
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

void command_main(char *cmd_raw)
{
	char ***cmd_split;

	if (!(cmd_split = make_command_array(cmd_raw)))
		return;
	int i = -1;
	while (cmd_split[++i])
	{
		int j = -1;
		while (cmd_split[i][++j])
			printf("%s\n", cmd_split[i][j]);
	}
}
/*

typedef struct s_syntax_check
{
	char pipe;
	char redirect;
}	t_syntax_check;

 int _syntax_check_main_process
int syntax_check_main(char *cmd)
{
	char bitflag_quote;
	t_syntax_check check;
	int tmp;

	_bzero(&check, sizeof (t_syntax_check));
	bitflag_quote = 0;
	while (*cmd)
	{
		if (!(tmp = _syntax_check_main_process(cmd, &check)))
			return (tmp);
		cmd++;
	}
	return (0);
}

int main(void)
{
	command_main(NULL, "cat >text ||| ls");
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

*/