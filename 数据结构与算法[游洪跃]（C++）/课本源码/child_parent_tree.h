#ifndef __CHILD_PARENT_TREE_H__
#define __CHILD_PARENT_TREE_H__

#include "lk_queue.h"				// 链队列
#include "child_parent_tree_node.h"	// 孩子双亲表示树结点类

// 孩子双亲表示树类
template <class ElemType>
class ChildParentTree
{
protected:
//  树的数据成员:
	ChildParentTreeNode<ElemType> *nodes;			// 存储树结点
	int maxSize;									// 树结点最大个数 
	int root, num;									// 根的位置及结点数

//	辅助函数:
	void PreRootOrderHelp(int r, void (*Visit)(const ElemType &)) const;	// 先根序遍历
	void PostRootOrderHelp(int r, void (*Visit)(const ElemType &)) const;	// 后根序遍历
	int HeightHelp(int r) const;					// 返回以r为根的高
	int DegreeHelp(int r) const;					// 返回以r为根的树的度
	void MoveHelp(int from, int to);				// 将结点从from移到结点to
	void DeleteHelp(int r);							// 删除以r主根的树

public:
//  树方法声明及重载编译系统默认方法声明:
	ChildParentTree();								// 无参构造函数
	virtual ~ChildParentTree();						// 析构函数
	int GetRoot() const;							// 返回树的根
	bool Empty() const;								// 判断树是否为空
	StatusCode GetElem(int cur, ElemType &e) const;	// 用e返回结点元素值
	StatusCode SetElem(int cur, const ElemType &e);	// 将结cur的值置为e
	void PreRootOrder(void (*Visit)(const ElemType &)) const;	// 树的先序遍历
	void PostRootOrder(void (*Visit)(const ElemType &)) const;	// 树的后序遍历
	void LevelOrder(void (*Visit)(const ElemType &)) const;		// 树的层次遍历
	int NodeCount() const;							// 返回树的结点个数
	int NodeDegree(int cur) const;					// 返回结点cur的度
	int Degree() const;								// 返回树的度
	int FirstChild(int cur) const;					// 返回结点cur的第一个孩子
	int RightSibling(int cur) const;				// 返回结点cur的右兄弟
	int Parent(int cur) const;						// 返回结点cur的双亲
	StatusCode InsertChild(int cur, int i, const ElemType &e);	
		// 将数据元素插入为cur的第i个孩子
	StatusCode DeleteChild(int cur, int i);			// 删除cur的第i个棵子树
	int	Height() const;								// 返回树的高
	ChildParentTree(const ElemType &e, int size = DEFAULT_SIZE);
		// 建立以数据元素e为根的树
	ChildParentTree(const ChildParentTree<ElemType> &copy);	// 复制构造函数
	ChildParentTree(ElemType items[], int parents[], int r, int n, int size = DEFAULT_SIZE);
		// 建立数据元素为items[],对应结点双亲为parents[],根结点位置为r,结点个数为n的树
	ChildParentTree<ElemType> &operator=(const ChildParentTree<ElemType>& copy);	
		// 赋值语句重载
};

template <class ElemType>
void DisplayTWithConcaveShapeHelp(const ChildParentTree<ElemType> &t, int r, int level);
	// 按凹入表示法显示树，level为层次数，可设根结点的层次数为1
template <class ElemType>
void DisplayTWithConcaveShape(const ChildParentTree<ElemType> &t);
	// 按凹入表示法显示树

// 孩子双亲表示树类的实现部分
template <class ElemType>
ChildParentTree<ElemType>::ChildParentTree()
// 操作结果：构造一个空树
{
	maxSize = DEFAULT_SIZE;								// 树结点最大个数
	nodes = new ChildParentTreeNode<ElemType>[maxSize];	// 分配存储空间
	root = -1;											// 表示不存在根
	num = 0;											// 空树的结点个数为0
}

template <class ElemType>
ChildParentTree<ElemType>::~ChildParentTree()
// 操作结果：释放存储空间
{
	delete []nodes;										// 释放存储空间
}



