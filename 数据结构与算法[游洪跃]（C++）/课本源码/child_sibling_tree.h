#ifndef __CHILD_SIBLING_TREE_H__
#define __CHILD_SIBLING_TREE_H__

#include "lk_queue.h"						// 链队列
#include "child_sibling_tree_node.h"		// 孩子兄弟表示树结点类

// 孩子兄弟表示树类
template <class ElemType>
class ChildSiblingTree
{
protected:
//  树的数据成员:
	ChildSiblingTreeNode<ElemType> *root;			// 根

//	辅助函数:
	void DestroyHelp(ChildSiblingTreeNode<ElemType> * &r);		// 销毁以r为根的树
	void PreRootOrderHelp(ChildSiblingTreeNode<ElemType> *r, void (*Visit)(const ElemType &)) const;	
		// 先根序遍历
	void PostRootOrderHelp(ChildSiblingTreeNode<ElemType> *r, void (*Visit)(const ElemType &)) const;
		// 后根序遍历
	int NodeCountHelp(ChildSiblingTreeNode<ElemType> *r) const;	// 返回以r为根的树的结点个数
	int HeightHelp(ChildSiblingTreeNode<ElemType> *r) const;	// 返回以r为根的树的高
	int DegreeHelp(ChildSiblingTreeNode<ElemType> *r) const;	// 返回以r为根的树的度
	void DeleteHelp(ChildSiblingTreeNode<ElemType> *r);		// 删除以r为根的树
	ChildSiblingTreeNode<ElemType> *ParentHelp(ChildSiblingTreeNode<ElemType> *r, 
		const ChildSiblingTreeNode<ElemType> *cur) const;	// 返回cur的双亲
	ChildSiblingTreeNode<ElemType> *CopyTreeHelp(ChildSiblingTreeNode<ElemType> *copy);	
		// 复制树
	ChildSiblingTreeNode<ElemType> *CreateTreeGhelp(ElemType items[], int parents[], int r, int n);
		// 建立数据元素为items[],对应结点双亲为parents[],根结点位置为r,结点个数为n的
		// 树，并返回树的根

public:
//  树方法声明及重载编译系统默认方法声明:
	ChildSiblingTree();									// 无参数的构造函数
	virtual ~ChildSiblingTree();						// 析构函数
	ChildSiblingTreeNode<ElemType> * GetRoot() const;	// 返回树的根
	bool Empty() const;									// 判断树是否为空
	StatusCode GetElem(ChildSiblingTreeNode<ElemType> *cur, ElemType &e) const;
		// 用e返回结点元素值
	StatusCode SetElem(ChildSiblingTreeNode<ElemType> *cur, const ElemType &e);
		// 将结cur的值置为e
	void PreRootOrder(void (*Visit)(const ElemType &)) const;		// 树的先根序遍历
	void PostRootOrder(void (*Visit)(const ElemType &)) const;		// 树的后根序遍历
	void LevelOrder(void (*Visit)(const ElemType &)) const;			// 树的层次遍历
	int NodeCount() const;								// 返回树的结点个数
	int NodeDegree(ChildSiblingTreeNode<ElemType> *cur) const;	// 返回结点cur的度
	int Degree() const;									// 返回树的度
	ChildSiblingTreeNode<ElemType> *FirstChild(ChildSiblingTreeNode<ElemType> *cur) const;	
		// 返回树结点cur的第一个孩子
	ChildSiblingTreeNode<ElemType> *RightSibling(ChildSiblingTreeNode<ElemType> *cur) const;				
		// 返回树结点cur的右兄弟
	ChildSiblingTreeNode<ElemType> *Parent(ChildSiblingTreeNode<ElemType> *cur) const;
		// 返回树结点cur的双亲
	StatusCode InsertChild(ChildSiblingTreeNode<ElemType> *cur, int i, const ElemType &e);	
		// 将数据元素插入为cur的第i个孩子
	StatusCode DeleteChild(ChildSiblingTreeNode<ElemType> *cur, int i);// 删除cur的第i个棵子树
	int	Height() const;									// 返回树的高
	ChildSiblingTree(const ElemType &e);				// 建立以数据元素e为根的树
	ChildSiblingTree(const ChildSiblingTree<ElemType> &copy);	// 复制构造函数
	ChildSiblingTree(ElemType items[], int parents[], int r, int n);
		// 建立数据元素为items[],对应结点双亲为parents[],根结点位置为r,结点个数为n的树
	ChildSiblingTree(ChildSiblingTreeNode<ElemType> *r);// 建立以r为根的树
	ChildSiblingTree<ElemType> &operator=(const ChildSiblingTree<ElemType>& copy);	
		// 赋值语句重载
};

