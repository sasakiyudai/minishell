/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 13:31:11 by marvin            #+#    #+#             */
/*   Updated: 2021/02/10 21:07:48 by rnitta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_with_declare(char *envp[])
{
	int	i;

	sort(envp);
	i = 0;
	while (envp[i])
		printf("declare -x %s\n", envp[i++]);
}

void	export_err(int err, char *cmd)
{
	if (err == BAD_ARGNAME)
	{
		ft_putstr_fd("bash: export: `", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd("\': not a valid identifier\n", 2);
	}
}

int		export_name_check(char *cmd)
{
	if (!ft_isalpha(*cmd) && *cmd != '_')
		return (1);
	if (*cmd == '=' || *cmd == '\0')
		return (1);
	while (*cmd)
	{
		if (*cmd == '=')
			return (0);
		if (!ft_isalnum(*cmd) && *cmd != '_')
			return (1);
		cmd++;
	}
	return (0);
}

void	set_arg(t_arg *arg, char *args[], t_arg_main *arg_main)
{
	char	*tmp;

	if ((tmp = ft_strchr(*args, '=')))
	{
		arg->name = ft_strndup(*args, (int)(tmp - *args));
		arg->data = ft_strdup(tmp + 1);
	}
	else
	{
		arg->name = ft_strdup(*args);
		arg->data = NULL;
	}
	arg_add(arg_main, arg);
	arg_free(arg);
}

int		export_argadd(char *args[], t_arg_main *arg_main)
{
	t_arg	arg;
	int		ret;

	ret = 0;
	arg.type = ARG_TYPE_STR;
	while (*(++args))
	{
		if (export_name_check(*args))
		{
			export_err(BAD_ARGNAME, *args);
			ret = 1;
		}
		else
			set_arg(&arg, args, arg_main);
	}
	return (ret);
}
