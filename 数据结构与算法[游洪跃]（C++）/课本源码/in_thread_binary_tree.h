#ifndef __IN_THREAD_BINARY_TREE_H__
#define __IN_THREAD_BINARY_TREE_H__

#include "binary_tree.h"			// 二叉树类
#include "thread_bin_tree_node.h"	// 线索二叉树结点类

// 中序线索二叉树类
template <class ElemType>
class InThreadBinTree
{
protected:
//  线索二叉树的数据成员:
	ThreadBinTreeNode<ElemType> *root;

//	辅助函数:
	void InThreadHelp(ThreadBinTreeNode<ElemType> *cur, ThreadBinTreeNode<ElemType> *&pre);
		// 中序线索化以cur为根的二叉树
	ThreadBinTreeNode<ElemType> *TransformHelp(BinTreeNode<ElemType> *r);
		// bt为根的二叉树转换成新的未线索化的中序线索二叉树,返回新二叉树的根
	ThreadBinTreeNode<ElemType> *CopyTreeHelp(ThreadBinTreeNode<ElemType> *copy);	
		// 复制线索二叉树
	void DestroyHelp(ThreadBinTreeNode<ElemType> * &r);		// 销毁以r为根二叉树

public:
//  线索二叉树方法声明及重载编译系统默认方法声明:
	InThreadBinTree(const BinaryTree<ElemType> &bt);		
		// 由二叉树构造中序线索二叉树——转换构造函数
	virtual ~InThreadBinTree();								// 析构函数
	ThreadBinTreeNode<ElemType> *GetRoot() const;			// 返回线索二叉树的根
	void InThread();										// 中序线索化二叉树
	void InOrder(void (*Visit)(const ElemType &)) const;	// 二叉树的中序遍历	
	InThreadBinTree(const InThreadBinTree<ElemType> &copy);	// 复制构造函数
	InThreadBinTree<ElemType> &operator=(const InThreadBinTree<ElemType>& copy);
		// 赋值运算符重载
};

template <class ElemType>
void DisplayBTWithTreeShapeHelp(ThreadBinTreeNode<ElemType> *r, int level);
	//	按树状形式显示以r为根的线索二叉树，level为层次数，可设根结点的层次数为1
template <class ElemType>
void DisplayBTWithTreeShape(InThreadBinTree<ElemType> &bt);
	//	树状形式显示线索二叉树 


// 二叉树类的实现部分
template <class ElemType>
void InThreadBinTree<ElemType>::InThreadHelp(ThreadBinTreeNode<ElemType> *cur, 
	ThreadBinTreeNode<ElemType> *&pre)
// 操作结果：中序线索化以cur为根的二叉树,pre表示cur的前驱
{
	if (cur != NULL)
	{	// 按中序遍历方式进行线索化
		if (cur->leftTag == CHILD_PTR)		
			InThreadHelp(cur->leftChild, pre);	// 线索化左子树
		
		if(cur->leftChild == NULL)
		{	// cur无左孩子,加线索 
			cur->leftChild = pre;				// cur前驱为pre
			cur->leftTag = THREAD_PTR;			// 线索标志
		}
		else
		{	// cur有左孩子, 修改标志 
			cur->leftTag = CHILD_PTR;			// 孩子指针标志
		}
		
		if(pre != NULL && pre->rightChild == NULL)
		{	// pre无右孩子, 加线索
			pre->rightChild = cur;				// pre后继为cur
			pre->rightTag = THREAD_PTR;			// 线索标志 
  		}
  		else if (pre != NULL)
		{	// cur有右孩子, 修改标志 
			pre->rightTag = CHILD_PTR;			// 孩子指针标志
		}
		pre = cur;								// 遍历下一结点时,cur为下一结点的前驱
		
		if (cur->rightTag == CHILD_PTR)		
			InThreadHelp(cur->rightChild, pre);	// 线索化右子树
	}
}

template <class ElemType>
void InThreadBinTree<ElemType>::InThread()
// 操作结果：中序线索化二叉树
{
	ThreadBinTreeNode<ElemType> *pre = NULL;	// 开始线索化时前驱为空
	InThreadHelp(root, pre);					// 中序线索化以root为根的二叉树
	if (pre->rightChild == NULL)				// pre为中序序列中最后一个结点
		pre->rightTag = THREAD_PTR;				// 如无右孩子,则加线索标记
}

template <class ElemType>
ThreadBinTreeNode<ElemType> *InThreadBinTree<ElemType>::TransformHelp(BinTreeNode<ElemType> *r)
// 操作结果：r为根的二叉树转换成新的未线索化的中序线索二叉树,返回新二叉树的根
{
	if (r == NULL)
	{	// 空二叉树转换成新的空线索二叉树
		return NULL;							// 空线索二叉树根为空	
	}
	else
	{	// 转换非空二叉树
		ThreadBinTreeNode<ElemType> *lChild = TransformHelp(r->leftChild);	// 转换左子树
		ThreadBinTreeNode<ElemType> *rChild = TransformHelp(r->rightChild);	// 转换右子树
		ThreadBinTreeNode<ElemType> *rt = new ThreadBinTreeNode<ElemType>(r->data, lChild, rChild);
			// 转换根结点
		return rt;															// 返回根结点
	}
}

