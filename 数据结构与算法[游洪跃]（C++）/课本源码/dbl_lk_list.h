#ifndef __DBL_LK_LIST_H__
#define __DBL_LK_LIST_H__

#include "dbl_node.h"				// 双向链表结点类

// 双向链表类
template <class ElemType>
class DblLinkList 
{
protected:
//  循环链表实现的数据成员:
	DblNode<ElemType> *head;			// 头结点指针
	mutable int curPosition;			// 当前位置的序号
	mutable DblNode<ElemType> * curPtr;	// 指向当前位置的指针
	int count;							// 元素个数

// 辅助函数
	DblNode<ElemType> *GetElemPtr(int position) const;	// 返回指向第position个结点的指针
	void Init();				// 初始化线性表

public:
//  抽象数据类型方法声明及重载编译系统默认方法声明:
	DblLinkList();				// 无参数的构造函数
	virtual ~DblLinkList();		// 析构函数
	int Length() const;			// 求线性表长度			 
	bool Empty() const;			// 判断线性表是否为空
	void Clear();				// 将线性表清空
	void Traverse(void (*Visit)(const ElemType &)) const;	// 遍历线性表
	int GetCurPosition() const;								// 返回当前位置
	StatusCode GetElem(int position, ElemType &e) const;	// 求指定位置的元素	
	StatusCode SetElem(int position, const ElemType &e);	// 设置指定位置的元素值
	StatusCode Delete(int position, ElemType &e);			// 删除元素		
	StatusCode Insert(int position, const ElemType &e);		// 插入元素
	DblLinkList(const DblLinkList<ElemType> &copy);			// 复制构造函数
	DblLinkList<ElemType> &operator =(const DblLinkList<ElemType> &copy); // 赋值语句重载
};


// 链表类的实现部分

template<class ElemType>
DblNode<ElemType> *DblLinkList<ElemType>::GetElemPtr(int position) const
// 操作结果：返回指向第position个结点的指针
{
	if (curPosition < position)
	{	// 当前位置在所查找位置之前,向后查找
		for (; curPosition < position; curPosition++)
			curPtr = curPtr->next;			// 查找位置position
	}
	else if (curPosition > position)
	{	// 当前位置在所查找位置之后,向前查找
		for (; curPosition > position; curPosition--)
			curPtr = curPtr->back;			// 查找位置position
	}

	return curPtr;

}

template <class ElemType>
void DblLinkList<ElemType>::Init()
// 操作结果：初始化线性表
{
	head = new DblNode<ElemType>;	// 构造头指针
	head->next = head;				// 空循环链表的头结点后继为头结点本身
	curPtr = head;	curPosition = 0;// 初始化当前位置
	count = 0;						// 初始化元素个数
}

template <class ElemType>
DblLinkList<ElemType>::DblLinkList()
// 操作结果：构造一个空链表
{
	Init();
}

template <class ElemType>
DblLinkList<ElemType>::~DblLinkList()
// 操作结果：销毁线性表
{
	Clear();			// 清空线性表
	delete head;		// 释放头结点所点空间
}

template <class ElemType>
int DblLinkList<ElemType>::Length() const
// 操作结果：返回线性表元素个数
{
	return count;
}

template <class ElemType>
bool DblLinkList<ElemType>::Empty() const
// 操作结果：如线性表为空，则返回true，否则返回false
{
	return head->next == head;
}

template <class ElemType>
void DblLinkList<ElemType>::Clear()
// 操作结果：清空线性表
{

	ElemType tmpElem;	// 临时元素值
	while (Length() > 0)
	{	// 表性表非空，则删除第1个元素
		Delete(1, tmpElem);
	}
}

template <class ElemType>
void DblLinkList<ElemType>::Traverse(void (*Visit)(const ElemType &)) const
// 操作结果：依次对线性表的每个元素调用函数(*visit)
{
	for (DblNode<ElemType> *tmpPtr = head->next; tmpPtr != head; tmpPtr = tmpPtr->next)
	{	// 用tmpPtr依次指向每个元素
		(*Visit)(tmpPtr->data);	// 对线性表的每个元素调用函数(*visit)
	}
}

template <class ElemType>
int DblLinkList<ElemType>::GetCurPosition() const
// 操作结果：返回当前位置
{
	return curPosition;
}

template <class ElemType>
StatusCode DblLinkList<ElemType>::GetElem(int position, ElemType &e) const
// 操作结果：当线性表存在第position个元素时，用e返回其值，函数返回ENTRY_FOUND,
//	否则函数返回NOT_PRESENT
{
	if (position < 1 || position > Length())
	{	// position范围错
		return NOT_PRESENT;				// 元素不存在
	}
	else
	{	// position合法
		DblNode<ElemType> *tmpPtr;
		tmpPtr = GetElemPtr(position);	// 取出指向第position个结点的指针	
		e = tmpPtr->data;				// 用e返回第position个元素的值
		return ENTRY_FOUND;
	}
}

