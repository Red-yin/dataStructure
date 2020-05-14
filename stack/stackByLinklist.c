/*************************************************************************
	> c File Name: stackByLinklist.c
	> c Created Time: 2020年05月12日 星期二 15时16分08秒
 ************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include"stackByLinklist.h"

void *popStackLinklist(stackLinklistTop stack)
{
	if(isEmptyStackLinklist(stack) == 1){
		printf("no data in stack\n");
		return NULL;
	}
	void *ret = stack->top->data;
	stackLinklist tmp = stack->top;
	stack->top = stack->top->next;
	stack->count--;
	free(tmp);
	return ret;
}

int pushStackLinklist(stackLinklistTop stack, void *data)
{
	if(isFullStackLinklist(stack) == 1){
		printf("stack is full already\n");
		return -1;
	}
	stackLinklist tmp = (stackLinklist)malloc(sizeof(struct stackLinklist));
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

int isEmptyStackLinklist(stackLinklistTop stack)
{
	 return (stack == NULL || stack->count == 0);
}

int isFullStackLinklist(stackLinklistTop stack)
{
	if(stack == NULL){
		printf("error: stack point is NULL\n");
		return -1;
	}
	return stack->count == stack->max;
}

stackLinklistTop createStackLinklist(unsigned int max)
{
	stackLinklistTop stack = (stackLinklistTop)malloc(sizeof(struct stackLinklistTop));
	if(stack == NULL){
		printf("no memory in stack init\n");
		return NULL;
	}
	stack->top = NULL;
	stack->max = max;
	stack->count = 0;
	return stack;
}

int main()
{
	stackLinklistTop s = createStackLinklist(100);
	int i = 0;
	for(;i < 200; i++){
		int *d = (int *)malloc(sizeof(int));
		*d = i;
		if(pushStackLinklist(s, d) < 0){
			free(d);
		}
	}
	for(i = 0;i < 200; i++){
		void *d = NULL;
		if((d = popStackLinklist(s)) != NULL){
			printf("data is %d\n", *(int *)d);
			free(d);
		}
	}
	return 0;
}
