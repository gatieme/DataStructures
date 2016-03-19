#ifndef __CHILD_PARENT_FOREST_H__
#define __CHILD_PARENT_FOREST_H__

#include "lk_queue.h"												// 链队列
#include "child_parent_tree_node.h"									// 孩子双亲表示森林结点类

// 孩子双亲表示森林类
template <class ElemType>
class ChildParentForest
{
protected:
//  森林的数据成员:
	ChildParentTreeNode<ElemType> *nodes;							// 存储森林结点
	int maxSize;													// 森林结点最大个数 
	int num;														// 根的位置及结点数

//	辅助函数:
	void PreOrderHelp(int r, void (*Visit)(const ElemType &)) const;// 先序遍历以r为第一棵树的根的森林
	void InOrderHelp(int r, void (*Visit)(const ElemType &)) const;	// 中序遍历以r为第一棵树的根的森林
	void MoveHelp(int from, int to);								// 将结点从from移到结点to
	void DeleteHelp(int r);											// 删除以r为根的森林

public:
//  森林方法声明及重载编译系统默认方法声明:
	ChildParentForest();											// 无参数的构造函数
	virtual ~ChildParentForest();									// 析构函数
	int GetFirstRoot() const;										// 返回森林的第一棵树的根
	bool Empty() const;												// 判断森林是否为空
	StatusCode GetElem(int cur, ElemType &e) const;					// 用e返回结点元素值
	StatusCode SetElem(int cur, const ElemType &e);					// 将结点cur的值置为e
	void PreOrder(void (*Visit)(const ElemType &)) const;			// 森林的先序遍历
	void InOrder(void (*Visit)(const ElemType &)) const;			// 森林的中序遍历
	void LevelOrder(void (*Visit)(const ElemType &)) const;			// 森林的层次遍历
	int NodeCount() const;											// 求森林的结点个数
	int NodeDegree(int cur) const;									// 求结点cur的度
	int FirstChild(int cur) const;									// 返回结点cur的第一个孩子
	int RightSibling(int cur) const;								// 返回结点cur的右兄弟
	int Parent(int cur) const;										// 返回结点cur的双亲
	StatusCode InsertChild(int cur, int i, const ElemType &e);	
		// 将数据元素插入为cur的第i个孩子
	StatusCode DeleteChild(int cur, int i);							// 删除cur的第i个棵子森林
	ChildParentForest(const ElemType &e, int size = DEFAULT_SIZE);
		// 建立以数据元素e为根的树所构成的只有一棵树的森林
	ChildParentForest(const ChildParentForest<ElemType> &copy);		// 复制构造函数
	ChildParentForest(ElemType items[], int parents[], int n, int size = DEFAULT_SIZE);
		// 建立数据元素为items[],对应结点双亲为parents[],结点个数为n的森林
	ChildParentForest<ElemType> &operator=(const ChildParentForest<ElemType>& copy);	
		// 赋值语句重载
};

template <class ElemType>
void DisplayTWithConcaveShapeHelp(const ChildParentForest<ElemType> &f, int r, int level);
	// 按凹入表示法显示森林，level为层次数，可设根结点的层次数为1
template <class ElemType>
void DisplayTWithConcaveShape(const ChildParentForest<ElemType> &f);
	// 按凹入表示法显示森林

// 孩子双亲表示森林类的实现部分
template <class ElemType>
ChildParentForest<ElemType>::ChildParentForest()
// 操作结果：构造一个空森林
{
	maxSize = DEFAULT_SIZE;											// 森林结点最大个数
	nodes = new ChildParentTreeNode<ElemType>[maxSize];				// 分配存储空间
	num = 0;														// 空森林的结点个数为0
}

template <class ElemType>
ChildParentForest<ElemType>::~ChildParentForest()
// 操作结果：销毁森林
{
	delete []nodes;													// 释放存储空间
}

template <class ElemType>
int ChildParentForest<ElemType>::GetFirstRoot() const
// 操作结果：返回森林的第一棵树的根
{
	for (int r = 0; r < num; r++)
	{	// 找查第一棵树的根
		if (Parent(r) == -1) return r;								// pos为第一棵树的根
	}
	return -1;														// 空森林根为空
}

template <class ElemType>
bool ChildParentForest<ElemType>::Empty() const
// 操作结果：判断森林是否为空
{
	return num == 0;
}

