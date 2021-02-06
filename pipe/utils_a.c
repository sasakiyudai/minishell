/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   utils_a.c										  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: syudai <syudai@student.42tokyo.jp>		 +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2021/01/28 17:48:51 by syudai			#+#	#+#			 */
/*   Updated: 2021/01/28 17:49:25 by syudai		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "minishell.h"

int		count(char ***cmd)
{
	int i;

	i = 0;
	while (cmd[i])
		i++;
	return (i);
}

void	safe_close(int fd)
{
	if (fd > 0)
		close(fd);
}
