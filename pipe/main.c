/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syudai <syudai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 17:48:31 by syudai            #+#    #+#             */
/*   Updated: 2021/01/29 15:00:42 by syudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
	t_arg_main arg_main;
	t_arg		arg;

	arg.name = "PATH";
	arg.data = read_all(0);
	arg.type = ARG_TYPE_STR;

	arg_main_ini(&arg_main);
	arg_add(&arg_main, &arg);
	
	char *ls[] = {"ls", ">", "hoge", NULL};
	char *ls1[] = {"ls", NULL};
	char *cat[] = {"cat", NULL};
	char *cat1[] = {"cat", NULL};

	char **raw_cmd[] = {ls, cat, NULL};
	char **cmd[] = {ls1, cat1, NULL};

	pipeline(cmd, raw_cmd, &arg_main);
	return (0);
}
