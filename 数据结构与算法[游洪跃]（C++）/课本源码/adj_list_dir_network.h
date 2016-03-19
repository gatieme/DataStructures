#ifndef __ADJ_LIST_GRAPH_H__
#define __ADJ_LIST_GRAPH_H__

#include "lk_list.h"							// 线性链表类
#include "adj_list_network_edge.h"				// 邻接表有向网边数据类
#include "adj_list_network_vex_node.h"			// 邻接表有向网顶点结点类

// 有向网的邻接表类
template <class ElemType, class WeightType>
class AdjListDirNetwork
{
protected:
// 邻接表的数据成员:
	int vexNum, edgeNum;						// 顶点个数和边数
	AdjListNetWorkVexNode<ElemType, WeightType> *vexTable;	// 顶点表
	mutable StatusCode *tag;					// 指向标志数组的指针				
	WeightType infinity;							// 无穷大

// 辅助函数
	void DestroyHelp();							// 销毁有向网,释放有向网点用的空间
	int IndexHelp(const LinkList<AdjListNetworkEdge<WeightType> > *la, int v) const;
		//定位顶点v在邻接链表中的位置

public:
// 抽象数据类型方法声明及重载编译系统默认方法声明:
	AdjListDirNetwork(ElemType es[], int vertexNum = DEFAULT_SIZE, 
		WeightType infinit = (WeightType)DEFAULT_INFINITY);
		// 构造顶点数据为es[],顶点个数为vertexNum,infinit表示无穷大,边数为0的有向网
	AdjListDirNetwork(int vertexNum = DEFAULT_SIZE, 
		WeightType infinit = (WeightType)DEFAULT_INFINITY);
		// 构造顶点个数为vertexNum,infinit表示无穷大,边数为0的有向网
	~AdjListDirNetwork();						// 析构函数
	StatusCode GetElem(int v, ElemType &e) const;// 求顶点的元素	
	StatusCode SetElem(int v, const ElemType &e);// 设置顶点的元素值
	WeightType GetInfinity() const;				// 返回无穷大			 
	int GetVexNum() const;						// 返回顶点个数			 
	int GetEdgeNum() const;						// 返回边数个数			 
	int FirstAdjVex(int v) const;				// 返回顶点v的第一个邻接点			 
	int NextAdjVex(int v1, int v2) const;		// 返回顶点v1的相对于v2的下一个邻接点			 
	void InsertEdge(int v1, int v2, WeightType w);	// 插入顶点为v1和v2,权为w的边			 
	void DeleteEdge(int v1, int v2);			// 删除顶点为v1和v2的边			 
	WeightType GetWeight(int v1, int v2) const;	// 返回顶点为v1和v2的边的权值
	void SetWeight(int v1, int v2, WeightType w);// 设置顶点为v1和v2的边的权值
	StatusCode GetTag(int v) const;				// 返回顶点v的标志		 
	void SetTag(int v, StatusCode val) const;	// 设置顶点v的标志为val		 
	AdjListDirNetwork(const AdjListDirNetwork<ElemType, WeightType> &copy);	// 复制构造函数
	AdjListDirNetwork<ElemType, WeightType> &operator =
		(const AdjListDirNetwork<ElemType, WeightType> &copy); // 赋值语句重载
};

template <class ElemType, class WeightType>
void Display(const AdjListDirNetwork<ElemType, WeightType> &net, bool showVexElem);	// 显示邻接矩阵有向网

// 有向网的邻接表类的实现部分
template <class ElemType, class WeightType>
AdjListDirNetwork<ElemType, WeightType>::AdjListDirNetwork(ElemType es[], int vertexNum, WeightType infinit)
// 操作结果：构造顶点数为numVex,顶点数据为es[],顶点个数为vertexNum,infinit表示无穷大,边数为0的有向网
{
	if (vertexNum < 0)	throw Error("顶点个数不能为负!");// 抛出异常

	infinity = infinit;							// 无穷大
	vexNum = vertexNum;							// 顶点数为vertexNum
	edgeNum = 0;								// 边数为0

	tag = new StatusCode[vexNum];				// 生成标志数组
	int curPos;									// 临时变量 
	for (curPos = 0; curPos < vexNum; curPos++)
	{	// 初始化标志数组
		tag[curPos] = UNVISITED;
	}

	vexTable = new AdjListNetWorkVexNode<ElemType, WeightType>[vexNum];// 生成邻接表
	for (curPos = 0; curPos < vexNum; curPos++)
	{	// 初始化顶点数据
		vexTable[curPos].data = es[curPos];
	}
}

