#include "minishell.h"

char    *ft_strcat(char *dest, char *src)
{
    int i;

    i = -1;
    while (src[++i])
        dest[i] = src[i];
    dest[i] = '\0';
    return (dest);
}

int ft_strcat_int(char *dest, char *src)
{
    int i;

    i = -1;
    if (!src)
        return (0);
    while (src[++i])
        dest[i] = src[i];
    dest[i] = '\0';
    return (i);
}

int    ft_itoa(long long int n, char *dest)
{
    int len;
    int ret;
    long long int tmp;

    if (n == LLONG_MIN)
    {
        ft_strcat(dest, STR_LLONG_MIN);
        return (ft_strlen(STR_LLONG_MIN));
    }
    if (!n)
        dest[0] = '0';
    if (n < 0)
        dest[0] = '-';
    len = n < 0 ? 3 : 2;
    if (n < 0)
        n *= -1;
    tmp = n;
    while ((n /= 10))
        len++;
    dest[--len] = '\0';
    ret = len;
    while (tmp)
    {
        dest[--len] = '0' + tmp % 10;
        tmp /= 10;
    }
    return (ret);
}

void    arg_free(t_arg *arg)
{
    free(arg->name);
    free(arg->data);
    arg->name = NULL;
    arg->data = NULL;
}

int    arg_copy(t_arg *dest, t_arg *src)
{
    dest->name = ft_strdup(src->name);
    dest->data = ft_strdup(src->data);
    return (0);
}

int     arg_new(t_arg_main *arg_main, t_arg *src)
{
    t_arg_list *tmp_arg_list;

    if (arg_main->arg_num == INT_MAX)
        return (-10);
    tmp_arg_list = arg_main->head.next;
    arg_main->head.next = (t_arg_list *)malloc(sizeof(t_arg_list));
    arg_copy(&(arg_main->head.next->arg), src);
    arg_main->arg_num++;
    arg_main->head.next->next = tmp_arg_list;
    return (0);
}

int arg_add(t_arg_main *arg_main, t_arg *arg)
{
    t_arg_list   *tmp_arg_list;

    if ((tmp_arg_list = arg_isexist(arg_main, arg->name)))
    {
        arg_free(&(tmp_arg_list->arg));
        return (arg_copy(&(tmp_arg_list->arg), arg));
    }
    return (arg_new(arg_main, arg));
}

void    _arg_list_ini_process(t_arg_list *arg_list)
{
    while (arg_list->next)
        _arg_list_ini_process(arg_list->next);
    arg_free(&(arg_list->arg));
    free(arg_list);
}

int    arg_list_ini(t_arg_main *arg_main)
{
    if (arg_main->head.next)
        _arg_list_ini_process(arg_main->head.next);
    arg_free(&(arg_main->head.arg));
    return (arg_main_ini(arg_main));
}

int    arg_main_ini(t_arg_main *arg_main)
{
    arg_main->arg_num = 1;
    arg_main->head.arg.name = ft_strdup("?");
    arg_main->head.arg.data = ft_strdup("0");
    arg_main->head.next = NULL;
    return (0);
}

int arg_charlen(t_arg *arg, int quote)
{
    long long int len;

    len = ft_strlen(arg->name) + 1;
    len += ft_strlen(arg->data);
    if (!arg->data)
    {
        if (quote)
            len--;
        else
            len += 2;
    }
    return (len);
}

char *arg_to_str_quotes(t_arg *arg)
{
    char *ret;
    int i;

    if (!arg)
        return (NULL);
    ret = (char *)malloc(arg_charlen(arg, 1) + 3);
    i = ft_strcat_int(ret, arg->name);
    if (arg->data)
    {
        i += ft_strcat_int(ret + i, "=\"");
        i += ft_strcat_int(ret + i, arg->data);
        i += ft_strcat_int(ret + i, "\"");
    }
    return (ret);
}

char *arg_to_str(t_arg *arg)
{
    char *ret;
    int i;

    if (!arg)
        return (NULL);
    ret = (char *)malloc(arg_charlen(arg, 0) + 1);
    i = ft_strcat_int(ret, arg->name);
    i += ft_strcat_int(ret + i, "=");
    if (arg->data)
        i += ft_strcat_int(ret + i, arg->data);
    else
    {
        ret[i] = -1;
        ret[i + 1] = '\0';
    }
    return (ret);
}


char **arg_list_get_quote(t_arg_main *arg_main)
{
    char **ret;
    t_arg_list  *current;
    int i;
    int arg_num;

    arg_num = arg_main->arg_num - 1;
    ret = (char **)malloc(sizeof (char *) * (arg_num + 1));
    current = arg_main->head.next;
    i = -1;
    while (++i < arg_num)
    {
        ret[i] = arg_to_str_quotes(&(current->arg));
        current = current->next;
    }
    ret[i] = NULL;
    return (ret);
}

int arg_list_cnt(t_arg_list *arg_list)
{
    if (arg_list->next)
        return ((!!arg_list->arg.data) + arg_list_cnt(arg_list->next));
    return (!!arg_list->arg.data);
}

char **arg_list_get(t_arg_main *arg_main)
{
    char **ret;
    t_arg_list  *current;
    int i;
    int arg_num;

    arg_num = arg_list_cnt(&(arg_main->head)) - 1;
    ret = (char **)malloc(sizeof (char *) * (arg_num + 1));
    current = arg_main->head.next;
    i = 0;
    while (i < arg_num)
    {
        if (current->arg.data)
            ret[i++] = arg_to_str(&(current->arg));
        current = current->next;
    }
    ret[i] = NULL;
    return (ret);
}

