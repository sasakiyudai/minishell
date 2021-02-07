#include "minishell.h"

char	*ft_newstr_ncat(char *src1, char *src2, int n)
{
	char	*ret;
	int		i;
	int		j;

	if (!(ret = (char *)malloc(n + 1)))
		return (NULL);
	i = -1;
	while (src1[++i])
		ret[i] = src1[i];
	j = 0;
	while (src2[j] != '\0')
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
	char	buf[1001];
	int		cnt_read;
	int		ret_read;
	int		f;

	cnt_read = 0;
	f = 0;
	ret = ft_strdup("");
	while (1 + (ret_read = read(fd, buf, 3)))
	{
		if (!f && !ret_read)
			exit(0 * write(1, "exit\n", 5));
		if ((f = 1) && !ret_read)
			continue;
		buf[ret_read] = '\0';
		ret = ft_newstr_ncatfree(ret, buf, (cnt_read += ret_read), 1);
		if (buf[ret_read - 1] == '\n' && !(ret[cnt_read - 1] = '\0'))
			break ;
		if (buf[ret_read - 1])
			write(1, "  \b\b", 4);
	}
	if (ret_read >= 0)
		return (ret);
	exit(1);
}

char	*ft_strndup(char *src, int n)
{
	char	*ret;

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

	ret = 0;
	bitflag_quote = 0;
	flag_sequencial = 0;
	while (*s == c)
		s++;
	while (*s)
	{
		check_quote(*s, &bitflag_quote);
		if ((!bitflag_quote || *s != c) && !flag_sequencial)
		{
			ret++;
			flag_sequencial = 1;
		}
		else if (!bitflag_quote && *s == c)
			flag_sequencial = 0;
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

void	split_make_str(char **s, t_split *split_arg, char **ret)
{
	ret[split_arg->cnt_splitnum] = ft_strndup(*s, split_arg->cnt_moji - 1);
	*s += split_arg->cnt_moji;
	split_arg->cnt_moji = 0;
	split_arg->flag_sequencial = 1;
}

int		split_command_ini(char **s, char c, t_split *split_arg, char ***ret)
{
	split_arg->cnt_splitnum = cnt_splitnum_command(*s, c) + 1;
	*ret = (char **)malloc(sizeof(char *) * split_arg->cnt_splitnum);
	if (!*ret)
		return (-1);
	ft_bzero(split_arg, sizeof(t_split));
	split_arg->flag_sequencial = 1;
	while (**s == c)
		(*s)++;
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
	char	**ret;

	if (split_command_ini(&s, c, &split_arg, &ret))
		return (NULL);
	while (s[split_arg.cnt_moji])
	{
		check_quote(s[split_arg.cnt_moji], &split_arg.bitflag_quote);
		if (s[split_arg.cnt_moji++] != c)
			split_arg.flag_sequencial = 0;
		else if (!split_arg.bitflag_quote && !split_arg.flag_sequencial &&
			(split_arg.cnt_moji >= 2 && s[split_arg.cnt_moji - 2] != '\\'))
		{
			split_make_str(&s, &split_arg, ret);
			if (!ret[split_arg.cnt_splitnum++])
				return (split_command_free(ret, split_arg.cnt_splitnum - 1));
		}
		else if (!split_arg.bitflag_quote)
		{
			split_arg.cnt_moji = 0;
			s++;
		}
	}
	split_command_last(s, &split_arg, &ret);
	return (ret);
}
