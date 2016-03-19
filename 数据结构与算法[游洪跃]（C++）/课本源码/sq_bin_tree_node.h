#ifndef __SQ_BIN_TREE_NODE_H__
#define __SQ_BIN_TREE_NODE_H__

#ifndef __SQ_BIN_TREE_NODE_TAG_TYPE__
#define __SQ_BIN_TREE_NODE_TAG_TYPE__
enum SqBinTreeNodeTagType {EMPTY_NODE, USED_NODE};
#endif

// 顺序存储二叉树结点类
template <class ElemType>
struct SqBinTreeNode 
{
// 数据成员:
	ElemType data;				// 数据域
	SqBinTreeNodeTagType tag;	// 结点使用标志

// 构造函数:
	SqBinTreeNode();						// 无参数的构造函数
	SqBinTreeNode(ElemType item, SqBinTreeNodeTagType tg = EMPTY_NODE);	
		// 已知数据域和使用标志建立结构
};

// 顺序存储二叉树结点类的实现部分
template<class ElemType>
SqBinTreeNode<ElemType>::SqBinTreeNode()
// 操作结果：构造指针域为空的结点
{
   tag = EMPTY_NODE;			// 标一个空结点
}

template<class ElemType>
SqBinTreeNode<ElemType>::SqBinTreeNode(ElemType item, SqBinTreeNodeTagType tg)
// 操作结果：构造一个数据域为item和标志域为tg的结点
{
   data = item;					// 数据域
   tag = tg;					// 标志域
}

#endif
