#ifndef __SIMPLE_CIRC_LK_LIST_H__
#define __SIMPLE_CIRC_LK_LIST_H__

#include "node.h"					// 结点类

// 简单循环链表类
template <class ElemType>
class SimpleCircLinkList 
{
protected:
//  循环链表实现的数据成员:
	Node<ElemType> *head;			// 头结点指针

// 辅助函数
	Node<ElemType> *GetElemPtr(int position) const;	// 返回指向第position个结点的指针
	void Init();					// 初始化线性表

public:
//  抽象数据类型方法声明及重载编译系统默认方法声明:
	SimpleCircLinkList();			// 无参数的构造函数
	virtual ~SimpleCircLinkList();	// 析构函数
	int Length() const;				// 求线性表长度			 
	bool Empty() const;				// 判断线性表是否为空
	void Clear();					// 将线性表清空
	void Traverse(void (*Visit)(const ElemType &)) const;	// 遍历线性表
	StatusCode GetElem(int position, ElemType &e) const;	// 求指定位置的元素	
	StatusCode SetElem(int position, const ElemType &e);	// 设置指定位置的元素值
	StatusCode Delete(int position, ElemType &e);			// 删除元素		
	StatusCode Insert(int position, const ElemType &e);		// 插入元素
	SimpleCircLinkList(const SimpleCircLinkList<ElemType> &copy); // 复制构造函数
	SimpleCircLinkList<ElemType> &operator =(const SimpleCircLinkList<ElemType> &copy); // 赋值语句重载
};


// 简单链表类的实现部分
template<class ElemType>
Node<ElemType> *SimpleCircLinkList<ElemType>::GetElemPtr(int position) const
// 操作结果：返回指向第position个结点的指针
{
	if (position == 0)
	{	// 头结点的序号为0
		return head;
	}

	Node<ElemType> *tmpPtr = head->next;// 用tmpPtr遍历线性表以查找第position个结点
	int curPosition = 1;				// tmpPtr所指结点的位置 

	while (tmpPtr != head && curPosition < position)
	// 顺指针向后查找，直到tmpPtr指向第position个结点
	{
		tmpPtr = tmpPtr->next;
		curPosition++;
	}

	if (tmpPtr != head && curPosition == position)
	{	// 查找成功
		return tmpPtr;	
	}
	else
	{	// 查找失败
		return NULL;	
	}

}

template <class ElemType>
void SimpleCircLinkList<ElemType>::Init()
// 操作结果：初始化线性表
{
	head = new Node<ElemType>;		// 构造头指针
	head->next = head;				// 空循环链表的头结点后继为头结点本身
}

template <class ElemType>
SimpleCircLinkList<ElemType>::SimpleCircLinkList()
// 操作结果：构造一个空链表
{
	Init();
}

template <class ElemType>
SimpleCircLinkList<ElemType>::~SimpleCircLinkList()
// 操作结果：销毁线性表
{
	Clear();			// 清空线性表
	delete head;		// 释放头结点所点空间
}

template <class ElemType>
int SimpleCircLinkList<ElemType>::Length() const
// 操作结果：返回线性表元素个数
{
	int count = 0;		// 计数器 
	for (Node<ElemType> *tmpPtr = head->next; tmpPtr != head; tmpPtr = tmpPtr->next)
	{	// 用tmpPtr依次指向每个元素
		count++;	// 对线性表的每个元素进行计数
	}
	return count;
}

template <class ElemType>
bool SimpleCircLinkList<ElemType>::Empty() const
// 操作结果：如线性表为空，则返回true，否则返回false
{
	return head->next == head;
}

template <class ElemType>
void SimpleCircLinkList<ElemType>::Clear()
// 操作结果：清空线性表
{

	ElemType tmpElem;	// 临时元素值
	while (Length() > 0)
	{	// 表性表非空，则删除第1个元素
		Delete(1, tmpElem);
	}
}

template <class ElemType>
void SimpleCircLinkList<ElemType>::Traverse(void (*Visit)(const ElemType &)) const
// 操作结果：依次对线性表的每个元素调用函数(*visit)
{
	for (Node<ElemType> *tmpPtr = head->next; tmpPtr != head; tmpPtr = tmpPtr->next)
	{	// 用tmpPtr依次指向每个元素
		(*Visit)(tmpPtr->data);	// 对线性表的每个元素调用函数(*visit)
	}
}

template <class ElemType>
StatusCode SimpleCircLinkList<ElemType>::GetElem(int position, ElemType &e) const
// 操作结果：当线性表存在第position个元素时，用e返回其值，函数返回ENTRY_FOUND,
//	否则函数返回NOT_PRESENT
{
	if (position < 1 || position > Length())
	{	// position范围错
		return NOT_PRESENT;				// 元素不存在
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
StatusCode SimpleCircLinkList<ElemType>::SetElem(int position, const ElemType &e)
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
StatusCode SimpleCircLinkList<ElemType>::Delete(int position, ElemType &e)
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
		Node<ElemType> *tmpPtr;
		tmpPtr = GetElemPtr(position - 1);		// 取出指向第position-1个结点的指针
		Node<ElemType> *nextPtr = tmpPtr->next;	// nextPtr为tmpPtr的后继
		tmpPtr->next = nextPtr->next;			// 删除结点
		e = nextPtr->data;						// 用e返回被删结点元素值	
		delete nextPtr;							// 释放被删结点
		return SUCCESS;
	}
}

template <class ElemType>
StatusCode SimpleCircLinkList<ElemType>::Insert(int position, const ElemType &e)
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
		Node<ElemType> *tmpPtr;
		tmpPtr = GetElemPtr(position - 1);	// 取出指向第position-1个结点的指针
		Node<ElemType> *newPtr;
		newPtr = new Node<ElemType>(e, tmpPtr->next);// 生成新结点
		tmpPtr->next = newPtr;			// 将tmpPtr插入到链表中
		return SUCCESS;
	}
}

template <class ElemType>
SimpleCircLinkList<ElemType>::SimpleCircLinkList(const SimpleCircLinkList<ElemType> &copy)
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
SimpleCircLinkList<ElemType> &SimpleCircLinkList<ElemType>::operator =(const SimpleCircLinkList<ElemType> &copy)
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
