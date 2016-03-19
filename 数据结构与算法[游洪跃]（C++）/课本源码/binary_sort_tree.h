#ifndef __BINNARY_TREE_H__
#define __BINNARY_TREE_H__

#include "lk_queue.h"				// 链队列
#include "bin_tree_node.h"			// 二叉树结点类

// 二叉排序树类
template <class ElemType, class KeyType>
class BinarySortTree
{
protected:
//  二叉排序树的数据成员:
	BinTreeNode<ElemType> *root;

//	辅助函数:
	BinTreeNode<ElemType> *CopyTreeHelp(BinTreeNode<ElemType> *copy);	// 复制二叉排序树
	void DestroyHelp(BinTreeNode<ElemType> * &r);						// 销毁以r为根二叉排序树
	void PreOrderHelp(BinTreeNode<ElemType> *r, void (*Visit)(const ElemType &)) const;	// 先序遍历
	void InOrderHelp(BinTreeNode<ElemType> *r, void (*Visit)(const ElemType &)) const;	// 中序遍历
	void PostOrderHelp(BinTreeNode<ElemType> *r, void (*Visit)(const ElemType &)) const;// 后序遍历
    int HeightHelp(const BinTreeNode<ElemType> *r) const;	// 返回二叉排序树的高
	int NodeCountHelp(const BinTreeNode<ElemType> *r) const;// 返回二叉排序树的结点个数
	BinTreeNode<ElemType> *ParentHelp(BinTreeNode<ElemType> *r, 
		const BinTreeNode<ElemType> *cur) const;			// 返回cur的双亲
	BinTreeNode<ElemType> *SearchHelp(const KeyType &key, BinTreeNode<ElemType> *&f) const;	
		// 查找关键字为key的数据元素
	void DeleteHelp(BinTreeNode<ElemType> *&p);				// 删除p指向的结点

public:
//  二叉排序树方法声明及重载编译系统默认方法声明:
	BinarySortTree();										// 无参数的构造函数
	virtual ~BinarySortTree();								// 析构函数
	BinTreeNode<ElemType> *GetRoot() const;					// 返回二叉排序树的根
	bool Empty() const;										// 判断二叉排序树是否为空
	StatusCode GetElem(BinTreeNode<ElemType> *cur, ElemType &e) const;
		// 用e返回结点数据元素值
	StatusCode SetElem(BinTreeNode<ElemType> *cur, const ElemType &e);
		// 将结cur的值置为e
	void InOrder(void (*Visit)(const ElemType &)) const;	// 二叉排序树的中序遍历	
	void PreOrder(void (*Visit)(const ElemType &)) const;	// 二叉排序树的先序遍历
	void PostOrder(void (*Visit)(const ElemType &)) const;	// 二叉排序树的后序遍历
	void LevelOrder(void (*Visit)(const ElemType &)) const;	// 二叉排序树的层次遍历
	int NodeCount() const;									// 求二叉排序树的结点个数
	BinTreeNode<ElemType> *Search(const KeyType &key) const;// 查找关键字为key的数据元素
	bool Insert(const ElemType &e);							// 插入数据元素e
	bool Delete(const KeyType &key);						// 删除关键字为key的数据元素
	BinTreeNode<ElemType> *LeftChild(const BinTreeNode<ElemType> *cur) const;
		// 返回二叉排序树结点cur的左孩子
	BinTreeNode<ElemType> *RightChild(const BinTreeNode<ElemType> *cur) const;
		// 返回二叉排序树结点cur的右孩子
	BinTreeNode<ElemType> *Parent(const BinTreeNode<ElemType> *cur) const;
		// 返回二叉排序树结点cur的双亲
	int	Height() const;										// 求二叉排序树的高
	BinarySortTree(const ElemType &e);						// 建立以e为根的二叉排序树
	BinarySortTree(const BinarySortTree<ElemType, KeyType> &copy);	// 复制构造函数
	BinarySortTree(BinTreeNode<ElemType> *r);				// 建立以r为根的二叉排序树
	BinarySortTree<ElemType, KeyType> &operator=
		(const BinarySortTree<ElemType, KeyType>& copy);	// 赋值语句重载
};

