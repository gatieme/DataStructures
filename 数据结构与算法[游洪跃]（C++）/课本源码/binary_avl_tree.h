#ifndef __BINNARY_TREE_H__
#define __BINNARY_TREE_H__

#include "lk_queue.h"					// 链队列
#include "lk_stack.h"					// 链栈
#include "bin_avl_tree_node.h"			// 二叉平衡树结点类

// 二叉平衡树类
template <class ElemType, class KeyType>
class BinaryAVLTree
{
protected:
//  二叉平衡树的数据成员:
	BinAVLTreeNode<ElemType> *root;

//	辅助函数:
	BinAVLTreeNode<ElemType> *CopyTreeHelp(BinAVLTreeNode<ElemType> *copy);	// 复制二叉平衡树
	void DestroyHelp(BinAVLTreeNode<ElemType> * &r);						// 销毁以r为根二叉平衡树
	void PreOrderHelp(BinAVLTreeNode<ElemType> *r, void (*Visit)(const ElemType &)) const;	// 先序遍历
	void InOrderHelp(BinAVLTreeNode<ElemType> *r, void (*Visit)(const ElemType &)) const;	// 中序遍历
	void PostOrderHelp(BinAVLTreeNode<ElemType> *r, void (*Visit)(const ElemType &)) const;	// 后序遍历
    int HeightHelp(const BinAVLTreeNode<ElemType> *r) const;	// 返回二叉平衡树的高
	int NodeCountHelp(const BinAVLTreeNode<ElemType> *r) const;// 返回二叉平衡树的结点个数
	BinAVLTreeNode<ElemType> *ParentHelp(BinAVLTreeNode<ElemType> *r, 
		const BinAVLTreeNode<ElemType> *cur) const;			// 返回cur的双亲
	BinAVLTreeNode<ElemType> *SearchHelp(const KeyType &key, BinAVLTreeNode<ElemType> *&f) const;	
		// 查找关键字为key的数据元素

	BinAVLTreeNode<ElemType> *SearchHelp(const KeyType &key, BinAVLTreeNode<ElemType> *&f,
		LinkStack<BinAVLTreeNode<ElemType> *> &s); // 返回指向关键字为key的元素的指针,用f返回其双亲
	void LeftRotate(BinAVLTreeNode<ElemType> *&subRoot);
		// 对以subRoot为根的二叉树作左旋处理,处理之后subRoot指向新的树根结点,也就是旋转处理前的右子
		// 树的根结点
	void RightRotate(BinAVLTreeNode<ElemType> *&subRoot);
		// 对以subRoot为根的二叉树作右旋处理,处理之后subRoot指向新的树根结点,也就是旋转处理前的左子
		// 树的根结点
	void InsertLeftBalance(BinAVLTreeNode<ElemType> *&subRoot);
		// 对以subRoot为根的二叉树插入时作左平衡处理,处理后subRoot指向新的树根结点
	void InsertRightBalance(BinAVLTreeNode<ElemType> *&subRoot);
		// 对以subRoot为根的二叉树插入时作右平衡处理,处理后subRoot指向新的树根结点
	void InsertBalance(const ElemType &elem, LinkStack< BinAVLTreeNode<ElemType> *> &s);
		// 从插入结点elem根据查找路径进行回溯,并作平衡处理
	void DeleteLeftBalance(BinAVLTreeNode<ElemType> *&subRoot, bool &isShorter);
		// 对以subRoot为根的二叉树删除时作左平衡处理,处理后subRoot指向新的树根结点
	void DeleteRightBalance(BinAVLTreeNode<ElemType> *&subRoot, bool &isShorter);
		// 对以subRoot为根的二叉树删除时作右平衡处理,处理后subRoot指向新的树根结点
	void DeleteBalance(const KeyType &key, LinkStack<BinAVLTreeNode<ElemType> *> &s);
		// 从删除结点根据查找路径进行回溯,并作平衡处理
	void DeleteHelp(const KeyType &key, BinAVLTreeNode<ElemType> *&p,
		LinkStack< BinAVLTreeNode<ElemType> *> &s);		// 删除p指向的结点

public:
//  二叉平衡树方法声明及重载编译系统默认方法声明:
	BinaryAVLTree();										// 无参数的构造函数
	virtual ~BinaryAVLTree();								// 析构函数
	BinAVLTreeNode<ElemType> *GetRoot() const;				// 返回二叉平衡树的根
	bool Empty() const;										// 判断二叉平衡树是否为空
	StatusCode GetElem(BinAVLTreeNode<ElemType> *cur, ElemType &e) const;
		// 用e返回结点数据元素值
	StatusCode SetElem(BinAVLTreeNode<ElemType> *cur, const ElemType &e);
		// 将结cur的值置为e
	void InOrder(void (*Visit)(const ElemType &)) const;	// 二叉平衡树的中序遍历	
	void PreOrder(void (*Visit)(const ElemType &)) const;	// 二叉平衡树的先序遍历
	void PostOrder(void (*Visit)(const ElemType &)) const;	// 二叉平衡树的后序遍历
	void LevelOrder(void (*Visit)(const ElemType &)) const;	// 二叉平衡树的层次遍历
	int NodeCount() const;									// 求二叉平衡树的结点个数
	BinAVLTreeNode<ElemType> *Search(const KeyType &key) const;// 查找关键字为key的数据元素
	bool Insert(const ElemType &e);							// 插入数据元素e
	bool Delete(const KeyType &key);						// 删除关键字为key的数据元素
	BinAVLTreeNode<ElemType> *LeftChild(const BinAVLTreeNode<ElemType> *cur) const;
		// 返回二叉平衡树结点cur的左孩子
	BinAVLTreeNode<ElemType> *RightChild(const BinAVLTreeNode<ElemType> *cur) const;
		// 返回二叉平衡树结点cur的右孩子
	BinAVLTreeNode<ElemType> *Parent(const BinAVLTreeNode<ElemType> *cur) const;
		// 返回二叉平衡树结点cur的双亲
	int	Height() const;										// 求二叉平衡树的高
	BinaryAVLTree(const ElemType &e);						// 建立以e为根的二叉平衡树
	BinaryAVLTree(const BinaryAVLTree<ElemType, KeyType> &copy);	// 复制构造函数
	BinaryAVLTree(BinAVLTreeNode<ElemType> *r);				// 建立以r为根的二叉平衡树
	BinaryAVLTree<ElemType, KeyType> &operator=(const BinaryAVLTree<ElemType, KeyType>& copy);	// 赋值语句重载
};

