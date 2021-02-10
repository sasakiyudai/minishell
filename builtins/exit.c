/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syudai <syudai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 17:53:37 by syudai            #+#    #+#             */
/*   Updated: 2021/02/10 18:55:49 by rnitta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_isnum(char c, int i)
{
	if ('0' <= c && c <= '9')
		return (1);
	if (i == 0 && (c == '-' || c == '+'))
		return (1);
	return (0);
}

int		include_no_num(char *arg)
{
	int i;
	int over;

	i = 0;
	while (arg[i])
	{
		if (!ft_isnum(arg[i], i))
			return (1);
		i++;
	}
	if (i == 1 && (arg[0] == '-' || arg[0] == '+'))
		return (1);
	over = 0;
	if (ft_atoll(arg, &over) == -1 || ft_atoll(arg, &over) == 0)
		if (over == 1)
			return (1);
	return (0);
}

int		exit_errors(int option, char *args[])
{
	int ret;

	ft_putstr_fd("minishell: exit: ", 2);
	if (option == 0)
	{
		ret = 255;
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd("numeric argument required", 2);
	}
	else
	{
		ret = 1;
		ft_putendl_fd("too many arguments", 2);
	}
	return (ret);
}

int		ft_exit(char *args[])
{
	int		len;
	int		ret;
	t_arg	arg;

	arg_get(g_arg_main, &arg, "?");
	ret = ft_atoi(arg.data);
	arg_free(&arg);
	len = ft_len(args);
	write(2, "exit\n", 5);
	if (len == 1)
		;
	else if (include_no_num(args[1]))
		exit(exit_errors(0, args));
	else if (len >= 3)
		return (exit_errors(1, args));
	else
		ret = (unsigned char)ft_atoi(args[1]);
	exit(ret % 256);
}
