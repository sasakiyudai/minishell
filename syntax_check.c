#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "minishell.h"

# define MALLOC_FAIL 1
# define ARG_TYPE_STR 0
# define ARG_TYPE_int 0
#define ARG_TYPE_STR 0
#define ARG_TYPE_LLINT 1
#define STR_LLONG_MIN "-9223372036854775808"
#define STR_LLONG_MAX "9223372036854775807"
#define FLAG_DOUBLE_QUOTE 2
#define FLAG_SINGLE_QUOTE 1

#define SYNTAX_ERROR_QUOTE 1
	void	print_error(int i);
typedef struct s_syntax_flag
{
	char pipe;
	char r_redirect;
	char l_redirect;
	char semi;
}				t_syntax_flag;

int		syntax_check_make_sedstr(char *cmd_raw, char **ret)
{
	char	bitflag_quote;
	int		i;

	if (!(*ret = (char *)malloc(strlen(cmd_raw) + 1)))
	{
		print_error(MALLOC_FAIL);
		return (-1);
	}
	bitflag_quote = 0;
	i = -1;
	while (*cmd_raw)
	{
		check_quote(*cmd_raw, &bitflag_quote);
		if (bitflag_quote <= FLAG_DOUBLE_QUOTE)
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

int		print_synerr(char *cmd)
{
	char s[8];

	s[0] = cmd[0];
	s[2] = '\0';
	if (cmd[0] == '\n' || cmd[0] == '\0')
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
	set_hatena(g_arg_main, 258);
	return (258);
}

int		syntax_check_process3(char *cmd, t_syntax_flag *syntax_flag)
{
	if (*cmd == '\n' || *cmd == '\0')
	{
		if (syntax_flag->pipe || syntax_flag->r_redirect ||
			syntax_flag->l_redirect)
			return (print_synerr(cmd));
	}
	else if (*cmd == ';')
	{
		if (syntax_flag->pipe || syntax_flag->r_redirect ||
			syntax_flag->l_redirect || syntax_flag->semi)
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

int		syntax_check_process2(char *cmd, t_syntax_flag *syntax_flag)
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
		return (syntax_check_process3(cmd, syntax_flag));
	}
	return (0);
}

int		syntax_check_process(char *cmd, t_syntax_flag *syntax_flag)
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
		return (syntax_check_process2(cmd, syntax_flag));
	return (0);
}

int		syntax_check_main(char *cmd)
{
	t_syntax_flag	syntax_flag;

	bzero(&syntax_flag, sizeof(t_syntax_flag));
	while (*cmd)
	{
		if (syntax_check_process(cmd, &syntax_flag))
			return (258);
		cmd++;
	}
	if (syntax_check_process(cmd, &syntax_flag))
		return (258);
	return (0);
}

int		myprint_error(int i)
{
	i++;
	if (SYNTAX_ERROR_QUOTE)
		printf("bash: bad quote\n");
	return (258);
}

int		syntax_check(char *cmd_raw)
{
	char	*cmd;
	int		tmp;

	if (syntax_check_make_sedstr(cmd_raw, &cmd) == 1)
	{
		free(cmd);
		return (myprint_error(SYNTAX_ERROR_QUOTE));
	}
	if (!cmd)
		return (-1);
	tmp = syntax_check_main(cmd);
	free(cmd);
	return (tmp);
}
