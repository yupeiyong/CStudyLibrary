// Stack.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Stack.h"
#include "malloc.h"
#include <stdlib.h>

//������ݵ�����
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


//ɾ����Ԫ��
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

//���ض�Ԫ��
dataType get_top() {
	if (top == NULL)
		return -9999;
	
	return top->data;
}

//ջ�Ƿ�Ϊ��
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

