/*************************************************************************
	>c++ File Name: queueByLinklist.h
	>c++ Created Time: 2020年05月12日 星期二 16时19分27秒
 ************************************************************************/

#include <pthread.h>
typedef struct queueNode{
	void *data;
	struct queueNode *next;
}*pQueueNode;

typedef struct linklistQueue{
	int max;			//队列的容量
	unsigned int count;	//队列当前数据量
	pQueueNode front;	//队列数据头，从这里取出数据
	pQueueNode rear;	//队列数据尾，从这里加入数据
	pthread_mutex_t mutex;
	int (*push)(struct linklistQueue *queue, void *data);
	void *(*pop)(struct linklistQueue *queue);
	int (*isEmpty)(struct linklistQueue *queue);
	int (*isFull)(struct linklistQueue *queue);
	void (*clean)(struct linklistQueue *queue);
	void (*destoryData)(void *data);
}*pLinklistQueue;

pLinklistQueue createLinklistQueue(int max, void (*destoryData)(void *data));
void destoryLinklistQueue(pLinklistQueue queue);
