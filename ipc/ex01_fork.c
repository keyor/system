#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

int main(void)
{
	FILE *fp = NULL;

	fp = fopen("/proc/sys/kernel/pid_max", "r+");
	if(!fp)
	{
		perror("打开文件失败");
		return -1;
	}

	pid_t pid = fork();

	if(pid == 0){
		printf("子进程, 进程 pid: %d\n", getpid());
		char buffer[10];
		fgets(buffer, 10, fp);
		printf("当前Linux内核进程号最大值: %s", buffer);
	}else if(pid > 0){
		printf("父进程, 进程 pid: %d\n", getpid());
	}else{
		perror("出错");
		printf("%s\n", strerror(errno));
	}

	return 0;
}
