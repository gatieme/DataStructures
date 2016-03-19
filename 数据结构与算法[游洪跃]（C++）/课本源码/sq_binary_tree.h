#ifndef __SQ_BINNARY_TREE_H__
#define __SQ_BINNARY_TREE_H__

#include "lk_queue.h"										// 链队列
#include "sq_bin_tree_node.h"								// 顺序存储二叉树结点类

// 顺序存储二叉树类
template <class ElemType>
class SqBinaryTree
{
protected:
//  二叉树的数据成员:
	int maxSize;											// 二叉树的最大结点个数
	SqBinTreeNode<ElemType> *elems;							// 结点存储空间
	int root;												// 二叉树的根

//	辅助函数:
	int NodeCountHelp(int r) const;							// 返回二叉树的结点个数
	void SetNodeEmpty(int cur);								// 将结点cur置空
	void DestroyHelp(int r);								// 销毁以r为根二叉树
	void PreOrderHelp(int r, void (*Visit)(const ElemType &)) const;	// 先序遍历
	void InOrderHelp(int r, void (*Visit)(const ElemType &)) const;		// 中序遍历
	void PostOrderHelp(int r, void (*Visit)(const ElemType &)) const;	// 后序遍历
    int HeightHelp(int r) const;							// 返回二叉树的高

public:
//  二叉树方法声明及重载编译系统默认方法声明:
	SqBinaryTree();											// 无参数的构造函数
	virtual ~SqBinaryTree();								// 析构函数
	int GetRoot() const;									// 返回二叉树的根
	bool NodeEmpty(int cur) const;							// 判断结点cur是否为空
	StatusCode GetItem(int cur, ElemType &e);				// 返回结点cur的元素值
	StatusCode SetElem(int cur, const ElemType &e);			// 将结点cur的值置为e
	bool Empty() const;										// 判断二叉树是否为空
	void InOrder(void (*Visit)(const ElemType &)) const;	// 二叉树的中序遍历	
	void PreOrder(void (*Visit)(const ElemType &)) const;	// 二叉树的先序遍历
	void PostOrder(void (*Visit)(const ElemType &)) const;	// 二叉树的后序遍历
	void LevelOrder(void (*Visit)(const ElemType &)) const;	// 二叉树的层次遍历
	int NodeCount() const;									// 求二叉树的结点个数
	int LeftChild(const int cur) const;						// 返回二叉树结点cur的左孩子
	int RightChild(const int cur) const;					// 返回二叉树结点cur的右孩子
	int Parent(const int cur) const;						// 返回二叉树结点cur的双亲
	void InsertLeftChild(int cur, const ElemType &e);		// 插入左孩子
	void InsertRightChild(int cur, const ElemType &e);		// 插入右孩子
	void DeleteLeftChild(int cur);							// 删除左子树
	void DeleteRightChild(int cur);							// 删除右子村
	int	Height() const;										// 求二叉树的高
	SqBinaryTree(const ElemType &e, int size = DEFAULT_SIZE);	// 建立以e为根的二叉树
	SqBinaryTree(const SqBinaryTree<ElemType> &copy);		// 复制构造函数
	SqBinaryTree(SqBinTreeNode<ElemType> es[], int r, int size = DEFAULT_SIZE);	
		// 由es[]、r与size构造二叉树
	SqBinaryTree<ElemType> &operator=(const SqBinaryTree<ElemType>& copy);		
		// 赋值运算符重载
};


template <class ElemType>
void DisplayBTWithTreeShapeHelp(int r, int level);
	//	按树状形式显示以r为根的二叉树，level为层次数，可设根结点的层次数为1
template <class ElemType>
void DisplayBTWithTreeShape(SqBinaryTree<ElemType> &bt);
	//	树状形式显示二叉树 
template <class ElemType>
void CreateBinaryTreeHelp(SqBinTreeNode<ElemType> es, int r, ElemType pre[], ElemType in[], 
	int preLeft, int preRight, int inLeft, int inRight);	
	// 已知二叉树的先序序列pre[preLeft..preRight]和中序序列in[inLeft..inRight]构造以r为根的二叉树
