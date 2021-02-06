/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_strdup.c										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: syudai <syudai@student.42tokyo.jp>		 +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2020/11/03 11:21:14 by syudai			#+#	#+#			 */
/*   Updated: 2020/11/04 18:36:27 by syudai		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*ret;

	if (!s1)
		return (NULL);
	i = 0;
	while (s1[i])
		i++;
	if (!(ret = malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = 0;
	while (s1[i])
	{
		ret[i] = s1[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}
