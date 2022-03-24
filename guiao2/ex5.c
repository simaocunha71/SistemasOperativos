#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */

#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

 

#define NCols 50

#define NLin 5

 

int checkNumber (int x, int v[], int N){

    int i, flag = 0;

    int r = 0;

    for (i = 0; i < N && flag == 0; i++){

        if (v[i] == x){

            r = 1;

            flag = 1;

        }

    }

    return r;

}

 

void generateMatrix(int mat[NLin][NCols]){

    int i, j;

    for (i = 0; i < NLin; i++){

        for (j = 0; j < NCols; j++){

            mat[i][j] = (i+j) * i;

        }

    }

}

 

void printMatrix(int x, int mat[NLin][NCols]){

    int i, j;

    for (i = 0; i < NLin; i++){

        for (j = 0; j < NCols; j++){

            if(mat[i][j] == x){

                printf("\x1b[93m%d\033[0m ",mat[i][j]);

            }else{

                printf("%d ",mat[i][j]);

            }

           

        }

        printf("\n");

    }

}

 

int main(int argc, char const *argv[])

{

    int mat[NLin][NCols];

    generateMatrix(mat);

    int i, status, found = 0;

    pid_t pid;

    for(i = 0 ; i < NLin; i++){

        if((pid = fork() == 0)){

            found = checkNumber(atoi(argv[1]), mat[i], NCols);

            _exit(found);

        }

 

    }

 

    for(i = 0 ; i < NLin; i++){
        pid_t p = waitpid(,&status,0); //TODO
    }

    printMatrix(atoi(argv[1]),mat);
    return 0;

}
