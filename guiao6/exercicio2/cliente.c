#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define SIZE 1024

int main(){
    char buffer[SIZE];
    int bytes_read, fd = open("fifo", O_WRONLY);

    while( (bytes_read = read(0,buffer,SIZE)) > 0){
        write(fd,buffer,bytes_read); //Le do stdin e mete no fifo
    }

	return 0;
}