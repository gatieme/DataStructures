#ifndef __INSERT_SORT_H__
#define __INSERT_SORT_H__

template <class ElemType>
void StraightInsertSort(ElemType elem[], int n)
// 操作结果:对数组elem作直接插入排序序
{
	for ( int i = 1; i < n; i++)
	{	// 第i趟直接插入排序
		ElemType e = elem[i];			// 暂存elem[i]
		int j;							// 临时变量
		for (j = i - 1; j >= 0 && e < elem[j]; j--)
		{	// 将比e大的计录都后移
			elem[j + 1] = elem[j];		// 后移
		}
		elem[j + 1] = e;				// j+1为插入位置
	}
}

#endif

