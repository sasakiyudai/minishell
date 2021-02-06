#include "minishell.h"

void	bcopy(void *dest, void *src, int size)
{
	char	*s1;
	char	*s2;

	s1 = (char *)dest;
	s2 = (char *)src;
	while (size--)
		s1[size] = s2[size];
}

int		bcopy_int(void *dest, void *src, int size)
{
	bcopy(dest, src, size);
	return (0);
}

void	bzero(void *s, int n)
{
	char	*str;
	int		i;

	i = 0;
	str = (char *)s;
	while (i < n)
	{
		str[i] = 0;
		i++;
	}
}
