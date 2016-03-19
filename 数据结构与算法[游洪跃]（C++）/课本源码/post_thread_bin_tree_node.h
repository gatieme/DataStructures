#ifndef __POST_THREAD_BIN_TREE_NODE_H__
#define __POST_THREAD_BIN_TREE_NODE_H__

#ifndef __POINTER_TAG_TYPE__
#define __POINTER_TAG_TYPE__
enum PointerTagType {CHILD_PTR, THREAD_PTR};	
	// 指针标志类型,CHILD_PTR(0):指向孩子的指针,THREAD_PTR(1):指向线索的指针
#endif

// 后序线索二叉树结点类
template <class ElemType>
struct PostThreadBinTreeNode
{
// 数据成员:
	ElemType data;								// 数据域
	PostThreadBinTreeNode<ElemType> *leftChild;	// 左孩子指针域
	PostThreadBinTreeNode<ElemType> *rightChild;// 右孩子指针域
	PostThreadBinTreeNode<ElemType> *parent;	// 双亲指针域
	PointerTagType leftTag, rightTag;			// 左右标域域

//	构造函数:
	PostThreadBinTreeNode();					// 无参数的构造函数 
	PostThreadBinTreeNode(const ElemType &val,	// 由数据元素值,指针及标志域构造结点
		PostThreadBinTreeNode<ElemType> *lChild = NULL, 
		PostThreadBinTreeNode<ElemType> *rChild = NULL,
		PostThreadBinTreeNode<ElemType> *pt = NULL,
		PointerTagType leftTag = CHILD_PTR,
		PointerTagType rightTag = CHILD_PTR);
};

// 后序线索二叉树结点类的实现部分
template <class ElemType>
PostThreadBinTreeNode<ElemType>::PostThreadBinTreeNode()
// 操作结果：构造一个叶结点
{
	leftChild = rightChild = parent = NULL;		// 指针域为空
	leftTag = rightTag = CHILD_PTR;				// 标志域
}

template <class ElemType>
PostThreadBinTreeNode<ElemType>::PostThreadBinTreeNode(const ElemType &val, 
		PostThreadBinTreeNode<ElemType> *lChild, 
		PostThreadBinTreeNode<ElemType> *rChild,
		PostThreadBinTreeNode<ElemType> *pt,
		PointerTagType lTag,
		PointerTagType rTag)
// 操作结果：构造一个数据域为val,左孩子为lChild,右孩子为rChild的结点,双亲为
//	pt,左标志为lTag,右标志为rTag的结点
{	
	data = val;									// 数据元素值
	leftChild = lChild;							// 左孩子
	rightChild = rChild;						// 右孩子
	parent = pt;								// 双亲
	leftTag = lTag;								// 左标志
	rightTag = rTag;							// 右标志
}

#endif

