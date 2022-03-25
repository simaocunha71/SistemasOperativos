#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[]){
    pid_t pid;
    int status;

    pid = fork();
    if (pid == 0){
        printf("[Filho] Vou executar\n\n");
        execl("/bin/ls", "/bin/ls", "-l", NULL);
        _exit(0);
    }
    else{
        wait(&status);
        if (WIFEXITED(status))
            printf("\n[PAI] Esperei pelo filho e acabei\n");
        else
            printf("\n[PAI] Aconteceu algum erro com o filho\n");
    }
}
