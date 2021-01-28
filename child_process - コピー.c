#include <dirent.h>

typedef struct s_cmd
{
    char *name;
    int (*func)(char **);
}               t_cmd;


int isbuiltin(char *name, t_cmd cmd[], int (**ret)(char **))
{
    while (cmd[0].name)
    {
        if (!strcmp(name, cmd[0].name))
        {
            *ret = cmd[0].func;
            return (1);
        }
        cmd++;
    }
    return (0);
}

int ispath_ok(char *path, char *name)
{
    DIR *dir;
    struct dirent *dent;

    if (!(dir = opendir(path)))
        return (0);
        printf("s");
    while (!(dent = readdir(dir)))
    {
        printf("a");
        if (!strcmp(dent->d_name, name))
        {
            closedir(dir);
            return (1);
        }
    }
    closedir(dir);
    return (0);
}

int main(void)
{
    printf("%d", ispath_ok("./", "main.c"));
}

/*
int get_path_makestr(char **ret, char *path, char *name)
{
    int path_len;

    path_len = ft_strlen(path);
    if (!(*ret = (char *)malloc(path_len + 1 + ft_strlen(name) + 1)))
        return (-1);
    ft_strcpy(*ret, *path);
    (*ret)[path_len] = '/';
    ft_strcpy(*ret + path_len + 1, name);
    return (0);
}

int get_path_make_strarry(t_arg_main *arg_main, char ***path)
{
    t_arg arg;
    int tmp;

    if ((tmp = arg_get(arg_main, &arg, "PATH")))
        return (tmp); 
    if (!(*path = split_command((char *)(arg.data), ':')))
    {
        arg_free(&arg);
        return (-1);
    }
    arg_free(&arg);
    return (0);
}

int get_path(t_arg *arg_main, char **ret, char *name)
{
    char **path;
    char **tmp_path;
    t_arg arg;
    int tmp;

    if (!(tmp = get_path_make_strarry(arg_main, &path)))
        return (tmp);
    tmp_path = path;
    while (*path)
    {
        if (ispath_ok(*path, name))
        {
            tmp = get_path_makestr(ret, *path, name);
            split_free_all(tmp_path);
            return (tmp);
        }
        path++;
    }
    split_free_all(tmp_path);
    return (0);
}

*/