template <class ElemType>
SqBinaryTree<ElemType> &CreateBinaryTree(ElemType pre[], ElemType in[], int n);
	// 已知先序和中序序列构造二叉树

// 二叉树类的实现部分
template <class ElemType>
bool SqBinaryTree<ElemType>::NodeEmpty(int cur) const
// 操作结果：如果结点cur为空,则返回true,否则返回false
{
	if(cur <1 || cur > maxSize || elems[cur].tag == EMPTY_NODE) return true;	// 此时结点为空
	else return false;
}

template <class ElemType>
StatusCode SqBinaryTree<ElemType>::GetItem(int cur, ElemType &e)
// 操作结果：用e返回结点cur的元素值,则操作成功,函数返回SUCCESS,否则返回FAIL
{
	if (NodeEmpty(cur)) return FAIL;		// 操作失败
	else
	{
		e = elems[cur].data;				// 用e返回结点cur的元素值
		return SUCCESS;						// 操作成功
	}
}

template <class ElemType>
StatusCode SqBinaryTree<ElemType>::SetElem(int cur, const ElemType &e)
// 操作结果：如果不存在结点cur,则返回FAIL,否则返回SUCCESS,并将结点cur的值设置为e
{
	if (NodeEmpty(cur)) return FAIL;		// 操作失败
	else
	{	// 存在结点cur
		elems[cur].data = e;				// 将结点cur的值设置为e
		return SUCCESS;						// 返回SUCCESS
	}
}

template <class ElemType>
void SqBinaryTree<ElemType>::SetNodeEmpty(int cur)
// 操作结果：将结点cur置空
{
	if (cur > 0 && cur <= maxSize) elems[cur].tag = EMPTY_NODE;	// 将cur置空
}

template <class ElemType>
SqBinaryTree<ElemType>::SqBinaryTree()
// 操作结果：构造一棵空二叉树
{
	maxSize = DEFAULT_SIZE;			// 最大结点个数
	elems = new SqBinTreeNode<ElemType>[maxSize + 1];	// 分配存储空间, 未使用elems[0]
	for (int i = 1; i <=maxSize; i++)
	{	// 将所有结点标识为空
		elems[i].tag = EMPTY_NODE;
	}
	root = 1;						// elems[1]存储根
}

template <class ElemType>
SqBinaryTree<ElemType>::~SqBinaryTree()
// 操作结果：销毁二叉树
{
	delete []elems;					// 释放存储空间
}

template <class ElemType>
int SqBinaryTree<ElemType>::GetRoot() const
// 操作结果：返回二叉树的根
{
	return root;						// root为根
}

template <class ElemType>
bool SqBinaryTree<ElemType>::Empty() const
// 操作结果：判断二叉树是否为空
{
	return NodeEmpty(root);
}

template <class ElemType>
void SqBinaryTree<ElemType>::PreOrderHelp(int r, void (*Visit)(const ElemType &)) const
// 操作结果：先序遍历以r为根的二叉树
{
	if (!NodeEmpty(r)) 
	{	// 根非空
		(*Visit)(elems[r].data);			// 访问根结点
		PreOrderHelp(LeftChild(r), Visit);			// 遍历左子树
		PreOrderHelp(RightChild(r), Visit);		// 遍历右子树
	}
}

template <class ElemType>
void SqBinaryTree<ElemType>::PreOrder(void (*Visit)(const ElemType &)) const
// 操作结果：先序遍历二叉树
{
	PreOrderHelp(root, Visit);	
}	

template <class ElemType>
void SqBinaryTree<ElemType>::InOrderHelp(int r, void (*Visit)(const ElemType &)) const
// 操作结果：中序遍历以r为根的二叉树
{
	if (!NodeEmpty(r)) 
	{	// 根非空
		InOrderHelp(LeftChild(r), Visit);			// 遍历左子树
		(*Visit)(elems[r].data);					// 访问根结点
		InOrderHelp(RightChild(r), Visit);			// 遍历右子树
	}
}

