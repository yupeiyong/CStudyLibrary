#pragma once
//节点数据类型
typedef int dataType;

//节点数量
int count;

typedef int BOOL;
#define true 0
#define false 1
//链表节点
typedef struct node {
	dataType data;
	struct node *next;
}Node, *node_point;

//链表头节点
node_point top = NULL;

//添加数据到顶部
void push(dataType data, node_point *top);


//返回并删除顶元素
dataType pop();

//返回顶元素
dataType get_top();

//栈是否为空
BOOL is_empty(node_point top);
