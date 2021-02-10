/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ini.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 13:31:57 by marvin            #+#    #+#             */
/*   Updated: 2021/02/10 15:11:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*g_signal;
t_arg_main	*g_arg_main;

void	ini3(t_arg_main *arg_main, char *env)
{
	t_arg	arg;

	arg.name = ft_strdup(env);
	arg.data = NULL;
	arg_add(arg_main, &arg);
	arg_free(&arg);
}

void	ini2(t_arg_main *arg_main, char *env)
{
	size_t	tmp;
	t_arg	arg;

	tmp = (size_t)(ft_strchr(env, '=') - env);
	arg.name = malloc2(tmp + 1);
	ft_strncpy(arg.name, env, tmp);
	if (ft_strcmp(arg.name, "OLDPWD"))
	{
		arg.data = malloc2(ft_strlen(env) - tmp);
		ft_strcpy((char *)(arg.data), env + tmp + 1);
	}
	else
		arg.data = NULL;
	arg_add(arg_main, &arg);
	arg_free(&arg);
}

void	ini(t_arg_main *arg_main, char *env[])
{
	t_arg	arg;
	int		i;

	i = -1;
	arg_main_ini(arg_main);
	g_arg_main = arg_main;
	arg_main->pwd_slash = 0;
	arg.type = ARG_TYPE_STR;
	while (env[++i])
		if (ft_strchr(env[i], '='))
			ini2(arg_main, env[i]);
		else
			ini3(arg_main, env[i]);
	arg.data = NULL;
	arg.name = "OLDPWD";
	arg_add(arg_main, &arg);
}
