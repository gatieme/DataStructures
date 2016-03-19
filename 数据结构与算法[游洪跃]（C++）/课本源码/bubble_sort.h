#ifndef __BUBBLE_SORT_H__
#define __BUBBLE_SORT_H__

template <class ElemType>
void BubbleSort(ElemType elem[], int n)
// 操作结果:在数组elem中用起泡排序进行排序
{
	for (int i = n - 1; i > 0; i--)
	{	// 第i趟起泡排序
		for (int j = 0; j < i; j++)
		{	// 比较elem[j]与elem[j + 1]
			if (elem[j] > elem[j + 1])
			{	// 如出现逆序,则交换elem[j]和elem[j + 1]
				Swap(elem[j], elem[j + 1]);
			}
		}
	}
}



#endif

