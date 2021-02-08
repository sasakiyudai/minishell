/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syudai <syudai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 22:32:19 by syudai            #+#    #+#             */
/*   Updated: 2021/02/08 15:59:25 by rnitta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define MALLOC_FAIL 1
# define ARG_TYPE_STR 0
# define ARG_TYPE_int 0
#define ARG_TYPE_STR 0
#define ARG_TYPE_LLINT 1
#define STR_LLONG_MIN "-9223372036854775808"
#define STR_LLONG_MAX "9223372036854775807"
#define FLAG_DOUBLE_QUOTE 2
#define FLAG_SINGLE_QUOTE 1
#define FLAG_MINUS_ONE 4
#define FLAG_ESCAPE 8
#define BAD_ARGNAME 1

# include "../libft/libft.h"
# include <stdint.h>

typedef struct s_arg
{
	char *name;
	int type;
	void *data;
}               t_arg;

typedef struct s_arg_list
{
	t_arg   arg;
	struct s_arg_list  *next;
}               t_arg_list;

typedef struct s_arg_main
{
	t_arg_list  head;
	int		pwd_slash;
	int			arg_num;
}               t_arg_main;

typedef    struct    s_split
{
    int        cnt_splitnum;
    int        cnt_moji;
    int        flag_sequencial;
    char    bitflag_quote;
}                t_split;

extern char* g_signal;
extern t_arg_main* g_arg_main;

int             is_ok(char *command, int i);
int             is_space(char c);
int             is_redirect(char c);
int             num_of_redirect(char **tab);
int             ft_tablen(char **tab);
char			*arg_to_str_quotes(t_arg *arg);
void			remove_quotes(char *cmd);
void			set_hatena(t_arg_main *arg_main, int i);
void			set_right(char ***raw_cmd, int j, int *fd, int is_pipe);
void			set_left(char ***raw_cmd, int j, int *fd, int is_pipe);
int				count(char ***cmd);
void			pipeline(char ***cmd, char ***raw_cmd, t_arg_main *arg_main);
void			safe_close(int fd);
int				ft_cd(char **args, t_arg_main *arg_main);
int				ft_echo(char *args[]);
int				ft_pwd(void);
int 			ft_exit(char *args[]);
int				ft_export(char *args[], t_arg_main *arg_main);
int				ft_unset(char *argv[], t_arg_main *arg_main);
int				ft_env(t_arg_main *arg_main);
void    		arg_free(t_arg *arg);
int				arg_copy(t_arg *dest, t_arg *src);
int 			arg_new(t_arg_main *arg_main, t_arg *src);
int				arg_add(t_arg_main *arg_main, t_arg *arg);
int 			arg_main_ini(t_arg_main *arg_main);
int				ft_strcat_int(char *dest, char *src);
int				syntax_check(char *cmd_raw);
char			*arg_to_str(t_arg *arg);
char			**arg_list_get(t_arg_main *arg_main);
char			**arg_list_get_quote(t_arg_main *arg_main);
int				arg_delete_process(t_arg_main *arg_main, t_arg_list *arg_list, char *name, t_arg_list **ret);
void			arg_delete(t_arg_main *arg_main, char *name);
t_arg_list		*_arg_isexist_process(t_arg_list *arg_list, char *name);
t_arg_list		*arg_isexist(t_arg_main *arg_main, char *name);
int				arg_get(t_arg_main *arg_main, t_arg *arg, char *name);
int				arg_list_ini(t_arg_main *arg_main);
void			arg_list_ini_process(t_arg_list *arg_list);
int				get_path(t_arg_main *arg_main, char **ret, char *name);
char    		*ft_strndup(char *src, int n);
int     		cnt_splitnum_command(char *s, char c);
char    		**split_command_free(char **ret, int cnt_splitnum);
void    		free_split_command_all(char **s);
void    		check_quote(char c, char *bitflag_quote);
void    		split_make_str(char **s, t_split *split_arg, char **ret);
int				split_command_ini(char **s, char c, t_split *split_arg, char ***ret);
void    		split_command_last(char *s, t_split *split_arg, char ***ret);
char    		**split_command(char *s, char c);
void			split_free_all(char **s);
void    		arg_free(t_arg *arg);
char			*surround_minus_one(char *value);
char			*ft_strjoin_free(char *s1, char *s2);
int    			arg_copy(t_arg *dest, t_arg *src);
int     		arg_new(t_arg_main *arg_main, t_arg *src);
int 			arg_add(t_arg_main *arg_main, t_arg *arg);
int    			arg_main_ini(t_arg_main *arg_main);
int 			arg_charlen(t_arg *arg, int quote);
int 			ft_strcat_int(char *dest, char *src);
char 			*arg_to_str(t_arg *arg);
void   			arg_delete(t_arg_main *arg_main, char *name);
t_arg_list   	*_arg_isexist_process(t_arg_list *arg_list, char *name);
t_arg_list   	*arg_isexist(t_arg_main *arg_main, char *name);
int     		arg_get(t_arg_main *arg_main, t_arg *arg, char *name);
int    			arg_list_ini(t_arg_main *arg_main);
void    		arg_list_ini_process(t_arg_list *arg_list);
void			print_error(int i);
int				is_dollarble(char c);
char			fff(char flag);
int 			ft_len(char *args[]);
char			*read_all(int fd);
int				count(char ***cmd);
int				is_builtin(char *command);
int				call_builtin(int tmp, char **str_b, t_arg_main *arg_main);
int				error(char *path);
char			*ft_strndup(char *src, int n);
char			*ft_strchar(const char *s, int c);
char			*deploy(char *input, t_arg_main *arg_main);
void			print_tab(char *env[]);
char 			**make_strb(char **str_a);
int				syntax_check(char *cmd_raw);
char 			*separate_redirect(char *command);
void 			one_command(char ***cmd, char ***raw_cmd, t_arg_main *arg_main);
void			remove_quotes(char *cmd);
int 			which_quote(char c, int flag);
void 		   check_quote(char c, char *bitflag_quote);
void			remove_quotes(char *cmd);
int 			single_quote(char now, int flag);

#endif
