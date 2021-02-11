/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syudai <syudai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 17:48:31 by syudai            #+#    #+#             */
/*   Updated: 2021/02/11 21:49:49 by syudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	err_general(char *s, char *err, int status)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(err, 2);
	set_hatena(g_arg_main, status);
}

void	one_command_bin(char ***cmd, char ***raw_cmd, t_arg_main *arg_main)
{
	pid_t	pid;
	int		status;
	char	*path;

	path = NULL;
	if ((pid = fork()) == 0)
	{
		just_for_norm(raw_cmd);
		just_for_child(raw_cmd, cmd, path, arg_main);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		set_hatena(arg_main, WEXITSTATUS(status));
	else
		write(2, "\n", 1);
}

void	one_command_bin_e(char ***raw_cmd, t_arg_main *arg_main)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		just_for_norm(raw_cmd);
		exit(0);
	}
	waitpid(pid, &status, 0);
	set_hatena(arg_main, WEXITSTATUS(status));
}

int		rare_exception(char ***raw_cmd)
{
	int i;

	i = 0;
	while ((*raw_cmd)[i])
	{
		if (i % 2 == 0)
		{
			if (ft_strcmp(">", (*raw_cmd)[0]) != 0
			&& ft_strcmp("<", (*raw_cmd)[0]) != 0
			&& ft_strcmp(">>", (*raw_cmd)[0]) != 0)
				return (0);
		}
		i++;
	}
	if (i % 2 != 0 || i == 0)
		return (0);
	return (1);
}

void	one_command(char ***cmd, char ***raw_cmd, t_arg_main *arg_main)
{
	int tmp;
	int semi[2];

	if (rare_exception(raw_cmd))
		one_command_bin_e(raw_cmd, arg_main);
	else if ((tmp = is_builtin((*cmd)[0])))
	{
		if (set_right(raw_cmd, 0, semi, 0) ||
			set_left(raw_cmd, 0, semi, 0))
		{
			set_hatena(arg_main, 1);
			return ;
		}
		set_hatena(g_arg_main, call_builtin(tmp, *cmd, arg_main));
	}
	else
	{
		one_command_bin(cmd, raw_cmd, arg_main);
	}
}
