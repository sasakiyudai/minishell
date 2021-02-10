/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 13:31:53 by marvin            #+#    #+#             */
/*   Updated: 2021/02/10 13:43:36 by rnitta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*g_signal;
t_arg_main	*g_arg_main;

void	command_main_free(char ***cmd_split, char ***tmp_cmd_split)
{
	int i;

	i = -1;
	while (cmd_split[++i])
		split_free_all(cmd_split[i]);
	free(cmd_split);
	i = -1;
	while (tmp_cmd_split[++i])
		free(tmp_cmd_split[i]);
	free(tmp_cmd_split);
}
