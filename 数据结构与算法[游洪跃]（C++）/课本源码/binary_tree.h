#ifndef __BINNARY_TREE_H__
#define __BINNARY_TREE_H__

#include "lk_queue.h"				// 链队列
#include "bin_tree_node.h"			// 二叉树结点类

// 二叉树类
template <class ElemType>
class BinaryTree
{
protected:
//  二叉树的数据成员:
	BinTreeNode<ElemType> *root;

//	辅助函数:
	BinTreeNode<ElemType> *CopyTreeHelp(BinTreeNode<ElemType> *copy);	// 复制二叉树
	void DestroyHelp(BinTreeNode<ElemType> * &r);						// 销毁以r为根二叉树
	void PreOrderHelp(BinTreeNode<ElemType> *r, void (*Visit)(const ElemType &)) const ;	// 先序遍历
	void InOrderHelp(BinTreeNode<ElemType> *r, void (*Visit)(const ElemType &)) const ;	// 中序遍历
	void PostOrderHelp(BinTreeNode<ElemType> *r, void (*Visit)(const ElemType &)) const ;// 后序遍历
    int HeightHelp(const BinTreeNode<ElemType> *r) const;	// 返回二叉树的高
	int NodeCountHelp(const BinTreeNode<ElemType> *r) const;// 返回二叉树的结点个数
	BinTreeNode<ElemType> *ParentHelp(BinTreeNode<ElemType> *r, 
		const BinTreeNode<ElemType> *cur) const;			// 返回cur的双亲

public:
//  二叉树方法声明及重载编译系统默认方法声明:
	BinaryTree();											// 无参数的构造函数
	virtual ~BinaryTree();									// 析构函数
	BinTreeNode<ElemType> *GetRoot() const;					// 返回二叉树的根
	bool Empty() const;										// 判断二叉树是否为空
	StatusCode GetElem(BinTreeNode<ElemType> *cur, ElemType &e) const;
		// 用e返回结点元素值
	StatusCode SetElem(BinTreeNode<ElemType> *cur, const ElemType &e);
		// 将结点cur的值置为e
	void InOrder(void (*Visit)(const ElemType &)) const;	// 二叉树的中序遍历	
	void PreOrder(void (*Visit)(const ElemType &)) const;	// 二叉树的先序遍历
	void PostOrder(void (*Visit)(const ElemType &)) const;	// 二叉树的后序遍历
	void LevelOrder(void (*Visit)(const ElemType &)) const;	// 二叉树的层次遍历
	int NodeCount() const;									// 求二叉树的结点个数
	BinTreeNode<ElemType> *LeftChild(const BinTreeNode<ElemType> *cur) const;
		// 返回二叉树结点cur的左孩子
	BinTreeNode<ElemType> *RightChild(const BinTreeNode<ElemType> *cur) const;
		// 返回二叉树结点cur的右孩子
	BinTreeNode<ElemType> *Parent(const BinTreeNode<ElemType> *cur) const;
		// 返回二叉树结点cur的双亲
	void InsertLeftChild(BinTreeNode<ElemType> *cur, const ElemType &e);// 插入左孩子
	void InsertRightChild(BinTreeNode<ElemType> *cur, const ElemType &e);// 插入右孩子
	void DeleteLeftChild(BinTreeNode<ElemType> *cur);		// 删除左子树
	void DeleteRightChild(BinTreeNode<ElemType> *cur);		// 删除右子村
	int	Height() const;										// 求二叉树的高
	BinaryTree(const ElemType &e);							// 建立以e为根的二叉树
	BinaryTree(const BinaryTree<ElemType> &copy);			// 复制构造函数
	BinaryTree(BinTreeNode<ElemType> *r);					// 建立以r为根的二叉树
	BinaryTree<ElemType> &operator=(const BinaryTree<ElemType>& copy);	// 赋值运算符重载
};

template <class ElemType>
void DisplayBTWithTreeShapeHelp(BinTreeNode<ElemType> *r, int level);
	//	按树状形式显示以r为根的二叉树，level为层次数，可设根结点的层次数为1
template <class ElemType>
void DisplayBTWithTreeShape(BinaryTree<ElemType> &bt);
	//	树状形式显示二叉树 
template <class ElemType>
void CreateBinaryTreeHelp(BinTreeNode<ElemType> *&r, ElemType pre[], ElemType in[], 
	int preLeft, int preRight, int inLeft, int inRight);	
	// 已知二叉树的先序序列pre[preLeft..preRight]和中序序列in[inLeft..inRight]构造以r为根的
	// 二叉树
