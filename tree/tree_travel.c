/*************************************************************************
	> c File Name: tree_travel.c
	> c Created Time: 2020年05月12日 星期二 14时40分35秒
 ************************************************************************/
#include<stdio.h>

typedef struct BinTree{
	void *data;
	struct BinTree* left;
	struct BinTree* right;
}*BinTree;

void PreOrderTraversal(BinTree BT)
{
	if(BT){
		printf("%d\n", *(int *)BT->data);
		PreOrderTraversal(BT->left);
		PreOrderTraversal(BT->right);
	}
}

void InOrderTraversal(BinTree BT)
{
	if(BT){
		InOrderTraversal(BT->left);
		printf("%d\n", *(int *)BT->data);
		InOrderTraversal(BT->right);
	}
}

void PostOrderTraversal(BinTree BT)
{
	if(BT){
		PostOrderTraversal(BT->left);
		PostOrderTraversal(BT->right);
		printf("%d\n", *(int *)BT->data);
	}
}

int main()
{}
