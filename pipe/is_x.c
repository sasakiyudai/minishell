/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_x.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syudai <syudai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 17:48:01 by syudai            #+#    #+#             */
/*   Updated: 2021/02/10 12:03:03 by syudai           ###   ########.fr       */
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

int		set_right_first(char ***raw_cmd, int j, int *fd, int is_pipe)
{
	int	i;
	int ffd;

	is_pipe = *fd;
	i = -1;
	while (raw_cmd[j / 2][++i])
	{
		if (create_right(raw_cmd, j, i))
			return (1);
		else if (!ft_strcmp(raw_cmd[j / 2][i], ">"))
		{
			if ((ffd = open(raw_cmd[j / 2][i + 1],
				O_CREAT | O_WRONLY | O_TRUNC, 0666)) == -1)
				return (return_print(raw_cmd[j / 2][i + 1]));
		}
		else if (!ft_strcmp(raw_cmd[j / 2][i], "<"))
			if ((ffd = open(raw_cmd[j / 2][i + 1],
				O_RDONLY, S_IRWXU)) == -1)
				return (return_print(raw_cmd[j / 2][i + 1]));
		close(ffd);
	}
	return (0);
}

int		set_right(char ***raw_cmd, int j, int *fd, int is_pipe)
{
	int r;
	int out;

	if (set_right_first(raw_cmd, j, fd, is_pipe))
		return (1);
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
			ft_putstr_fd(raw_cmd[j / 2][r > 0 ? r : -r], 2);
			ft_putstr_fd(": ", 2);
			ft_putendl_fd(strerror(errno), 2);
			return (1);
		}
		dup2(out, 1);
	}
	return (0);
}

int		set_left(char ***raw_cmd, int j, int *fd, int is_pipe)
{
	int r;
	int in;

	(void)is_pipe;
	(void)fd;
	if ((r = is_left(raw_cmd[j / 2])))
	{
		in = open(raw_cmd[j / 2][r], O_RDONLY, S_IRWXU);
		if (in == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(raw_cmd[j / 2][r], 2);
			ft_putstr_fd(": ", 2);
			ft_putendl_fd(strerror(errno), 2);
			return (1);
		}
		dup2(in, 0);
	}
	return (0);
}
