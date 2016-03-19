#ifndef __SIMPLE_MERGE_SORT_H__
#define __SIMPLE_MERGE_SORT_H__

template <class ElemType>
void SimpleMerge(ElemType elem[], int low, int mid, int high)
// 操作结果:将有序子序列elem[low .. mid]和elem[mid + 1 .. midhigh]归并为新的
//	有序序列elem[low .. high]
{
	ElemType *tmpElem = new ElemType[high + 1]; // 定义临时数组
	
	int i, j, k;								// 临时变量 
	for (i = low, j = mid + 1, k = low; i <= mid && j <= high; k++)
	{	// i为归并时elem[low .. mid]当前元素的下标,j为归并时elem[mid + 1 .. high]当前元素
		// 的下标,k为tmpElem中当前元素的下标
		if (elem[i] <= elem[j])
		{	// elem[i]较小,先归并
			tmpElem[k] = elem[i];
			i++;
		}
		else
		{	// elem[j]较小,先归并
			tmpElem[k] = elem[j];
			j++;
		}
	}

	for (; i <= mid; i++, k++)
	{	// 归并elem[low .. mid]中剩余元素
		tmpElem[k] = elem[i];
	}

	for (; j <= high; j++, k++)
	{	// 归并elem[mid + 1 .. high]中剩余元素
		tmpElem[k] = elem[j];
	}

	for (i = low; i <= high; i++)
	{	// 将tmpElem[low .. high]复制到elem[low .. high]
		elem[i] = tmpElem[i];
	}

	delete []tmpElem;		// 释放tmpElem所点用空间
}

template <class ElemType>
void SimpleMergeSortHelp(ElemType elem[], int low, int high)
// 操作结果:对elem[low .. high]进行简单归并排序
{
	if (low < high)
	{	
		int mid = (low + high) / 2;			
			// 将elem[low .. high]平分为elem[low .. mid]和elem[mid + 1 .. high]
		SimpleMergeSortHelp(elem, low, mid);		// 对elem[low .. mid]进行简单归并排序
		SimpleMergeSortHelp(elem, mid + 1, high);	// 对elem[mid + 1 .. high]进行简单归并排序
		SimpleMerge(elem, low, mid, high);			// 对elem[low .. mid]和elem[mid + 1 .. high]进行归并
	}
}

template <class ElemType>
void SimpleMergeSort(ElemType elem[], int n)
// 操作结果:对elem进行简单归并排序
{
	SimpleMergeSortHelp(elem, 0, n - 1);
}

#endif

