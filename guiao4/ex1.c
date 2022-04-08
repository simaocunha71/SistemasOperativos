#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char const *argv[]){

    int res = 0;
    int i = 0;
    char buffer;
    char line[1024];

    int fileIN  = open("/etc/passwd", O_RDONLY);
    int fileOUT = open("saida.txt"  , O_WRONLY | O_CREAT | O_APPEND ,0660);
    int fileERR = open("erros.txt"  , O_WRONLY | O_CREAT | O_APPEND ,0660);
    
    res = dup2(fileIN,0);
    printf("fileIN (old, new) = %d, %d\n", fileIN, res);

    res = dup2(fileOUT,0);
    printf("fileOUT (old, new) = %d, %d\n", fileOUT, res);

    res = dup2(fileERR,0);
    printf("fileERR (old, new) = %d, %d\n", fileERR, res);

    close(fileIN);
    close(fileOUT);
    close(fileERR);
    
    int read_res;
    setbuf(stdout,NULL);

	while((read_res = read (0, &buffer, 1)) > 0){
		line[i] = buffer;
		i++;
		if (buffer == '\n'){
			write(1,line,i);
			write(2,line,i);
			printf("[DEBUG] Escrevi linha\n"); 
			fflush(stdout); 
			i = 0;
		}
	}
    return 0;
}
