#ifndef __DBL_NODE_H__
#define __DBL_NODE_H__


// 双向链表结点类
template <class ElemType>
struct DblNode 
{
// 数据成员:
	ElemType data;				// 数据域
	DblNode<ElemType> *back;	// 指向前驱的指针域
	DblNode<ElemType> *next;	// 指向后继的指针域

// 构造函数:
	DblNode();						// 无数据的构造函数
	DblNode(ElemType item, 
	DblNode<ElemType> *linkBack = NULL,
	DblNode<ElemType> *linkNext = NULL);// 已知数据域和指针域建立结构
};


// 双向链表结点类的实现部分

template<class ElemType>
DblNode<ElemType>::DblNode()
// 操作结果：构造指针域为空的结点
{
   next = NULL;
}

template<class ElemType>
DblNode<ElemType>::DblNode(ElemType item,
			DblNode<ElemType> *linkBack,
			DblNode<ElemType> *linkNext)
// 操作结果：构造一个数据域为item和指针域为linkBack和linkNext的结点
{
   data = item;
   back = linkBack;
   next = linkNext;
}


#endif