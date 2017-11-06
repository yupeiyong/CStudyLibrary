//节点数据类型
typedef int dataType  ;

typedef int Bool;

#define true 1;

#define false 0;

typedef struct node {
	dataType data;
	struct node*next;
}Node,*link ;

//初始化链表,成功返回true,否则返回false
Bool init(link*list);

//返回链表长度
int get_length(link list);

//在指定位置之前插入元素
Bool insert(link*list, int location,dataType data);

//在末尾添加元素
Bool add(link*list, dataType data);

//删除指定位置的元素
Bool remove(link list, int location);

void display_list(link list, void(*visit)(dataType data));

//链表是否为空
Bool list_is_empty(link list);

Bool find(link list, dataType data);

dataType get_data(link list, int location);



