#include "minishell.h"

char	*ft_newstr_ncat(char *src1, char *src2, int n)
{
	char	*ret;
	int		i;
	int		j;

	if (!(ret = (char *)malloc2(n + 1)))
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

void	exit_ctrld(void)
{
	t_arg	arg;

	write(2, "exit\n", 5);
	arg_get(g_arg_main, &arg, "?");
	exit(ft_atoi(arg.data));
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
			exit_ctrld();
		if ((f = 1) && !ret_read)
		{
			write(2, "  \b\b", 4);
			continue;
		}
		buf[ret_read] = '\0';
		ret = ft_newstr_ncatfree(ret, buf, (cnt_read += ret_read), 1);
		if (buf[ret_read - 1] == '\n' && !(ret[cnt_read - 1] = '\0'))
			break ;
		if (buf[ret_read - 1])
			write(2, "  \b\b", 4);
	}
	if (ret_read >= 0)
		return (ret);
	exit(1);
}
