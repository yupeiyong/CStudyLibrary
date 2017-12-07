// CommonSubstring.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "stdlib.h"
#include <string.h> 
//������Ӵ�����

/*
�����ⷨ �C ���ü�����
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
��̬�滮�� �C �ռ任ʱ��

����һ���������ķ�����һ���ܲ���������ˣ����������ϱߵĽⷨ�ش�������϶�����õ���ɣ�
���Թٻ��ǻ�����û�и��õĽⷨ�أ����������ⷨ��Ȼ�������ŵģ�������Ȼ���Դ����ҵ�һ���Ľ������������ѷ������Ӵ��Ƚ����кܶ���ظ��ıȽϡ�

�����ٱȽ���i��j�ֱ�Ϊ��ʼ���ַ���ʱ���п��ܻ����i+1��j+1�Լ�i+2��j+2λ�õ��ַ��ıȽϣ����ڱȽ�i+1��j+1�ֱ�Ϊ��ʼ���ַ���ʱ��
��Щ�ַ��ֻᱻ�Ƚ�һ���ˡ�Ҳ����˵�������зǳ����Ƶ������⣬��������֮�������ص�����͸���̬�滮����Ӧ���ṩ��������

�����ⷨ�Ǵ��ַ������˿�ʼ��Ѱ�����ڻ���˼ά�������ַ���β���Ӵ������ö�̬�滮����

���������ַ����ֱ�Ϊs��t��s[i]��t[j]�ֱ��ʾ���i�͵�j���ַ�(�ַ�˳���0��ʼ)������L[i, j]��ʾ��s[i]��s[j]Ϊ��β����ͬ�Ӵ�����󳤶ȡ�
Ӧ�ò��ѵ��Ƴ�L[i, j]��L[i+1,j+1]֮��Ĺ�ϵ����Ϊ������ʵֻ��s[i+1]��t[j+1]��һ���ַ�����s[i+1]��t[j+1]��ͬ����ôL[i+1, j+1]��ȻӦ����0����Ϊ�κ�������Ϊ��β���Ӵ�����������ȫ��ͬ�������s[i+1]��t[j+1]��ͬ����ô��ֻҪ����s[i]��t[j]��β�����ͬ�Ӵ�֮��ֱ������������ַ����ɣ������Ϳ����ó�������һλ���ϲ��������������Ҳ�͵õ�L[i+1,j+1]=(s[i]==t[j]?L[i,j]+1:0)�����Ĺ�ϵ��

������ҪС�ĵľ����ٽ�λ�ã����������ַ������κ�һ���ǿմ�����ô������Ӵ��ĳ���ֻ����0��
��iΪ0ʱ��L[0,j]Ӧ���ǵ���L[-1,j-1]�ټ���s[0]��t[j]�ṩ��ֵ����L[-1,j-1]������Ч����������s[-1]�ǿ��ַ�Ҳ�ͱ����ǰ��һ���ٽ������
�����Ϳ�֪L[-1,j-1]==0������L[0,j]=(s[0]==t[j]?1:0)������jΪ0Ҳ��һ���ģ�ͬ���ɵ�L[i,0]=(s[i]==t[0]?1:0)��

1���߽�(��ռ䣬Ҷ���)
	str1[i]!=str2[j]�������ȵ���0
2��������
	str1[i]��str2[j]�Ƚϣ���str1[i-1]��str2[j-1]�Ƚ�����ͬ��������
3�������ӽṹ

4���ظ�������
	���� str1[2]��str2[2]�Ƚϣ����ܻ���ж��
5���������ȽϽ��
	�ö�ά���鱣����������
	table[m,n],m,n�������������ַ�������
*/

int getlongestCommonSubstring2(const char str1[], const char str2[])
{
	size_t size1 = strlen(str1);
	size_t size2 = strlen(str2);
	if (size1 == 0 || size2 == 0) return 0;

	int**table;

	table = (int**)malloc(sizeof(int*)*size1);
	for (int i = 0; i < size1; i++)
	{
		*(table + i) = (int*)malloc(sizeof(int)*size2);
	}
	for (int j = 0; j < size2; ++j)
	{
		table[0][j] = (str1[0] == str2[j] ? 1 : 0);
	}
	for (int i = 1; i < size1; i++) {
		table[i][0] = str1[i] == str2[0] ? 1 : 0;
		for (int j = 1; j < size2; j++) {
			if (str1[i] == str2[j]) {
				table[i][j] = table[i - 1][j - 1] + 1;
			}
			else {
				table[i][j] = 0;
			}
		}
	}

	int longest = 0;
	for (int i = 0; i < size1; i++) {
		for (int j = 0; j < size2; j++) {
			printf("%d ", table[i][j]);
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
	1��������� O(n��4�η�)
	*/
	char str1[] = "abceab";
	char str2[] = "xyceaab";
	int longest1 = getlongestCommonSubstring(str1, str2);
	printf("������������ַ�������%d\n", longest1);

	/*
	2����̬�滮��� O(n��2�η�)
	*/
	longest1 = getlongestCommonSubstring2(str1, str2);
	printf("��̬�滮��������ַ�������%d\n", longest1);

	system("PAUSE");
	return 0;
}

