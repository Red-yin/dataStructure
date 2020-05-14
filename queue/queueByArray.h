/*************************************************************************
	>c++ File Name: queueByArray.h
	>c++ Created Time: 2020年05月12日 星期二 17时30分51秒
 ************************************************************************/

typedef int queueDataType;
typedef struct queueArray{
	int max;			//队列数据容量
	int count;			//队列当前数据量大小
	unsigned int front;	//队列数据头，从这里取出数据
	unsigned int rear;	//队列数据尾，从这里加入数据
	queueDataType *data;//队列数组起点
}*pQueueArray;

/*	queue: 队列句柄
 *	number: 请求放入的元素个数，队列空余空间至少需要sizeof(queueDataType)*number
 *	data: 存放待放入数据的缓存区
 */
int putInQueueArray(pQueueArray queue, int number, queueDataType *data);
/*	queue: 队列句柄
 *	number: 请求取出的元素个数
 *	buf: 存放待取出数据的缓存区，大小至少需要sizeof(queueDataType)*number
 */
int getQueueArray(pQueueArray queue, int number, queueDataType *buf);
int isEmptyQueueArray(pQueueArray queue);
int isFullQueueArray(pQueueArray queue);
pQueueArray createQueueArray(int max);
