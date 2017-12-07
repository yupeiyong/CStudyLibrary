// KnapSack.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include "stdafx.h"
#include "stdlib.h"
/*
01�������⣨��̬�滮�ⷨ��
����������

����N����Ʒ��һ����������Ʒi��������Wi,���ֵλVi ������������ΪC����Ӧ�����ѡ��װ�뱳������Ʒ��ʹ��ת�뱳������Ʒ���ܼ�ֵΪ��󣿣�

��ѡ����Ʒ��ʱ�򣬶�ÿ����Ʒiֻ������ѡ�񣬼�װ�뱳����װ�뱳�������ܽ���Ʒiװ���Σ�Ҳ����ֻװ����Ʒ��һ���֡���ˣ������ⱻ��Ϊ0-1�������⡣



�����������V(i,j)��ʾ��ǰi(1<=i<=n)����Ʒ���ܹ�װ������Ϊ��j(1<=j<=C)�ı����е���Ʒ������ֵ������Եõ����µĶ�̬�滮����:

(1)   V(i,0)=V(0,j)=0

(2)A   V(i,j)=V(i-1,j)  j<wi

(2)B   V(i,j)=max{V(i-1,j) ,V(i-1,j-wi)+vi) } j>wi

(2)Aʽ�����������i����Ʒ���������ڱ�������������װ��ǰi����Ʒ�õ�������ֵ��װ��ǰi-1����Ʒ�õ�����������ͬ�ģ�����Ʒi����װ�뱳����
(2)Bʽ����:�����i����Ʒ������С�ڱ����������������һ�����������
	(a)����ѵ�i����Ʒװ�뱳�����򱳰���Ʒ�ļ�ֵ���ڵ�i-1����Ʒװ������λj-wi �ı����еļ�ֵ���ϵ�i����Ʒ�ļ�ֵvi;
	(b)�����i����Ʒû��װ�뱳�����򱳰�����Ʒ��ֵ�͵��ڰ�ǰi-1����Ʒװ������Ϊj�ı�������ȡ�õļ�ֵ��
		��Ȼ��ȡ�����м�ֵ������Ϊ��ǰi����Ʒװ������Ϊj�ı����е����Ž⡣

�кܶ��������ص�������knapsack(3)��ִ��3��
									knapsack(5)
									/             \
								   /                \
								 0/                    \1
								 /						\
							   /                         \
							  /						      \
				  knapsack(4)									knapsack(3)
			  /                   \                           /            \
			0/                     \1                       0/              \1
			/						\						/                \
		knapsack(3)               knapsack(2)             knapsack(2)       knapsack(1)
	  0/        \1                0/            \1          0/           \1
	knapsack(2)   knapsack(1)  knapsack(1) knapsack(0) knapsack(1) knapsack(0)
 0/                \1
knapsack(1) knapsack(0)
0����ѡ��1����ѡ��

1���߽�(��ռ䣬Ҷ���)
	Ҷ����Ϊ�߽�
2��������
	knapsack[i]��knapsack[i-1]�Ƚϣ���knapsack[i-1]��knapsack[i-2]�Ƚ�����ͬ��������
3�������ӽṹ
	V(i,j)=max{V(i-1,j) ,V(i-1,j-wi)+vi) } j>wi
4���ظ�������
	���� knapsack[i]�����ܻ���ж��
5���������ȽϽ��
	�ö�ά���鱣����������
	table[m,n],m,n�������������ַ�������

*/

//��������ֵ
int maxValues[200][200];

int max(int x, int y) {
	if (x > y)return x;
	return y;
}
/*
	knapsackCount:����Ʒ�ı�������
	weights������Ʒ�ı��������б�
	values������Ʒ�ı�����ֵ�б�
	maxWeight������ȡ���������
*/
int getMaxValue(int knapsackCount,int*weights, int*values, int maxWeight) {
	//�ȳ�ʼ��Ҷ���
	//��������Ϊ��
	for (int i = 0; i <= knapsackCount; i++){
		maxValues[i][0] = 0;
	}
	//�������Ϊ��
	for (int i = 0; i <= maxWeight; i++) {
		maxValues[0][i] = 0;
	}

	for (int i = 1; i < knapsackCount; i++) {
		for (int j = 1; j <= maxWeight; j++) {
			if (weights[i] > j) {
				maxValues[i][j] = maxValues[i - 1][j];
			}
			else {
				maxValues[i][j] =max(maxValues[i-1][j-weights[i]]+values[i], maxValues[i - 1][j]);
			}
		}
	}

	for (int i = 0; i <= knapsackCount; i++) {
		for (int j = 0; j <= maxWeight; j++) {
			printf("% d", maxValues[i][j]);
		}
	}

	return maxValues[knapsackCount-1][maxWeight];
}
int main()
{
	//����Ʒ�ı�������
	int knapsackCount = 5;
	//�������
	int maxWeight = 12;

	//int *weights;
	//weights = (int*)malloc(sizeof(int)*knapsackCount);
	//printf("����������\n");
	//for (int i = 0; i < knapsackCount; i++) {
	//	int r =abs(rand());
	//	r = r % 10;
	//	r = r == 0 ? r + 9 : r;
	//	weights[i] = r ;
	//	printf("%d ", r);
	//}
	//printf("\n������ֵ��\n");
	//int *values;
	//values = (int*)malloc(sizeof(int)*knapsackCount);

	//for (int i = 0; i < knapsackCount; i++) {
	//	int r = abs(rand());
	//	r = r % 20;
	//	r = r == 0 ? r + 11 : r;
	//	values[i] = r;
	//	printf("%d ", r);
	//}
	int weights[5] = {6,3,2,7,9};
	printf("����������\n{6,3,2,7,9}\n");
	printf("������ֵ��\n{ 16,23,12,7,18 }\n");
	int values[5] = { 16,23,12,7,18 };
	int maxValue = getMaxValue(knapsackCount, weights, values, maxWeight);
	printf("��ȡ���������%d������ֵ��%d",maxWeight, maxValue);
	system("PAUSE");
	return 0;
}

