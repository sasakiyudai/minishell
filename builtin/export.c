#include "libft.h"

int ft_len(char *args[])
{
	int i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

int	ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i])
	{
		if (s1[i] == '\0')
			return (0);
		i++;
	}
	return (s1[i] > s2[i] ? 1 : -1);
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

int export(char *args[], char *envp[])
{
	if (!args[1])
	{
		print_with_declare(envp);
		return (0);
	}
	return (0);
}

int main(int argc, char *argv[], char *envp[])
{
	export(argv, envp);
}