template <class ElemType>
int ChildParentTree<ElemType>::GetRoot() const
// 操作结果：返回树的根
{
	return root;
}

template <class ElemType>
bool ChildParentTree<ElemType>::Empty() const
// 操作结果：判断树是否为空
{
	return num == 0;
}

template <class ElemType>
StatusCode ChildParentTree<ElemType>::GetElem(int cur, ElemType &e) const
// 操作结果：用e返回结点cur元素值,如果不存在结点cur,函数返回NOT_PRESENT,否则返回ENTRY_FOUND
{
	if (cur < 0 || cur >= num)	
	{	// 不存在结点cur
		return NOT_PRESENT;					// 返回NOT_PRESENT
	}
	else
	{	// 存在结点cur
		e = nodes[cur].data;				// 用e返回元素值
		return ENTRY_FOUND;					// 返回ENTRY_FOUND
	}
}

template <class ElemType>
StatusCode ChildParentTree<ElemType>::SetElem(int cur, const ElemType &e)
// 操作结果：如果不存在结点cur,则返回FAIL,否则返回SUCCESS,并将结点cur的值设置为e
{
	if (cur < 0 || cur >= num)	
	{	// 不存在结点cur
		return FAIL;						// 返回FAIL
	}
	else
	{	// 存在结点cur
		nodes[cur].data = e;				// 将结点cur的值设置为e
		return SUCCESS;						// 返回SUCCESS
	}
}

template <class ElemType>
void ChildParentTree<ElemType>::PreRootOrderHelp(int r, void (*Visit)(const ElemType &)) const
// 操作结果：按先根序依次对以r为根的树的每个元素调用函数(*visit)
{
	if (r >=0 && r < num)
	{	// r范围合法
		(*Visit)(nodes[r].data);			// 访问根结点
		for (int child = FirstChild(r); child != -1; child = RightSibling(child))
		{	// 依次先根序遍历每棵子树
			PreRootOrderHelp(child, Visit);
		}
	}
}

template <class ElemType>
void ChildParentTree<ElemType>::PreRootOrder(void (*Visit)(const ElemType &)) const
// 操作结果：按先根序依次对树的每个元素调用函数(*visit)
{
	PreRootOrderHelp(GetRoot(), Visit);		// 调用辅助函数实现后先序遍历
}

template <class ElemType>
void ChildParentTree<ElemType>::PostRootOrderHelp(int r, void (*Visit)(const ElemType &)) const
// 操作结果：按后根序依次对以r为根的树的每个元素调用函数(*visit)
{
	if (r >=0 && r < num)
	{	// r范围合法
		for (int child = FirstChild(r); child != -1; child = RightSibling(child))
		{	// 依次后根序遍历每棵子树
			PostRootOrderHelp(child, Visit);
		}
		(*Visit)(nodes[r].data);			// 访问根结点
	}
}

template <class ElemType>
void ChildParentTree<ElemType>::PostRootOrder(void (*Visit)(const ElemType &)) const
// 操作结果：按后根序依次对树的每个元素调用函数(*visit)
{
	PostRootOrderHelp(GetRoot(), Visit);	// 调用辅助函数实现后根序遍历
}

template <class ElemType>
void ChildParentTree<ElemType>::LevelOrder(void (*Visit)(const ElemType &)) const
// 操作结果：层次遍历树
{
	LinkQueue<int> q;	// 队列
	int cur = root;		// 从根结点开始进行层次遍历
	
	if (cur >= 0 || cur < num) q.InQueue(cur);	// 如果根合法,则入队
	while (!q.Empty())
	{	// q非空,说明还有结点未访问
		q.OutQueue(cur);						// 出队
		(*Visit)(nodes[cur].data);				// 访问当前结点
		for (int child = FirstChild(cur); child != -1; child = RightSibling(child))
		{	// 依次将cur的孩子入列
			q.InQueue(child);					// 孩子入队
		}
	}
}

