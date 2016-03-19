#ifndef __TRI_LK_BINNARY_TREE_H__
#define __TRI_LK_BINNARY_TREE_H__

#include "lk_queue.h"				// 链队列
#include "tri_lk_bin_tree_node.h"	// 三叉链表二叉树结点类

// 三叉链表二叉树类
template <class ElemType>
class TriLkBinaryTree
{
protected:
//  二叉树的数据成员:
	TriLkBinTreeNode<ElemType> *root;

//	辅助函数:
	TriLkBinTreeNode<ElemType> *CopyTreeHelp(TriLkBinTreeNode<ElemType> *copy);	// 复制二叉树
	void DestroyHelp(TriLkBinTreeNode<ElemType> * &r);						// 销毁以r为根二叉树
	void PreOrderHelp(TriLkBinTreeNode<ElemType> *r, void (*Visit)(const ElemType &)) const;	// 先序遍历
	void InOrderHelp(TriLkBinTreeNode<ElemType> *r, void (*Visit)(const ElemType &)) const;		// 中序遍历
	void PostOrderHelp(TriLkBinTreeNode<ElemType> *r, void (*Visit)(const ElemType &)) const;	// 后序遍历
    int HeightHelp(const TriLkBinTreeNode<ElemType> *r) const;				// 返回二叉树的高
	int NodeCountHelp(const TriLkBinTreeNode<ElemType> *r) const;			// 返回二叉树的结点个数

public:
//  二叉树方法声明及重载编译系统默认方法声明:
	TriLkBinaryTree();											// 无参数的构造函数
	virtual ~TriLkBinaryTree();									// 析构函数
	TriLkBinTreeNode<ElemType> *GetRoot() const;				// 返回二叉树的根
	bool Empty() const;											// 判断二叉树是否为空
	StatusCode GetElem(TriLkBinTreeNode<ElemType> *cur, ElemType &e) const;
		// 用e返回结点元素值
	StatusCode SetElem(TriLkBinTreeNode<ElemType> *cur, const ElemType &e);
		// 将结cur的值置为e
	void InOrder(void (*Visit)(const ElemType &)) const;		// 二叉树的中序遍历	
	void PreOrder(void (*Visit)(const ElemType &)) const;		// 二叉树的先序遍历
	void PostOrder(void (*Visit)(const ElemType &)) const;		// 二叉树的后序遍历
	void LevelOrder(void (*Visit)(const ElemType &)) const;		// 二叉树的层次遍历
	int NodeCount() const;										// 求二叉树的结点个数
	TriLkBinTreeNode<ElemType> *LeftChild(const TriLkBinTreeNode<ElemType> *cur) const;
		// 返回二叉树结点cur的左孩子
	TriLkBinTreeNode<ElemType> *RightChild(const TriLkBinTreeNode<ElemType> *cur) const;
		// 返回二叉树结点cur的右孩子
	TriLkBinTreeNode<ElemType> *Parent(const TriLkBinTreeNode<ElemType> *cur) const;
		// 返回二叉树结点cur的双亲
	void InsertLeftChild(TriLkBinTreeNode<ElemType> *cur, const ElemType &e);	// 插入左孩子
	void InsertRightChild(TriLkBinTreeNode<ElemType> *cur, const ElemType &e);// 插入右孩子
	void DeleteLeftChild(TriLkBinTreeNode<ElemType> *cur);		// 删除左子树
	void DeleteRightChild(TriLkBinTreeNode<ElemType> *cur);		// 删除右子村
	int	Height() const;											// 求二叉树的高
	TriLkBinaryTree(const ElemType &e);							// 建立以e为根的二叉树
	TriLkBinaryTree(const TriLkBinaryTree<ElemType> &copy);		// 复制构造函数
	TriLkBinaryTree(TriLkBinTreeNode<ElemType> *r);				// 建立以r为根的二叉树
	TriLkBinaryTree<ElemType> &operator=(const TriLkBinaryTree<ElemType>& copy);	// 赋值运算符重载
};

template <class ElemType>
void DisplayBTWithTreeShapeHelp(TriLkBinTreeNode<ElemType> *r, int level);
	//	按树状形式显示以r为根的二叉树，level为层次数，可设根结点的层次数为1
