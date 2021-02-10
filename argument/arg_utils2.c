#include "minishell.h"

t_arg_list	*arg_isexist_process(t_arg_list *arg_list, char *name)
{
	if (!arg_list->next)
		return (NULL);
	if (!(ft_strcmp(arg_list->next->arg.name, name)))
		return (arg_list->next);
	return (arg_isexist_process(arg_list->next, name));
}

t_arg_list	*arg_isexist(t_arg_main *arg_main, char *name)
{
	if (!ft_strcmp(name, "?"))
		return (&(arg_main->head));
	return (arg_isexist_process(&(arg_main->head), name));
}

int		arg_get(t_arg_main *arg_main, t_arg *arg, char *name)
{
	t_arg_list *tmp_arg;

	if (!(tmp_arg = arg_isexist(arg_main, name)))
		return (1);
	arg_copy(arg, &(tmp_arg->arg));
	return (0);
}
