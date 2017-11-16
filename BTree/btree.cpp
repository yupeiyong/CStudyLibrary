// BTree.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include <stdlib.h>  
#include <stdio.h>  
#include "btree.h"  

btree search(typekey, btree);
btree insert(typekey, btree);
btree remove(typekey, btree);
int height(btree);
int count(btree);
double payload(btree);
btree deltree(btree);

static void InternalInsert(typekey, btree);
static void InsInNode(btree, int);
static void SplitNode(btree, int);
static btree NewRoot(btree);

static void InternalDelete(typekey, btree);
static void JoinNode(btree, int);
static void MoveLeftNode(btree t, int);
static void MoveRightNode(btree t, int);
static void DelFromNode(btree t, int);
static btree FreeRoot(btree);

static btree delall(btree);
static void Error(int, typekey);

int btree_disp; /* ����ʱ�ҵ��ļ��ڽڵ��е�λ�� */
char * InsValue = NULL; /* ��Ҫ��ļ����Ӧ��ֵ */
static int flag; /* �ڵ�������־ */
static int btree_level = 0; /* ��·���ĸ߶� */
static int btree_count = 0; /* ��·���ļ����� */
static int node_sum = 0;   /* ��·���Ľڵ����� */
static int level; /* ��ǰ���ʵĽڵ������ĸ߶� */
static btree NewTree; /* �ڽڵ�ָ��ʱ��ָ���½��Ľڵ� */
static typekey InsKey; /* Ҫ����ļ� */

btree search(typekey key, btree t)
{
	int i, j, m;
	level = btree_level - 1;
	while (level >= 0) {
		for (i = 0, j = t->d - 1; i < j; m = (j + i) / 2, (key > t->k[m]) ? (i = m + 1) : (j = m));
		if (key == t->k[i]) {
			btree_disp = i;
			return t;
		}
		if (key > t->k[i]) /* i == t->d-1 ʱ�п��ܳ��� */
			i++;
		t = t->p[i];
		level--;
	}
	return NULL;
}

btree insert(typekey key, btree t)
{
	level = btree_level;
	InternalInsert(key, t);

	if (flag == 1)   /* ���ڵ���֮�������ָ�����������ڵ� */
		t = NewRoot(t);     /* ���ĸ߶����� */
	return t;
}

void InternalInsert(typekey key, btree t)
{
	int i, j, m;

	level--;
	if (level < 0) { /* ���������ĵײ�: ָ��Ҫ���Ĳ��� */
		NewTree = NULL; /* �����û�ж�Ӧ������ */
		InsKey = key; /* ���µײ��Ҷ�ӽڵ����Ӽ�ֵ+�������� */
		btree_count++;
		flag = 1; /* ָʾ�ϲ�ڵ�ѷ��صļ��������� */
		return;
	}
	for (i = 0, j = t->d - 1; i < j; m = (j + i) / 2, (key > t->k[m]) ? (i = m + 1) : (j = m));
	if (key == t->k[i]) {
		Error(1, key); /* ���Ѿ������� */
		flag = 0;
		return;
	}
	if (key > t->k[i]) /* i == t->d-1 ʱ�п��ܳ��� */
		i++;
	InternalInsert(key, t->p[i]);

	if (flag == 0)
		return;
	/* ���¼�Ҫ���뵽��ǰ�ڵ��� */
	if (t->d < 2 * M) {/* ��ǰ�ڵ�δ�� */
		InsInNode(t, i); /* �Ѽ�ֵ+�����Բ��뵱ǰ�ڵ��� */
		flag = 0; /* ָʾ�ϲ�ڵ�û����Ҫ����ļ�ֵ+������������̽��� */
	}
	else /* ��ǰ�ڵ���������ָ����ҳ�沢�Ѽ�ֵ+�����Բ��뵱ǰ�ڵ��� */
		SplitNode(t, i); /* ����ָʾ�ϲ�ڵ�ѷ��صļ�ֵ+������������ */
}

