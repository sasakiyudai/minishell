#include "minishell.h"
#define MAX_FILENAME 1024

int ft_cd(char *args[])
{
	char s[MAX_FILENAME]; 
  
    printf("%s\n", getcwd(s, MAX_FILENAME)); 
	if (args[1] == NULL)
		printf("with only a relative or absolute path");
	else
	{
		if (chdir(args[1]) != 0)
			perror("cd");
	}
    printf("%s\n", getcwd(s, MAX_FILENAME)); 
    return 0; 
}