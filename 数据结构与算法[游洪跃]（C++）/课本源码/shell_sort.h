#ifndef __SHELL_SORT_H__
#define __SHELL_SORT_H__

template <class ElemType>
void ShellInsert(ElemType elem[], int n, int incr)
// 操作结果: 对数组elem作一趟增量为incr的Shell排序,对插入排序作出的修改是
//	子序列中前后相邻记录的增量为incr,而不是1
{
	for ( int i = incr ; i < n; i++)
	{	// 第i趟插入排序
		ElemType e = elem[i];			// 暂存elem[i]
		int j;							// 临时变量
		for (j = i - incr; j >= 0 && e < elem[j]; j -= incr)
		{	// 将子序列中比e大的计录都后移
			elem[j + incr] = elem[j];	// 后移
		}
		elem[j + incr] = e;				// j+incr为插入位置
	}
}

template <class ElemType>
void ShellSort(ElemType elem[], int n, int inc[], int t)
// 操作结果: 按增量序列inc[0 .. t -1 ]对数组elem作Shell排序
{
	for ( int k = 0 ; k < t; k++)
	{	// 第k趟Shell排序
		ShellInsert(elem, n, inc[k]);
	}
}

#endif

