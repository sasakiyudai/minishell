#include "libft.h"
#define MAX_FILENAME 1024

int cd(char *args[])
{
	char s[MAX_FILENAME]; 
  
    // printing current working directory 
    printf("%s\n", getcwd(s, MAX_FILENAME)); 
  
	if (args[1] == NULL)
		printf("with only a relative or absolute path");
	else
	{
		if (chdir(args[1]) != 0)
			perror("cd");
	}

    // printing current working directory 
    printf("%s\n", getcwd(s, MAX_FILENAME)); 

    return 0; 
}

// hit like "./a.out {relative/absolute path}"
int main(int argc, char** argv)
{
    cd(argv);
}