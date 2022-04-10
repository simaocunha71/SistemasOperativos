#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h> 
#include <fcntl.h> 

/*
************Template*****************

void func(){
    int filesDescriptors[2];
    pipes(filesDescriptors);

    if ((pid = fork()) == 0){ //CONSUMIDOR
        close(filesDescriptors[1]);
        read(filesDescriptors[0], ..., ...);
        close(fileDescriptors[0]);
        _exit(...);
    }
    else{ //PRODUTOR
        close(filesDescriptors[0]);
        write(filesDescriptors[1], ..., ...);
        close(filesDescriptors[1]);
        wait(...);
    }
}

*/


/**
 * @brief Pai envia uma linha de texto para o filho
 * @return int 0 se sucesso, != 0 caso contrário
 */
int pai2filho(){
	int p[2];
	char line[] = "conteudo a passar";
	char buffer[20];
	int res,status;

	if (pipe(p) == -1){
		perror("Erro a criar um pipe");
		return -1;
	}

	switch (fork()){
		case -1:
			perror("Erro a efetuar fork");
			return -1;
		case 0: //Processo-filho (Lê)
			close(p[1]); //Fecha extremo de escrita no inicio
			res = read(p[0], &buffer, sizeof(buffer));
			printf("[FILHO]: li \"%s\" do pipe (%d bytes)\n", buffer, res);
			close(p[0]); //Fecha extremo de leitura depois de ler do buffer
			_exit(0);
		default: //Processo-pai (Escreve)
			close(p[0]); //Fecha extremo de leitura no inicio
			//sleep(5);
			res = write(p[1], &line, sizeof(line));
			printf("[PAI]: escrevi \"%s\" do pipe (%d bytes)\n", line, res);
			close(p[1]); //Fecha extremo de escrita depois de escrever no buffer
			wait(&status);
	}
	return 0;
}

/**
 * @brief Filho envia uma linha de texto para o pai
 * @return int 0 se sucesso, != 0 caso contrário
 */
int filho2pai(){
	int p[2];
	char line[] = "conteudo a passar";
	char buffer[20];
	int res,status;

	if (pipe(p) == -1){
		perror("Erro a criar um pipe");
		return -1;
	}

	switch (fork()){
		case -1:
			perror("Erro a efetuar fork");
			return -1;
		case 0: //Processo-filho (Escreve)
			close(p[0]);// Fecho extremo de leitura
			res = write(p[1], &line, sizeof(line));
			printf("[FILHO]: escrevi \"%s\" do pipe (%d bytes)\n", line, res);
			close(p[1]); //Fecha extremo de escrita depois de escrever no buffer
			_exit(0);
		default: //Processo-pai (Lê)
			close(p[1]);//Fecha extremo de escrita no inicio
			//sleep(5);
			wait(&status);
			res = read(p[0], &buffer, sizeof(buffer));
			printf("[PAI]: li \"%s\" do pipe (%d bytes)\n", buffer, res);
			close(p[0]);//Fecha extremo de leitura depois de ler do buffer

	}
	return 0;
}


int main(int argc, char const *argv[]){
	pai2filho();
	printf("------------\n");
	//filho2pai();

    return 0;
}
