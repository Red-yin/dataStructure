/*************************************************************************
	> c File Name: stackByLinklist.c
	> c Created Time: 2020年05月12日 星期二 15时16分08秒
 ************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include"stackByLinklist.h"

int isEmptyStackLinklist(pStackLinklist stack)
{
	 return (stack == NULL || stack->count == 0);
}

int isFullStackLinklist(pStackLinklist stack)
{
	if(stack == NULL){
		printf("error: stack point is NULL\n");
		return -1;
	}
	return stack->count == stack->max;
}

void *popStackLinklist(pStackLinklist stack)
{
	if(isEmptyStackLinklist(stack) == 1){
		printf("no data in stack\n");
		return NULL;
	}
	void *ret = stack->top->data;
	pStackNode tmp = stack->top;
	stack->top = stack->top->next;
	stack->count--;
	free(tmp);
	return ret;
}

int pushStackLinklist(pStackLinklist stack, void *data)
{
	if(isFullStackLinklist(stack) == 1){
		printf("stack is full already\n");
		return -1;
	}
	pStackNode tmp = (pStackNode)malloc(sizeof(struct stackNode));
	if(tmp == NULL){
		printf("no memory in stack malloc\n");
		return -2;
	}
	tmp->data = data;
	tmp->next = stack->top;
	stack->top = tmp;
	stack->count++;
	return 0;
}

pStackLinklist createStackLinklist(unsigned int max)
{
	pStackLinklist stack = (pStackLinklist)malloc(sizeof(struct stackLinklist));
	if(stack == NULL){
		printf("no memory in stack init\n");
		return NULL;
	}
	stack->top = NULL;
	stack->max = max;
	stack->count = 0;
	stack->pop = popStackLinklist;
	stack->push = pushStackLinklist;
	stack->isEmpty = isEmptyStackLinklist;
	stack->isFull = isFullStackLinklist;
	return stack;
}

int main()
{
	pStackLinklist s = createStackLinklist(100);
	int i = 0;
	for(;i < 200; i++){
		int *d = (int *)malloc(sizeof(int));
		*d = i;
		if(s->push(s, d) < 0){
			free(d);
		}
	}
	for(i = 0;i < 200; i++){
		void *d = NULL;
		if((d = s->pop(s)) != NULL){
			printf("data is %d\n", *(int *)d);
			free(d);
		}
	}
	return 0;
}
