/*************************************************************************
	>c++ File Name: binaryTree.h
	>c++ Created Time: 2020年05月14日 星期四 16时14分25秒
 ************************************************************************/

typedef struct binaryTreeNode{
	int data;
	struct binaryTreeNode *left;
	struct binaryTreeNode *right;
}*pBinaryTreeNode;

typedef struct binaryTree{
	int nodeNum;		//整棵树上的节点个数
	pBinaryTreeNode root;
}*pBinaryTree;

int insertBinaryTreeNode(pBinaryTree tree, int data);
int deleteBinaryTreeNode(pBinaryTree tree, int data);
pBinaryTreeNode findBinaryTreeNode(pBinaryTree tree, int data);
int isEmptyBinaryTree(pBinaryTree tree);
pBinaryTree createBinaryTree();
void travelBinaryTree(pBinaryTreeNode node);