template <class ElemType>
int ChildParentTree<ElemType>::HeightHelp(int r) const
// 操作结果：返回以r为根的树的高
{
	if (r < 0 || r >= num)
	{	// 空树,高为0
		return 0;
	}
	else
	{
		int maxSubTreeHeight = 0;
		for (int child = FirstChild(r); child != -1; child = RightSibling(child))
		{	// 求各子树高的最大值
			int h = HeightHelp(child);			// 临时变量存储高
			maxSubTreeHeight = (maxSubTreeHeight < h) ? h : maxSubTreeHeight;
				// 求条子树高的最大值
		}
		return maxSubTreeHeight + 1;			// 树高为各子树的最大值再加1
	}
}

template <class ElemType>
int ChildParentTree<ElemType>::Height() const
// 操作结果：返回树的高
{
	return HeightHelp(root);					// 调用辅助函数实现返回树的高
}

template <class ElemType>
int ChildParentTree<ElemType>::NodeCount() const
// 操作结果：返回树的结点个数
{
	return num;
}

template <class ElemType>
int ChildParentTree<ElemType>::NodeDegree(int cur) const
// 操作结果：返回结点cur的度
{
	int d = 0;						// 临时变量,用于对孩子个数进行计数
	for (int child = FirstChild(cur); child != -1; child = RightSibling(child))
	{	// 找查cur的孩子
		d++;						// 对孩子个数进行计数
	}
	return d;
}

template <class ElemType>
int ChildParentTree<ElemType>::DegreeHelp(int r) const
// 操作结果：返回以r为根的树的度
{

	int d = 0;						// 临时变量,用于结点的孩子个数
	int maxSubTreeDegree = 0;		// 子树度的最大值
	for (int child = FirstChild(r); child != -1; child = RightSibling(child))
	{	// 找查r的孩子
		d++;						// 对孩子个数进行计数
		int subTreeDegree = DegreeHelp(child);	// 子树的度
		maxSubTreeDegree = (maxSubTreeDegree < subTreeDegree) ? subTreeDegree : maxSubTreeDegree;
			// 求子树度最大值
	}
	return (d < maxSubTreeDegree) ? maxSubTreeDegree : d;
}

template <class ElemType>
int ChildParentTree<ElemType>::Degree() const
// 操作结果：返回树的度
{
	return DegreeHelp(root);
}

template <class ElemType>
int ChildParentTree<ElemType>::FirstChild(int cur) const
// 操作结果：如cur无孩子,则返回-1,否则返回树结点cur的第一个孩子,
{
	if (cur < 0 || cur >= num)	
		return -1;						// 结点cur不存在,返回-1表示无孩子
	
	if (nodes[cur].childLkList.Empty())
	{	// 无孩子
		return -1;
	}
	else
	{
		int child;
		nodes[cur].childLkList.GetElem(1, child);	// 取出第一个孩子
		return child;
	}
}

template <class ElemType>
int ChildParentTree<ElemType>::RightSibling(int cur) const
// 操作结果：如果结点cur无右兄弟,则返回-1,否则返回cur的右兄弟
{
	if (cur < 0 || cur >= num)						
		return -1;						// 结点cur不存在,返回-1表示无孩子

	int pt = nodes[cur].parent;			// cur的双亲 
	for (int pos = 1; pos < nodes[pt].childLkList.Length(); pos++)
	{	// 查找cur在孩子链表中的位置
		int child;
		nodes[pt].childLkList.GetElem(pos, child);	// 取出孩子
		if (cur == child)
		{	// pos为cur在孩子链表中的位置
			int rightSibling;							
			if (nodes[pt].childLkList.GetElem(pos + 1, rightSibling) == ENTRY_FOUND)
			{	// 存在右兄弟
				return rightSibling;				// 反回右兄弟
			}
			else
			{	// 不存在右兄弟
				return -1;				// 表示无右兄弟
			}
		}
	}
	return -1;							// 查找失败,表示无兄弟
}

template <class ElemType>
int ChildParentTree<ElemType>::Parent(int cur) const
// 操作结果：返回树结点cur的双亲
{
	if (cur < 0 || cur >= num)						
		return -1;						// 结点cur不存在,返回-1表示无双亲
	return nodes[cur].parent;
}

