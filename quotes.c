/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 18:24:26 by syudai            #+#    #+#             */
/*   Updated: 2021/02/10 15:11:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*deploy_one(char *flag, int *i, char *input)
{
	char	*ret;
	int		len;

	len = 0;
	(*i)++;
	while (input[(*i)] != '\'')
	{
		len++;
		(*i)++;
	}
	ret = ft_strndup(input + ((*i) - (len + 1)), (len + 1) + 1);
	(*i)++;
	*flag = 0;
	return (ret);
}

char	*deploy_two(int *i, char *input)
{
	char	*ret;
	int		len;

	(*i)++;
	len = 0;
	if (input[*i] == '?')
	{
		len = 1;
		(*i)++;
	}
	else
		while (ft_isalnum(input[*i]) || input[*i] == '_')
		{
			len++;
			(*i)++;
		}
	ret = ft_strndup(input + *i - len, len);
	return (ret);
}

void	joke_tmp(char **tmp, int *i, char *input)
{
	*tmp = malloc2(sizeof(char) * 1 + 1);
	(*tmp)[0] = input[*i];
	(*tmp)[1] = '\0';
	(*i)++;
}

char	*deploy_three(char *input, char *flag, int *i, t_arg_main *arg_main)
{
	t_arg	arg;
	char	*tmp;

	if (*flag == FLAG_SINGLE_QUOTE)
		tmp = deploy_one(flag, i, input);
	else if (input[*i] == '$' && (!*i || input[*i - 1] != '\\')
	&& is_dollarble(input[*i + 1]))
	{
		tmp = deploy_two(i, input);
		if (0 == arg_get(arg_main, &arg, tmp))
		{
			free(tmp);
			tmp = surround_minus_one((char *)arg.data);
			arg_free(&arg);
		}
		else
		{
			free(tmp);
			tmp = ft_strdup("");
		}
	}
	else
		joke_tmp(&tmp, i, input);
	return (tmp);
}

char	*deploy(char *input, t_arg_main *arg_main)
{
	int		i;
	char	flag;
	char	*tmp;
	char	*ret;

	i = 0;
	flag = 0;
	ret = malloc2(1);
	ret[0] = '\0';
	while (input[i])
	{
		check_quote(input[i], &flag);
		tmp = deploy_three(input, &flag, &i, arg_main);
		ret = ft_strjoin_free(ret, tmp);
	}
	return (ret);
}
