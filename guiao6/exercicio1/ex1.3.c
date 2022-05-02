#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h> 
#include <fcntl.h> 
#include <string.h>
#include <sys/stat.h>

#define SIZE 1024
int main(int argc, char const *argv[]){
    if(mkfifo("fifo", 0666) == -1)
        perror("Error a criar o fifo");
    char buffer[SIZE];
    int bytes_read;
    int fd = open("fifo", O_WRONLY);
    if (fd == -1)
        perror("Erro file");

    while((bytes_read = read(fd,buffer,SIZE)) > 0){
        if (write(1,buffer,bytes_read) == -1)
            perror("Erro a escrever");
    

    close(fd);
    //unlink("fifo");
    return 0;
}
