/*************************************************************************
	>c++ File Name: stackBylinklist.h
	>c++ Created Time: 2020年05月12日 星期二 15时16分39秒
 ************************************************************************/

typedef struct stackLinklist{
	void *data;
	struct stackLinklist* next;
}*stackLinklist;

typedef struct stackLinklistTop{
	unsigned int max;
	unsigned int count;
	stackLinklist top;
}*stackLinklistTop;

void *popStackLinklist(stackLinklistTop stack);
int pushStackLinklist(stackLinklistTop stack, void *data);
int isEmptyStackLinklist(stackLinklistTop stack);
int isFullStackLinklist(stackLinklistTop stack);
stackLinklistTop createStackLinklist(unsigned int max);
