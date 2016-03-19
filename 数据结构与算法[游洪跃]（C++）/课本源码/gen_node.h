#ifndef __GEN_NODE_H__
#define __GEN_NODE_H__

#ifndef __GEN_LIST_NODE_TYPE__
#define __GEN_LIST_NODE_TYPE__
enum GenListNodeType {HEAD, ATOM, LIST};
#endif

#include "use_space_list.h"				// 广义表使用空间表类

// 广义表结点类
template<class ElemType>
struct GenListNode
{
// 数据成员:
	GenListNodeType tag;				// 标志域,HEAD(0):头结点, ATOM(1):原子结构, LIST(2):表结点
	GenListNode<ElemType> *nextLink;	// 指向同一层中的下一个结点指针域
	union
	{
		ElemType atom;					// tag=ATOM,存放原子结点的数据域
		GenListNode<ElemType> *subLink;	// tag=LISK,存放指向子表的指针域
	}; 

// 构造函数:
	GenListNode(GenListNodeType tg = HEAD, GenListNode<ElemType> *next = NULL);
		// 由标志tg和指针next构造广义表结点
};

// 广义表结点类的实现部分
template<class ElemType>
GenListNode<ElemType>::GenListNode(GenListNodeType tg, GenListNode<ElemType> *next)
// 操作结果：由标志tg和指针next构造广义表结点
{
	tag = tg;							// 标志
	nextLink = next;					// 后继
	gUseSpaceList.Push(this);			// 将指向当前结点的指针加入到广义表使用空间表中
}


#endif
