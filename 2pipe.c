/*
** pipex.c - multipipes support
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

/*
 * loop over commands by sharing
 * pipes.
 */
static void
pipeline(char ***cmd)
{
	int fd[2];
	pid_t pid;
	int fdd = 0;				/* Backup */

	while (*cmd != NULL) {
		if(pipe(fd) < 0) {
            perror("couldn't pipe");
            exit(EXIT_FAILURE);
        }

		if ((pid = fork()) == -1) {
			perror("fork");
			exit(1);
		}
		else if (pid == 0) {
			if(dup2(fdd, 0) < 0){
                perror("dup2");
                exit(EXIT_FAILURE);
            }
			
			if (*(cmd + 1) != NULL) {
				if(dup2(fd[1], 1) < 0){
                    perror("dup2");
                    exit(EXIT_FAILURE);
                }
			}
			close(fd[0]);
			if(execvp((*cmd)[0], *cmd) < 0 ){
                    perror((*cmd)[0]);
                    exit(EXIT_FAILURE);
            }
		} else if(pid < 0){
            perror("error");
            exit(EXIT_FAILURE);
        }
		else {
			close(fd[1]);
			fdd = fd[0];
			cmd++;
		}
	}
	int i;
    for(i = 0; i < 4; i++)
        wait(NULL);
}

/*
 * Compute multi-pipeline based
 * on a command list.
 */
int
main(int argc, char *argv[])
{
	char *ls[] = {"ls", NULL};
	char *rev[] = {"rev", NULL};
	char *nl[] = {"nl", NULL};
	char *cat[] = {"cat", NULL};
	char **cmd[] = {cat, ls, cat, NULL};

	pipeline(cmd);
	return (0);
}