template <class ElemType>
void SqBinaryTree<ElemType>::InOrder(void (*Visit)(const ElemType &)) const
// 操作结果：中序遍历二叉树
{
	InOrderHelp(root, Visit);	
}	

template <class ElemType>
void SqBinaryTree<ElemType>::PostOrderHelp(int r, void (*Visit)(const ElemType &)) const
// 操作结果：后序遍历以r为根的二叉树
{
	if (!NodeEmpty(r)) 
	{	// 根非空
		PostOrderHelp(LeftChild(r), Visit);		// 遍历左子树
		PostOrderHelp(RightChild(r), Visit);	// 遍历右子树
		(*Visit)(elems[r].data);					// 访问根结点
	}
}

template <class ElemType>
void SqBinaryTree<ElemType>::PostOrder(void (*Visit)(const ElemType &)) const
// 操作结果：后序遍历二叉树
{
	PostOrderHelp(root, Visit);	
}	

template <class ElemType>
void SqBinaryTree<ElemType>::LevelOrder(void (*Visit)(const ElemType &)) const
// 操作结果：层次遍历二叉树
{
	LinkQueue<int > q;						// 队列
	int t = root;							// 从根结点开始进行层次遍历
	
	if (!NodeEmpty(t)) q.InQueue(t);		// 如果根非空,则入队
	while (!q.Empty())
	{	// q非空,说明还有结点未访问
		q.OutQueue(t);     
		(*Visit)(elems[t].data);
		if (!NodeEmpty(LeftChild(t)))				// 左孩子非空
			q.InQueue(LeftChild(t));				// 左孩子入队
		if (!NodeEmpty(RightChild(t)))			// 右孩子非空
			q.InQueue(RightChild(t));			// 右孩子入队
	}
}

template <class ElemType>
int SqBinaryTree<ElemType>::HeightHelp(int r) const
// 操作结果：返回以r为根的二叉树的高
{
	if(NodeEmpty(r))
	{	// 空二叉树高为0
		return 0;
	}
	else
	{	// 非空二叉树高为左右子树的高的最大值再加1
		int lHeight, rHeight;
		lHeight = HeightHelp(LeftChild(r));		// 左子树的高
		rHeight = HeightHelp(RightChild(r));	// 右子树的高
		return 1 + (lHeight > rHeight ? lHeight : rHeight);
			// 非空二叉树高为左右子树的高的最大值再加1
	}
}

template <class ElemType>
int SqBinaryTree<ElemType>::Height() const
// 操作结果：返回二叉树的高
{
	return HeightHelp(root);
}

template <class ElemType>
int SqBinaryTree<ElemType>::NodeCountHelp(int r) const
// 操作结果：返回以r为根的二叉树的结点个数
{
	if (NodeEmpty(r)) return 0;	// 空二叉数结点个数为0
	else return 1 + NodeCountHelp(LeftChild(r)) + NodeCountHelp(RightChild(r));
		// 非空二叉树结点个为左右子树的结点个数之和再加1
}

template <class ElemType>
int SqBinaryTree<ElemType>::NodeCount() const
// 操作结果：返回二叉树的结点个数
{
	return NodeCountHelp(root);
}

template <class ElemType>
int SqBinaryTree<ElemType>::LeftChild(const int cur) const
// 操作结果：返回二叉树结点cur的左孩子
{
	return 2 * cur;				// 2 * cur为左孩子 
}

template <class ElemType>
int SqBinaryTree<ElemType>::RightChild(const int cur) const
// 操作结果：返回二叉树结点cur的右孩子
{
	return 2 * cur + 1;			// 2 * cur + 1为右孩子 
}

template <class ElemType>
int SqBinaryTree<ElemType>::Parent(const int cur) const
// 操作结果：返回二叉树结点cur的双亲
{
	return cur / 2;				// cur / 2为双亲
}

