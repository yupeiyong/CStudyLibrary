
#include "stdafx.h"
#include "LinkList.h"
#include "malloc.h"
#include <stdlib.h>

void add(dataType data, node_point * head)
{
	node_point node = (node_point)malloc(sizeof(Node));
	node->data = data;
	node->next = NULL;
	if (*head == NULL) {
		*head = node;
		return;
	}
	node_point p = *head;
	while (p->next != NULL) {
		p = p->next;
	}
	p->next = node;
	count++;
}

void remove(dataType data, node_point head)
{
	if (is_empty(head)) {
		printf("链表为空！");
		return;
	}
	if (head->data == data) {
		node_point tmp = head;
		head = head->next;
		free(tmp);
		tmp = NULL;
		count--;
		return;
	}
	node_point p = head;
	node_point curNode = head->next;
	while (curNode->next != NULL && curNode->data != data) {
		p = curNode;
		curNode = curNode->next;
	}
	if (curNode->data == data) {
		p->next = curNode->next;
		free(curNode);
		curNode = NULL;
		count--;
	}
}

node_point find(dataType data, node_point head)
{
	if (is_empty(head)) {
		printf("链表为空！");
		return NULL;
	}
	node_point p = head;
	while (p != NULL) {
		if (p->data == data) {
			return p;
		}
		p = p->next;
	}
	return NULL;
}

BOOL is_empty(node_point head)
{
	return count == 0 || head == NULL;
}
void print(dataType data) {
	printf("%d ", data);
}
void display(node_point head, void(*visit)(dataType data))
{
	if (head == NULL) {
		return;
	}
	node_point p = head;
	while (p != NULL) {
		visit(p->data);
		p = p->next;
	}
}
int _tmain(int argc, _TCHAR* argv[])
{
	for (int i = 0; i < 30; i++) {
		add(i, &head);
	}
	display(head, print);
	printf("\r\n");
	node_point node = find(15, head);
	if (node != NULL) {
		printf("成功找到元素15！\r\n");
	}

	printf("\r\n删除元素15\r\n");
	remove(15, head);
	display(head, print);

	system("PAUSE");
	return 0;
}


