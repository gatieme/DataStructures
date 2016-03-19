#ifndef __GEN_LIST_H__
#define __GEN_LIST_H__

#include "ref_gen_node.h"					// 引用数法广义表结点类

// 引用数法广义表类
template<class ElemType>
class RefGenList
{
protected:
// 引用数法广义表类的数据成员:
	RefGenListNode<ElemType> *head;			// 引用数法广义表头指针
	
// 辅助函数
	void ShowHelp(RefGenListNode<ElemType> *hd) const;	
		// 显示以hd为头结点的引用数法广义表
	int DepthHelp(const RefGenListNode<ElemType> *hd);	
		// 计算以hd为表头的引用数法广义表的深度
	void ClearHelp(RefGenListNode<ElemType> *hd);		
		// 释放以hd为表头的引用数法广义表结构
	void CopyHelp(const RefGenListNode<ElemType> *sourceHead, 
		 RefGenListNode<ElemType> *&destHead);	
		// 将以destHead为头结点的引用数法广义表复制成以sourceHead为头结点的引用数法
		// 广义表
	static void CreateHelp(RefGenListNode<ElemType> *&first);
		// 创建以first为头结点的引用数法广义表

public:
// 抽象数据类型方法声明及重载编译系统默认方法声明:
	RefGenList();								// 无参数的构造函数
	RefGenList(RefGenListNode<ElemType> *hd);	// 由头结点指针构造引用数法广义表
	~RefGenList();								// 析构函数
	RefGenListNode<ElemType> *First() const;	// 返回引用数法广义表的第一个元素
	RefGenListNode<ElemType> *Next(RefGenListNode<ElemType> *elemPtr) const;	                                                                               
		// 返回elemPtr指向的引用数法广义表元素的后继
	bool Empty() const;						// 判断引用数法广义表是否为空
	void Push(const ElemType &e);			// 将原子元素e作为表头加入到引用数法广义表最前面
	void Push(RefGenList<ElemType> &subList);	
		// 将子表subList作为表头加入到引用数法广义表最前面
	int Depth();							// 计算引用数法广义表深度
	RefGenList(const RefGenList<ElemType> &copy);	// 复制构造函数
	RefGenList<ElemType> &operator =(const RefGenList<ElemType> &copy);// 赋值语句重载
	void Input(void);						// 输入广义表	
	void Show(void);						// 显示广义表	
};

// 引用数法广义表类的实现部分
template <class ElemType>
RefGenList<ElemType>::RefGenList()
// 操作结果：构造一个空引用数法广义表
{
	head = new RefGenListNode<ElemType>(HEAD);
	head->ref = 1;							// 引用数
}

template <class ElemType>
RefGenList<ElemType>::RefGenList(RefGenListNode<ElemType> *hd)
// 操作结果：由头结点指针构造引用数法广义表
{
	head = hd;								// 头结点
}

template <class ElemType>
RefGenListNode<ElemType> *RefGenList<ElemType>::First() const
// 操作结果：返回引用数法广义表的第一个元素
{
	return head->nextLink;
}

template <class ElemType>
RefGenListNode<ElemType> *RefGenList<ElemType>::Next(RefGenListNode<ElemType> *elemPtr) const
// 操作结果：返回elemPtr指向的引用数法广义表元素的后继
{
	return elemPtr->nextLink;
}

template <class ElemType>
bool RefGenList<ElemType>::Empty() const
// 操作结果：如引用数法广义表为空，则返回true，否则返回false
{
	return head->nextLink == NULL;
}

template <class ElemType>
void RefGenList<ElemType>::Push(const ElemType &e)
// 操作结果：将原子元素e作为表头加入到引用数法广义表最前面
{
	RefGenListNode<ElemType> *tmpPtr = new RefGenListNode<ElemType>(ATOM, head->nextLink);
	tmpPtr->atom = e;					// 数据域
	head->nextLink = tmpPtr;			// 将tmpPtr插入在head与head->nextLink之间 
}

