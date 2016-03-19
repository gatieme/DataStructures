#ifndef __CHILD_SIBLING_FOREST_NODE_H__
#define __CHILD_SIBLING_FOREST_NODE_H__

// 孩子兄弟表示树结点类
template <class ElemType>
struct ChildSiblingTreeNode 
{
// 数据成员:
	ElemType data;								// 数据域
	ChildSiblingTreeNode<ElemType> *firstChild;	// 指向首孩子指针域
	ChildSiblingTreeNode<ElemType> *rightSibling;// 指向右兄弟指针域

// 构造函数:
	ChildSiblingTreeNode();						// 无参数的构造函数
	ChildSiblingTreeNode(ElemType item,			// 已知数据域值、指向首孩子与右兄弟指针建立结点
		ChildSiblingTreeNode<ElemType> *fChild = NULL,
		ChildSiblingTreeNode<ElemType> *rSibling = NULL);	
		
};

// 孩子兄弟表示树结点类的实现部分
template<class ElemType>
ChildSiblingTreeNode<ElemType>::ChildSiblingTreeNode()
// 操作结果：构造指针域为空的结点
{
	firstChild = rightSibling = NULL;			// 指向首孩子及兄弟的指针都为空
}

template<class ElemType>
ChildSiblingTreeNode<ElemType>::ChildSiblingTreeNode(ElemType item,			// 已知数据域值和双亲位置建立结构
		ChildSiblingTreeNode<ElemType> *fChild,
		ChildSiblingTreeNode<ElemType> *rSibling)
// 操作结果：构造一个数据域为item和首孩子为fChild，右兄弟为rChild的结点
{
	data = item;								// 数据
	firstChild = fChild;						// 首孩子
	rightSibling = rSibling;					// 右兄弟
}

#endif
