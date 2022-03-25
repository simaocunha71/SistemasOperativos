#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[]){
    pid_t pid;
    int to_exec, status;
    int i;

    for (i = 1; i < argc; i++){
        if((pid = fork()) == 0){
            to_exec = execlp(argv[i], argv[i], NULL);
            printf("%d\n",to_exec);
            _exit(to_exec);
        }
    }

    for(i = 1; i < argc; i++){
        pid_t terminated_pid = wait(&status);
        printf("Esperei pelo filho %d\n",terminated_pid);
    }
    return 0;
}