template <class ElemType>
BinaryTree<ElemType> &CreateBinaryTree(ElemType pre[], ElemType in[], int n);
	// 已知先序和中序序列构造二叉树



// 二叉树类的实现部分
template <class ElemType>
BinaryTree<ElemType>::BinaryTree()
// 操作结果：构造一个空二叉树
{
	root = NULL;
}

template <class ElemType>
BinaryTree<ElemType>::~BinaryTree()
// 操作结果：销毁二叉树--析造函数
{
	DestroyHelp(root);
}

template <class ElemType>
BinTreeNode<ElemType> *BinaryTree<ElemType>::GetRoot() const
// 操作结果：返回二叉树的根
{
	return root;
}

template <class ElemType>
bool BinaryTree<ElemType>::Empty() const
// 操作结果：判断二叉树是否为空
{
	return root == NULL;
}

template <class ElemType>
StatusCode BinaryTree<ElemType>::GetElem(BinTreeNode<ElemType> *cur, ElemType &e) const
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
StatusCode BinaryTree<ElemType>::SetElem(BinTreeNode<ElemType> *cur, const ElemType &e)
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
void BinaryTree<ElemType>::PreOrderHelp(BinTreeNode<ElemType> *r, void (*Visit)(const ElemType &)) const
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
void BinaryTree<ElemType>::PreOrder(void (*Visit)(const ElemType &)) const
// 操作结果：先序遍历二叉树
{
	PreOrderHelp(root, Visit);	
}	

template <class ElemType>
void BinaryTree<ElemType>::InOrderHelp(BinTreeNode<ElemType> *r, void (*Visit)(const ElemType &)) const
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
void BinaryTree<ElemType>::InOrder(void (*Visit)(const ElemType &)) const
// 操作结果：中序遍历二叉树
{
	InOrderHelp(root, Visit);	
}	

template <class ElemType>
void BinaryTree<ElemType>::PostOrderHelp(BinTreeNode<ElemType> *r, void (*Visit)(const ElemType &)) const
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
void BinaryTree<ElemType>::PostOrder(void (*Visit)(const ElemType &)) const
// 操作结果：后序遍历二叉树
{
	PostOrderHelp(root, Visit);	
}	

template <class ElemType>
void BinaryTree<ElemType>::LevelOrder(void (*Visit)(const ElemType &)) const
// 操作结果：层次遍历二叉树
{
	LinkQueue<BinTreeNode<ElemType> *> q;	// 队列
	BinTreeNode<ElemType> *t = root;		// 从根结点开始进行层次遍历
	
	if (t != NULL) q.InQueue(t);			// 如果根非空,则入队
	while (!q.Empty())
	{	// q非空,说明还有结点未访问
		q.OutQueue(t);     
		(*Visit)(t->data);
		if (t->leftChild != NULL)			// 左孩子非空
			q.InQueue(t->leftChild);		// 左孩子入队
		if (t->rightChild != NULL)			// 右孩子非空
			q.InQueue(t->rightChild);		// 右孩子入队
	}
}

template <class ElemType>
int BinaryTree<ElemType>::HeightHelp(const BinTreeNode<ElemType> *r) const
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
		return (lHeight > rHeight ? lHeight : rHeight) + 1;
			// 非空二叉树高为左右子树的高的最大值再加1
	}
}

template <class ElemType>
int BinaryTree<ElemType>::Height() const
// 操作结果：返回二叉树的高
{
	return HeightHelp(root);
}

template <class ElemType>
BinaryTree<ElemType>::BinaryTree(const ElemType &e)
// 操作结果：建立以e为根的二叉树
{
	root = new BinTreeNode<ElemType>(e);
}

template <class ElemType>
int BinaryTree<ElemType>::NodeCountHelp(const BinTreeNode<ElemType> *r) const
// 操作结果：返回以r为根的二叉树的结点个数
{
	if (r ==NULL) return 0;			// 空二叉树结点个数为0
	else return NodeCountHelp(r->leftChild) + NodeCountHelp(r->rightChild) + 1;
		// 非空二叉树结点个为左右子树的结点个数之和再加1
}

template <class ElemType>
int BinaryTree<ElemType>::NodeCount() const
// 操作结果：返回二叉树的结点个数
{
	return NodeCountHelp(root);
}

