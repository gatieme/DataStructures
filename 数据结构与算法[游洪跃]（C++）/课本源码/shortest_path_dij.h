#ifndef __SHORTEST_PATH_DIJ_H__
#define __SHORTEST_PATH_DIJ_H__

#include "adj_matrix_dir_network.h"			// 邻接矩阵有向网

template <class ElemType, class WeightType>
void ShortestPathDIJ(const AdjMatrixDirNetwork<ElemType, WeightType> &net, int v0, 
	int *path, WeightType *dist)
// 操作结果: 用Dijkstra算法求有向网net从顶点v0到其余顶点v的最短路径path和路径长度dist[v],
//	path[v]存储最短路径上至此顶点的前一顶点的顶点号
{
	for (int v = 0; v < net.GetVexNum(); v++)
	{	// 初始化path和dist及顶点标志
		dist[v] = (v0 != v && net.GetWeight(v0, v) == 0 ) ? net.GetInfinity() : net.GetWeight(v0, v);
		if (v0 != v && dist[v] < net.GetInfinity()) path[v] = v0;
		else path[v] = -1;		// 路径存放数组初始化
		net.SetTag(v, UNVISITED);	// 置顶点标志
	}
	net.SetTag(v0, VISITED);		// U={v0}

	for (int u = 1; u < net.GetVexNum(); u++)
	{	// 除v0外的其余net.GetVexNum() - 1个顶点
		WeightType minVal = net.GetInfinity(); int v1 = v0;
		for (int w = 0; w < net.GetVexNum(); w++)
		{	// disk[v1] = min{dist[w] | w ∈V - U
			if (net.GetTag(w) == UNVISITED && dist[w] < minVal)
			{	// net.GetTag(w) == UNVISITED表示w∈V - U
				v1 = w;
				minVal = dist[w];
			}
		}
		net.SetTag(v1, VISITED);		// 将v1并入U

		for (int v2 = net.FirstAdjVex(v1); v2 != -1; v2 = net.NextAdjVex(v1, v2))
		{	// 更新当前最短路径及距离
			if (net.GetTag(v2) == UNVISITED && minVal + net.GetWeight(v1, v2) < dist[v2])
			{	// 如v2∈V - U且minVal + net.GetWeight(v1, v2) < dist[v2],则修改dist[v2]
				// 及path[v2]
				dist[v2] = minVal + net.GetWeight(v1, v2);
				path[v2] = v1;
			}
		}
	}
}

#endif

