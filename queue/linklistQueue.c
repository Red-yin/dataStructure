/*************************************************************************
	> c File Name: queueByLinklist.c
	> c Created Time: 2020年05月12日 星期二 16时19分18秒
 ************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include"linklistQueue.h"

int addToLinklistQueue(pLinklistQueue queue, void *data);
void *deleteFromLinklistQueue(pLinklistQueue queue);
int isEmptyInLinklistQueue(pLinklistQueue queue);
int isFullInLinklistQueue(pLinklistQueue queue);

int addToLinklistQueue(pLinklistQueue queue, void *data)
{
	if(1 == isFullInLinklistQueue(queue)){
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

void *deleteFromLinklistQueue(pLinklistQueue queue)
{
	void *ret = NULL;
	if(1 == isEmptyInLinklistQueue(queue)){
		return NULL;
	}
	ret = queue->front->data;
	pQueueNode tmp = queue->front;
	queue->front = queue->front->next;
	queue->count--;
	free(tmp);
	return ret;
}

int isEmptyInLinklistQueue(pLinklistQueue queue)
{
	return (queue == NULL || queue->count == 0);
}

int isFullInLinklistQueue(pLinklistQueue queue)
{
	if(queue == NULL){
		printf("queue is NULL\n");
		return -1;
	}
	return queue->count == queue->max;
}

pLinklistQueue createLinklistQueue(int max)
{
	/*
	if(max <= 0){
		printf("max num must > 0\n");
		return NULL;
	}
	*/
	pLinklistQueue queue = (pLinklistQueue)malloc(sizeof(struct linklistQueue));
	if(queue == NULL){
		printf("no memory when create queue\n");
		return NULL;
	}
	queue->max = max;
	queue->count = 0;
	queue->front = queue->rear = NULL;
	queue->push = addToLinklistQueue;
	queue->pop = deleteFromLinklistQueue;
	queue->isEmpty = isEmptyInLinklistQueue;
	queue->isFull = isFullInLinklistQueue;
	return queue;
}

void destoryLinklistQueue(pLinklistQueue *queue)
{
	if(queue)
		if(*queue){
			free(*queue);
			*queue = NULL;
		}
}
