/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_strmapi.c									   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: syudai <syudai@student.42tokyo.jp>		 +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2020/11/03 18:05:57 by syudai			#+#	#+#			 */
/*   Updated: 2020/11/03 18:11:25 by syudai		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*p;

	if (!(p = malloc(sizeof(char) * (ft_strlen(s) + 1))))
		return (NULL);
	i = 0;
	while (s[i])
	{
		p[i] = f(i, s[i]);
		i++;
	}
	p[i] = '\0';
	return (p);
}