template <class ElemType>
void SqBinaryTree<ElemType>::InsertLeftChild(int cur, const ElemType &e)
// 初始条件：cur和cur左孩子非空
// 操作结果：插入e为cur的左孩子，如果cur的左孩子非空，操作作失败
{
	if (NodeEmpty(cur))
	{	// cur为空，返回
		return;
	}
	else 
	{	// 插入左孩子    
		if (NodeEmpty(LeftChild(cur)) && LeftChild(cur) <= maxSize && LeftChild(cur) > 0)
		{	// cur左孩子为空,且合法
			elems[LeftChild(cur)].data = e;				// 左孩子元素值
			elems[LeftChild(cur)].tag = USED_NODE;		// 左孩子标志
		}
		return;
	}
}

template <class ElemType>
void SqBinaryTree<ElemType>::InsertRightChild(int cur, const ElemType &e)
// 初始条件：cur和cur右孩子非空
// 操作结果：插入e为cur的右孩子，如果cur的右孩子非空，操作作失败
{
	if (NodeEmpty(cur))
	{	//  cur为空，返回
		return;
	}
	else
	{	// 插入右孩子
		if (NodeEmpty(RightChild(cur)) && RightChild(cur) <= maxSize && RightChild(cur) > 0)
		{	// cur右孩子为空,且合法
			elems[RightChild(cur)].data = e;				// 右孩子元素值
			elems[RightChild(cur)].tag = USED_NODE;		// 右孩子标志
		}
		return;
	}
}

template <class ElemType>
void SqBinaryTree<ElemType>::DeleteLeftChild(int cur)
// 初始条件：cur非空
// 操作结果：删除cur左子树
{
	if (NodeEmpty(cur))
	{	// cur为空
		return;
	}
	else
	{	// cur非空
		DestroyHelp(LeftChild(cur));	// 删除cur左子树
	}
}

template <class ElemType>
void SqBinaryTree<ElemType>::DeleteRightChild(int cur)
// 初始条件：cur非空
// 操作结果：删除cur右子树
{
	if (NodeEmpty(cur))
	{	// cur为空
		return;
	}
	else
	{	// cur非空
		DestroyHelp(RightChild(cur));	// 删除cur右子树
	}
}

template <class ElemType>
void SqBinaryTree<ElemType>::DestroyHelp(int r)
// 操作结果：销毁以r的二叉树
{
	if(!NodeEmpty(r))
	{	// r非空,实施销毁
		DestroyHelp(LeftChild(r));		// 销毁左子树
		DestroyHelp(RightChild(r));		// 销毁右子树
		SetNodeEmpty(r);				// 将r置空
	}
}

template <class ElemType>
SqBinaryTree<ElemType>::SqBinaryTree(const ElemType &e, int size)
// 操作结果：建立以e为根的最大结点个数为size的二叉树
{
	maxSize = size;					// 最大结点个数
	elems = new SqBinTreeNode<ElemType>[maxSize + 1];	// 分配存储空间, 未使用elems[0]
	for (int i = 2; i <=maxSize; i++)
	{	// 将所有结点标识为空
		elems[i].tag = EMPTY_NODE;
	}
	root = 1;						// elems[1]存储根
	elems[root].tag = USED_NODE;	// 根标志
	elems[root].data = e;			// 根的数据元素值
}


template <class ElemType>
SqBinaryTree<ElemType>::SqBinaryTree(const SqBinaryTree<ElemType> &copy)
// 操作结果：由已知二叉树构造新二叉树——复制构造函数
{
	maxSize = copy.maxSize;							// 最大结点个数
	elems = new SqBinTreeNode<ElemType>[maxSize + 1];	// 分配存储空间, 未使用elems[0]
	for (int i = 1; i <=maxSize; i++)
	{	// 复制结点
		elems[i] = copy.elems[i];
	}
	root = copy.GetRoot();							// 复制二叉树根
}

template <class ElemType>
SqBinaryTree<ElemType>::SqBinaryTree(SqBinTreeNode<ElemType> es[], int r, int size)
// 操作结果：由es[]与r构造最大结点个数为size的二叉树, 
{
	maxSize = size;									// 最大结点个数
	elems = new SqBinTreeNode<ElemType>[maxSize + 1];	// 分配存储空间, 未使用elems[0]
	for (int i = 1; i <=maxSize; i++)
	{	// 复制结点
		elems[i] = es[i];
	}
	root = r;			// 复制二叉树根
}

