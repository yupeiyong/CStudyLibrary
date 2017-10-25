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

//添加数据到链表末尾
void add(dataType data, node_point *head);


//删除链表元素
void remove(dataType data, node_point head);


//查找链表元素
node_point find(dataType data, node_point head);

//链表是否为空
BOOL is_empty(node_point head);


//显示链表数据
void display(node_point head, void(*visit)(dataType data));
