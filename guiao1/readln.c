#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <stdlib.h>
#include <stdio.h>

#define SizeBuf 1024

//Apenas lê um só caractere
int read_char (int fd, char* s){
    return read(fd, s, 1);
}

// Exercicio 3
ssize_t readln(int fd, char *line, size_t size){
	ssize_t loaded, char_readed = 0;

	while (char_readed < size && (loaded = read_char(fd,&line[char_readed]) > 0)){
		char_readed++;
		if (line[char_readed-1] == '\n')
			break;
	}
	return char_readed;
}



// Exercicio 4
int main(int argc, char const *argv[]){
    char buffer[SizeBuf]; 
    int bytes_read; int i = 0; int newline = 0;
    while ((bytes_read = readln (0, buffer, SizeBuf)) > 0 && newline == 0){
        char linha_para_numero[10] = "";
        if((buffer[bytes_read - 1])== '\n'){
            snprintf(linha_para_numero, 10, "%d:", i);
            write(1, linha_para_numero, sizeof(linha_para_numero));
            i++;
        }
 
        if(buffer[bytes_read - 1] != '\n')
            newline = 1;
        else
            newline = 0;
    }
    return 0;
}
