/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_b.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syudai <syudai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 17:41:50 by syudai            #+#    #+#             */
/*   Updated: 2021/02/10 20:16:07 by rnitta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tab(char *env[])
{
	int i;

	i = 0;
	while (env[i])
		fprintf(stdout, "%s\n", env[i++]);
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
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errno), 2);
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

int		call_builtin(int tmp, char **str_b, t_arg_main *arg_main)
{
	int result;

	result = 0;
	if (tmp == 1)
		ft_echo(str_b);
	else if (tmp == 2)
		result = ft_cd(str_b, arg_main);
	else if (tmp == 3)
		result = ft_pwd();
	else if (tmp == 4)
		result = ft_export(str_b, arg_main);
	else if (tmp == 5)
		ft_unset(str_b, arg_main);
	else if (tmp == 6)
		ft_env(arg_main);
	else if (tmp == 7)
		result = ft_exit(str_b);
	return (result);
}
