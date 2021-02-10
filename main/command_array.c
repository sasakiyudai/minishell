/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 13:31:59 by marvin            #+#    #+#             */
/*   Updated: 2021/02/10 15:11:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**make_command_array_splitpipe(char *cmd)
{
	char **cmd_split;

	if (!(cmd = separate_redirect(cmd)))
		return (NULL);
	if (!(cmd_split = split_command(cmd, '|')))
	{
		free(cmd);
		return (NULL);
	}
	free(cmd);
	return (cmd_split);
}

char	***make_command_array_malloc2(char **tmp)
{
	int		cnt;
	char	***ret;

	cnt = 0;
	while (tmp[cnt])
		cnt++;
	ret = (char ***)malloc2(sizeof(char **) * (cnt + 1));
	return (ret);
}

void	command_array_free(char ***cmd)
{
	int	i;

	i = -1;
	while (cmd[++i])
		split_free_all(cmd[i]);
	free(cmd);
}

char	***make_command_array(char *cmd)
{
	char	**tmp;
	char	***ret;
	int		i;

	tmp = make_command_array_splitpipe(cmd);
	ret = make_command_array_malloc2(tmp);
	i = -1;
	while (tmp[++i])
		ret[i] = split_command(tmp[i], ' ');
	split_free_all(tmp);
	ret[i] = NULL;
	return (ret);
}
