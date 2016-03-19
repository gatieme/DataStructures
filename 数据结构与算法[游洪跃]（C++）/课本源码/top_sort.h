#ifndef __TOPSORT_H__
#define __TOPSORT_H__

#include "lk_queue.h"
#include "adj_matrix_dir_graph.h"			// 邻接矩阵有向图

template <class ElemType>
void StatIndegree(const AdjMatrixDirGraph<ElemType> &g, int *indegree)
// 操作结果：统计图g各顶点的入度
{
	for (int v = 0; v < g.GetVexNum(); v++)
	{	// 初始化入度为0
		indegree[v] = 0;
	}

	for (int v1 = 0; v1 < g.GetVexNum(); v1++)
	{	// 遍历图的顶点
		for (int v2 = g.FirstAdjVex(v1); v2 != -1; v2 = g.NextAdjVex(v1, v2))
		{	// v2为v1的一个邻接点
			indegree[v2]++;
		}
	}
}

template <class ElemType>
StatusCode TopSort(const AdjMatrixDirGraph<ElemType> &g)
// 初始条件：存在有向图g
// 操作结果：如g无回路,则输出g的顶点的一个拓扑序列,并返回SUCCESS,否则返回FAIL
{
	int *indegree = new int[g.GetVexNum()];	// 顶点入度数组		
	LinkQueue<int> q;					// 队列
	int count = 0;
	StatIndegree(g, indegree);				// 统计顶点的入度

	for (int v = 0; v < g.GetVexNum(); v++)
	{	// 遍历顶点
		if (indegree[v] == 0)
		{	// 建立入度为0的顶点队列
			q.InQueue(v);
		}
	}

	while (!q.Empty())
	{	// 队列非空
		int v1;
		q.OutQueue(v1);		// 取出一个入度为0的顶点
		cout << v1 << "  ";
		count++;			// 对输出顶点进行记数
		for (int v2 = g.FirstAdjVex(v1); v2 != -1; v2 = g.NextAdjVex(v1, v2))
		{	// v2为v1的一个邻接点,对v1的每个邻接点入度减1
			if (--indegree[v2] == 0)
			{	// v2入度为0,将v2入队
				q.InQueue(v2);
			};
		}
	}
	delete []indegree;						// 释放indegree所占用的存储空间

	if (count < g.GetVexNum()) return FAIL;	// 图g有回路
	else return SUCCESS;					// 拓扑排序成功
}

#endif

