/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syudai <syudai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 21:13:50 by syudai            #+#    #+#             */
/*   Updated: 2021/02/10 11:18:32 by syudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		which_quote(char c, int flag)
{
	if (c == '\'')
		return (1);
	else if (c == '\"')
		return (2);
	else if (c == -1)
		return (flag == 3 ? 0 : 3);
	return (flag);
}

void	check_quote(char c, char *bitflag_quote)
{
	if (c == '\\' && (*bitflag_quote < 4 || *bitflag_quote >= FLAG_ESCAPE)
	&& !(*bitflag_quote & FLAG_SINGLE_QUOTE))
		*bitflag_quote ^= FLAG_ESCAPE;
	else if (*bitflag_quote & FLAG_ESCAPE)
	{
		*bitflag_quote &= ~FLAG_ESCAPE;
		return ;
	}
	if (c == '\'' && *bitflag_quote < 4 && !(*bitflag_quote
	& FLAG_DOUBLE_QUOTE))
		*bitflag_quote ^= FLAG_SINGLE_QUOTE;
	if (c == '\"' && *bitflag_quote < 4 && !(*bitflag_quote
	& FLAG_SINGLE_QUOTE))
		*bitflag_quote ^= FLAG_DOUBLE_QUOTE;
	if (c == -1)
		*bitflag_quote ^= FLAG_MINUS_ONE;
}

void	remove_quotes(char *cmd)
{
	char	flag;
	int		i;
	int		j;
	char	flag2;

	i = 0;
	j = -1;
	flag = 0;
	flag2 = 0;
	while (cmd[++j])
	{
		check_quote(cmd[j], &flag);
		if (flag < flag2)
		{
			if (flag2 >= FLAG_ESCAPE)
				cmd[i++] = cmd[j];
		}
		else if (cmd[j] != fff(flag) || (flag & FLAG_DOUBLE_QUOTE
		&& '\\' == fff(flag) && cmd[j + 1] != '\"'
		&& cmd[j + 1] != '\\' && cmd[j + 1] != '$'))
			cmd[i++] = cmd[j];
		flag2 = flag;
	}
	cmd[i] = '\0';
}

int		single_quote(char now, int flag)
{
	flag = 0;
	if (now == '\'')
		return (1);
	else
		return (flag);
}
