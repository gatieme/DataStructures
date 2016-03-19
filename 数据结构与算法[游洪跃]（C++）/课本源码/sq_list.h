#ifndef __SQ_LIST_H__
#define __SQ_LIST_H__

// 顺序表类
template <class ElemType>
class SqList 
{
protected:
// 顺序表实现的数据成员:
	int count;					// 元素个数
	int maxSize;				// 顺序表最大元素个数
	ElemType *elems;			// 元素存储空间

// 辅助函数
	bool Full() const;			// 判断线性表是否已满
	void Init(int size);		// 初始化线性表

public:
// 抽象数据类型方法声明及重载编译系统默认方法声明:
	SqList(int size = DEFAULT_SIZE);	// 构造函数
	virtual ~SqList();			// 析构函数
	int Length() const;			// 求线性表长度			 
	bool Empty() const;			// 判断线性表是否为空
	void Clear();				// 将线性表清空
	void Traverse(void (*Visit)(const ElemType &)) const;	// 遍历线性表
	StatusCode GetElem(int position, ElemType &e) const;	// 求指定位置的元素	
	StatusCode SetElem(int position, const ElemType &e);	// 设置指定位置的元素值
	StatusCode Delete(int position, ElemType &e);// 删除元素		
	StatusCode Insert(int position, const ElemType &e); // 插入元素
	SqList(const SqList<ElemType> &copy); // 复制构造函数
	SqList<ElemType> &operator =(const SqList<ElemType> &copy); // 赋值语句重载
};


// 顺序表类的实现部分

template <class ElemType>
bool SqList<ElemType>::Full() const
// 操作结果：如线性表已满，则返回true，否则返回false
{
	return count == maxSize;
}

template <class ElemType>
void SqList<ElemType>::Init(int size)
// 操作结果：初始化线性表为最大元素个数为size的空线性表
{
	maxSize = size;						// 最大元素个数
	if (elems != NULL) delete []elems;	// 释放存储空间
	elems = new ElemType[maxSize];		// 分配存储空间
	count = 0;							// 空线性表元素个数为0
}

template <class ElemType>
SqList<ElemType>::SqList(int size)
// 操作结果：构造一个最大元素个数为size的空顺序表
{
	elems = NULL;						// 未分配存储空间前,elems为空
	Init(size);							// 初始化线性表
}

template <class ElemType>
SqList<ElemType>::~SqList()
// 操作结果：销毁线性表
{
	delete []elems;						// 释放存储空间
}

template <class ElemType>
int SqList<ElemType>::Length() const
// 操作结果：返回线性表元素个数
{
	return count;
}

template <class ElemType>
bool SqList<ElemType>::Empty() const
// 操作结果：如线性表为空，则返回true，否则返回false
{
	return count == 0;
}

template <class ElemType>
void SqList<ElemType>::Clear()
// 操作结果：清空线性表
{
	count = 0;
}

template <class ElemType>
void SqList<ElemType>::Traverse(void (*visit)(const ElemType &)) const
// 操作结果：依次对线性表的每个元素调用函数(*visit)
{
	for (int curPosition = 1; curPosition <= Length(); curPosition++)
	{	// 对线性表的每个元素调用函数(*visit)
		(*visit)(elems[curPosition - 1]);
	}
}

template <class ElemType>
StatusCode SqList<ElemType>::GetElem(int position, ElemType &e) const
// 操作结果：当线性表存在第position个元素时，用e返回其值，函数返回ENTRY_FOUND,
//	否则函数返回NOT_PRESENT
{
	if(position < 1 || position > Length())
	{	// position范围错
		return NOT_PRESENT;	// 元素不存在
	}
	else
	{	// position合法
		e = elems[position - 1];
		return ENTRY_FOUND;	// 元素存在
	}
}

template <class ElemType>
StatusCode SqList<ElemType>::SetElem(int position, const ElemType &e)
// 操作结果：将线性表的第position个位置的元素赋值为e,
//	position的取值范围为1≤position≤Length(),
//	position合法时函数返回SUCCESS,否则函数返回RANGE_ERROR
{
	if (position < 1 || position > Length())
	{	// position范围错
		return RANGE_ERROR;	// 位置错
	}
	else
	{	// position合法
		elems[position - 1] = e;
		return SUCCESS;		// 成功
	}
}

template <class ElemType>
StatusCode SqList<ElemType>::Delete(int position, ElemType &e)
// 操作结果：删除线性表的第position个位置的元素, 并前用e返回其值,
//	position的的取值范围为1≤position≤Length(),
//	position合法时函数返回SUCCESS,否则函数返回RANGE_ERROR
{
	int len = Length();
	ElemType tmp;

	if (position < 1 || position >= len)
	{	// position范围错
		return RANGE_ERROR;
	}
	else
	{	// position合法
		GetElem(position, e);	// 用e返回被删除元素的值
		for (int curPosition = position + 1; curPosition <= len; curPosition++)
		// 被删除元素之后的元素依次左移
		{
			GetElem(curPosition, tmp); SetElem(curPosition - 1, tmp); 
		}
		count--;				// 删除后元素个数将自减1
		return SUCCESS;
	}
}

template <class ElemType>
StatusCode SqList<ElemType>::Insert(int position, const ElemType &e)
// 操作结果：在线性表的第position个位置前插入元素e,
//	position的的取值范围为1≤position≤Length()+1
//	如线性表已满,则返回OVER_FLOW,
//	如position合法, 则返回SUCCESS, 否则函数返回RANGE_ERROR
{
	int len = Length();
	ElemType tmp;
	if (Full())
	{	// 线性表已满返回OVER_FLOW
		return OVER_FLOW;	
	}
	else if (position < 1 || position > len + 1)
	{	// position范围错
		return RANGE_ERROR;
	}
	else
	{	// 成功
		count++;				// 插入后元素个数将自增1
		for (int curPosition = len; curPosition >= position; curPosition--)
		{	// 插入位置之后的元素右移
			GetElem(curPosition, tmp); SetElem(curPosition + 1, tmp); 
		}

		SetElem(position, e);	// 将e赋值到position位置处	
		return SUCCESS;			// 插入成功
	}
}

template <class ElemType>
SqList<ElemType>::SqList(const SqList<ElemType> &copy)
// 操作结果：由线性表copy构造新线性表——复制构造函数
{
	int copyLength = copy.Length();			// copy的长度
	ElemType e;

	elems = NULL;							// 未分配存储空间前,elems为空
	Init(copy.maxSize);						// 初始化新线性表
	for (int curPosition = 1; curPosition <= copyLength; curPosition++)
	{	// 复制数据元素
		copy.GetElem(curPosition, e);		// 取出第curPosition个元素
		Insert(Length() + 1, e);			// 将e插入到当前线性表
	}
}

template <class ElemType>
SqList<ElemType> &SqList<ElemType>::operator =(const SqList<ElemType> &copy)
// 操作结果：将线性表copy赋值给当前线性表——赋值语句重载
{
	if (&copy != this)
	{
		int copyLength = copy.Length();		// copy的长度
		ElemType e;

		Init(copy.maxSize);					// 初始化当前线性表
		for (int curPosition = 1; curPosition <= copyLength; curPosition++)
		{	// 复制数据元素
			copy.GetElem(curPosition, e);	// 取出第curPosition个元素
			Insert(Length() + 1, e);		// 将e插入到当前线性表
		}
	}
	return *this;
}

#endif