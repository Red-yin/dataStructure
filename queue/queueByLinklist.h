/*************************************************************************
	>c++ File Name: queueByLinklist.h
	>c++ Created Time: 2020年05月12日 星期二 16时19分27秒
 ************************************************************************/

typedef struct queueNode{
	void *data;
	struct queueNode *next;
}*pQueueNode;

typedef struct queueLinklist{
	int max;
	unsigned int count;
	pQueueNode front;
	pQueueNode rear;
}*pQueueLinklist;

int addToQueueLinklist(pQueueLinklist queue, void *data);
void *deleteFromQueueLinklist(pQueueLinklist queue);
int isEmptyInQueueLinklist(pQueueLinklist queue);
int isFullInQueueLinklist(pQueueLinklist queue);
pQueueLinklist createQueueLinklist(int max);
