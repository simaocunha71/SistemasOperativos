#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[]){
    pid_t filho;
    if((filho = fork()) == 0){ //filho
        printf("SOU O PROCESSO FILHO:\n");
        printf("-> ID próprio    : %d\n", getpid());
        printf("-> ID do seu pai : %d\n", getppid());
    }else{ //pai
        printf("SOU O PROCESSO PAI:\n");
        printf("-> ID próprio      : %d\n", getpid());                                                  
        printf("-> ID do seu pai   : %d\n", getppid());
        printf("-> ID do seu filho : %d\n", filho);
    }
    return 0;
}
