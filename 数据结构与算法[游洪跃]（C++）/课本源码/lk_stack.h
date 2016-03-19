#ifndef __LK_STACK_H__
#define __LK_STACK_H__

#include "node.h"				// 结点类

// 链栈类
template<class ElemType>
class LinkStack 
{
protected:
//  链栈实现的数据成员:
	Node<ElemType> *top;								// 栈顶指针

// 辅助函数
	void Init();										// 初始化栈

public:
//  抽象数据类型方法声明及重载编译系统默认方法声明:
	LinkStack();										// 无参数的构造函数
	virtual ~LinkStack();								// 析构函数
	int Length() const;									// 求栈长度			 
	bool Empty() const;									// 判断栈是否为空
	void Clear();										// 将栈清空
	void Traverse(void (*Visit)(const ElemType &)) const ;		// 遍历栈
	StatusCode Push(const ElemType &e);					// 入栈
	StatusCode Top(ElemType &e) const;					// 返回栈顶元素
	StatusCode Pop(ElemType &e);						// 出栈
	LinkStack(const LinkStack<ElemType> &copy);			// 复制构造函数
	LinkStack<ElemType> &operator =(const LinkStack<ElemType> &copy); // 赋值语句重载
};


// 链栈类的实现部分
template <class ElemType>
void LinkStack<ElemType>::Init()
// 操作结果：初始化栈
{
	top = NULL;				// 构造栈顶指针
}

template<class ElemType>
LinkStack<ElemType>::LinkStack()
// 操作结果：构造一个空栈表
{
	Init();
}

template<class ElemType>
LinkStack<ElemType>::~LinkStack()
// 操作结果：销毁栈
{
	Clear();
}

template <class ElemType>
int LinkStack<ElemType>::Length() const
// 操作结果：返回栈元素个数
{
	int count = 0;		// 计数器 
	for (Node<ElemType> *tmpPtr = top; tmpPtr != NULL; tmpPtr = tmpPtr->next)
	{	// 用tmpPtr依次指向每个元素
		count++;		// 对栈每个元素进行计数
	}
	return count;
}

template<class ElemType>
bool LinkStack<ElemType>::Empty() const
// 操作结果：如栈为空，则返回true，否则返回false
{
	return top == NULL;
}

template<class ElemType>
void LinkStack<ElemType>::Clear()
// 操作结果：清空栈
{
	ElemType tmpElem;	// 临时元素值
	while (!Empty())
		Pop(tmpElem);
}

template <class ElemType>
void LinkStack<ElemType>::Traverse(void (*Visit)(const ElemType &)) const
// 操作结果：从栈底到栈顶依次对栈的每个元素调用函数(*visit)
{
	Node<ElemType> *tmpPtr;		
	LinkStack<ElemType> tmpS;	// 临时栈,tmpS中元素顺序与当前栈元素顺序相反
	for (tmpPtr = top; tmpPtr != NULL; tmpPtr = tmpPtr->next)
	{	// 用tmpPtr依次指向当前栈的每个元素
		tmpS.Push(tmpPtr->data);	// 对当前栈的每个元素入栈到tmpS中
	}
	
	for (tmpPtr = tmpS.top; tmpPtr != NULL; tmpPtr = tmpPtr->next)
	{	// 用tmpPtr从栈顶到栈底依次指向栈tmpS的每个元素
		(*Visit)(tmpPtr->data);		// 对栈tmpS的每个元素调用函数(*visit)
	}
}

template<class ElemType>
StatusCode LinkStack<ElemType>::Push(const ElemType &e)
// 操作结果：将元素e追加到栈顶,如成功则返加SUCCESS,否则如动态内存已耗尽
//	将返回OVER_FLOW
{
	Node<ElemType> *new_top = new Node<ElemType>(e, top);
	if (new_top == NULL) 
	{	// 动态内存耗尽
		return OVER_FLOW;
	}
	else
	{	// 操作成功
		top = new_top;
		return SUCCESS;
	}
}

template<class ElemType>
StatusCode LinkStack<ElemType>::Top(ElemType &e) const
// 操作结果：如栈非空,用e返回栈顶元素,函数返回SUCCESS,否则函数返回UNDER_FLOW
{
	if(Empty())
	{	// 栈空
		return UNDER_FLOW;
	}
	else
	{	// 栈非空,操作成功
		e = top->data;				// 用e返回栈顶元素
		return SUCCESS;
	}
}

template<class ElemType>
StatusCode LinkStack<ElemType>::Pop(ElemType &e)
// 操作结果：如栈非空,删除栈顶元素,并用e返回栈顶元素,函数返回SUCCESS,否则
//	函数返回UNDER_FLOW
{
	if (Empty())
	{	// 栈空
		return UNDER_FLOW;
	}
	else
	{	// 操作成功
		Node<ElemType> *old_top = top;	// 旧栈顶
		e = old_top->data;				// 用e返回栈顶元素
		top = old_top->next;			// top指向新栈顶
		delete old_top;					// 删除旧栈顶
		return SUCCESS;
	}
}

template<class ElemType>
LinkStack<ElemType>::LinkStack(const LinkStack<ElemType> &copy) 
// 操作结果：由栈copy构造新栈--复制构造函数
{
	if (copy.Empty())
	{	// copy为空
		Init();									// 构造一空栈
	}
	else 
	{	// copy非空,复制栈
		top = new Node<ElemType>(copy.top->data);	// 生成当前栈项
		Node<ElemType> *buttomPtr = top;			// 当前栈底指针
		for (Node<ElemType> *tmpPtr = copy.top->next; tmpPtr != NULL; tmpPtr = tmpPtr->next)
		{	// 用tmpPtr依次指向其余元素
			buttomPtr->next = new Node<ElemType>(tmpPtr->data); // 向栈底追加元素	
			buttomPtr = buttomPtr->next;					// buttomPtr指向新栈底
		}
	}
}


template<class ElemType>
LinkStack<ElemType> &LinkStack<ElemType>::operator = (const LinkStack<ElemType> &copy)
// 操作结果：将栈copy赋值给当前栈--赋值语句重载
{
	if (&copy != this)
	{
		if (copy.Empty())
		{	// copy为空
			Init();										// 构造一空栈
		}
		else 
		{	// copy非空,复制栈
			Clear();									// 清空当前栈
			top = new Node<ElemType>(copy.top->data);	// 生成当前栈项
			Node<ElemType> *buttomPtr = top;			// 当前栈底指针
			for (Node<ElemType> *tmpPtr = copy.top->next; tmpPtr != NULL; tmpPtr = tmpPtr->next)
			{	// 用tmpPtr依次指向其余元素
				buttomPtr->next = new Node<ElemType>(tmpPtr->data); // 向栈底追加元素	
				buttomPtr = buttomPtr->next;			// buttomPtr指向新栈底
			}
		}
	}
	return *this;
}

#endif