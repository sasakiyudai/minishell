#include "minishell.h"
#include <errno.h>
#include <string.h>
#define MAX_FILENAME 1024

void cd_error(char **args)
{
    ft_putstr_fd("cd: ", 2);
	if (args[1])
	{
    	ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
	}
	else
	{
		ft_putstr_fd("", 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd("No such file or directory", 2);
	}
}

int update(t_arg_main *arg_main)
{
    char    cwd[MAX_FILENAME];
    t_arg   arg;
    t_arg   tmp_arg;

    if (getcwd(cwd, MAX_FILENAME) == NULL)
        return (1);
	arg.data = cwd;
	arg.name = "OLDPWD";
	arg.type = ARG_TYPE_STR;
    if (arg_get(arg_main, &tmp_arg, "OLDPWD") == 1)
	{
        arg_add(arg_main, &arg);
	}
    return (0);
}

int ft_cd(char **args, t_arg_main *arg_main)
{
    int     cd_ret;
    
	if (ft_len(args) != 2)
	{
		cd_error(args);
		return (1);
	}
	/* fprintf(stderr, "\n\n\n\n\n\n\n\n");
	print_tab(args);
	fprintf(stderr, "\n\n\n\n\n\n\n\n"); */
	update(arg_main);
	cd_ret = chdir(args[1]);
	if (cd_ret < 0)
		cd_ret *= -1;
	if (cd_ret != 0)
		cd_error(args);
    return (cd_ret);
}