template <class ElemType>
void DisplayBTWithTreeShape(TriLkBinaryTree<ElemType> &bt);
	//	树状形式显示二叉树 
template <class ElemType>
void CreateBinaryTreeHelp(TriLkBinTreeNode<ElemType> *&r, ElemType pre[], ElemType in[], 
							int preLeft, int preRight, int inLeft, int inRight);	
	// 已知二叉树的先序序列pre[preLeft..preRight]和中序序列in[inLeft..inRight]构造以r为根的
	// 二叉树
template <class ElemType>
TriLkBinaryTree<ElemType> &CreateBinaryTree(ElemType pre[], ElemType in[], int n);
	// 已知先序和中序序列构造二叉树



// 二叉树类的实现部分
template <class ElemType>
TriLkBinaryTree<ElemType>::TriLkBinaryTree()
// 操作结果：构造一个空二叉树
{
	root = NULL;
}

template <class ElemType>
TriLkBinaryTree<ElemType>::~TriLkBinaryTree()
// 操作结果：销毁二叉树--析造函数
{
	DestroyHelp(root);
}

template <class ElemType>
TriLkBinTreeNode<ElemType> *TriLkBinaryTree<ElemType>::GetRoot() const
// 操作结果：返回二叉树的根
{
	return root;
}

template <class ElemType>
bool TriLkBinaryTree<ElemType>::Empty() const
// 操作结果：判断二叉树是否为空
{
	return root == NULL;
}

template <class ElemType>
StatusCode TriLkBinaryTree<ElemType>::GetElem(TriLkBinTreeNode<ElemType> *cur, ElemType &e) const
// 操作结果：用e返回结点cur元素值,如果不存在结点cur,函数返回NOT_PRESENT,否则返回ENTRY_FOUND
{
	if (cur == NULL)	
	{	// 不存在结点cur
		return NOT_PRESENT;			// 返回NOT_PRESENT
	}
	else
	{	// 存在结点cur
		e = cur->data;				// 用e返回元素值
		return ENTRY_FOUND;			// 返回ENTRY_FOUND
	}
}

template <class ElemType>
StatusCode TriLkBinaryTree<ElemType>::SetElem(TriLkBinTreeNode<ElemType> *cur, const ElemType &e)
// 操作结果：如果不存在结点cur,则返回FAIL,否则返回SUCCESS,并将结点cur的值设置为e
{
	if (cur == NULL)	
	{	// 不存在结点cur
		return FAIL;				// 返回FAIL
	}
	else
	{	// 存在结点cur
		cur->data = e;				// 将结点cur的值设置为e
		return SUCCESS;				// 返回SUCCESS
	}
}

template <class ElemType>
void TriLkBinaryTree<ElemType>::PreOrderHelp(TriLkBinTreeNode<ElemType> *r, void (*Visit)(const ElemType &))const
// 操作结果：先序遍历以r为根的二叉树
{
	if (r != NULL) 
	{
		(*Visit)(r->data);					// 访问根结点
		PreOrderHelp(r->leftChild, Visit);	// 遍历左子树
		PreOrderHelp(r->rightChild, Visit);	// 遍历右子树
	}
}

template <class ElemType>
void TriLkBinaryTree<ElemType>::PreOrder(void (*Visit)(const ElemType &)) const
// 操作结果：先序遍历二叉树
{
	PreOrderHelp(root, Visit);	
}	

template <class ElemType>
void TriLkBinaryTree<ElemType>::InOrderHelp(TriLkBinTreeNode<ElemType> *r, void (*Visit)(const ElemType &)) const
// 操作结果：中序遍历以r为根的二叉树
{
	if (r != NULL) 
	{
		InOrderHelp(r->leftChild, Visit);	// 遍历左子树
		(*Visit)(r->data);					// 访问根结点
		InOrderHelp(r->rightChild, Visit);	// 遍历右子树
	}
}

template <class ElemType>
void TriLkBinaryTree<ElemType>::InOrder(void (*Visit)(const ElemType &)) const
// 操作结果：中序遍历二叉树
{
	InOrderHelp(root, Visit);	
}	

