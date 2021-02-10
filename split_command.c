/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 15:54:27 by marvin            #+#    #+#             */
/*   Updated: 2021/02/10 15:54:29 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		cnt_splitnum_command(char *s, char c)
{
	int		ret;
	char	bitflag_quote;
	char	flag_sequencial;

	ret = 0;
	bitflag_quote = 0;
	flag_sequencial = 0;
	while (*s == c)
		s++;
	while (*s)
	{
		check_quote(*s, &bitflag_quote);
		if ((!bitflag_quote || *s != c) && !flag_sequencial)
		{
			ret++;
			flag_sequencial = 1;
		}
		else if (!bitflag_quote && *s == c)
			flag_sequencial = 0;
		s++;
	}
	return (ret);
}

void	split_make_str(char **s, t_split *split_arg, char **ret)
{
	ret[split_arg->cnt_splitnum] = ft_strndup(*s, split_arg->cnt_moji - 1);
	*s += split_arg->cnt_moji;
	split_arg->cnt_moji = 0;
	split_arg->flag_sequencial = 1;
}

int		split_command_ini(char **s, char c, t_split *split_arg, char ***ret)
{
	split_arg->cnt_splitnum = cnt_splitnum_command(*s, c) + 1;
	*ret = (char **)malloc2(sizeof(char *) * split_arg->cnt_splitnum);
	if (!*ret)
		return (-1);
	ft_bzero(split_arg, sizeof(t_split));
	split_arg->flag_sequencial = 1;
	while (**s == c)
		(*s)++;
	return (0);
}

void	split_command_last(char *s, t_split *split_arg, char ***ret)
{
	split_arg->cnt_moji++;
	if (!split_arg->flag_sequencial)
	{
		split_make_str(&s, split_arg, *ret);
		if (!(*ret)[split_arg->cnt_splitnum++])
		{
			split_command_free(*ret, split_arg->cnt_splitnum - 1);
			*ret = NULL;
		}
		else
			(*ret)[split_arg->cnt_splitnum] = NULL;
	}
	else
		(*ret)[split_arg->cnt_splitnum] = NULL;
}

char	**split_command(char *s, char c)
{
	t_split	split_arg;
	char	**ret;

	if (split_command_ini(&s, c, &split_arg, &ret))
		return (NULL);
	while (s[split_arg.cnt_moji])
	{
		check_quote(s[split_arg.cnt_moji], &split_arg.bitflag_quote);
		if (s[split_arg.cnt_moji++] != c)
			split_arg.flag_sequencial = 0;
		else if (!split_arg.bitflag_quote && !split_arg.flag_sequencial &&
			(split_arg.cnt_moji >= 2 && s[split_arg.cnt_moji - 2] != '\\'))
		{
			split_make_str(&s, &split_arg, ret);
			if (!ret[split_arg.cnt_splitnum++])
				return (split_command_free(ret, split_arg.cnt_splitnum - 1));
		}
		else if (!split_arg.bitflag_quote)
		{
			split_arg.cnt_moji = 0;
			s++;
		}
	}
	split_command_last(s, &split_arg, &ret);
	return (ret);
}
