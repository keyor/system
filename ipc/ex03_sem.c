#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <signal.h>

sem_t *sem = NULL;

void signal_handler(int sig)
{
	if(sig == SIGINT)
	{
		int val = 0;
		sem_getvalue(sem, &val);
		if(val < 0)
			printf("父进程，阻塞在这个信号量的进程有 %d个\n", val);
		sem_post(sem);
	}
}

int main(void)
{

	sem = sem_open("/demo", O_CREAT | O_RDWR, 0666, 5);

	if(sem == SEM_FAILED)
	{
		perror("sem_open 失败");
		exit(-1);
	}
	
	signal(SIGINT, signal_handler);

	pid_t pid = fork();
	
	if(pid > 0)
	{
		for(;;)
			pause();
	}else if(pid == 0)
	{	
		int i,val = -1;
		for(i = 0; i < 100; i++)
		{
			printf("子进程 %d 阻塞等待\n", getpid());
			sem_wait(sem);
			sem_getvalue(sem, &val);
			printf("子进程 %d 运行第 %d 次, val: %d\n",getpid(), i+1, val);
		}
	}



	return 0;
}
