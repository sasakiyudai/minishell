/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syudai <syudai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 17:48:31 by syudai            #+#    #+#             */
/*   Updated: 2021/01/29 20:38:15 by syudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void one_command(char ***cmd, char ***raw_cmd, t_arg_main *arg_main)
{
	pid_t pid;
	int tmp;
	int semi[2];
	char **envs;
	char *path;

	if (!(envs = arg_list_get(arg_main)))
		exit(1); //　これでいいのか
	if ((tmp = is_builtin((*cmd)[0])))
	{
		set_right(raw_cmd, 0, semi, 0);
		set_left(raw_cmd, 0, semi, 0);
		call_builtin(tmp, *cmd, arg_main, envs);
		return ;
	}
	else if ((pid = fork()) == 0)
	{
		if (0 == (tmp = get_path(arg_main, &path, (*cmd)[0])))
		{
			set_right(raw_cmd, 0, semi, 0);
			set_left(raw_cmd, 0, semi, 0);
			execve(path, *cmd, envs);
		}
		else if (tmp == -1)
			print_error(MALLOC_FAIL);
		exit(error((*cmd)[0]));
	}
	wait(NULL);
}

int main(void)
{
	t_arg_main arg_main;
	t_arg		arg;

	arg.name = "PATH";
	arg.data = "/bin";
	arg.type = ARG_TYPE_STR;

	arg_main_ini(&arg_main);
	arg_add(&arg_main, &arg);
	
	char *ls[] = {"ls", ">", "hoge", NULL};
	char *ls1[] = {"ls", NULL};
	//char *cat[] = {"cat", NULL};
	//char *cat1[] = {"cat", NULL};

	char **raw_cmd[] = {ls, NULL};
	char **cmd[] = {ls1, NULL};

	
	if (count(cmd) == 1)
		one_command(cmd, raw_cmd, &arg_main);
	else if (count(cmd) >= 1)
		pipeline(cmd, raw_cmd, &arg_main);
	return (0);
}
