#pragma once
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
node_point head = NULL;

//链表尾部节点
node_point tail = NULL;

//队列是否为空
BOOL is_empty();

//从 队列 中移除所有的元素。
void Clear();

//判断某个元素是否在 队列 中。
BOOL Contains(dataType data);

//移除并返回在 队列 的开头的对象。
dataType Dequeue();

//向 队列 的末尾添加一个对象。
void Enqueue(dataType data);

