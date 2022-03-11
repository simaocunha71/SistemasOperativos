#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[]){
    pid_t t, pid_terminado;
    int id_process, status;

    for(id_process = 0; id_process < 10; id_process++){
       
        if((t = fork()) == 0){ //filho
            printf("\n***********************PROCESSO #%d *************************", id_process + 1);
            printf("\nFILHO:\n");
            printf("ID próprio: %d\n", getpid());
            printf("ID do pai: %d\n", getppid());
            _exit(id_process+1);
        }
        else{ //pai
            pid_terminado = wait(&status);
            printf("\nPAI:\n");
            printf("ID pŕoprio: %d\n", getpid());
            printf("ID do filho: %d, como codigo de erro \"%d\"\n", pid_terminado, WEXITSTATUS(status));
        }
    }

    return 0;
}
