#include <stdlib.h>
#include <stdio.h>
#include <string.h>
# define MALLOC_FAIL 1
# define ARG_TYPE_STR 0
# define ARG_TYPE_int 0
#define SYNTAX_ERROR_QUOTE 1
#define ARG_TYPE_STR 0
#define ARG_TYPE_LLINT 1
#define STR_LLONG_MIN "-9223372036854775808"
#define STR_LLONG_MAX "9223372036854775807"
#define FLAG_DOUBLE_QUOTE 2
#define FLAG_SINGLE_QUOTE 1

typedef int t_all;

typedef struct s_syntax_flag
{
	char pipe;
	char r_redirect;
	char l_redirect;
    char semi;
}               t_syntax_flag;

char	**split_command(char *s, char c);


void	_bzero(void	 *s, int n)
{
	char *str = (char *)s;
	int i = 0;

	while (i < n)
	{
		str[i] = 0;
		i++;
	}
}
void	check_quote(char c, char *bitflag_quote)
{
	if (c == '\'' && !(*bitflag_quote & FLAG_DOUBLE_QUOTE))
		*bitflag_quote ^= FLAG_SINGLE_QUOTE;
	if (c == '\"' && !(*bitflag_quote & FLAG_SINGLE_QUOTE))
		*bitflag_quote ^= FLAG_DOUBLE_QUOTE;
}

void    print_error(int i)
{
    
}

int	_syntax_check_make_sedstr(char *cmd_raw, char **ret)
{
	char bitflag_quote;
	int i;
	int j;

	if (!(*ret = (char *)malloc(strlen(cmd_raw))))
    {
        print_error(MALLOC_FAIL);
		return (-1);
    }
	bitflag_quote = 0;
	i = -1;
	while (*cmd_raw)
	{
		check_quote(*cmd_raw, &bitflag_quote);
		if (!bitflag_quote)
		{
			(*ret)[++i] = *cmd_raw;
			if (*cmd_raw == '\'' || *cmd_raw == '\"')
				(*ret)[i] = 'a';
		}
		cmd_raw++;
	}
    (*ret)[++i] = '\0';
    return (!!bitflag_quote);
}

int print_synerr(char *cmd)
{
	char s[8];

	s[0] = cmd[0];
	s[2] = '\0';
	if (cmd[0] == '\n')
		strcpy(s, "newline");
	else if (cmd[0] == '>')
		s[1] = cmd[1] * (cmd[1] == cmd[0]);
	else if (cmd[0] == '<')
		s[1] = '\0';
	else if (cmd[0] == '|')
		s[1] = cmd[1] * (cmd[1] == cmd[0]);
    else if (cmd[0] == ';')
		s[1] = cmd[1] * (cmd[1] == cmd[0]);
	printf("bash: syntax error near unexpected token `%s'\n", s);
	return (258);
}


int _syntax_check_process3(char *cmd, t_syntax_flag *syntax_flag)
{
    if (*cmd == '\n')
    {
        if (syntax_flag->pipe || syntax_flag->r_redirect || syntax_flag->l_redirect)
            return (print_synerr(cmd));
    }
    else if (*cmd == ';')
    {
        if (syntax_flag->pipe || syntax_flag->r_redirect || syntax_flag->l_redirect || syntax_flag->semi)
            return (print_synerr(cmd));
        syntax_flag->semi = 1;
    }
	else
	{
		syntax_flag->l_redirect = 0;
		syntax_flag->r_redirect = 0;
        syntax_flag->pipe = 0;
        syntax_flag->semi = 0;
	}
    return (0);
}

int _syntax_check_process2(char *cmd, t_syntax_flag *syntax_flag)
{
	if (*cmd == '>')
	{
		if (syntax_flag->r_redirect >= 2 || syntax_flag->l_redirect)
			return (print_synerr(cmd));
		(syntax_flag->r_redirect)++;
	}
	else if (*cmd == '<')
	{
		if (syntax_flag->r_redirect || syntax_flag->l_redirect)
			return (print_synerr(cmd));
		(syntax_flag->l_redirect)++;
	}
    else
    {
        return (_syntax_check_process3(cmd,syntax_flag));
    }
	return (0);
}

int	_syntax_check_process(char *cmd, t_syntax_flag *syntax_flag)
{
	if (*cmd == ' ')
	{
		if (syntax_flag->pipe)
			syntax_flag->pipe = 2;
		if (syntax_flag->r_redirect)
			syntax_flag->r_redirect = 2;
		if (syntax_flag->l_redirect)
		    syntax_flag->l_redirect = 2;
	}
	else if (*cmd == '|')	
	{
		if (syntax_flag->pipe >= 2 || syntax_flag->r_redirect || syntax_flag->l_redirect)
			return (print_synerr(cmd));
		syntax_flag->pipe++;
	}
	else
		return (_syntax_check_process2(cmd,syntax_flag));
	return (0);
}

int syntax_check_main(char *cmd)
{
	t_syntax_flag syntax_flag;

    _bzero(&syntax_flag, sizeof (t_syntax_flag));
	while (*cmd)
	{
		if (_syntax_check_process(cmd, &syntax_flag))
			return (258);
		cmd++;
	}
	return (0);
}

void myprint_error(int i)
{
    if (SYNTAX_ERROR_QUOTE)
        printf("bash: bad quote\n");
}