template <class ElemType, class WeightType>
AdjListDirNetwork<ElemType, WeightType>::AdjListDirNetwork(int vertexNum, WeightType infinit)
// 操作结果：构造顶点数为numVex,顶点个数为vertexNum,infinit表示无穷大,边数为0的有向网
{
	if (vertexNum < 0)	throw Error("顶点个数不能为负!");// 抛出异常

	infinity = infinit;							// 无穷大
	vexNum = vertexNum;							// 顶点数为vertexNum
	edgeNum = 0;								// 边数为0

	tag = new StatusCode[vexNum];				// 生成标志数组
	int curPos;									// 临时变量 
	for (curPos = 0; curPos < vexNum; curPos++)
	{	// 初始化标志数组
		tag[curPos] = UNVISITED;
	}

	vexTable = new AdjListNetWorkVexNode<ElemType, WeightType>[vexNum];// 生成邻接表
}

template <class ElemType, class WeightType>
void AdjListDirNetwork<ElemType, WeightType>::DestroyHelp()
// 操作结果：销毁有向网,释放有向网点用的空间
{
	delete []tag;								// 释放标志
	for (int iPos = 0; iPos < vexNum; iPos++)
	{	// 释放链表
		if (vexTable[iPos].adjLink != NULL)
			delete vexTable[iPos].adjLink;
	}
	delete []vexTable;							// 释放邻接表
}

template <class ElemType, class WeightType>
AdjListDirNetwork<ElemType, WeightType>::~AdjListDirNetwork()
// 操作结果：释放邻接表有向网所占用空间
{
	DestroyHelp();
}

template <class ElemType, class WeightType>
StatusCode AdjListDirNetwork<ElemType, WeightType>::GetElem(int v, ElemType &e) const
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

template <class ElemType, class WeightType>
StatusCode AdjListDirNetwork<ElemType, WeightType>::SetElem(int v, const ElemType &e)
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

template <class ElemType, class WeightType>
WeightType AdjListDirNetwork<ElemType, WeightType>::GetInfinity() const
// 操作结果：返回无穷大
{
	return infinity;
}

template <class ElemType, class WeightType>
int AdjListDirNetwork<ElemType, WeightType>::GetVexNum() const
// 操作结果：返回顶点个数			 
{
	return vexNum;
}

template <class ElemType, class WeightType>
int AdjListDirNetwork<ElemType, WeightType>::GetEdgeNum() const
// 操作结果：返回边数个数
{
	return edgeNum;
}		 

template <class ElemType, class WeightType>
int AdjListDirNetwork<ElemType, WeightType>::FirstAdjVex(int v) const
// 操作结果：返回顶点v的第一个邻接点			 
{
	if (v < 0 || v >= vexNum) throw Error("v不合法!");// 抛出异常

	if (vexTable[v].adjLink == NULL)
	{	// 空邻接链表，无邻接点
		return -1; 
	}
	else
	{	// 空邻接链表，存在邻接点
		AdjListNetworkEdge<WeightType> tmpEdgeNode;
		vexTable[v].adjLink->GetElem(1, tmpEdgeNode);
		return tmpEdgeNode.adjVex;
	}
}

template <class ElemType, class WeightType>
int AdjListDirNetwork<ElemType, WeightType>::IndexHelp(const LinkList<AdjListNetworkEdge<WeightType> > *la, int v) const
// 操作结果：定位顶点v在邻接链表中的位置
{
	AdjListNetworkEdge<WeightType> tmpEdgeNode;
	int curPos; 
	curPos = la->GetCurPosition();

	la->GetElem(curPos, tmpEdgeNode);				// 取邻接点信息
	if (tmpEdgeNode.adjVex == v) return curPos;		// v为线性链表的当前位置处 
	
	curPos = 1;
	for (curPos = 1; curPos <= la->Length(); curPos++)
	{	// 循环定定
		la->GetElem(curPos, tmpEdgeNode);			// 取得边信息
		if (tmpEdgeNode.adjVex == v) break;			// 定位成功
	}
	
	return curPos;									// curPos = la.Length() + 1 表定失败
}

template <class ElemType, class WeightType>
int AdjListDirNetwork<ElemType, WeightType>::NextAdjVex(int v1, int v2) const
// 操作结果：返回顶点v1的相对于v2的下一个邻接点			 
{
	if (v1 < 0 || v1 >= vexNum) throw Error("v1不合法!");	// 抛出异常
	if (v2 < 0 || v2 >= vexNum) throw Error("v2不合法!");	// 抛出异常
	if (v1 == v2) throw Error("v1不能等于v2!");				// 抛出异常
	
	if (vexTable[v1].adjLink == NULL) return -1;				// 邻接链表vexTable[v1].adjLink,不存在,返回-1

	AdjListNetworkEdge<WeightType> tmpEdgeNode;
	int curPos = IndexHelp(vexTable[v1].adjLink, v2);	// 取出v2在邻接链表中的位置
	if (curPos < vexTable[v1].adjLink->Length())
	{	// 存在下1个邻接点
		vexTable[v1].adjLink->GetElem(curPos + 1, tmpEdgeNode);// 取出后继
		return tmpEdgeNode.adjVex;
	}
	else
	{	// 不存在下一个邻接点
		return -1;
	}
}

