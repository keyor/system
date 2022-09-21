#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <stdio.h>


int main(void)
{
	mqd_t mq = mq_open("/mail", O_RDONLY | O_NONBLOCK);

	if(mq == (mqd_t)-1)
		printf("打开消息队列失败\n");
	
	while(1)
	{
		char data[8192];
		ssize_t len = mq_receive(mq, data, 8192, NULL);
		
		if(len > 0)
			printf("接收到:%s\n", data);
	}

	return 0;
}
