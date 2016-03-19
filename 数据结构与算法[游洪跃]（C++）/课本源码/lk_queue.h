#ifndef __LK_QUEUE_H__
#define __LK_QUEUE_H__

#include "node.h"				// 结点类

// 链队列类

template<class ElemType>
class LinkQueue 
{
protected:
//  链队列实现的数据成员:
	Node<ElemType> *front, *rear;					// 队头队尾指指

// 辅助函数:
	void Init();									// 初始化队列

public:
//  抽象数据类型方法声明及重载编译系统默认方法声明:
	LinkQueue();									// 无参数的构造函数
	virtual ~LinkQueue();							// 析构函数
	int Length() const;								// 求队列长度			 
	bool Empty() const;								// 判断队列是否为空
	void Clear();									// 将队列清空
	void Traverse(void (*Visit)(const ElemType &)) const ;	// 遍历队列
	StatusCode OutQueue(ElemType &e);				// 出队操作
	StatusCode GetHead(ElemType &e) const;			// 取队头操作
	StatusCode InQueue(const ElemType &e);			// 入队操作
	LinkQueue(const LinkQueue<ElemType> &copy);		// 复制构造函数
	LinkQueue<ElemType> &operator =(const LinkQueue<ElemType> &copy);// 赋值语句重载
};

// 链队列类的实现部分

template <class ElemType>
void LinkQueue<ElemType>::Init()
// 操作结果：初始化队列
{
	rear = front = new Node<ElemType>;	// 生成头结点
}

template<class ElemType>
LinkQueue<ElemType>::LinkQueue()
// 操作结果：构造一个空队列
{
	Init();
}

template<class ElemType>
LinkQueue<ElemType>::~LinkQueue()
// 操作结果：销毁队列
{
	Clear();		
}

template<class ElemType>
int LinkQueue<ElemType>::Length() const
// 操作结果：返回队列长度			 
{
	int count = 0;		// 计数器 
	for (Node<ElemType> *tmpPtr = front->next; tmpPtr != NULL; tmpPtr = tmpPtr->next)
	{	// 用tmpPtr依次指向每个元素
		count++;		// 对栈每个元素进行计数
	}
	return count;
}

template<class ElemType>
bool LinkQueue<ElemType>::Empty() const
// 操作结果：如队列为空，则返回true，否则返回false
{
   return rear == front;
}

template<class ElemType>
void LinkQueue<ElemType>::Clear() 
// 操作结果：清空队列
{
	ElemType tmpElem;	// 临时元素值
	while (Length() > 0)
	{	// 队列非空，则出列
		OutQueue(tmpElem);
	}
}

template <class ElemType>
void LinkQueue<ElemType>::Traverse(void (*Visit)(const ElemType &)) const 
// 操作结果：依次对队列的每个元素调用函数(*visit)
{
	for (Node<ElemType> *tmpPtr = front->next; tmpPtr != NULL; 
		tmpPtr = tmpPtr->next)
	{	// 对队列每个元素调用函数(*visit)
		(*Visit)(tmpPtr->data);
	}
}


template<class ElemType>
StatusCode LinkQueue<ElemType>::OutQueue(ElemType &e)
// 操作结果：如果队列非空，那么删除队头元素，并用e返回其值，函数返回SUCCESS,
//	否则函数返回UNDER_FLOW，
{
	if (!Empty()) 
	{	// 队列非空
		Node<ElemType> *tmpPtr = front->next;	// 指向队列头素
		e = tmpPtr->data;						// 用e返回队头元素
		front->next = tmpPtr->next;				// front指向下一元素
		if (rear == tmpPtr)
		{	// 表示出队前队列中只有一个元素，出队后为空队列
			rear = front;
		}
		delete tmpPtr;							// 释放出队的结点
		return SUCCESS;
	}
	else
	{	// 队列为空
		return UNDER_FLOW;
	}
}

template<class ElemType>
StatusCode LinkQueue<ElemType>::GetHead(ElemType &e) const
// 操作结果：如果队列非空，那么用e返回队头元素，函数返回SUCCESS,
//	否则函数返回UNDER_FLOW，
{
	if (!Empty()) 
	{	// 队列非空
		Node<ElemType> *tmpPtr = front->next;	// 指向队列头素
		e = tmpPtr->data;						// 用e返回队头元素
		return SUCCESS;
	}
	else
	{	// 队列为空
		return UNDER_FLOW;
	}
}

template<class ElemType>
StatusCode LinkQueue<ElemType>::InQueue(const ElemType &e)
// 操作结果：插入元素e为新的队尾，返回SUCCESS
{
	Node<ElemType> *tmpPtr = new Node<ElemType>(e);	// 生成新结点
	rear->next = tmpPtr;							// 新结点追加在队尾
	rear = tmpPtr;									// rear指向新队尾
	return SUCCESS;
}

template<class ElemType>
LinkQueue<ElemType>::LinkQueue(const LinkQueue<ElemType> &copy)
// 操作结果：由队列copy构造新队列--复制构造函数
{
	Init();
	for (Node<ElemType> *tmpPtr = copy.front->next; tmpPtr != NULL; 
		tmpPtr = tmpPtr->next)
	{	// 对copy队列每个元素对当前队列作入队列操作
		InQueue(tmpPtr->data);
	}
}

template<class ElemType>
LinkQueue<ElemType> &LinkQueue<ElemType>::operator =(const LinkQueue<ElemType> &copy)
// 操作结果：将队列copy赋值给当前队列--赋值语句重载
{
	if (&copy != this)
	{
		Clear();
		for (Node<ElemType> *tmpPtr = copy.front->next; tmpPtr != NULL; 
			tmpPtr = tmpPtr->next)
		{	// 对copy队列每个元素对当前队列作入队列操作
			InQueue(tmpPtr->data);
		}
	}
	return *this;
}

#endif
