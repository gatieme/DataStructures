#ifndef __ADJ_LIST_DIR_GRAPH_H__
#define __ADJ_LIST_DIR_GRAPH_H__

#include "lk_list.h"							// 线性链表类
#include "adj_list_graph_vex_node.h"			// 邻接表有向图顶点结点类

// 有向图的邻接表类
template <class ElemType>
class AdjListDirGraph
{
protected:
// 邻接表的数据成员:
	int vexNum, edgeNum;						// 顶点个数和边数
	AdjListGraphVexNode<ElemType> *vexTable;	// 顶点表
	mutable StatusCode *tag;					// 指向标志数组的指针				

// 辅助函数
	void DestroyHelp();							// 销毁有向图,释放有向图点用的空间
	int IndexHelp(const LinkList<int> *la, int v) const;
		//定位顶点v在邻接链表中的位置

public:
// 抽象数据类型方法声明及重载编译系统默认方法声明:
	AdjListDirGraph(ElemType es[], int vertexNum = DEFAULT_SIZE);
		// 构造顶点数据为es[],顶点个数为vertexNum,边数为0的有向图
	AdjListDirGraph(int vertexNum = DEFAULT_SIZE);
		// 构造顶点个数为vertexNum,边数为0的有向图
	~AdjListDirGraph();							// 析构函数
	StatusCode GetElem(int v, ElemType &e) const;// 求顶点的元素	
	StatusCode SetElem(int v, const ElemType &e);// 设置顶点的元素值
	int GetVexNum() const;						// 返回顶点个数			 
	int GetedgeNum() const;						// 返回边数个数			 
	int FirstAdjVex(int v) const;				// 返回顶点v的第一个邻接点			 
	int NextAdjVex(int v1, int v2) const;		// 返回顶点v1的相对于v2的下一个邻接点			 
	void InsertEdge(int v1, int v2);			// 插入顶点为v1和v2的边			 
	void DeleteEdge(int v1, int v2);			// 删除顶点为v1和v2的边			 
	StatusCode GetTag(int v) const;			// 返回顶点v的标志		 
	void SetTag(int v, StatusCode val) const;	// 设置顶点v的标志为val		 
	AdjListDirGraph(const AdjListDirGraph<ElemType> &copy);	// 复制构造函数
	AdjListDirGraph<ElemType> &operator =(const AdjListDirGraph<ElemType> &copy); 
		// 赋值语句重载
};

template <class ElemType>
void Display(const AdjListDirGraph<ElemType> &g, bool showVexElem);	// 显示邻接矩阵有向图

// 有向图的邻接表类的实现部分
template <class ElemType>
AdjListDirGraph<ElemType>::AdjListDirGraph(ElemType es[], int vertexNum)
// 操作结果：构造顶点数为numVex,顶点数据为es[],种类为kf,顶点个数为vertexNum,边数为0的有向图
{
	if (vertexNum < 0)	throw Error("顶点个数不能为负!");// 抛出异常

	vexNum = vertexNum;							// 顶点数为vertexNum
	edgeNum = 0;								// 边数为0

	tag = new StatusCode[vexNum];				// 生成标志数组
	int curPos;									// 临时变量 
	for (curPos = 0; curPos < vexNum; curPos++)
	{	// 初始化标志数组
		tag[curPos] = UNVISITED;
	}

	vexTable = new AdjListGraphVexNode<ElemType>[vexNum];// 生成邻接表
	for (curPos = 0; curPos < vexNum; curPos++)
	{	// 初始化顶点数据
		vexTable[curPos].data = es[curPos];
	}
}

template <class ElemType>
AdjListDirGraph<ElemType>::AdjListDirGraph(int vertexNum)
// 操作结果：构造顶点数为numVex,种类为kf,顶点个数为vertexNum,边数为0的有向图
{
	if (vertexNum < 0)	throw Error("顶点个数不能为负!");// 抛出异常

	vexNum = vertexNum;							// 顶点数为vertexNum
	edgeNum = 0;								// 边数为0

	tag = new StatusCode[vexNum];				// 生成标志数组
	int curPos;									// 临时变量 
	for (curPos = 0; curPos < vexNum; curPos++)
	{	// 初始化标志数组
		tag[curPos] = UNVISITED;
	}

	vexTable = new AdjListGraphVexNode<ElemType>[vexNum];// 生成邻接表
}

template <class ElemType>
void AdjListDirGraph<ElemType>::DestroyHelp()
// 操作结果：销毁有向图,释放有向图点用的空间
{
	delete []tag;								// 释放标志
	for (int iPos = 0; iPos < vexNum; iPos++)
	{	// 释放链表
		if (vexTable[iPos].adjLink != NULL)
			delete vexTable[iPos].adjLink;
	}
	delete []vexTable;							// 释放邻接表
}

