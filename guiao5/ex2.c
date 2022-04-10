#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h> 
#include <fcntl.h> 
#include <string.h>

#define SIZE 20

// Pai envia linha de texto para o filho
int main(int argc, char const *argv[]) {
    int pipe_fd[2];
    pid_t pid;
    char buffer[SIZE];
    char* str = "\"conteudo a passar\"!\n";

    if(pipe(pipe_fd) < 0) {
        perror("Erro a fazer pipe");
        exit(-1);
    }

    if((pid = fork()) == 0) {
        close(pipe_fd[1]);
        int bytes_read = 0;
        while((bytes_read = read(pipe_fd[0], buffer, SIZE)) > 0) {
            write(1, buffer, bytes_read);
        }
        close(pipe_fd[0]);
        _exit(0);
    } 
    else {
        close(pipe_fd[0]);
        write(pipe_fd[1], str, strlen(str) + 1);
        close(pipe_fd[1]);
        wait(NULL);
    }

    return 0;
}