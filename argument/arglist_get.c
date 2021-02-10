/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arglist_get.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 13:30:05 by marvin            #+#    #+#             */
/*   Updated: 2021/02/10 15:11:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*arg_to_str_quotes(t_arg *arg)
{
	char	*ret;
	int		i;

	if (!arg)
		return (NULL);
	ret = (char *)malloc2(arg_charlen(arg, 1) + 3);
	i = ft_strcpy_int(ret, arg->name);
	if (arg->data)
	{
		i += ft_strcpy_int(ret + i, "=\"");
		i += ft_strcpy_int(ret + i, arg->data);
		i += ft_strcpy_int(ret + i, "\"");
	}
	return (ret);
}

char	*arg_to_str(t_arg *arg)
{
	char	*ret;
	int		i;

	if (!arg)
		return (NULL);
	ret = (char *)malloc2(arg_charlen(arg, 0) + 1);
	i = ft_strcpy_int(ret, arg->name);
	i += ft_strcpy_int(ret + i, "=");
	if (arg->data)
		i += ft_strcpy_int(ret + i, arg->data);
	else
	{
		ret[i] = -1;
		ret[i + 1] = '\0';
	}
	return (ret);
}

char	**arg_list_get_quote(t_arg_main *arg_main)
{
	char		**ret;
	t_arg_list	*current;
	int			i;
	int			arg_num;

	arg_num = arg_main->arg_num - 1;
	ret = (char **)malloc2(sizeof(char *) * (arg_num + 1));
	current = arg_main->head.next;
	i = -1;
	while (++i < arg_num)
	{
		ret[i] = arg_to_str_quotes(&(current->arg));
		current = current->next;
	}
	ret[i] = NULL;
	return (ret);
}

char	**arg_list_get(t_arg_main *arg_main)
{
	char		**ret;
	t_arg_list	*current;
	int			i;
	int			arg_num;

	arg_num = arg_list_cnt(&(arg_main->head)) - 1;
	ret = (char **)malloc2(sizeof(char *) * (arg_num + 1));
	current = arg_main->head.next;
	i = 0;
	while (i < arg_num)
	{
		if (current->arg.data)
			ret[i++] = arg_to_str(&(current->arg));
		current = current->next;
	}
	ret[i] = NULL;
	return (ret);
}
