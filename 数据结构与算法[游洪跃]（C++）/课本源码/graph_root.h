// 文件路径名: graph_root\graph_root.h
#ifndef __GRPH_ROOT_H__
#define __GRPH_ROOT_H__

#include "adj_matrix_dir_graph.h"				// 有向图的邻接矩阵类

template <class ElemType>
void GraphRoot(const AdjMatrixDirGraph<ElemType> &g)
// 操作结果: 判断有向图g是否有根，若有，则显示所有根结点的值
{
	bool exitRoot = false;						// 是否存在树

	for (int v = 0; v < g.GetVexNum(); v++)
	{	// 依次判断每个顶点是否为根
		for(int u = 0; u < g.GetVexNum(); u++)
		{	// 设置访问标志
			g.SetTag(u, UNVISITED);
		}
		int count = 0;							// 已访问顶点数
		DFS(g, v, count);						// 用DFS算法从v出发搜索树
		if (count == g.GetVexNum())
		{	//count == g.GetVexNum()表示v为根顶点
			if (!exitRoot)
			{	// 显示存储根顶点
				exitRoot = true;				// 表示存在根顶点
				cout << "存在根顶点:";
			}
			cout << v << "  ";					// 显示根顶点
		}
	}
	cout << endl;								// 换行
	
	if (!exitRoot)
	{	// 显示不存在根顶点
		cout << "存在根顶点." << endl;
	}
}

template <class ElemType>
void DFS(const AdjMatrixDirGraph<ElemType> &g, int v, int &count)
// 操作结果: 从第v个顶点出发递归地深度优先搜索图G
{
	g.SetTag(v, VISITED);						// 作访问标志
	count++;									// 对已访问顶点进行记数
	for (int w = g.FirstAdjVex(v); w != -1; w = g.NextAdjVex(v, w))
	{	// 对v的尚未访问过的邻接顶点w递归调用DFS
		if (g.GetTag(w) == UNVISITED)
		{	// 从w开始进行深度优先搜索
			#ifdef _MSC_VER
				DFS<ElemType>(g, w , count);	// VC需<ElemType>确定函数模板参数
			#else
				DFS(g, w , count);
			#endif
		}
	}
}

#endif