template <class ElemType>
void DisplayTWithConcaveShapeHelp(const ChildSiblingTree<ElemType> &t, ChildSiblingTreeNode<ElemType> *r, int level);
	// 按凹入表示法显示树，level为层次数，可设根结点的层次数为1
template <class ElemType>
void DisplayTWithConcaveShape(const ChildSiblingTree<ElemType> &t);
	// 按凹入表示法显示树

// 孩子兄弟表示树类的实现部分

template <class ElemType>
ChildSiblingTree<ElemType>::ChildSiblingTree()
// 操作结果：构造一个空树
{
	root = NULL;					// 表示树为空
}

template <class ElemType>
void ChildSiblingTree<ElemType>::DestroyHelp(ChildSiblingTreeNode<ElemType> * &r)
// 操作结果：销毁以r为根的树
{
	if (r != NULL)
	{	// r非空,实施销毁
		for (ChildSiblingTreeNode<ElemType> *child = FirstChild(r); child != NULL;
			child = RightSibling(child))
		{	// 销毁子树
			DestroyHelp(child);		// 销毁子树
		}
		delete r;					// 销毁根结点
		r = NULL;
	}
}

template <class ElemType>
ChildSiblingTree<ElemType>::~ChildSiblingTree()
// 操作结果：销毁树--析造函数
{
	DestroyHelp(root);				// 销毁树
}

template <class ElemType>
ChildSiblingTreeNode<ElemType> *ChildSiblingTree<ElemType>::GetRoot() const
// 操作结果：返回树的根
{
	return root;					// 树根
}

template <class ElemType>
bool ChildSiblingTree<ElemType>::Empty() const
// 操作结果：判断树是否为空
{
	return root == NULL;			// root为空表示树为空
}

template <class ElemType>
StatusCode ChildSiblingTree<ElemType>::GetElem(ChildSiblingTreeNode<ElemType> *cur, ElemType &e) const
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
StatusCode ChildSiblingTree<ElemType>::SetElem(ChildSiblingTreeNode<ElemType> *cur, const ElemType &e)
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
void ChildSiblingTree<ElemType>::PreRootOrderHelp(ChildSiblingTreeNode<ElemType> *r, 
	void (*Visit)(const ElemType &)) const
// 操作结果：按先根序依次对以r为根的树的每个元素调用函数(*visit)
{
	if (r != NULL)	
	{	// r非空
		(*Visit)(r->data);			// 访问根结点
		for (ChildSiblingTreeNode<ElemType> *child = FirstChild(r); child != NULL;
			child = RightSibling(child))
		{	// 依次先根序遍历每棵子树
			PreRootOrderHelp(child, Visit);
		}
	}
}

template <class ElemType>
void ChildSiblingTree<ElemType>::PreRootOrder(void (*Visit)(const ElemType &)) const
// 操作结果：按先根序依次对树的每个元素调用函数(*visit)
{
	PreRootOrderHelp(GetRoot(), Visit);				// 调用辅助函数实现树的先根遍历
}

template <class ElemType>
void ChildSiblingTree<ElemType>::PostRootOrderHelp(ChildSiblingTreeNode<ElemType> *r, void (*Visit)(const ElemType &)) const
// 操作结果：按后根序依次对以r为根的树的每个元素调用函数(*visit)
{
	if (r != NULL)	
	{	// r非空
		for (ChildSiblingTreeNode<ElemType> *child = FirstChild(r); child != NULL;
			child = RightSibling(child))
		{	// 依次后根序遍历每棵子树
			PostRootOrderHelp(child, Visit);
		}
		(*Visit)(r->data);					// 访问根结点
	}
}