template <class ElemType>
AdjListDirGraph<ElemType>::~AdjListDirGraph()
// 操作结果：释放邻接表有向图所占用空间
{
	DestroyHelp();
}

template <class ElemType>
StatusCode AdjListDirGraph<ElemType>::GetElem(int v, ElemType &e) const
// 操作结果：求顶点v的元素, v的取值范围为0 ≤ v ＜ vexNum, v合法时函数返回
//	SUCCESS, 否则函数返回RANGE_ERROR
{
	if (v < 0 || v >= vexNum)
	{	// v范围错
		return NOT_PRESENT;			// 元素不存在
	}
	else
	{	// v合法
		e = vexTable[v].data;		// 将顶点v的元素值赋给e
		return ENTRY_FOUND;			// 元素存在
	}
}	

template <class ElemType>
StatusCode AdjListDirGraph<ElemType>::SetElem(int v, const ElemType &e)
// 操作结果：设置顶点的元素值v的取值范围为0 ≤ v ＜ vexNum, v合法时函数返回
//	SUCCESS, 否则函数返回RANGE_ERROR
{
	if (v < 0 || v >= vexNum)
	{	// v范围错
		return RANGE_ERROR;			// 位置错
	}
	else
	{	// v合法
		vexTable[v].data = e;		// 顶点元素
		return SUCCESS;				// 成功
	}
}

template <class ElemType>
int AdjListDirGraph<ElemType>::GetVexNum() const
// 操作结果：返回顶点个数			 
{
	return vexNum;
}

template <class ElemType>
int AdjListDirGraph<ElemType>::GetedgeNum() const
// 操作结果：返回边数个数
{
	return edgeNum;
}		 

template <class ElemType>
int AdjListDirGraph<ElemType>::FirstAdjVex(int v) const
// 操作结果：返回顶点v的第一个邻接点			 
{
	if (v < 0 || v >= vexNum) throw Error("v不合法!");// 抛出异常

	if (vexTable[v].adjLink == NULL)
	{	// 空邻接链表，无邻接点
		return -1; 
	}
	else
	{	// 非空邻接链表，存在邻接点
		int adjVex;
		vexTable[v].adjLink->GetElem(1, adjVex);
		return adjVex;
	}
}

template <class ElemType>
int AdjListDirGraph<ElemType>::IndexHelp(const LinkList<int> *la, int v) const
// 操作结果：定位顶点v在邻接链表中的位置
{
	int curPos, adjVex;
	curPos = la->GetCurPosition();

	la->GetElem(curPos, adjVex);					// 取得邻接点信息
	if (adjVex == v) return curPos;					// v为线性链表的当前位置处 
	
	curPos = 1;
	for (curPos = 1; curPos <= la->Length(); curPos++)
	{	// 循环定定
		la->GetElem(curPos, adjVex);				// 取得边信息
		if (adjVex == v) break;						// 定位成功
	}
	
	return curPos;									// curPos = la.Length() + 1 表示定位失败
}

template <class ElemType>
int AdjListDirGraph<ElemType>::NextAdjVex(int v1, int v2) const
// 操作结果：返回顶点v1的相对于v2的下一个邻接点			 
{
	if (v1 < 0 || v1 >= vexNum) throw Error("v1不合法!");	// 抛出异常
	if (v2 < 0 || v2 >= vexNum) throw Error("v2不合法!");	// 抛出异常
	if (v1 == v2) throw Error("v1不能等于v2!");				// 抛出异常
	
	if (vexTable[v1].adjLink == NULL) return -1;			// 邻接链表vexTable[v1].adjList为空,返回-1

	int curPos = IndexHelp(vexTable[v1].adjLink, v2);	// 取出v2在邻接链表中的位置
	if (curPos < vexTable[v1].adjLink->Length())
	{	// 存在下1个邻接点
		int adjVex;
		vexTable[v1].adjLink->GetElem(curPos + 1, adjVex);// 取出后继
		return adjVex;
	}
	else
	{	// 不存在下一个邻接点
		return -1;
	}
}

template <class ElemType>
void AdjListDirGraph<ElemType>::InsertEdge(int v1, int v2)
// 操作结果：插入顶点为v1和v2的边			 
{
	if (v1 < 0 || v1 >= vexNum) throw Error("v1不合法!");	// 抛出异常
	if (v2 < 0 || v2 >= vexNum) throw Error("v2不合法!");	// 抛出异常
	if (v1 == v2) throw Error("v1不能等于v2!");				// 抛出异常

	if (vexTable[v1].adjLink == NULL)
	{	// 空链表
		vexTable[v1].adjLink = new LinkList<int>;
	}

	int curPos = IndexHelp(vexTable[v1].adjLink, v2);		// 取出v2在邻接链表中的位置
	if (curPos > vexTable[v1].adjLink->Length())
	{	// 不存在边<v1, v2>
		vexTable[v1].adjLink->Insert(curPos, v2);			// 插入边<v1, v2>
		edgeNum++;											// 边数自增1
	}
}

