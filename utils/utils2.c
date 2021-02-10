/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 13:33:04 by marvin            #+#    #+#             */
/*   Updated: 2021/02/10 15:46:40 by rnitta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*malloc2(size_t size)
{
	void	*p;

	if (!(p = malloc(size)))
		exit(3);
	return (p);
}

char	*ft_strndup(char *src, int n)
{
	char	*ret;

	if (!(ret = (char *)malloc2(n + 1)))
		return (NULL);
	ret[n] = '\0';
	while (n--)
		ret[n] = src[n];
	return (ret);
}

char	**split_command_free(char **ret, int cnt_splitnum)
{
	while (cnt_splitnum--)
		free(ret[cnt_splitnum]);
	free(ret);
	return (NULL);
}

int		ft_len(char *args[])
{
	int i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

void	sort(char *envp[])
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < ft_len(envp) - 1)
	{
		j = 1;
		while (j < ft_len(envp) - i)
		{
			if (ft_strcmp(envp[j], envp[j - 1]) < 0)
			{
				tmp = envp[j];
				envp[j] = envp[j - 1];
				envp[j - 1] = tmp;
			}
			j++;
		}
		i++;
	}
}
