/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syudai <syudai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 17:47:28 by syudai            #+#    #+#             */
/*   Updated: 2021/02/07 14:01:00 by syudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_fd(char ***cmd, char ***raw_cmd, int *fd, int j)
{
	if (*(cmd + 1) != NULL)
		dup2(fd[j + 1], 1);
	if (j != 0)
		dup2(fd[j - 2], 0);
	set_right(raw_cmd, j, fd, 1);
	set_left(raw_cmd, j, fd, 1);
}

void	wait_chiledren_and_free_fd(int cmd_len, int *fd, pid_t *pids)
{
	int		i;
	int		status;
	pid_t	ret;
	int		cnt;
	int		j;

	cnt = cmd_len;
	i = 0;
	while (i < 2 * (cmd_len - 1))
		close(fd[i++]);
	i = 0;
	while (cnt--)
	{
		ret = waitpid(-1, &status, 0);
		j = -1;
		while (++j < cmd_len)
		{
			if (ret == pids[j])
				set_hatena(g_arg_main, WEXITSTATUS(status));
		}
	}
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

	i = 0;
	while (i < 2 * (cmd_len - 1))
		close(fd[i++]);
	if ((tmp = is_builtin((*cmd)[0])))
		exit(call_builtin(tmp, *cmd, arg_main));
	else
	{
		if (ft_strchr((*cmd)[0], '/') ||
		0 == (tmp = get_path(arg_main, &path, (*cmd)[0])))
		{
			envs = arg_list_get(arg_main);
			execve((ft_strchr((*cmd)[0], '/')) ? (*cmd)[0] : path, *cmd, envs);
		}
		else if (tmp == -1)
			print_error(MALLOC_FAIL);
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

	fd = malloc(sizeof(int) * 2 * (count(cmd) - 1));
	pids = malloc(sizeof(pid_t) * count(cmd));
	i = 0;
	j = 0;
	while (i < count(cmd) - 1)
		pipe(fd + i++ * 2);
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
