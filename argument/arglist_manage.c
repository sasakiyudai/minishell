/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arglist_manage.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 13:29:58 by marvin            #+#    #+#             */
/*   Updated: 2021/02/10 15:11:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		arg_new(t_arg_main *arg_main, t_arg *src)
{
	t_arg_list *tmp_arg_list;

	if (arg_main->arg_num == INT_MAX)
		return (-10);
	tmp_arg_list = arg_main->head.next;
	arg_main->head.next = (t_arg_list *)malloc2(sizeof(t_arg_list));
	arg_copy(&(arg_main->head.next->arg), src);
	arg_main->arg_num++;
	arg_main->head.next->next = tmp_arg_list;
	return (0);
}

int		arg_add(t_arg_main *arg_main, t_arg *arg)
{
	t_arg_list	*tmp_arg_list;

	if ((tmp_arg_list = arg_isexist(arg_main, arg->name)))
	{
		if (!arg->data)
			return (0);
		arg_free(&(tmp_arg_list->arg));
		return (arg_copy(&(tmp_arg_list->arg), arg));
	}
	return (arg_new(arg_main, arg));
}

int		arg_delete_process(t_arg_main *arg_main, t_arg_list
	*arg_list, char *name, t_arg_list **ret)
{
	t_arg_list *ret_arg_list;

	if (!ft_strcmp(arg_list->arg.name, name))
	{
		*ret = arg_list->next;
		arg_free(&(arg_list->arg));
		free(arg_list);
		arg_main->arg_num--;
		return (1);
	}
	else if (arg_list->next)
		if (arg_delete_process(arg_main, arg_list->next, name, &ret_arg_list))
			arg_list->next = ret_arg_list;
	return (0);
}

void	arg_delete(t_arg_main *arg_main, char *name)
{
	t_arg_list	*tmp;

	if (arg_main->head.next)
		if (arg_delete_process(arg_main, arg_main->head.next, name, &tmp))
			arg_main->head.next = tmp;
}
