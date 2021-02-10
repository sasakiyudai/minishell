/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check_process.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 13:32:18 by marvin            #+#    #+#             */
/*   Updated: 2021/02/10 15:11:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		syntax_check_make_sedstr(char *cmd_raw, char **ret)
{
	char	bitflag_quote;
	int		i;
	int		flag2;

	*ret = (char *)malloc2(strlen(cmd_raw) + 1);
	bitflag_quote = 0;
	flag2 = 0;
	i = -1;
	while (*cmd_raw)
	{
		check_quote(*cmd_raw, &bitflag_quote);
		if ((!bitflag_quote && bitflag_quote < FLAG_ESCAPE) ||
			(!flag2 && flag2 < FLAG_ESCAPE))
			(*ret)[++i] = 'a';
		else
			(*ret)[++i] = *cmd_raw;
		cmd_raw++;
	}
	(*ret)[++i] = '\0';
	return (!!bitflag_quote);
}

int		syntax_check_process3(char *cmd, t_syntax_flag *syntax_flag)
{
	if (*cmd == '\n' || *cmd == '\0')
	{
		if (syntax_flag->pipe || syntax_flag->r_redirect ||
			syntax_flag->l_redirect)
			return (print_synerr(cmd));
	}
	else if (*cmd == ';')
	{
		if (syntax_flag->pipe || syntax_flag->r_redirect ||
			syntax_flag->l_redirect || syntax_flag->semi)
			return (print_synerr(cmd));
		syntax_flag->semi = 1;
	}
	else
	{
		syntax_flag->l_redirect = 0;
		syntax_flag->r_redirect = 0;
		syntax_flag->pipe = 0;
		syntax_flag->semi = 0;
	}
	return (0);
}

int		syntax_check_process2(char *cmd, t_syntax_flag *syntax_flag)
{
	if (*cmd == '>')
	{
		if (syntax_flag->r_redirect >= 2 || syntax_flag->l_redirect)
			return (print_synerr(cmd));
		(syntax_flag->r_redirect)++;
	}
	else if (*cmd == '<')
	{
		if (syntax_flag->r_redirect || syntax_flag->l_redirect)
			return (print_synerr(cmd));
		(syntax_flag->l_redirect)++;
	}
	else
	{
		return (syntax_check_process3(cmd, syntax_flag));
	}
	return (0);
}

int		syntax_check_process(char *cmd, t_syntax_flag *syntax_flag)
{
	if (*cmd == ' ')
	{
		if (syntax_flag->pipe)
			syntax_flag->pipe = 2;
		if (syntax_flag->r_redirect)
			syntax_flag->r_redirect = 2;
		if (syntax_flag->l_redirect)
			syntax_flag->l_redirect = 2;
	}
	else if (*cmd == '|')
	{
		if (syntax_flag->pipe >= 2 || syntax_flag->r_redirect ||
			syntax_flag->l_redirect)
			return (print_synerr(cmd));
		syntax_flag->pipe++;
	}
	else
		return (syntax_check_process2(cmd, syntax_flag));
	return (0);
}

int		syntax_check_main(char *cmd)
{
	t_syntax_flag	syntax_flag;

	ft_bzero(&syntax_flag, sizeof(t_syntax_flag));
	while (*cmd)
	{
		if (syntax_check_process(cmd, &syntax_flag))
			return (258);
		cmd++;
	}
	if (syntax_check_process(cmd, &syntax_flag))
		return (258);
	return (0);
}
