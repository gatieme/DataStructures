#ifndef __MPOLYNOMIAL_NODE_H__
#define __MPOLYNOMIAL_NODE_H__

#ifndef __MPOLYNOMIAL_NODE_TYPE__
#define __MPOLYNOMIAL_NODE_TYPE__
enum MPolynomialNodeType {HEAD, ATOM, LIST};
#endif

#include "use_space_list.h"					// 广义表使用空间表类

// m元多项式结点类
template<class CoefType>
struct MPolynomialNode
{
// 数据成员:
	MPolynomialNodeType tag;				// 标志域,HEAD(0):头结点, ATOM(1):原子结点, LIST(2):表结点
	MPolynomialNode<CoefType> *nextLink;	// 指向同一层中的下一个结点指针域
	union
	{
		char var;							// tag=HEAD,存放m元多项式的主变量
		struct								// tag=ATOM，原子结点
		{
			CoefType coef;					// 存放系数域
			int exp;						// 存放指数域
		} atom;								// 原子结构
		struct								// tag=LISK, 表结构
		{
			MPolynomialNode<CoefType> *subLink;	// 存放指向子表的指针域
			int exp;						// 存放指数域
		} list;								// 表结点结构 
	}; 

// 构造函数:
	MPolynomialNode(MPolynomialNodeType tg = HEAD, 
		MPolynomialNode<CoefType> *next = NULL);// 由标志tg和指针next构造m元多项式结点
};

// m元多项式结点类的实现部分
template<class CoefType>
MPolynomialNode<CoefType>::MPolynomialNode(MPolynomialNodeType tg, MPolynomialNode<CoefType> *next)
// 操作结果：由标志tg和指针next构造m元多项式结点
{
	tag = tg;								// 标志
	nextLink = next;						// 后继
	gUseSpaceList.Push(this);				// 将指向当前结点的指针加入到广义表使用空间表中
}

#endif
