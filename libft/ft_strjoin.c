/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syudai <syudai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 12:51:40 by syudai            #+#    #+#             */
/*   Updated: 2020/11/03 13:25:34 by syudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	char	*p;

	p = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!p)
		return (NULL);
	i = 0;
	while (i < ft_strlen(s1))
	{
		p[i] = s1[i];
		i++;
	}
	i = 0;
	while (i <= ft_strlen(s2))
	{
		p[ft_strlen(s1) + i] = s2[i];
		i++;
	}
	return (p);
}
