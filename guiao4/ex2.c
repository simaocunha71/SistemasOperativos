#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <wait.h>

int main (int argc, char* argv[]){
	int status,fork_ret;
	char buffer;
	char line[1024];
	int i = 0;
	
	int input_fd  = open("/etc/passwd", O_RDONLY);
	int output_fd = open("saida.txt", O_CREAT | O_TRUNC | O_WRONLY, 06660);
	int error_fd  = open("erros.txt", O_CREAT | O_TRUNC | O_WRONLY, 06660);

	dup2(input_fd, 0);	//stdin  = 0
	dup2(output_fd, 1); //stdout = 1
	dup2(error_fd, 2);	//stderr = 2

	close(input_fd);
	close(output_fd);
	close(error_fd);

	fork_ret = fork();

	if(fork_ret== 0) { //Processo-filho
		int read_res;
		while((read_res = read(0, &buffer, 1)) != 0){
			line[i] = buffer;
			i++;
			if (buffer == '\n'){
				write(1,line,i);
				write(2,line,i);
				printf("Escrevi linha\n");
				fflush(stdout); //acaba o buffering
				i = 0;
			}
		}
		_exit(0);	
	}
	else { //Processo-pai
		wait(&status);
		if (WIFEXITED(status))
			printf("\nO filho retornou %d\n", WEXITSTATUS(status));
		else
			printf("\nO filho nao terminou\n");
	}


	return 0;
}