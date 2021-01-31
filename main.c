#include "minishell.h"
#define MALLOC_FAIL 1
#define EXIT 2
#define INI_FAIL MALLOC_FAIL + EXIT

typedef int t_all;

char	**split_command(char *s, char c);

void	ft_strncpy(char *dest, char *src, size_t n)
{
	dest[n] = '\0';
	while (n--)
		dest[n] = src[n];
}

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
	//pipeline
}



void ini(t_arg_main *arg_main, char *env[])
{
	int i;
	size_t tmp;
	t_arg arg;

	arg_main_ini(arg_main);
	i = -1;
	arg.type = ARG_TYPE_STR;
	while (env[++i])
	{
		tmp = (size_t)(ft_strchar(env[i], '=') - env[i]);
		arg.name = malloc(tmp + 1);
		ft_strncpy(arg.name, env[i], tmp);
		arg.data = malloc(ft_strlen(env[i]) - tmp);
		ft_strcpy((char *)(arg.data), env[i] + tmp + 1);
		arg_add(arg_main, &arg);
	}
}

int main(int argc, char *argv[], char *env[])
{
	t_arg_main arg_main;
	ini(&arg_main, env);
	char **s = arg_list_get(&arg_main);
	int i = -1;
	while (s[++i])
	{
		printf("%s\n", s[i]);
	}

}

/*
int main(int argc, char *argv[], char *env[])
{
	char *cmd_all;
	char **cmd_split;
	char **tmp_cmd_split;
	t_arg_main arg_main;

	ini(&arg_main, env);
	while (1)
	{
		cmd_all = read_all(0);
		cmd_split = split_command(cmd_all, ';');
		tmp_cmd_split = cmd_split;
		while (*cmd_split)
		{
			command_main(*cmd_split);
			cmd_split++;
		}
		split_free_all(tmp_cmd_split);
		free(cmd_all);	
	}
}

*/