template <class ElemType>
void TriLkBinaryTree<ElemType>::PostOrderHelp(TriLkBinTreeNode<ElemType> *r, void (*Visit)(const ElemType &)) const
// 操作结果：后序遍历以r为根的二叉树
{
	if (r != NULL) 
	{
		PostOrderHelp(r->leftChild, Visit);	// 遍历左子树
		PostOrderHelp(r->rightChild, Visit);// 遍历右子树
		(*Visit)(r->data);					// 访问根结点
	}
}

template <class ElemType>
void TriLkBinaryTree<ElemType>::PostOrder(void (*Visit)(const ElemType &)) const
// 操作结果：后序遍历二叉树
{
	PostOrderHelp(root, Visit);	
}	

template <class ElemType>
void TriLkBinaryTree<ElemType>::LevelOrder(void (*Visit)(const ElemType &)) const
// 操作结果：层次遍历二叉树
{
	LinkQueue<TriLkBinTreeNode<ElemType> *> q;	// 队列
	TriLkBinTreeNode<ElemType> *t = root;		// 从根结点开始进行层次遍历
	
	if (t != NULL) q.InQueue(t);				// 如果根非空,则入队
	while (!q.Empty())
	{	// q非空,说明还有结点未访问
		q.OutQueue(t);     
		(*Visit)(t->data);
		if (t->leftChild != NULL)				// 左孩子非空
			q.InQueue(t->leftChild);			// 左孩子入队
		if (t->rightChild != NULL)				// 右孩子非空
			q.InQueue(t->rightChild);			// 右孩子入队
	}
}

template <class ElemType>
int TriLkBinaryTree<ElemType>::HeightHelp(const TriLkBinTreeNode<ElemType> *r) const
// 操作结果：返回以r为根的二叉树的高
{
	if(r == NULL)
	{	// 空二叉树高为0
		return 0;
	}
	else
	{	// 非空二叉树高为左右子树的高的最大值再加1
		int lHeight, rHeight;
		lHeight = HeightHelp(r->leftChild);		// 左子树的高
		rHeight = HeightHelp(r->rightChild);	// 右子树的高
		return 1 + (lHeight > rHeight ? lHeight : rHeight);
			// 非空二叉树高为左右子树的高的最大值再加1
	}
}

template <class ElemType>
int TriLkBinaryTree<ElemType>::Height() const
// 操作结果：返回二叉树的高
{
	return HeightHelp(root);
}

template <class ElemType>
TriLkBinaryTree<ElemType>::TriLkBinaryTree(const ElemType &e)
// 操作结果：建立以e为根的二叉树
{
	root = new TriLkBinTreeNode<ElemType>(e);
}

template <class ElemType>
int TriLkBinaryTree<ElemType>::NodeCountHelp(const TriLkBinTreeNode<ElemType> *r) const
// 操作结果：返回以r为根的二叉树的结点个数
{
	if (r ==NULL) return 0;						// 空二叉树结点个数为0
	else return 1 + NodeCountHelp(r->leftChild) + NodeCountHelp(r->rightChild);
		// 非空二叉树结点个为左右子树的结点个数之和再加1
}

template <class ElemType>
int TriLkBinaryTree<ElemType>::NodeCount() const
// 操作结果：返回二叉树的结点个数
{
	return NodeCountHelp(root);
}

template <class ElemType>
TriLkBinTreeNode<ElemType> *TriLkBinaryTree<ElemType>::LeftChild(const TriLkBinTreeNode<ElemType> *cur) const
// 操作结果：返回二叉树结点cur的左孩子
{
	return cur->leftChild;
}

template <class ElemType>
TriLkBinTreeNode<ElemType> *TriLkBinaryTree<ElemType>::RightChild(const TriLkBinTreeNode<ElemType> *cur) const
// 操作结果：返回二叉树结点cur的右孩子
{
	return cur->rightChild;
}

template <class ElemType>
TriLkBinTreeNode<ElemType> *TriLkBinaryTree<ElemType>::Parent(const TriLkBinTreeNode<ElemType> *cur) const
// 操作结果：返回二叉树结点cur的双亲
{
	return cur->parent;
}

