#include "minishell.h"

char	*ft_newstr_ncat(char *src1, char *src2, int n)
{
	char	*ret;
	int	 i;
	int	 j;

	if (!(ret = (char *)malloc(n)))
		return (NULL);
	i = -1;
	while (src1[++i])
		ret[i] = src1[i];
	j = 0;
	while (i < n - 1)
		ret[i++] = src2[j++];
	ret[i] = '\0';
	return (ret);
}

char	*ft_newstr_ncatfree(char *src1, char *src2, int n, int bitflag)
{
	char	*ret;
	ret = ft_newstr_ncat(src1, src2, n);
	if (bitflag & 1)
		free(src1);
	if (bitflag & 2)
		free(src2);
	return (ret);
}

char	*read_all(int fd)
{
	char	*ret;
	char	buf[1000];
	int		cnt_read;
	int		ret_read;

	cnt_read = 0;
	ret = (char *)malloc(1);
	ret[0] = '\0';
	while ((ret_read = read(fd, buf, 1000)) > 0 && buf[ret_read - 1] != '\n')
		if (!(ret = ft_newstr_ncatfree(ret, buf, (cnt_read += ret_read), 1)))
			return (NULL);
	if (!(ret = ft_newstr_ncatfree(ret, buf, (cnt_read += ret_read), 1)))
		return (NULL);
	if (ret_read >= 0)
		return (ret);
	free(ret);
	return (NULL);
}

char	*ft_strndup(char *src, int n)
{
	char *ret;

	if (!(ret = (char *)malloc(n + 1)))
		return (NULL);
	ret[n] = '\0';
	while (n--)
		ret[n] = src[n];
	return (ret);
}

int		cnt_splitnum_command(char *s, char c)
{
	int		ret;
	char	bitflag_quote;
	char	flag_sequencial;

	ret = 1;
	bitflag_quote = 0;
	flag_sequencial = 1;
	while (*s)
	{
		if (*s == '\'' && (!bitflag_quote) & FLAG_DOUBLE_QUOTE)
			bitflag_quote ^= FLAG_SINGLE_QUOTE;
		if (*s == '\"' && (!bitflag_quote) & FLAG_SINGLE_QUOTE)
			bitflag_quote ^= FLAG_DOUBLE_QUOTE;
		if (*s != c)
			flag_sequencial = 0;
		else if (!bitflag_quote && !flag_sequencial)
		{
			ret++;
			flag_sequencial = 1;
		}
		s++;
	}
	return (ret);
}

void	set_zero(int *a, int *b, int *c, int *d)
{
	*a = 0;
	*b = 0;
	*c = 0;
	*d = 0;
}

char	**split_command_free(char **ret, int cnt_splitnum)
{
	while (cnt_splitnum--)
		free(ret[cnt_splitnum]);
	free(ret);
	return (NULL);
}
/*
void	split_free_all(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		free(s[i++]);
	free(s);
}
*/
void	check_quote(char c, char *bitflag_quote)
{
	if (c == '\'' && !(*bitflag_quote & FLAG_DOUBLE_QUOTE))
		*bitflag_quote ^= FLAG_SINGLE_QUOTE;
	if (c == '\"' && !(*bitflag_quote & FLAG_SINGLE_QUOTE))
		*bitflag_quote ^= FLAG_DOUBLE_QUOTE;
}


void	split_make_str(char **s, t_split *split_arg, char **ret)
{
	ret[split_arg->cnt_splitnum] = ft_strndup(*s, split_arg->cnt_moji - 1);
	*s += split_arg->cnt_moji;
	split_arg->cnt_moji = 0;
	split_arg->flag_sequencial = 1;
}


int		split_command_ini(char *s, char c, t_split *split_arg, char ***ret)
{
	split_arg->cnt_splitnum = cnt_splitnum_command(s, c) + 1;
	*ret = (char **)malloc(sizeof(char *) * split_arg->cnt_splitnum);
	if (!*ret)
		return (-1);
	_bzero(split_arg, sizeof(t_split));
	split_arg->flag_sequencial = 1;
	return (0);
}

void	split_command_last(char *s, t_split *split_arg, char ***ret)
{
	split_arg->cnt_moji++;
	if (!split_arg->flag_sequencial)
	{
		split_make_str(&s, split_arg, *ret);
		if (!(*ret)[split_arg->cnt_splitnum++])
		{
			split_command_free(*ret, split_arg->cnt_splitnum - 1);
			*ret = NULL;
		}
		else
			(*ret)[split_arg->cnt_splitnum] = NULL;
	}
	else
		(*ret)[split_arg->cnt_splitnum] = NULL;
}

char	**split_command(char *s, char c)
{
	t_split	split_arg;
	char **ret;

	if (split_command_ini(s, c, &split_arg, &ret))
		return (NULL);
	while (s[split_arg.cnt_moji])
	{
		check_quote(s[split_arg.cnt_moji], &split_arg.bitflag_quote);
		if (s[split_arg.cnt_moji++] != c)
			split_arg.flag_sequencial = 0;
		else if (!split_arg.bitflag_quote && !split_arg.flag_sequencial)
		{
			split_make_str(&s, &split_arg, ret);
			if (!ret[split_arg.cnt_splitnum++])
				return (split_command_free(ret, split_arg.cnt_splitnum - 1));
		}
		else
		{
			split_arg.cnt_moji = 0;
			s++;
		}
	}
	split_command_last(s, &split_arg, &ret);
	return (ret);
}

/*
int main()
{
	char *s = read_all(0);
	char **ps = split_command(s, ';');
	char **tmp = ps;
	printf("\n\n%p\n", ps);
	printf("-------\n");
	while (*ps)
	{
		printf("%s\n", *ps);
		ps++;
	}
	split_free_all(tmp);
}
*/