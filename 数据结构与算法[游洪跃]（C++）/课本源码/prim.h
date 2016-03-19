#ifndef __PRIM_H__
#define __PRIM_H__

template <class ElemType, class WeightType>
int MinVertex(const AdjMatrixUndirNetwork<ElemType, WeightType> &net, int *adjVex)	
// 操作结果：返回w，使得边<w, adjVex[w]>为连接V-U到U的具有最小权值的边
{
	int w = -1;				// 初始化最小顶点
	int v;					// 临时顶点
	for (v = 0; v < net.GetVexNum(); v++)	
	{	// 查找第一个满足条件的V - U中顶点v
		if (net.GetTag(v) == UNVISITED				// 表示v为V - U中的顶点
			&& net.GetWeight(v, adjVex[v]) > 0)		// 存在从v到U的边(v, adjVex[v])
		{	 
			w = v;
			break;
		}
	}
    for (v++; v < net.GetVexNum(); v++)	// 查找连接V-U到U的具有最小权值的边<w, adjVex[w]>
		if (net.GetTag(v) == UNVISITED && net.GetWeight(v, adjVex[v]) >0 &&
			net.GetWeight(v, adjVex[v]) < net.GetWeight(w, adjVex[w]))
			w = v;
	return w;
}

template <class ElemType, class WeightType>
void MiniSpanTreePrim(const AdjMatrixUndirNetwork<ElemType, WeightType> &net, int u0)
// 初始条件：存在网net,u0为g的一个顶点
// 操作结果：用Prim算法从u0出发构造网g的最小代价生成树
{
	if (u0 < 0 || u0 >= net.GetVexNum())	throw Error("u0不合法1!");// 抛出异常

	int *adjVex;						// 如果v∈V-U,net.GetWeight(v, adjVex[v])>0
										// 表示(v, adjVex[v])是v到U具有最小权值边的邻接点
	int u, v, w;						// 表示顶点的临时变量 
	adjVex = new int[net.GetVexNum()];	// 分配存储空间
	for (v = 0; v < net.GetVexNum(); v++)
	{	// 初始化辅助数组adjVex，并对顶点作标志，此时U = {v0}
		if (v != u0)
		{	// 对于v∈V-U
			adjVex[v] = u0;
			net.SetTag(v, UNVISITED);
		}
		else
		{	// 对于v∈U
			net.SetTag(v, VISITED);
			adjVex[v] = u0;
		}
	}
	for (u = 1; u < net.GetVexNum(); u++)
	{	// 选择生成树的其余net.GetVexNum() - 1个顶点
		w = MinVertex(net, adjVex);	
			// 选择使得边<w, adjVex[w]>为连接V-U到U的具有最小权值的边
		if (w == -1)
		{	// 表示U与V-U已无边相连
			return;
		}
		cout << "edge:(" << adjVex[w] << "," <<  w << ") weight:" 
			<<net.GetWeight(w, adjVex[w])<< endl ; // 输出边及权值
		net.SetTag(w, VISITED);		// 将w并入U
		for (int v = net.FirstAdjVex(w); v >= 0 ; v = net.NextAdjVex(w, v))
		{	// 新顶点并入U后重新选择最小边
			if (net.GetTag(v) == UNVISITED &&		// v ∈V - U
				(net.GetWeight(v, w) < net.GetWeight(v, adjVex[v]) || // 边<v,w>的权值更小
				net.GetWeight(v, adjVex[v]) == 0) ) // 不存在边<v, adjVex[v]>
			{	// <v, w>为新的最小边
				adjVex[v] = w;
			}
		}
	}
	delete []adjVex;			// 释放存储空间
}

#endif

