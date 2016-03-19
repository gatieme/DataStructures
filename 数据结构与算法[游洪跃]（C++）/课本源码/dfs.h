#ifndef __DFS_H__
#define __DFS_H__

#include "adj_matrix_dir_graph.h"	// 邻接矩阵有向图

template <class ElemType>
void DFSTraverse(const AdjMatrixDirGraph<ElemType> &g, void (*Visit)(const ElemType &))
// 初始条件：存在图g
// 操作结果：对图g进行深度优先遍历
{
	int v;
	for (v = 0; v < g.GetVexNum(); v++)
	{	// 对每个顶点作访问标志
		g.SetTag(v, UNVISITED);
	}

	for (v = 0; v < g.GetVexNum(); v++)
	{	// 对尚未访问的顶点按DFS进行深度优先搜索
		if (g.GetTag(v) == UNVISITED)
		{	// 从v开始进行深度优先搜索   
			#ifdef _MSC_VER
				DFS<ElemType>(g, v , Visit);	// VC需<ElemType>确定函数模板参数
			#else
				DFS(g, v , Visit);
			#endif
		}
	}
}

template <class ElemType>
void DFS(const AdjMatrixDirGraph<ElemType> &g, int v, void (*Visit)(const ElemType &))
// 初始条件：存在图g
// 操作结果：从顶点v出发进行深度优先搜索图g
{	
	g.SetTag(v, VISITED);			// 作访问标志
	ElemType e;						// 临时变量
	g.GetElem(v, e);				// 顶点v的数据元素
	Visit(e);						// 访问顶点v的数据元素
	for (int w = g.FirstAdjVex(v); w != -1; w = g.NextAdjVex(v, w))
	{	// 对v的尚未访问过的邻接顶点w递归调用DFS
		if (g.GetTag(w) == UNVISITED)
		{	// 从w开始进行深度优先搜索
			#ifdef _MSC_VER
				DFS<ElemType>(g, w , Visit);	// VC需<ElemType>确定函数模板参数
			#else
				DFS(g, w , Visit);
			#endif
		}
	}
}

#endif
