#ifndef __RADIX_SORT_H__
#define __RADIX_SORT_H__

#include "lk_list.h"			// 线性链表

template <class ElemType>
void Distribute(ElemType elem[], int n, int r, int d, int i, LinkList<ElemType> list[])
// 初始条件: r为基数,d为关键字位数,list[0 .. r - 1]为被分配的线性表数组
// 操作结果: 进行第i趟分配
{
	for (int power = (int)pow((double)r, i - 1), j = 0; j < n; j++)
	{	// 进行第i起分配
		int index = (elem[j] / power) % r;		
		list[index].Insert(list[index].Length() + 1, elem[j]); 
	}
}

template <class ElemType>
void Colect(ElemType elem[], int n, int r, int d, int i, LinkList<ElemType> list[])
// 初始条件: r为基数,d为关键字位数,list[0 .. r - 1]为被分配的线性表数组
// 操作结果: 进行第i趟收集
{
	for (int k = 0, j = 0; j < r; j++)
	{	// 进行第i起分配
		ElemType tmpElem;
		while (!list[j].Empty())
		{	// 收集list[j]
			list[j].Delete(1, tmpElem);
			elem[k++] = tmpElem;
		}
	}
}

template <class ElemType>
void RadixSort(ElemType elem[], int n, int r, int d)
// 初始条件: r为基数,d为关键字位数
// 操作结果: 对elem进行基数排序
{
	LinkList<ElemType> *list;	// 用于存储被分配的线性表数组
	list = new LinkList<ElemType>[r];
	for (int i = 1; i <= d; i++)
	{	// 第i趟分配与收集
		Distribute(elem, n, r, d, i, list);	// 分配
		Colect(elem, n, r, d, i, list);		// 收集
	}
	delete []list;
}

#endif

