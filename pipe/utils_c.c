/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_c.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syudai <syudai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 11:54:06 by syudai            #+#    #+#             */
/*   Updated: 2021/02/10 12:05:49 by syudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_exec(int *i, int cmd_len, int *fd)
{
	*i = 0;
	while (*i < 2 * (cmd_len - 1))
		close(fd[(*i)++]);
}

void	p_exit(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	exit(127);
}

void	init_pipe(int *i, int *j, int count, int *fd)
{
	*i = 0;
	*j = 0;
	while (*i < count - 1)
		pipe(fd + (*i)++ * 2);
}

void	set_fd(char ***cmd, char ***raw_cmd, int *fd, int j)
{
	if (*(cmd + 1) != NULL)
		dup2(fd[j + 1], 1);
	if (j != 0)
		dup2(fd[j - 2], 0);
	if (set_right(raw_cmd, j, fd, 1))
		exit(1);
	if (set_left(raw_cmd, j, fd, 1))
		exit(1);
}

void	just_for_norm(char ***raw_cmd)
{
	int		semi[2];

	if (set_right(raw_cmd, 0, semi, 0))
		exit(1);
	if (set_left(raw_cmd, 0, semi, 0))
		exit(1);
}