/*
* ��һ�����Ͷ�Ӧ������������һ���ڵ���
*/
void InsInNode(btree t, int d)
{
	int i;
	/* �����д���Ҫ����ļ�ֵ�ļ��Ͷ�Ӧ������������ */
	for (i = t->d; i > d; i--) {
		t->k[i] = t->k[i - 1];
		t->v[i] = t->v[i - 1];
		t->p[i + 1] = t->p[i];
	}
	/* ������������� */
	t->k[i] = InsKey;
	t->p[i + 1] = NewTree;
	t->v[i] = InsValue;
	t->d++;
}
/*
* ǰ����Ҫ����һ�����Ͷ�Ӧ�������������ұ��ڵ��Ѿ���
* ���·ָ�����ڵ㣬������Ͷ�Ӧ����������
* �����ϲ㷵��һ��Ҫ������Ͷ�Ӧ��������
*/
void SplitNode(btree t, int d)
{
	int i, j;
	btree temp;
	typekey temp_k;
	char *temp_v;
	/* �����½ڵ� */
	temp = (btree)malloc(sizeof(node));
	/*
	*   +---+--------+-----+-----+--------+-----+
	*   | 0 | ...... |   M   | M+1 | ...... |2*M-1|
	*   +---+--------+-----+-----+--------+-----+
	*   |<-       M+1     ->|<-         M-1     ->|
	*/
	if (d > M) { /* Ҫ���뵱ǰ�ڵ���Ұ벿�� */
				 /* �Ѵ� 2*M-1 �� M+1 �� M-1 ����ֵ+������ת�Ƶ��½ڵ���,
				 * ����ΪҪ����ļ�ֵ+�����ճ�λ�� */
		for (i = 2 * M - 1, j = M - 1; i >= d; i--, j--) {
			temp->k[j] = t->k[i];
			temp->v[j] = t->v[i];
			temp->p[j + 1] = t->p[i + 1];
		}
		for (i = d - 1, j = d - M - 2; j >= 0; i--, j--) {
			temp->k[j] = t->k[i];
			temp->v[j] = t->v[i];

			temp->p[j + 1] = t->p[i + 1];
		}
		/* �ѽڵ����������ת�Ƴ��½ڵ���������� */
		temp->p[0] = t->p[M + 1];
		/* ���½ڵ��в������������ */
		temp->k[d - M - 1] = InsKey;
		temp->p[d - M] = NewTree;
		temp->v[d - M - 1] = InsValue;
		/* ����Ҫ�����ϲ�ڵ�ļ���ֵ */
		InsKey = t->k[M];
		InsValue = t->v[M];

	}
	else { /* d <= M */
		   /* �Ѵ� 2*M-1 �� M �� M ����ֵ+������ת�Ƶ��½ڵ��� */
		for (i = 2 * M - 1, j = M - 1; j >= 0; i--, j--) {
			temp->k[j] = t->k[i];
			temp->v[j] = t->v[i];
			temp->p[j + 1] = t->p[i + 1];
		}
		if (d == M) /* Ҫ���뵱ǰ�ڵ�����м� */
					/* ��Ҫ�����������Ϊ�½ڵ���������� */
			temp->p[0] = NewTree;
		/* ֱ�Ӱ�Ҫ����ļ���ֵ���ظ��ϲ�ڵ� */
		else { /* (d<M) Ҫ���뵱ǰ�ڵ����벿�� */
			   /* �ѽڵ㵱ǰ����������ת�Ƴ��½ڵ���������� */
			temp->p[0] = t->p[M];
			/* ����Ҫ�����ϲ�ڵ�ļ���ֵ */
			temp_k = t->k[M - 1];
			temp_v = t->v[M - 1];
			/* �����д���Ҫ����ļ�ֵ�ļ��Ͷ�Ӧ������������ */
			for (i = M - 1; i > d; i--) {
				t->k[i] = t->k[i - 1];
				t->v[i] = t->v[i - 1];
				t->p[i + 1] = t->p[i];
			}
			/* �ڽڵ��в������������ */
			t->k[d] = InsKey;
			t->p[d + 1] = NewTree;
			t->v[d] = InsValue;
			/* ����Ҫ�����ϲ�ڵ�ļ���ֵ */
			InsKey = temp_k;
			InsValue = temp_v;
		}
	}
	t->d = M;
	temp->d = M;
	NewTree = temp;
	node_sum++;
}

