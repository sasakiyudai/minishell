/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syudai <syudai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 17:48:31 by syudai            #+#    #+#             */
/*   Updated: 2021/02/07 00:28:31 by syudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	just_for_norm(char ***raw_cmd)
{
	int		semi[2];

	set_right(raw_cmd, 0, semi, 0);
	set_left(raw_cmd, 0, semi, 0);
}

void	one_command_bin(char ***cmd, char ***raw_cmd, t_arg_main *arg_main)
{
	pid_t	pid;
	int		status;
	char	*path;

	if (ft_strchr((*cmd)[0], '/') ||
	get_path(arg_main, &path, (*cmd)[0]) == 0)
	{
		pid = fork();
		if (pid == 0)
		{
			just_for_norm(raw_cmd);
			execve((ft_strchr((*cmd)[0], '/')) ? (*cmd)[0]
			: path, *cmd, arg_list_get(arg_main));
			exit(error((*cmd)[0]));
		}
		if (ft_strchr((*cmd)[0], '/') == NULL)
			free(path);
		waitpid(pid, &status, 0);
		set_hatena(arg_main, WEXITSTATUS(status));
	}
	else
	{
		set_hatena(arg_main, 127);
		error((*cmd)[0]);
	}
}

void	one_command(char ***cmd, char ***raw_cmd, t_arg_main *arg_main)
{
	int tmp;
	int semi[2];

	if ((tmp = is_builtin((*cmd)[0])))
	{
		set_right(raw_cmd, 0, semi, 0);
		set_left(raw_cmd, 0, semi, 0);
		set_hatena(g_arg_main, call_builtin(tmp, *cmd, arg_main));
	}
	else
	{
		one_command_bin(cmd, raw_cmd, arg_main);
	}
}