template <class ElemType, class WeightType>
void AdjListDirNetwork<ElemType, WeightType>::InsertEdge(int v1, int v2, WeightType w)
// 操作结果：插入顶点为v1和v2,权为w的边			 
{
	if (v1 < 0 || v1 >= vexNum) throw Error("v1不合法!");	// 抛出异常
	if (v2 < 0 || v2 >= vexNum) throw Error("v2不合法!");	// 抛出异常
	if (v1 == v2) throw Error("v1不能等于v2!");				// 抛出异常
	if (w == infinity) throw Error("w不能为无空大!");		// 抛出异常

	AdjListNetworkEdge<WeightType> tmpEdgeNode;
	if (vexTable[v1].adjLink == NULL)
	{	// 空链表
		vexTable[v1].adjLink = new LinkList<AdjListNetworkEdge<WeightType> >;
	}

	int curPos = IndexHelp(vexTable[v1].adjLink, v2);		// 取出v2在邻接链表中的位置
	if (curPos <= vexTable[v1].adjLink->Length())
	{	// 存在边<v1, v2>
		vexTable[v1].adjLink->GetElem(curPos, tmpEdgeNode);	// 取出边
		tmpEdgeNode.weight = w;								// 设设置权值
		vexTable[v1].adjLink->SetElem(curPos, tmpEdgeNode);	// 设置边
	}
	else
	{	// 不存在边<v1, v2>
		tmpEdgeNode.adjVex = v2; tmpEdgeNode.weight = w;	// 定义边
		vexTable[v1].adjLink->Insert(curPos, tmpEdgeNode);		// 插入边<v1, v2>
		edgeNum++;											// 边数自增1
	}
}

template <class ElemType, class WeightType>
void AdjListDirNetwork<ElemType, WeightType>::DeleteEdge(int v1, int v2)
// 操作结果：删除顶点为v1和v2的边			 
{
	if (v1 < 0 || v1 >= vexNum) throw Error("v1不合法!");	// 抛出异常
	if (v2 < 0 || v2 >= vexNum) throw Error("v2不合法!");	// 抛出异常
	if (v1 == v2) throw Error("v1不能等于v2!");				// 抛出异常

	AdjListNetworkEdge<WeightType> tmpEdgeNode;
	
	int curPos = IndexHelp(vexTable[v1].adjLink, v2);	// 取出v2在邻接链表中的位置
	if (curPos <= vexTable[v1].adjLink->Length())
	{	// 存在边<v1, v2>
		vexTable[v1].adjLink->Delete(curPos, tmpEdgeNode);	// 删除边<v1, v2>
 		edgeNum--;									// 边数自减1
	}
}

template <class ElemType, class WeightType>
WeightType AdjListDirNetwork<ElemType, WeightType>::GetWeight(int v1, int v2) const
// 操作结果：返回顶点为v1和v2的边的权值
{
	if (v1 < 0 || v1 >= vexNum) throw Error("v1不合法!");	// 抛出异常
	if (v2 < 0 || v2 >= vexNum) throw Error("v2不合法!");	// 抛出异常

	AdjListNetworkEdge<WeightType> tmpEdgeNode;
	int curPos = IndexHelp(vexTable[v1].adjLink, v2);			// 取出v2在邻接链表中的位置
	if (curPos <= vexTable[v1].adjLink->Length())
	{	// 存在边<v1, v2>
		vexTable[v1].adjLink->GetElem(curPos, tmpEdgeNode);		// 取出边
		return tmpEdgeNode.weight;							// 返回权值
	}
	else
	{	// 不存在边<v1, v2>
		return infinity;									// 权值为infinity表示边不存在
	}
}