template <class ElemType>
void ChildSiblingTree<ElemType>::PostRootOrder(void (*Visit)(const ElemType &)) const
// 操作结果：按后根序依次对树的每个元素调用函数(*visit)
{
	PostRootOrderHelp(GetRoot(), Visit);			// 调用辅助函数实现后根序遍历
}

template <class ElemType>
void ChildSiblingTree<ElemType>::LevelOrder(void (*Visit)(const ElemType &)) const
// 操作结果：层次遍历树
{
	LinkQueue<ChildSiblingTreeNode<ElemType> *> q;	// 队列
	ChildSiblingTreeNode<ElemType> *cur = root;		// 从根结点开始进行层次遍历
	
	if (cur != NULL) q.InQueue(cur);			// 如果根非空,则入队
	while (!q.Empty())
	{	// q非空,说明还有结点未访问
		q.OutQueue(cur);						// 出队
		(*Visit)(cur->data);					// 访问当前结点
		for (ChildSiblingTreeNode<ElemType> *child = FirstChild(cur); child != NULL;
			child = RightSibling(child))
		{	// 依次将cur的孩子入列
			q.InQueue(child);					// 孩子入队
		}
	}
}

template <class ElemType>
int ChildSiblingTree<ElemType>::NodeCountHelp(ChildSiblingTreeNode<ElemType> *r) const
// 操作结果：返回以r为根的树的结点个数
{
	if (r == NULL) return 0;			// 空树结点个数为0
	else
	{	// 求子树的结点个数之和
		int subTreeNodeCountSum = 0;	// 子树结点个数之和
		for (ChildSiblingTreeNode<ElemType> *child = FirstChild(r); child != NULL;
			child = RightSibling(child))
		{	// 依次求r的子树结点个数并进行累加
			subTreeNodeCountSum += NodeCountHelp(child);// 累加子树结点个数
		}
		return 1 + subTreeNodeCountSum;	// 非空树结点个为子树的结点个数之和再加1
	}
}

template <class ElemType>
int ChildSiblingTree<ElemType>::NodeCount() const
// 操作结果：返回树的结点个数
{
	return NodeCountHelp(root);			// 用辅助函数实现求树结点个数
}


template <class ElemType>
int ChildSiblingTree<ElemType>::HeightHelp(ChildSiblingTreeNode<ElemType> *r) const
// 操作结果：返回以r为根的树的高
{
	if (r == NULL)
	{	// 空树,高为0
		return 0;
	}
	else
	{
		int maxSubTreeHeight = 0;
		for (ChildSiblingTreeNode<ElemType> *child = FirstChild(r); child != NULL;
			child = RightSibling(child))
		{	// 求各子树高的最大值
			int h = HeightHelp(child);			// 临时变量存储高
			maxSubTreeHeight = (maxSubTreeHeight < h) ? h : maxSubTreeHeight;
				// 求条子树高的最大值
		}
		return maxSubTreeHeight + 1;			// 树高为各子树的最大值再加1
	}
}

template <class ElemType>
int ChildSiblingTree<ElemType>::Height() const
// 操作结果：返回树的高
{
	return HeightHelp(root);					// 调用辅助函数实现返回树的高
}

template <class ElemType>
int ChildSiblingTree<ElemType>::NodeDegree(ChildSiblingTreeNode<ElemType> *cur) const
// 操作结果：返回结点cur的度
{
	int d = 0;					// 临时变量,用于对孩子个数进行计数
	for (ChildSiblingTreeNode<ElemType> *child = FirstChild(cur); child != NULL;
		child = RightSibling(child))
	{	// 找查cur的孩子
		d++;					// 对孩子个数进行计数
	}
	return d;
}

