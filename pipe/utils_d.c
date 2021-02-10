/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syudai <syudai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 12:16:48 by syudai            #+#    #+#             */
/*   Updated: 2021/02/10 12:17:16 by syudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_one_to_seven(t_arg_main *arg_main, char *cmd)
{
	set_hatena(arg_main, 127);
	error(cmd);
}

void	just_for_child(char ***r, char ***cmd, char *path, t_arg_main *ar)
{
	just_for_norm(r);
	execve((ft_strchr((*cmd)[0], '/')) ? (*cmd)[0]
	: path, *cmd, arg_list_get(ar));
	exit(error((*cmd)[0]));
}
