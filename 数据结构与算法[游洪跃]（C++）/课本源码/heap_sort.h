#ifndef __HEAP_SORT_H__
#define __HEAP_SORT_H__

template <class ElemType>
void SiftAdjust(ElemType elem[], int low, int high)
// 操作结果:elem[low .. high]中记录除elem[low]以外都满足堆定义,调
//	整elem[low]使其elem[low .. high]成为一个大顶堆
{
	for (int f = low, i = 2 * low + 1; i <= high; i = 2 * i + 1)
	{	// f为被调整结点,i为f的最大孩子
		if (i < high && elem[i] < elem[i + 1])
		{	// 右孩子更大, i指向右孩子
			i++;
		}
		if (elem[f] >= elem[i])
		{	// 已成为大顶堆
			break;
		}
		Swap(elem[f], elem[i]);	// 交换elem[f], elem[i]
		f = i;					// 成为新的调整结点		
	}
}


template <class ElemType>
void HeapSort(ElemType elem[], int n)
// 操作结果:对数组elem进行堆排序
{
	int i;
	for (i = (n-2)/2; i >= 0; --i) 
	{	// 将elem[0 .. n - 1]调整成大顶堆
		SiftAdjust(elem, i, n - 1);
	};

	for (i = n - 1; i > 0; --i)
	{	// 第i趟堆排序
		Swap(elem[0], elem[i]);		
			// 将堆顶元素和当前未经排序的子序列elem[0 .. i]中最后一个元素交换
		SiftAdjust(elem, 0, i - 1);	// 将elem[0 .. i - 1]重新调整为大顶堆
	}
}

#endif