void    split_free_all(char **ss)
{
    int i;

    i = -1;
    while (ss[++i])
        free(ss[i]);
    free(ss);
}

int	_arg_delete_process(t_arg_main *arg_main, t_arg_list *arg_list, char *name, t_arg_list **ret)
{
    t_arg_list *ret_arg_list;

    if (!ft_strcmp(arg_list->arg.name, name))
    {
        *ret = arg_list->next;
        arg_free(&(arg_list->arg));
        free(arg_list);
        arg_main->arg_num--;
        return (1);
    }
    else if (arg_list->next)
        if (_arg_delete_process(arg_main, arg_list->next, name, &ret_arg_list))
            arg_list->next = ret_arg_list;
    return (0);
}

void    arg_delete(t_arg_main *arg_main, char *name)
{
    t_arg_list  *tmp;

	if (arg_main->head.next)
	    if (_arg_delete_process(arg_main, &(arg_main->head), name, &tmp))
    	    arg_main->head.next = tmp;
}

t_arg_list   *_arg_isexist_process(t_arg_list *arg_list, char *name)
{
    if (!arg_list->next)
        return (NULL);
    if (!(ft_strcmp(arg_list->next->arg.name, name)))
        return (arg_list->next);
    return (_arg_isexist_process(arg_list->next, name));
}

t_arg_list   *arg_isexist(t_arg_main *arg_main, char *name)
{
    if (!ft_strcmp(name, "?"))
        return (&(arg_main->head));
    return (_arg_isexist_process(&(arg_main->head), name));
}

int     arg_get(t_arg_main *arg_main, t_arg *arg, char *name)
{
    t_arg_list *tmp_arg;

    if (!(tmp_arg = arg_isexist(arg_main, name)))
        return (1);
    arg_copy(arg, &(tmp_arg->arg));
    return (0);
}

void    set_hatena(t_arg_main *arg_main, int i)
{
    int j;
    int len;
    t_arg arg;

    j = i;
    len = 1 + (i < 0);
    i = i < 0 ? -i : i;
    while (i > 9 && len++)
        i /= 10;
    arg.name = "?";
    arg.data = malloc(len + 1);
    ft_itoa(j, (arg.data));
    arg_add(arg_main, &arg);
}

void    add_out(t_arg_main *arg_main, t_arg arg)
{
    char **ss;
    int i;

    arg_add(arg_main, &arg);
    ss=arg_list_get(arg_main);

    i = -1;
	while (ss[++i])
		printf("%s\n", ss[i]);
    split_free_all(ss);
}

/*
int main()
{
    t_arg_main arg_main;
	long long int j[] = {12345, 0, -12345, 1, -1, LLONG_MAX, LLONG_MIN};
    t_arg arg[] = {{"?", ARG_TYPE_STR, "abcde"},
                    {"arg1", ARG_TYPE_STR, "123"},
                    {"arg2", ARG_TYPE_STR, "456"},
                    {"arg3", ARG_TYPE_STR, "789"},
                    {"arg4", ARG_TYPE_LLINT, &j[0]},
					{"arg5", ARG_TYPE_LLINT, &j[1]},
					{"arg6", ARG_TYPE_LLINT, &j[2]},
					{"arg7", ARG_TYPE_LLINT, &j[3]},
					{"arg8", ARG_TYPE_LLINT, &j[4]},
					{"arg9", ARG_TYPE_LLINT, &j[5]},
					{"arg10", ARG_TYPE_LLINT, &j[6]},
					};
    int i;

    if (arg_main_ini(&arg_main))
        return (-1);
    char **ss = arg_list_get(&arg_main);
    printf("==============\nprint  ini\n");{
        i = -1;
        while (ss[++i])
            printf("%s\n", ss[i]);
        split_free_all(ss);
        printf("==============\n");
    }

    printf("==============\ndelete  bad arg name\n");{
        arg_delete(&arg_main, "bad name");
		ss = arg_list_get(&arg_main);
        i = -1;
        while (ss[++i])
            printf("%s\n", ss[i]);
        split_free_all(ss);
        printf("==============\n");
    }

    printf("==============\nadd arg1\n");{
        add_out(&arg_main, arg[1]);
        printf("==============\n");
    }

    printf("==============\nadd arg2\n");{
        add_out(&arg_main, arg[2]);
        printf("==============\n");
    }

    printf("==============\ndelete arg1\n");{
        arg_delete(&arg_main, "arg1");
		ss = arg_list_get(&arg_main);
        i = -1;
        while (ss[++i])
            printf("%s\n", ss[i]);
        split_free_all(ss);
        printf("==============\n");
    }

    printf("==============\ndelete  bad arg name\n");{
        arg_delete(&arg_main, "bad name");
		ss = arg_list_get(&arg_main);
        i = -1;
        while (ss[++i])
            printf("%s\n", ss[i]);
        split_free_all(ss);
        printf("==============\n");
    }

    printf("==============\ndelete arg2\n");{
        arg_delete(&arg_main, "arg2");
		ss = arg_list_get(&arg_main);
        i = -1;
        while (ss[++i])
            printf("%s\n", ss[i]);
        split_free_all(ss);
        printf("==============\n");
    }

    printf("==============\ndelete ?\n");{
        arg_delete(&arg_main, "?");
		ss = arg_list_get(&arg_main);
        i = -1;
        while (ss[++i])
            printf("%s\n", ss[i]);
        split_free_all(ss);
        printf("==============\n");
    }

	int k;
	k = -1;
	while (++k < 7)
	{
    	printf("==============\nadd arg%d\n", k);{
        	add_out(&arg_main, arg[4 + k]);
    	    printf("==============\n");
	    }
	}
}
*/
