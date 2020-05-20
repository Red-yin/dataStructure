/*************************************************************************
	>c++ File Name: queueByLinklist.h
	>c++ Created Time: 2020年05月12日 星期二 16时19分27秒
 ************************************************************************/

typedef struct queueNode{
	void *data;
	struct queueNode *next;
}*pQueueNode;

typedef struct queueLinklist{
	int max;			//队列的容量
	unsigned int count;	//队列当前数据量
	pQueueNode front;	//队列数据头，从这里取出数据
	pQueueNode rear;	//队列数据尾，从这里加入数据
	int (*push)(struct queueLinklist *queue, void *data);
	void *(*pop)(struct queueLinklist *queue);
	int (*isEmpty)(struct queueLinklist *queue);
	int (*isFull)(struct queueLinklist *queue);
}*pQueueLinklist;

pQueueLinklist createQueueLinklist(int max);
void destoryQueueLinklist(pQueueLinklist *queue);
