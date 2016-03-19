#ifndef __BIN_SERACH_H__
#define __BIN_SERACH_H__

template <class ElemType, class KeyType>
int BinSerach(ElemType elem[], int n, KeyType key)
// 操作结果: 在有序表中查找其关键字的值等于key的记录,如查找成功,则返回此记录的序号,否则
//	返回-1
{
	int low = 0, high = n -1;		// 查找区间初值
	
	while (low <= high)
	{
		int mid = (low + high) / 2;	// 查找区间中间位置
		if (key == elem[mid])
		{	// 查找成功
			return mid;
		}
		else if (key <= elem[mid])
		{	// 继续在左半区间进行查找
			high = mid - 1;
		}
		else
		{	// 继续在右半区间进行查找
			low = mid + 1;
		}
	}

	return -1;	// 查找失败
}

#endif