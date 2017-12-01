// DynamicProgramming.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "stdlib.h"
#define NIL -1  
#define MAX 100  

//쳲�������
/*
�кܶ��������ص�������fib(3)��ִ��3��
				fib(5)
				/             \
			fib(4)                fib(3)
			/      \                /     \
		fib(3)      fib(2)         fib(2)    fib(1)
		/     \        /    \       /    \
	fib(2)   fib(1)  fib(1) fib(0) fib(1) fib(0)
	/    \
fib(1) fib(0)  */
int  fib(int n) {
	if (n <= 1)return n;
	return fib(n - 1) + fib(n - 2);
}


/*
��̬�滮��һ�ֵ��͵��㷨��������ͨ����һ�������ĸ�������ָ�Ϊ�����⣬Ȼ��������Ľ�����д洢�����ٴμ�����ͬ�Ľ����
��������������������ԣ���������ʱ����ô��˼����˵�����������ö�̬�滮��˼���������

1) �ص���������
2) ���ŵ��ӽṹ

�ڼ���쳲�������ʱ���кܶ��ظ����㣨�ص��������⣩�����Կ����ö�̬�滮��д
*/

/*
a) ���䷨ (�Զ�����):
b) �Ʊ� (�Ե�����):

*/


int lookup[MAX];

/* Function to initialize NIL values in lookup table */
void _initialize()
{
	int i;
	for (i = 0; i < MAX; i++)
		lookup[i] = NIL;
}

/* ���䷨ (�Զ�����) */
int fib1(int n)
{
	if (lookup[n] == NIL)
	{
		if (n <= 1)
			lookup[n] = n;
		else
			lookup[n] = fib1(n - 1) + fib1(n - 2);
	}

	return lookup[n];
}

/* �Ʊ� (�Ե�����),�ñ���¼�������������ظ����� */
int fib2(int n) {
	int* arr;
	arr = (int*)malloc(sizeof(int)*n + 1);
	arr[0] = 0;
	arr[1] = 1;
	int i;
	for (i = 2; i <= n; i++)
		arr[i] = arr[i - 1] + arr[i - 2];

	return arr[n];
}
int main()
{
	int result = fib(9);
	printf("%d\n", result);

	_initialize();
	result = fib1(9);
	printf("%d\n", result);

	result = fib2(9);
	printf("%d\n", result);

	system("PAUSE");
	return 0;
}

