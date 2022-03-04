#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <stdlib.h>
#include <stdio.h>

#define SizeBuf 1024

int main(int argc, char const *argv[]){
    int file1, file2, loaded;
    char buf[SizeBuf];

    if (argc < 2){
        perror("Não existem argumentos suficientes");
        exit(-1);
    }

    file1 = open(argv[1], O_WRONLY|O_CREAT|O_TRUNC, 0660);
    if(file1 < 0){
        perror("Erro ao abrir um dos ficheiro");
        exit(-1);
    }
    file2 = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC, 0660);
    if(file1 < 0){
        perror("Erro ao abrir um dos ficheiro");
        exit(-1);
    }

    while((loaded = read(file1,buf,SizeBuf) > 0))
        write(file2, buf, loaded);

    close(file1);
    close(file2);
    exit(0);

    return 0;
}