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
}*pQueueLinklist;

int addToQueueLinklist(pQueueLinklist queue, void *data);
void *deleteFromQueueLinklist(pQueueLinklist queue);
int isEmptyInQueueLinklist(pQueueLinklist queue);
int isFullInQueueLinklist(pQueueLinklist queue);
pQueueLinklist createQueueLinklist(int max);
