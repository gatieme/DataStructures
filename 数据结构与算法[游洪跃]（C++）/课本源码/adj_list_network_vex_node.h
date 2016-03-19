#ifndef __ADJ_LIST_NETWORK_VEX_NODE_H__
#define __ADJ_LIST_NETWORK_VEX_NODE_H__

#include "adj_list_network_edge.h"			// 邻接表网边数据类

// 邻接表网顶点结点类
template <class ElemType, class WeightType>
class AdjListNetWorkVexNode
{
public:
// 数据成员:
	ElemType data;							// 数据元素值
	LinkList<AdjListNetworkEdge<WeightType> > *adjLink;
		// 指向邻接链表的指针

// 构造函数:
	AdjListNetWorkVexNode();				// 无参数的构造函数
	AdjListNetWorkVexNode(ElemType item, 
		LinkList<AdjListNetworkEdge<WeightType> > *adj = NULL);
		// 构造顶点数据为item,指向邻接链表的指针为adj的结构
};

// 邻接表网顶点结点类的实现部分
template <class ElemType, class WeightType>
AdjListNetWorkVexNode<ElemType, WeightType>::AdjListNetWorkVexNode()
// 操作结果：构造一个空顶点结点——无参构造函数
{
	adjLink = NULL;							// 指向邻接链表的指针为空
}

template <class ElemType, class WeightType>
AdjListNetWorkVexNode<ElemType, WeightType>::AdjListNetWorkVexNode(ElemType item, 
	LinkList<AdjListNetworkEdge<WeightType> > *adj)
// 操作结果：构造数据为item,边为eg的顶点
{
	data = item;							// 顶点数据
	adjLink = adj;							// 指向邻接链表的指针
}

#endif