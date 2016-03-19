#ifndef __POST_THREAD_BINARY_TREE_H__
#define __POST_THREAD_BINARY_TREE_H__

#include "tri_lk_binary_tree.h"			// 三叉链表二叉树类
#include "post_thread_bin_tree_node.h"	// 后先线索二叉树结点类

// 后序线索二叉树类
template <class ElemType>
class PostThreadBinTree
{
protected:
//  线索二叉树的数据成员:
	PostThreadBinTreeNode<ElemType> *root;

//	辅助函数:
	void PostThreadHelp(PostThreadBinTreeNode<ElemType> *cur, PostThreadBinTreeNode<ElemType> *&pre);
		// 后序线索化以cur为根的二叉树
	PostThreadBinTreeNode<ElemType> *TransformHelp(TriLkBinTreeNode<ElemType> *r);
		// bt为根的二叉树转换成新的未线索化的后序线索二叉树,返回新二叉树的根
	PostThreadBinTreeNode<ElemType> *CopyTreeHelp(PostThreadBinTreeNode<ElemType> *copy);	
		// 复制线索二叉树
	void DestroyHelp(PostThreadBinTreeNode<ElemType> * &r);		// 销毁以r为根二叉树

public:
//  线索二叉树方法声明及重载编译系统默认方法声明:
	PostThreadBinTree(const TriLkBinaryTree<ElemType> &bt);		// 由二叉树构造后序线索二叉树——转换构造函数
	virtual ~PostThreadBinTree();								// 析造函数
	PostThreadBinTreeNode<ElemType> *GetRoot() const;			// 返回线索二叉树的根
	void PostThread();											// 后序线索化二叉树
	void PostOrder(void (*Visit)(const ElemType &)) const;		// 二叉树的后序遍历	
	PostThreadBinTree(const PostThreadBinTree<ElemType> &copy);	// 复制构造函数
	PostThreadBinTree<ElemType> &operator=(const PostThreadBinTree<ElemType>& copy);// 赋值运算符重载
};

template <class ElemType>
void DisplayBTWithTreeShapeHelp(PostThreadBinTreeNode<ElemType> *r, int level);
	//	按树状形式显示以r为根的线索二叉树，level为层次数，可设根结点的层次数为1
template <class ElemType>
void DisplayBTWithTreeShape(PostThreadBinTree<ElemType> &bt);
	//	树状形式显示线索二叉树 

// 二叉树类的实现部分
template <class ElemType>
void PostThreadBinTree<ElemType>::PostThreadHelp(PostThreadBinTreeNode<ElemType> *cur, PostThreadBinTreeNode<ElemType> *&pre)
// 操作结果：后序线索化以cur为根的二叉树,pre表示cur的前驱
{
	if (cur != NULL)
	{	// 按后序遍历方式进行线索化
		if (cur->leftTag == CHILD_PTR)		
			PostThreadHelp(cur->leftChild, pre);// 线索化左子树
		if (cur->rightTag == CHILD_PTR)		
			PostThreadHelp(cur->rightChild, pre);// 线索化右子树

		if(cur->leftChild == NULL)
		{	// cur无左孩子,加线索 
			cur->leftChild = pre;				// cur前驱为pre
			cur->leftTag = THREAD_PTR;			// 线索标志
		}
		
		if(pre != NULL && pre->rightChild == NULL)
		{	// pre无右孩子, 加线索
			pre->rightChild = cur;				// pre后继为cur
			pre->rightTag = THREAD_PTR;			// 线索标志 
  		}

		pre = cur;								// 遍历下一结点时,cur为下一结点的前驱
	}
}

template <class ElemType>
void PostThreadBinTree<ElemType>::PostThread()
// 操作结果：后序线索化二叉树
{
	PostThreadBinTreeNode<ElemType> *pre = NULL;// 开始线索化时前驱为空
	PostThreadHelp(root, pre);					// 后序线索化以root为根的二叉树
	if (pre->rightChild == NULL)				// pre为后序序列中最后一个结点
		pre->rightTag = THREAD_PTR;				// 如无右孩子,则加线索标记
}

template <class ElemType>
PostThreadBinTreeNode<ElemType> *PostThreadBinTree<ElemType>::TransformHelp(TriLkBinTreeNode<ElemType> *r)
// 操作结果：r为根的二叉树转换成新的未线索化的后序线索二叉树,返回新二叉树的根
{
	if (r == NULL)
	{	// 空二叉树转换成新的空线索二叉树
		return NULL;					// 空线索二叉树根为空	
	}
	else
	{	// 转换非空二叉树
		PostThreadBinTreeNode<ElemType> *lChild = TransformHelp(r->leftChild);	// 转换左子树
		PostThreadBinTreeNode<ElemType> *rChild = TransformHelp(r->rightChild);	// 转换右子树
		PostThreadBinTreeNode<ElemType> *rt = new PostThreadBinTreeNode<ElemType>(r->data, lChild, rChild);
			// 转换根结点
		if (lChild != NULL) lChild->parent = rt;	// lChild双亲为rt
		if (rChild != NULL) rChild->parent = rt;	// rChild双亲为rt
		return rt;															// 返回根结点
	}
}

template <class ElemType>
PostThreadBinTree<ElemType>::PostThreadBinTree(const TriLkBinaryTree<ElemType> &bt)
// 操作结果：由二叉树构造后序线索二叉树——转换构造函数
{
	root = TransformHelp(bt.GetRoot());			// 转换成未线索化的二叉树
	PostThread();								// 线索化二叉树
}

template <class ElemType>
void PostThreadBinTree<ElemType>::DestroyHelp(PostThreadBinTreeNode<ElemType> * &r)
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
PostThreadBinTree<ElemType>::~PostThreadBinTree()
// 操作结果：销毁线索二叉树--析造函数
{
	DestroyHelp(root);
}

