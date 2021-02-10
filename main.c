#include "includes/minishell.h"

char		*g_signal;
t_arg_main	*g_arg_main;

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

char	**make_command_array_splitpipe(char *cmd)
{
	char **cmd_split;

	if (!(cmd = separate_redirect(cmd)))
		return (NULL);
	if (!(cmd_split = split_command(cmd, '|')))
	{
		free(cmd);
		return (NULL);
	}
	free(cmd);
	return (cmd_split);
}

char	***make_command_array_malloc(char **tmp)
{
	int		cnt;
	char	***ret;

	cnt = 0;
	while (tmp[cnt])
		cnt++;
	ret = (char ***)malloc(sizeof(char **) * (cnt + 1));
	return (ret);
}

void	command_array_free(char ***cmd)
{
	int	i;

	i = -1;
	while (cmd[++i])
		split_free_all(cmd[i]);
	free(cmd);
}

char	***make_command_array(char *cmd)
{
	char	**tmp;
	char	***ret;
	int		i;

	tmp = make_command_array_splitpipe(cmd);
	ret = make_command_array_malloc(tmp);
	i = -1;
	while (tmp[++i])
		ret[i] = split_command(tmp[i], ' ');
	split_free_all(tmp);
	ret[i] = NULL;
	return (ret);
}

void	print_tabs(char ***tabs)
{
	int	i;

	i = 0;
	while (tabs[i])
	{
		print_tab(tabs[i]);
		i++;
	}
}

char	***make_strb_array(char ***cmd_split)
{
	char	***ret;
	int		i;

	ret = malloc(sizeof(char **) * (count(cmd_split) + 1));
	i = -1;
	while (cmd_split[++i])
		ret[i] = make_strb(cmd_split[i]);
	ret[i] = NULL;
	return (ret);
}

int		is_strb_empty(char *s)
{
	int	ret;

	if (!*s)
		return (0);
	ret = 1;
	while (*s)
	{
		if (*s != -1)
			ret = 0;
		s++;
	}
	return (ret);
}

void	remove_empty_strb(char **cmd_split, int *i)
{
	if (is_strb_empty(cmd_split[*i]))
		free(cmd_split[*i]);
	else
	{
		remove_quotes(cmd_split[*i]);
		(*i)++;
	}
}

void	command_main_fre(char ***cmd_split, char ***tmp_cmd_split)
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

void	command_main(char *cmd_raw, t_arg_main *arg_main)
{
	char	***cmd_split;
	char	***tmp_cmd_split;
	int		i;
	int		j;
	char	*tmp;

	cmd_split = make_command_array(cmd_raw);
	tmp_cmd_split = cmd_split;
	while (*tmp_cmd_split)
	{
		j = -1;
		i = 0;
		while (tmp_cmd_split[0][++j])
		{
			tmp = tmp_cmd_split[0][j];
			tmp_cmd_split[0][i] = deploy(tmp, arg_main);
			free(tmp);
			remove_empty_strb(tmp_cmd_split[0], &i);
		}
		tmp_cmd_split[0][i] = NULL;
		tmp_cmd_split++;
	}
	pipeline((tmp_cmd_split = make_strb_array(cmd_split)), cmd_split, arg_main);
	command_main_fre(cmd_split, tmp_cmd_split);
}

void	ini3(t_arg_main *arg_main, char *env)
{
	t_arg	arg;

	arg.name = ft_strdup(env);
	arg.data = NULL;
	arg_add(arg_main, &arg);
	arg_free(&arg);
}

void	ini2(t_arg_main *arg_main, char *env)
{
	size_t	tmp;
	t_arg	arg;

	tmp = (size_t)(ft_strchr(env, '=') - env);
	arg.name = malloc(tmp + 1);
	ft_strncpy(arg.name, env, tmp);
	if (ft_strcmp(arg.name, "OLDPWD"))
	{
		arg.data = malloc(ft_strlen(env) - tmp);
		ft_strcpy((char *)(arg.data), env + tmp + 1);
	}
	else
		arg.data = NULL;
	arg_add(arg_main, &arg);
	arg_free(&arg);
}

void	ini(t_arg_main *arg_main, char *env[])
{
	t_arg	arg;
	int		i;

	i = -1;
	arg_main_ini(arg_main);
	g_arg_main = arg_main;
	arg_main->pwd_slash = 0;
	arg.type = ARG_TYPE_STR;
	while (env[++i])
		if (ft_strchr(env[i], '='))
			ini2(arg_main, env[i]);
		else
			ini3(arg_main, env[i]);
	arg.data = NULL;
	arg.name = "OLDPWD";
	arg_add(arg_main, &arg);
}

void	sig_handler(int sig)
{
	t_arg	arg;

	arg.name = "?";
	arg.type = ARG_TYPE_STR;
	if (sig == SIGINT)
	{
		arg.data = ft_strdup(g_signal);
		arg_add(g_arg_main, &arg);
		free((char *)(arg.data));
		if (!ft_strcmp(g_signal, "1"))
			write(1, "\b\b  \n$ ", 7);
	}
	else if (sig == SIGQUIT && ft_strcmp(g_signal, "1"))
	{
		arg.data = "131";
		arg_add(g_arg_main, &arg);
		write(2, "Quit: 3", 7);
	}
	else if (sig == SIGQUIT)
		write(2, "\b\b  \b\b\n$ ", 9);
}

char	*main_process_ini(void)
{
	char	*cmd_all;

	write(2, "$ ", 2);
	g_signal = "1";
	cmd_all = read_all(0);
	g_signal = "130";
	if (syntax_check(cmd_all))
	{
		free(cmd_all);
		return (NULL);
	}
}

void	main_process(t_arg_main *arg_main)
{
	char		*cmd_all;
	char		**cmd_split;
	char		**tmp_cmd_split;

	while (1)
	{
		if (!(cmd_all = main_process_ini()))
			continue;
		cmd_split = split_command(cmd_all, ';');
		tmp_cmd_split = cmd_split;
		while (*cmd_split)
		{
			command_main(*cmd_split, arg_main);
			dup2(arg_main->std_in, 0);
			dup2(arg_main->std_out, 1);
			cmd_split++;
		}
		split_free_all(tmp_cmd_split);
		free(cmd_all);
	}
}

int		main(int argc, char *argv[], char *env[])
{
	t_arg_main	arg_main;

	(void)argc;
	(void)argv;
	ini(&arg_main, env);
	arg_main.std_in = dup(0);
	arg_main.std_out = dup(1);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	main_process(&arg_main);
	arg_list_ini(&arg_main);
	arg_free(&arg_main.head.arg);
	system("leaks minishell");
	return (0);
}
