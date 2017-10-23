#include "stdafx.h"
#include "tree_node.h"
#include<stdlib.h>
#include<cstdio>
#include<queue>
using namespace std;

void add_node(node_point * root, dataType data)
{
	node_point p = (node_point)malloc(sizeof(struct tree_node));
	p->data = data;
	p->left=p->right = NULL;

	if (*root == NULL) {
		*root = p;
		return;
	}
	queue<node_point> q;
	q.push(*root);
	while (!q.empty()) {
		node_point curNode = q.front();
		q.pop();
		if (curNode->left == NULL) {
			curNode->left = p;
			return;
		}
		q.push(curNode->left);
		if (curNode->right == NULL) {
			curNode->right = p;
			return;
		}
		q.push(curNode->right);
	}
}

void preorder(node_point root, void(*visit)(dataType data))
{
	if (root != NULL) {
		visit(root->data);
		preorder(root->left, visit);
		preorder(root->right, visit);
	}
}

void level_traversal(node_point root, void(*visit)(dataType data))
{
	if (root == NULL)return;
	queue<node_point>q;
	q.push(root);
	while (!q.empty()) {
		node_point curNode=q.front();
		visit(curNode->data);
		q.pop();
		if (curNode->left != NULL) {
			q.push(curNode->left);
		}
		if (curNode->right != NULL) {
			q.push(curNode->right);
		}
	}
}

