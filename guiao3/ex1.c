#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <stdio.h>

int main(int argc, char const *argv[]){
    int x = execl("/bin/ls","-l",NULL);
    printf("%d\n",x);
    return 0;
}
