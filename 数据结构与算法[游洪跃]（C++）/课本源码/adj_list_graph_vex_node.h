#ifndef __ADJ_LIST_NETWORK_VEX_NODE_H__
#define __ADJ_LIST_NETWORK_VEX_NODE_H__

// 邻接表图顶点结点类
template <class ElemType>
class AdjListGraphVexNode
{
public:
// 数据成员:
	ElemType data;							// 数据元素值
	LinkList<int> *adjLink;					// 邻接链表

// 构造函数:
	AdjListGraphVexNode();					// 无参数的构造函数
	AdjListGraphVexNode(ElemType item, LinkList<int> *adj = NULL);
		// 构造顶点数据为item,指向邻接链表的指针为adj的结构
};

// 邻接表图顶点结点类的实现部分
template <class ElemType>
AdjListGraphVexNode<ElemType>::AdjListGraphVexNode()
// 操作结果：构造一个空顶点结点——无参构造函数
{
	adjLink = NULL;							// 邻接链表为空
}

template <class ElemType>
AdjListGraphVexNode<ElemType>::AdjListGraphVexNode(ElemType item, LinkList<int> *adj)
// 操作结果：构造数据为item,指向邻接链表为adj的顶点
{
	data = item;							// 顶点数据
	adjLink = adj;							// 邻接链表
}

#endif