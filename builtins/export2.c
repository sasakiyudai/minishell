/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 13:31:11 by marvin            #+#    #+#             */
/*   Updated: 2021/02/10 21:08:21 by rnitta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_export(char *args[], t_arg_main *arg_main)
{
	char	**env;

	if (!args[1])
	{
		env = arg_list_get_quote(arg_main);
		print_with_declare(env);
		split_free_all(env);
		return (0);
	}
	return (export_argadd(args, arg_main));
}
