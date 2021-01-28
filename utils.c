#include <stdio.h>

void     _bcopy(void *dest, void *src, int size)
{
    char    *s1;
    char    *s2;

    s1 = (char *)dest;
    s2 = (char *)src;
    while (size--)
        s1[size] = s2[size];
}

int     _bcopy_int(void *dest, void *src, int size)
{
    _bcopy(dest, src, size);
    return (0);
}

void	_bzero(void	 *s, int n)
{
	char *str = (char *)s;
	size_t i = 0;
	while (i < n)
	{
		str[i] = 0;
		i++;
	}
}