#include "includes/minishell.h"
#define MALLOC_FAIL 1
#define EXIT 2
#define INI_FAIL MALLOC_FAIL + EXIT

typedef int t_all;

char* g_signal;
t_arg_main* g_arg_main;

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

	if (!(cmd = separate_redirect(cmd)))
		return (NULL);
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

void print_tabs(char ***tabs)
{
	int i;

	i = 0;
	while (tabs[i])
	{
		print_tab(tabs[i]);
		i++;
	}
}

char ***make_strb_array(char ***cmd_split)
{
    char ***ret;
    int i;

    ret = malloc(sizeof (char **) * (count(cmd_split) + 1));
    i = -1;
	
    while (cmd_split[++i])
        ret[i] = make_strb(cmd_split[i]);
    ret[i] = NULL;
    return (ret);
}

void command_main(char *cmd_raw, t_arg_main *arg_main)
{
	char ***cmd_split;
	int i;
	int j;
	char *tmp;

	if (!(cmd_split = make_command_array(cmd_raw)))
		return;
	//pipeline
	i = 0;
	while (cmd_split[i])
	{
		j = 0;
		while (cmd_split[i][j])
		{
			tmp = cmd_split[i][j];
			cmd_split[i][j] = deploy(tmp, arg_main);
			free(tmp);
			j++;
		}
		i++;
	}
	//print_tabs(cmd_split);
	//print_tabs(make_strb_array(cmd_split));

	pipeline(make_strb_array(cmd_split), cmd_split, arg_main);
}



void ini(t_arg_main *arg_main, char *env[])
{
	int i;
	size_t tmp;
	t_arg arg;

	arg_main_ini(arg_main);
	g_arg_main = arg_main;
	i = -1;
	arg.type = ARG_TYPE_STR;
	while (env[++i])
	{
		tmp = (size_t)(ft_strchr(env[i], '=') - env[i]);
		arg.name = malloc(tmp + 1);
		ft_strncpy(arg.name, env[i], tmp);
		arg.data = malloc(ft_strlen(env[i]) - tmp);
		ft_strcpy((char *)(arg.data), env[i] + tmp + 1);
		arg_add(arg_main, &arg);
	}
}

/*
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
*/

void sig_handler(int sig)
{
	t_arg arg;
	
	arg.name = "?";
	arg.type = ARG_TYPE_STR;
	if (sig == SIGINT)
	{
		arg.data = ft_strdup(g_signal);
		arg_add(g_arg_main, &arg);
		free((char *)(arg.data));
		if (!ft_strcmp(g_signal, "1"))
			write(1, "\b\b  \n$ ", 7);
		else
			write(1, "\n", 1);
	}
	else if (sig == SIGQUIT && ft_strcmp(g_signal, "1"))
	{
		arg.data = "131";
		arg_add(g_arg_main, &arg);
		write(1, "Quit: 3\n", 8);
	}
	else if (sig == SIGQUIT)
		write(1, "\b\b  \b\b", 6);
	// else if (sig == )
	printf("%d\n", sig);
}

int main(int argc, char *argv[], char *env[])
{
	char *cmd_all;
	char **cmd_split;
	char **tmp_cmd_split;
	t_arg_main arg_main;
	(void)argc;
	(void)argv;
	ini(&arg_main, env);
	while (1)
	{
		set_hatena(&arg_main, 12);
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, sig_handler);
		write(1, "$ ", 2);
		g_signal = "1";
		cmd_all = read_all(0);
		g_signal = "130";
		if (syntax_check(cmd_all))
		{
			free(cmd_all);
			continue;
		}
		cmd_split = split_command(cmd_all, ';');
		tmp_cmd_split = cmd_split;
		while (*cmd_split)
		{
			command_main(*cmd_split, &arg_main);
			cmd_split++;
		}
		split_free_all(tmp_cmd_split);
		free(cmd_all);
	}
}
