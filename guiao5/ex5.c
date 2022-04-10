#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h> 
#include <fcntl.h> 

/*
Simular o funcionamento de:
    $ grep -v ˆ# /etc/passwd | cut -f7 -d: | uniq | wc -l
    14
*/

/**
 * @brief Redireciona o fd para o std
 * @param fd File descriptor de um ficheiro
 * @param std 0 (STDIN), 1 (STDOUT) ou 2 (STDERR)
 */
void redirection(int fd[], int std){
    dup2(fd[std], std);
    close(fd[0]);
    close(fd[1]);
}

int main(int argc, char const *argv[]){
    int pipe_files[2];

    pipe(pipe_files);

    if(fork() == 0){
        redirection(pipe_files, 1);
        pipe(pipe_files);
        if(fork() == 0){
            redirection(pipe_files, 1);
            pipe(pipe_files);     
            if(fork() == 0){
                redirection(pipe_files, 1);
                execlp("grep", "grep", "-v", "^#", "/etc/passwd", NULL);
            }
            else{
                redirection(pipe_files,0);  
                execlp("cut", "cut", "-f7", "-d:", NULL);
                _exit(1);
            }   
        }           
        else{
            redirection(pipe_files,0);  
            execlp("uniq", "uniq", NULL);
            _exit(1);
        }
    }
    else{
        redirection(pipe_files,0);  
        execlp("wc", "wc", "-l", NULL);
        _exit(1);
    }
            
    return 0;
}
