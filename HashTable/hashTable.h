//哈希表的数据类型
typedef int dataType;

//哈希表最大容量
#define MAX 20

//未定义值
#define UNDEFINE -32678


//链表结点
typedef struct t_node {
	dataType data;
	struct t_node*next;
}node;

//哈希结构
typedef struct hash_table {
	int count;
	node *datas;
}table;

//初始化哈希表
void table_init(table *t);

//添加数据到哈希表
void add(table *t, dataType data);

//查询关键字是否在哈希表
bool search(table *t, dataType data);

//生成哈希码（除留余法）
int hash_code(dataType data);

//删除关键字
void remove(table *t, dataType data);

void traverse(table *t, void(*visit)(dataType data));