template <class ElemType, class KeyType>
void DisplayBTWithTreeShapeHelp(const BinTreeNode<ElemType> *r, int level);
	//	按树状形式显示以r为根的二叉排序树，level为层次数，可设根结点的层次数为1
template <class ElemType, class KeyType>
void DisplayBTWithTreeShape(const BinarySortTree<ElemType, KeyType> &bt);
	//	树状形式显示二叉排序树 

// 二叉排序树类的实现部分
template <class ElemType, class KeyType>
BinarySortTree<ElemType, KeyType>::BinarySortTree()
// 操作结果：构造一个空二叉排序树
{
	root = NULL;
}

template <class ElemType, class KeyType>
BinarySortTree<ElemType, KeyType>::~BinarySortTree()
// 操作结果：销毁二叉排序树--析造函数
{
	DestroyHelp(root);
}

template <class ElemType, class KeyType>
BinTreeNode<ElemType> *BinarySortTree<ElemType, KeyType>::GetRoot() const
// 操作结果：返回二叉排序树的根
{
	return root;
}

template <class ElemType, class KeyType>
bool BinarySortTree<ElemType, KeyType>::Empty() const
// 操作结果：判断二叉排序树是否为空
{
	return root == NULL;
}

template <class ElemType, class KeyType>
StatusCode BinarySortTree<ElemType, KeyType>::GetElem(BinTreeNode<ElemType> *cur, ElemType &e) const
// 操作结果：用e返回结点cur数据元素值,如果不存在结点cur,函数返回NOT_PRESENT,否则返回ENTRY_FOUND
{
	if (cur == NULL)	
	{	// 不存在结点cur
		return NOT_PRESENT;			// 返回NOT_PRESENT
	}
	else
	{	// 存在结点cur
		e = cur->data;				// 用e返回数据元素值
		return ENTRY_FOUND;			// 返回ENTRY_FOUND
	}
}

template <class ElemType, class KeyType>
StatusCode BinarySortTree<ElemType, KeyType>::SetElem(BinTreeNode<ElemType> *cur, const ElemType &e)
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

template <class ElemType, class KeyType>
void BinarySortTree<ElemType, KeyType>::PreOrderHelp(BinTreeNode<ElemType> *r, void (*Visit)(const ElemType &)) const
// 操作结果：先序遍历以r为根的二叉排序树
{
	if (r != NULL) 
	{
		(*Visit)(r->data);					// 访问根结点
		PreOrderHelp(r->leftChild, Visit);	// 遍历左子树
		PreOrderHelp(r->rightChild, Visit);	// 遍历右子树
	}
}

template <class ElemType, class KeyType>
void BinarySortTree<ElemType, KeyType>::PreOrder(void (*Visit)(const ElemType &)) const
// 操作结果：先序遍历二叉排序树
{
	PreOrderHelp(root, Visit);	
}	

template <class ElemType, class KeyType>
void BinarySortTree<ElemType, KeyType>::InOrderHelp(BinTreeNode<ElemType> *r, void (*Visit)(const ElemType &)) const
// 操作结果：中序遍历以r为根的二叉排序树
{
	if (r != NULL) 
	{
		InOrderHelp(r->leftChild, Visit);	// 遍历左子树
		(*Visit)(r->data);					// 访问根结点
		InOrderHelp(r->rightChild, Visit);	// 遍历右子树
	}
}

template <class ElemType, class KeyType>
void BinarySortTree<ElemType, KeyType>::InOrder(void (*Visit)(const ElemType &)) const
// 操作结果：中序遍历二叉排序树
{
	InOrderHelp(root, Visit);	
}	

