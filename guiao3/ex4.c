#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//a corrigir
int main(int argc, char const *argv[]){
    int to_exec = execv("exercicio3",argv);
    return 0;
}
