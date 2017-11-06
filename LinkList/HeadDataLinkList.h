//�ڵ���������
typedef int dataType  ;

typedef int Bool;

#define true 1;

#define false 0;

typedef struct node {
	dataType data;
	struct node*next;
}Node,*link ;

//��ʼ������,�ɹ�����true,���򷵻�false
Bool init(link*list);

//����������
int get_length(link list);

//��ָ��λ��֮ǰ����Ԫ��
Bool insert(link*list, int location,dataType data);

//��ĩβ���Ԫ��
Bool add(link*list, dataType data);

//ɾ��ָ��λ�õ�Ԫ��
Bool remove(link list, int location);

void display_list(link list, void(*visit)(dataType data));

//�����Ƿ�Ϊ��
Bool list_is_empty(link list);

Bool find(link list, dataType data);

dataType get_data(link list, int location);