template <class ElemType, class KeyType>
void DisplayBTWithTreeShapeHelp(const BinAVLTreeNode<ElemType> *r, int level);
	//	按树状形式显示以r为根的二叉平衡树，level为层次数，可设根结点的层次数为1
template <class ElemType, class KeyType>
void DisplayBTWithTreeShape(const BinaryAVLTree<ElemType, KeyType> &bt);
	//	树状形式显示二叉平衡树 

// 二叉平衡树类的实现部分
template <class ElemType, class KeyType>
BinaryAVLTree<ElemType, KeyType>::BinaryAVLTree()
// 操作结果：构造一个空二叉平衡树
{
	root = NULL;
}

template <class ElemType, class KeyType>
BinaryAVLTree<ElemType, KeyType>::~BinaryAVLTree()
// 操作结果：销毁二叉平衡树--析造函数
{
	DestroyHelp(root);
}

template <class ElemType, class KeyType>
BinAVLTreeNode<ElemType> *BinaryAVLTree<ElemType, KeyType>::GetRoot() const
// 操作结果：返回二叉平衡树的根
{
	return root;
}

template <class ElemType, class KeyType>
bool BinaryAVLTree<ElemType, KeyType>::Empty() const
// 操作结果：判断二叉平衡树是否为空
{
	return root == NULL;
}

template <class ElemType, class KeyType>
StatusCode BinaryAVLTree<ElemType, KeyType>::GetElem(BinAVLTreeNode<ElemType> *cur, ElemType &e) const
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
StatusCode BinaryAVLTree<ElemType, KeyType>::SetElem(BinAVLTreeNode<ElemType> *cur, const ElemType &e)
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
void BinaryAVLTree<ElemType, KeyType>::PreOrderHelp(BinAVLTreeNode<ElemType> *r, void (*Visit)(const ElemType &)) const
// 操作结果：先序遍历以r为根的二叉平衡树
{
	if (r != NULL) 
	{
		(*Visit)(r->data);					// 访问根结点
		PreOrderHelp(r->leftChild, Visit);	// 遍历左子树
		PreOrderHelp(r->rightChild, Visit);	// 遍历右子树
	}
}

template <class ElemType, class KeyType>
void BinaryAVLTree<ElemType, KeyType>::PreOrder(void (*Visit)(const ElemType &)) const
// 操作结果：先序遍历二叉平衡树
{
	PreOrderHelp(root, Visit);	
}	

template <class ElemType, class KeyType>
void BinaryAVLTree<ElemType, KeyType>::InOrderHelp(BinAVLTreeNode<ElemType> *r, void (*Visit)(const ElemType &)) const
// 操作结果：中序遍历以r为根的二叉平衡树
{
	if (r != NULL) 
	{
		InOrderHelp(r->leftChild, Visit);	// 遍历左子树
		(*Visit)(r->data);					// 访问根结点
		InOrderHelp(r->rightChild, Visit);	// 遍历右子树
	}
}

