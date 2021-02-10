/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_c.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syudai <syudai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 18:22:40 by syudai            #+#    #+#             */
/*   Updated: 2021/02/06 18:28:55 by syudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_free(char *s1, char *s2)
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
	free(s1);
	free(s2);
	return (p);
}

char	*surround_minus_one(char *value)
{
	int		len;
	int		i;
	char	*ret;

	i = 0;
	len = ft_strlen(value);
	ret = malloc(sizeof(char) * (len + 2) + 1);
	ret[i++] = -1;
	while (i <= len)
	{
		ret[i] = value[i - 1];
		i++;
	}
	ret[i] = -1;
	ret[++i] = '\0';
	return (ret);
}

int		is_dollarble(char c)
{
	return (ft_isalnum(c) || c == '_' || c == '?');
}

char	fff(char flag)
{
	if (flag & FLAG_ESCAPE)
		return ('\\');
	if (flag == FLAG_SINGLE_QUOTE)
		return ('\'');
	if (flag == FLAG_DOUBLE_QUOTE)
		return ('\"');
	if (flag & FLAG_MINUS_ONE)
		return (-1);
	return (0);
}
