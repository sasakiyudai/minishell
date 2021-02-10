/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syudai <syudai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 18:10:15 by syudai            #+#    #+#             */
/*   Updated: 2021/02/10 21:25:07 by rnitta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_check(int sign, long rev, int i, const char *str)
{
	if (rev > 922337203685477580)
		return (0);
	if (rev == 922337203685477580)
	{
		if (sign == 1)
		{
			if (str[i] > '7')
				return (0);
		}
		else
		{
			if (str[i] > '8')
				return (0);
		}
	}
	return (1);
}

long long	ft_atoll(const char *str, int *over)
{
	int			i;
	int			sign;
	long long	rev;

	i = 0;
	sign = 1;
	while ((rev = 0) || str[i] == ' ' || str[i] == '\f' || str[i] == '\n'
			|| str[i] == '\r' || str[i] == '\t' || str[i] == '\v')
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while ('0' <= str[i] && str[i] <= '9')
	{
		if (ft_check(sign, rev, i, str))
			rev = rev * 10 + (str[i] - '0');
		else
		{
			*over = 1;
			return (sign == 1 ? -1 : 0);
		}
		i++;
	}
	return (sign * rev);
}
