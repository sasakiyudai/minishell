/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_calloc.c										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: syudai <syudai@student.42tokyo.jp>		 +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2020/11/03 10:49:58 by syudai			#+#	#+#			 */
/*   Updated: 2020/11/07 12:00:18 by syudai		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (!(ptr = (void*)malloc(count * size)))
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
}
