#ifndef __TRI_LK_BIN_TREE_NODE_H__
#define __TRI_LK_BIN_TREE_NODE_H__

// 三叉链表二叉树结点类
template <class ElemType>
struct TriLkBinTreeNode
{
// 数据成员:
	ElemType data;							// 数据域
	TriLkBinTreeNode<ElemType>  *leftChild;	// 左孩子指针域
	TriLkBinTreeNode<ElemType>  *rightChild;// 右孩子指针域
	TriLkBinTreeNode<ElemType>  *parent;	// 双亲指针域

//	构造函数:
	TriLkBinTreeNode();						// 无参数的构造函数 
	TriLkBinTreeNode(const ElemType &val,	// 由数据元素值,指向左右孩子及双亲的指针构造结点
		TriLkBinTreeNode<ElemType> *lChild = NULL, 
		TriLkBinTreeNode<ElemType> *rChild = NULL,
		TriLkBinTreeNode<ElemType> *pt = NULL);
};

// 二叉树结点类的实现部分
template <class ElemType>
TriLkBinTreeNode<ElemType>::TriLkBinTreeNode()
// 操作结果：构造一个叶结点
{
	leftChild = rightChild = NULL;			// 叶结点左右孩子为空
}

template <class ElemType>
TriLkBinTreeNode<ElemType>::TriLkBinTreeNode(const ElemType &val, 
	TriLkBinTreeNode<ElemType> *lChild, 
	TriLkBinTreeNode<ElemType> *rChild,
	TriLkBinTreeNode<ElemType> *pt)
// 操作结果：构造一个数据域为val,双亲为pt,左孩子为lChild,右孩子为rChild的结点
{	
	data = val;								// 数据元素值
	leftChild = lChild;						// 左孩子
	rightChild = rChild;					// 右孩子
	parent = pt;							// 双亲
}

#endif

