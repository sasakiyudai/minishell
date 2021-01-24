//#include <stdio.h>
//
//int main(int argc, char *argv[])
//{
//	printf("%s\n",argv[0]);
//	printf("%s\n",argv[1]);
//	printf("%s\n",argv[2]);
//}

// come here if ft_strcmp("echo", args[0]) == 0

#include "libft.h"

int ft_len(char *args[])
{
	int i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

int echo(char *args[])
{
	int i;
	int is_n;

	i = 1;
	is_n = 0;
	if (ft_len(args) != 1) // only "echo" should return "\n"
	{
		while (args[i] && ft_strncmp("-n", args[i], ft_strlen(args[i])) == 0) // "-n" can exitst more than one.
		{
			is_n = 1;
			i++;
		}
		while (args[i])
		{
			ft_putstr_fd(args[i], 1);
			if (args[i][0] != '\0' && args[i + 1]) // if there is next char, " " is needed.
				write(1, " ", 1);
			i++;
		}
	}
	if (!is_n) // whthout n option, or only echo, "\n" is needed.
		write(1, "\n", 1);
	return (0);
}

// args = ["echo", "-n", "hello", "world!", "a b c"]
// test required to change "echo" to nothing
int main(int argc, char **argv)
{
	echo(argv);
}