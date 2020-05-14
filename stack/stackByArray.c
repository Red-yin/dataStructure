/*************************************************************************
	> c File Name: stackByArray.c
	> c Created Time: 2020年05月14日 星期四 11时19分33秒
 ************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include"stackByArray.h"

int popStackArray(pStackArray stack, stackDataType *buf)
{
	if(isEmptyStackArray(stack) == 1){
		printf("stack is empty\n");
		return -1;
	}
	*buf = stack->bottom[stack->top--];
	return 0;
}

int pushStackArray(pStackArray stack, stackDataType data)
{
	if(1 == isFullStackArray(stack)){
		printf("stack is full\n");
		return -1;
	}
	stack->bottom[++stack->top] = data;
	return 0;
}

int isEmptyStackArray(pStackArray stack)
{
	return stack->top == -1;
}

int isFullStackArray(pStackArray stack)
{
	return stack->top == (stack->max-1);
}

pStackArray createStackArray(int max)
{
	if(max <= 0){
		printf("stack max must > 0\n");
		return NULL;
	}
	pStackArray stack = (pStackArray)malloc(sizeof(struct stackArray));
	if(stack == NULL){
		printf("no memory when create stack\n");
		return NULL;
	}
	stack->max = max;
	stack->top = -1;
	stack->bottom = (stackDataType *)malloc(max*sizeof(stackDataType));
	if(stack->bottom == NULL){
		printf("no memory when malloc stack size\n");
		free(stack);
		return NULL;
	}
	return stack;
}

int main()
{
	pStackArray stack = createStackArray(10);
	stackDataType i = 0;
	for(i = 36; i < 50; i++){
		if(0 != pushStackArray(stack, i))
			printf("push %d failed\n", i);
		else
			printf("push %d\n", i);
	}
	stackDataType buf;
	while(1){
		if(0 != popStackArray(stack, &buf))
			break;
		else
			printf("pop %d\n", buf);
	}
	return 0;
}
