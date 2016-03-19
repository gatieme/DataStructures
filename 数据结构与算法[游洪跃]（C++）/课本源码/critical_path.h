#ifndef __TOPSORT_H__
#define __TOPSORT_H__

#include "lk_queue.h"						// 队列
#include "lk_stack.h"						// 栈
#include "adj_matrix_dir_network.h"			// 邻接矩阵有向网

template <class ElemType, class WeightType>
void StatIndegree(const AdjMatrixDirNetwork<ElemType, WeightType> &net, int *indegree)
// 操作结果：统计网net各顶点的入度
{
	for (int v = 0; v < net.GetVexNum(); v++)
	{	// 初始化入度为0
		indegree[v] = 0;
	}

	for (int v1 = 0; v1 < net.GetVexNum(); v1++)
	{	// 遍历网的顶点
		for (int v2 = net.FirstAdjVex(v1); v2 != -1; v2 = net.NextAdjVex(v1, v2))
		{	// v2为v1的一个邻接点
			indegree[v2]++;
		}
	}
}

template <class ElemType, class WeightType>
StatusCode CriticalPath(const AdjMatrixDirNetwork<ElemType, WeightType> &net)
// 初始条件：存在有向网net
// 操作结果：如net无回路,则输出net的关键活动,并返回SUCCESS,否则返回FAIL
{
	int *indegree = new int[net.GetVexNum()];	// 顶点入度数组
	int *ve = new int[net.GetVexNum()];			// 事件最早发生时刻数组
	LinkQueue<WeightType> q;					// 用于存储入度为0的顶点
	LinkStack<WeightType> s;					// 用于实现逆扑序序列的栈
	int ee, el, u, v, count = 0;

	for (v = 0; v < net.GetVexNum(); v++) 
	{	// 初始化事件最早发生时刻
		ve[v] = 0;
	}

	StatIndegree(net, indegree);				// 统计顶点的入度

	for (v = 0; v < net.GetVexNum(); v++)
	{	// 遍历顶点
		if (indegree[v] == 0)
		{	// 建立入度为0的顶点队列
			q.InQueue(v);
		}
	}

	while (!q.Empty())
	{	// 队列非空
		q.OutQueue(u);			// 取出一个入度为0的顶点
		s.Push(u);				// 顶点u入栈,以便得逆拓扑排序序列
		count++;				// 对顶点进行记数
		for (v = net.FirstAdjVex(u); v != -1; v = net.NextAdjVex(u, v))
		{	// v2为v1的一个邻接点,对v1的每个邻接点入度减1
			if (--indegree[v] == 0)
			{	// v入度为0,将v入队
				q.InQueue(v);
			};
			if (ve[u] + net.GetWeight(u, v) > ve[v])
			{	// 修改ve[v]
				ve[v] = ve[u] + net.GetWeight(u, v);
			}
		}
	}
	delete []indegree;			// 释放indegree所占用的存储空间

	if (count < net.GetVexNum()) 
	{
		delete []ve;			// 释放ve所占用的存储空间
		return FAIL;			// 网g有回路
	}

	int *vl = new int[net.GetVexNum()];		// 事件最迟发生时刻数组
	s.Top(u);								// 取出栈顶,栈顶为汇点
	for (v = 0; v < net.GetVexNum(); v++) 
	{	// 初始化事件最迟发生时刻
		vl[v] = ve[u];
	}

	while (!s.Empty())
	{	// s非空
		s.Pop(u);
		for (v = net.FirstAdjVex(u); v != -1; v = net.NextAdjVex(u, v))
		{	// v为u的一个邻接点
			if (vl[v] - net.GetWeight(u, v) < vl[u])
			{	// 修改vl[u]
				vl[u] = vl[v] - net.GetWeight(u, v);
			}
		}
	}

	for (u = 0; u < net.GetVexNum(); u++)
	{	// 求ee, el和关键路径
		for (v = net.FirstAdjVex(u); v != -1; v = net.NextAdjVex(u, v))
		{	// v为u的一个邻接点
			ee = ve[u]; el = vl[v] - net.GetWeight(u, v);
			if (ee == el)
			{	// <u, v>为关键活动
				cout << "<" << u << "," << v << "> ";
			}
		}
	}
	
	delete []ve;				// 释放ve所占用的存储空间
	delete []vl;				// 释放vl所占用的存储空间
	return SUCCESS;				// 操作成功
}

#endif

