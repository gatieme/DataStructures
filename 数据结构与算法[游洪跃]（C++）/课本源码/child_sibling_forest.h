#ifndef __CHILD_SIBLING_FOREST_H__
#define __CHILD_SIBLING_FOREST_H__

#include "lk_queue.h"							// 链队列
#include "child_sibling_tree_node.h"			// 孩子兄弟表示树结点类

// 孩子兄弟表示森林类
template <class ElemType>
class ChildSiblingForest
{
protected:
//  森林的数据成员:
	ChildSiblingTreeNode<ElemType> *root;		// 森林第一棵树的根

//	辅助函数:
	void DestroyHelp(ChildSiblingTreeNode<ElemType> * &r);		// 销毁以r为第一棵树根的森林
	void PreOrderHelp(ChildSiblingTreeNode<ElemType> *r, void (*Visit)(const ElemType &)) const;
		// 先序遍历以r为第一棵树的根的森林
	void InOrderHelp(ChildSiblingTreeNode<ElemType> *r, void (*Visit)(const ElemType &)) const;	
		// 中序遍历以r为第一棵树的根的森林
	int NodeCountHelp(ChildSiblingTreeNode<ElemType> *r) const;	// 返回结点个数
	void DeleteHelp(ChildSiblingTreeNode<ElemType> *r);	// 删除以r为第一棵树的根的森林
	ChildSiblingTreeNode<ElemType> *ParentHelp(ChildSiblingTreeNode<ElemType> *r, 
		const ChildSiblingTreeNode<ElemType> *cur) const;	// 返回cur的双亲
	ChildSiblingTreeNode<ElemType> *CopyTreeHelp(ChildSiblingTreeNode<ElemType> *copy);	
		// 复制森林
	ChildSiblingTreeNode<ElemType> *CreateForestHelp(ElemType items[], int parents[], int r, int n);
		// 建立数据元素为items[],对应结点双亲为parents[],第一棵树根结点位置为r,结点个数
		// 为n的森林，并返回森林的根

public:
//  森林方法声明及重载编译系统默认方法声明:
	ChildSiblingForest();									// 无参数的构造函数
	virtual ~ChildSiblingForest();							// 析构函数
	ChildSiblingTreeNode<ElemType> *GetFirstRoot() const;	// 返回森林的第一棵树的根
	bool Empty() const;								// 判断森林是否为空
	StatusCode GetElem(ChildSiblingTreeNode<ElemType> *cur, ElemType &e) const;
		// 用e返回结点元素值
	StatusCode SetElem(ChildSiblingTreeNode<ElemType> *cur, const ElemType &e);
		// 将结点cur的值置为e
	void PreOrder(void (*Visit)(const ElemType &)) const;		// 森林的先序遍历
	void InOrder(void (*Visit)(const ElemType &)) const;		// 森林的中序遍历
	void LevelOrder(void (*Visit)(const ElemType &)) const;		// 森林的层次遍历
	int NodeCount() const;							// 求森林的结点个数
	int NodeDegree(ChildSiblingTreeNode<ElemType> *cur) const;	// 求结点cur的度
	ChildSiblingTreeNode<ElemType> *FirstChild(ChildSiblingTreeNode<ElemType> *cur) const;	
		// 返回森林结点cur的第一个孩子
	ChildSiblingTreeNode<ElemType> *RightSibling(ChildSiblingTreeNode<ElemType> *cur) const;				
		// 返回森林结点cur的右兄弟
	ChildSiblingTreeNode<ElemType> *Parent(ChildSiblingTreeNode<ElemType> *cur) const;
		// 返回森林结点cur的双亲
	StatusCode InsertChild(ChildSiblingTreeNode<ElemType> *cur, int i, const ElemType &e);	
		// 将数据元素插入为cur的第i个孩子
	StatusCode DeleteChild(ChildSiblingTreeNode<ElemType> *cur, int i);		// 删除cur的第i个棵子森林
	ChildSiblingForest(const ElemType &e);					// 建立以数据元素e为根的树所构成的只有一棵树的森林
	ChildSiblingForest(const ChildSiblingForest<ElemType> &copy);	// 复制构造函数
	ChildSiblingForest(ElemType items[], int parents[], int n);
		// 建立数据元素为items[],对应结点双亲为parents[],结点个数为n的森林
	ChildSiblingForest(ChildSiblingTreeNode<ElemType> *r);// 建立以r为第一棵树的根的森林
	ChildSiblingForest<ElemType> &operator=(const ChildSiblingForest<ElemType>& copy);	
		// 赋值语句重载
};

