// CStudyLibrary.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "tree_node.h"
#include<stdlib.h>


void print(dataType data) {
	printf("%d ", data);
}
int main()
{
	node_point root=NULL;
	int arr[] = {1,2,3,4,5,6,7,8};
	for (int i = 0; i < 8; i++) {
		add_node(&root, arr[i]);
	}

	preorder(root, print);
	level_traversal(root, print);
	system("PAUSE");
    return 0;
}