template <class ElemType>
void ChildParentTree<ElemType>::MoveHelp(int from, int to)
// 操作结果：将结点从from移到to
{
	nodes[to] = nodes[from];						// 将nodes[from]赋值给nodes[to]
	nodes[from].childLkList.Clear();				// 清空from的孩子链表
	for (int pos = 0; pos < num; pos++)
	{	// 将以from为双亲的结点改为以to为双亲的结点
		if (from == nodes[pos].parent) nodes[pos].parent = to;
	}
}

template <class ElemType>
StatusCode ChildParentTree<ElemType>::InsertChild(int cur, int i, const ElemType &e)
// 操作结果：将数据元素插入为cur的第i个孩子,如果插入成功,则返回SUCCESS,否则返回FAIL
{
	if (cur < 0 || cur >= num) return FAIL;
	if (i < 0 || i > NodeDegree(cur) + 1) return FAIL;
	int n, child;									// 临时变量 
	for (n = 1, child = FirstChild(cur); n < i && child != -1; child = RightSibling(child), n++);
		// 查找第i个孩子的位置
	if (child != -1)
	{	// 存在第i个孩子,第i个孩子的位置为插入位置
		for (int pos = num - 1; pos >= child; pos--)
		{	// 从num - 1到child的结点依次后移
			MoveHelp(pos, pos + 1);
		}
		nodes[child].data = e;						// 将结点child的的数据元素值赋为e
		nodes[child].parent = cur;					// 结点child的双亲为cur
		LinkList<int> &cLkList = nodes[cur].childLkList;// 双亲的孩子链表
		cLkList.Insert(i, child);	// 将child插入在双亲的孩子链表中
	}
	else
	{	// 不存在第i+1个孩子,插在最后
		child = num;								// child为最后位置
		nodes[child].data = e;						// 将结点child的的数据元素值赋为e
		nodes[child].parent = cur;					// 结点child的双亲为cur
		LinkList<int> &cLkList = nodes[cur].childLkList;// 双亲的孩子链表
		cLkList.Insert(cLkList.Length() + 1, child);	// 将child插入在双亲的孩子链表中
	}
	num++;											// 插入成功,结点数自加1
	return SUCCESS;
}

template <class ElemType>
void ChildParentTree<ElemType>::DeleteHelp(int r)
// 操作结果：删除以r主根的树
{
	if (r >= 0 || r < num)
	{	// r合法
		for (int child = FirstChild(r); child != -1; child = RightSibling(child))
		{	// 找查r的子树
			DeleteHelp(child);						// 删除以child根的子树
		}
		nodes[r].parent = -2;						// 双亲为-2,特表示此结点已被删除
	}
}

template <class ElemType>
StatusCode ChildParentTree<ElemType>::DeleteChild(int cur, int i)
// 操作结果：删除cur的第i个棵子树,如果删除成功,则返回SUCCESS,否则返回FAIL
{
	if (i < 0 && i > NodeDegree(cur)) return FAIL;	// 操作失败
	int n, child;									// 临时变量 
	for (n = 1, child = FirstChild(cur); n < i && child != -1; child = RightSibling(child), n++);
		// 查找第i个孩子的位置
	
	DeleteHelp(child);								// 删除第i棵子树
	for (int pos = num - 1; pos >= 0; pos--)
	{	// 清除被删除的结点
		if (Parent(pos) == -2)
		{	// 被删除结点
			for (int i = num - 1; i >= pos + 1; i--)
			{	// 从num - 1到pos + 1的结点依次前移
				MoveHelp(i, i - 1);					// 前移
			}
			nodes[pos].childLkList.Clear();			// 清空孩子链表
			num--;									// 清除被删除结点后,结点个数自减1			
		}
	}
	return SUCCESS;									// 操作成功
}

template <class ElemType>
ChildParentTree<ElemType>::ChildParentTree(const ElemType &e, int size)
// 操作结果：建立以数据元素e为根的树
{
	maxSize = DEFAULT_SIZE;							// 树结点最大个数
	nodes = new ChildParentTreeNode<ElemType>[maxSize];	// 分配存储空间
	root = 0;										// 根的位置
	nodes[root].data = e;							// 对数据域进行赋值
	nodes[root].parent = -1;						// 根的双亲为-1
	num = 1;										// 结点个数
}

