#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <stdio.h>

int main(void)
{
	mqd_t mq = mq_open("/mail", O_RDONLY);

	if(mq == (mqd_t)-1)
		printf("消息队列打开失败\n");
		
	struct mq_attr attr;


	int ret = 0;
	ret = mq_getattr(mq, &attr);
	if(ret == -1)
		printf("获取消息队列属性失败\n");
	
	printf("消息队列最大长度: %d\n", attr.mq_maxmsg);
	printf("消息队列单条最大大小: %d\n", attr.mq_msgsize);
	printf("消息队列元素的位置:%d\n", attr.mq_curmsgs);

	return 0;
}
