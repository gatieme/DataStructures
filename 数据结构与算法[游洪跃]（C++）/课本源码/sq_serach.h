#ifndef __SQ_SERACH_H__
#define __SQ_SERACH_H__

template <class ElemType, class KeyType>
int SqSerach(ElemType elem[], int n, KeyType key)
// 操作结果: 在顺序表中查找关键字的值等于key的记录,如查找成功,则返回此记录的序号,否则返回-1
{
	int i;					// 临时变量 
	for (i = 0; i < n && elem[i] != key; i++);
	if (i < n)
	{	// 查找成功
		return i;
	}
	else
	{	// 查找失败
		return -1;
	}
}

#endif