template <class ElemType>
void AdjListDirGraph<ElemType>::DeleteEdge(int v1, int v2)
// 操作结果：删除顶点为v1和v2的边			 
{
	if (v1 < 0 || v1 >= vexNum) throw Error("v1不合法!");	// 抛出异常
	if (v2 < 0 || v2 >= vexNum) throw Error("v2不合法!");	// 抛出异常
	if (v1 == v2) throw Error("v1不能等于v2!");				// 抛出异常

	int curPos = IndexHelp(vexTable[v1].adjLink, v2);	// 取出v2在邻接链表中的位置
	if (curPos <= vexTable[v1].adjLink->Length())
	{	// 存在边<v1, v2>
		vexTable[v1].adjLink->Delete(curPos, v2);		// 删除<v1,v2>
 		edgeNum--;										// 边数自减1
	}
}

template <class ElemType>
StatusCode AdjListDirGraph<ElemType>::GetTag(int v) const
// 操作结果：返回顶点v的标志		 
{
	if (v < 0 || v >= vexNum) throw Error("v不合法!");	// 抛出异常

	return tag[v];
}

template <class ElemType>
void AdjListDirGraph<ElemType>::SetTag(int v, StatusCode val) const
// 操作结果：设置顶点v的标志为val		 
{
	if (v < 0 || v >= vexNum) throw Error("v不合法!");		// 抛出异常

	tag[v] = val;
}

template <class ElemType>
AdjListDirGraph<ElemType>::AdjListDirGraph(const AdjListDirGraph<ElemType> &copy)
// 操作结果：由有向图的邻接矩阵copy构造新有向图的邻接矩阵copy——复制构造函数
{
	int curPos;									// 临时变量
	vexNum = copy.vexNum;						// 复制顶点数
	edgeNum = copy.edgeNum;						// 复制边数

	tag = new StatusCode[vexNum];				// 生成标志数组
	for (curPos = 0; curPos < vexNum; curPos++)
	{	// 复制标志数组
		tag[curPos] = copy.tag[curPos];
	}

	vexTable = new AdjListGraphVexNode<ElemType>[vexNum];// 生成邻接表
	for (curPos = 0; curPos < vexNum; curPos++)
	{	// 复制邻接链表
		vexTable[curPos].data = copy.vexTable[curPos].data;	// 复制顶点数据
		vexTable[curPos].adjLink = new LinkList<int>(*copy.vexTable[curPos].adjLink);	
	}
}

template <class ElemType>
AdjListDirGraph<ElemType> &AdjListDirGraph<ElemType>::operator =(const AdjListDirGraph<ElemType> &copy)
// 操作结果：将有向图的邻接矩阵copy赋值给当前有向图的邻接矩阵——赋值语句重载
{
	if (&copy != this)
	{
		DestroyHelp();								// 释放当前有向图占用空间

		int curPos;									// 临时变量
		vexNum = copy.vexNum;						// 复制顶点数
		edgeNum = copy.edgeNum;						// 复制边数

		tag = new StatusCode[vexNum];				// 生成标志数组
		for (curPos = 0; curPos < vexNum; curPos++)
		{	// 复制标志数组
			tag[curPos] = copy.tag[curPos];
		}

		vexTable = new AdjListGraphVexNode<ElemType>[vexNum];// 生成邻接表
		for (curPos = 0; curPos < vexNum; curPos++)
		{	// 复制邻接链表
			vexTable[curPos].data = copy.vexTable[curPos].data;	// 复制顶点数据
			vexTable[curPos].adjLink = new LinkList<int>(*copy.vexTable[curPos].adjLink);	
		}
	}
	return *this;
}

template <class ElemType>
void Display(const AdjListDirGraph<ElemType> &g, bool showVexElem = true)
// 操作结果: 显示邻接矩阵有向图
{
	for (int v = 0; v < g.GetVexNum(); v++)
	{	// 显示第v个邻接链表
		cout << endl << v << "  ";							// 显示顶点号
		if (showVexElem)
		{	// 显示顶点元素
			ElemType e;										// 数据元素
			g.GetElem(v, e);								// 取出元素值
			cout << e << "  ";								// 显示顶点元素
		}

		for (int u = g.FirstAdjVex(v); u != -1; u = g.NextAdjVex(v, u))
		{	// 显示第v个邻接链表的一个结点（表示一个邻接点）
			cout << "-->" << u; 
		}
		cout << endl; 
	}
}

#endif
