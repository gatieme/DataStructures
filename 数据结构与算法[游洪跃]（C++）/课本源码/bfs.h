#ifndef __BFS_H__
#define __BFS_H__

#include "adj_list_dir_graph.h"	// 邻接表有向图
#include "lk_queue.h"			// 链队列

template <class ElemType>
void BFSTraverse(const AdjListDirGraph<ElemType> &g, void (*Visit)(const ElemType &))
// 初始条件：存在图g
// 操作结果：对图g进行广度优先遍历
{
	int v;
	for (v = 0; v < g.GetVexNum(); v++)
	{	// 对每个顶点作访问标志
		g.SetTag(v, UNVISITED);
	}

	for (v = 0; v < g.GetVexNum(); v++)
	{	// 对尚未访问的顶点按BFS进行深度优先搜索
		if (g.GetTag(v) == UNVISITED) 
		{
			#ifdef _MSC_VER
				BFS<ElemType>(g, v , Visit);	// VC需<ElemType>确定函数模板参数
			#else
				BFS(g, v , Visit);
			#endif
		}
	}
}

template <class ElemType>
void BFS(const AdjListDirGraph<ElemType> &g, int v, void (*Visit)(const ElemType &))
// 初始条件：存在图g
// 操作结果：从第顶点v出发进行广度优先搜索图g
{	
	g.SetTag(v, VISITED);						// 作访问标志
	ElemType e;									// 临时变量
	g.GetElem(v, e);							// 顶点v的数据元素
	Visit(e);									// 记问顶点v的数据元素
	LinkQueue<int> q;							// 定义队列
	q.InQueue(v);								// v入队
	while (!q.Empty())
	{	// 队列q非空, 进行循环
		int u, w;								// 临时顶点
		q.OutQueue(u);							// 出队
		for (w = g.FirstAdjVex(v); w >= 0; w = g.NextAdjVex(v, w))
		{	// 对u尚未访问过的邻接顶点w进行访问
			if (g.GetTag(w) == UNVISITED)
			{	// 对w进行访问
				g.SetTag(w, VISITED);			// 作访问标志
 				g.GetElem(w, e);				// 顶点w的数据元素
				Visit(e);						// 记问顶点w的数据元素
				q.InQueue(w);					// w入队
			}
		}
	}
}

#endif