template <class ElemType>
void DisplayTWithConcaveShapeHelp(const ChildSiblingForest<ElemType> &t, ChildSiblingTreeNode<ElemType> *r, int level);
	// 按凹入表示法显示森林，level为层次数，可设根结点的层次数为1
template <class ElemType>
void DisplayTWithConcaveShape(const ChildSiblingForest<ElemType> &f);
	// 按凹入表示法显示森林

// 孩子兄弟表示森林类的实现部分
template <class ElemType>
ChildSiblingForest<ElemType>::ChildSiblingForest()
// 操作结果：构造一个空森林
{
	root = NULL;						// 表示森林为空
}

template <class ElemType>
void ChildSiblingForest<ElemType>::DestroyHelp(ChildSiblingTreeNode<ElemType> * &r)
// 操作结果：销毁以r为第一棵树根的森林
{
	if (r != NULL)
	{	// r非空,实施销毁
		ChildSiblingTreeNode<ElemType> *fChild = FirstChild(r);		// 首孩子
		ChildSiblingTreeNode<ElemType> *rSibling = RightSibling(r);	// 右兄弟
		DestroyHelp(fChild);			// 销毁第一棵树的子树森林
		DestroyHelp(rSibling);			// 销毁除去第一棵树后剩余的树构成的森林
		delete r;						// 销毁根结点
		r = NULL;
	}
}

template <class ElemType>
ChildSiblingForest<ElemType>::~ChildSiblingForest()
// 操作结果：销毁森林--析造函数
{
	DestroyHelp(root);				// 销毁森林
}

template <class ElemType>
ChildSiblingTreeNode<ElemType> *ChildSiblingForest<ElemType>::GetFirstRoot() const
// 操作结果：返回森林的第一棵树的根
{
	return root;
}

template <class ElemType>
bool ChildSiblingForest<ElemType>::Empty() const
// 操作结果：判断森林是否为空
{
	return root == NULL;			// root为空表示森林为空
}

template <class ElemType>
StatusCode ChildSiblingForest<ElemType>::GetElem(ChildSiblingTreeNode<ElemType> *cur, ElemType &e) const
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
StatusCode ChildSiblingForest<ElemType>::SetElem(ChildSiblingTreeNode<ElemType> *cur, const ElemType &e)
// 操作结果：如果存在结点cur,则返回FAIL,否则返回SUCCESS,并将结点cur的值设置为e
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
void ChildSiblingForest<ElemType>::PreOrderHelp(ChildSiblingTreeNode<ElemType> *r, void (*Visit)(const ElemType &)) const
// 初始条件: r为森林中第一棵树的根
// 操作结果：按森林先序遍历依次对每个元素调用函数(*visit)
{
	if (r != NULL)
	{	// r非空
		(*Visit)(r->data);							// 访问第一棵树的根结点
		PreOrderHelp(FirstChild(r), Visit);			// 先序遍历第一棵树的子树森林
		PreOrderHelp(RightSibling(r), Visit);		// 先序遍历除去第一棵树后剩余的树构成的森林
	}
}

template <class ElemType>
void ChildSiblingForest<ElemType>::PreOrder(void (*Visit)(const ElemType &)) const
// 操作结果：按先序依次对森林的每个元素调用函数(*visit)
{
	PreOrderHelp(GetFirstRoot(), Visit);	// GetFirstRoot()为第一棵树的根
}

template <class ElemType>
void ChildSiblingForest<ElemType>::InOrderHelp(ChildSiblingTreeNode<ElemType> *r, 
	void (*Visit)(const ElemType &)) const
// 初始条件: r为森林中第一棵树的根
// 操作结果：按森林中序遍历依次对每个元素调用函数(*visit)
{
	if (r != NULL)
	{	// r非空
		InOrderHelp(FirstChild(r), Visit);			// 中序遍历第一棵树的子树森林
		(*Visit)(r->data);							// 访问第一棵树的根结点
		InOrderHelp(RightSibling(r), Visit);		// 中序遍历除去第一棵树后剩余的树构成的森林
	}
}