template <class ElemType>
void RefGenList<ElemType>::Push(RefGenList<ElemType> &subList)
// 操作结果：将子表subList作为表头加入到引用数法广义表最前面
{
	RefGenListNode<ElemType> *tmpPtr = new RefGenListNode<ElemType>(LIST, head->nextLink);
	tmpPtr->subLink = subList.head;		// 子表
	subList.head->ref++;				// subList引用数自加1
	head->nextLink = tmpPtr;			// 将tmpPtr插入在head与head->nextLink之间 
}

template <class ElemType>
void RefGenList<ElemType>::ShowHelp(RefGenListNode<ElemType> *hd) const
// 操作结果：显示以hd为头结点的引用数法广义表
{
	bool frist = true;
	cout << "(";						// 引用数法广义表以(开始
	for (RefGenListNode<ElemType> *tmpPtr = hd->nextLink; tmpPtr != NULL; tmpPtr = tmpPtr->nextLink)
	{	// 依次处理引用数法广义表各元素 
		if (frist) frist = false;		// 第一个元素
		else cout << ",";				// 不同元素这间用逗号隔开
		if (tmpPtr->tag == ATOM)
		{	// 原子结点
			cout << tmpPtr->atom;
		}
		else
		{	// 表结点
			ShowHelp(tmpPtr->subLink);
		}
	}
	cout << ")";						// 引用数法广义表以)结束
}

template <class ElemType>
void RefGenList<ElemType>::Show(void)
// 操作结果：显示广义表	
{
	ShowHelp(head);					// 调用辅助函数显示广义表
}


template <class ElemType>
int RefGenList<ElemType>::DepthHelp(const RefGenListNode<ElemType> *hd)
// 操作结果：返回以hd为表头的引用数法广义表的深度
{
	if (hd->nextLink == NULL) return 1;// 空引用数法广义表的深度为1
	
	int subMaxDepth = 0;				// 子表最大深度
	for (RefGenListNode<ElemType> *tmpPtr = hd->nextLink; tmpPtr != NULL; 
		tmpPtr = tmpPtr->nextLink)
	{	// 求子表的最大深度
		if (tmpPtr->tag == LIST)
		{	// 子表
			int curSubDepth = DepthHelp(tmpPtr->subLink);	// 子表深度
			if (subMaxDepth < curSubDepth) subMaxDepth = curSubDepth;
		}
	}
	return subMaxDepth + 1;				// 引用数法广义表深度为子表最大深度加1
}

template <class ElemType>
int RefGenList<ElemType>::Depth()
// 操作结果：返回引用数法广义表深度
{
	return DepthHelp(head);
}

template <class ElemType>
void RefGenList<ElemType>::ClearHelp(RefGenListNode<ElemType> *hd)
// 操作结果：释放以hd为表头的引用数法广义表结构
{
	hd->ref--;								// 引用数自减1
	
	if (hd->ref == 0)
	{	// 引用数为0,释放结点所占用空间
		RefGenListNode<ElemType> *tmpPre, *tmpPtr;	// 临时变量 
		for (tmpPre = hd, tmpPtr = hd->nextLink; 
			tmpPtr != NULL; tmpPre = tmpPtr, tmpPtr = tmpPtr->nextLink)
		{	// 扫描引用数法广义表hd的顶层
			delete tmpPre;					// 释放tmpPre
			if (tmpPtr->tag == LIST)
			{	// tmpPtr为子表
				ClearHelp(tmpPtr->subLink);	// 释放子表
			}
		}
		delete tmpPre;						// 释放尾结点tmpPre
	}
}

template <class ElemType>
RefGenList<ElemType>::~RefGenList()
// 操作结果：释放引用数法广义表结构——析构函数
{
	ClearHelp(head);
}

template <class ElemType>
void RefGenList<ElemType>::CopyHelp(const RefGenListNode<ElemType> *sourceHead, 
	RefGenListNode<ElemType> *&destHead)	
