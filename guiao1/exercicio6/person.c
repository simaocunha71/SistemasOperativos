#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include "person.h"

int main(int argc, char* argv[]){
    clock_t t;
    char id[20] = "";

    t = clock();
    if(strcmp(argv[1], "-i") == 0){
        int res = new_person(argv[2], atoi(argv[3]));
        snprintf(id, 20, "registo: %d\n", res);
        write(1, id, sizeof(id));
    }

    if(strcmp(argv[1], "-u") == 0){
        int res = person_change_age(argv[2], atoi(argv[3]));
    }

    t = clock() - t;
    printf("Demorou %ld ms\n", t);
    return 0;
}

int new_person(char * name, int age){
    Person p;
    strcpy(p.name, name);
    p.age = age;

    int fd_open = open(FILENAME, O_CREAT | O_APPEND | O_WRONLY);
    int res = write(fd_open, &p, sizeof(Person));

    //Depois de alterar o nome, coloca o apontador para o local onde estava antes do ciclo while
    int seek_res = lseek(fd_open, -sizeof(Person), SEEK_CUR); 

    close(fd_open);
    
    return seek_res;
}

int person_change_age (char * name, int age){
    Person person;
    int update = 0;
    int fd_open = open(FILENAME, O_RDWR);
    
    while ((read(fd_open, &person, sizeof(Person)) > 0) && update == 0){
        if (strcmp(person.name, name) == 0){
            person.age = age;

            //Depois de alterar o nome, coloca o apontador para o local onde estava antes do ciclo while
            int seek_res = lseek(fd_open, -sizeof(Person), SEEK_CUR); 
            
            update = 1;
        }
    }
    if(!update){
        perror("didn't update");
        close(fd_open);
        return -1;
    }
    
    close(fd_open);
    return update;
}