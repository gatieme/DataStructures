#ifndef __SIMPLE_LK_LIST_WITHOUT_first_NODE_H__
#define __SIMPLE_LK_LIST_WITHOUT_first_NODE_H__

#include "node.h"

// 无头结点的简单线性链表类
template <class ElemType>
class SimpleLinkListWithoutHeadNode 
{
protected:
//  链表实现的数据成员:
	Node<ElemType> *first;		// 指向首元素结构的指针

// 辅助函数
	Node<ElemType> *GetElemPtr(int position) const;	// 返回指向第position个结点的指针
	void Init();				// 初始化线性表

public:
//  抽象数据类型方法声明及重载编译系统默认方法声明:
	SimpleLinkListWithoutHeadNode();			// 无参数的构造函数
	virtual ~SimpleLinkListWithoutHeadNode();	// 析构函数
	int Length() const;			// 求线性表长度			 
	bool Empty() const;			// 判断线性表是否为空
	void Clear();				// 将线性表清空
	void Traverse(void (*Visit)(const ElemType &)) const;	// 遍历线性表
	StatusCode GetElem(int position, ElemType &e) const;	// 求指定位置的元素	
	StatusCode SetElem(int position, const ElemType &e);	// 设置指定位置的元素值
	StatusCode Delete(int position, ElemType &e);			// 删除元素		
	StatusCode Insert(int position, const ElemType &e);		// 插入元素
	SimpleLinkListWithoutHeadNode(const SimpleLinkListWithoutHeadNode<ElemType> &copy);	
		// 复制构造函数
	SimpleLinkListWithoutHeadNode<ElemType> &operator =
		(const SimpleLinkListWithoutHeadNode<ElemType> &copy); // 赋值运算符重载
};


// 简单线性链表类的实现部分
template<class ElemType>
Node<ElemType> *SimpleLinkListWithoutHeadNode<ElemType>::GetElemPtr(int position) const
// 操作结果：返回指向第position个结点的指针
{
	Node<ElemType> *tmpPtr = first;		// 用tmpPtr遍历线性表以查找第position个结点
	int curPosition = 1;				// tmpPtr所指结点的位置 

	while (tmpPtr != NULL && curPosition < position)
	// 顺指针向后查找，直到tmpPtr指向第position个结点
	{
		tmpPtr = tmpPtr->next;
		curPosition++;
	}

	if (tmpPtr != NULL && curPosition == position)
	{	// 查找成功
		return tmpPtr;	
	}
	else
	{	// 查找失败
		return NULL;	
	}

}

template <class ElemType>
void SimpleLinkListWithoutHeadNode<ElemType>::Init()
// 操作结果：初始化线性表
{
	first = NULL;		// 空链表指向首元素结构的指钍为空
}

template <class ElemType>
SimpleLinkListWithoutHeadNode<ElemType>::SimpleLinkListWithoutHeadNode()
// 操作结果：构造一个空链表
{
	Init();
}

template <class ElemType>
SimpleLinkListWithoutHeadNode<ElemType>::~SimpleLinkListWithoutHeadNode()
// 操作结果：销毁线性表
{
	Clear();			// 清空线性表
}

template <class ElemType>
int SimpleLinkListWithoutHeadNode<ElemType>::Length() const
// 操作结果：返回线性表元素个数
{
	int count = 0;		// 计数器 
	for (Node<ElemType> *tmpPtr = first; tmpPtr != NULL; tmpPtr = tmpPtr->next)
	{	// 用tmpPtr依次指向每个元素
		count++;	// 对线性表的每个元素进行计数
	}
	return count;
}

template <class ElemType>
bool SimpleLinkListWithoutHeadNode<ElemType>::Empty() const
// 操作结果：如线性表为空，则返回true，否则返回false
{
	return first == NULL;
}

template <class ElemType>
void SimpleLinkListWithoutHeadNode<ElemType>::Clear()
// 操作结果：清空线性表
{

	ElemType tmpElem;	// 临时元素值
	while (Length() > 0)
	{	// 表性表非空，则删除第1个元素
		Delete(1, tmpElem);
	}
}

