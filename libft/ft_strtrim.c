/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 13:26:06 by syudai            #+#    #+#             */
/*   Updated: 2021/02/10 15:11:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		len;
	int		i;

	if (!s1 && !set)
		return (NULL);
	len = ft_strlen(s1) - 1;
	i = 0;
	while (s1[i])
	{
		if (ft_strchr(set, s1[i]))
			i++;
		else
			break ;
	}
	while (len > i)
	{
		if (!ft_strchr(set, s1[len]))
			break ;
		len--;
	}
	if (!(str = (char *)malloc2(sizeof(char) * ((len - i + 1) + 1))))
		return (NULL);
	ft_strlcpy(str, (char *)(s1 + i), len - i + 2);
	return (str);
}
