/*************************************************************************
  > c File Name: test.c
  > c Created Time: 2020年05月18日 星期一 17时39分06秒
 ************************************************************************/
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include"arrayStack.h"
#include"linklistStack.h"
#include"arrayQueue.h"
#include"linklistQueue.h"
#include <pthread.h>

#define MAX 5
struct pt_param{
	int pt_index;
	void *run_param;
};
int testNum = 0;
void *queueAdd(void *param)
{
	static int count = 0;
	struct pt_param *pm = (struct pt_param *)param;
	pLinklistQueue q = (pLinklistQueue)pm->run_param;
	while(count < 1000){
		q->push(q, (void *)testNum);
		printf("thread[%d] queue add: %d\n", pm->pt_index, testNum);
		testNum++;
		count++;
	}
	printf("thread[%d] quit\n", pm->pt_index);
	return NULL;
}

int testLinklistQueueAdd(pLinklistQueue q)
{
	pthread_t pt[MAX];
	struct pt_param param[MAX];
	int i = 0;
	for(i = 0; i < sizeof(pt)/sizeof(pthread_t *); i++){
		param[i].pt_index = i;
		param[i].run_param = (void *)q;
		pthread_create(&pt[i], NULL, queueAdd, (void *)&param[i]);
	}

	while(1){
		FILE *fp = fopen("./result.txt", "a");
		if(q->isEmpty(q) == 0){
			int d = (int)q->pop(q);
			printf("queue get: %d\n", d);
			char buf[8] = {0};
			sprintf(buf, "%d\n", d);
			fwrite(buf, 1, strlen(buf), fp);
		}else{
			usleep(10*1000);
		}
		fclose(fp);
	}
}
int testLinklistQueue()
{
	pLinklistQueue q = createLinklistQueue(-1);
#if 1
	testLinklistQueueAdd(q);
#else
	while(1){
		int i = 0;
		printf("queue put:\n");
		for(;i < MAX; i++){
			q->push(q, (void *)i);
			printf("%d ", i);
		}
		printf("\nqueue get:\n");
		while(q->isEmpty(q) == 0){
			int d = (int)q->pop(q);
			printf("%d ", d);
		}
		printf("\n");
		sleep(3);
	}
#endif
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

int main()
{
	testLinklistQueue();
	return 0;
}
