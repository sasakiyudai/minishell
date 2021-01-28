#include "minishell.h"
#define MAX_FILENAME 1024

int ft_pwd(void)
{
	char s[MAX_FILENAME];

	if (!getcwd(s, MAX_FILENAME))
		return (1);
	else
		ft_putendl_fd(s, 1);
	return (0);
}