template <class ElemType>
BinTreeNode<ElemType> *BinaryTree<ElemType>::LeftChild(const BinTreeNode<ElemType> *cur) const
// 操作结果：返回二叉树结点cur的左孩子
{
	return cur->leftChild;
}

template <class ElemType>
BinTreeNode<ElemType> *BinaryTree<ElemType>::RightChild(const BinTreeNode<ElemType> *cur) const
// 操作结果：返回二叉树结点cur的右孩子
{
	return cur->rightChild;
}

template <class ElemType>
BinTreeNode<ElemType> * BinaryTree<ElemType>::ParentHelp(BinTreeNode<ElemType> *r, const BinTreeNode<ElemType> *cur) const
// 操作结果：返回以r为根的二叉树, 结点cur的双亲
{
	if (r == NULL) return NULL;		// 空二叉树
	else if (r->leftChild == cur || r->rightChild == cur) return r; // r为cur的双亲
	else
	{	// 在子树上求双亲
		BinTreeNode<ElemType> *tmp;
		
		tmp = ParentHelp(r->leftChild, cur);	// 在左子树上求cur的双亲	
		if (tmp != NULL) return tmp;			// 双亲在左子树上

		tmp = ParentHelp(r->rightChild, cur);	// 在右子树上求cur的双亲	
		if (tmp != NULL) return tmp;			// 双亲在右子树上
		else return NULL;						// 表示cur无双亲
	}
}

template <class ElemType>
BinTreeNode<ElemType> *BinaryTree<ElemType>::Parent(const BinTreeNode<ElemType> *cur) const
// 操作结果：返回二叉树结点cur的双亲
{
	return ParentHelp(root, cur);
}

template <class ElemType>
void BinaryTree<ElemType>::InsertLeftChild(BinTreeNode<ElemType> *cur, const ElemType &e)
// 初始条件：cur非空，
// 操作结果：插入元素值为e的结点为cur的左孩子，如果cur的左孩子非空，则cur原有左子树成为e的左子树
{
	if (cur == NULL)
	{	// cur空，返回
		return;
	}
	else 
	{	// 插入左孩子
		BinTreeNode<ElemType> *child =  new BinTreeNode<ElemType>(e);// 元素值为e结点
		if (cur->leftChild != NULL)
		{	// cur的左孩子非空
			child->leftChild = cur->leftChild;	// cur原有左子树成为e的左子树
		}
		cur->leftChild = child;					// e成为cur的左孩子
		return;
	}
}

template <class ElemType>
void BinaryTree<ElemType>::InsertRightChild(BinTreeNode<ElemType> *cur, const ElemType &e)
// 初始条件：cur非空
// 操作结果：插入元素值为e的结点为cur的右孩子，如果cur的右孩子非空，则cur原有右子树成为e的右子树
{
	if (cur == NULL)
	{	// cur为空，返回
		return;
	}
	else
	{	// 插入右孩子
		BinTreeNode<ElemType> *child =  new BinTreeNode<ElemType>(e);// 元素值为e结点
		if (cur->rightChild != NULL)
		{	// cur的右孩子非空
			child->rightChild = cur->rightChild;	// cur原有右子树成为e的右子树
		}
		cur->rightChild = child;					// e成为cur的右孩子
		return;
	}
}

template <class ElemType>
void BinaryTree<ElemType>::DeleteLeftChild(BinTreeNode<ElemType> *cur)
// 初始条件：cur非空
// 操作结果：删除cur左子树
{
	if (cur == NULL)
	{	// cur为空
		return;
	}
	else
	{	// cur非空
		DestroyHelp(cur->leftChild);	// 删除cur左子树
	}
}

template <class ElemType>
void BinaryTree<ElemType>::DeleteRightChild(BinTreeNode<ElemType> *cur)
// 初始条件：cur非空
// 操作结果：删除cur右子树
{
	if (cur == NULL)
	{	// cur为空
		return;
	}
	else
	{	// cur非空
		DestroyHelp(cur->rightChild);	// 删除cur右子树
	}
}

template <class ElemType>
void BinaryTree<ElemType>::DestroyHelp(BinTreeNode<ElemType> *&r)
// 操作结果：销毁以r的二叉树
{
	if(r != NULL)
	{	// r非空,实施销毁
		DestroyHelp(r->leftChild);		// 销毁左子树
		DestroyHelp(r->rightChild);		// 销毁右子树
		delete r;						// 销毁根结点
		r = NULL;
	}
}