template <class ElemType>
void ChildSiblingForest<ElemType>::InOrder(void (*Visit)(const ElemType &)) const
// 操作结果：按中序依次对森林的每个元素调用函数(*visit)
{
	InOrderHelp(GetFirstRoot(), Visit);			// GetFirstRoot()为第一棵树的根
}

template <class ElemType>
void ChildSiblingForest<ElemType>::LevelOrder(void (*Visit)(const ElemType &)) const
// 操作结果：层次遍历森林
{
	for (ChildSiblingTreeNode<ElemType> *treeRoot = root; treeRoot != NULL; 
		treeRoot = RightSibling(treeRoot))
	{	// 依次层次遍历森林中每棵树
		LinkQueue<ChildSiblingTreeNode<ElemType> *> q;	// 队列
		ChildSiblingTreeNode<ElemType> *cur = treeRoot;	// 从根结点开始进行层次遍历
		
		if (cur != NULL) q.InQueue(cur);			// 如果根非空,则入队
		while (!q.Empty())
		{	// q非空,说明还有结点未访问
			q.OutQueue(cur);						// 出队
			(*Visit)(cur->data);				// 访问当前结点
			for (ChildSiblingTreeNode<ElemType> *child = FirstChild(cur); child != NULL;
				child = RightSibling(child))
			{	// 依次将cur的孩子入列
				q.InQueue(child);					// 孩子入队
			}
		}
	}
}

template <class ElemType>
int ChildSiblingForest<ElemType>::NodeCountHelp(ChildSiblingTreeNode<ElemType> *r) const
// 操作结果：返回以r为根的森林的结点个数
{
	if (r == NULL) return 0;			// 空森林结点个数为0
	else
	{	// 求子森林的结点个数之和
		int forestNodeCountSum = 0;		// 森林结点个数之和
		forestNodeCountSum += NodeCountHelp(FirstChild(r));	// 第一棵树的子树森林结点个数
		forestNodeCountSum += NodeCountHelp(RightSibling(r));	// 除去第一棵树后剩余的树构成的森林结点个数
		return 1 + forestNodeCountSum;	
			// 非空森林结点个为每一棵树子树森林的结点个数加上除去第一棵树后剩余的树构成的森林结点个数之和再加1
	}
}

template <class ElemType>
int ChildSiblingForest<ElemType>::NodeCount() const
// 操作结果：返回森林的结点个数
{
	return NodeCountHelp(root);			// 用辅助函数实现求森林结点个数
}

template <class ElemType>
int ChildSiblingForest<ElemType>::NodeDegree(ChildSiblingTreeNode<ElemType> *cur) const
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
ChildSiblingTreeNode<ElemType> *ChildSiblingForest<ElemType>::FirstChild(ChildSiblingTreeNode<ElemType> *cur) const
// 操作结果：如为NULL,则返回第一棵树的根,否则返回森林结点cur的第一个孩子,
{
	if (cur == NULL)
	{	// cur空,树的根的双亲为NULL,将森林中每棵树的根都看成为NULL的孩子
		return root;			
	}
	else
	{	// cur非空
		return cur->firstChild;			// firstChild为第一个孩子
	}
}

template <class ElemType>
ChildSiblingTreeNode<ElemType> *ChildSiblingForest<ElemType>::RightSibling(ChildSiblingTreeNode<ElemType> *cur) const
// 操作结果：如果结点cur无右兄弟,则返回NULL,否则返回cur的右兄弟
{
	if (cur == NULL)
	{	// cur为空
		return NULL;					// 空结点右兄弟
	}
	else
	{	// cur非空
		return cur->rightSibling;		// rightSibling为右兄弟
	}
}

template <class ElemType>
ChildSiblingTreeNode<ElemType> *ChildSiblingForest<ElemType>::ParentHelp(ChildSiblingTreeNode<ElemType> *r, 
	const ChildSiblingTreeNode<ElemType> *cur) const
// 操作结果：返回以r为第一棵树根的森林中, 结点cur的双亲
{
	if (r == NULL) return NULL;				// 空森林

	if (FirstChild(r) == cur)
	{	// r为cur的第一个孩子的双亲
		return r;
	}

	ChildSiblingTreeNode<ElemType> *tmp;
	tmp = ParentHelp(FirstChild(r), cur);	// 在第一棵树的子树森林上求双亲
	if (tmp != NULL) return tmp;			// 存在双亲,则返回双亲
	
	tmp = ParentHelp(RightSibling(r), cur);	// 在除去第一棵树后剩余的树构成的森林上求双亲
	if (tmp != NULL) return tmp;			// 存在双亲,则返回双亲

	return NULL;							// 未找到双亲
}

