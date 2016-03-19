#ifndef __SHORTEST_PATH_FLOYD_H__
#define __SHORTEST_PATH_FLOYD_H__

#include "adj_list_dir_network.h"			// 邻接表有向网

template <class ElemType, class WeightType>
void ShortestPathFloyd(const AdjListDirNetwork<ElemType, WeightType> &net, int **path, 
	WeightType **dist)
// 操作结果: 用Floyd算法求有向网net中各对顶点u和v之间的最短路径path[u][v]和路径长度
//	dist[u][v],path[u][v]存储从u到v的最短路径上至此顶点的前一顶点的顶点号,dist[u][v]
//	存储从u到v的最短路径的长度
{
	for (int u = 0; u < net.GetVexNum(); u++)
		for (int v = 0; v < net.GetVexNum(); v++)
		{	// 初始化path和dist
			dist[u][v] = (u != v) ? net.GetWeight(u, v) : 0;
			if (u != v && dist[u][v] < net.GetInfinity()) path[u][v] = u;	// 存在边<u,v>
			else path[u][v] = -1;											// 不存在边<u,v>
		}

	for (int k = 0; k < net.GetVexNum(); k++)
		for (int i = 0; i < net.GetVexNum(); i++)
			for (int j = 0; j < net.GetVexNum(); j++)
				if (dist[i][k] + dist[k][j] < dist[i][j])
				{	// 从i到k再到j的路径长度更短
					dist[i][j] = dist[i][k] + dist[k][j]; 
					path[i][j] = path[k][j];
				}
}

#endif

