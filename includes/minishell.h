/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syudai <syudai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 14:00:42 by marvin            #+#    #+#             */
/*   Updated: 2021/02/11 21:28:18 by syudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define ARG_TYPE_STR 0
# define ARG_TYPE_LLINT 1
# define STR_LLONG_MIN "-9223372036854775808"
# define STR_LLONG_MAX "9223372036854775807"
# define FLAG_DOUBLE_QUOTE 2
# define FLAG_SINGLE_QUOTE 1
# define FLAG_MINUS_ONE 4
# define FLAG_ESCAPE 8
# define BAD_ARGNAME 1
# define SYNTAX_ERROR_QUOTE 1

# include "../libft/libft.h"
# include <stdint.h>
# include <errno.h>
# include <string.h>

typedef struct	s_arg
{
	char		*name;
	int			type;
	void		*data;
}				t_arg;

typedef struct	s_arg_list
{
	t_arg				arg;
	struct s_arg_list	*next;
}				t_arg_list;

typedef struct	s_arg_main
{
	t_arg_list	head;
	char		***raw;
	int			pwd_slash;
	int			arg_num;
	int			flag_sig;
	int			std_in;
	int			std_out;
}				t_arg_main;

typedef	struct	s_split
{
	int		cnt_splitnum;
	int		cnt_moji;
	int		flag_sequencial;
	char	bitflag_quote;
}				t_split;

typedef struct	s_syntax_flag
{
	char	pipe;
	char	r_redirect;
	char	l_redirect;
	char	semi;
}				t_syntax_flag;

extern char			*g_signal;
extern t_arg_main	*g_arg_main;

void			err_general(char *s, char *err, int status);
void			error_one_to_seven(t_arg_main *arg_main, char *cmd);
void			just_for_child(char ***r,
char ***cmd, char *path, t_arg_main *ar);
int				create_right(char ***raw_cmd, int j, int i);
int				return_print(char *cmd);
void			init_exec(int *i, int cmd_len, int *fd);
void			p_exit(char *cmd);
void			init_pipe(int *i, int *j, int count, int *fd);
void			set_fd(char ***cmd, char ***raw_cmd, int *fd, int j);
void			just_for_norm(char ***raw_cmd);
void			bin_e(char ***raw_cmd);
void			one_command_bin_e(char ***raw_cmd, t_arg_main *arg_main);
int				rare_exception(char ***raw_cmd);
int				is_ok(char *command, int i);
int				is_space(char c);
int				is_redirect(char c);
int				num_of_redirect(char **tab);
int				export_argadd(char *args[], t_arg_main *arg_main);
void			print_with_declare(char *envp[]);
int				export_name_check(char *cmd);
int				ft_tablen(char **tab);
char			*arg_to_str_quotes(t_arg *arg);
void			remove_quotes(char *cmd);
void			set_hatena(t_arg_main *arg_main, int i);
int				set_right(char ***raw_cmd, int j, int *fd, int is_pipe);
int				set_left(char ***raw_cmd, int j, int *fd, int is_pipe);
int				count(char ***cmd);
void			pipeline(char ***cmd, char ***raw_cmd, t_arg_main *arg_main);
void			safe_close(int fd);
void			sort(char *envp[]);
void			*malloc2(size_t size);
int				ft_cd(char **args, t_arg_main *arg_main);
int				ft_echo(char *args[]);
int				ft_pwd(void);
int				ft_exit(char *args[]);
int				ft_export(char *args[], t_arg_main *arg_main);
int				ft_unset(char *argv[], t_arg_main *arg_main);
int				ft_env(t_arg_main *arg_main);
void			arg_free(t_arg *arg);
int				arg_copy(t_arg *dest, t_arg *src);
int				arg_new(t_arg_main *arg_main, t_arg *src);
char			***make_command_array(char *cmd);
char			***make_strb_array(char ***cmd_split);
void			command_main(char *cmd_raw, t_arg_main *arg_main);
void			command_main_free(char ***cmd_split, char ***tmp_cmd_split);
void			ini(t_arg_main *arg_main, char *env[]);
void			remove_empty_strb(char **cmd_split, int *i);
void			ft_strncpy(char *dest, char *src, size_t n);
int				arg_add(t_arg_main *arg_main, t_arg *arg);
int				arg_main_ini(t_arg_main *arg_main);
int				ft_strcpy_int(char *dest, char *src);
char			*arg_to_str(t_arg *arg);
char			**arg_list_get(t_arg_main *arg_main);
int				arg_list_cnt(t_arg_list *arg_list);
char			**arg_list_get_quote(t_arg_main *arg_main);
int				arg_delete_process(t_arg_main *arg_main,
t_arg_list *arg_list, char *name, t_arg_list **ret);
void			arg_delete(t_arg_main *arg_main, char *name);
int				arg_get(t_arg_main *arg_main, t_arg *arg, char *name);
int				arg_list_ini(t_arg_main *arg_main);
void			arg_list_ini_process(t_arg_list *arg_list);
int				get_path(t_arg_main *arg_main, char **ret, char *name);
char			*ft_strndup(char *src, int n);
int				cnt_splitnum_command(char *s, char c);
char			**split_command_free(char **ret, int cnt_splitnum);
void			free_split_command_all(char **s);
void			check_quote(char c, char *bitflag_quote);
void			split_make_str(char **s, t_split *split_arg, char **ret);
int				split_command_ini(char **s,
char c, t_split *split_arg, char ***ret);
void			split_command_last(char *s, t_split *split_arg, char ***ret);
char			**split_command(char *s, char c);
void			split_free_all(char **s);
void			arg_free(t_arg *arg);
char			*surround_minus_one(char *value);
char			*ft_strjoin_free(char *s1, char *s2);
int				arg_copy(t_arg *dest, t_arg *src);
int				arg_new(t_arg_main *arg_main, t_arg *src);
int				arg_add(t_arg_main *arg_main, t_arg *arg);
int				arg_main_ini(t_arg_main *arg_main);
int				arg_charlen(t_arg *arg, int quote);
int				ft_strcpy_int(char *dest, char *src);
char			*arg_to_str(t_arg *arg);
void			arg_delete(t_arg_main *arg_main, char *name);
t_arg_list		*arg_isexist_process(t_arg_list *arg_list, char *name);
t_arg_list		*arg_isexist(t_arg_main *arg_main, char *name);
int				arg_get(t_arg_main *arg_main, t_arg *arg, char *name);
int				arg_list_ini(t_arg_main *arg_main);
void			arg_list_ini_process(t_arg_list *arg_list);
int				is_dollarble(char c);
char			fff(char flag);
int				ft_len(char *args[]);
char			*read_all(int fd);
int				count(char ***cmd);
int				is_builtin(char *command);
int				call_builtin(int tmp, char **str_b, t_arg_main *arg_main);
int				error(char *path);
char			*ft_strndup(char *src, int n);
char			*ft_strchar(const char *s, int c);
char			*deploy(char *input, t_arg_main *arg_main);
void			print_tab(char *env[]);
char			**make_strb(char **str_a);
int				syntax_check(char *cmd_raw);
int				print_synerr(char *cmd);
int				myprint_error(int i);
int				syntax_check_make_sedstr(char *cmd_raw, char **ret);
int				syntax_check_process3(char *cmd, t_syntax_flag *syntax_flag);
int				syntax_check_process2(char *cmd, t_syntax_flag *syntax_flag);
int				syntax_check_process(char *cmd, t_syntax_flag *syntax_flag);
int				syntax_check_main(char *cmd);
char			*separate_redirect(char *command);
void			one_command(char ***cmd, char ***raw_cmd, t_arg_main *arg_main);
void			remove_quotes(char *cmd);
int				which_quote(char c, int flag);
void			check_quote(char c, char *bitflag_quote);
int				ft_itoa(long long int n, char *dest);
void			remove_quotes(char *cmd);
int				single_quote(char now, int flag);

#endif