template <class ElemType>
ChildParentTree<ElemType>::ChildParentTree(const ChildParentTree<ElemType> &copy)
// 操作结果：由已知树构造新树——复制构造函数
{
	maxSize = copy.maxSize;											// 最大结点个数
	nodes = new ChildParentTreeNode<ElemType>[maxSize];				// 分配存储空间
	for (int pos = 0; pos < copy.num; pos++)
	{	// 依次对结点数据元素及双亲位置进行赋值
		nodes[pos].data = copy.nodes[pos].data;						// 数据元素值
		nodes[pos].parent = copy.nodes[pos].parent;					// 双亲位置
		nodes[pos].childLkList = copy.nodes[pos].childLkList;		// 孩子链表
	}
	root = copy.root;												// 根
	num = copy.num;													// 结点个数
}
  
template <class ElemType>
ChildParentTree<ElemType>::ChildParentTree(ElemType items[], int parents[], int r, int n, int size)
// 操作结果：建立数据元素为items[],对应结点双亲为parents[],根结点位置为r,结点个数为n的树
{
	maxSize = size;													// 最大结点个数
	if (n > maxSize)	
		throw Error("结点个数太多!");								// 抛出异常
	nodes = new ChildParentTreeNode<ElemType>[maxSize];				// 分配存储空间
	for (int pos = 0; pos < n; pos++)
	{	// 依次对结点数据元素及双亲位置进行赋值
		nodes[pos].data = items[pos];								// 数据元素值
		nodes[pos].parent = parents[pos];							// 双亲位置
		if (parents[pos] != -1)
		{
			LinkList<int> &cLkList = nodes[parents[pos]].childLkList;	// 双亲的孩子链表
			cLkList.Insert(cLkList.Length() + 1, pos);					// 将pos插入在双亲的孩子链表中
		}
	}
	root = r;														// 根
	num = n;														// 结点个数
}

template <class ElemType>
ChildParentTree<ElemType> &ChildParentTree<ElemType>::operator=(const ChildParentTree<ElemType> &copy)
// 操作结果：由已知树copy复制到当前树--赋值语句重载
{
	if (&copy != this)
	{
		maxSize = copy.maxSize;										// 最大结点个数
		delete []nodes;												// 释放存储空间
		nodes = new ChildParentTreeNode<ElemType>[maxSize];			// 分配存储空间
		for (int pos = 0; pos < copy.num; pos++)
		{	// 依次对结点数据元素及双亲位置进行赋值
			nodes[pos].data = copy.nodes[pos].data;					// 数据元素值
			nodes[pos].parent = copy.nodes[pos].parent;				// 双亲位置
			nodes[pos].childLkList = copy.nodes[pos].childLkList;	// 孩子链表
		}
		root = copy.root;											// 根
		num = copy.num;												// 结点个数
	}
	return *this;
}

template <class ElemType>
void DisplayTWithConcaveShapeHelp(const ChildParentTree<ElemType> &t, int r, int level)
// 操作结果：按凹入表示法显示树，level为层次数，可设根结点的层次数为1
{
	if (r >= 0 && r < t.NodeCount())
	{	// 存在结点r,才显示r的信息
		cout<<endl;													//显示新行	
		for(int i = 0; i< level - 1; i++)
			cout<<" ";												//确保在第level列显示结点
		ElemType e;
		t.GetElem(r, e);											// 取出结点r的元素值
		cout << e;													// 显示结点元素值
		for (int child = t.FirstChild(r); child != -1; child = t.RightSibling(child))
		{	// 依次显示各棵子树
			DisplayTWithConcaveShapeHelp(t, child, level + 1);
		}
	}
}

template <class ElemType>
void DisplayTWithConcaveShape(const ChildParentTree<ElemType> &t)
// 操作结果：按凹入表示法显示树
{
	DisplayTWithConcaveShapeHelp(t, t.GetRoot(), 1);				// 调用辅助函数实现按凹入表示法显示树
	cout << endl;													// 换行
}

#endif
