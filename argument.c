#include <stdlib.h>
#include <limits.h>
#include <stdio.h>

#define ARG_TYPE_STR 0
#define ARG_TYPE_INT 1

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
    int arg_num;
}               t_arg_main;


void    arg_free(t_arg *arg);
int    arg_copy(t_arg *dest, t_arg *src);
int     arg_new(t_arg_main *arg_main, t_arg *src);
int arg_add(t_arg_main *arg_main, t_arg *arg);
int    arg_main_ini(t_arg_main *arg_main);
int arg_charlen(t_arg *arg);
int ft_strcpy_int(char *dest, char *src);
char *arg_list_get_makestr(t_arg *arg);
char **arg_list_get(t_arg_main *arg_main);
int    _arg_delete_process(t_arg_main *arg_main, t_arg_list *arg_list, char *name, t_arg_list **ret);
void    arg_delete(t_arg_main *arg_main, char *name);
t_arg_list   *_arg_isexist_process(t_arg_list *arg_list, char *name);
t_arg_list   *arg_isexist(t_arg_main *arg_main, char *name);
int     arg_get(t_arg_main *arg_main, t_arg *arg, char *name);


int ft_strlen(char *s)
{
    int ret;

    ret = 0;
    while (*s)
    {
        ret++;
        s++;
    }
    return (ret);
}

char *ft_strdup(char *s)
{
    char *ret;
    int i;

    if (!(ret = (char *)malloc(ft_strlen(s) + 1)))
        return (NULL);
    i = -1;
    while (s[++i])
        ret[i] = s[i];
    ret[i] = '\0';
    return (ret);
}

int ft_strcmp(char *s1, char *s2)
{
    int i;

    if (!s1 || !s2)
        return (-1);
    i = -1;
    while (s1[++i])
        if (s1[i] != s2[i])
            return (1);
    return (!!s2[i]);
}

char *ft_itoa(int n)
{
    int len;
    int tmp;
    char *ret;

    if (n == INT_MIN)
        return (ft_strdup("-2147483648"));
    len = n < 0 ? 3 : 2;
    if (n < 0)
        n *= -1;
    tmp = n;
    while ((n /= 10))
        len++;
    if (!(ret = (char *)malloc(len)))
        return (NULL);
    ret[--len] = '\0';
    if (!tmp)
        ret[0] = '0';
    if (tmp < 0)
        ret[0] = '-';
    while (tmp)
    {
        ret[--len] = '0' + tmp % 10;
        tmp /= 10;
    }
    return (ret);
}



void    arg_free(t_arg *arg)
{
    free(arg->name);
    if (arg->type == ARG_TYPE_STR)
        free((char *)(arg->data));
    else if (arg->type == ARG_TYPE_INT)
        free(arg->data);
    arg->name = NULL;
    arg->data = NULL;
}

int    arg_copy(t_arg *dest, t_arg *src)
{
    if (!(dest->name = ft_strdup(src->name)))
        return (-1);
    if (src->type == ARG_TYPE_STR)
    {
        if (!(dest->data = ft_strdup((char *)(src->data))))
        {
            free(dest->name);
            return (-1);
        }
    }
    else
    {
        if (!(dest->data = (int *)malloc(sizeof (int))))
        {
            free(dest->name);
            return (-1);
        }
        *(int *)(dest->data) = *(int *)(src->data);
    }
    dest->type = src->type;
    return (0);
}

int     arg_new(t_arg_main *arg_main, t_arg *src)
{
    t_arg_list *tmp_arg_list;

    if (arg_main->arg_num == INT_MAX)
        return (-10);
    tmp_arg_list = arg_main->head.next;
    if (!(arg_main->head.next = (t_arg_list *)malloc(sizeof(t_arg_list))))
    {
        arg_main->head.next = tmp_arg_list;
        return (-1);
    }
    if (arg_copy(&(arg_main->head.next->arg), src))
    {
        free(arg_main->head.next);
        arg_main->head.next = tmp_arg_list;
        return (-1);
    }
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

int    arg_main_ini(t_arg_main *arg_main)
{
    arg_main->arg_num = 1;
    if (!(arg_main->head.arg.name = ft_strdup("?")))
        return (-1);
    arg_main->head.arg.type = ARG_TYPE_STR;
    if (!(arg_main->head.arg.data = ft_strdup("0")))
    {
        free(arg_main->head.arg.name);
        return (-1);
    }
    arg_main->head.next = NULL;
    return (0);
}

int arg_charlen(t_arg *arg)
{
    long long int len;
    long long int tmp_data;

    len = ft_strlen(arg->name) + 2;
    if (arg->type == ARG_TYPE_STR)
        len += ft_strlen((char *)(arg->data));
    else if (arg->type == ARG_TYPE_INT)
    {
        tmp_data = (long long int)*((int *)(arg->data));
        if (tmp_data < 0)
		{
            len++;
			tmp_data *= -1;
		}
        len++;
        while (tmp_data /= 10)
            len++;
    }
    if (len > INT_MAX)
        return (-1);
    return (len);
}

int ft_strcpy_int(char *dest, char *src)
{
    int i;

    i = -1;
    while (src[++i])
        dest[i] = src[i];
    dest[i] = '\0';
    return (i);
}

char *arg_list_get_makestr(t_arg *arg)
{
    char *ret;
    int i;
    int j;
    char *tmp_str;

    if (!(ret = (char *)malloc(arg_charlen(arg) + 1)))
        return (NULL);
    i = ft_strcpy_int(ret, arg->name);
    i += ft_strcpy_int(ret + i, "=");
    if (arg->type == ARG_TYPE_STR)
        i += ft_strcpy_int(ret + i, (char *)arg->data);
    else if (arg->type == ARG_TYPE_INT)
    {
        tmp_str = ft_itoa(*(int *)(arg->data));
        i += ft_strcpy_int(ret + i, tmp_str);
        free(tmp_str);
    }
    return (ret);   
}


char **arg_list_get(t_arg_main *arg_main)
{
    char **ret;
    t_arg_list  *current;
    int i;
    int arg_num;

    arg_num = arg_main->arg_num;
    if (!(ret = (char **)malloc(sizeof (char *) * (arg_num + 1))))
        return (NULL);
    current = &(arg_main->head);
    i = -1;
    while (++i < arg_num)
    {
        if (!(ret[i] = arg_list_get_makestr(&(current->arg))))
        {
            while (--i >= 0)
                free(ret[i]);
            free(ret);
            return (NULL);
        }
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
    if (!(arg_copy(arg, &(tmp_arg->arg))))
        return (-1);
    return (0);
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


int main()
{
    t_arg_main arg_main;
	int j[] = {12345, 0, -12345, 1, -1, INT_MAX, INT_MIN};
    t_arg arg[] = {{"?", ARG_TYPE_STR, "abcde"},
                    {"arg1", ARG_TYPE_STR, "123"},
                    {"arg2", ARG_TYPE_STR, "456"},
                    {"arg3", ARG_TYPE_STR, "789"},
                    {"arg4", ARG_TYPE_INT, &j[0]},
					{"arg5", ARG_TYPE_INT, &j[1]},
					{"arg6", ARG_TYPE_INT, &j[2]},
					{"arg7", ARG_TYPE_INT, &j[3]},
					{"arg8", ARG_TYPE_INT, &j[4]},
					{"arg9", ARG_TYPE_INT, &j[5]},
					{"arg10", ARG_TYPE_INT, &j[6]},
					};
    int tmp;
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
    	printf("==============\nadd arg4\n");{
        	add_out(&arg_main, arg[4 + k]);
    	    printf("==============\n");
	    }
	}
}
