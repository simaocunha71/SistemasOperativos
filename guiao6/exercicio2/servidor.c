#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>

#define SIZE 1024

int main(){
    char buffer[SIZE];

    int fd_file = open("log.txt", O_CREAT | O_APPEND | O_WRONLY, 0666); 
    int fd_fifo, bytes_read;

    while(1){
        if (mkfifo("fifo", 0660) == -1)
            perror("Erro fifo");
        fd_fifo = open("fifo", O_RDONLY);
        while( (bytes_read = read(fd_fifo,buffer,SIZE)) > 0 ) //le as mensagens dos clientes e mete no ficheiro
            write(fd_file,buffer,bytes_read);
    }
    close(fd_file);
    close(fd_fifo);

	return 0;
}