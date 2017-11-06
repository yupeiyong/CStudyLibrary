#include "stdafx.h"
#include "HeadDataLinkList.h"
#include "malloc.h"
#include <stdlib.h>

/*
������ͷ�����һ���ǿս��
*/
Bool init(link * list)
{
	(*list) = (Node*)malloc(sizeof(Node));
	if (!(*list))
		//�����ڴ�ʧ�ܣ�����false
		return false;

	(*list)->next = NULL;
	(*list)->data = 0;//��ǰ����Ϊ0
	return true;
}

int get_length(link list)
{
	if (!list)
		return 0;

	//���ر�����ͷ����е�������
	return list->data;
}

//����Ԫ�ص�ָ��λ��
//location��0��ʼ������λ��
Bool insert(link * list, int location, dataType data)
{
	link node;
	node = (Node*)malloc(sizeof(Node));
	if (!node)
		//�����ڴ治�ɹ�����false
		return false;

	node->data = data;
	node->next = NULL;

	//����Ϊ�գ����ȳ�ʼ��
	if (!(*list))
		init(list);

	if (location<0 || location>get_length((*list)) - 1)
		//����λ�ò���С��0�ʹ��ڵ�ǰ����
		return false;

	//����������λ��
	int curIndex = 0;
	link p = *list;
	while (p->next && curIndex < location) {
		p = p->next;
		curIndex++;
	}

	//δ�ҵ�����λ�ã�λ�ô���������
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
		//�����ڴ治�ɹ�����false
		return false;

	node->data = data;
	node->next = NULL;

	//����Ϊ�գ����ȳ�ʼ��
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
	//����Ϊ�գ�����false
	if (list_is_empty(list))
		return false;

	if (location<0 || location>get_length(list) - 1)
		//����λ�ò���С��0�ʹ��ڵ�ǰ����
		return false;

	//����������λ��
	int curIndex = 0;
	link p = list;
	while (p->next && curIndex < location) {
		p = p->next;
		curIndex++;
	}

	//δ�ҵ�����λ�ã�λ�ô���������
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
	//����Ϊ�գ����ȳ�ʼ��
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
	//����Ϊ�գ�����false
	if (list_is_empty(list))
		throw;

	if (location<0 || location>get_length(list) - 1)
		//����λ�ò���С��0�ʹ��ڵ�ǰ����
		throw;

	//����������λ��
	int curIndex = 0;
	link p = list;
	while (p->next && curIndex < location) {
		p = p->next;
		curIndex++;
	}

	//δ�ҵ�����λ�ã�λ�ô���������
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
		printf("�ɹ��ҵ�Ԫ��5��\r\n");
	}

	result = find(head, 55);
	if (!result) {
		printf("δ�ҵ�Ԫ��55��\r\n");
	}

	printf("\r\nɾ��Ԫ��2\r\n");
	remove(head,2);
	display_list(head, print_list);

	printf("\r\n����99����һ��λ��\r\n");
	//����99����һ��λ��
	insert(&head, 0, 99);
	display_list(head, print_list);

	printf("\r\n����111����2��λ��\r\n");
	//����99����һ��λ��
	insert(&head, 1, 111);
	display_list(head, print_list);

	printf("\r\n����88�����λ��\r\n");
	//����88�����λ��
	insert(&head, get_length(head)-1, 88);
	display_list(head, print_list);

	system("PAUSE");
	return 0;
}
