/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 13:29:12 by marvin            #+#    #+#             */
/*   Updated: 2021/02/10 16:12:40 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*g_signal;
t_arg_main	*g_arg_main;

void	command_main(char *cmd_raw, t_arg_main *arg_main)
{
	char	***cmd_split;
	char	***tmp_cmd_split;
	int		i;
	int		j;
	char	*tmp;

	cmd_split = make_command_array(cmd_raw);
	tmp_cmd_split = cmd_split;
	while (*tmp_cmd_split)
	{
		j = -1;
		i = 0;
		while (tmp_cmd_split[0][++j])
		{
			tmp = tmp_cmd_split[0][j];
			tmp_cmd_split[0][i] = deploy(tmp, arg_main);
			free(tmp);
			remove_empty_strb(tmp_cmd_split[0], &i);
		}
		tmp_cmd_split[0][i] = NULL;
		tmp_cmd_split++;
	}
	pipeline((tmp_cmd_split = make_strb_array(cmd_split)), cmd_split, arg_main);
	command_main_free(cmd_split, tmp_cmd_split);
}

void	sig_handler(int sig)
{
	t_arg	arg;

	arg.name = "?";
	arg.type = ARG_TYPE_STR;
	if (sig == SIGINT)
	{
		arg.data = ft_strdup(g_signal);
		arg_add(g_arg_main, &arg);
		free((char *)(arg.data));
		if (!ft_strcmp(g_signal, "1"))
			write(1, "\b\b  \n$ ", 7);
		g_arg_main->flag_sig = 1;
	}
	else if (sig == SIGQUIT && ft_strcmp(g_signal, "1"))
	{
		arg.data = "131";
		arg_add(g_arg_main, &arg);
		write(2, "Quit: 3", 7);
	}
	else if (sig == SIGQUIT)
		write(2, "\b\b  \b\b\n$ ", 6);
}

char	*main_process_ini(void)
{
	char	*cmd_all;

	write(2, "$ ", 2);
	g_signal = "1";
	g_arg_main->flag_sig = 0;
	cmd_all = read_all(0);
	g_signal = "130";
	if (syntax_check(cmd_all))
	{
		free(cmd_all);
		return (NULL);
	}
	return (cmd_all);
}

void	main_process(t_arg_main *arg_main)
{
	char		*cmd_all;
	char		**cmd_split;
	char		**tmp_cmd_split;

	while (1)
	{
		if (!(cmd_all = main_process_ini()))
			continue;
		cmd_split = split_command(cmd_all, ';');
		tmp_cmd_split = cmd_split;
		while (*cmd_split)
		{
			command_main(*cmd_split, arg_main);
			dup2(arg_main->std_in, 0);
			dup2(arg_main->std_out, 1);
			cmd_split++;
		}
		split_free_all(tmp_cmd_split);
		free(cmd_all);
	}
}

int		main(int argc, char *argv[], char *env[])
{
	t_arg_main	arg_main;

	(void)argc;
	(void)argv;
	ini(&arg_main, env);
	arg_main.std_in = dup(0);
	arg_main.std_out = dup(1);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	main_process(&arg_main);
	arg_list_ini(&arg_main);
	arg_free(&arg_main.head.arg);
	return (0);
}