template <class ElemType>
StatusCode DblLinkList<ElemType>::SetElem(int position, const ElemType &e)
// 操作结果：将线性表的第position个位置的元素赋值为e,
//	position的取值范围为1≤position≤Length(),
//	position合法时函数返回SUCCESS,否则函数返回RANGE_ERROR
{
	if (position < 1 || position > Length())
	{	// position范围错
		return RANGE_ERROR;
	}
	else
	{	// position合法
		DblNode<ElemType> *tmpPtr;
		tmpPtr = GetElemPtr(position);	// 取出指向第position个结点的指针
		tmpPtr->data = e;				// 设置第position个元素的值
		return SUCCESS;
	}
}

template <class ElemType>
StatusCode DblLinkList<ElemType>::Delete(int position, ElemType &e)
// 操作结果：删除线性表的第position个位置的元素, 并用e返回其值,
//	position的取值范围为1≤position≤Length(),
//	position合法时函数返回SUCCESS,否则函数返回RANGE_ERROR
{
	if (position < 1 || position > Length())
	{	// position范围错
		return RANGE_ERROR;
	}
	else
	{	// position合法
		DblNode<ElemType> *tmpPtr;
		tmpPtr = GetElemPtr(position - 1);		// 取出指向第position - 1个结点的指针
		tmpPtr = tmpPtr->next;					// tmpPtr指向第position 个结点
		tmpPtr->back->next = tmpPtr->next;		// 修改向右的指针
		tmpPtr->next->back = tmpPtr->back;		// 修改向左的指针
		e = tmpPtr->data;						// 用e返回被删结点元素值
		if (position == Length())
		{	// 删除尾结点,当前结点变为头结点
			curPosition = 0;					// 设置当前位置的序号
			curPtr = head;						// 设置指向当前位置的指针
		}
		else
		{	// 删除非尾结点,当前结点变为第position个结点
			curPosition = position;				// 设置当前位置的序号
			curPtr = tmpPtr->next;				// 设置指向当前位置的指针
		}
		count--;								// 删除成功后元素个数减1 
		delete tmpPtr;							// 释放被删结点

		return SUCCESS;
	}
}

template <class ElemType>
StatusCode DblLinkList<ElemType>::Insert(int position, const ElemType &e)
// 操作结果：在线性表的第position个位置前插入元素e
//	position的取值范围为1≤position≤Length()+1
//	position合法时返回SUCCESS, 否则函数返回RANGE_ERROR
{
	if (position < 1 || position > Length() + 1)
	{	// position范围错
		return RANGE_ERROR; // 位置不合法
	}
	else
	{	// position合法
		DblNode<ElemType> *tmpPtr, *nextPtr, *newPtr;
		tmpPtr = GetElemPtr(position - 1);	// 取出指向第position-1个结点的指针
		nextPtr = tmpPtr->next;				// nextPtr指向第position个结点	
		newPtr = new DblNode<ElemType>(e, tmpPtr, nextPtr);// 生成新结点
		tmpPtr->next = newPtr;				// 修改向右的指针
		nextPtr->back = newPtr;				// 修改向左的指针
		curPosition = position;				// 设置当前位置的序号
		curPtr = newPtr;					// 设置指向当前位置的指针
		count++;							// 插入成功后元素个数加1 
		return SUCCESS;
	}
}

template <class ElemType>
DblLinkList<ElemType>::DblLinkList(const DblLinkList<ElemType> &copy)
// 操作结果：由线性表copy构造新线性表——复制构造函数
{
	int copyLength = copy.Length();		// copy的长度
	ElemType e;
	Init();								// 初始化线性表

	for (int curPosition = 1; curPosition <= copyLength; curPosition++)
	{	// 复制数据元素
		copy.GetElem(curPosition, e);	// 取出第curPosition个元素
		Insert(Length() + 1, e);		// 将e插入到当前线性表
	}
}

template <class ElemType>
DblLinkList<ElemType> &DblLinkList<ElemType>::operator =(const DblLinkList<ElemType> &copy)
// 操作结果：将线性表copy赋值给当前线性表——赋值语句重载
{
	if (&copy != this)
	{
		int copyLength = copy.Length();		// copy的长度
		ElemType e;
		Clear();							// 清空当前线性表

		for (int curPosition = 1; curPosition <= copyLength; curPosition++)
		{	// 复制数据元素
			copy.GetElem(curPosition, e);	// 取出第curPosition个元素
			Insert(Length() + 1, e);		// 将e插入到当前线性表
		}
	}
	return *this;
}

#endif