template <class ElemType>
StatusCode ChildParentForest<ElemType>::GetElem(int cur, ElemType &e) const
// 操作结果：用e返回结点cur元素值,如果不存在结点cur,函数返回NOT_PRESENT,否则返回ENTRY_FOUND
{
	if (cur < 0 || cur >= num)	
	{	// 不存在结点cur
		return NOT_PRESENT;											// 返回NOT_PRESENT
	}
	else
	{	// 存在结点cur
		e = nodes[cur].data;										// 用e返回元素值
		return ENTRY_FOUND;											// 返回ENTRY_FOUND
	}
}

template <class ElemType>
StatusCode ChildParentForest<ElemType>::SetElem(int cur, const ElemType &e)
// 操作结果：如果不存在结点cur,则返回FAIL,否则返回SUCCESS,并将结点cur的值设置为e
{
	if (cur < 0 || cur >= num)	
	{	// 不存在结点cur
		return FAIL;												// 返回FAIL
	}
	else
	{	// 存在结点cur
		nodes[cur].data = e;										// 将结点cur的值设置为e
		return SUCCESS;												// 返回SUCCESS
	}
}

template <class ElemType>
void ChildParentForest<ElemType>::PreOrderHelp(int r, void (*Visit)(const ElemType &)) const
// 初始条件: r为森林中第一棵树的根
// 操作结果：按森林先序遍历依次对每个元素调用函数(*visit)
{
	if (r >=0 && r < num)
	{	// r范围合法
		(*Visit)(nodes[r].data);									// 访问第一棵树的根结点
		PreOrderHelp(FirstChild(r), Visit);							// 先序遍历第一棵树的子树森林
		PreOrderHelp(RightSibling(r), Visit);						// 先序遍历除去第一棵树后剩余的树构成的森林
	}
}

template <class ElemType>
void ChildParentForest<ElemType>::PreOrder(void (*Visit)(const ElemType &)) const
// 操作结果：按先序依次对森林的每个元素调用函数(*visit)
{
	PreOrderHelp(GetFirstRoot(), Visit);							// GetFirstRoot()为第一棵树的根
}

template <class ElemType>
void ChildParentForest<ElemType>::InOrderHelp(int r, void (*Visit)(const ElemType &)) const
// 初始条件: r为森林中第一棵树的根
// 操作结果：按森林中序遍历依次对每个元素调用函数(*visit)
{
	if (r >=0 && r < num)
	{	// r范围合法
		InOrderHelp(FirstChild(r), Visit);							// 中序遍历第一棵树的子树森林
		(*Visit)(nodes[r].data);									// 访问第一棵树的根结点
		InOrderHelp(RightSibling(r), Visit);						// 中序遍历除去第一棵树后剩余的树构成的森林
	}
}

template <class ElemType>
void ChildParentForest<ElemType>::InOrder(void (*Visit)(const ElemType &)) const
// 操作结果：按中序依次对森林的每个元素调用函数(*visit)
{
	InOrderHelp(GetFirstRoot(), Visit);								// GetFirstRoot()为第一棵树的根
}

template <class ElemType>
void ChildParentForest<ElemType>::LevelOrder(void (*Visit)(const ElemType &)) const
// 操作结果：层次遍历森林
{
	for (int cur = 0; cur < num; cur++)
	{	// 查找森林中各棵树的根结点
		if (nodes[cur].parent == -1)				
		{	// 根结点,层次遍历以cur为根的树
			LinkQueue<int> q;	// 队列
			q.InQueue(cur);	// 将子树根入队
		
			while (!q.Empty())
			{	// q非空,说明还有结点未访问
				q.OutQueue(cur);									// 出队
				(*Visit)(nodes[cur].data);							// 访问当前结点
				for (int child = FirstChild(cur); child != -1; child = RightSibling(child))
				{	// 依次将cur的孩子入列
					q.InQueue(child);								// 孩子入队
				}
			}
		}
	}
}

template <class ElemType>
int ChildParentForest<ElemType>::NodeCount() const
// 操作结果：返回森林的结点个数
{
	return num;
}

template <class ElemType>
int ChildParentForest<ElemType>::NodeDegree(int cur) const
// 操作结果：返回结点cur的度
{
	int d = 0;														// 临时变量,用于对孩子个数进行计数
	for (int child = FirstChild(cur); child != -1; child = RightSibling(child))
	{	// 找查cur的孩子
		d++;														// 对孩子个数进行计数
	}
	return d;
}

template <class ElemType>
int ChildParentForest<ElemType>::FirstChild(int cur) const
// 操作结果：如cur无孩子,则返回-1,否则返回森林结点cur的第一个孩子,
{
	if (cur < -1 || cur >= num)	
		return -1;													// 结点cur不存在,返回-1表示无孩子
	
	if (cur == -1)
	{	//  树的根的双亲为-1,将森林中每棵树的根都看成为-1的孩子
		for (int r = 0; r < num; r++)
		{	// 查找第一棵树的根
			if (Parent(r) == -1) return r;							// r为第一棵树的根
		}
	}
	
	if (nodes[cur].childLkList.Empty())
	{	// 无孩子
		return -1;
	}
	else
	{
		int child;
		nodes[cur].childLkList.GetElem(1, child);					// 取出第一个孩子
		return child;
	}
}

