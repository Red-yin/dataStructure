/*************************************************************************
  > c File Name: binaryTree.c
  > c Created Time: 2020年05月15日 星期五 10时17分48秒
 ************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include"binaryTree.h"
#include"queueByLinklist.h"

//检查二叉树的平衡，返回左子树的深度-右子树的深度
int checkBinaryTreeBlance(pBinaryTreeNode node)
{
	int bf = 0, count1[2] = {0}, count2[2] = {0};
	int left = 0, right = 0;
	if(node == NULL)
		return -1;
	pQueueLinklist q1 = createQueueLinklist(-1);
	pQueueLinklist q2 = createQueueLinklist(-1);
	if(q1 == NULL || q2 == NULL){
		printf("queue create failed\n");
		return -1000;
	}
	q1->push(q1, (void *)node->left);
	q2->push(q2, (void *)node->right);
	count1[1]++;
	count2[1]++;
	pBinaryTreeNode t1 = NULL, t2 = NULL;
	while(1){
		t1 = q1->pop(q1);
		if(t1){
			count1[1]--;
			if(t1->left){
				q1->push(q1, (void *)t1->left);
				count1[0]++;
			}
			if(t1->right){
				q1->push(q1, (void *)t1->right);
				count1[0]++;
			}
			if(count1[1] == 0){
				count1[1] = count1[0];
				count1[0] = 0;
				left++;
			}
		}
		t2 = q2->pop(q2);
		if(t2){
			count2[1]--;
			if(t2->left){
				q2->push(q2, (void *)t2->left);
				count2[0]++;
			}
			if(t2->right){
				q2->push(q2, (void *)t2->right);
				count2[0]++;
			}
			if(count2[1] == 0){
				count2[1] = count2[0];
				count2[0] = 0;
				right++;
			}
		}
		if(q1->isEmpty(q1) && q2->isEmpty(q2))
			break;
	}
	destoryQueueLinklist(&q1);
	destoryQueueLinklist(&q2);
	return (left - right);
}

void LLrotate(pBinaryTree tree, pBinaryTreeNode imblanceNode)
{

}
void LRrotate(pBinaryTree tree, pBinaryTreeNode imblanceNode)
{

}
void RRrotate(pBinaryTree tree, pBinaryTreeNode imblanceNode)
{

}
void RLrotate(pBinaryTree tree, pBinaryTreeNode imblanceNode)
{

}
pBinaryTreeNode findFatherNode(pBinaryTree tree, int data)
{
	if(isEmptyBinaryTree(tree) == 1){
		printf("tree is empty\n");
		return NULL;
	}	
	pBinaryTreeNode c = tree->root;
	pBinaryTreeNode f = NULL;
	while(1){
		if(data > c->data){
			f = c;
			c = c->right;
		}else if(data < c->data){
			f = c;
			c = c->left;
		}else{
			break;
		}
		if(c == NULL){
			f = NULL;
			break;
		}
	}
	return f;
}

int insertBinaryTreeNode(pBinaryTree tree, int data)
{
	if(isEmptyBinaryTree(tree) == 0){
		if(findBinaryTreeNode(tree, data) != NULL){
			printf("data is existed\n");
			return -1;
		}
	}	
	pBinaryTreeNode aNode = (pBinaryTreeNode)malloc(sizeof(struct binaryTreeNode));
	if(aNode == NULL){
		printf("no memory when alloc binary tree node\n");
		return -1;
	}
	aNode->data = data;
	aNode->left = aNode->right = NULL;
	tree->nodeNum++;
	if(tree->root == NULL){
		tree->root = aNode;
		return 0;
	}
	pBinaryTreeNode p = tree->root;
	while(1){
		if(data > p->data)	
			if(p->right != NULL)
				p = p->right;
			else{
				p->right = aNode;
				break;
			}
		else
			if(p->left != NULL)
				p = p->left;
			else{
				p->left = aNode;
				break;
			}
	}	
	return 0;
}

int deleteBinaryTreeNode(pBinaryTree tree, int data)
{
	if(isEmptyBinaryTree(tree) == 1){
		printf("tree is empty\n");
		return -1;
	}	
	pBinaryTreeNode dNode = findBinaryTreeNode(tree, data);
	if(dNode == NULL){
		printf("%d is not exist\n", data);
		return -1;
	}
	printf("--%s--%d--\n", __func__, __LINE__);
	int a = checkBinaryTreeBlance(tree->root);
	printf("tree depth: %d\n", a);
	printf("--%s--%d--\n", __func__, __LINE__);
	pBinaryTreeNode fNode = findFatherNode(tree, data);
	int numSons = ((dNode->left != NULL) + (dNode->right != NULL));
	switch(numSons){
		case 0:
		case 1:{
				   pBinaryTreeNode s = (dNode->left == NULL ? dNode->right: dNode->left);
				   if(fNode == NULL){
					   tree->root = s;
				   }else{
					   if(fNode->left == dNode)
						   fNode->left = s;
					   else
						   fNode->right = s;

				   }
				   free(dNode);
				   break;
			   }
		case 2:{
				   pBinaryTreeNode r = NULL;
				   if(checkBinaryTreeBlance(dNode) >= 0){	//左子树层数大，找左子树最大节点
					   for(r = dNode->left; r->right != NULL; r = r->right);
				   }else{									//右子树层数大，找右子树最小节点
					   for(r = dNode->right; r->left != NULL; r = r->left);
				   }
				   //保存找到的节点数据，删除这个节点，然后用保存的数据替换待删除节点数据
				   int rData = r->data;
				   deleteBinaryTreeNode(tree, r->data);
				   dNode->data = rData;
				   break;
			   }
	}
	tree->nodeNum--;
	return 0;
}

pBinaryTreeNode findBinaryTreeNode(pBinaryTree tree, int data)
{
	if(isEmptyBinaryTree(tree) == 1){
		printf("tree is empty\n");
		return NULL;
	}	
	pBinaryTreeNode c = tree->root;
	while(1){
		if(data > c->data){
			c = c->right;
		}else if(data < c->data){
			c = c->left;
		}else{
			break;
		}
		if(c == NULL)
			break;
	}
	return c;
}

int isEmptyBinaryTree(pBinaryTree tree)
{
	return 0 == tree->nodeNum;
}

pBinaryTree createBinaryTree()
{
	pBinaryTree tree = (pBinaryTree)malloc(sizeof(struct binaryTree));
	if(tree == NULL){
		printf("no memory when malloc tree\n");
		return NULL;
	}
	tree->nodeNum = 0;
	tree->root = NULL;
	return tree;
}

void travelBinaryTreeInMidorder(pBinaryTreeNode node)
{
	if(node){
		travelBinaryTreeInMidorder(node->left);
		printf("%d\t", node->data);
		travelBinaryTreeInMidorder(node->right);
	}
}

void travelBinaryTreeInLevel(pBinaryTreeNode node)
{
	if(node){
		pQueueLinklist q = createQueueLinklist(-1);
		int count_push = 0, count_pop = 0, level = 0;
		q->push(q, (void *)node);
		count_pop = 1;
		count_push = 0;
		pBinaryTreeNode tmp = NULL;
		printf("level[%d]\t", level);
		while(1){
			tmp = q->pop(q);
			if(tmp == NULL){
				break;
			}
			count_pop--;
			printf("%d\t", tmp->data);
			if(tmp->left){
				q->push(q, tmp->left);
				count_push++;
			}
			if(tmp->right){
				q->push(q, tmp->right);
				count_push++;
			}
			if(count_pop == 0){
				count_pop = count_push;
				count_push = 0;
				printf("\nlevel[%d]\t", ++level);
			}
		}
		destoryQueueLinklist(&q);
	}
}
