//��ϣ�����������
typedef int dataType;

//��ϣ���������
#define MAX 20

//δ����ֵ
#define UNDEFINE -32678


//������
typedef struct t_node {
	dataType data;
	struct t_node*next;
}node;

//��ϣ�ṹ
typedef struct hash_table {
	int count;
	node *datas;
}table;

//��ʼ����ϣ��
void table_init(table *t);

//������ݵ���ϣ��
void add(table *t, dataType data);

//��ѯ�ؼ����Ƿ��ڹ�ϣ��
bool search(table *t, dataType data);

//���ɹ�ϣ�루�����෨��
int hash_code(dataType data);

//ɾ���ؼ���
void remove(table *t, dataType data);

void traverse(table *t, void(*visit)(dataType data));