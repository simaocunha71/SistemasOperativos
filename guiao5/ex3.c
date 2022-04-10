#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h> 
#include <fcntl.h> 

#define SIZE 20

int main(int argc, char const *argv[]) {
    int pipe_fd[2], bytes_read;
    char buffer[SIZE];

    if(pipe(pipe_fd) < 0) {
        perror("Erro a fazer pipe");
        exit(-1);
    }

    pid_t pid;
    int file = open("linhas.txt", O_RDONLY, 0660);

    if((pid = fork()) == 0) {
        close(pipe_fd[1]);
        dup2(pipe_fd[0], 0);
        close(pipe_fd[0]);
        execlp("wc","wc",NULL);
    } 
    else {
        close(pipe_fd[0]);
        
        for (int i = 0; i < 4; i++){
            while((bytes_read = read(file, buffer, SIZE)) > 0){
                write(pipe_fd[1], buffer, bytes_read);
            }
                
        }
        close(pipe_fd[1]);
        wait(NULL);
    }
    close(file);
    return 0;
}