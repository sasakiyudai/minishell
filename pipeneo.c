#include "libft.h"
//
//char *get_path(t_arg *args, char *command);
//void pipeline(char ***cmd, t_arg *args);
//char *cmd_join(char *s1, char *s2);
//char *search_dir(char *path, char *command);
//
size_t	ft_strlen(const char *s)
{
	size_t len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

int	ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i])
	{
		if (s1[i] == '\0')
			return (0);
		i++;
	}
	return (s1[i] > s2[i] ? 1 : -1);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*p;

	if (!(p = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = 0;
	if (ft_strlen(s) <= start)
	{
		p[i] = 0;
		return (p);
	}
	while (i < len)
	{
		p[i] = s[start + i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

static int	ft_count(char const *s, char c)
{
	int word;
	int len;

	word = 0;
	len = 0;
	while (*s)
	{
		if (*s == c)
		{
			if (len > 0)
				word++;
			len = 0;
		}
		else
			len++;
		s++;
	}
	if (len > 0)
		word++;
	return (word);
}

char		**ft_split(char const *s, char c)
{
	char	**p;
	int		cnt;
	int		i;
	int		j;

	if (!(p = malloc(sizeof(char*) * (ft_count(s, c) + 1))))
		return (NULL);
	i = 0;
	j = 0;
	while (s[j])
	{
		while (s[j] == c)
			j++;
		cnt = j;
		while (s[j] != c && s[j])
			j++;
		if (j > cnt)
			p[i++] = ft_substr(s, cnt, j - cnt);
	}
	p[i] = NULL;
	return (p);
}

//
//void pipeline(char ***cmd, t_arg *args)
//{
//	int fd[2];
//	char **envs;
//	pid_t pid;
//	int fdd = 0;
//	
//	while (*cmd != NULL) {
//		pipe(fd);
//		if ((pid = fork()) == -1) {
//			perror("fork");
//			exit(1);
//		}
//		//子プロセス
//		else if (pid == 0) {
//			dup2(fdd, 0);               // dup2 : 右のファイルディスクリプタを左のやつに参照させる
//			if (*(cmd + 1) != NULL) {   // 次の（パイプで区切られた）コマンド要素が存在するなら
//				dup2(fd[1], 1);         // 標準出力を次の要素へ向ける　（もし最後だったらほんまもんの標準出力へ出す）
//			}
//			close(fd[0]);               //子供側ではfd[0]使わない(cf. pipe.gif)
//			
//			
//			// リダイレクト
//			
//
//
//			// 組み込みだったら
//				// 組み込み実行
//			//　外部だったら
//				get_path(args, (*cmd)[0]); // execve　の第一引数をgetする　（大体実装）
//				envs = list_to_str(args); // 環境変数リストを　execve　の第三引数のために文字列配列化する　（未実装）
//				
//				execve((*cmd)[0], *cmd, envs);    // ！！！！！！　　ここでコマンド実行　　！！！！！！
//				
//				free_tab(envs);
//				exit(1);
//
//			exit(1);
//		}
//		// 親プロセス
//		else {
//			wait(NULL);                 // 子プロセス終了待ち
//			close(fd[1]);			    //親側ではfd[1](cf. pipe.gif)使わないのでクローズ（ファイルディスクリプタはプロセスみんなで共有してるから閉じないと大変）
//			fdd = fd[0];				// 標準入力を次の要素の標準入力へつなげるために保存する。　->　19行目にて実際につなげる
//			cmd++;
//		}
//	}
//}
//
//int main(int argc, char *argv[], char *envp[])
//{
//	t_arg *args;
//
//	envp_list(envp, args); // 環境変数文字列配列を連結リストへ
//	char *ls[] = {"ls", "-al", NULL};
//	char *rev[] = {"rev", NULL};
//	char *nl[] = {"nl", NULL};
//	char *cat[] = {"cat", "-e", NULL};
//	char **cmd[] = {ls, rev, nl, cat, NULL};
//
//	pipeline(cmd, args);
//	return (0);
//}
//
//char *cmd_join(char *s1, char *s2)
//{
//	char	*tmp;
//	char	*path;
//
//	tmp = ft_strjoin(s1, "/");
//	path = ft_strjoin(tmp, s2);
//	free(tmp);
//	tmp = NULL;
//	return (path);
//}
//
//char *search_dir(char *path, char *command)
//{
//	char	*ret;
//	DIR		*drip;
//	struct dirent *cmd;
//
//	ret = NULL;
//	if (!(drip = opendir(path)))
//		return (NULL);
//	while ((cmd = readdir(drip)))
//	{
//		if (ft_strcmp(cmd->d_name, command) == 0)
//			ret = cmd_join(path, command);
//	}
//	closedir(drip);
//	return (ret);
//}
//
//char *get_path(t_arg *args, char *command)
//{
//	char **paths;
//	char *path;
//	int i;
//
//	path = NULL;
//	while (ft_strcmp(args->name, "PATH") != 0)
//	 	args = args->next;
//	paths = ft_split(args->data, ':');
//	if (paths[0] == NULL)
//		return ("");
//	path = search_dir(paths[0], command);
//	i = 1;
//	while (path == NULL && paths[i])
//		path = search_dir(paths[i++], command);
//	if (path == NULL)
//		return ("");
//	free_tab(paths);
//	return (path);
//}
//// path　要フリー

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


// just count number of commands
int count(char ***cmd)
{
	int i;
	i = 0;
	while (cmd[i])
		i++;
	return i;
}

int ft_tablen(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int num_of_redirect(char **tab)
{
	int i;
	int res;

	i = 0;
	res = 0;
	while (tab[i])
	{
		if (ft_strcmp(tab[i], ">") == 0 || ft_strcmp(tab[i], ">>") == 0 || ft_strcmp(tab[i], "<") == 0)
			res++;
		i++;
	}
	return (res);
}

int is_right(char **cmd)
{
	int i;
	int ret;

	i = 0;
	ret = 0;
	while (cmd[i])
	{
		if (ft_strcmp(cmd[i], ">") == 0)
			ret = i;
		if (ft_strcmp(cmd[i], ">>") == 0)
			ret = -i;
		i++;
	}
	return (ret);
}

int is_left(char **cmd)
{
	int i;
	int ret;

	i = 0;
	ret = 0;
	while (cmd[i])
	{
		if (ft_strcmp(cmd[i], "<") == 0)
			ret = i;
		i++;
	}
	return (ret);
}


void pipeline(char ***cmd, char ***raw_cmd)
{
	int		i, j = 0;
	pid_t	pid;
	int		cmd_len = count(cmd);
	int		fd[2*cmd_len];

	// pipe(2) for cmd_len times
	for(i = 0; i < cmd_len; i++){
        if(pipe(fd + i*2) < 0) {
            perror("couldn't pipe");
            exit(EXIT_FAILURE);
        }
    }
	while (*cmd != NULL) {

		if ((pid = fork()) == -1) {
			perror("fork");
			exit(1);
		}
		else if (pid == 0) {
			
			// if there is next
			if (*(cmd + 1) != NULL) {
			if(dup2(fd[j + 1], 1) < 0){
					perror("dup2");
					exit(EXIT_FAILURE);
				}
			}
			// if there is previous
			if (j != 0) {
				if(dup2(fd[j - 2], 0) < 0){
					perror("dup2");
					exit(EXIT_FAILURE);
				}
			}

			int in;
			int out;
			int r;
			if ((r = is_right(raw_cmd[j / 2])))
			{
				close(fd[j + 1]);
				if (r > 0)
					out = open(raw_cmd[j / 2][r + 1], O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
				else
					out = open(raw_cmd[j / 2][-r + 1], O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
				if (out == -1)
				{
					perror("open");
					return ;
				}
				dup2(out, 1);
			}
			if ((r = is_left(raw_cmd[j / 2])))
			{
				close(fd[j - 2]);
				in = open(raw_cmd[j / 2][r - 1], O_RDONLY, S_IRWXU);
				if (in == -1)
				{
					perror("open");
					return ;
				}
				dup2(in, 0);
			}

			for(i = 0; i < 2 * cmd_len; i++){
                close(fd[i]);
            }

			if(execvp((*cmd)[0], *cmd) < 0 ){
                perror((*cmd)[0]);
                exit(EXIT_FAILURE);
            }
		}
		else if(pid < 0) {
            perror("error");
            exit(EXIT_FAILURE);
        }

		// no wait in each process, 
		// because I want children to exec without waiting for each other
		// as bash does.
		cmd++;
		j += 2;
	}
	// close fds in parent process
	for(i = 0; i < 2 * cmd_len; i++){
        close(fd[i]);
    }
	// wait for children 
    for(i = 0; i < cmd_len; i++)
        wait(NULL);
}

char *separate_redirect(char *command);

void print_tab(char *tab[])
{
	int i;

	i = 0;
	while (tab[i])
		printf("%s\n", tab[i++]);
}

char **make_strb(char **str_a);

int main(int argc, char *argv[])
{
	// ">" "<" ">>"　を見つけたら、前後にスペースを開けた文字列を生成する関数　→　その後にスプリット
	char *raw_cat = "cat architecture.c > hi";
	char *raw_cat_ret;
	char *raw_echo = "echo toto";
	char *raw_echo_ret;
	
	raw_cat_ret = separate_redirect(raw_cat);
	raw_echo_ret = separate_redirect(raw_echo);

	char **cat = ft_split(raw_cat_ret, ' ');
	//char *cat1[] = {"cat", "architecture.c", NULL};
	char **cat1 = make_strb(cat);

	print_tab(cat);
	print_tab(cat1);
	//print_tab(cat1);
	char *ls[] = {"ls", NULL};
	char *ls1[] = {"ls", NULL};

	char *rev[] = {"rev", NULL};
	char *nl[] = {"nl", NULL};

	// char *cat[] = {"cat", "architecture.c", ">", "hi", NULL};
	// char *cat1[] = {"cat", "architecture.c", NULL};

	// char *wc[] = {"wc", "-c", NULL};
	// char *head[] = {"head", "-c", "1000", NULL};
	// char *time[] = {"time", "-p", "sleep", "3", NULL};
	// char *echo[] = {"echo", "toto", NULL};

	// raw_cmd　→　リダイレクトもファイル名も残したままのやつ
	// cmd →　リダイレクトもファイル名も削ぎ落として整形したやつ
	char **raw_cmd[] = {cat, NULL};
	char **cmd[] = {cat1, NULL};

	//pipeline(cmd, raw_cmd);
	return (0);
}

// ex) command = "ls > filename"
// ex) command = "ls >> filename"

int is_space(char c)
{
	if (c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t' || c == '\v')
		return (1);
	return (0);
}

int is_redirect(char c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

int is_ok(char *command, int i)
{
	int len = ft_strlen(command);

	if (command[i] == '<')
		return (1);
	if (i < len - 1 && command[i] == '>' && command[i + 1] == '>')
		return (1);
	if (1 < i && command[i] != '>' && command[i - 1] == '>' && command[i - 2] == '>')
		return (1);
	if (0 < i && i < len - 1 && command[i] == '>' && command[i - 1] != '>' && command[i + 1] != '>')
		return (1);
	if (0 < i && command[i] != '>' && command[i - 1] == '>' && command[i - 2])
		return (1);
	return (0);
}

char *set_res(char *res, char *command)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (command[i])
	{
		if (is_ok(command, i))
			res[j++] = ' ';
		res[j++] = command[i++];
	}
	res[j] = '\0';
	return (res);
}

char *separate_redirect(char *command)
{
	int i;
	int redirect;
	char *res;

	i = 0;
	redirect = 0;
	while (command[i])
	{
		if (is_redirect(command[i]))
			redirect++;
		i++;
	}
	res = malloc(sizeof(char) * (i + redirect + 1));
	return (set_res(res, command));
}

char **really_make_strb(char **str_a, int *table)
{
	int i;
	int j;
	int len;
	int cnt_redirect;
	char **str_b;
	
	i = 0;
	j = 0;
	len = ft_tablen(str_a);
	cnt_redirect = num_of_redirect(str_a);
	str_b = malloc(sizeof(char *) * (len - cnt_redirect * 2 + 1));
	while (str_a[i])
	{
		if (table[i] == 1)
		{
			i++;
			continue;
		}
		str_b[j++] = str_a[i++];
	}
	str_b[j] = NULL;
	return (str_b);
}

char **make_strb(char **str_a)
{
	int i;
	int *table;

	i = 0;
	table = malloc(sizeof(int) * ft_tablen(str_a));
	while (str_a[i])
	{
		if (ft_strcmp(str_a[i], ">>") == 0 || ft_strcmp(str_a[i], ">") == 0)
		{
			table[i] = 1;
			table[i + 1] = 1;
			i += 2;
		}
		else if (ft_strcmp(str_a[i], "<") == 0)
		{
			table[i] = 1;
			table[i - 1] = 1;
		}
		else
			table[i] = 0;
		i++;
	}
	return (really_make_strb(str_a, table));
}