template <class ElemType>
int ChildParentForest<ElemType>::RightSibling(int cur) const
// 操作结果：如果结点cur无右兄弟,则返回-1,否则返回cur的右兄弟
{
	if (cur < 0 || cur >= num)						
		return -1;													// 结点cur不存在,返回-1表示无孩子

	if (nodes[cur].parent == -1)
	{	// cur为根,将森林中每棵树的根都看成为-1的孩子
		for (int pos = cur + 1; pos < num; pos++)
		{	// 查找cur的右兄弟
			if (nodes[cur].parent == nodes[pos].parent) return pos;	// pos为cur的右兄弟
		}
		return -1;													// 查找失败,表示无右兄弟
	}
	else
	{
		int pt = nodes[cur].parent;									// cur的双亲 
		for (int pos = 1; pos < nodes[pt].childLkList.Length(); pos++)
		{	// 查找cur在孩子链表中的位置
			int child;
			nodes[pt].childLkList.GetElem(pos, child);				// 取出孩子
			if (cur == child)
			{	// pos为cur在孩子链表中的位置
				int rightSibling;							
				if (nodes[pt].childLkList.GetElem(pos + 1, rightSibling) == ENTRY_FOUND)
				{	// 存在右兄弟
					return rightSibling;							// 反回右兄弟
				}
				else
				{	// 不存在右兄弟
					return -1;										// 表示无右兄弟
				}
			}
		}
		return -1;													// 查找失败,表示无兄弟
	}
}

template <class ElemType>
int ChildParentForest<ElemType>::Parent(int cur) const
// 操作结果：返回森林中结点cur的双亲
{
	if (cur < 0 || cur >= num)						
		return -1;													// 结点cur不存在,返回-1表示无双亲
	return nodes[cur].parent;
}

template <class ElemType>
void ChildParentForest<ElemType>::MoveHelp(int from, int to)
// 操作结果：将结点从from移到to
{
	nodes[to] = nodes[from];										// 将nodes[from]赋值给nodes[to]
	for (int pos = 0; pos < num; pos++)
	{	// 将以from为双亲的结点改为以to为双亲的结点
		if (from == nodes[pos].parent) nodes[pos].parent = to;
	}
	nodes[from].childLkList.Clear();								// 清空from的孩子链表
}

template <class ElemType>
StatusCode ChildParentForest<ElemType>::InsertChild(int cur, int i, const ElemType &e)
// 操作结果：将数据元素插入为cur的第i个孩子,如果插入成功,则返回SUCCESS,否则返回FAIL
{
	if (cur < 0 || cur >= num) return FAIL;
	if (i < 0 || i > NodeDegree(cur) + 1) return FAIL;
	int n, child;													// 临时变量 
	for (n = 1, child = FirstChild(cur); n < i && child != -1; child = RightSibling(child), n++);
		// 查找第i个孩子的位置
	if (child != -1)
	{	// 存在第i个孩子,第i个孩子的位置为插入位置
		for (int pos = num - 1; pos >= child; pos--)
		{	// 从num - 1到child的结点依次后移
			MoveHelp(pos, pos + 1);
		}
		nodes[child].data = e;										// 将结点child的的数据元素值赋为e
		nodes[child].parent = cur;									// 结点child的双亲为cur
		LinkList<int> &cLkList = nodes[cur].childLkList;			// 双亲的孩子链表
		cLkList.Insert(i, child);									// 将child插入在双亲的孩子链表中
	}
	else
	{	// 不存在第i+1个孩子,插在最后
		child = num;												// child为最后位置
		nodes[child].data = e;										// 将结点child的的数据元素值赋为e
		nodes[child].parent = cur;									// 结点child的双亲为cur
		LinkList<int> &cLkList = nodes[cur].childLkList;			// 双亲的孩子链表
		cLkList.Insert(cLkList.Length() + 1, child);				// 将child插入在双亲的孩子链表中
	}


	num++;															// 插入成功,结点数自加1
	return SUCCESS;
}

template <class ElemType>
void ChildParentForest<ElemType>::DeleteHelp(int r)
// 操作结果：删除以r为根的森林
{
	if (r >= 0 || r < num)
	{	// r合法
		for (int child = FirstChild(r); child != -1; child = RightSibling(child))
		{	// 找查r的子森林
			DeleteHelp(child);										// 删除以child根的子森林
		}
		nodes[r].parent = -2;										// 双亲为-2,特表示此结点已被删除
	}
}

