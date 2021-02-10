/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 13:30:10 by marvin            #+#    #+#             */
/*   Updated: 2021/02/10 15:11:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	arg_free(t_arg *arg)
{
	free(arg->name);
	free(arg->data);
	arg->name = NULL;
	arg->data = NULL;
}

int		arg_copy(t_arg *dest, t_arg *src)
{
	dest->name = ft_strdup(src->name);
	dest->data = ft_strdup(src->data);
	return (0);
}

int		arg_list_cnt(t_arg_list *arg_list)
{
	if (arg_list->next)
		return ((!!arg_list->arg.data) + arg_list_cnt(arg_list->next));
	return (!!arg_list->arg.data);
}

void	set_hatena(t_arg_main *arg_main, int i)
{
	int		j;
	int		len;
	t_arg	arg;

	j = i;
	len = 1 + (i < 0);
	i = i < 0 ? -i : i;
	while (i > 9 && len++)
		i /= 10;
	arg.name = "?";
	arg.data = malloc2(len + 1);
	ft_itoa(j, (arg.data));
	arg_add(arg_main, &arg);
	free(arg.data);
}

int		arg_charlen(t_arg *arg, int quote)
{
	long long int len;

	len = ft_strlen(arg->name) + 1;
	len += ft_strlen(arg->data);
	if (!arg->data)
	{
		if (quote)
			len--;
		else
			len += 2;
	}
	return (len);
}
