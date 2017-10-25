// Queue.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Queue.h"
#include "malloc.h"
#include <stdlib.h>
//队列是否为空
BOOL is_empty() {
	return count == 0;
}

//从 队列 中移除所有的元素。
void Clear() {
}

//判断某个元素是否在 队列 中。
BOOL Contains(dataType data) {
	return false;
}

//移除并返回在 队列 的开头的对象。
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

//向 队列 的末尾添加一个对象。
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

