#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

void signal_hander(int sig)
{	
	int status = 0;
	if(sig == SIGINT)
		printf("父进程捕获到SIGINT信号\n");
	if(sig == SIGCHLD)
	{
		printf("子进程终止信号\n");
		pid_t pid = waitpid(-1, &status, WNOHANG | WUNTRACED);
		if(WIFEXITED(status))
			printf("子进程正常结束, pid: %d\n", pid);
		else
			printf("子进程异常终止\n");
	}
}

int main(void)
{	
	signal(SIGINT, signal_hander);
	signal(SIGCHLD, signal_hander);
	
	pid_t pid = fork();

	if(pid > 0)
	{	
		int status;
		for(;;)
			pause();
	}else if(pid == 0){
		printf("一次就好\n");	
	}

	return 0;
}
