/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syudai <syudai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 22:32:19 by syudai            #+#    #+#             */
/*   Updated: 2021/01/28 17:45:47 by syudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define MALLOC_FAIL 1
# include "libft.h"

void	print_error(int i);
void	set_right(char ***raw_cmd, int j, int *fd);
void	set_left(char ***raw_cmd, int j, int *fd);
int		count(char ***cmd);
void	pipeline(char ***cmd, char ***raw_cmd);
void	safe_close(int fd);

#endif