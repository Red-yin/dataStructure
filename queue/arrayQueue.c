/*************************************************************************
	> c File Name: queueByArray.c
	> c Created Time: 2020年05月14日 星期四 15时15分13秒
 ************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include"arrayQueue.h"

int putInArrayQueue(pArrayQueue queue, int number, queueDataType *data);
int getArrayQueue(pArrayQueue queue, int number, queueDataType *buf);
int isEmptyArrayQueue(pArrayQueue queue);
int isFullArrayQueue(pArrayQueue queue);

int putInArrayQueue(pArrayQueue queue, int number, queueDataType *data)
{
	if(1 == isFullArrayQueue(queue)){
		printf("queue is full\n");
		return -1;
	}
	pthread_mutex_lock(&queue->mutex);
	if(queue->count + number > queue->max){
		printf("queue left space < number, put data failed\n");
		goto end;
	}
	int i = 0;
	for(; i < number; i++){
		queue->data[queue->rear] = data[i];
		queue->rear++;
		queue->count++;
		if(queue->rear == queue->max){
			queue->rear = 0;
		}
	}
end:
	pthread_mutex_unlock(&queue->mutex);
	return 0;
}

int getArrayQueue(pArrayQueue queue, int number, queueDataType *buf)
{
	if(1 == isEmptyArrayQueue(queue)){
		printf("queue is empty\n");
		return -1;
	}
	int i = 0;
	pthread_mutex_lock(&queue->mutex);
	for(; i < number; i++){
		buf[i] = queue->data[queue->front];
		queue->front++;
		queue->count--;
		if(queue->front == queue->max)
			queue->front = 0;
		if(queue->count == 0)
			break;
	}
	pthread_mutex_unlock(&queue->mutex);
	return i;
}
void cleanArrayQueue(pArrayQueue queue)
{
	if(0 != isEmptyArrayQueue(queue)){
		return;
	}
	pthread_mutex_lock(&queue->mutex);
	queue->front = queue->rear = 0;
	queue->count = 0;
	pthread_mutex_unlock(&queue->mutex);
}

int isEmptyArrayQueue(pArrayQueue queue)
{
	return (queue == NULL || queue->count == 0);
}

int isFullArrayQueue(pArrayQueue queue)
{
	return queue->count == queue->max;
}

pArrayQueue createArrayQueue(int max)
{
	if(max <= 0){
		printf("queue data size must > 0\n");
		return NULL;
	}
	pArrayQueue queue = (pArrayQueue)malloc(sizeof(arrayQueue));
	if(queue == NULL){
		printf("no memory when malloc queue\n");
		return NULL;
	}
	queue->max = max;
	queue->count = 0;
	queue->front = queue->rear = 0;
	queue->data = (queueDataType *)calloc(max, sizeof(queueDataType));
	if(queue->data == NULL){
		printf("no memory when malloc queue array\n");
		free(queue);
		return NULL;
	}
	pthread_mutex_init(&queue->mutex, NULL);
	queue->push = putInArrayQueue;
	queue->pop = getArrayQueue;
	queue->clean = cleanArrayQueue;
	queue->isEmpty = isEmptyArrayQueue;
	queue->isFull = isFullArrayQueue;
	return queue;
}

void destoryArrayQueue(pArrayQueue queue)
{
	if(queue){
		if(queue->data){
			free(queue->data);
		}
		pthread_mutex_destroy(&queue->mutex);
		free(queue);
	}
}