template <class ElemType, class WeightType>
void AdjListDirNetwork<ElemType, WeightType>::SetWeight(int v1, int v2, WeightType w)
// 操作结果：设置顶点为v1和v2的边的权值
{
	if (v1 < 0 || v1 >= vexNum) throw Error("v1不合法!");	// 抛出异常
	if (v2 < 0 || v2 >= vexNum) throw Error("v2不合法!");	// 抛出异常
	if (v1 == v2) throw Error("v1不能等于v2!");				// 抛出异常
	if (w == infinity) throw Error("w不能为无空大!");		// 抛出异常

	AdjListNetworkEdge<WeightType> tmpEdgeNode;
	
	int curPos = IndexHelp(vexTable[v1].adjLink, v2);			// 取出v2在邻接链表中的位置
	if (curPos <= vexTable[v1].adjLink->Length())
	{	// 存在边<v1, v2>
		vexTable[v1].adjLink->GetElem(curPos, tmpEdgeNode);		// 取出边
		tmpEdgeNode.weight = w;								// 修改权值
		vexTable[v1].adjLink->SetElem(curPos, tmpEdgeNode);		// 设置边
	}
}

template <class ElemType, class WeightType>
StatusCode AdjListDirNetwork<ElemType, WeightType>::GetTag(int v) const
// 操作结果：返回顶点v的标志		 
{
	if (v < 0 || v >= vexNum) throw Error("v不合法!");		// 抛出异常

	return tag[v];
}

template <class ElemType, class WeightType>
void AdjListDirNetwork<ElemType, WeightType>::SetTag(int v, StatusCode val) const
// 操作结果：设置顶点v的标志为val		 
{
	if (v < 0 || v >= vexNum) throw Error("v不合法!");		// 抛出异常

	tag[v] = val;
}

template <class ElemType, class WeightType>
AdjListDirNetwork<ElemType, WeightType>::AdjListDirNetwork(const AdjListDirNetwork<ElemType, WeightType> &copy)
// 操作结果：由有向网的邻接矩阵copy构造新有向网的邻接矩阵copy——复制构造函数
{
	int curPos;									// 临时变量
	infinity =copy.infinity;					// 复制无穷大
	vexNum = copy.vexNum;						// 复制顶点数
	edgeNum = copy.edgeNum;						// 复制边数

	tag = new StatusCode[vexNum];				// 生成标志数组
	for (curPos = 0; curPos < vexNum; curPos++)
	{	// 复制标志数组
		tag[curPos] = copy.tag[curPos];
	}

	vexTable = new AdjListNetWorkVexNode<ElemType, WeightType>[vexNum];// 生成邻接表
	for (curPos = 0; curPos < vexNum; curPos++)
	{	// 复制邻接链表
		vexTable[curPos].data = copy.vexTable[curPos].data;	// 复制顶点数据
		vexTable[curPos].adjLink = new LinkList<AdjListNetworkEdge<WeightType> >(*copy.vexTable[curPos].adjLink);	
	}
}

template <class ElemType, class WeightType>
AdjListDirNetwork<ElemType, WeightType> &AdjListDirNetwork<ElemType, WeightType>::operator =(const AdjListDirNetwork<ElemType, WeightType> &copy)
// 操作结果：将有向网的邻接矩阵copy赋值给当前有向网的邻接矩阵——赋值语句重载
{
	if (&copy != this)
	{
		DestroyHelp();								// 释放当前有向网占用空间

		int curPos;									// 临时变量
		infinity =copy.infinity;					// 复制无穷大
		vexNum = copy.vexNum;						// 复制顶点数
		edgeNum = copy.edgeNum;						// 复制边数

		tag = new StatusCode[vexNum];				// 生成标志数组
		for (curPos = 0; curPos < vexNum; curPos++)
		{	// 复制标志数组
			tag[curPos] = copy.tag[curPos];
		}

		vexTable = new AdjListNetWorkVexNode<ElemType, WeightType>[vexNum];// 生成邻接表
		for (curPos = 0; curPos < vexNum; curPos++)
		{	// 复制邻接链表
			vexTable[curPos].data = copy.vexTable[curPos].data;	// 复制顶点数据
			vexTable[curPos].adjLink = new LinkList<AdjListNetworkEdge<WeightType> >(*copy.vexTable[curPos].adjLink);	
		}
	}
	return *this;
}

template <class ElemType, class WeightType>
void Display(const AdjListDirNetwork<ElemType, WeightType> &net, bool showVexElem = true)
// 操作结果: 显示邻接矩阵有向网
{
	for (int v = 0; v < net.GetVexNum(); v++)
	{	// 显示第v个邻接链表
		cout << endl << v << "  ";							// 显示顶点号
		if (showVexElem)
		{	// 显示顶点元素
			ElemType e;										// 数据元素
			net.GetElem(v, e);								// 取出元素值
			cout << e << "  ";								// 显示顶点元素
		}

		for (int u = net.FirstAdjVex(v); u != -1; u = net.NextAdjVex(v, u))
		{	// 显示第v个邻接链表的一个结点（表示一个邻接点）
			cout << "-->(" << u << "," << net.GetWeight(v, u) << ")"; 
		}
		cout << endl; 
	}
}

#endif