template <class ElemType>
int ChildSiblingTree<ElemType>::DegreeHelp(ChildSiblingTreeNode<ElemType> *r) const
// 操作结果：返回以r为根的树的度
{

	int d = 0;					// 临时变量,用于结点的孩子个数
	int maxSubTreeDegree = 0;	// 子树度的最大值
	for (ChildSiblingTreeNode<ElemType> *child = FirstChild(r); child != NULL;
		child = RightSibling(child))
	{	// 找查r的孩子
		d++;					// 对孩子个数进行计数
		int subTreeDegree = DegreeHelp(child);	// 子树的度
		maxSubTreeDegree = (maxSubTreeDegree < subTreeDegree) ? subTreeDegree : maxSubTreeDegree;
			// 求子树度最大值
	}
	return (d < maxSubTreeDegree) ? maxSubTreeDegree : d;
}

template <class ElemType>
int ChildSiblingTree<ElemType>::Degree() const
// 操作结果：返回树的度
{
	return DegreeHelp(root);
}

template <class ElemType>
ChildSiblingTreeNode<ElemType> *ChildSiblingTree<ElemType>::FirstChild(ChildSiblingTreeNode<ElemType> *cur) const
// 操作结果：如cur无孩子,则返回NULL,否则返回树结点cur的第一个孩子,
{
	if (cur == NULL)
	{	// cur为空
		return NULL;				// 空结点无孩子		
	}
	else
	{	// cur非空
		return cur->firstChild;			// firstChild为第一个孩子
	}
}

template <class ElemType>
ChildSiblingTreeNode<ElemType> *ChildSiblingTree<ElemType>::RightSibling(ChildSiblingTreeNode<ElemType> *cur) const
// 操作结果：如果结点cur无右兄弟,则返回NULL,否则返回cur的右兄弟
{
	if (cur == NULL)
	{	// cur为空
		return NULL;				// 空结点右兄弟
	}
	else
	{	// cur非空
		return cur->rightSibling;			// rightSibling为右兄弟
	}
}

template <class ElemType>
ChildSiblingTreeNode<ElemType> *ChildSiblingTree<ElemType>::ParentHelp(ChildSiblingTreeNode<ElemType> *r, 
	const ChildSiblingTreeNode<ElemType> *cur) const
// 操作结果：返回以r为根的树, 结点cur的双亲
{
	if (r == NULL) return NULL;					// 空二叉树
	
	ChildSiblingTreeNode<ElemType> *child;		// 孩子 
	for (child = FirstChild(r); child != NULL;
		child = RightSibling(child))
	{	// 找查r的孩子
		if (child == cur) return r;				// cur双亲为r
	}
	
	for (child = FirstChild(r); child != NULL; child = RightSibling(child))
	{	// 在子树上求双亲
		ChildSiblingTreeNode<ElemType> *tmp;
		tmp = ParentHelp(child, cur);			// 在子树上求cur的双亲	
		if (tmp != NULL) return tmp;			// 双亲在子树上
	}
	
	return NULL;								// 未找到双亲
}



template <class ElemType>
ChildSiblingTreeNode<ElemType> *ChildSiblingTree<ElemType>::Parent(ChildSiblingTreeNode<ElemType> *cur) const
// 操作结果：返回结点cur的双亲
{
	return ParentHelp(root, cur);				// 用辅助函数求树中结点的双亲
}

template <class ElemType>
StatusCode ChildSiblingTree<ElemType>::InsertChild(ChildSiblingTreeNode<ElemType> *cur, int i, const ElemType &e)
// 操作结果：将数据元素插入为cur的第i个孩子,如果插入成功,则返回SUCCESS,否则返回FAIL
{
	if (cur == NULL) return FAIL;
	if (i < 0 || i > NodeDegree(cur) + 1) return FAIL;

	ChildSiblingTreeNode<ElemType> *newNodePtr = new ChildSiblingTreeNode<ElemType>(e);	// 新结点
	if (i == 1)
	{	// 插入的是首孩子
		ChildSiblingTreeNode<ElemType> *tmp = cur->firstChild;	// 暂存cur的首孩子
		cur->firstChild = newNodePtr;				// newNodePtr插入为cur的首孩子
		newNodePtr->rightSibling = tmp;				// 原cur的首孩子变为newNodePtr的右兄弟
	}
	else
	
	{
		int n = 1;
		ChildSiblingTreeNode<ElemType> *child;		// 孩子 
		for (child = FirstChild(cur); n < i - 1 && child != NULL;
			child = RightSibling(child), n++);
			// 查找第i-1个孩子

		newNodePtr->rightSibling = child->rightSibling; child->rightSibling = newNodePtr;
			// 将tmp插入作为第i个孩子
	}
	return SUCCESS;
}

