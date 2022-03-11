#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Escrever uma mensagem para cada processo filho.
    Se escrevermos mais do que uma mensagem, vai aparecer mensagens baralhadas com as de outros processos, tendo em conta a concorrência de processos
*/

int main(int argc, char const *argv[]){

    int status, i;
    pid_t pid,t;

    //Cria todos os filhos em primeiro lugar
    for (i = 0; i < 10; i++){
        t = fork();
        if (t == 0) {
            printf("Filho #%d com PID %d\n", i + 1, getpid());
            _exit(i + 1);
        }
    }
    
    //Pai só executa depois dos filhos acabarem
    for (i = 0; i < 10; i++){
        pid = wait(&status);
        printf("Sou o pai, tenho um filho com PID %d e com código %d\n", pid, WEXITSTATUS(status));
    }
    
    return 0;
}