/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syudai <syudai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 17:47:28 by syudai            #+#    #+#             */
/*   Updated: 2021/01/29 14:16:35 by syudai           ###   ########.fr       */
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

int		is_builtin(char *command)
{
	if (ft_strcmp(command, "echo") == 0)
		return (1);
	else if (ft_strcmp(command, "cd") == 0)
		return (2);
	else if (ft_strcmp(command, "pwd") == 0)
		return (3);
	else if (ft_strcmp(command, "export") == 0)
		return (4);
	else if (ft_strcmp(command, "unset") == 0)
		return (5);
	else if (ft_strcmp(command, "env") == 0)
		return (6);
	else if (ft_strcmp(command, "exit") == 0)
		return (7);
	return (0);
}

void	call_builtin(int tmp, char **str_b, t_arg_main *arg_main, char **envs)
{
	if (tmp == 1)
		ft_echo(str_b);
	else if (tmp == 2)
		ft_cd(str_b);
	else if (tmp == 3)
		ft_pwd();
	else if (tmp == 4)
		ft_export(str_b, envs, arg_main);
	else if (tmp == 5)
		ft_unset(str_b, arg_main);
	else if (tmp == 6)
		ft_env(envs);
	else if (tmp == 7)
		exit(0);
	exit(EXIT_SUCCESS);
}

void print_tab(char *env[])
{
	int i = 0;

	while (env[i])
		fprintf(stderr, "%s\n", env[i++]);
}

void	exec_child(int cmd_len, int *fd, char ***cmd, t_arg_main *arg_main)
{
	int		exit_code;
	int		i;
	int		tmp;
	char	*path;
	char	**envs;

	i = 0;
	if (!(envs = arg_list_get(arg_main)))
		exit(1);
	while (i < 2 * cmd_len)
		close(fd[i++]);

	if ((tmp = is_builtin((*cmd)[0])))
	{
		//printf("hello, builtin\n");
		//exit(0);
		call_builtin(tmp, *cmd, arg_main, envs);
	}
	else
	{
		if (0 == (tmp = get_path(arg_main, &path, (*cmd)[0])))
		{
			execve(path, *cmd, envs);
		}
		else if (tmp == -1)
			print_error(MALLOC_FAIL);
		exit_code = error((*cmd)[0]);
		exit(exit_code);
	}
}

void	pipeline(char ***cmd, char ***raw_cmd, t_arg_main *arg_main)
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
			exec_child(cmd_len, fd, cmd, arg_main);
		}
		cmd++;
		j += 2;
	}
	wait_chiledren_and_free_fd(cmd_len, fd);
}