template <class ElemType>
void TriLkBinaryTree<ElemType>::InsertLeftChild(TriLkBinTreeNode<ElemType> *cur, const ElemType &e)
// 初始条件：cur非空，
// 操作结果：插入元素值为e的结点为cur的左孩子，如果cur的左孩子非空，则cur原有左子树成为e的左子树
{
	if (cur == NULL)
	{	// cur为空，返回
		return;
	}
	else 
	{	// 插入左孩子
		TriLkBinTreeNode<ElemType> *child =  new TriLkBinTreeNode<ElemType>(e);// 元素值为e结点
		if (cur->leftChild != NULL)
		{	// cur的左孩子非空
			child->leftChild = cur->leftChild;	// cur原有左子树成为e的左子树
			cur->leftChild->parent = child;		// cur原有左子树的根的双亲为e
		}
		cur->leftChild = child;					// e成为cur的左孩子
		child->parent = cur;					// e的双亲为cur
		return;
	}
}

template <class ElemType>
void TriLkBinaryTree<ElemType>::InsertRightChild(TriLkBinTreeNode<ElemType> *cur, const ElemType &e)
// 初始条件：cur非空
// 操作结果：插入元素值为e的结点为cur的右孩子，如果cur的右孩子非空，则cur原有右子树成为e的右子树
{
	if (cur == NULL)
	{	// cur为空，返回
		return;
	}
	else
	{	// 插入右孩子
		TriLkBinTreeNode<ElemType> *child =  new TriLkBinTreeNode<ElemType>(e);// 元素值为e结点
		if (cur->rightChild != NULL)
		{	// cur的右孩子非空
			child->rightChild = cur->rightChild;// cur原有右子树成为e的右子树
			cur->rightChild->parent = child;	// cur原有右子树成的根的双亲为child
		}
		cur->rightChild = child;				// e成为cur的右孩子
		child->parent= cur;						// e的双亲为cur
		return;
	}
}

template <class ElemType>
void TriLkBinaryTree<ElemType>::DeleteLeftChild(TriLkBinTreeNode<ElemType> *cur)
// 初始条件：cur非空
// 操作结果：删除cur左子树
{
	if (cur == NULL)
	{	// cur为空
		return;
	}
	else
	{	// cur非空
		DestroyHelp(cur->leftChild);		// 删除cur左子树
	}
}

template <class ElemType>
void TriLkBinaryTree<ElemType>::DeleteRightChild(TriLkBinTreeNode<ElemType> *cur)
// 初始条件：cur非空
// 操作结果：删除cur右子树
{
	if (cur == NULL)
	{	// cur为空
		return;
	}
	else
	{	// cur非空
		DestroyHelp(cur->rightChild);		// 删除cur右子树
	}
}

template <class ElemType>
void TriLkBinaryTree<ElemType>::DestroyHelp(TriLkBinTreeNode<ElemType> *&r)
// 操作结果：销毁以r的二叉树
{
	if(r != NULL)
	{	// r非空,实施销毁
		DestroyHelp(r->leftChild);			// 销毁左子树
		DestroyHelp(r->rightChild);			// 销毁右子树
		delete r;							// 销毁根结点
		r = NULL;
	}
}

template <class ElemType>
TriLkBinTreeNode<ElemType> *TriLkBinaryTree<ElemType>::CopyTreeHelp(TriLkBinTreeNode<ElemType> *copy)
// 操作结果：将以copy为根的二叉树复制成新的二叉树,返回新二叉树的根
{
	if (copy == NULL)
	{	// 复制空二叉树
		return NULL;						// 空二叉树根为空	
	}
	else
	{	// 复制非空二叉树
		TriLkBinTreeNode<ElemType> *lChild = CopyTreeHelp(copy->leftChild);	// 复制左子树
		TriLkBinTreeNode<ElemType> *rChild = CopyTreeHelp(copy->rightChild);// 复制右子树
		TriLkBinTreeNode<ElemType> *r = new TriLkBinTreeNode<ElemType>(copy->data, lChild, rChild);
			// 复制根结点
		if (lChild != NULL) lChild->parent = r;		// lChild双亲为r
		if (rChild != NULL) rChild->parent = r;		// rChild双亲为r
		return r;
	}
}

