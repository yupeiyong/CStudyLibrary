// HashTable.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "stdlib.h"
#include "malloc.h"
#include "hashTable.h"


//��ʼ����ϣ��
void table_init(table *t) {
	t->count = MAX;
	t->datas = (node*)malloc(sizeof(node)*MAX);
	for (int i = 0; i < t->count; i++) {
		t->datas[i].data = UNDEFINE;
		t->datas[i].next = NULL;
	}
}

//������ݵ���ϣ��
void add(table *t, dataType data) {
	int hashCode = hash_code(data);
	dataType curKey = t->datas[hashCode].data;
	if (curKey != data && curKey != UNDEFINE) {
		node*tmp;
		tmp = (node*)malloc(sizeof(node));
		tmp->data = data;
		tmp->next = t->datas[hashCode].next;
		t->datas[hashCode].next = tmp;
	}
	else if (curKey == UNDEFINE) {
		t->datas[hashCode].data = data;
	}
}

//��ѯ�ؼ����Ƿ��ڹ�ϣ��
bool search(table *t, dataType data) {
	if (t == NULL)return false;
	int hashCode = hash_code(data);
	dataType curKey = t->datas[hashCode].data;
	if (curKey == UNDEFINE)return false;
	if (curKey == data)return true;
	node*p = t->datas[hashCode].next;
	while (p != NULL) {
		if (p->data == data)
			return true;
		p = p->next;
	}
	return false;
}

//���ɹ�ϣ�루�����෨��
int hash_code(dataType data) {
	return data % MAX;
}

//ɾ���ؼ���
void remove(table *t, dataType data) {
	if (t == NULL)return;
	int hashCode = hash_code(data);
	dataType curKey = t->datas[hashCode].data;
	if (curKey == UNDEFINE)return;
	if (curKey == data) {
		if (t->datas[hashCode].next == NULL) {
			t->datas[hashCode].data = UNDEFINE;
		}
		else {
			node *next = t->datas[hashCode].next;
			t->datas[hashCode].data = next->data;
			t->datas[hashCode].next = next->next;
			free(next);
			next = NULL;
		}
	}
	else {
		node *p = t->datas[hashCode].next;
		if (p == NULL)return;
		//��һ���ӽ��Ĺؼ��֣�Ҫɾ���Ĺؼ���
		if (p->data == data) {
			//���ӽ����ڵ�һ���ӽ�����һ���
			t->datas[hashCode].next = p->next;
		}
		else {
			while (p->next != NULL && p->next->data != data) {
				p = p->next;
			}

			if (p->next->data == data) {
				node*tmp = p->next;
				p->next = tmp->next;
				free(tmp);
			}
		}
	}
	return;

}

void traverse(table *t, void(*visit)(dataType data)) {
	if (t == NULL)
		return;
	for (int i = 0; i < MAX; i++) {
		if (t->datas[i].data == UNDEFINE)continue;
		node n = t->datas[i];
		visit(n.data);
		node *p = n.next;
		while (p != NULL) {
			visit(p->data);
			p = p->next;
		}
	}
}

void print(dataType data) {
	printf("%d ", data);
}
void search_key(table *t, dataType data) {
	bool isExsits = search(t, data);
	if (isExsits) {
		printf("��ϣ����ֵ: %d\n", data);
	}
	else {
		printf("��ϣ��û��ֵ: %d\n", data);
	}
}
int main()
{
	//Ҫ�����Ĺ�ϣ��
	table _table;
	table_init(&_table);
	for (int i = 1; i < 200; i++) {
		add(&_table, i);
	}
	traverse(&_table, print);
	printf("\n");
	search_key(&_table, 10);
	search_key(&_table, 99);

	//ɾ���ؼ���
	remove(&_table, 10);
	printf("ɾ���ؼ���10�Ժ�");
	search_key(&_table, 10);

	printf("ɾ���ؼ���20�Ժ�");
	remove(&_table, 20);
	search_key(&_table, 20);

	printf("ɾ���ؼ���170�Ժ�");
	remove(&_table, 170);
	search_key(&_table, 170);

	printf("ɾ���ؼ���30�Ժ�");
	remove(&_table, 30);
	search_key(&_table, 30);

	printf("ɾ���ؼ���40�Ժ�");
	remove(&_table, 40);
	search_key(&_table, 40);

	printf("ɾ���ؼ���50�Ժ�");
	remove(&_table, 50);
	search_key(&_table, 50);

	traverse(&_table, print);
	system("PAUSE");
	return 0;
}

