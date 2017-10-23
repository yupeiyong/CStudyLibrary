// BinaryTree.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<malloc.h> 
#include <stdlib.h>

typedef int data_type;
typedef struct bst_node {
	data_type data;
	struct bst_node *left=NULL, *right=NULL;
}node,*nodeP;

void insert(nodeP*root, data_type data) {
	nodeP newNode = (nodeP)malloc(sizeof(struct bst_node));
	newNode->data = data;
	newNode->left = newNode->right = NULL;
	if (*root==NULL) {
		*root = newNode;
	}
	else {
		nodeP curNodep = *root;
		nodeP parent;
		while (curNodep) {
			parent = curNodep;
			if (data < curNodep->data) {
				if (curNodep->left==NULL) {
					parent->left = newNode;
					break;
				}
				curNodep = curNodep->left;
			}
			else {
				if (curNodep->right == NULL) {
					parent->right = newNode;
					break;
				}
				curNodep = curNodep->right;
			}
		}
	}
}

nodeP find(nodeP node,data_type data) {
	if (node == NULL)return NULL;
	nodeP curNode = node;
	while (curNode != NULL) {
		if (curNode->data == data) {
			return curNode;
		}
		if (data < curNode->data) {
			curNode = curNode->left;
		}
		else {
			curNode = curNode->right;
		}
	}
	return NULL;
}

void remove(nodeP*root, data_type data) {
	if (*root == NULL)return;
	nodeP p = *root;
	if (data < p->data) {
		remove(&(p->left), data);
	}
	else if (data > p->data) {
		remove(&(p->right), data);
	}
	else {
		if (p->left == NULL && p->right == NULL) {
			*root = NULL;
			free(p);
		}
		else if (p->left == NULL) {
			p = p->right;
		}
		else if (p->right == NULL) {
			p = p->left;
		}
		else {
			nodeP rightChild = p->right;
			if (rightChild->left == NULL) {
				p = rightChild;
			}
			else {
				nodeP minParent=rightChild;
				nodeP curNode = rightChild;
				while (curNode->left!=NULL) {
					minParent = curNode;
					curNode = curNode->left;
				}
				minParent->right = curNode->right;
				minParent->left = NULL;
				curNode->right = p->right;
				curNode->left = p->left;
				*root = curNode;
				curNode = NULL;
				free(curNode);
				free(p);
			}
		}
	}
}

void inOrderTraverse(nodeP node,void(*vist)(data_type data)) {
	if (node) {
		inOrderTraverse(node->left, vist);
		vist(node->data);
		inOrderTraverse(node->right, vist);
	}
}

void preOrderTraverse(nodeP node, void(*vist)(data_type data)) {
	if (node) {
		vist(node->data);
		preOrderTraverse(node->left, vist);
		preOrderTraverse(node->right, vist);
	}
}

void postOrderTraverse(nodeP node, void(*vist)(data_type data)) {
	if (node) {
		postOrderTraverse(node->left, vist);
		postOrderTraverse(node->right, vist);
		vist(node->data);
	}
}
void print(data_type data) {
	printf("%d ", data);
}
int main()
{
	nodeP root = NULL;
	data_type arr[] = {1,5,0,56,9,3,8};
	for (int i = 0; i < 7; i++) {
		insert(&root, arr[i]);
	}

	printf("中序排列：\r\n");
	inOrderTraverse(root, print);
	printf("前序排列：\r\n");
	preOrderTraverse(root, print);
	printf("后序排列：\r\n");
	postOrderTraverse(root, print);

	printf("\r\n");
	nodeP p = find(root, 0);
	if (p) {
		printf("找到元素0\r\n");
	}
	else {
		printf("未找到元素0\r\n");
	}

	printf("\r\n");
	p = find(root, 133333);
	if (p) {
		printf("找到元素133333\r\n");
	}
	else {
		printf("未找到元素133333\r\n");
	}

	remove(&root, 8);
	printf("删除8后的中序排列：\r\n");
	inOrderTraverse(root, print);


	remove(&root, 5);
	printf("删除5后的中序排列：\r\n");
	inOrderTraverse(root, print);

	printf("\r\n");
	system("PAUSE");
    return 0;
}