template <class ElemType, class KeyType>
void BinarySortTree<ElemType, KeyType>::PostOrderHelp(BinTreeNode<ElemType> *r, void (*Visit)(const ElemType &)) const
// 操作结果：后序遍历以r为根的二叉排序树
{
	if (r != NULL) 
	{
		PostOrderHelp(r->leftChild, Visit);	// 遍历左子树
		PostOrderHelp(r->rightChild, Visit);// 遍历右子树
		(*Visit)(r->data);					// 访问根结点
	}
}

template <class ElemType, class KeyType>
void BinarySortTree<ElemType, KeyType>::PostOrder(void (*Visit)(const ElemType &)) const
// 操作结果：后序遍历二叉排序树
{
	PostOrderHelp(root, Visit);	
}	

template <class ElemType, class KeyType>
void BinarySortTree<ElemType, KeyType>::LevelOrder(void (*Visit)(const ElemType &)) const
// 操作结果：层次遍历二叉排序树
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

template <class ElemType, class KeyType>
int BinarySortTree<ElemType, KeyType>::HeightHelp(const BinTreeNode<ElemType> *r) const
// 操作结果：返回以r为根的二叉排序树的高
{
	if(r == NULL)
	{	// 空二叉排序树高为0
		return 0;
	}
	else
	{	// 非空二叉排序树高为左右子树的高的最大值再加1
		int lHeight, rHeight;
		lHeight = HeightHelp(r->leftChild);		// 左子树的高
		rHeight = HeightHelp(r->rightChild);	// 右子树的高
		return 1 + (lHeight > rHeight ? lHeight : rHeight);
			// 非空二叉排序树高为左右子树的高的最大值再加1
	}
}

template <class ElemType, class KeyType>
int BinarySortTree<ElemType, KeyType>::Height() const
// 操作结果：返回二叉排序树的高
{
	return HeightHelp(root);
}

template <class ElemType, class KeyType>
BinarySortTree<ElemType, KeyType>::BinarySortTree(const ElemType &e)
// 操作结果：建立以e为根的二叉排序树
{
	root = new BinTreeNode<ElemType>(e);
}

template <class ElemType, class KeyType>
int BinarySortTree<ElemType, KeyType>::NodeCountHelp(const BinTreeNode<ElemType> *r) const
// 操作结果：返回以r为根的二叉排序树的结点个数
{
	if (r ==NULL) return 0;			// 空二叉排序树结点个数为0
	else return 1 + NodeCountHelp(r->leftChild) + NodeCountHelp(r->rightChild);
		// 非空二叉排序树结点个为左右子树的结点个数之和再加1
}

template <class ElemType, class KeyType>
int BinarySortTree<ElemType, KeyType>::NodeCount() const
// 操作结果：返回二叉排序树的结点个数
{
	return NodeCountHelp(root);
}

template <class ElemType, class KeyType>
BinTreeNode<ElemType> *BinarySortTree<ElemType, KeyType>::LeftChild(const BinTreeNode<ElemType> *cur) const
// 操作结果：返回二叉排序树结点cur的左孩子
{
	return cur->leftChild;
}

template <class ElemType, class KeyType>
BinTreeNode<ElemType> *BinarySortTree<ElemType, KeyType>::RightChild(const BinTreeNode<ElemType> *cur) const
// 操作结果：返回二叉排序树结点cur的右孩子
{
	return cur->rightChild;
}