template <class ElemType>
InThreadBinTree<ElemType>::InThreadBinTree(const BinaryTree<ElemType> &bt)
// 操作结果：由二叉树构造中序线索二叉树——转换构造函数
{
	root = TransformHelp(bt.GetRoot());			// 转换成未线索化的二叉树
	InThread();									// 线索化二叉树
}

template <class ElemType>
void InThreadBinTree<ElemType>::DestroyHelp(ThreadBinTreeNode<ElemType> * &r)
// 操作结果：销毁以r为根的线索二叉树
{
	if(r != NULL)
	{	// r非空,实施销毁
		if (r->leftTag == CHILD_PTR) DestroyHelp(r->leftChild);		// 销毁左子树
		if (r->rightTag == CHILD_PTR) DestroyHelp(r->rightChild);	// 销毁右子树
		delete r;													// 销毁根结点
		r = NULL;					
	}
}

template <class ElemType>
InThreadBinTree<ElemType>::~InThreadBinTree()
// 操作结果：销毁线索二叉树--析构函数
{
	DestroyHelp(root);
}

template <class ElemType>
ThreadBinTreeNode<ElemType> *InThreadBinTree<ElemType>::GetRoot() const
// 操作结果：返回线索二叉树的根
{	
	return root;
}

template <class ElemType>
void InThreadBinTree<ElemType>::InOrder(void (*Visit)(const ElemType &)) const
// 操作结果：二叉树的中序遍历	
{
	if (root != NULL)
	{
		ThreadBinTreeNode<ElemType> *cur = root;	// 从根开始遍历
		
		while (cur->leftTag == CHILD_PTR)			// 查找最左侧的结点，此结 
			cur = cur->leftChild;					// 点为中序序列的第一个结点
		while (cur != NULL)
		{
			(*Visit)(cur->data);					// 访问当前结点

			if (cur->rightTag == THREAD_PTR)
			{	// 右链为线索，后继为cur->rightChild
				cur = cur->rightChild;
			} 
			else
			{	// 右链为孩子，cur右子树最左侧的结点为后继
 				cur = cur->rightChild;				// cur指向右孩子	
				while (cur->leftTag == CHILD_PTR) 
					cur = cur->leftChild;			// 查找原cur右子树最左侧的结点
			}
		}
	}
}

template <class ElemType>
ThreadBinTreeNode<ElemType> *InThreadBinTree<ElemType>::CopyTreeHelp(ThreadBinTreeNode<ElemType> *copy)	
// 操作结果：将以copy为根的线索二叉树复制成新的未线索化的二叉树,返回新二叉树的根
{
	if (copy == NULL)
	{	// 复制空线索二叉树
		return NULL;								// 空线索二叉树根为空	
	}
	else
	{	// 复制非空线索二叉树
		ThreadBinTreeNode<ElemType> *lChild;
		ThreadBinTreeNode<ElemType> *rChild;
		if (copy->leftTag == CHILD_PTR)
			lChild = CopyTreeHelp(copy->leftChild);	// 复制左子树
		else lChild = NULL;							// 左子树为空
		if (copy->rightTag == CHILD_PTR)
			rChild = CopyTreeHelp(copy->rightChild);// 复制右子树
		else rChild = NULL;							// 左子树为空
		ThreadBinTreeNode<ElemType> *r = new ThreadBinTreeNode<ElemType>(copy->data, lChild, rChild);
			// 复制根结点
		return r;
	}
}

template <class ElemType>
InThreadBinTree<ElemType>::InThreadBinTree(const InThreadBinTree<ElemType> &copy)
// 操作结果：由已知线索二叉树构造新线索二叉树——复制构造函数
{
	root = CopyTreeHelp(copy.root);					// 复制线索二叉树
	InThread();										// 中序线索化二叉树
}

template <class ElemType>
InThreadBinTree<ElemType> &InThreadBinTree<ElemType>::operator=(const InThreadBinTree<ElemType> &copy)
// 操作结果：由已知线索二叉树copy复制到当前线索二叉树--赋值运算符重载
{
	if (&copy != this)
	{
		DestroyHelp(root);							// 释放原线索二叉树所占用空间
		root = CopyTreeHelp(copy.root);				// 复制线索二叉树
		InThread();									// 中序线索化二叉树
	}
	return *this;
}

template <class ElemType>
void DisplayBTWithTreeShapeHelp(ThreadBinTreeNode<ElemType> *r, int level)
//	操作结果：按树状形式显示以r为根的线索二叉树，level为层次数，可设根结点的层次数为1
{
	if(r != NULL)
	{	//空树不显式，只显式非空树
		if (r->rightTag == CHILD_PTR)
			DisplayBTWithTreeShapeHelp<ElemType>(r->rightChild, level + 1);//显示右子树
		cout << endl;								//显示新行	
		for(int i = 0; i < level - 1; i++)
			cout << " ";							//确保在第level列显示结点
		cout << r->data;							//显示结点
		if (r->leftTag == CHILD_PTR)
			DisplayBTWithTreeShapeHelp<ElemType>(r->leftChild, level + 1);//显示左子树
	}
}

template <class ElemType>
void DisplayBTWithTreeShape(InThreadBinTree<ElemType> &bt)
//	操作结果：树状形式显示线索二叉树 
{
	DisplayBTWithTreeShapeHelp<ElemType>(bt.GetRoot(), 1);	
		// 树状显示以bt.GetRoot()为根的线索二叉树
	cout << endl;
}

#endif
