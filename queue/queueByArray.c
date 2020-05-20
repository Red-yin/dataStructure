/*************************************************************************
	> c File Name: queueByArray.c
	> c Created Time: 2020年05月14日 星期四 15时15分13秒
 ************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include"queueByArray.h"

int putInQueueArray(pQueueArray queue, int number, queueDataType *data);
int getQueueArray(pQueueArray queue, int number, queueDataType *buf);
int isEmptyQueueArray(pQueueArray queue);
int isFullQueueArray(pQueueArray queue);

int putInQueueArray(pQueueArray queue, int number, queueDataType *data)
{
	if(1 == isFullQueueArray(queue)){
		printf("queue is full\n");
		return -1;
	}
	if(queue->count + number > queue->max){
		printf("queue left space < number, put data failed\n");
		return -1;
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
	return 0;
}

int getQueueArray(pQueueArray queue, int number, queueDataType *buf)
{
	if(1 == isEmptyQueueArray(queue)){
		printf("queue is empty\n");
		return -1;
	}
	int i = 0;
	for(; i < number; i++){
		buf[i] = queue->data[queue->front];
		queue->front++;
		queue->count--;
		if(queue->front == queue->max)
			queue->front = 0;
		if(queue->count == 0)
			break;
	}
	return i;
}

int isEmptyQueueArray(pQueueArray queue)
{
	return queue->count == 0;
}

int isFullQueueArray(pQueueArray queue)
{
	return queue->count == queue->max;
}

pQueueArray createQueueArray(int max)
{
	if(max <= 0){
		printf("queue data size must > 0\n");
		return NULL;
	}
	pQueueArray queue = (pQueueArray)malloc(sizeof(struct queueArray));
	if(queue == NULL){
		printf("no memory when malloc queue\n");
		return NULL;
	}
	queue->max = max;
	queue->count = 0;
	queue->front = queue->rear = 0;
	queue->data = (queueDataType *)malloc(max*sizeof(queueDataType));
	if(queue->data == NULL){
		printf("no memory when malloc queue array\n");
		free(queue);
		return NULL;
	}
	queue->push = putInQueueArray;
	queue->pop = getQueueArray;
	queue->isEmpty = isEmptyQueueArray;
	queue->isFull = isFullQueueArray;
	return queue;
}

