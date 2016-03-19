#ifndef __KMP_MATCH_H__
#define __KMP_MATCH_H__

#include "string.h"				// 串类

// KMP匹配算法
void getNext(const String &P, int next[])
// 操作结果: 求模式串P的next数组的元素值
{
	next[0] = -1;				// 由next[0] = -1开始进行递推
	int j = 0, k = -1;			// next[j] = k成立的初始情况
	while (j < P.Length() - 1)		
	{	// 数组next的下标范围为0 ~ P.Length() - 1, 通过递推方式求得next[j+1]的值
		if (k == -1)
		{	// k == -1只在j == 0时发生
			next[j+1]=0;		// next[j+1]=next[1] = 0
			j=1; k = 0;			// 由于已求得next[1] = 0,所以j = 1, k = 0
		}
		else if (P[k] == P[j])
		{	// 此时next[j+1] = next[j]+1
			next[j+1]=k+1;		// 由于P[k] == P[j],所以next[j+1] = next[j]+1 = k + 1
			j++; k++;			// 由于已求得next[j+1]=k+1,所以j更新为++j,k更新为++k
		}
		else
		{	// P[k]与P[j]不匹配
			k = next[k];		// 寻求新的匹配字符
		}
	}
}


int KMPIndexHelp(const String &T, const String &P, int pos, int next[])
// 操作结果: 通过next数组查找模式串P第一次在目标串T中从第pos个字符开始出现的位置
{
	int i = pos, j = 0;			// i为目标串T中的当前字符位置,j为模式串P的当前字符位置
	while (i < T.Length() && j < P.Length())
	{	
		if (j == -1)
		{	// 此时表明P中任何字符都不再与T[i]进行比较,下次P[0]与T[i+1]开始进行比较
			i++; j = 0;
		}
		else if (P[j] == T[i])
		{	// P[j]与T[i]匹配
			i++; j++;			// 模式串P与目标串T的当前位置向后移
		}
		else
		{	// P[j]与T[i]不匹配
			j = next[j];		// 寻找新的模式串P的匹配字符位置
		}
	}

	if (j < P.Length()) return -1;			// 匹配失败
	else return i - j;						// 匹配成功
}

int KMPIndex(const String &T, const String &P, int pos = 0)
// 操作结果: 查找模式串P第一次在目标串T中从第pos个字符开始出现的位置
{
	int *next = new int[P.Length()];		// 为数组next分配空间
	getNext(P, next);						// 求模式串P的next数组的元素值
	int result = KMPIndexHelp(T, P, pos, next);	
		// 返回模式串P第一次在目标串T中从第pos个字符开始出现的位置
	delete []next;							// 释next所占用的存储空间
	return result;
}

#endif

