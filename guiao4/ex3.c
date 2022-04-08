#include <stdio.h>
#include <sys/types.h>
#include <unistd.h> 
#include <fcntl.h> 


int main (int argc, char* argv[]){
	int input_fd = open("/etc/passwd", O_RDONLY);
	int output_fd = open("saida.txt", O_CREAT | O_TRUNC | O_WRONLY, 06660);
	int error_fd = open("erros.txt", O_CREAT | O_TRUNC | O_WRONLY, 06660);

	dup2(input_fd, 0);  //stdin  = 0
	dup2(output_fd, 1); //stdout = 1
	dup2(error_fd, 2);  //stderr = 2

	close(input_fd);
	close(output_fd);
	close(error_fd);

	execlp("wc", "wc", NULL);

	return 0;
}