template <class ElemType, class KeyType>
void BinaryAVLTree<ElemType, KeyType>::InOrder(void (*Visit)(const ElemType &)) const
// 操作结果：中序遍历二叉平衡树
{
	InOrderHelp(root, Visit);	
}	

template <class ElemType, class KeyType>
void BinaryAVLTree<ElemType, KeyType>::PostOrderHelp(BinAVLTreeNode<ElemType> *r, void (*Visit)(const ElemType &)) const
// 操作结果：后序遍历以r为根的二叉平衡树
{
	if (r != NULL) 
	{
		PostOrderHelp(r->leftChild, Visit);	// 遍历左子树
		PostOrderHelp(r->rightChild, Visit);// 遍历右子树
		(*Visit)(r->data);					// 访问根结点
	}
}

template <class ElemType, class KeyType>
void BinaryAVLTree<ElemType, KeyType>::PostOrder(void (*Visit)(const ElemType &)) const
// 操作结果：后序遍历二叉平衡树
{
	PostOrderHelp(root, Visit);	
}	

template <class ElemType, class KeyType>
void BinaryAVLTree<ElemType, KeyType>::LevelOrder(void (*Visit)(const ElemType &)) const
// 操作结果：层次遍历二叉平衡树
{
	LinkQueue<BinAVLTreeNode<ElemType> *> q;	// 队列
	BinAVLTreeNode<ElemType> *t = root;		// 从根结点开始进行层次遍历
	
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
int BinaryAVLTree<ElemType, KeyType>::HeightHelp(const BinAVLTreeNode<ElemType> *r) const
// 操作结果：返回以r为根的二叉平衡树的高
{
	if(r == NULL)
	{	// 空二叉平衡树高为0
		return 0;
	}
	else
	{	// 非空二叉平衡树高为左右子树的高的最大值再加1
		int lHeight, rHeight;
		lHeight = HeightHelp(r->leftChild);		// 左子树的高
		rHeight = HeightHelp(r->rightChild);	// 右子树的高
		return 1 + (lHeight > rHeight ? lHeight : rHeight);
			// 非空二叉平衡树高为左右子树的高的最大值再加1
	}
}

template <class ElemType, class KeyType>
int BinaryAVLTree<ElemType, KeyType>::Height() const
// 操作结果：返回二叉平衡树的高
{
	return HeightHelp(root);
}

template <class ElemType, class KeyType>
BinaryAVLTree<ElemType, KeyType>::BinaryAVLTree(const ElemType &e)
// 操作结果：建立以e为根的二叉平衡树
{
	root = new BinAVLTreeNode<ElemType>(e);
}

template <class ElemType, class KeyType>
int BinaryAVLTree<ElemType, KeyType>::NodeCountHelp(const BinAVLTreeNode<ElemType> *r) const
// 操作结果：返回以r为根的二叉平衡树的结点个数
{
	if (r ==NULL) return 0;			// 空二叉平衡树结点个数为0
	else return 1 + NodeCountHelp(r->leftChild) + NodeCountHelp(r->rightChild);
		// 非空二叉平衡树结点个为左右子树的结点个数之和再加1
}

template <class ElemType, class KeyType>
int BinaryAVLTree<ElemType, KeyType>::NodeCount() const
// 操作结果：返回二叉平衡树的结点个数
{
	return NodeCountHelp(root);
}

template <class ElemType, class KeyType>
BinAVLTreeNode<ElemType> *BinaryAVLTree<ElemType, KeyType>::LeftChild(const BinAVLTreeNode<ElemType> *cur) const
// 操作结果：返回二叉平衡树结点cur的左孩子
{
	return cur->leftChild;
}

template <class ElemType, class KeyType>
BinAVLTreeNode<ElemType> *BinaryAVLTree<ElemType, KeyType>::RightChild(const BinAVLTreeNode<ElemType> *cur) const
// 操作结果：返回二叉平衡树结点cur的右孩子
{
	return cur->rightChild;
}

template <class ElemType, class KeyType>
BinAVLTreeNode<ElemType> * BinaryAVLTree<ElemType, KeyType>::ParentHelp(BinAVLTreeNode<ElemType> *r, const BinAVLTreeNode<ElemType> *cur) const
// 操作结果：返回以r为根的二叉平衡树, 结点cur的双亲
{
	if (r == NULL) return NULL;		// 空二叉平衡树
	else if (r->leftChild == cur || r->rightChild == cur) return r; // r为cur的双亲
	else
	{	// 在子树上求双亲
		BinAVLTreeNode<ElemType> *tmp;
		
		tmp = ParentHelp(r->leftChild, cur);	// 在左子树上求cur的双亲	
		if (tmp != NULL) return tmp;			// 双亲在左子树上

		tmp = ParentHelp(r->rightChild, cur);	// 在右子树上求cur的双亲	
		if (tmp != NULL) return tmp;			// 双亲在右子树上
		else return NULL;						// 表示cur无双亲
	}
}

template <class ElemType, class KeyType>
BinAVLTreeNode<ElemType> *BinaryAVLTree<ElemType, KeyType>::Parent(const BinAVLTreeNode<ElemType> *cur) const
// 操作结果：返回二叉平衡树结点cur的双亲
{
	return ParentHelp(root, cur);
}

template <class ElemType, class KeyType>
BinAVLTreeNode<ElemType> *BinaryAVLTree<ElemType, KeyType>::SearchHelp(const KeyType &key, BinAVLTreeNode<ElemType> *&f) const
// 操作结果: 返回指向关键字为key的数据元素的指针,用f返回其双亲,栈s存储查找路径
{
	BinAVLTreeNode< ElemType> *p = GetRoot();	// 指向当前结点
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
BinAVLTreeNode<ElemType> *BinaryAVLTree<ElemType, KeyType>::Search(const KeyType &key)	const 
// 操作结果: 返回指向关键字为key的数据元素的指针
{
	BinAVLTreeNode<ElemType> *f;			// 指向被查找结点的双亲
	return SearchHelp(key, f);
}

template <class ElemType, class KeyType>
BinAVLTreeNode<ElemType> *BinaryAVLTree<ElemType, KeyType>::SearchHelp(
	const KeyType &key,	BinAVLTreeNode<ElemType> *&f,
	LinkStack<BinAVLTreeNode<ElemType> *> &s) 
// 操作结果: 返回指向关键字为key的元素的指针,用f返回其双亲
{
	BinAVLTreeNode<ElemType> *p = GetRoot();	// 指向当前结点
	f = NULL;		// 指向p的双亲
	while (p != NULL && p->data != key)
	{	// 查寻关键字为key的结点
		if (key < p->data)
		{	// key更小,在左子树上进行查找
			f = p;
			s.Push(p);
			p = p->leftChild;
		}
		else
		{	// key更大,在右子树上进行查找
			f = p;
			s.Push(p);
			p = p->rightChild;
		}
	}
	return p;
}

template <class ElemType, class KeyType>
void BinaryAVLTree<ElemType, KeyType>::LeftRotate(BinAVLTreeNode<ElemType> *&subRoot)
// 操作结果: 对以subRoot为根的二叉树作左旋处理,处理之后subRoot指向新的树根结点,
//	也就是旋转处理前的右子树的根结点
{
	BinAVLTreeNode<ElemType> *ptrRChild;
	ptrRChild = subRoot->rightChild;			// ptrRChild指向subRoot右孩子
	subRoot->rightChild = ptrRChild->leftChild;	// ptrRChild的左子树链接为subRoot的右子树
	ptrRChild->leftChild = subRoot;				// subRoot链接为ptrRChild的左孩子
	subRoot = ptrRChild;						// subRoot指向新的根结点
}

template <class ElemType, class KeyType>
void BinaryAVLTree<ElemType, KeyType>::RightRotate(BinAVLTreeNode<ElemType> *&subRoot)
// 操作结果: 对以subRoot为根的二叉树作右旋处理,处理之后subRoot指向新的树根结点,
//	也就是旋转处理前的左子树的根结点
{
	BinAVLTreeNode<ElemType> *pLChild;
	pLChild = subRoot->leftChild;				// pLChild指向subRoot左孩子
	subRoot->leftChild = pLChild->rightChild;	// pLChild的右子树链接为subRoot的左子树
	pLChild->rightChild = subRoot;				// subRoot链接为pLChild的右孩子
	subRoot = pLChild;							// subRoot指向新的根结点
}

template <class ElemType, class KeyType>
void BinaryAVLTree<ElemType, KeyType>::InsertLeftBalance(BinAVLTreeNode<ElemType> *&subRoot)
// 操作结果: 对以subRoot为根的二叉树插入时作左平衡处理,插入结点在subRoot左子树上,处理后
//	subRoot指向新的树根结点
{
	BinAVLTreeNode<ElemType> *ptrLChild, *ptrLRChild;	
	ptrLChild  = subRoot->leftChild;	// ptrLChild指向subRoot左孩子
	switch (ptrLChild->bf)
	{	// 根据subRoot的左子树的平衡因子作相应的平衡处理
	case LH:							// 插入结点在subRoot的左孩子的左子树上,作单右旋处理
		subRoot->bf = ptrLChild->bf = EH;// 平衡因子都为0
		RightRotate(subRoot);			// 右旋
		break;
	case RH:							// 插入结点在subRoot的左孩子的右子树上,作先左旋后右旋处理
		ptrLRChild = ptrLChild->rightChild;// ptrLRChild指向subRoot的左孩子的右子树的根
		switch (ptrLRChild->bf)
		{	// 修改subRoot及左孩子的平衡因子
		case LH:						// 插入结点在ptrLRChild的左子树上
			subRoot->bf = RH;
			ptrLChild->bf = EH;
			break;
		case EH:						// 插入前ptrLRChild为空,ptrLRChild指向插入结点
			subRoot->bf = ptrLChild->bf = EH;
			break;
		case RH:						// 插入结点在ptrLRChild的左子树上
			subRoot->bf = EH;
			ptrLChild->bf = LH;
			break;
		}
		ptrLRChild->bf = 0;
		LeftRotate(subRoot->leftChild);	// 对subRoot左子树作左旋处理
		RightRotate(subRoot);			// 对subRoot作右旋处理
	}
}

template <class ElemType, class KeyType>
void BinaryAVLTree<ElemType, KeyType>::InsertRightBalance(BinAVLTreeNode<ElemType> *&subRoot)
// 操作结果: 对以subRoot为根的二叉树插入时作右平衡处理,插入结点在subRoot左子树上,处理后
//	subRoot指向新的树根结点
{
	BinAVLTreeNode<ElemType> *ptrRChild, *ptrRLChild;	
	ptrRChild  = subRoot->rightChild;	// ptrRChild指向subRoot右孩子
	switch (ptrRChild->bf)
	{	// 根据subRoot的右子树的平衡因子作相应的平衡处理
	case RH:							// 插入结点在subRoot的右孩子的右子树上,作单左旋处理
		subRoot->bf = ptrRChild->bf = EH;// 平衡因子都为0
		LeftRotate(subRoot);			// 左旋
		break;
	case LH:							// 插入结点在subRoot的右孩子的左子树上,作先右旋后左旋处理
		ptrRLChild = ptrRChild->leftChild;// ptrRLChild指向subRoot的右孩子的左子树的根
		switch (ptrRLChild->bf)
		{	// 修改subRoot及右孩子的平衡因子
		case RH:						// 插入结点在ptrRLChild的右子树上
			subRoot->bf = LH;
			ptrRChild->bf = EH;
			break;
		case EH:						// 插入前ptrRLChild为空,ptrRLChild指向插入结点
			subRoot->bf = ptrRChild->bf = EH;
			break;
		case LH:						// 插入结点在ptrRLChild的左子树上
			subRoot->bf = EH;
			ptrRChild->bf = RH;
			break;
		}
		ptrRLChild->bf = 0;
		RightRotate(subRoot->rightChild);// 对subRoot右子树作右旋处理
		LeftRotate(subRoot);			// 对subRoot作左旋处理
	}
}

template <class ElemType, class KeyType>
void BinaryAVLTree<ElemType, KeyType>::InsertBalance(const ElemType &e,
	LinkStack<BinAVLTreeNode<ElemType> *> &s)
// 操作结果: 从插入元素e根据查找路径进行回溯,并作平衡处理
{
	bool isTaller = true;
	while (!s.Empty() && isTaller)
	{
		BinAVLTreeNode<ElemType> *ptrCurNode, *ptrParent;
		s.Pop(ptrCurNode);			// 取出待平衡的结点
		if (s.Empty())
		{	// ptrCurNode已为根结点,ptrParent为空
			ptrParent = NULL;
		}
		else
		{	// ptrCurNode不为根结点,取出双亲ptrParent
			s.Top(ptrParent);
		}

		if (e < ptrCurNode->data)
		{	// e插入在ptrCurNode的左子树上
			switch (ptrCurNode->bf)
			{	// 检查ptrCurNode的平衡度
			case LH:						// 插入后ptrCurNode->bf=2, 作左平衡处理
				if (ptrParent == NULL)
				{	// 已回溯到根结点
					InsertLeftBalance(ptrCurNode);	
					root = ptrCurNode;		// 转换后ptrCurNode为新根
				}
				else if (ptrParent->leftChild == ptrCurNode)
				{	// ptrParent左子树作平衡处理
					InsertLeftBalance(ptrParent->leftChild);
				}
				else
				{	// ptrParent右子树作平衡处理
					InsertLeftBalance(ptrParent->rightChild);
				}
				isTaller = false;
				break;
			case EH:					// 插入后ptrCurNode->bf=LH
				ptrCurNode->bf = LH;
				break;	
			case RH:					// 插入后ptrCurNode->bf=EH
				ptrCurNode->bf = EH;
				isTaller = false;
				break;
			}
		}
		else
		{	// e插入在ptrCurNode的右子树上
			switch (ptrCurNode->bf)
			{	// 检查ptrCurNode的平衡度
			case RH:						// 插入后ptrCurNode->bf=-2, 作右平衡处理
				if (ptrParent == NULL)
				{	// 已回溯到根结点
					InsertRightBalance(ptrCurNode);
					root = ptrCurNode;		// 转换后ptrCurNode为新根
				}
				else if (ptrParent->leftChild == ptrCurNode)
				{	// ptrParent左子树作平衡处理
					InsertRightBalance(ptrParent->leftChild);
				}
				else
				{	// ptrParent右子树作平衡处理
					InsertRightBalance(ptrParent->rightChild);
				}
				isTaller = false;
				break;
			case EH:						// 插入后ptrCurNode->bf=RH
				ptrCurNode->bf = RH;
				break;
			case LH:						// 插入后ptrCurNode->bf=EH
				ptrCurNode->bf = EH;
				isTaller = false;
				break;
			}
		}
	}
}

template <class ElemType, class KeyType>
bool BinaryAVLTree<ElemType, KeyType>::Insert(const ElemType &e)
// 操作结果: 插入数据元素e
{
	BinAVLTreeNode<ElemType> *f;
	LinkStack< BinAVLTreeNode<ElemType> *> s;
	if (SearchHelp(e, f, s) == NULL)
	{	// 查找失败, 插入成功
		BinAVLTreeNode<ElemType> *p;		// 插入的新结点
		p = new BinAVLTreeNode<ElemType>(e);// 生成插入结点
		p->bf = 0;
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

		InsertBalance(e, s);// 插入结点后作平衡处理
		return true;		
	}
	else
	{	// 查找成功, 插入失败
		return false;
	}
}

template <class ElemType, class KeyType>
void BinaryAVLTree<ElemType, KeyType>::DeleteLeftBalance(BinAVLTreeNode<ElemType> *&
subRoot, bool &isShorter)
// 操作结果: 对以subRoot为根的二叉树删除时作左平衡处理, 删除subRoot的左子树上的结点，处
//	理后subRoot指向新的树根结点
{
	BinAVLTreeNode<ElemType> *ptrRChild, *ptrRLChild;	
	ptrRChild  = subRoot->rightChild;		// ptrRChild指向subRoot右孩子
	switch (ptrRChild->bf)
	{	// 根据subRoot的右子树的平衡因子作相应的平衡处理
	case RH:								// 右高，作单左旋转
		subRoot->bf = ptrRChild->bf = EH;	// 平衡因子都为0
		LeftRotate(subRoot);				// 左旋
		isShorter = true;
		break;
	case EH:								// 等高，作单左旋转
		subRoot->bf = RH;
		ptrRChild->bf = LH;		
		LeftRotate(subRoot);				// 左旋
		isShorter = false;
		break;
	case LH:								// 左高,先右旋后左旋
		ptrRLChild = ptrRChild->leftChild;	// ptrRLChild指向subRoot的右孩子的左子树的根
		switch (ptrRLChild->bf)
		{	// 修改subRoot及右孩子的平衡因子
		case LH:
			subRoot->bf = EH;
			ptrRChild->bf = RH;
			isShorter = true;
			break;
		case EH:
			subRoot->bf = ptrRChild->bf = EH;
			isShorter = false;
			break;
		case RH:
			subRoot->bf = LH;
			ptrRChild->bf = EH;
			isShorter = true;
			break;
		}
		ptrRLChild->bf = 0;
		RightRotate(subRoot->rightChild);	// 对subRoot右子树作右旋处理
		LeftRotate(subRoot);				// 对subRoot作左旋处理
	}
}

template <class ElemType, class KeyType>
void BinaryAVLTree<ElemType, KeyType>::DeleteRightBalance(BinAVLTreeNode<ElemType> *
&subRoot, bool &isShorter)
// 操作结果: 对以subRoot为根的二叉树删除时作右平衡处理, 删除subRoot的右子树上的结点，处
//	理后subRoot指向新的树根结点
{
	BinAVLTreeNode<ElemType> *ptrLChild, *ptrLRChild;	
	ptrLChild  = subRoot->leftChild;	// ptrLChild指向subRoot左孩子
	switch (ptrLChild->bf)
	{	// 根据subRoot的左子树的平衡因子作相应的平衡处理
	case LH:						// 右高，作单右旋转
		subRoot->bf = ptrLChild->bf = EH;// 平衡因子都为0
		RightRotate(subRoot);			// 右旋
		isShorter = true;
		break;
	case EH:						// 等高，作单右旋转
		subRoot->bf = LH;
		ptrLChild->bf = RH;			// 平衡因子都为0
		RightRotate(subRoot);			// 右旋
		isShorter = false;
		break;
	case RH:						// 左高,先左旋后右旋
		ptrLRChild = ptrLChild->rightChild;// ptrLRChild指向subRoot的左孩子的右子树的根
		switch (ptrLRChild->bf)
		{	// 修改subRoot及左孩子的平衡因子
		case LH:
			subRoot->bf = RH;
			ptrLChild->bf = EH;
			isShorter = true;
			break;
		case EH:
			subRoot->bf = ptrLChild->bf = EH;
			isShorter = false;
			break;
		case RH:
			subRoot->bf = EH;
			ptrLChild->bf = LH;
			isShorter = true;
			break;
		}
		ptrLRChild->bf = 0;
		LeftRotate(subRoot->leftChild);	// 对subRoot左子树作左旋处理
		RightRotate(subRoot);			// 对subRoot作右旋处理
	}
}

template <class ElemType, class KeyType>
void BinaryAVLTree<ElemType, KeyType>::DeleteBalance(const KeyType &key, 
LinkStack<BinAVLTreeNode<ElemType> *> &s)
// 操作结果: 从删除结点根据查找路径进行回溯,并作平衡处理
{
	bool isShorter = true;
	while (!s.Empty() && isShorter)
	{
		BinAVLTreeNode<ElemType> *ptrCurNode, *ptrParent;
		s.Pop(ptrCurNode);					// 取出待平衡的结点
		if (s.Empty())
		{	// ptrCurNode已为根结点,ptrParent为空
			ptrParent = NULL;
		}
		else
		{	// ptrCurNode不为根结点,取出双亲ptrParent
			s.Top(ptrParent);
		}

		if (key < ptrCurNode->data)
		{	// 删除ptrCurNode的左子树上的结点
			switch (ptrCurNode->bf)
			{	// 检查ptrCurNode的平衡度
			case LH:						// 左高
				ptrCurNode->bf = EH;
				break;
			case EH:						// 等高
				ptrCurNode->bf = RH;
				isShorter = false;
				break;
			case RH:						// 右高
				if (ptrParent == NULL)
				{	// 已回溯到根结点
					DeleteLeftBalance(ptrCurNode, isShorter);
					root = ptrCurNode;		// 转换后ptrCurNode为新根
				}
				else if (ptrParent->leftChild == ptrCurNode)
				{	// ptrParent左子树作平衡处理
					DeleteLeftBalance(ptrParent->leftChild, isShorter);
				}
				else
				{	// ptrParent右子树作平衡处理
					DeleteLeftBalance(ptrParent->rightChild, isShorter);
				}
				break;
			}
		}
		else
		{	// 删除ptrCurNode的右子树上的结点
			switch (ptrCurNode->bf)
			{	// 检查ptrCurNode的平衡度
			case RH: 						// 右高
				ptrCurNode->bf = EH;
				break;
			case EH: 						// 等高
				ptrCurNode->bf = LH;
				isShorter = false;
				break;
			case LH: 						// 左高
				if (ptrParent == NULL)
				{	// 已回溯到根结点
					DeleteLeftBalance(ptrCurNode, isShorter);
					root = ptrCurNode;		// 转换后ptrCurNode为新根
				}
				else if (ptrParent->leftChild == ptrCurNode)
				{	// ptrParent左子树作平衡处理
					DeleteLeftBalance(ptrParent->leftChild, isShorter);
				}
				else
				{	// ptrParent右子树作平衡处理
					DeleteLeftBalance(ptrParent->rightChild, isShorter);
				}
				break;
			}
		}
	}
}

template <class ElemType, class KeyType>
void BinaryAVLTree<ElemType, KeyType>::DeleteHelp(const KeyType &key, 
BinAVLTreeNode<ElemType> *&p, LinkStack< BinAVLTreeNode<ElemType> *> &s)
// 操作结果: 删除p指向的结点
{
	BinAVLTreeNode<ElemType> *tmpPtr, *tmpF;  
	if (p->leftChild == NULL && p->rightChild == NULL)
	{	// p为叶结点
		delete p;
		p = NULL;
		DeleteBalance(key, s);
	}
	else if (p->leftChild == NULL)
	{	// p只有左子树为空
		tmpPtr = p;
		p = p->rightChild;
		delete tmpPtr;
		DeleteBalance(key, s);
	}
	else if (p->rightChild == NULL)
	{	// p只有右子树非空
		tmpPtr = p;
		p = p->leftChild;
		delete tmpPtr;
		DeleteBalance(key, s);
	}
	else
	{	// p左右子非空
		tmpF = p;
		s.Push(tmpF);
		tmpPtr = p->leftChild;
		while (tmpPtr->rightChild != NULL)
		{	// 查找p在中序序列中直接前驱tmpPtr及其双亲tmpF,tmpPtr无右子树为空
			tmpF = tmpPtr;
			s.Push(tmpF);
			tmpPtr = tmpPtr->rightChild;
		}
		p->data = tmpPtr->data;// 将tmpPtr指向结点的元素值赋值给tmpF指向结点的元素值

		// 删除tmpPtr指向的结点
		if (tmpF->rightChild == tmpPtr)
		{	// 删除tmpF的右孩子
			DeleteHelp(key, tmpF->rightChild, s);
		}
		else
		{	// 删除tmpF的左孩子
			DeleteHelp(key, tmpF->leftChild, s);
		}
	}
}

template <class ElemType, class KeyType>
bool BinaryAVLTree<ElemType, KeyType>::Delete(const KeyType &key)
// 操作结果: 删除关键字为key的结点
{
	BinAVLTreeNode<ElemType> *p, *f;
	LinkStack< BinAVLTreeNode<ElemType> *> s;
	p = SearchHelp(key, f, s);
	if ( p == NULL)
	{	// 查找失败, 删除失败
		return false;
	}
	else
	{	// 查找成功, 插入失败
		if (f == NULL)
		{	// 被删除结点为根结点
			DeleteHelp(key, root, s);
		}
		else if (key < f->data)
		{	// key更小,删除f的左孩子
			DeleteHelp(key, f->leftChild, s);
		}
		else
		{	// key更大,插入f的右孩子
			DeleteHelp(key, f->rightChild, s);
		}
		return true;		
	}
}

template <class ElemType, class KeyType>
void BinaryAVLTree<ElemType, KeyType>::DestroyHelp(BinAVLTreeNode<ElemType> *&r)
// 操作结果：销毁以r的二叉平衡树
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
BinAVLTreeNode<ElemType> *BinaryAVLTree<ElemType, KeyType>::CopyTreeHelp(BinAVLTreeNode<ElemType> *copy)
// 操作结果：将以copy为根的二叉平衡树复制成新的二叉平衡树,返回新二叉平衡树的根
{
	if (copy == NULL)
	{	// 复制空二叉平衡树
		return NULL;					// 空二叉平衡树根为空	
	}
	else
	{	// 复制非空二叉平衡树
		BinAVLTreeNode<ElemType> *lChild = CopyTreeHelp(copy->leftChild);	// 复制左子树
		BinAVLTreeNode<ElemType> *rChild = CopyTreeHelp(copy->rightChild);	// 复制右子树
		BinAVLTreeNode<ElemType> *r = new BinAVLTreeNode<ElemType>(copy->data, copy->bf, lChild, rChild);
			// 复制根结点
		return r;
	}
}

template <class ElemType, class KeyType>
BinaryAVLTree<ElemType, KeyType>::BinaryAVLTree(const BinaryAVLTree<ElemType, KeyType> &copy)
// 操作结果：由已知二叉平衡树构造新二叉平衡树——复制构造函数
{
	root = CopyTreeHelp(copy.root);	// 复制二叉平衡树
}

template <class ElemType, class KeyType>
BinaryAVLTree<ElemType, KeyType>::BinaryAVLTree(BinAVLTreeNode<ElemType> *r)
// 操作结果：建立以r为根的二叉平衡树
{	
	root = r;	// 复制二叉平衡树
}

template <class ElemType, class KeyType>
BinaryAVLTree<ElemType, KeyType> &BinaryAVLTree<ElemType, KeyType>::operator=(const BinaryAVLTree<ElemType, KeyType> &copy)
// 操作结果：由已知二叉平衡树copy复制到当前二叉平衡树--赋值语句重载
{
	if (&copy != this)
	{
		DestroyHelp(root);				// 释放原二叉平衡树所占用空间
		root = CopyTreeHelp(copy.root);	// 复制二叉平衡树
	}
	return *this;
}

template <class ElemType, class KeyType>
void DisplayBTWithTreeShapeHelp(const BinAVLTreeNode<ElemType> *r, int level)
//	操作结果：按树状形式显示以r为根的二叉平衡树，level为层次数，可设根结点的层次数为1
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
void DisplayBTWithTreeShape(const BinaryAVLTree<ElemType, KeyType> &bt)
//	操作结果：树状形式显示二叉平衡树 
{
	DisplayBTWithTreeShapeHelp<ElemType, KeyType>(bt.GetRoot(), 1);	
		// 树状显示以bt.GetRoot()为根的二叉平衡树
	cout << endl;
}

#endif
