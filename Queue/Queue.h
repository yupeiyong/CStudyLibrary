#pragma once
#pragma once
//�ڵ���������
typedef int dataType;

//�ڵ�����
int count;

typedef int BOOL;
#define true 0
#define false 1
//����ڵ�
typedef struct node {
	dataType data;
	struct node *next;
}Node, *node_point;

//����ͷ�ڵ�
node_point head = NULL;

//����β���ڵ�
node_point tail = NULL;

//�����Ƿ�Ϊ��
BOOL is_empty();

//�� ���� ���Ƴ����е�Ԫ�ء�
void Clear();

//�ж�ĳ��Ԫ���Ƿ��� ���� �С�
BOOL Contains(dataType data);

//�Ƴ��������� ���� �Ŀ�ͷ�Ķ���
dataType Dequeue();

//�� ���� ��ĩβ���һ������
void Enqueue(dataType data);

