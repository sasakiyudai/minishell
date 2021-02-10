/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arglist_initialize.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 13:30:03 by marvin            #+#    #+#             */
/*   Updated: 2021/02/10 13:30:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	arg_list_ini_process(t_arg_list *arg_list)
{
	if (arg_list->next)
		arg_list_ini_process(arg_list->next);
	arg_free(&(arg_list->arg));
	free(arg_list);
}

int		arg_list_ini(t_arg_main *arg_main)
{
	if (arg_main->head.next)
		arg_list_ini_process(arg_main->head.next);
	arg_free(&(arg_main->head.arg));
	return (arg_main_ini(arg_main));
}

int		arg_main_ini(t_arg_main *arg_main)
{
	arg_main->arg_num = 1;
	arg_main->head.arg.name = ft_strdup("?");
	arg_main->head.arg.data = ft_strdup("0");
	arg_main->head.next = NULL;
	return (0);
}
