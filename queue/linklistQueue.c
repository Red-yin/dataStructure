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
void cleanLinklistQueue(pLinklistQueue queue);

void destoryQueueNode(pQueueNode node)
{
	if(node != NULL){
		free(node);
	}
}

void cleanLinklistQueue(pLinklistQueue queue)
{
	if(1 == isEmptyInLinklistQueue(queue)){
		return ;
	}
	void *data = NULL;
	pthread_mutex_lock(&queue->mutex);
	pQueueNode tmp = queue->front;
	while(tmp != NULL){
		data = queue->front->data;
		if(queue->destoryData != NULL){
			queue->destoryData(data);
		}
		queue->front = queue->front->next;
		destoryQueueNode(tmp);
		queue->count--;
		//printf("delete left: %d\n", queue->count);
		tmp = queue->front;
	}
	if(queue->count != 0){
		printf("WARNING: queue count is not 0\n");
	}
	queue->count = 0;
	pthread_mutex_unlock(&queue->mutex);
}

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
	pthread_mutex_lock(&queue->mutex);
	if(queue->rear)
		queue->rear->next = tmp;
	queue->rear = tmp;
	queue->count++;
	if(queue->front == NULL)
		queue->front = tmp;
	pthread_mutex_unlock(&queue->mutex);
	pthread_cond_signal(&queue->cond);
	return 0;
}

void *deleteFromLinklistQueueBlock(pLinklistQueue queue)
{
	void *ret = NULL;
	pthread_mutex_lock(&queue->mutex);
	if(0 != isEmptyInLinklistQueue(queue)){
		printf("queue is empty, waiting...\n");
		pthread_cond_wait(&queue->cond, &queue->mutex);
	}
	ret = queue->front->data;
	pQueueNode tmp = queue->front;
	queue->front = queue->front->next;
	queue->count--;
	destoryQueueNode(tmp);
	pthread_mutex_unlock(&queue->mutex);
	return ret;
}

void *deleteFromLinklistQueue(pLinklistQueue queue)
{
	void *ret = NULL;
	if(1 == isEmptyInLinklistQueue(queue)){
		return NULL;
	}
	pthread_mutex_lock(&queue->mutex);
	ret = queue->front->data;
	pQueueNode tmp = queue->front;
	queue->front = queue->front->next;
	queue->count--;
	destoryQueueNode(tmp);
	pthread_mutex_unlock(&queue->mutex);
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

pLinklistQueue createLinklistQueue(int max, void (*destoryData)(void *data))
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
	queue->pop_block = deleteFromLinklistQueueBlock;
	queue->isEmpty = isEmptyInLinklistQueue;
	queue->isFull = isFullInLinklistQueue;
	queue->clean = cleanLinklistQueue;
	queue->destoryData = destoryData;
	pthread_mutex_init(&queue->mutex, NULL);
	return queue;
}

void destoryLinklistQueue(pLinklistQueue queue)
{
	if(queue){
		cleanLinklistQueue(queue);
		pthread_mutex_destroy(&queue->mutex);
		free(queue);
	}
}
