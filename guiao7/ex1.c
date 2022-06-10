#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int count, t = 0;

void ctrl_c_handler(int signal){
    count++;
    printf("\nPassaram %ds desde o inicio do programa\n",t);
}

void ctrl_slash_handler(int signal){
   printf("\nCtrl + c foi pressionado %d vezes\n",count); 
   exit(0);
}

void count_time_handler(int signal){
    alarm(1);
    t++;
}

int main(){
    signal(SIGINT,ctrl_c_handler);
    signal(SIGQUIT,ctrl_slash_handler);
    signal(SIGALRM,count_time_handler);

    alarm(1);
    while(1){
        pause();
    }

    return 0;
}