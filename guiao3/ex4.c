#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int mysystem (char* command){

    pid_t pid;
    int return_exec;
    int status;
    int return_value;
    char* string;
    int i=0;

    char* exec_args[20];

    string = strtok(command, "");

    while (string != NULL){
        exec_args[i] = string;
        string = strtok(NULL," ");
        i++;
    }
    
    exec_args[i] = NULL;

    if ((pid = fork()) == 0) {
	  return_exec = execvp(exec_args[0], exec_args);
	  _exit(return_exec);
    } else {
        if(pid != -1) {
            pid_t terminated_pid = waitpid (pid, &status, 0);

            if(WIFEXITED(status)){

                return_value = WEXITSTATUS(status);

            } else {
                return_value = -1;
            }
        } else {
            return_value = -1;
        }
    }
    
     return return_value;
}

int main(int argc, char** argv){
    char comando1[] = "ls -l -a -h";
    char comando2[] = "sleep 10";
    char comando3[] = "ps";
    int ret;

    printf("a executar mysystem para %s/n",comando1);
    ret = mysystem(comando1);
    printf("Return value: %d/n/n",ret);

    printf("a executar mysystem para %s/n",comando2);
    ret = mysystem(comando2);
    printf("Return value: %d/n/n",ret);

    printf("a executar mysystem para %s/n",comando3);
    ret = mysystem(comando3);
    printf("Return value: %d/n/n",ret);
}