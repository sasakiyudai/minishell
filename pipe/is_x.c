/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_x.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syudai <syudai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 17:48:01 by syudai            #+#    #+#             */
/*   Updated: 2021/02/01 23:53:20 by syudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_right(char **cmd)
{
	int i;
	int ret;
	int f;

	i = 0;
	ret = 0;
	f = 0;
	while (cmd[i])
	{
		if (ft_strcmp(cmd[i], ">") == 0)
		{
			ret = i + 1;
			f = 1;
		}
		if (ft_strcmp(cmd[i], ">>") == 0)
		{
			ret = -i - 1;
			f = 1;
		}
		i++;
	}
	if (f)
		return (ret);
	return (0);
}

int		is_left(char **cmd)
{
	int i;
	int ret;
	int f;

	i = 0;
	ret = 0;
	f = 0;
	while (cmd[i])
	{
		if (ft_strcmp(cmd[i], "<") == 0)
		{
			ret = i + 1;
			f = 1;
		}
		i++;
	}
	if (f)
		return (ret);
	return (0);
}

void	set_right(char ***raw_cmd, int j, int *fd, int is_pipe)
{
	int r;
	int out;

	if (is_pipe && count(raw_cmd) != j / 2 + 1)
		close(fd[j + 1]);
	if ((r = is_right(raw_cmd[j / 2])))
	{
		if (r > 0)
			out = open(raw_cmd[j / 2][r], O_CREAT | O_WRONLY
			| O_TRUNC, S_IRWXU);
		else
			out = open(raw_cmd[j / 2][-r], O_CREAT | O_WRONLY
			| O_APPEND, S_IRWXU);
		if (out == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(raw_cmd[j / 2][-r], 2);
			ft_putstr_fd(": No such file or directory", 2);
			
			return ;
		}
		dup2(out, 1);
	}
}

void	set_left(char ***raw_cmd, int j, int *fd, int is_pipe)
{
	int r;
	int in;

	if (is_pipe && j != 0)
		close(fd[j - 2]);
	if ((r = is_left(raw_cmd[j / 2])))
	{
		in = open(raw_cmd[j / 2][r], O_RDONLY, S_IRWXU);
		if (in == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(raw_cmd[j / 2][r], 2);
			ft_putstr_fd(": No such file or directory", 2);
			return ;
		}
		dup2(in, 0);
	}
}