btree remove(typekey key, btree t)
{
	level = btree_level;
	InternalDelete(key, t);
	if (t->d == 0)
		/* ���ڵ���ӽڵ�ϲ����¸��ڵ������Ŀ��֮���٣�
		* �����ڵ���û�м���ʱ��ֻ�����������������ܷǿ� */
		t = FreeRoot(t);
	return t;
}

void InternalDelete(typekey key, btree t)
{
	int i, j, m;
	btree l, r;
	int lvl;

	level--;
	if (level < 0) {
		Error(0, key); /* ����������δ�ҵ�Ҫɾ���ļ� */
		flag = 0;

		return;
	}
	for (i = 0, j = t->d - 1; i < j; m = (j + i) / 2, (key > t->k[m]) ? (i = m + 1) : (j = m));
	if (key == t->k[i]) { /* �ҵ�Ҫɾ���ļ� */
		if (t->v[i] != NULL)
			free(t->v[i]); /* �ͷ�����ڵ������ֵ */
		if (level == 0) { /* ������Ϊ���������λ��Ҷ�ӽڵ� */
			DelFromNode(t, i);
			btree_count--;
			flag = 1;
			/* ָʾ�ϲ�ڵ㱾�����ļ��������� */
			return;
		}
		else { /* �����λ�ڷ�Ҷ�ڵ� */
			lvl = level - 1;
			/* �ҵ�ǰ���ڵ� */
			r = t->p[i];
			while (lvl > 0) {
				r = r->p[r->d];
				lvl--;
			}
			t->k[i] = r->k[r->d - 1];
			t->v[i] = r->v[r->d - 1];
			r->v[r->d - 1] = NULL;
			key = r->k[r->d - 1];
		}
	}
	else if (key > t->k[i]) /* i == t->d-1 ʱ�п��ܳ��� */
		i++;
	InternalDelete(key, t->p[i]);
	/* ����ƽ�� */
	if (flag == 0)
		return;
	if (t->p[i]->d < M) {
		if (i == t->d) /* �����������з�����ɾ�� */
			i--; /* �������Ҽ�����������ƽ�� */
		l = t->p[i];
		r = t->p[i + 1];
		if (r->d > M)
			MoveLeftNode(t, i);
		else if (l->d > M)
			MoveRightNode(t, i);
		else {
			JoinNode(t, i);
			/* ����ָʾ�ϲ�ڵ㱾�����ļ��������� */
			return;
		}
		flag = 0;
		/* ָʾ�ϲ�ڵ㱾�����ļ�����û�м��٣�ɾ�����̽��� */
	}
}

