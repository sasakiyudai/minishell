/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syudai <syudai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 17:47:28 by syudai            #+#    #+#             */
/*   Updated: 2021/01/28 17:47:47 by syudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_fd(char ***cmd, char ***raw_cmd, int *fd, int j)
{
	if (*(cmd + 1) != NULL)
		dup2(fd[j + 1], 1);
	if (j != 0)
		dup2(fd[j - 2], 0);
	set_right(raw_cmd, j, fd);
	set_left(raw_cmd, j, fd);
}

void	wait_chiledren_and_free_fd(int cmd_len, int *fd)
{
	int i;

	i = 0;
	i = 0;
	while (i < 2 * cmd_len)
		close(fd[i++]);
	i = 0;
	while (i < cmd_len)
	{
		wait(NULL);
		i++;
	}
	free(fd);
}

int		error(char *path)
{
	DIR	*folder;
	int	fd;
	int	exit_code;

	fd = open(path, O_WRONLY);
	folder = opendir(path);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(path, 2);
	if (ft_strchr(path, '/') == NULL)
		ft_putendl_fd(": command not found", 2);
	else if (fd == -1 && folder == NULL)
		ft_putendl_fd(": No such file or directory", 2);
	else if (fd == -1 && folder != NULL)
		ft_putendl_fd(": is a directory", 2);
	else if (fd != -1 && folder == NULL)
		ft_putendl_fd(": Permission denied", 2);
	if (ft_strchr(path, '/') == NULL || (fd == -1 && folder == NULL))
		exit_code = 127;
	else
		exit_code = 126;
	if (folder)
		closedir(folder);
	safe_close(fd);
	return (exit_code);
}

void	exec_child(int cmd_len, int *fd, char ***cmd)
{
	int exit_code;
	int i;

	i = 0;
	while (i < 2 * cmd_len)
		close(fd[i++]);
	execvp((*cmd)[0], *cmd);
	exit_code = error((*cmd)[0]);
	exit(exit_code);
}

void	pipeline(char ***cmd, char ***raw_cmd)
{
	int		i;
	int		j;
	pid_t	pid;
	int		cmd_len;
	int		*fd;

	cmd_len = count(cmd);
	if (!(fd = malloc(sizeof(int) * 2 * cmd_len)))
		return (print_error(MALLOC_FAIL));
	i = 0;
	j = 0;
	while (i < cmd_len)
		pipe(fd + i++ * 2);
	while (*cmd != NULL)
	{
		pid = fork();
		if (pid == 0)
		{
			set_fd(cmd, raw_cmd, fd, j);
			exec_child(cmd_len, fd, cmd);
		}
		cmd++;
		j += 2;
	}
	wait_chiledren_and_free_fd(cmd_len, fd);
}