template <class ElemType>
void ChildSiblingTree<ElemType>::DeleteHelp(ChildSiblingTreeNode<ElemType> *r)
// 操作结果：删除以r为根的树
{
	if (r != NULL)
	{	// r非空
		for (ChildSiblingTreeNode<ElemType> *child = FirstChild(r); child != NULL;
			child = RightSibling(child))
		{	// 找查r的子树
			DeleteHelp(child);						// 删除以child为根的子树
		}
		delete r;									// 释放r
		r = NULL;
	}
}

template <class ElemType>
StatusCode ChildSiblingTree<ElemType>::DeleteChild(ChildSiblingTreeNode<ElemType> *cur, int i)
// 操作结果：删除cur的第i个棵子树,如果删除成功,则返回SUCCESS,否则返回FAIL
{
	if (i < 0 && i > NodeDegree(cur)) return FAIL;	// 操作失败
	if (i == 1)
	{
		ChildSiblingTreeNode<ElemType> *tmp = cur->firstChild;	// 暂存第1棵子树的根
		cur->firstChild = tmp->rightSibling;		// 在逻辑上删除第1棵子树
		DeleteHelp(tmp);							// 物理上删除第1棵子树
	}
	else
	{
		int n = 1;
		ChildSiblingTreeNode<ElemType> *child;		// 孩子 
		for (child = FirstChild(cur); n < i - 1 && child != NULL; 
			child = RightSibling(child), n++);
			// 查找第i - 1个孩子

		ChildSiblingTreeNode<ElemType> *tmp = child->rightSibling;	// 暂存第i棵子树的根
		child->rightSibling = tmp->rightSibling;		// 辑逻上删除第i个棵子树
		DeleteHelp(tmp);								// 物理上删除第i棵子树
//		return SUCCESS;									// 操作成功
	}
	return SUCCESS;									// 操作成功
}

template <class ElemType>
ChildSiblingTree<ElemType>::ChildSiblingTree(const ElemType &e)
// 操作结果：建立以数据元素e为根的树
{
	root = new ChildSiblingTreeNode<ElemType>(e);	// 生成根结点
}

template <class ElemType>
ChildSiblingTreeNode<ElemType> *ChildSiblingTree<ElemType>::CopyTreeHelp(ChildSiblingTreeNode<ElemType> *copy)
// 操作结果：将以copy为根的树复制成新的树,返回新树的根
{
	if (copy == NULL)
	{	// 复制空二叉树
		return NULL;					// 空二叉树根为空	
	}
	else
	{	// 复制非空二叉树
		ChildSiblingTreeNode<ElemType> *r = new ChildSiblingTreeNode<ElemType>(copy->data);	// 复制根结点
		ChildSiblingTreeNode<ElemType> *subTreeRoot, *cur;
		for (ChildSiblingTreeNode<ElemType> *child = FirstChild(copy); child != NULL;
			child = RightSibling(child))
		{	// 复制子树
//			ChildSiblingTreeNode<ElemType> *subTreeRoot = CopyTreeHelp(child);	// 复制子树
			subTreeRoot = CopyTreeHelp(child);	// 复制子树
			if (r->firstChild == NULL)
			{	// subTreeRoot为首孩子
				r->firstChild = subTreeRoot;	// subTreeRoot为首孩子	
				cur = subTreeRoot;				// cur最新复制的子树的根
			}
			else
			{	// subTreeRoot为cur的右兄弟
				cur->rightSibling = subTreeRoot;// subTreeRoot为右兄弟
				cur = subTreeRoot;				// cur最新复制的子树的根
			}
		}
		return r;
	}
}

