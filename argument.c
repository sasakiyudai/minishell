//type   string:0  int:1

#define ARG_SIZE 30
#define ARG_TYPE_STR 0
#define ARG_TYPE_int 0

typedef struct s_arg
{
    char *name;
    int type;
    void *data;
}               t_arg;

typedef struct s_arg_list
{
    t_arg   args[ARG_SIZE];
    int     arg_num;
    s_arg_list  *next;
}               t_arg_list;

int     arg_add(t_arg *arg, t_arg_list *arg_list)
{
    int i;

    i = -1;
    while (++i < arg_list->arg_num)
        if (!arg_list->args[i].name)
            return (_bcopy_int(&arg_list[i], arg, sizeof(t_arg)));
    if (!arg_list->next)
        if (!(arg_list->next = (t_arg_list *)malloc(sizof(t_arg_list))))
            return (-1);
        else
            _bzero(arg_list->next, sizeof(t_arg_list));
    return (arg_add(arg, arg_list->next));)
}

int     arg_free(t_arg *arg)
{
    free(arg->name);
    if (arg->type == ARG_TYPE_STR)
        free(*(arg->data));
    free(arg->data);
    arg->name = NULL;
    arg->data = NULL;
    return (0);
}

int     arg_delete(t_arg *arg, t_arg_list *arg_list)
{
    int i;

    i = -1;
    while (++i < arg_list->arg_num)
        if (!strcmp(arg_list->args[i].name, arg->name))
            return (arg_free(arg_list->args[i]));
    if (!arg_list->next)
        return (-1);
    arg_delete(arg, arg_list->next);
}
