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
node_point top = NULL;

//������ݵ�����
void push(dataType data, node_point *top);


//���ز�ɾ����Ԫ��
dataType pop();

//���ض�Ԫ��
dataType get_top();

//ջ�Ƿ�Ϊ��
BOOL is_empty(node_point top);
