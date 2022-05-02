#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h> 
#include <fcntl.h> 
#include <string.h>
#include <sys/stat.h>

int main(int argc, char const *argv[]){
    if(mkfifo("fifo", 0666) == -1)
        perror("Error a criar o fifo");
    return 0;
}
