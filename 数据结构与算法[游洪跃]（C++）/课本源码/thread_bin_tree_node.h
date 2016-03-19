#ifndef __IN_THREAD_BIN_TREE_NODE_H__
#define __IN_THREAD_BIN_TREE_NODE_H__

#ifndef __POINTER_TAG_TYPE__
#define __POINTER_TAG_TYPE__
enum PointerTagType {CHILD_PTR, THREAD_PTR};
	// 指针标志类型,CHILD_PTR(0):指向孩子的指针,THREAD_PTR(1):指向线索的指针
#endif

// 线索二叉树结点类
template <class ElemType>
struct ThreadBinTreeNode
{
// 数据成员:
	ElemType data;							// 数据域
	ThreadBinTreeNode<ElemType> *leftChild;	// 左孩子指针域
	ThreadBinTreeNode<ElemType> *rightChild;// 右孩子指针域
	PointerTagType leftTag, rightTag;		// 左右标志域

//	构造函数:
	ThreadBinTreeNode();					// 无参数的构造函数 
	ThreadBinTreeNode(const ElemType &val,	// 由数据元素值,指针及标志域构造结点
		ThreadBinTreeNode<ElemType> *lChild = NULL, 
		ThreadBinTreeNode<ElemType> *rChild = NULL,
		PointerTagType leftTag = CHILD_PTR,
		PointerTagType rightTag = CHILD_PTR);
};

// 线索二叉树结点类的实现部分
template <class ElemType>
ThreadBinTreeNode<ElemType>::ThreadBinTreeNode()
// 操作结果：构造一个叶结点
{
	leftChild = rightChild = NULL;			// 指针域为空
	leftTag = rightTag = CHILD_PTR;			// 标志域
}

template <class ElemType>
ThreadBinTreeNode<ElemType>::ThreadBinTreeNode(const ElemType &val, 
		ThreadBinTreeNode<ElemType> *lChild, 
		ThreadBinTreeNode<ElemType> *rChild,
		PointerTagType lTag,
		PointerTagType rTag)
// 操作结果：构造一个数据域为val,左孩子为lChild,右孩子为rChild的结点,左标
//	志为lTag,右标志为rTag的结点
{	
	data = val;								// 数据元素值
	leftChild = lChild;						// 左孩子
	rightChild = rChild;					// 右孩子
	leftTag = lTag;							// 左标志
	rightTag = rTag;						// 右标志
}

#endif

