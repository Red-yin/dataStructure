/*************************************************************************
	>c++ File Name: queueByArray.h
	>c++ Created Time: 2020年05月12日 星期二 17时30分51秒
 ************************************************************************/

typedef struct queueArray{
	int max;
	unsigned int front;
	unsigned int rear;
	char *data;
}*pQueueArray;

int addToQueueArray(pQueueArray queue, char *data);
char *deleteFromQueueArray(pQueueArray queue);
