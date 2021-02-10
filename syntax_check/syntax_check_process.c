/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check_process.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 18:14:10 by marvin            #+#    #+#             */
/*   Updated: 2021/02/10 19:53:58 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		syntax_check_main(char *cmd)
{
	t_syntax_flag	syntax_flag;

	ft_bzero(&syntax_flag, sizeof(t_syntax_flag));
	syntax_flag.pipe = 2;
	syntax_flag.semi = 1;
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

int		myprint_error(int i)
{
	i++;
	if (SYNTAX_ERROR_QUOTE)
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