int syntax_check(char *cmd_raw)
{
	char *cmd;
	int tmp;

	if (_syntax_check_make_sedstr(cmd_raw, &cmd) == 1)
	{
		free(cmd);
		myprint_error(SYNTAX_ERROR_QUOTE);
		return (1);
	}
	if (!cmd)
		return (-1);
	tmp = syntax_check_main(cmd);
	free(cmd);
	return (tmp);	
}

int main(void)
{
	//printf("\n%d", syntax_check(strdup("cat > text\n")));
    printf("newline error\n======================================\n");
    {
        printf("%d\n\n", syntax_check(strdup("cat |\n")));
        printf("%d\n\n", syntax_check(strdup("cat ||\n")));
        printf("%d\n\n", syntax_check(strdup("cat >\n")));
        printf("%d\n\n", syntax_check(strdup("cat >>\n")));
        printf("%d\n\n", syntax_check(strdup("cat <\n")));
        printf("----1----\n");
        printf("%d\n\n", syntax_check(strdup("cat | cat |\n")));
        printf("%d\n\n", syntax_check(strdup("cat | cat |>\n")));
        printf("%d\n\n", syntax_check(strdup("cat | cat |>>\n")));
        printf("%d\n\n", syntax_check(strdup("cat | cat |<\n")));
        printf("----2----\n");
        printf("%d\n\n", syntax_check(strdup("cat | cat| \n")));
        printf("%d\n\n", syntax_check(strdup("cat | cat|> \n")));
        printf("%d\n\n", syntax_check(strdup("cat | cat|>> \n")));
        printf("%d\n\n", syntax_check(strdup("cat | cat|< \n")));

        printf("\nnewline  OK\n------------------------------------\n");
        printf("%d\n\n", syntax_check(strdup("cat |cat\n")));
        printf("%d\n\n", syntax_check(strdup("cat >text\n")));
        printf("%d\n\n", syntax_check(strdup("cat >>text\n")));
        printf("%d\n\n", syntax_check(strdup("cat <text\n")));
        printf("----4----\n");
        printf("%d\n\n", syntax_check(strdup("cat | cat | cat\n")));
        printf("%d\n\n", syntax_check(strdup("cat | cat |> text\n")));
        printf("%d\n\n", syntax_check(strdup("cat | cat |>> text\n")));
        printf("%d\n\n", syntax_check(strdup("cat | cat |< text\n")));
        printf("----5----\n");
        printf("%d\n\n", syntax_check(strdup("cat | cat|cat \n")));
        printf("%d\n\n", syntax_check(strdup("cat | cat|>text \n")));
        printf("%d\n\n", syntax_check(strdup("cat | cat|>>text \n")));
        printf("%d\n\n", syntax_check(strdup("cat | cat|<text \n")));
        printf("============\n");
    }

    printf("> < | error\n======================================\n");
    {
        printf("%d\n\n", syntax_check(strdup("cat >|\n")));
        printf("%d\n\n", syntax_check(strdup("cat >||\n")));
        printf("%d\n\n", syntax_check(strdup("cat >|||\n")));
        printf("%d\n\n", syntax_check(strdup("cat ><\n")));
        printf("%d\n\n", syntax_check(strdup("cat ><<\n")));
        printf("----11---\n");
        printf("%d\n\n", syntax_check(strdup("cat >><\n")));
        printf("%d\n\n", syntax_check(strdup("cat >><<\n")));
        printf("%d\n\n", syntax_check(strdup("cat >>>\n")));
        printf("%d\n\n", syntax_check(strdup("cat >>>>\n")));
        printf("%d\n\n", syntax_check(strdup("cat >>>>>\n")));
        printf("----12----\n");
        printf("%d\n\n", syntax_check(strdup("cat <|\n")));
        printf("%d\n\n", syntax_check(strdup("cat <||\n")));
        printf("%d\n\n", syntax_check(strdup("cat <|||\n")));
        printf("%d\n\n", syntax_check(strdup("cat <<\n")));
        printf("%d\n\n", syntax_check(strdup("cat <<<\n")));
        printf("======================\n");
    } 

    printf("pipe error\n======================================\n");
    {
        printf("%d\n\n", syntax_check(strdup("cat |||\n")));
        printf("%d\n\n", syntax_check(strdup("cat | |\n")));
        printf("%d\n\n", syntax_check(strdup("cat | ||\n")));
        printf("%d\n\n", syntax_check(strdup("cat | |||\n")));
        printf("----21----\n");
        printf("%d\n\n", syntax_check(strdup("cat || |\n")));
        printf("%d\n\n", syntax_check(strdup("cat || ||\n")));
        printf("%d\n\n", syntax_check(strdup("cat || |||\n")));
        printf("----22----\n");

        printf("OK\n==================\n");
        printf("%d\n\n", syntax_check(strdup("cat |\"\"\n")));
        printf("%d\n\n", syntax_check(strdup("cat >\"\"\n")));

    }
}


/*
int ini(t_all *all)
{
	if (!(arg_main_ini(&(all->arg_main))))
	{
		error(INI_FAIL);
		return (-1);
	}
}

int main(void)
{
	char *cmd_all;
	char **cmd_split;
	char **tmp_cmd_split;
	t_all all;

	if (ini(&all))
		while (1)
		{
			while (!(cmd_all = read_all(0)))
				error(MALLOC_FAIL);
			if (!(cmd_split = split_command(cmd_all, ';')))
				error(MALLOC_FAIL);
			else
			{
				tmp_cmd_split = cmd_split;
				while (*cmd_split)
				{
					command_main(*cmd_split);
					cmd_split++;
				}
				split_free_all(tmp_cmd_split);
			}
			free(cmd_all);	
		}

}

*/