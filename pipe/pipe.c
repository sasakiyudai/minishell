/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 17:47:28 by syudai            #+#    #+#             */
/*   Updated: 2021/02/10 17:37:50 by rnitta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		wait_support(int cmd_len, int *status, pid_t *ret, pid_t *pids)
{
	int j;

	*ret = waitpid(-1, status, 0);
	j = -1;
	while (++j < cmd_len)
	{
		if (*ret == pids[j])
		{
			if (!WIFSIGNALED(*status))
			{
				if (j == cmd_len - 1)
					set_hatena(g_arg_main, WEXITSTATUS(*status));
			}
			else if (WTERMSIG(*status) != 13)
				return (1);
		}
	}
	return (0);
}

void	wait_chiledren_and_free_fd(int cmd_len, int *fd, pid_t *pids)
{
	int		i;
	int		status;
	pid_t	ret;
	int		cnt;

	cnt = cmd_len;
	i = 0;
	while (i < 2 * (cmd_len - 1))
		close(fd[i++]);
	i = 0;
	while (cnt--)
	{
		i |= wait_support(cmd_len, &status, &ret, pids);
	}
	write(2, "\n", i);
	free(pids);
	free(fd);
}

void	exec_child(int cmd_len, int *fd, char ***cmd, t_arg_main *arg_main)
{
	int		exit_code;
	int		i;
	int		tmp;
	char	*path;
	char	**envs;

	init_exec(&i, cmd_len, fd);
	if (rare_exception(arg_main->raw))
		bin_e(arg_main->raw);
	else if ((tmp = is_builtin((*cmd)[0])))
		exit(call_builtin(tmp, *cmd, arg_main));
	else
	{
		if (ft_strchr((*cmd)[0], '/') ||
		0 == (tmp = get_path(arg_main, &path, (*cmd)[0])))
		{
			envs = arg_list_get(arg_main);
			execve((ft_strchr((*cmd)[0], '/')) ? (*cmd)[0] : path, *cmd, envs);
		}
		else if (tmp == 1)
			p_exit((*cmd)[0]);
		exit_code = error((*cmd)[0]);
		exit(exit_code);
	}
}

void	pipeline2(char ***cmd, char ***raw_cmd, t_arg_main *arg_main)
{
	int		i;
	int		j;
	pid_t	pid;
	pid_t	*pids;
	int		*fd;

	fd = malloc2(sizeof(int) * 2 * (count(cmd) - 1));
	pids = malloc2(sizeof(pid_t) * count(cmd));
	arg_main->raw = raw_cmd;
	init_pipe(&i, &j, count(cmd), fd);
	while (*cmd != NULL)
	{
		pid = fork();
		if (pid == 0)
		{
			set_fd(cmd, raw_cmd, fd, j);
			exec_child(i + 1, fd, cmd, arg_main);
		}
		pids[j / 2] = pid;
		cmd++;
		(arg_main->raw)++;
		j += 2;
	}
	wait_chiledren_and_free_fd(i + 1, fd, pids);
}

void	pipeline(char ***cmd, char ***raw_cmd, t_arg_main *arg_main)
{
	if (count(cmd) == 1 && raw_cmd[0][0] != NULL)
		one_command(cmd, raw_cmd, arg_main);
	else if (count(cmd) > 1)
		pipeline2(cmd, raw_cmd, arg_main);
}
