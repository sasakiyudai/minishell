/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 13:33:06 by marvin            #+#    #+#             */
/*   Updated: 2021/02/10 13:33:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	split_free_all(char **s)
{
	int	i;

	i = -1;
	while (s[++i])
		free(s[i]);
	free(s);
}

void	ft_strncpy(char *dest, char *src, size_t n)
{
	dest[n] = '\0';
	while (n--)
		dest[n] = src[n];
}

void	ft_bzero(void *s, size_t n)
{
	char	*str;
	size_t	i;

	i = 0;
	str = (char *)s;
	while (i < n)
	{
		str[i] = 0;
		i++;
	}
}

int		ft_strcpy_int(char *dest, char *src)
{
	int i;

	i = -1;
	if (!src)
		return (0);
	while (src[++i])
		dest[i] = src[i];
	dest[i] = '\0';
	return (i);
}

int		ft_itoa(long long int n, char *dest)
{
	int				len;
	int				ret;
	long long int	tmp;

	if (!n)
		dest[0] = '0';
	if (n < 0)
		dest[0] = '-';
	len = n < 0 ? 3 : 2;
	if (n < 0)
		n *= -1;
	tmp = n;
	while ((n /= 10))
		len++;
	dest[--len] = '\0';
	ret = len;
	while (tmp)
	{
		dest[--len] = '0' + tmp % 10;
		tmp /= 10;
	}
	return (ret);
}
