/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syudai <syudai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 17:55:23 by syudai            #+#    #+#             */
/*   Updated: 2021/02/09 17:35:51 by rnitta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_env(t_arg_main *arg_main)
{
	int		i;
	int		j;
	char	**env;

	i = 0;
	env = arg_list_get(arg_main);
	while (env[i])
	{
		j = 0;
		while (env[i][j])
			if (env[i][j++] == -1)
				break ;
		printf("%s\n", env[i++]);
	}
	split_free_all(env);
	return (0);
}
