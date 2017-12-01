// CommonSubstring.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "stdlib.h"
#include <string.h> 
//最长公共子串问题

/*
暴力解法 – 所得即所求
*/
int getlongestCommonSubstring(const char str1[], const char str2[])
{
	size_t size1 = strlen(str1);
	size_t size2 = strlen(str2);
	if (size1 == 0 || size2 == 0) return 0;

	int longest = 0;
	for (int i = 0; i < size1; i++) {
		for (int j = 0; j < size2; j++) {
			int m = i, n = j, l = 0;
			while (m < size1 && n < size2) {
				if (str1[m] != str2[n]) {
					break;
				}
				m++;
				n++;
				l++;
			}
			if (l > longest)longest = l;
		}
	}
	return longest;
}

/*
动态规划法 – 空间换时间

有了一个解决问题的方法是一件很不错的事情了，但是拿着上边的解法回答面试题肯定不会得到许可，
面试官还是会问有没有更好的解法呢？不过上述解法虽然不是最优的，但是依然可以从中找到一个改进的线索。不难发现在子串比较中有很多次重复的比较。

比如再比较以i和j分别为起始点字符串时，有可能会进行i+1和j+1以及i+2和j+2位置的字符的比较；而在比较i+1和j+1分别为起始点字符串时，
这些字符又会被比较一次了。也就是说该问题有非常相似的子问题，而子问题之间又有重叠，这就给动态规划法的应该提供了契机。

暴力解法是从字符串开端开始找寻，现在换个思维考虑以字符结尾的子串来利用动态规划法。

假设两个字符串分别为s和t，s[i]和t[j]分别表示其第i和第j个字符(字符顺序从0开始)，再令L[i, j]表示以s[i]和s[j]为结尾的相同子串的最大长度。
应该不难递推出L[i, j]和L[i+1,j+1]之间的关系，因为两者其实只差s[i+1]和t[j+1]这一对字符。若s[i+1]和t[j+1]不同，那么L[i+1, j+1]自然应该是0，因为任何以它们为结尾的子串都不可能完全相同；而如果s[i+1]和t[j+1]相同，那么就只要在以s[i]和t[j]结尾的最长相同子串之后分别添上这两个字符即可，这样就可以让长度增加一位。合并上述两种情况，也就得到L[i+1,j+1]=(s[i]==t[j]?L[i,j]+1:0)这样的关系。

最后就是要小心的就是临界位置：如若两个字符串中任何一个是空串，那么最长公共子串的长度只能是0；
当i为0时，L[0,j]应该是等于L[-1,j-1]再加上s[0]和t[j]提供的值，但L[-1,j-1]本是无效，但可以视s[-1]是空字符也就变成了前面一种临界情况，
这样就可知L[-1,j-1]==0，所以L[0,j]=(s[0]==t[j]?1:0)。对于j为0也是一样的，同样可得L[i,0]=(s[i]==t[0]?1:0)。

1、边界
	str1[i]!=str2[j]连续长度等于0
2、子问题
	str1[i]和str2[j]比较，和str1[i-1]与str2[j-1]比较是相同的子问题
3、最优子结构

4、重复子问题
	比如 str1[2]和str2[2]比较，可能会进行多次
5、构造表保存比较结果
	用二维数组保存连续长度
	table[m,n],m,n分明代表两个字符串长度
*/

int getlongestCommonSubstring2(const char str1[], const char str2[])
{
	size_t size1 = strlen(str1);
	size_t size2 = strlen(str2);
	if (size1 == 0 || size2 == 0) return 0;

	int**table;

	table = (int**)malloc(sizeof(int*)*size1);
	for (int i = 0; i<size1; i++)
	{
		*(table + i) = (int*)malloc(sizeof(int)*size2);
	}
	for (int j = 0; j < size2; ++j)
	{
		table[0][j] = (str1[0] == str2[j] ? 1 : 0);
	}
	for (int i = 1; i < size1; i++) {
		for (int j = 1; j < size2; j++) {
			table[i][0] = str1[i] == str2[j] ? 1 : 0;
			if (str1[i] == str2[j]) {
				table[i][j] = table[i - 1][j - 1] + 1;
			}
		}
	}
	int longest = 0;
	for (int i = 0; i < size1; i++) {
		for (int j = 0; j < size2; j++) {
			if (table[i][j] > longest) {
				longest = table[i][j];
			}
		}
	}

	return longest;
}
int main()
{
	/*
	1、暴力求解 O(n的4次方)
	*/
	char str1[] = "abceab";
	char str2[] = "xyceaab";
	int longest1 = getlongestCommonSubstring(str1, str2);
	printf("暴力求最长公共字符串长度%d\n", longest1);

	/*
	2、动态规划求解 O(n的4次方)
	*/
	longest1 = getlongestCommonSubstring2(str1, str2);
	printf("动态规划求最长公共字符串长度%d\n", longest1);

	system("PAUSE");
	return 0;
}

