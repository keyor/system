#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>

int main(void)
{
	int input[2];

	pipe(input);

	pid_t pid = fork();

	if(pid > 0){
		char inbuffer[1024];
		close(input[0]);
		while(1)
		{
			fgets(inbuffer, 1024, stdin);	
			write(input[1], inbuffer, 1024);
		}
	}else if(pid == 0){
		close(input[1]);
		char outbuffer[1024];
		while(1)
		{
			read(input[0], outbuffer, 1024);
			printf("Message: %s", outbuffer);
		}
	}

	return 0;
}