template <class ElemType>
SqBinaryTree<ElemType> &SqBinaryTree<ElemType>::operator=(const SqBinaryTree<ElemType> &copy)
// 操作结果：由已知二叉树copy复制到当前二叉树--赋值运算符重载
{
	if (&copy != this)
	{
		delete []elems;					// 释放存储空间
		maxSize = copy.maxSize;							// 最大结点个数
		elems = new SqBinTreeNode<ElemType>[maxSize + 1];	// 分配存储空间, 未使用elems[0]

		for (int i = 1; i <=maxSize; i++)
		{	// 复制结点
			elems[i] = copy.elems[i];
		}
		root = copy.GetRoot();			// 复制二叉树根
	}
	return *this;
}

template <class ElemType>
void DisplayBTWithTreeShapeHelp(SqBinaryTree<ElemType> &bt, int r, int level)
//	操作结果：按树状形式显示以r为根的二叉树，level为层次数，可设根结点的层次数为1
{
	if(!bt.NodeEmpty(r))
	{	//空树不显式，只显式非空树
		DisplayBTWithTreeShapeHelp<ElemType>(bt, bt.RightChild(r), level + 1);//显示右子树
		cout << endl;					//显示新行	
		for(int i = 0; i < level - 1; i++)
			cout << " ";				//确保在第level列显示结点
		ElemType e;
		bt.GetItem(r, e);
		cout << e;						//显示结点
		DisplayBTWithTreeShapeHelp<ElemType>(bt, bt.LeftChild(r), level + 1);//显示左子树
	}
}

template <class ElemType>
void DisplayBTWithTreeShape(SqBinaryTree<ElemType> &bt)
//	操作结果：树状形式显示二叉树 
{
	DisplayBTWithTreeShapeHelp<ElemType>(bt, bt.GetRoot(), 1);	
		// 树状显示以bt.GetRoot()为根的二叉树
	cout << endl;
}

template <class ElemType>
void CreateBinaryTreeHelp(SqBinTreeNode<ElemType> es[], int r, ElemType pre[], ElemType in[], 
	int preLeft, int preRight, int inLeft, int inRight)	
// 操作结果：已知二叉树的先序序列pre[preLeft..preRight]和中序序列in[inLeft..inRight]构造
//	以r为根的二叉树
{
	if (inLeft > inRight)
	{	// 二叉树无结点,空二叉树
		r = 0;							// 空二叉树根为空
	}
	else
	{	// 二叉树有结点,非空二叉树
		es[r].data = pre[preLeft];es[r].tag = USED_NODE; // 生成根结点
		int mid = inLeft;
		while (in[mid] != pre[preLeft]) 
		{	// 查找pre[preLeft]在in[]中的位置,也就是中序序列中根的位置
			mid++;
		}
		CreateBinaryTreeHelp(es, 2 * r, pre, in, preLeft+1, preLeft + mid - inLeft, inLeft, mid - 1);
			// 生成左子树
		CreateBinaryTreeHelp(es, 2 * r + 1, pre, in, preLeft + mid - inLeft + 1, preRight, mid + 1, 
			inRight);					// 生成右子树
	}
} 

template <class ElemType>
SqBinaryTree<ElemType> &CreateBinaryTree(ElemType pre[], ElemType in[], int n)
// 操作结果：已知先序和中序序列构造二叉树
{
	SqBinTreeNode<ElemType> *es = new SqBinTreeNode<ElemType>[n + 1];	// 存储二叉树信息
	int r = 1;											// 二叉树的根
	CreateBinaryTreeHelp<ElemType>(es, r, pre, in, 0, n - 1, 0, n - 1);
		// 由先序和中序序列构造以r为根的二叉树 
	SqBinaryTree<ElemType> *bt = new SqBinaryTree<ElemType>(es, r, n);	// 生成二叉树
	delete []es;										// 释放存储空间
	return *bt;
}

#endif
