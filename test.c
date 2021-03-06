/*************************************************************************
	> c File Name: test.c
	> c Created Time: 2020年05月18日 星期一 17时39分06秒
 ************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include"stackByArray.h"
#include"stackByLinklist.h"
#include"queueByArray.h"
#include"queueByLinklist.h"
#include"binaryTree.h"

int testQueueLinklist()
{
	pQueueLinklist q = createQueueLinklist(100);
	int i = 0;
	for(;i < 200; i++){
		int *d = (int *)malloc(sizeof(int));
		*d = i;
		if(q->push(q, d) < 0){
			free(d);
		}
	}
	for(i = 0;i < 200; i++){
		void *d = NULL;
		if((d = q->pop(q)) != NULL){
			printf("data is %d\n", *(int *)d);
			free(d);
		}
	}
	return 0;
	
}
int testQueueArray()
{
	pQueueArray q = createQueueArray(15);
	int i = 0;
	for(;i < 20; i++){
		if(q->push(q, 1, &i) < 0){
			printf("%d put failed\n", i);
		}
	}
	int n = 100;
	queueDataType buf[n];
	while(1){
		if(0 >= q->pop(q, 10, buf))
			break;
		else
			for(i = 0; i < 10; i++)
				printf("get %d\n", buf[i]);
	}
	return 0;


}
int testStackArray()
{
	pStackArray stack = createStackArray(10);
	stackDataType i = 0;
	for(i = 36; i < 50; i++){
		if(0 != stack->push(stack, i))
			printf("push %d failed\n", i);
		else
			printf("push %d\n", i);
	}
	stackDataType buf;
	while(1){
		if(0 != stack->pop(stack, &buf))
			break;
		else
			printf("pop %d\n", buf);
	}
	return 0;
}

int testStackLinklist()
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


int testBinaryTree()
{
	printf("print tree: pp\ndelete node: d num\nadd node:anum\nquit: qq\n");
	pBinaryTree tree = createBinaryTree();
	char handle = 0;
	int data = 0;
	while(1){
		printf("input:\n");
		scanf("%c%d", &handle, &data);
		printf("handle: %c, data: %d\n", handle, data);
		switch(handle){
			case 'p':
				travelBinaryTreeInLevel(tree->root);
				printf("\n");
				travelBinaryTreeInMidorder(tree->root);
				break;
			case 'd':
				deleteBinaryTreeNode(tree, data);
				break;
			case 'a':
				insertBinaryTreeNode(tree, data);
				break;
			case 'q':
				exit(0);
				break;
		}
	}
}

int main()
{
	testBinaryTree();
	return 0;
}
