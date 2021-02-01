#include "minishell.h"

int		ft_isalnum(int c)
{
	if (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z')
			|| ('0' <= c && c <= '9'))
		return (c);
	else
		return (0);
}


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


char *surround_minus_one(char *value)
{
	int len;
	int i;
	char *ret;

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

int which_quote(char c, int flag)
{
	if (c == '\'')
		return (1);
	else if (c == '\"')
		return (2);
	else if (c == -1)
		return (flag == 3 ? 0 : 3);
	return (flag);
}

void    check_quote(char c, char *bitflag_quote)
{
    if (c == '\'' && *bitflag_quote < 4 && !(*bitflag_quote & FLAG_DOUBLE_QUOTE))
        *bitflag_quote ^= FLAG_SINGLE_QUOTE;
    if (c == '\"' && *bitflag_quote < 4 && !(*bitflag_quote & FLAG_SINGLE_QUOTE))
        *bitflag_quote ^= FLAG_DOUBLE_QUOTE;
    if (c == -1)
        *bitflag_quote ^= FLAG_MINUS_ONE;
}

char        fff(char flag)
{
    if (flag == FLAG_SINGLE_QUOTE)
        return ('\'');
    if (flag == FLAG_DOUBLE_QUOTE)
        return ('\"');
    if (flag & FLAG_MINUS_ONE)
        return (-1);
	return (0);
}

void	remove_quotes(char *cmd)
{
    char flag;
    int i;
    int j;
    char flag2;

    i = 0;
    j = -1;
    flag = 0;
    flag2 = 0;
    while (cmd[++j])
    {
        check_quote(cmd[j], &flag);
        if (flag < flag2)
        {
            if (cmd[j] != fff(flag2))
                cmd[i++] = cmd[j];
        }
        else if (cmd[j] != fff(flag))
            cmd[i++] = cmd[j];
        flag2 = flag;
    }
    cmd[i] = '\0';
}

int single_quote(char now, int flag)
{
	flag = 0;
	if (now == '\'')
		return (1);
	else
		return (flag);
}

char *deploy(char *input, t_arg_main *arg_main)
{
	int i;
	char flag;
	char *tmp;
	int len;
	char *ret = malloc(1);
	t_arg arg;

	ret[0] = '\0';

	i = 0;
	flag = 0;
	while (input[i])
	{
		check_quote(input[i], &flag);
		if (flag == FLAG_SINGLE_QUOTE)
		{
			len = 0;
			i++;
			while (input[i] != '\'')
			{
				len++;
				i++;
			}
			tmp = ft_strndup(input + (i - (len + 1)), (len + 1) + 1);
			i++;
			flag = 0;
		}
		else if (input[i] == '$' && input[i + 1])
		{
			i++;
			len = 0;
			while (ft_isalnum(input[i]) || (input[i] == '?' && len == 0))
			{
				len++;
				i++;
			}
			tmp = ft_strndup(input + i - len, len);

			if (0 == arg_get(arg_main, &arg, tmp))
			{	
				tmp = surround_minus_one((char *)arg.data);
				arg_free(&arg);
			}
			else
			{
				free(tmp);
				tmp = ft_strdup("");
			}
		}
		else
		{				
			tmp = malloc(sizeof(char) * 1 + 1);
			tmp[0] = input[i];
			tmp[1] = '\0';
			i++;
		}
		ret = ft_strjoin_free(ret, tmp);
	}
	return (ret);
}