template <class ElemType>
BinTreeNode<ElemType> *BinaryTree<ElemType>::CopyTreeHelp(BinTreeNode<ElemType> *copy)
// 操作结果：将以copy为根的二叉树复制成新的二叉树,返回新二叉树的根
{
	if (copy == NULL)
	{	// 复制空二叉树
		return NULL;					// 空二叉树根为空	
	}
	else
	{	// 复制非空二叉树
		BinTreeNode<ElemType> *lChild = CopyTreeHelp(copy->leftChild);	// 复制左子树
		BinTreeNode<ElemType> *rChild = CopyTreeHelp(copy->rightChild);	// 复制右子树
		BinTreeNode<ElemType> *r = new BinTreeNode<ElemType>(copy->data, lChild, rChild);
			// 复制根结点
		return r;
	}
}

template <class ElemType>
BinaryTree<ElemType>::BinaryTree(const BinaryTree<ElemType> &copy)
// 操作结果：由已知二叉树构造新二叉树——复制构造函数
{
	root = CopyTreeHelp(copy.root);	// 复制二叉树
}

template <class ElemType>
BinaryTree<ElemType>::BinaryTree(BinTreeNode<ElemType> *r)
// 操作结果：建立以r为根的二叉树
{	
	root = r;	// 复制二叉树
}

template <class ElemType>
BinaryTree<ElemType> &BinaryTree<ElemType>::operator=(const BinaryTree<ElemType> &copy)
// 操作结果：由已知二叉树copy复制到当前二叉树--赋值运算符重载
{
	if (&copy != this)
	{
		DestroyHelp(root);				// 释放原二叉树所占用空间
		root = CopyTreeHelp(copy.root);	// 复制二叉树
	}
	return *this;
}

template <class ElemType>
void DisplayBTWithTreeShapeHelp(BinTreeNode<ElemType> *r, int level)
// 操作结果：按树状形式显示以r为根的二叉树，level为层次数，可设根结点的层次数为1
{
	if(r != NULL)
	{	// 空树不显式，只显式非空树
		DisplayBTWithTreeShapeHelp<ElemType>(r->rightChild, level + 1);//显示右子树
		cout << endl;					//显示新行	
		for(int i = 0; i < level - 1; i++)
			cout << " ";				//确保在第level列显示结点
		cout << r->data;				//显示结点
		DisplayBTWithTreeShapeHelp<ElemType>(r->leftChild, level + 1);//显示左子树
	}
}

template <class ElemType>
void DisplayBTWithTreeShape(BinaryTree<ElemType> &bt)
// 操作结果：树状形式显示二叉树 
{
	DisplayBTWithTreeShapeHelp<ElemType>(bt.GetRoot(), 1);	
		// 树状显示以bt.GetRoot()为根的二叉树
	cout << endl;
}

template <class ElemType>
void CreateBinaryTreeHelp(BinTreeNode<ElemType> *&r, ElemType pre[], ElemType in[], 
							int preLeft, int preRight, int inLeft, int inRight)	
// 操作结果：已知二叉树的先序序列pre[preLeft..preRight]和中序序列in[inLeft..inRight]构造
//	以r为根的二叉树
{
	if (inLeft > inRight)
	{	// 二叉树无结点,空二叉树
		r = NULL;			// 空二叉树根为空
	}
	else
	{	// 二叉树有结点,非空二叉树
		r = new BinTreeNode<ElemType>(pre[preLeft]);// 生成根结点
		int mid = inLeft;
		while (in[mid] != pre[preLeft]) 
		{	// 查找pre[preLeft]在in[]中的位置,也就是中序序列中根的位置
			mid++;
		}
		CreateBinaryTreeHelp(r->leftChild, pre, in, preLeft+1, preLeft + mid - inLeft, inLeft, mid - 1);
			// 生成左子树
		CreateBinaryTreeHelp(r->rightChild, pre, in, preLeft + mid - inLeft + 1, preRight, mid + 1, 
			inRight);								// 生成右子树
	}
} 

template <class ElemType>
BinaryTree<ElemType> &CreateBinaryTree(ElemType pre[], ElemType in[], int n)
// 操作结果：已知先序和中序序列构造二叉树
{
	BinTreeNode<ElemType> *r;						// 二叉树的根
	CreateBinaryTreeHelp<ElemType>(r, pre, in, 0, n - 1, 0, n - 1);
		// 由先序和中序序列构造以r为根的二叉树 
	BinaryTree<ElemType> *bt = new BinaryTree<ElemType>(r);	// 生成二叉树
	return *bt;
}

#endif
