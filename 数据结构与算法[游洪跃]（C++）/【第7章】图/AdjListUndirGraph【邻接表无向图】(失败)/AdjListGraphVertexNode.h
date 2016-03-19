/**
******************************************************************************
*  CopyRight  : 2012-2013, HerBinUnversity, GatieMe                          *
*  File Name  : main.cpp                                                     *
*  Description: 邻接表无向图类AdjListUndirGraph声明头文件                               *
*  Author     : Gatie_Me                                                     *
*  Version    : Copyright 2012 JULY_CITY                                     *
*  Data_Time  : 2012-11-6_10:21:43                                           *
*  Content    : 数据结构与算法（C++）版书上源码                             *
******************************************************************************
**/

#ifndef ADJLISTGRAPHVERTEXNODE_H_INCLUDED
#define ADJLISTGRAPHVERTEXNODE_H_INCLUDED

#include "LinkList.h"

template <class ElemType>
class AdjListGraphVertexNode
{
/*===========================【PUBLIC：公共接口】============================*/
public :      // 公共接口
    // 邻接表无向图结点类AdjListGraphVertexNode数据成员
    ElemType m_data;                // 数据元素值
    LinkList<int> *m_adjLink;         // 邻接链表


    // 邻接表无向图结点类AdjListGraphVertexNode基本成员函数
    AdjListGraphVertexNode( );          // 默认构造函数模版

    AdjListGraphVertexNode(ElemType elem, LinkList<int> *adjLink = NULL);// 构造顶点为elem, 指向邻接表的指针为adjLink的结点

    AdjListGraphVertexNode(const AdjListGraphVertexNode<ElemType> &copy);   // 复制构造函数

    AdjListGraphVertexNode& operator=(const AdjListGraphVertexNode<ElemType> &copy);   // 赋值运算符重载函数


/*===========================【PUBLIC：公共接口】============================*/
};


/**邻接表无向图结点类AdjListGraphVertexNode基本成员函数************************************
    AdjListGraphVertexNode( );          // 默认构造函数模版
    AdjListGraphVertexNode(ElemType elem, LinkList<int> *adjLink = NULL);// 构造顶点为elem, 指向邻接表的指针为adjLink的结点
************************************邻接表无向图结点类AdjListGraphVertexNode基本成员函数**/
// 函数名称：AdjListGraphVertexNode( );
// 操作如果：默认构造函数模版
template <class ElemType>
AdjListGraphVertexNode<ElemType>::AdjListGraphVertexNode( )          // 默认构造函数模版
{
    this->m_adjLink = NULL;
}

// 函数名称：AdjListGraphVertexNode(ElemType elem, LinkList<int> *adjLink = NULL);
// 操作结果：构造顶点为elem, 指向邻接表的指针为adjLink的结点
template <class ElemType>
AdjListGraphVertexNode<ElemType>::AdjListGraphVertexNode(ElemType elem, LinkList<int> *adjLink/*= NULL*/)// 构造顶点为elem, 指向邻接表的指针为adjLink的结点
{
    this->m_data = elem;
    this->m_adjLink = adjLink;
}



// 函数名称：AdjListGraphVertexNode(const AdjListGraphVertexNode<ElemType> &copy);
// 操作结果：复制构造函数
template <class ElemType>
AdjListGraphVertexNode<ElemType>::AdjListGraphVertexNode(const AdjListGraphVertexNode<ElemType> &copy)   // 复制构造函数
{
    this->m_data = copy.m_data;
    if(copy.m_adjLink != NULL)
    {
        this->m_adjLink = new LinkList<int>(*copy.m_adjLink);
    }
    else
    {
        this->m_adjLink = NULL;
    }
}

// 函数名称：AdjListGraphVertexNode& operator=(const AdjListGraphVertexNode<ElemType> &copy);
// 操作结果：赋值运算符重载函数
// 操作结果：复制构造函数
template <class ElemType>
AdjListGraphVertexNode<ElemType>& AdjListGraphVertexNode<ElemType>::operator=(const AdjListGraphVertexNode<ElemType> &copy)   // 赋值运算符重载函数
{
    if(this == &copy)
    {
        return *this;
    }

    this->m_data = copy.m_data;
    if(copy.m_adjLink != NULL)
    {
        this->m_adjLink = new LinkList<int>(*copy.m_adjLink);
    }
    else
    {
        this->m_adjLink = NULL;
    }

    return (*this);
}



#endif // ADJLISTGRAPHVERTEXNODE_H_INCLUDED