template <class ElemType>
TriLkBinaryTree<ElemType>::TriLkBinaryTree(const TriLkBinaryTree<ElemType> &copy)
// 操作结果：由已知二叉树构造新二叉树——复制构造函数
{
	root = CopyTreeHelp(copy.root);				// 复制二叉树
}

template <class ElemType>
TriLkBinaryTree<ElemType>::TriLkBinaryTree(TriLkBinTreeNode<ElemType> *r)
// 操作结果：建立以r为根的二叉树
{	
	root = r;								// 复制二叉树
}

template <class ElemType>
TriLkBinaryTree<ElemType> &TriLkBinaryTree<ElemType>::operator=(const TriLkBinaryTree<ElemType> &copy)
// 操作结果：由已知二叉树copy复制到当前二叉树--赋值运算符重载
{
	if (&copy != this)
	{
		DestroyHelp(root);					// 释放原二叉树所占用空间
		root = CopyTreeHelp(copy.root);			// 复制二叉树
	}
	return *this;
}

template <class ElemType>
void DisplayBTWithTreeShapeHelp(TriLkBinTreeNode<ElemType> *r, int level)
//	操作结果：按树状形式显示以r为根的二叉树，level为层次数，可设根结点的层次数为1
{
	if(r != NULL)
	{	//空树不显式，只显式非空树
		DisplayBTWithTreeShapeHelp<ElemType>(r->rightChild, level + 1);//显示右子树
		cout << endl;						// 显示新行	
		for(int i = 0; i < level - 1; i++)
			cout << " ";					// 确保在第level列显示结点
		cout << r->data;					// 显示结点
		DisplayBTWithTreeShapeHelp<ElemType>(r->leftChild, level + 1);//显示左子树
	}
}

template <class ElemType>
void DisplayBTWithTreeShape(TriLkBinaryTree<ElemType> &bt)
//	操作结果：树状形式显示二叉树 
{
	DisplayBTWithTreeShapeHelp<ElemType>(bt.GetRoot(), 1);	
		// 树状显示以bt.GetRoot()为根的二叉树
	cout << endl;
}

template <class ElemType>
void CreateBinaryTreeHelp(TriLkBinTreeNode<ElemType> *&r, ElemType pre[], ElemType in[], 
							int preLeft, int preRight, int inLeft, int inRight)	
// 操作结果：已知二叉树的先序序列pre[preLeft..preRight]和中序序列in[inLeft..inRight]构造
//	以r为根的二叉树
{
	if (inLeft > inRight)
	{	// 二叉树无结点,空二叉树
		r = NULL;							// 空二叉树根为空
	}
	else
	{	// 二叉树有结点,非空二叉树
		r = new TriLkBinTreeNode<ElemType>(pre[preLeft]);		// 生成根结点
		int mid = inLeft;
		while (in[mid] != pre[preLeft]) 
		{	// 查找pre[preLeft]在in[]中的位置,也就是中序序列中根的位置
			mid++;
		}
		CreateBinaryTreeHelp(r->leftChild, pre, in, preLeft+1, preLeft + mid - inLeft, inLeft, mid - 1);
			// 生成左子树
		if (r->leftChild != NULL) r->leftChild->parent = r;		// 左孩子的双亲为r
		CreateBinaryTreeHelp(r->rightChild, pre, in, preLeft + mid - inLeft + 1, preRight, mid + 1, 
			inRight);											// 生成右子树
		if (r->rightChild != NULL) r->rightChild->parent = r;	// 右孩子的双亲为r
	}
} 

template <class ElemType>
TriLkBinaryTree<ElemType> &CreateBinaryTree(ElemType pre[], ElemType in[], int n)
// 操作结果：已知先序和中序序列构造二叉树
{
	TriLkBinTreeNode<ElemType> *r;								// 二叉树的根
	CreateBinaryTreeHelp<ElemType>(r, pre, in, 0, n - 1, 0, n - 1);
		// 由先序和中序序列构造以r为根的二叉树 
	TriLkBinaryTree<ElemType> *bt = new TriLkBinaryTree<ElemType>(r);// 生成二叉树
	return *bt;
}

#endif
