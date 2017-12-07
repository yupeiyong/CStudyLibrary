// KnapSack.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include "stdlib.h"
/*
01背包问题（动态规划解法）
问题描述：

给定N中物品和一个背包。物品i的重量是Wi,其价值位Vi ，背包的容量为C。问应该如何选择装入背包的物品，使得转入背包的物品的总价值为最大？？

在选择物品的时候，对每种物品i只有两种选择，即装入背包或不装入背包。不能讲物品i装入多次，也不能只装入物品的一部分。因此，该问题被称为0-1背包问题。



问题分析：令V(i,j)表示在前i(1<=i<=n)个物品中能够装入容量为就j(1<=j<=C)的背包中的物品的最大价值，则可以得到如下的动态规划函数:

(1)   V(i,0)=V(0,j)=0

(2)A   V(i,j)=V(i-1,j)  j<wi

(2)B   V(i,j)=max{V(i-1,j) ,V(i-1,j-wi)+vi) } j>wi

(2)A式表明：如果第i个物品的重量大于背包的容量，则装人前i个物品得到的最大价值和装入前i-1个物品得到的最大价是相同的，即物品i不能装入背包；
(2)B式表明:如果第i个物品的重量小于背包的容量，则会有一下两种情况：
	(a)如果把第i个物品装入背包，则背包物品的价值等于第i-1个物品装入容量位j-wi 的背包中的价值加上第i个物品的价值vi;
	(b)如果第i个物品没有装入背包，则背包中物品价值就等于把前i-1个物品装入容量为j的背包中所取得的价值。
		显然，取二者中价值最大的作为把前i个物品装入容量为j的背包中的最优解。

有很多子问题重叠，比如knapsack(3)就执行3次
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
0代表不选择，1代表选择

1、边界(解空间，叶结点)
	叶结点就为边界
2、子问题
	knapsack[i]和knapsack[i-1]比较，和knapsack[i-1]与knapsack[i-2]比较是相同的子问题
3、最优子结构
	V(i,j)=max{V(i-1,j) ,V(i-1,j-wi)+vi) } j>wi
4、重复子问题
	比如 knapsack[i]，可能会进行多次
5、构造表保存比较结果
	用二维数组保存连续长度
	table[m,n],m,n分明代表两个字符串长度

*/

//背包最大价值
int maxValues[200][200];

int max(int x, int y) {
	if (x > y)return x;
	return y;
}
/*
	knapsackCount:放物品的背包数量
	weights：放物品的背包重量列表
	values：放物品的背包价值列表
	maxWeight：可以取的最大重量
*/
int getMaxValue(int knapsackCount,int*weights, int*values, int maxWeight) {
	//先初始化叶结点
	//背包数量为行
	for (int i = 0; i <= knapsackCount; i++){
		maxValues[i][0] = 0;
	}
	//最大重量为列
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
	//放物品的背包数量
	int knapsackCount = 5;
	//最大重量
	int maxWeight = 12;

	//int *weights;
	//weights = (int*)malloc(sizeof(int)*knapsackCount);
	//printf("背包重量：\n");
	//for (int i = 0; i < knapsackCount; i++) {
	//	int r =abs(rand());
	//	r = r % 10;
	//	r = r == 0 ? r + 9 : r;
	//	weights[i] = r ;
	//	printf("%d ", r);
	//}
	//printf("\n背包价值：\n");
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
	printf("背包重量：\n{6,3,2,7,9}\n");
	printf("背包价值：\n{ 16,23,12,7,18 }\n");
	int values[5] = { 16,23,12,7,18 };
	int maxValue = getMaxValue(knapsackCount, weights, values, maxWeight);
	printf("能取最大重量：%d，最大价值：%d",maxWeight, maxValue);
	system("PAUSE");
	return 0;
}

