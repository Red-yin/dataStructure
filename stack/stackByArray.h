/*************************************************************************
	>c++ File Name: stackByArray.h
	>c++ Created Time: 2020年05月14日 星期四 11时19分42秒
 ************************************************************************/

typedef int stackDataType;
typedef struct stackArray{
	int max;		//栈容量
	int top;		//栈顶位置
	stackDataType *bottom;	//栈底指针
}*pStackArray;

int popStackArray(pStackArray stack, stackDataType *buf);
int pushStackArray(pStackArray stack, stackDataType data);
int isEmptyStackArray(pStackArray stack);
int isFullStackArray(pStackArray stack);
pStackArray createStackArray(int max);
