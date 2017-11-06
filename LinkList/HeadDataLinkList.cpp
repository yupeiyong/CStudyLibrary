#include "stdafx.h"
#include "HeadDataLinkList.h"
#include "malloc.h"
#include <stdlib.h>

/*
单链表，头结点是一个非空结点
*/
Bool init(link * list)
{
	(*list) = (Node*)malloc(sizeof(Node));
	if (!(*list))
		//分配内存失败，返回false
		return false;

	(*list)->next = NULL;
	(*list)->data = 0;//当前数量为0
	return true;
}

int get_length(link list)
{
	if (!list)
		return 0;

	//返回保存在头结点中的链表长度
	return list->data;
}

//插入元素到指定位置
//location从0开始的索引位置
Bool insert(link * list, int location, dataType data)
{
	link node;
	node = (Node*)malloc(sizeof(Node));
	if (!node)
		//分配内存不成功返回false
		return false;

	node->data = data;
	node->next = NULL;

	//链表为空，就先初始化
	if (!(*list))
		init(list);

	if (location<0 || location>get_length((*list)) - 1)
		//索引位置不能小于0和大于当前长度
		return false;

	//父结点的索引位置
	int curIndex = 0;
	link p = *list;
	while (p->next && curIndex < location) {
		p = p->next;
		curIndex++;
	}

	//未找到索引位置，位置大于链表长度
	if (curIndex > location)
		return false;

	node->next = p->next;
	p->next = node;
	(*list)->data++;
	return true;
}

Bool add(link * list, dataType data)
{
	link node;
	node = (Node*)malloc(sizeof(Node));
	if (!node)
		//分配内存不成功返回false
		return false;

	node->data = data;
	node->next = NULL;

	//链表为空，就先初始化
	if (!(*list))
		init(list);

	link p = *list;
	while (p->next) {
		p = p->next;
	}

	p->next = node;
	(*list)->data++;
	return true;
}

Bool remove(link list, int location)
{
	//链表为空，返回false
	if (list_is_empty(list))
		return false;

	if (location<0 || location>get_length(list) - 1)
		//索引位置不能小于0和大于当前长度
		return false;

	//父结点的索引位置
	int curIndex = 0;
	link p = list;
	while (p->next && curIndex < location) {
		p = p->next;
		curIndex++;
	}

	//未找到索引位置，位置大于链表长度
	if (curIndex > location)
		return false;

	link q = p->next;
	p->next = q->next;
	free(q);
	list->data--;
	return true;
}

void display_list(link list, void(*visit)(dataType data))
{
	if (!list)return;
	link p = list->next;
	while (p) {
		visit(p->data);
		p = p->next;
	}
}

Bool list_is_empty(link list)
{
	return get_length(list) == 0;
}

Bool find(link list, dataType data)
{
	//链表为空，就先初始化
	if (!list)
		return false;

	link p = list;
	while (p->next && p->data != data) {
		p = p->next;
	}
	if (p != NULL && p->data == data) {
		return true;
	}
	else {
		return false;
	}
}

dataType get_data(link list, int location)
{
	//链表为空，返回false
	if (list_is_empty(list))
		throw;

	if (location<0 || location>get_length(list) - 1)
		//索引位置不能小于0和大于当前长度
		throw;

	//父结点的索引位置
	int curIndex = 0;
	link p = list;
	while (p->next && curIndex < location) {
		p = p->next;
		curIndex++;
	}

	//未找到索引位置，位置大于链表长度
	if (curIndex > location)
		throw;

	link q = p->next;
	return q->data;
}
void print_list(dataType data) {
	printf("%d ", data);
}
int _tmain(int argc, _TCHAR* argv[])
{
	link head=NULL;
	for (int i = 0; i < 10; i++) {
		add(&head,i);
	}
	display_list(head, print_list);
	printf("\r\n");
	Bool result = find(head,5);
	if (result) {
		printf("成功找到元素5！\r\n");
	}

	result = find(head, 55);
	if (!result) {
		printf("未找到元素55！\r\n");
	}

	printf("\r\n删除元素2\r\n");
	remove(head,2);
	display_list(head, print_list);

	printf("\r\n插入99到第一个位置\r\n");
	//插入99到第一个位置
	insert(&head, 0, 99);
	display_list(head, print_list);

	printf("\r\n插入111到第2个位置\r\n");
	//插入99到第一个位置
	insert(&head, 1, 111);
	display_list(head, print_list);

	printf("\r\n插入88到最后位置\r\n");
	//插入88到最后位置
	insert(&head, get_length(head)-1, 88);
	display_list(head, print_list);

	system("PAUSE");
	return 0;
}
