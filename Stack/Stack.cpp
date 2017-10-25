// Stack.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Stack.h"
#include "malloc.h"
#include <stdlib.h>

//添加数据到顶部
void push(dataType data, node_point *top) {
	node_point node = (node_point)malloc(sizeof(Node));
	node->data = data;
	node->next = NULL;
	if (*top == NULL) {
		*top = node;
		count++;
		return;
	}
	node->next = *top;
	*top = node;
	count++;
}


//删除顶元素
dataType pop() {
	if (top == NULL)
		return -9999;
	node_point tmp = top;
	top = top->next;
	dataType data = tmp->data;
	free(tmp);
	tmp = NULL;
	count--;
	return data;
}

//返回顶元素
dataType get_top() {
	if (top == NULL)
		return -9999;
	
	return top->data;
}

//栈是否为空
BOOL is_empty() {
	return count == 0 || top == NULL;
}

int main()
{
	for (int i = 0; i < 30; i++) {
		push(i, &top);
	}

	while (!is_empty()) {
		printf("%d ", pop());
	}
	system("PAUSE");
	return 0;
}

