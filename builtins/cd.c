/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syudai <syudai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 11:20:22 by syudai            #+#    #+#             */
/*   Updated: 2021/02/10 11:21:30 by syudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>
#include <string.h>
#define MAX_FILENAME 1024

void	cd_error(char **args)
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

int		update(t_arg_main *arg_main)
{
	t_arg_list	*arg_list;
	t_arg_list	*arg_list_pwd;
	char		s[MAX_FILENAME + 1];

	if ((arg_list = arg_isexist(arg_main, "OLDPWD")))
	{
		free(arg_list->arg.data);
		if ((arg_list_pwd = arg_isexist(arg_main, "PWD")))
			arg_list->arg.data = ft_strdup(arg_list_pwd->arg.data);
		else
		{
			getcwd(s, MAX_FILENAME);
			if (g_arg_main->pwd_slash)
				arg_list->arg.data = ft_strjoin("/", s);
			else
				arg_list->arg.data = ft_strdup(s);
		}
	}
	return (0);
}

int		update_pwd(t_arg_main *arg_main)
{
	char		cwd[MAX_FILENAME + 1];
	t_arg_list	*arg_list;

	if ((arg_list = arg_isexist(arg_main, "PWD")))
	{
		if (getcwd(cwd, MAX_FILENAME) == NULL)
			return (1);
		free(arg_list->arg.data);
		if (arg_main->pwd_slash)
			arg_list->arg.data = ft_strjoin("/", cwd);
		else
			arg_list->arg.data = ft_strdup(cwd);
		return (0);
	}
	return (0);
}

int		cd_process(t_arg_main *arg_main, char *dest, char **args)
{
	int	cd_ret;

	cd_ret = chdir(dest);
	if (cd_ret < 0)
		cd_ret *= -1;
	if (cd_ret != 0)
		cd_error(args);
	if (cd_ret == 0)
	{
		update(arg_main);
		if (ft_strlen(dest) >= 1 && dest[0] == '/' && dest[1] != '/')
			arg_main->pwd_slash = 0;
		if (ft_strlen(dest) >= 2 &&
			dest[0] == '/' && dest[1] == '/')
			arg_main->pwd_slash = dest[2] != '/';
		return (update_pwd(arg_main));
	}
	return (cd_ret);
}

int		ft_cd(char **args, t_arg_main *arg_main)
{
	int		cd_ret;
	char	*dest;
	t_arg	arg;

	if (ft_len(args) == 1)
	{
		if (arg_get(arg_main, &arg, "HOME") || arg.data == NULL)
			return (1 + 0 * (write(2, "bash: cd: HOME not set\n", 23)));
		dest = ft_strdup(arg.data);
		arg_free(&arg);
	}
	else
		dest = ft_strdup(args[1]);
	if (!dest[0])
	{
		free(dest);
		arg_main->pwd_slash = 0;
		update(arg_main);
		return (0);
	}
	cd_ret = cd_process(arg_main, dest, args);
	free(dest);
	return (cd_ret);
}