template <class ElemType>
void SimpleLinkListWithoutHeadNode<ElemType>::Traverse(void (*Visit)(const ElemType &)) const
// 操作结果：依次对线性表的每个元素调用函数(*visit)
{
	for (Node<ElemType> *tmpPtr = first; tmpPtr != NULL; tmpPtr = tmpPtr->next)
	{	// 用tmpPtr依次指向每个元素
		(*Visit)(tmpPtr->data);	// 对线性表的每个元素调用函数(*visit)
	}
}

template <class ElemType>
StatusCode SimpleLinkListWithoutHeadNode<ElemType>::GetElem(int position, ElemType &e) const
// 操作结果：当线性表存在第position个元素时，用e返回其值，函数返回RANGE_ERROR,
//	否则函数返回RANGE_ERROR
{
	if (position < 1 || position > Length())
	{	// position范围错
		return RANGE_ERROR;
	}
	else
	{	// position合法
		Node<ElemType> *tmpPtr;
		tmpPtr = GetElemPtr(position);	// 取出指向第position个结点的指针	
		e = tmpPtr->data;				// 用e返回第position个元素的值
		return ENTRY_FOUND;
	}
}

template <class ElemType>
StatusCode SimpleLinkListWithoutHeadNode<ElemType>::SetElem(int position, const ElemType &e)
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
		Node<ElemType> *tmpPtr;
		tmpPtr = GetElemPtr(position);	// 取出指向第position个结点的指针
		tmpPtr->data = e;				// 设置第position个元素的值
		return SUCCESS;
	}
}

template <class ElemType>
StatusCode SimpleLinkListWithoutHeadNode<ElemType>::Delete(int position, ElemType &e)
// 操作结果：删除线性表的第position个位置的元素, 并用e返回其值,
//	position的取值范围为1≤position≤Length(),
//	position合法时函数返回SUCCESS,否则函数返回NOT_PRESENT
{
	if (position < 1 || position > Length())
	{	// position范围错
		return NOT_PRESENT;	// 元素不存在
	}
	else
	{	// position合法
		Node<ElemType> *tmpPtr;
		if (position > 1)
		{	// 删除非第1个元素
			tmpPtr = GetElemPtr(position - 1);		// 取出指向第position-1个结点的指针
			Node<ElemType> *nextPtr = tmpPtr->next;	// nextPtr为tmpPtr的后继
			tmpPtr->next = nextPtr->next;			// 删除结点
			e = nextPtr->data;						// 用e返回被删结点元素值	
			delete nextPtr;							// 释放被删结点
		}
		else
		{	// 删除第1个元素
			tmpPtr = first;							// 暂存first
			first = first->next;					// first指向后继
			delete tmpPtr;							// 释放被删除结点
		}
		return SUCCESS;
	}
}

template <class ElemType>
StatusCode SimpleLinkListWithoutHeadNode<ElemType>::Insert(int position, const ElemType &e)
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
		Node<ElemType> *newPtr;				// 指向被插入结点
		if (position > 1)
		{	// 插入元素不为第1个元素
			Node<ElemType> *tmpPtr = GetElemPtr(position - 1);	
				// 取出指向第position-1个结点的指针
			newPtr = new Node<ElemType>(e, tmpPtr->next);// 生成新结点
			tmpPtr->next = newPtr;			// 将tmpPtr插入到链表中
		}
		else
		{	// 插入元素为第1个元素
			newPtr = new Node<ElemType>(e, first);// 生成新结点
			first = newPtr;					// newPtr为新的第1个元素的结点
		}
		return SUCCESS;
	}
}

template <class ElemType>
SimpleLinkListWithoutHeadNode<ElemType>::
	SimpleLinkListWithoutHeadNode(const SimpleLinkListWithoutHeadNode<ElemType> &copy)
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
SimpleLinkListWithoutHeadNode<ElemType> &SimpleLinkListWithoutHeadNode<ElemType>::
	operator =(const SimpleLinkListWithoutHeadNode<ElemType> &copy)
// 操作结果：将线性表copy赋值给当前线性表——赋值运算符重载
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
