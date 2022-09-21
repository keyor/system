## 1.进程的创建及处理
	fork()函数调用返回两次，在父进程返回的是子进程的pid，在子进程返回的是0,fork()调用失败则返回-1，并设置errno。
	fork()复制当前进程，在内核进程表中创建一个新的进程表项，新进程和原进程的堆指针、栈指针和标志寄存器相同。
	子进程会复制符进程的数据(堆数据、栈数据和静态数据),数据的复制采用写时复制
	父进程打开的文件描述符默认在子进程中也是打开的，且文件描述符的引用技术+1。
	
## 2.进程信号的处理
	int status = 0;
	pid = waitpid(-1, &status, WNOHANG | WUNTRACED);
	设置为-1等待任何子进程，status存放子进程退出的状态码，
	WNOHANG 为如果没有子进程退出函数立即返回0而不是阻塞等待，WUNTRACED如果子进程进入暂停状态，则马上返回
	WIFEXITED(status) : 如果子进程正常结束，则返回真

## 3.有名信号量
	有名信号量和无名信号量两种，不必由内核来维护,另外可能由与文件系统对应路径名字来标识
	信号量可执行的操作：等待/挂起
	有名信号量存放在 /dev/shm/目录下
	sem_t *sem = sem_open("/demo", O_CREAT | O_RDWR, 0666, 0);  // 0为信号量初值, 0666是它的权限位
	sem_close(sem_t *sem); //关闭一个信号量，但在内核中并没有把它删除
	sem_unlink(const char *name); //从系统中删除
	sem_getvalue(sem_t *sem, int *val); 获取信号量的当前值，如果为0，表示上锁, 则表示阻塞；如果为负数，表示阻塞在这个信号量上的进程或线程数目

## 4.无名管道
	int fd[2];
	pipe(fd);  // fd[0]读取, fd[1]写入
	对于管道来说，必须有读出者，否则写入是没意义的；当一个管道最后一次关闭时，则管道中的数据将丢失

## 5.有名管道


## 6.消息队列
	消息队列的消息具有随内核的持久性，也就是说，往队列中放入一条消息，哪怕进程关闭，其他进程之后也能从队列中读入。
#### 消息队列三属性
+ 一个无符号整数优先级
+ 消息的数据长度
+ 消息本身
#### 消息队列常用函数
	oflags: O_CREAT | O_EXCL 排他性创建消息队列， O_NONBLOCK非阻塞模式打开，
	mqd_t mq_open(const char* name, int oflags, mode_t mode, struct mq_attr *attr); 
		//创建或打开一个消息队列, 创建的话，如不指定消息队列mq_maxmsg 和 mq_msgsize,则创建后不能再修改
	mq_send(mqd_t, const char* buf, int buflen, int priv); //向队列写入一条消息, priv为优先级
	mq_receive(mqd_t, char* buf, size_t msg_len, uint* priv); 
		//从队列读取一条消息,buf的长度msg_len必须要大于消息队列单个元素mq_msgsize的大小，如果priv不为NULL,则接收到的消息的优先级被复制到这个值上。
	mq_close(); //关闭进程之前打开的一个消息队列
	mq_unlink(); //删除一个消息队列名并当所有进程关闭队列时对队列进行标记以便删除

