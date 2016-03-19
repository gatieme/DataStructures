#ifndef __QUICK_SORT_H__
#define __QUICK_SORT_H__

template <class ElemType>
int Partition(ElemType elem[], int low, int high)
// 操作结果:交换elem[low .. high]中的元素,使枢轴移动到适当置,要求在枢轴之前的元素
//	不大于枢轴,在枢轴之后的元素不小于枢轴的,并返回枢轴的位置

{
	while (low < high)
	{
		while (low < high && elem[high] >= elem[low])
		{	// elem[low]为枢轴,使high右边的元素不小于elem[low]
			high--;
		}
		Swap(elem[low], elem[high]);

		while (low < high && elem[low] <= elem[high])
		{	// elem[high]为枢轴,使low左边的元素不大于elem[high]
			low++;
		}
		Swap(elem[low], elem[high]);
	}
	return low;	// 返回枢轴位置
}

template <class ElemType>
void QuickSortHelp(ElemType elem[], int low, int high)
// 操作结果:对数组elem[low .. high]中的记录进行快速排序
{
	if (low < high)
	{	// 子序列elem[low .. high]长度大于1
		int pivotLoc = Partition(elem, low, high);	// 进行一趟找分
		QuickSortHelp(elem, low, pivotLoc - 1);		// 对子表elem[low, pivotLoc - 1]递归排序
		QuickSortHelp(elem, pivotLoc + 1, high);	// 对子表elem[pivotLoc + 1, high]递归排序
	}
}

template <class ElemType>
void QuickSort(ElemType elem[], int n)
// 操作结果:对数组elem进行快速排序
{
	QuickSortHelp(elem, 0, n - 1);
}

#endif

