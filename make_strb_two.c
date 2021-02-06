/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_strb_two.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syudai <syudai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 01:33:55 by syudai            #+#    #+#             */
/*   Updated: 2021/02/07 01:40:51 by syudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_tablen(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int		num_of_redirect(char **tab)
{
	int i;
	int res;

	i = 0;
	res = 0;
	while (tab[i])
	{
		if (ft_strcmp(tab[i], ">") == 0 || ft_strcmp(tab[i], ">>") == 0
		|| ft_strcmp(tab[i], "<") == 0)
			res++;
		i++;
	}
	return (res);
}

int		is_space(char c)
{
	if (c == ' ' || c == '\f' || c == '\n' || c == '\r'
	|| c == '\t' || c == '\v')
		return (1);
	return (0);
}

int		is_redirect(char c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}
