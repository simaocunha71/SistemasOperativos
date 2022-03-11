#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[]){
    printf("Id do processo     [PID]  = %d\n", getpid());
    printf("Id do processo pai [PPID] = %d\n",getppid());
    return 0;
}
