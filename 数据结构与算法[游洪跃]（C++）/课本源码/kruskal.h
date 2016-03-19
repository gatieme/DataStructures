#ifndef __KRUSKAL_H__
#define __KRUSKAL_H__
#include "adj_list_undir_network.h"		// 邻接表无向网

// Kruskal森林类
class KruskalForest
{
private:
	int *treeNo;		// 顶点所在的树编号
	int vexNum;			// 顶点数
public:
	KruskalForest(int num = DEFAULT_SIZE);	// 构造函数
	~KruskalForest(){ delete []treeNo; };	// 析构函数
	bool IsSameTree(int v1, int v2);		// 判断v1和v2是否在同一棵树上
	void Union(int v1, int v2);				// 将v2所在树的所有顶点合并到v1所在树上
};

// Kruskal森林类实现
KruskalForest::KruskalForest(int num)
// 操作结果：构造顶点数为num的Kruskal森林
{
	vexNum = num;					// 顶点数
	treeNo = new int[vexNum];		// 分配存储空间
	for (int v = 0; v < vexNum; v++)
	{	// 初始时,每棵树只有一个顶点,树的个数与顶点个数相同
		treeNo[v] = v;
	}
}

bool KruskalForest::IsSameTree(int v1, int v2)
// 操作结果：如果v1和v2在同一棵树上,则返回true,否则返回false
{
	return treeNo[v1] == treeNo[v2]; 
}

void KruskalForest::Union(int v1, int v2)
// 操作结果：将v2所在树的所有顶点合并到v1所在树上
{
	int v1TNo = treeNo[v1], v2TNo = treeNo[v2]; 
	for (int v = 0; v < vexNum; v++)
	{	// 查找v2所在树的顶点
		if (treeNo[v] == v2TNo)
		{	// // 将v2所在树上的顶点所在树编号改为v1所在树的编号
			treeNo[v] = v1TNo; 
		}
	}
}

// Kruskal边类
template <class WeightType>
class KruskalEdge
{
public:
	int vertex1, vertex2;			// 边的顶点
	WeightType weight;				// 边的权值
	KruskalEdge(int v1 = -1, int v2 = -1, int w = 0);	// 构造函数
};

template <class WeightType>
KruskalEdge<WeightType>::KruskalEdge(int v1, int v2, int w)
// 操作结果: 由顶点v1、v2和权w构造边——构造函数
{	// 构造函数
	vertex1 = v1;					// 顶点vertex1
	vertex2 = v2;					// 顶点vertex2
	weight = w;						// 权weight
}

template <class WeightType>
void Sort(KruskalEdge<WeightType> *a, int n)
// 操作结果：按权值对边进行升序排序
{
	for (int i = n - 1; i > 0; i--)
		for (int j = 0; j < i; j++)
			if (a[j].weight > a[j + 1].weight)
			{	// 出现逆序,则交换a[j]与a[j + 1] 
				KruskalEdge<WeightType> tmpEdge;	// 临时边
				tmpEdge = a[j]; 
				a[j] = a[j + 1];
				a[j + 1] = tmpEdge;
			}
}

template <class ElemType, class WeightType>
void MiniSpanTreeKruskal(const AdjListUndirNetwork<ElemType, WeightType> &net)
// 初始条件：存在网net
// 操作结果：用Kruskal算法构造网net的最小代价生成树
{
	int count;						// 记数器
	KruskalForest kForest(net.GetVexNum());	// 定义Kruskal森林
	KruskalEdge<WeightType> *kEdge;
	kEdge = new KruskalEdge<WeightType>[net.GetEdgeNum()];	// 定义边数组,只存储v > u的边(v,u)

	count = 0;						// 表示当前已存入kEdge的边数
	for (int v = 0; v < net.GetVexNum(); v++)
	{
		for (int u = net.FirstAdjVex(v); u >= 0; u = net.NextAdjVex(v, u))
		{	// 将边(v, u)存入kEdge中
			if (v > u)
			{	// 只存储v > u的边(v,u)
				KruskalEdge<WeightType> tmpKEdge(v, u, net.GetWeight(v, u));
				kEdge[count++] = tmpKEdge;
			}
		}
	}

	Sort(kEdge, count);				// 对边按权值进行排序

	for (int i = 0; i < count; i++)
	{	// 对kEdgePtr中的边进行搜索
		int v1 = kEdge[i].vertex1, v2 = kEdge[i].vertex2;
		if (!kForest.IsSameTree(v1, v2))
		{	// 边的两端不在同一棵树上,则为最小代价生成树上的边
			cout << "edge:(" << v1 << "," << v2 << ") weight:" 
				<<net.GetWeight(v1, v2)<< endl ; // 输出边及权值
			kForest.Union(v1, v2);		// 将v2所在树的所有顶点合并到v1所在树上
		}
	}
	delete []kEdge;					// 释放存储空间
}

#endif

