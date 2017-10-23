#pragma once
typedef int dataType;
typedef struct tree_node {
	dataType data;
	struct tree_node *left,*right;
}treeNode,*node_point;

void add_node(node_point *root,dataType data);
void preorder(node_point root, void(*visit)(dataType data));
void level_traversal(node_point root, void(*visit)(dataType data));
