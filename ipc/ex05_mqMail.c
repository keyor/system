#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <stdio.h>

int main(void)
{	
	mqd_t mq = mq_open("/mail", O_CREAT | O_EXCL | O_NONBLOCK | O_RDWR, 0666, NULL); //默认属性为NULL
	if(mq == (mqd_t)-1)
		printf("创建邮箱失败\n");
	else
		printf("创建邮箱mail成功\n");
	
	// 获取消息队列默认属性
	struct mq_attr attr;
	int ret = 0;
	
	ret = mq_getattr(mq, &attr);
	if(ret == -1)
		printf("获取消息队列默认属性失败\n");
	printf("消息队列最大消息总数: %d\n", attr.mq_maxmsg);
	printf("消息队列消息体的大小: %d\n", attr.mq_msgsize);
	printf("消息队列中当前消息数目：%d\n", attr.mq_curmsgs);
	
	struct mq_attr new_attr;
	new_attr.mq_maxmsg = 100;
	new_attr.mq_msgsize = 1024;
	
	// mq_maxmsg 和 mq_msgsize 创建后就无法修改
	ret = mq_setattr(mq, &new_attr, NULL); //如果不为NULL,则应传入 struct mq_attr结构来获取旧的属性值
	if(ret == -1)
		printf("设置消息队列属性失败\n");
	
	for(;;)
		pause();

	mq_close(mq);

	mq_unlink("/mail");
	
	return 0;
}
