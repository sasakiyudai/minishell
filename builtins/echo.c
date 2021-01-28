#include "minishell.h"

int ft_echo(char *args[])
{
	int i;
	int is_n;

	i = 1;
	is_n = 0;
	if (ft_len(args) != 1)
	{
		while (args[i] && ft_strncmp("-n", args[i], ft_strlen(args[i])) == 0)
		{
			is_n = 1;
			i++;
		}
		while (args[i])
		{
			ft_putstr_fd(args[i], 1);
			if (args[i][0] != '\0' && args[i + 1])
				write(1, " ", 1);
			i++;
		}
	}
	if (!is_n)
		write(1, "\n", 1);
	return (0);
}
