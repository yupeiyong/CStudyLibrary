// Queue.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Queue.h"
#include "malloc.h"
#include <stdlib.h>
//�����Ƿ�Ϊ��
BOOL is_empty() {
	return count == 0;
}

//�� ���� ���Ƴ����е�Ԫ�ء�
void Clear() {
}

//�ж�ĳ��Ԫ���Ƿ��� ���� �С�
BOOL Contains(dataType data) {
	return false;
}

//�Ƴ��������� ���� �Ŀ�ͷ�Ķ���
dataType Dequeue() {
	if (!is_empty()) {
		node_point p = head;
		if (p) {
			head = head -> next;
			dataType data = p->data;
			free(p);
			p = NULL;
			return data;
		}
		return -9999;
	}
	else {
		return -9999;
	}
}

//�� ���� ��ĩβ���һ������
void Enqueue(dataType data) {
	node_point node = (node_point)malloc(sizeof(Node));
	node->data = data;
	node->next = NULL;
	if (tail == NULL) {
		head = node;
		tail = node;
		count++;
	}
	else {
		tail->next = node;
		tail = tail->next;
	}
}
int main()
{
	for (int i = 0; i < 30; i++) {
		Enqueue(i);
	}

	while (!is_empty()) {
		printf("%d ", Dequeue());
	}

	system("PAUSE");
	return 0;
}

