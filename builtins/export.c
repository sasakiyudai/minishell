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

int ft_export(char *args[], char *envp[], t_arg_main *arg_main)
{
    t_arg arg;

    if (!args[1])
    {
        print_with_declare(envp);
        return (0);
    }
    arg.name = args[2];
    arg.data = (char *)args[4];
    arg_add(arg_main, &arg);
    return (0);
}