/*
* �ϲ�һ���ڵ��ĳ������Ӧ����������
*/
void JoinNode(btree t, int d)
{
	btree l, r;
	int i, j;
	l = t->p[d];
	r = t->p[d + 1];

	/* ����������Ƶ����������� */
	l->k[l->d] = t->k[d];
	l->v[l->d] = t->v[d];
	/* ���������е����м�ֵ������ת�Ƶ������� */
	for (j = r->d - 1, i = l->d + r->d; j >= 0; j--, i--) {
		l->k[i] = r->k[j];
		l->v[i] = r->v[j];
		l->p[i] = r->p[j];
	}
	l->p[l->d + r->d + 1] = r->p[r->d];
	l->d += r->d + 1;
	/* �ͷ��������Ľڵ� */

	free(r);
	/* ��������ұߵļ��Ͷ�Ӧ������������ */
	for (i = d; i < t->d - 1; i++) {
		t->k[i] = t->k[i + 1];
		t->v[i] = t->v[i + 1];
		t->p[i + 1] = t->p[i + 2];
	}
	t->d--;
	node_sum--;
}
/*
* ��һ��������������������ת��һЩ����ʹ��������ƽ��
*/
void MoveLeftNode(btree t, int d)
{
	btree l, r;
	int m; /* Ӧת�Ƶļ�����Ŀ */
	int i, j;
	l = t->p[d];
	r = t->p[d + 1];
	m = (r->d - l->d) / 2;

	/* ����������Ƶ����������� */
	l->k[l->d] = t->k[d];
	l->v[l->d] = t->v[d];
	/* ������������������ת�Ƴ�����������������
	* �����������������ƶ� m-1 ����+������ */
	for (j = m - 2, i = l->d + m - 1; j >= 0; j--, i--) {
		l->k[i] = r->k[j];
		l->v[i] = r->v[j];
		l->p[i] = r->p[j];
	}
	l->p[l->d + m] = r->p[m - 1];
	/* ����������������������������λ���� */
	t->k[d] = r->k[m - 1];
	t->v[d] = r->v[m - 1];
	/* ���������е����м�ֵ���������� m ��λ�� */
	r->p[0] = r->p[m];
	for (i = 0; i < r->d - m; i++) {
		r->k[i] = r->k[i + m];
		r->v[i] = r->v[i + m];
		r->p[i] = r->p[i + m];
	}
	r->p[r->d - m] = r->p[r->d];
	l->d += m;
	r->d -= m;
}
/*
* ��һ��������������������ת��һЩ����ʹ��������ƽ��
*/
void MoveRightNode(btree t, int d)
{
	btree l, r;
	int m; /* Ӧת�Ƶļ�����Ŀ */
	int i, j;
	l = t->p[d];
	r = t->p[d + 1];

	m = (l->d - r->d) / 2;
	/* ���������е����м�ֵ���������� m ��λ�� */
	r->p[r->d + m] = r->p[r->d];
	for (i = r->d - 1; i >= 0; i--) {
		r->k[i + m] = r->k[i];
		r->v[i + m] = r->v[i];
		r->p[i + m] = r->p[i];
	}
	/* ����������Ƶ����������� */
	r->k[m - 1] = t->k[d];
	r->v[m - 1] = t->v[d];
	/* ������������������ת�Ƴ����������������� */
	r->p[m - 1] = l->p[l->d];
	/* �����������������ƶ� m-1 ����+������ */
	for (i = l->d - 1, j = m - 2; j >= 0; j--, i--) {
		r->k[j] = l->k[i];
		r->v[j] = l->v[i];
		r->p[j] = l->p[i];
	}
	/* �������������Ҽ��������������λ���� */
	t->k[d] = l->k[i];
	t->v[d] = l->v[i];
	l->d -= m;
	r->d += m;
}
/*
* ��һ�����Ͷ�Ӧ����������һ���ڵ���ɾ��
*/
void DelFromNode(btree t, int d)
{
	int i;
	/* �����д���Ҫɾ���ļ�ֵ�ļ����� */
	for (i = d; i < t->d - 1; i++) {
		t->k[i] = t->k[i + 1];
		t->v[i] = t->v[i + 1];
	}
	t->d--;
}
/*
* ����������������һ�����ĸ��ڵ�
*/
btree NewRoot(btree t)
{
	btree temp;
	temp = (btree)malloc(sizeof(node));
	temp->d = 1;
	temp->p[0] = t;
	temp->p[1] = NewTree;

	temp->k[0] = InsKey;
	temp->v[0] = InsValue;
	btree_level++;
	node_sum++;
	return(temp);
}
/*
* �ͷŸ��ڵ㣬������������������
*/
btree FreeRoot(btree t)
{
	btree temp;
	temp = t->p[0];
	free(t);
	btree_level--;
	node_sum--;
	return temp;
}

void Error(int f, typekey key)
{
	if (f)
		printf("Btrees error: Insert %d!\n", key);
	else
		printf("Btrees error: delete %d!\n", key);
}

int height(btree t)
{
	return btree_level;
}

int count(btree t)
{
	return btree_count;
}
double payload(btree t)
{
	if (node_sum == 0)
		return 1;
	return (double)btree_count / (node_sum*(2 * M));
}
btree deltree(btree t)
{
	level = btree_level;
	btree_level = 0;
	return delall(t);

}
btree delall(btree t)
{
	int i;
	level--;
	if (level >= 0) {
		for (i = 0; i < t->d; i++)
			if (t->v[i] != NULL)
				free(t->v[i]);
		if (level > 0)
			for (i = 0; i <= t->d; i++)
				t->p[i] = delall(t->p[i]);
		free(t);
	}
	return NULL;
}
//int main()
//{
//	return 0;
//}

