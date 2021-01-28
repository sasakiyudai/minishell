/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syudai <syudai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 17:48:31 by syudai            #+#    #+#             */
/*   Updated: 2021/01/28 17:48:32 by syudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
	char *ls[] = {"ls", ">", "hoge", NULL};
	char *ls1[] = {"ls", NULL};
	char *cat[] = {"cat", NULL};
	char *cat1[] = {"cat", NULL};

	char **raw_cmd[] = {ls, cat, NULL};
	char **cmd[] = {ls1, cat1, NULL};

	pipeline(cmd, raw_cmd);
	return (0);
}