template <class ElemType>
ChildSiblingTreeNode<ElemType> *ChildSiblingForest<ElemType>::Parent(ChildSiblingTreeNode<ElemType> *cur) const
// 操作结果：返回森林中结点cur的双亲
{
	return ParentHelp(root, cur);			// 用辅助函数求森林中结点的双亲
}

template <class ElemType>
StatusCode ChildSiblingForest<ElemType>::InsertChild(ChildSiblingTreeNode<ElemType> *cur, int i, const ElemType &e)
// 操作结果：将数据元素插入为cur的第i个孩子,如果插入成功,则返回SUCCESS,否则返回FAIL
{
	if (cur == NULL) return FAIL;
	if (i < 0 || i > NodeDegree(cur) + 1) return FAIL;

	ChildSiblingTreeNode<ElemType> *newNodePtr = new ChildSiblingTreeNode<ElemType>(e);	// 新结点
	if (i == 1)
	{	// 插入的是首孩子
		ChildSiblingTreeNode<ElemType> *tmp = cur->firstChild;	// 暂存cur的首孩子
		cur->firstChild = newNodePtr;		// newNodePtr插入为cur的首孩子
		newNodePtr->rightSibling = tmp;		// 原cur的首孩子变为newNodePtr的右兄弟
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
void ChildSiblingForest<ElemType>::DeleteHelp(ChildSiblingTreeNode<ElemType> *r)
// 操作结果：删除以r为第一棵的根的森林
{
	if (r != NULL)
	{	// r非空
		DeleteHelp(FirstChild(r));			// 删除第一棵树的子树森林
		DeleteHelp(RightSibling(r));		// 删除除去第一棵树后剩余的树构成的森林
		delete r;							// 释放r
		r = NULL;
	}
}

template <class ElemType>
StatusCode ChildSiblingForest<ElemType>::DeleteChild(ChildSiblingTreeNode<ElemType> *cur, int i)
// 操作结果：删除cur的第i个棵子森林,如果删除成功,则返回SUCCESS,否则返回FAIL
{
	if (i < 0 && i > NodeDegree(cur)) return FAIL;	// 操作失败
	if (i == 1)
	{
		ChildSiblingTreeNode<ElemType> *tmp = cur->firstChild;	// 暂存第1棵子森林的根
		cur->firstChild = tmp->rightSibling;		// 在逻辑上删除第1棵子森林
		DeleteHelp(tmp);							// 物理上删除第1棵子森林
	}
	else
	{
		int n = 1;
		ChildSiblingTreeNode<ElemType> *child;		// 孩子 
		for (child = FirstChild(cur); n < i - 1 && child != NULL; 
			child = RightSibling(child), n++);
 			// 查找第i - 1个孩子

		ChildSiblingTreeNode<ElemType> *tmp = child->rightSibling;	// 暂存第i棵子森林的根
		child->rightSibling = tmp->rightSibling;		// 辑逻上删除第i个棵子森林
		DeleteHelp(tmp);								// 物理上删除第i棵子森林
		return SUCCESS;									// 操作成功
	}
	return SUCCESS;										// 操作成功
}

template <class ElemType>
ChildSiblingForest<ElemType>::ChildSiblingForest(const ElemType &e)
// 操作结果：建立以数据元素e为根的树所构成的只有一棵树的森林
{
	root = new ChildSiblingTreeNode<ElemType>(e);	// 生成根结点
}

template <class ElemType>
ChildSiblingTreeNode<ElemType> *ChildSiblingForest<ElemType>::CopyTreeHelp(ChildSiblingTreeNode<ElemType> *copy)
// 操作结果：将以copy为第一棵树的根的森林复制成新的森林,返回新森林第一棵树的根
{
	if (copy == NULL)
	{	// 复制空森林
		return NULL;					// 空森林第一棵子树的根为空	
	}
	else
	{	// 复制非空森林
		ChildSiblingTreeNode<ElemType> *r = new ChildSiblingTreeNode<ElemType>(copy->data);	// 复制第一棵树根结点
		r->firstChild = CopyTreeHelp(copy->firstChild);	// 复制第一棵对的子树森林
		r->rightSibling = CopyTreeHelp(copy->rightSibling);	// 复制除去第一棵树后剩余的树构成的森林
		return r;
	}	
}

template <class ElemType>
ChildSiblingForest<ElemType>::ChildSiblingForest(const ChildSiblingForest<ElemType> &copy)
// 操作结果：由已知森林构造新森林——复制构造函数
{
	root = CopyTreeHelp(copy.FirstChild(NULL));
}
  
template <class ElemType>
ChildSiblingTreeNode<ElemType> *ChildSiblingForest<ElemType>::CreateForestHelp(ElemType items[], int parents[], int r, int n)
// 操作结果：建立数据元素为items[],对应结点双亲为parents[],第一棵树根结点位置为r,结点个数为n的树，并返回第一棵树的根
{
	if (r >= 0 || r < n)
	{
		ChildSiblingTreeNode<ElemType> *rt = new ChildSiblingTreeNode<ElemType>(items[r]);
			// 复制第一棵树的根结点

		for (int fChild = 0; fChild < n; fChild++)
		{	// 查找r的第一个孩子
			if (parents[fChild] == r)
			{	// 建立第一棵树的子树森林
				rt->firstChild = CreateForestHelp(items, parents, fChild, n);
				break;
			}
		}

		for (int rSibling = r + 1; rSibling < n; rSibling++)
		{	// 查找r的右兄弟
			if (parents[rSibling] == parents[r])
			{	// 建立除去第一棵树后剩余的树构成的森林
				rt->rightSibling = CreateForestHelp(items, parents, rSibling, n);
				break;
			}
		}
		return rt;					// 第一棵树的根
	}
	else return NULL;				// 空森林
}

template <class ElemType>
ChildSiblingForest<ElemType>::ChildSiblingForest(ElemType items[], int parents[], int n)
// 操作结果：建立数据元素为items[],对应结点双亲为parents[],结点个数为n的森林
{
	int r;							// 临时变量 
	for (r = 0; r < n; r++)
	{	// 查找第一棵树的根
		if (parents[r] == -1)
		{	// r为第一棵树的根
			root = CreateForestHelp(items, parents, r, n);	// 用辅助函数建立森林
			return;
		}
	}
	if (r >= n) root = NULL;		// 未找到根,空森林
}

template <class ElemType>
ChildSiblingForest<ElemType>::ChildSiblingForest(ChildSiblingTreeNode<ElemType> *r)
// 操作结果：建立以r为第一棵树的根的森林
{
	root = r;
}

template <class ElemType>
ChildSiblingForest<ElemType> &ChildSiblingForest<ElemType>::operator=(const ChildSiblingForest<ElemType> &copy)
// 操作结果：由已知森林copy复制到当前森林--赋值语句重载
{
	if (&copy != this)
	{
		DestroyHelp(root);							// 销毁森林
		root = CopyTreeHelp(copy.FirstChild(NULL));
	}
	return *this;
}

template <class ElemType>
void DisplayTWithConcaveShapeHelp(const ChildSiblingForest<ElemType> &f, ChildSiblingTreeNode<ElemType> *r, int level)
// 操作结果：按凹入表示法显示森林，level为层次数，可设根结点的层次数为1
{
	if (r != NULL)
	{	// 非空根r
		cout<<endl;									//显示新行	
		for(int i = 0; i < level - 1; i++)
			cout<<" ";								//确保在第level列显示结点
		ElemType e;
		f.GetElem(r, e);							// 取出结点r的元素值
		cout << e;									// 显示结点元素值
		for (ChildSiblingTreeNode<ElemType> *child = f.FirstChild(r); child != NULL;
			child = f.RightSibling(child))
		{	// 依次显示各棵子森林
			DisplayTWithConcaveShapeHelp(f, child, level + 1);
		}
	}
}

template <class ElemType>
void DisplayTWithConcaveShape(const ChildSiblingForest<ElemType> &f)
// 操作结果：按凹入表示法显示森林
{
	for (ChildSiblingTreeNode<ElemType> *cur = f.GetFirstRoot(); cur != NULL;
		cur = f.RightSibling(cur))
	{	// 查找森林中各棵树的根结点
		DisplayTWithConcaveShapeHelp(f, cur, 1);
			// 调用辅助函数实现按凹入表示法显示森林的各棵树
		cout << endl;								// 换行
	}
}

#endif
