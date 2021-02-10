/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 18:14:43 by marvin            #+#    #+#             */
/*   Updated: 2021/02/10 18:30:34 by rnitta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		syntax_check_make_sedstr(char *cmd_raw, char **ret)
{
	char	bitflag_quote;
	int		i;

	*ret = (char *)malloc(strlen(cmd_raw) + 1);
	bitflag_quote = 0;
	i = -1;
	while (*cmd_raw)
	{
		check_quote(*cmd_raw, &bitflag_quote);
		if (bitflag_quote <= FLAG_DOUBLE_QUOTE)
		{
			(*ret)[++i] = *cmd_raw;
			if (*cmd_raw == '\'' || *cmd_raw == '\"')
				(*ret)[i] = 'a';
		}
		cmd_raw++;
	}
	(*ret)[++i] = '\0';
	return (!!bitflag_quote);
}

int		print_synerr(char *cmd)
{
	char s[8];

	s[0] = cmd[0];
	s[2] = '\0';
	if (cmd[0] == '\n' || cmd[0] == '\0')
		strcpy(s, "newline");
	else if (cmd[0] == '>')
		s[1] = cmd[1] * (cmd[1] == cmd[0]);
	else if (cmd[0] == '<')
		s[1] = '\0';
	else if (cmd[0] == '|')
		s[1] = cmd[1] * (cmd[1] == cmd[0]);
	else if (cmd[0] == ';')
		s[1] = cmd[1] * (cmd[1] == cmd[0]);
	ft_putstr_fd("bash: syntax error near unexpected token `", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd("'\n", 2);
	set_hatena(g_arg_main, 258);
	return (258);
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
