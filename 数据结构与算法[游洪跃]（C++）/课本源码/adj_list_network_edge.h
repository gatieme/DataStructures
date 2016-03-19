#ifndef __ADJ_LIST_NETWORK_EDGE_H__
#define __ADJ_LIST_NETWORK_EDGE_H__

// 邻接表网边数据类
template <class WeightType>
class AdjListNetworkEdge
{
public:
// 数据成员:
	int adjVex;								// 邻接点
	WeightType weight;						// 权值

// 构造函数:
	AdjListNetworkEdge();						// 无参数的构造函数
	AdjListNetworkEdge(int v, WeightType w);	// 构造邻接点为v，权为w的邻接边
};

// 邻接表网边数据类的实现部分
template <class WeightType>
AdjListNetworkEdge<WeightType>::AdjListNetworkEdge()
// 操作结果：构造一个空邻接表边结点边——无参构造函数
{
	adjVex = -1;
}

template <class WeightType>
AdjListNetworkEdge<WeightType>::AdjListNetworkEdge(int v, WeightType w)
// 操作结果：构造邻接点为v，权为w的邻接边
{
	adjVex = v;								// 邻接点
	weight = w;								// 权
}

#endif