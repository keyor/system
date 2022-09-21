#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
	mqd_t mq = mq_open("/mail", O_WRONLY | O_NONBLOCK);

	if(mq == (mqd_t)-1)
		printf("向邮箱发送失败\n");
	
	while(1)
	{
		char data[1024];
		memset(data, 0, 1024);
		fgets(data, 1024, stdin);
		mq_send(mq, data, 1024, 0); //优先级最低，0
		printf("向消息队列发送: %s\n", data);
	}

	return 0;
}