template <class ElemType>
ChildSiblingTree<ElemType>::ChildSiblingTree(const ChildSiblingTree<ElemType> &copy)
// 操作结果：由已知树构造新树——复制构造函数
{
	root = CopyTreeHelp(copy.GetRoot());
}
  
template <class ElemType>
ChildSiblingTreeNode<ElemType> *ChildSiblingTree<ElemType>::CreateTreeGhelp(ElemType items[], int parents[], int r, int n)
// 操作结果：建立数据元素为items[],对应结点双亲为parents[],根结点位置为r,结点个数为n的树，并返回树的根
{
	if (r >= 0 && r < n)
	{	// r合法
		ChildSiblingTreeNode<ElemType> *rt = new ChildSiblingTreeNode<ElemType>(items[r]);	// 复制根结点
		ChildSiblingTreeNode<ElemType> *subTreeRoot, *cur;

		for (int pos = 0; pos < n; pos++)
		{	// 查找r的孩子
			if (parents[pos] == r)
			{	// 建立以pos为根的子树
				subTreeRoot = CreateTreeGhelp(items, parents, pos, n);
				if (rt->firstChild == NULL)
				{	// subTreeRoot为第一棵子树的根
					rt->firstChild = subTreeRoot;		// subTreeRoot为首孩子	
					cur = subTreeRoot;					// cur最新建立的子树的根
				}
				else
				{	// subTreeRoot为cur的右兄弟
					cur->rightSibling = subTreeRoot;	// subTreeRoot为右兄弟
					cur = subTreeRoot;					// cur最新复制的子树的根
				}
			}
		}
		return rt;
	}
	else return NULL;									// r非法，建立空树
}


template <class ElemType>
ChildSiblingTree<ElemType>::ChildSiblingTree(ElemType items[], int parents[], int r, int n)
// 操作结果：建立数据元素为items[],对应结点双亲为parents[],根结点位置为r,结点个数为n的树
{
	root = CreateTreeGhelp(items, parents, r, n);	// 用辅助函数建立树
}

template <class ElemType>
ChildSiblingTree<ElemType>::ChildSiblingTree(ChildSiblingTreeNode<ElemType> *r)
// 操作结果：建立以r为根的树
{
	root = r;
}


template <class ElemType>
ChildSiblingTree<ElemType> &ChildSiblingTree<ElemType>::operator=(const ChildSiblingTree<ElemType> &copy)
// 操作结果：由已知树copy复制到当前树--赋值语句重载
{
	if (&copy != this)
	{
		DestroyHelp(root);							// 销毁树
		root = CopyTreeHelp(copy.GetRoot());
	}
	return *this;
}

template <class ElemType>
void DisplayTWithConcaveShapeHelp(const ChildSiblingTree<ElemType> &t, 
	ChildSiblingTreeNode<ElemType> *r, int level)
// 操作结果：按凹入表示法显示树，level为层次数，可设根结点的层次数为1
{
	if (r != NULL)
	{	// 非空根r
		cout<<endl;									//显示新行	
		for(int i = 0; i < level - 1; i++)
			cout<<" ";								//确保在第level列显示结点
		ElemType e;
		t.GetElem(r, e);							// 取出结点r的元素值
		cout << e;									// 显示结点元素值
		for (ChildSiblingTreeNode<ElemType> *child = t.FirstChild(r); child != NULL;
			child = t.RightSibling(child))
		{	// 依次显示各棵子树
			DisplayTWithConcaveShapeHelp(t, child, level + 1);
		}
	}
}

template <class ElemType>
void DisplayTWithConcaveShape(const ChildSiblingTree<ElemType> &t)
// 操作结果：按凹入表示法显示树
{
	DisplayTWithConcaveShapeHelp(t, t.GetRoot(), 1);// 调用辅助函数实现按凹入表示法显示树
	cout << endl;									// 换行
}

#endif