template <class ElemType, class KeyType>
BinTreeNode<ElemType> * BinarySortTree<ElemType, KeyType>::ParentHelp(BinTreeNode<ElemType> *r, const BinTreeNode<ElemType> *cur) const
// 操作结果：返回以r为根的二叉排序树, 结点cur的双亲
{
	if (r == NULL) return NULL;		// 空二叉排序树
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

template <class ElemType, class KeyType>
BinTreeNode<ElemType> *BinarySortTree<ElemType, KeyType>::Parent(const BinTreeNode<ElemType> *cur) const
// 操作结果：返回二叉排序树结点cur的双亲
{
	return ParentHelp(root, cur);
}

template <class ElemType, class KeyType>
BinTreeNode<ElemType> *BinarySortTree<ElemType, KeyType>::SearchHelp(const KeyType &key, 
	BinTreeNode<ElemType> *&f) const
// 操作结果: 返回指向关键字为key的数据元素的指针,用f返回其双亲
{
	BinTreeNode< ElemType> *p = GetRoot();	// 指向当前结点
	f = NULL;								// 指向p的双亲
	
	while (p != NULL && p->data != key)
	{	// 查找关键字为key的结点
		if (key < p->data)
		{	// key更小,在左子树上进行查找
			f = p;
			p = p->leftChild;
		}
		else
		{	// key更大,在右子树上进行查找
			f = p;
			p = p->rightChild;
		}
	}
	
	return p;
}

template <class ElemType, class KeyType>
BinTreeNode<ElemType> *BinarySortTree<ElemType, KeyType>::Search(const KeyType &key)	const 
// 操作结果: 返回指向关键字为key的数据元素的指针
{
	BinTreeNode<ElemType> *f;			// 指向被查找结点的双亲
	return SearchHelp(key, f);
}

template <class ElemType, class KeyType>
bool BinarySortTree<ElemType, KeyType>::Insert(const ElemType &e)
// 操作结果: 插入数据元素e
{
	BinTreeNode<ElemType> *f;			// 指向被查找结点的双亲

	if (SearchHelp(e, f) == NULL)
	{	// 查找失败, 插入成功
		BinTreeNode<ElemType> *p;		// 插入的新结点
		p = new BinTreeNode<ElemType>(e);
		if (Empty())
		{	// 空二叉树,新结点为根结点
			root = p;
		}
		else if (e < f->data)
		{	// e更小,插入结点为f的左孩子
			f->leftChild = p;
		}
		else
		{	// e更大,插入结点为f的右孩子
			f->rightChild = p;
		}

		return true;		
	}
	else
	{	// 查找成功, 插入失败
		return false;
	}
}

template <class ElemType, class KeyType>
void BinarySortTree<ElemType, KeyType>::DeleteHelp(BinTreeNode<ElemType> *&p)
// 操作结果: 删除p指向的结点
{
	BinTreeNode<ElemType> *tmpPtr, *tmpF;  
	if (p->leftChild == NULL && p->rightChild == NULL)
	{	// p为叶结点
		delete p;
		p = NULL;
	}
	else if (p->leftChild == NULL)
	{	// p只有左子树为空
		tmpPtr = p;
		p = p->rightChild;
		delete tmpPtr;
	}
	else if (p->rightChild == NULL)
	{	// p只有右子树非空
		tmpPtr = p;
		p = p->leftChild;
		delete tmpPtr;
	}
	else
	{	// p左右子非空
		tmpF = p;
		tmpPtr = p->leftChild;
		while (tmpPtr->rightChild != NULL)
		{	// 查找p在中序序列中直接前驱tmpPtr及其双亲tmpF,直到tmpPtr右子树为空
			tmpF = tmpPtr;
			tmpPtr = tmpPtr->rightChild;
		}
		p->data = tmpPtr->data;
			// 将tmpPtr指向结点的数据元素值赋值给tmpF指向结点的数据元素值

		// 删除tmpPtr指向的结点
		if (tmpF->rightChild == tmpPtr)
		{	// 删除tmpF的右孩子
			DeleteHelp(tmpF->rightChild);
		}
		else
		{	// 删除tmpF的左孩子
			DeleteHelp(tmpF->leftChild);
		}
	}
}

template <class ElemType, class KeyType>
bool BinarySortTree<ElemType, KeyType>::Delete(const KeyType &key)
// 操作结果: 删除关键字为key的数据元素
{
	BinTreeNode<ElemType> *p, *f;
	p = SearchHelp(key, f);
	if ( p == NULL)
	{	// 查找失败, 删除失败
		return false;
	}
	else
	{	// 查找成功, 插入失败
		if (f == NULL)
		{	// 被删除结点为根结点
			DeleteHelp(root);
		}
		else if (key < f->data)
		{	// elem.key更小,删除f的左孩子
			DeleteHelp(f->leftChild);
		}
		else
		{	// elem.key更大, 删除f的右孩子
			DeleteHelp(f->rightChild);
		}
		return true;		
	}
}

template <class ElemType, class KeyType>
void BinarySortTree<ElemType, KeyType>::DestroyHelp(BinTreeNode<ElemType> *&r)
// 操作结果：销毁以r的二叉排序树
{
	if(r != NULL)
	{	// r非空,实施销毁
		DestroyHelp(r->leftChild);		// 销毁左子树
		DestroyHelp(r->rightChild);		// 销毁右子树
		delete r;						// 销毁根结点
		r = NULL;
	}
}

template <class ElemType, class KeyType>
BinTreeNode<ElemType> *BinarySortTree<ElemType, KeyType>::CopyTreeHelp(BinTreeNode<ElemType> *copy)
// 操作结果：将以copy为根的二叉排序树复制成新的二叉排序树,返回新二叉排序树的根
{
	if (copy == NULL)
	{	// 复制空二叉排序树
		return NULL;					// 空二叉排序树根为空	
	}
	else
	{	// 复制非空二叉排序树
		BinTreeNode<ElemType> *lChild = CopyTreeHelp(copy->leftChild);	// 复制左子树
		BinTreeNode<ElemType> *rChild = CopyTreeHelp(copy->rightChild);	// 复制右子树
		BinTreeNode<ElemType> *r = new BinTreeNode<ElemType>(copy->data, lChild, rChild);
			// 复制根结点
		return r;
	}
}

template <class ElemType, class KeyType>
BinarySortTree<ElemType, KeyType>::BinarySortTree(const BinarySortTree<ElemType, KeyType> &copy)
// 操作结果：由已知二叉排序树构造新二叉排序树——复制构造函数
{
	root = CopyTreeHelp(copy.root);	// 复制二叉排序树
}

template <class ElemType, class KeyType>
BinarySortTree<ElemType, KeyType>::BinarySortTree(BinTreeNode<ElemType> *r)
// 操作结果：建立以r为根的二叉排序树
{	
	root = r;	// 复制二叉排序树
}

template <class ElemType, class KeyType>
BinarySortTree<ElemType, KeyType> &BinarySortTree<ElemType, KeyType>::operator=(const BinarySortTree<ElemType, KeyType> &copy)
// 操作结果：由已知二叉排序树copy复制到当前二叉排序树--赋值语句重载
{
	if (&copy != this)
	{
		DestroyHelp(root);				// 释放原二叉排序树所占用空间
		root = CopyTreeHelp(copy.root);	// 复制二叉排序树
	}
	return *this;
}

template <class ElemType, class KeyType>
void DisplayBTWithTreeShapeHelp(const BinTreeNode<ElemType> *r, int level)
//	操作结果：按树状形式显示以r为根的二叉排序树，level为层次数，可设根结点的层次数为1
{
	if(r != NULL)
	{	//空树不显式，只显式非空树
		DisplayBTWithTreeShapeHelp<ElemType, KeyType>(r->rightChild, level + 1);//显示右子树
		cout << endl;					//显示新行	
		for(int i = 0; i < level - 1; i++)
			cout << " ";				//确保在第level列显示结点
		cout << r->data;				//显示结点
		DisplayBTWithTreeShapeHelp<ElemType, KeyType>(r->leftChild, level + 1);//显示左子树
	}
}

template <class ElemType, class KeyType>
void DisplayBTWithTreeShape(const BinarySortTree<ElemType, KeyType> &bt)
//	操作结果：树状形式显示二叉排序树 
{
	DisplayBTWithTreeShapeHelp<ElemType, KeyType>(bt.GetRoot(), 1);	
		// 树状显示以bt.GetRoot()为根的二叉排序树
	cout << endl;
}

#endif