template <class ElemType>
StatusCode ChildParentForest<ElemType>::DeleteChild(int cur, int i)
// 操作结果：删除cur的第i个棵子森林,如果删除成功,则返回SUCCESS,否则返回FAIL
{
	if (i < 0 && i > NodeDegree(cur)) return FAIL;					// 操作失败
	int n, child;													// 临时变量 
	for (n = 1, child = FirstChild(cur); n < i && child != -1; child = RightSibling(child), n++);
		// 查找第i个孩子的位置
	
	DeleteHelp(child);												// 删除第i棵子森林
	for (int pos = num - 1; pos >= 0; pos--)
	{	// 清除被删除的结点
		if (Parent(pos) == -2)
		{	// 被删除结点
			for (int i = num - 1; i >= pos + 1; i--)
			{	// 从num - 1到pos + 1的结点依次前移
				MoveHelp(i, i - 1);									// 前移
			}
			nodes[pos].childLkList.Clear();							// 清空孩子链表
			num--;													// 清除被删除结点后,结点个数自减1			
		}
	}
	return SUCCESS;													// 操作成功
}

template <class ElemType>
ChildParentForest<ElemType>::ChildParentForest(const ElemType &e, int size)
// 操作结果：建立以数据元素e为根的树所构成的只有一棵树的森林
{
	maxSize = DEFAULT_SIZE;											// 树结点最大个数
	nodes = new ChildParentTreeNode<ElemType>[maxSize];				// 分配存储空间
	int root = 0;													// 根的位置
	nodes[root].data = e;											// 对数据域进行赋值
	nodes[root].parent = -1;										// 根的双亲为-1
	num = 1;														// 结点个数
}

template <class ElemType>
ChildParentForest<ElemType>::ChildParentForest(const ChildParentForest<ElemType> &copy)
// 操作结果：由已知森林构造新森林——复制构造函数
{
	maxSize = copy.maxSize;											// 最大结点个数
	nodes = new ChildParentTreeNode<ElemType>[maxSize];				// 分配存储空间
	for (int pos = 0; pos < copy.num; pos++)
	{	// 依次对结点数据元素及双亲位置进行赋值
		nodes[pos].data = copy.nodes[pos].data;						// 数据元素值
		nodes[pos].parent = copy.nodes[pos].parent;					// 双亲位置
		nodes[pos].childLkList = copy.nodes[pos].childLkList;		// 孩子链表
	}
	num = copy.num;													// 结点个数
}
  
template <class ElemType>
ChildParentForest<ElemType>::ChildParentForest(ElemType items[], int parents[], int n, int size)
// 操作结果：建立数据元素为items[],对应结点双亲为parents[],结点个数为n的森林
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
	num = n;														// 结点个数
}

template <class ElemType>
ChildParentForest<ElemType> &ChildParentForest<ElemType>::operator=(const ChildParentForest<ElemType> &copy)
// 操作结果：由已知森林copy复制到当前森林--赋值语句重载
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
		num = copy.num;												// 结点个数
	}
	return *this;
}

template <class ElemType>
void DisplayTWithConcaveShapeHelp(const ChildParentForest<ElemType> &f, int r, int level)
// 操作结果：按凹入表示法显示森林，level为层次数，可设根结点的层次数为1
{
	if (r >= 0 && r < f.NodeCount())
	{	// 存在结点r,才显示r的信息
		cout<<endl;													//显示新行	
		for(int i = 0; i< level - 1; i++)
			cout<<" ";												//确保在第level列显示结点
		ElemType e;
		f.GetElem(r, e);											// 取出结点r的元素值
		cout << e;													// 显示结点元素值
		for (int child = f.FirstChild(r); child != -1; child = f.RightSibling(child))
		{	// 依次显示各棵子树
			DisplayTWithConcaveShapeHelp(f, child, level + 1);
		}
	}
}

template <class ElemType>
void DisplayTWithConcaveShape(const ChildParentForest<ElemType> &f)
// 操作结果：按凹入表示法显示森林
{
	for (int cur = 0; cur < f.NodeCount(); cur++)
	{	// 查找森林中各棵树的根结点
		if (f.Parent(cur) == -1)				
		{	// 根结点
			DisplayTWithConcaveShapeHelp(f, cur, 1);
				// 调用辅助函数实现按凹入表示法显示森林的各棵树
			cout << endl;											// 换行
		}
	}
}

#endif
