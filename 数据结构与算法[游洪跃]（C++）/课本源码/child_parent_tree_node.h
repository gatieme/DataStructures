#ifndef __CHILD_PARENT_TREE_NODE_H__
#define __CHILD_PARENT_TREE_NODE_H__

#include "lk_list.h"				// 线性链表

// 孩子双法表示树结点类
template <class ElemType>
struct ChildParentTreeNode 
{
// 数据成员:
	ElemType data;					// 数据域
	LinkList<int> childLkList;		// 孩子链表	
	int parent;						// 双亲位置域

// 构造函数:
	ChildParentTreeNode();			// 无参数的构造函数
	ChildParentTreeNode(ElemType item, int pt = -1);// 已知数据域值和双亲位置建立结构
};

// 孩子双法表示树结点类的实现部分
template<class ElemType>
ChildParentTreeNode<ElemType>::ChildParentTreeNode()
// 操作结果：构造双亲域为-1的结点
{
	parent = -1;
}

template<class ElemType>
ChildParentTreeNode<ElemType>::ChildParentTreeNode(ElemType item, int pt)
// 操作结果：构造一个数据域为item和双亲域为pt的结点
{
	data = item;					// 数据元素值
	parent = pt;					// 双亲
}

#endif
