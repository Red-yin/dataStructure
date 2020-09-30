/*************************************************************************
	>c++ File Name: stackByArray.h
	>c++ Created Time: 2020年05月14日 星期四 11时19分42秒
 ************************************************************************/

typedef int stackDataType;
typedef struct stackArray{
	int max;		//栈容量
	int top;		//栈顶位置
	stackDataType *bottom;	//栈底指针
	int (*pop)(struct stackArray *stack, stackDataType *buf);
	int (*push)(struct stackArray *stack, stackDataType data);
	int (*isEmpty)(struct stackArray *stack);
	int (*isFull)(struct stackArray *stack);
}*pStackArray;

pStackArray createStackArray(int max);
