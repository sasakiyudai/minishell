#include "minishell.h"

int ft_len(char *args[])
{
	int i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

void sort(char *envp[])
{
	int i;
	int j;
	char *tmp;

	i = 0;
	while (i < ft_len(envp) - 1)
	{
		j = 1;
		while (j < ft_len(envp) - i)
		{
			if (ft_strcmp(envp[j], envp[j - 1]) < 0)
			{
				tmp = envp[j];
				envp[j] = envp[j - 1];
				envp[j - 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

void print_with_declare(char *envp[])
{
	int i;

	sort(envp);
	i = 0;
	while (envp[i])
		printf("declare -x %s\n", envp[i++]);
}

void	export_err(int err, char *cmd)
{
	if (err == BAD_ARGNAME)
		printf("bash: export: `%s\': not a valid identifier\n", cmd);
}

int export_name_check(char *cmd)
{
	if (!ft_isalpha(*cmd) && *cmd != '_')
		return (1);
	while (*cmd)
	{
		if (*cmd == '=')
			return (0);
		if (!ft_isalnum(*cmd) && *cmd != '_')
			return (1);
		cmd++;
	}
	return (0);
}

void	export_argadd(char *args[], t_arg_main *arg_main)
{
	t_arg arg;
	int len;
	char *tmp;

	arg.type = ARG_TYPE_STR;
	while (*args)
	{
		if (export_name_check(*args))
			export_err(BAD_NAME, *args);
		else if ((tmp = ft_strchr(*args, '=')))
		{
			arg.name = ft_strndup(*args, (int)(tmp - *args));
			arg.data = ft_strdup(tmp + 1);
		}
		else
		{
			arg.name = ft_strdup(*args);
			arg.data = NULL;
		}
		arg_add(arg_main, &arg.data);
		free(&arg);
		args++;
	}
}

int ft_export(char *args[], char *envp[], t_arg_main *arg_main)
{
	if (!args[1])
    {
        print_with_declare(envp);
        return (0);
    }
	export_argadd(args, arg_main);
}
