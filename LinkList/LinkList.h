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

//������ݵ�����ĩβ
void add(dataType data, node_point *head);


//ɾ������Ԫ��
void remove(dataType data, node_point head);


//��������Ԫ��
node_point find(dataType data, node_point head);

//�����Ƿ�Ϊ��
BOOL is_empty(node_point head);


//��ʾ��������
void display(node_point head, void(*visit)(dataType data));
