#include <stdio.h>
#include <sys/types.h>
#include <unistd.h> 
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <wait.h>

//  0     1        2          3        4          5        6      7   ...  
//redir [-i] [fich_entrada] [-o] [fich_saida] [comando] [arg1] [arg2] ...

int main(int argc, char const *argv[]) {
    int status;
    if(argc < 6) 
        exit(1);

    int input_fd;
    int output_fd;

    if(strcmp(argv[1], "-i") == 0){
        printf("Redirecionar input para 0...\n");
        input_fd = open(argv[2], O_RDONLY);
        dup2(input_fd, 0);
        close(input_fd);
    }
    else 
    	_exit(1);

    if(strcmp(argv[3], "-o") == 0){
        printf("Redirecionar output para 1...\n");
        output_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        dup2(output_fd,1);
        close(output_fd);
    } 
    else
    	_exit(1);

    argv[argc] = NULL;
    if(fork() == 0) {
        execlp(argv[5], *(argv+5), NULL);
        _exit(1);
    } 
    else{
    	wait(&status);
        printf("\n[PAI] Estou à espera que o filho termine\n");
    }
    
    return 0;
}