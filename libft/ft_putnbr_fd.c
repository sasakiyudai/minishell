/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syudai <syudai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 18:21:24 by syudai            #+#    #+#             */
/*   Updated: 2020/11/03 23:39:02 by syudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		write_digit(int n, int fd)
{
	char c;

	c = n + '0';
	write(fd, &c, 1);
}

void			ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
	{
		if (n == -2147483648)
			write(fd, "-2147483648", 11);
		else
		{
			write(fd, "-", 1);
			ft_putnbr_fd(-n, fd);
		}
	}
	else if (n < 10)
	{
		write_digit(n, fd);
	}
	else
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
}
