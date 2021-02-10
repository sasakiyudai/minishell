/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_a.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syudai <syudai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 17:48:51 by syudai            #+#    #+#             */
/*   Updated: 2021/02/10 12:03:37 by syudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		count(char ***cmd)
{
	int i;

	i = 0;
	while (cmd[i])
		i++;
	return (i);
}

void	safe_close(int fd)
{
	if (fd > 0)
		close(fd);
}

void	bin_e(char ***raw_cmd)
{
	just_for_norm(raw_cmd);
	exit(0);
}

int		return_print(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errno), 2);
	return (1);
}

int		create_right(char ***raw_cmd, int j, int i)
{
	int ffd;

	if (!ft_strcmp(raw_cmd[j / 2][i], ">>"))
	{
		if ((ffd = open(raw_cmd[j / 2][i + 1],
			O_CREAT | O_WRONLY | O_APPEND, 0666)) == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(raw_cmd[j / 2][i + 1], 2);
			ft_putstr_fd(": ", 2);
			ft_putendl_fd(strerror(errno), 2);
			return (1);
		}
		close(ffd);
	}
	return (0);
}
