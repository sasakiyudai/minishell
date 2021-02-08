/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syudai <syudai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 17:52:06 by syudai            #+#    #+#             */
/*   Updated: 2021/02/08 15:49:33 by rnitta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define MAX_FILENAME 1024

int		ft_pwd(void)
{
	char s[MAX_FILENAME];

	write(1, "/", !!g_arg_main->pwd_slash);
	if (!getcwd(s, MAX_FILENAME))
		return (1);
	else
		ft_putendl_fd(s, 1);
	return (0);
}
