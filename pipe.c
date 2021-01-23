#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void pipeline(char ***cmd)
{
	int fd[2];
	pid_t pid;
	int fdd = 0;
	
	while (*cmd != NULL) {
		pipe(fd);
		if ((pid = fork()) == -1) {
			perror("fork");
			exit(1);
		}
		//子プロセス
		else if (pid == 0) {
			dup2(fdd, 0);               // dup2 : 右のファイルディスクリプタを左のやつに参照させる
			if (*(cmd + 1) != NULL) {   // 次の（パイプで区切られた）コマンド要素が存在するなら
				dup2(fd[1], 1);         // 標準出力を次の要素へ向ける　（もし最後だったらほんまもんの標準出力へ出す）
			}
			close(fd[0]);               //子供側ではfd[0]使わない(cf. pipe.gif)
			
			//redirect();
			//excute();
			execvp((*cmd)[0], *cmd);    // ！！！！！！　　ここでコマンド実行　　！！！！！！
			
			exit(1);
		}
		// 親プロセス
		else {
			wait(NULL);                 // 子プロセス終了待ち
			close(fd[1]);			    //親側ではfd[1](cf. pipe.gif)使わないのでクローズ（ファイルディスクリプタはプロセスみんなで共有してるから閉じないと大変）
			fdd = fd[0];				// 標準入力を次の要素の標準入力へつなげるために保存する。　->　19行目にて実際につなげる
			cmd++;
		}
	}
}

int main(int argc, char *argv[])
{
	char *ls[] = {"ls", "-al", NULL};
	char *rev[] = {"rev", NULL};
	char *nl[] = {"nl", NULL};
	char *cat[] = {"cat", "-e", NULL};
	
	//　ここまでで

	char **cmd[] = {ls, rev, nl, cat, NULL};

	//　パイプあったら
		pipeline(cmd);
	
	// パイプなかったら
		//redirect();
		//excute();

	return (0);
}