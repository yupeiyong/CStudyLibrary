// DynamicProgramming.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "stdlib.h"
#define NIL -1  
#define MAX 100  

//斐波那契数
/*
有很多子问题重叠，比如fib(3)就执行3次
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
动态规划是一种典型的算法，它可以通过将一个给定的复杂问题分割为子问题，然后将子问题的结果进行存储以免再次计算相同的结果。
当问题具有下面两个属性（特征）的时候，那么意思就是说这个问题可以用动态规划的思想来解决。

1) 重叠的子问题
2) 最优的子结构

在计算斐波那契数时，有很多重复计算（重叠的子问题），可以考虑用动态规划来写
*/

/*
a) 记忆法 (自顶向下):
b) 制表法 (自底向上):

*/


int lookup[MAX];

/* Function to initialize NIL values in lookup table */
void _initialize()
{
	int i;
	for (i = 0; i < MAX; i++)
		lookup[i] = NIL;
}

/* 记忆法 (自顶向下) */
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

/* 制表法 (自底向上),用表格记录计算结果，避免重复计算 */
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