template <class ElemType>
PostThreadBinTreeNode<ElemType> *PostThreadBinTree<ElemType>::GetRoot() const
// 操作结果：返回线索二叉树的根
{	
	return root;
}

template <class ElemType>
void PostThreadBinTree<ElemType>::PostOrder(void (*Visit)(const ElemType &)) const
// 操作结果：二叉树的后序遍历	
{
	if (root != NULL)
	{
		PostThreadBinTreeNode<ElemType> *cur = root;		// 从根开始遍历
		while (cur->leftTag == CHILD_PTR || cur->rightTag == CHILD_PTR)
		{	// 查找最左下的结点,此结点为后序序列第一个结点
			if (cur->leftTag == CHILD_PTR) cur = cur->leftChild;	// 移向左孩子
			else cur = cur->rightChild;						// 无左孩子,则移向右孩子
		}
		
		while (cur != NULL)
		{
			(*Visit)(cur->data);							// 访问当前结点

			PostThreadBinTreeNode<ElemType> *pt = cur->parent;	// 当前结点的双亲 
			if (cur->rightTag == THREAD_PTR)
			{	// 右链域为线索, 后继为cur->rightChild
				cur = cur->rightChild; 
			}
			else if (cur == root)
			{	// 结点cur是二叉树的根，其后继为空
				cur = NULL;
			}
			else if (pt->rightChild == cur || pt->leftChild == cur && pt->rightTag == THREAD_PTR)
			{	// 结点cur是其双亲的右孩子或是其双亲的左孩子且其双亲没有右子树，则
				// 其后继即为双亲结点
				cur = pt;
			}
			else 
			{	// 结点cur是其双亲的左孩子，且其双亲有右子树，则其后继为双亲的右
				// 子树中按后续遍历列出的第一个结点，即其双亲的右子树中最左下的结点
				cur = pt->rightChild;						// cur指向双亲的右孩子
				while (cur->leftTag == CHILD_PTR || cur->rightTag == CHILD_PTR)
				{	// 查找最左下的结点,此结点为后序序列第一个结点
					if (cur->leftTag == CHILD_PTR) cur = cur->leftChild;	// 移向左孩子
					else cur = cur->rightChild;				// 无左孩子,则移向右孩子
				}
			}
		}
	}
}

template <class ElemType>
PostThreadBinTreeNode<ElemType> *PostThreadBinTree<ElemType>::CopyTreeHelp(PostThreadBinTreeNode<ElemType> *copy)	
// 操作结果：将以copy为根的线索二叉树复制成新的未线索化的二叉树,返回新二叉树的根
{
	if (copy == NULL)
	{	// 复制空线索二叉树
		return NULL;									// 空线索二叉树根为空	
	}
	else
	{	// 复制非空线索二叉树
		PostThreadBinTreeNode<ElemType> *lChild;
		PostThreadBinTreeNode<ElemType> *rChild;
		
		if (copy->leftTag == CHILD_PTR)
			lChild = CopyTreeHelp(copy->leftChild);		// 复制左子树
		else lChild = NULL;								// 左子树为空
		
		if (copy->rightTag == CHILD_PTR)
			rChild = CopyTreeHelp(copy->rightChild);	// 复制右子树
		else rChild = NULL;								// 右子树为空
		
		PostThreadBinTreeNode<ElemType> *r = new PostThreadBinTreeNode<ElemType>(copy->data, lChild, rChild);
			// 复制根结点
		if (lChild != NULL) lChild->parent = r;			// lChild双亲为r
		if (rChild != NULL) rChild->parent = r;			// rChild双亲为r

		return r;
	}
}

template <class ElemType>
PostThreadBinTree<ElemType>::PostThreadBinTree(const PostThreadBinTree<ElemType> &copy)
// 操作结果：由已知线索二叉树构造新线索二叉树——复制构造函数
{
	root = CopyTreeHelp(copy.root);						// 复制线索二叉树
	PostThread();										// 后序线索化二叉树
}

template <class ElemType>
PostThreadBinTree<ElemType> &PostThreadBinTree<ElemType>::operator=(const PostThreadBinTree<ElemType> &copy)
// 操作结果：由已知线索二叉树copy复制到当前线索二叉树--赋值运算符重载
{
	if (&copy != this)
	{
		DestroyHelp(root);								// 释放原线索二叉树所占用空间
		root = CopyTreeHelp(copy.root);					// 复制线索二叉树
		PostThread();									// 后序线索化二叉树
	}
	return *this;
}

template <class ElemType>
void DisplayBTWithTreeShapeHelp(PostThreadBinTreeNode<ElemType> *r, int level)
//	操作结果：按树状形式显示以r为根的线索二叉树，level为层次数，可设根结点的层次数为1
{
	if(r != NULL)
	{	//空树不显式，只显式非空树
		if (r->rightTag == CHILD_PTR)
			DisplayBTWithTreeShapeHelp<ElemType>(r->rightChild, level + 1);//显示右子树
		cout << endl;					//显示新行	
		for(int i = 0; i < level - 1; i++)
			cout << " ";				//确保在第level列显示结点
		cout << r->data;				//显示结点
		if (r->leftTag == CHILD_PTR)
			DisplayBTWithTreeShapeHelp<ElemType>(r->leftChild, level + 1);//显示左子树
	}
}

template <class ElemType>
void DisplayBTWithTreeShape(PostThreadBinTree<ElemType> &bt)
//	操作结果：树状形式显示线索二叉树 
{
	DisplayBTWithTreeShapeHelp<ElemType>(bt.GetRoot(), 1);	
		// 树状显示以bt.GetRoot()为根的线索二叉树
	cout << endl;
}

#endif
