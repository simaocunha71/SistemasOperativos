#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h> 
#include <fcntl.h> 

/*Simular o funcionamento de: 
    $ ls /etc | wc -l
*/

int main(int argc, char const *argv[]) {
    int pipe_fd[2];

    if(pipe(pipe_fd) < 0) {
        perror("Erro a fazer pipe");
        exit(-1);
    }

    if(fork() == 0) {
        close(pipe_fd[0]);
        dup2(pipe_fd[1], 1);
        close(pipe_fd[1]);
        execlp("ls", "ls", "/etc", NULL);
        _exit(1);
    }
    else
        wait(NULL);
    
    close(pipe_fd[1]);

    if (fork() == 0) {
        dup2(pipe_fd[0], 0);
        close(pipe_fd[0]);
        execlp("wc", "wc", "-l", NULL);
        _exit(1);
    }
    else
        wait(NULL);

    close(pipe_fd[0]);
    return 0;
}
