#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <stdlib.h>
#include <stdio.h>

#define SizeBuf 1024

int main(int argc, char const *argv[]){
    int loaded;
    char buf[SizeBuf];

    if (argc < 1){
        perror("Não existem argumentos suficientes");
        exit(-1);
    }

    while((loaded = read(1,buf,SizeBuf) > 0))
        write(2, buf, loaded);

    exit(0);

    return 0;
}