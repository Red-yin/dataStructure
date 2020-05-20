/*************************************************************************
	>c++ File Name: avlTree.h
	>c++ Created Time: 2020年05月18日 星期一 10时24分38秒
 ************************************************************************/

typedef struct avlTreeNode{
	int data;
	int bf;
	struct avlTreeNode *parent, *left, *right;
}*pAvlTreeNode;

typedef struct avlTree{
	pAvlTreeNode *root;
	int (*insert)(struct avlTree *tree, int data);
	int (*delete)(struct avlTree *tree, int data);
	pAvlTreeNode (*find)(struct avlTree *tree, int data);
}*pAvlTree;
