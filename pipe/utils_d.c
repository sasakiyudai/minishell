/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syudai <syudai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 12:16:48 by syudai            #+#    #+#             */
/*   Updated: 2021/02/11 22:15:27 by syudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_one_to_seven(t_arg_main *arg_main, char *cmd)
{
	(void)arg_main;
	error(cmd);
}

void	just_for_child(char ***r, char ***cmd, char *path, t_arg_main *ar)
{
	int ret;

	ret = 0;
	(void)r;
	if (ft_strchr((*cmd)[0], '/') ||
	(ret = get_path(ar, &path, (*cmd)[0])) == 0)
	{
		execve((ft_strchr((*cmd)[0], '/')) ? (*cmd)[0]
		: path, *cmd, arg_list_get(ar));
		exit(error((*cmd)[0]));
	}
	else if (ret == 1)
		err_general((*cmd)[0], "command not found", 127);
	else
		error_one_to_seven(ar, (*cmd)[0]);
	exit(127);
}
