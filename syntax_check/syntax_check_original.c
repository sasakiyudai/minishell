/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 13:32:20 by marvin            #+#    #+#             */
/*   Updated: 2021/02/10 14:56:32 by rnitta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int		myprint_error(int i)
{
	if (i == SYNTAX_ERROR_QUOTE)
		printf("bash: bad quote\n");
	return (258);
}

int		syntax_check(char *cmd_raw)
{
	char	*cmd;
	int		tmp;

	if (syntax_check_make_sedstr(cmd_raw, &cmd) == 1)
	{
		free(cmd);
		return (myprint_error(SYNTAX_ERROR_QUOTE));
	}
	if (!cmd)
		return (-1);
	tmp = syntax_check_main(cmd);
	free(cmd);
	return (tmp);
}