// 初始条件: 以sourceHead为头结点的引用数法广义表为非递归引用数法广义表
// 操作结果: 将以sourceHead为头结点的引用数法广义表复制成以destHead为头结点的引用数法
//	广义表
{
	destHead = new RefGenListNode<ElemType>(HEAD);		// 复制头结点
	RefGenListNode<ElemType> *destPtr = destHead;		// destHead的当前结点
	destHead->ref = 1;									// 引用数为1
	for (RefGenListNode<ElemType> *tmpPtr = sourceHead->nextLink; tmpPtr != NULL; 
		tmpPtr = tmpPtr->nextLink)
	{	// 扫描引用数法广义表sourceHead的顶层
		destPtr = destPtr->nextLink = new RefGenListNode<ElemType>(tmpPtr->tag);	
			// 生成新结点
		if (tmpPtr->tag == LIST)
		{	// 子表
			CopyHelp(tmpPtr->subLink, destPtr->subLink);// 复制子表
		}
		else
		{	// 原子结点
			destPtr->atom = tmpPtr->atom;				// 复制原子结点
		}
	}
}

template <class ElemType>
RefGenList<ElemType>::RefGenList(const RefGenList<ElemType> &copy)
// 操作结果：由引用数法广义表copy构造新引用数法广义表--复制构造函数
{
	CopyHelp(copy.head, head);
}

template<class ElemType>
RefGenList<ElemType> &RefGenList<ElemType>::operator =(const RefGenList<ElemType> &copy)
// 操作结果：将引用数法广义表copy赋值给当前引用数法广义表--赋值语句重载
{
	if (&copy != this)
	{
		ClearHelp(head);				// 清空当前引用数法广义表
		CopyHelp(copy.head, head);		// 复制引用数法广义表
	}
	return *this;
}

template<class ElemType>
void RefGenList<ElemType>::CreateHelp(RefGenListNode<ElemType> *&first)
// 操作结果：创建以first为头结点的引用数法广义表
{
	char ch = GetChar();					// 读入字符
	switch (ch)
	{
	case ')':								// 引用数法广义表建立完毕
		return;								// 结束
	case '(':								// 子表
		// 表头为子表
		first = new RefGenListNode<ElemType>(LIST);// 生成表结点
		
		RefGenListNode<ElemType> *subHead;	// 子表指针
		subHead = new RefGenListNode<ElemType>(HEAD);// 生成子表的头结点
		subHead->ref = 1;					// 引用数为1	
		first->subLink = subHead;			// subHead为子表
		CreateHelp(subHead->nextLink);		// 递归建立子表
		
		ch = GetChar();						// 跳过','
		if (ch != ',') cin.putback(ch);		// 如不是','，则将ch回退到输入流
		CreateHelp(first->nextLink);		// 建立引用数法广义表下一结点
		break;
	default:								// 原子
		// 表头为原子
		cin.putback(ch);					// 将ch回退到输入流
		ElemType amData;					// 原子结点数据
		cin >> amData;						// 输入原子结点数据
		first = new RefGenListNode<ElemType>(ATOM);// 生成原表结点
		first->atom = amData;				// 原子结点数据
		
		ch = GetChar();						// 跳过','
		if (ch != ',') cin.putback(ch);		// 如不是','，则将ch回退到输入流
		CreateHelp(first->nextLink);		// 建立引用数法广义表下一结点
		break;
	}
}

template<class ElemType>
void RefGenList<ElemType>::Input(void)
// 操作结果：输入广义表
{
	head = new RefGenListNode<ElemType>(HEAD);	// 生成引用数法广义表头结点
	head->ref = 1;								// 引用数为1
	
	GetChar();									// 读入第一个'('
	RefGenList<ElemType>::CreateHelp(head->nextLink);
		// 创建以head->nextLink为表头的引用数法广义表
}

#endif
