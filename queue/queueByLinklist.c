/*************************************************************************
	> c File Name: queueByLinklist.c
	> c Created Time: 2020年05月12日 星期二 16时19分18秒
 ************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include"queueByLinklist.h"

int addToQueueLinklist(pQueueLinklist queue, void *data)
{
	if(1 == isFullInQueueLinklist(queue)){
		printf("this queue is full already\n");
		return -1;
	}
	pQueueNode tmp = (pQueueNode)malloc(sizeof(struct queueNode));
	if(tmp == NULL){
		printf("no memory when add data in queue\n");
		return -1;
	}
	tmp->next = NULL;
	tmp->data = data;
	if(queue->rear)
		queue->rear->next = tmp;
	queue->rear = tmp;
	queue->count++;
	if(queue->front == NULL)
		queue->front = tmp;
	return 0;
}

void *deleteFromQueueLinklist(pQueueLinklist queue)
{
	void *ret = NULL;
	if(1 == isEmptyInQueueLinklist(queue)){
		printf("this queue is empty\n");
		return NULL;
	}
	ret = queue->front->data;
	pQueueNode tmp = queue->front;
	queue->front = queue->front->next;
	queue->count--;
	free(tmp);
	return ret;
}

int isEmptyInQueueLinklist(pQueueLinklist queue)
{
	return (queue == NULL || queue->count == 0);
}

int isFullInQueueLinklist(pQueueLinklist queue)
{
	if(queue == NULL){
		printf("queue is NULL\n");
		return -1;
	}
	return queue->count == queue->max;
}

pQueueLinklist createQueueLinklist(int max)
{
	if(max <= 0){
		printf("max num must > 0\n");
		return NULL;
	}
	pQueueLinklist queue = (pQueueLinklist)malloc(sizeof(struct queueLinklist));
	if(queue == NULL){
		printf("no memory when create queue\n");
		return NULL;
	}
	queue->max = max;
	queue->count = 0;
	queue->front = queue->rear = NULL;
	return queue;
}

int main()
{
	pQueueLinklist q = createQueueLinklist(100);
	int i = 0;
	for(;i < 200; i++){
		int *d = (int *)malloc(sizeof(int));
		*d = i;
		if(addToQueueLinklist(q, d) < 0){
			free(d);
		}
	}
	for(i = 0;i < 200; i++){
		void *d = NULL;
		if((d = deleteFromQueueLinklist(q)) != NULL){
			printf("data is %d\n", *(int *)d);
			free(d);
		}
	}
	return 0;
	
}