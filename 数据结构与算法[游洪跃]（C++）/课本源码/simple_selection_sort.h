#ifndef __SIMPLE_SELECT_SORT_H__
#define __SIMPLE_SELECT_SORT_H__

template <class ElemType>
void SimpleSelectionSort(ElemType elem[], int n)
// 操作结果:对数组elem作简单选择排序
{
	for ( int i = 0; i < n - 1; i++)
	{	// 第i趟简单选择排序
		int lowIndex = i;			// 记录elem[i .. n - 1]中最小元素小标
		for (int j = i + 1; j < n; j++)
		{
			if (elem[j] < elem[lowIndex])
			{	// 用lowIndexd存储当前寻到的最小元素小标
				lowIndex = j;
			}
		}
		Swap(elem[i], elem[lowIndex]);	// 交换elem[i], elem[lowIndex]
	}
}

#endif

