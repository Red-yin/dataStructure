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
#include <sys/time.h>

#define MAX 3
struct pt_param{
	int pt_index;
	void *run_param;
};
int testNum = 0;
static int count = 0;

int getNum()
{
	testNum++;
	return testNum;
}
void *queueAdd(void *param)
{
	pthread_detach(pthread_self());
	struct pt_param *pm = (struct pt_param *)param;
	pLinklistQueue q = (pLinklistQueue)pm->run_param;
	while(count < 10000){
		q->push(q, (void *)testNum);
		printf("thread[%d] queue add: %d\n", pm->pt_index, testNum);
		testNum++;
		count++;
	}
	printf("thread[%d] quit\n", pm->pt_index);
	pm->pt_index = -1;
	return NULL;
}

int multiThreadTest(void *run_param, void *(run_routine)(void *param))
{
	pthread_t pt[MAX];
	struct pt_param *param = (struct pt_param *)calloc(MAX, sizeof(struct pt_param));
	count = 0;
	int i = 0;
	for(i = 0; i < sizeof(pt)/sizeof(pthread_t *); i++){
		param[i].pt_index = i;
		param[i].run_param = run_param;
		pthread_create(&pt[i], NULL, run_routine, (void *)&param[i]);
	}
}
#if 0
	while(1){
		int flag = 1;
		for(i = 0; i < sizeof(pt)/sizeof(pthread_t *); i++){
			if(param[i].pt_index == -1){
				flag = 0;
			}else{
				flag = 1;
				break;
			}
		}
		if(flag == 0)
			break;
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
#endif
int testLinklistQueue()
{
#if 1
	while(1){
		pLinklistQueue q = createLinklistQueue(-1, NULL);
		multiThreadTest((void *)q, queueAdd);
		destoryLinklistQueue(q);
		sleep(1);
	}
#else
	while(1){
		pLinklistQueue q = createLinklistQueue(-1, NULL);
		int i = 0;
		printf("queue put:\n");
		for(;i < 10000; i++){
			q->push(q, (void *)i);
			printf("%d ", i);
		}
		destoryLinklistQueue(q);
#if 0
		printf("\nqueue get:\n");
		while(q->isEmpty(q) == 0){
			int d = (int)q->pop(q);
			printf("%d ", d);
		}
#endif
		printf("\n");
		sleep(1);
	}
#endif
	return 0;
}

void *arrayQueueAddData(void *param)
{
	int i = 0;
	printf("[%s %d]\n", __FILE__, __LINE__);
	struct pt_param *pm = (struct pt_param *)param;
	printf("thread: %d\n", pm->pt_index);
	pArrayQueue q = (pArrayQueue)pm->run_param;
	while(1){
		i = getNum();
		if(q->push_cover(q, 1, &i) < 0){
			printf("%d put failed\n", i);
		}else{
			printf("push: %d\n", i);
		}
	}
	return NULL;
}

int testArrayQueue()
{
	printf("[%s %d]\n", __FILE__, __LINE__);
	pArrayQueue q = createArrayQueue(1024*1024);
	//multiThreadTest((void *)q, arrayQueueAddData);
	printf("[%s %d]\n", __FILE__, __LINE__);
	queueDataType buf[300*1024];
	printf("[%s %d]\n", __FILE__, __LINE__);
	int i = 0, n = sizeof(buf)/sizeof(queueDataType);
	memset(buf, 0, sizeof(buf));
	printf("[%s %d]\n", __FILE__, __LINE__);
	long long gap = 0;
	for(int j = 0; j < 100; j++){
		for(i = 0; i < n; i++){
			buf[i] = i;
		}
		struct timeval start, end;
		gettimeofday(&start, NULL);
		//printf("start : %ld.%ld\n", start.tv_sec, start.tv_usec);
		q->push_cover(q, n, buf);
		gettimeofday(&end, NULL);
		//printf("end   : %ld.%ld\n", end.tv_sec, end.tv_usec);
		long t = (end.tv_sec - start.tv_sec)*1000000 + (end.tv_usec - start.tv_usec);
		//printf("time gap: %ld\n", t);
		gap += t;
	}
	printf("time sum gap: %lld\n", gap);
		//q->pop_block(q, n, buf);
	//}

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
	//testLinklistQueue();
	testArrayQueue();
	return 0;
}
