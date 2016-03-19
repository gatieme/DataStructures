/**
*********************************************************************************
*   CopyRight  : 2012-2013, HerBinUnversity, GatieMe                            *
*   File Name  : RefGenListNode.cpp                                             *
*   Description: 引用数法广义表结点类RefGenListNode头文件                      *
*   Author     : Gatie_Me                                                       *
*   Version    : Copyright 2012                                                 *
*   Data_Time  : 20112-10-30 18:43:34                                           *
*   Content    : 数据结构与算法（C++）版书上源码                               *
*********************************************************************************
**/




/// 首先定义一个结点类型枚举类
#ifndef REFGENLISTNODETYPE_INCLUDE
#define REFGENLISTNODETYPE_INCLUDE

// 结点类型枚举类
typedef enum{
    HEAD,   // 表示为头结点,
    DATA,   // 表示为原子结点
    LIST,   // 表示为表结点
}RefGenListNodeType;

#endif      // 结束结点类型枚举类的编译信息



#ifndef REFGENLISTNODE_H_INCLUDED
#define REFGENLISTNODE_H_INCLUDED


/// 引用数法广义表结点类模版
template <class ElemType>
struct RefGenListNode
{
    // 数据成员：
    RefGenListNodeType m_tag;       // 枚举类结点标识
    // 标识tag为HEAD[0]:表示当前结点为头结点
    // 标识tag为ATOM[1]:表示当前结点为原子数据结点
    // 标识tag为LIST[2]:表示当前结点为表结点
    union          // 联合体[依据标识确定联合体的数据]
    {
        int m_ref;          // tag=HEAD[0] -=> 表头结点的数据域, 用于存放引用数
        ElemType m_data;    // tag=ATOM[1] -=> 原子结点的数据域, 用于存放原子元素的值
        RefGenListNode<ElemType> *m_subLink;    // tag=LIST[2] -=>  表结点指针域, 用于存放表的地址
    };
    RefGenListNode<ElemType> *m_nextLink;   // 指向下一个结点的指针域

    // 成员函数
    RefGenListNode(RefGenListNodeType tag = HEAD, RefGenListNode<ElemType> *nextLink = NULL)    // 构造器
    {
        m_tag = tag;        //确定当前结点的标识信息
        switch(m_tag)   // 由标识tag构造数据信息
        {
            case 0: m_ref = 1;
            case 1: m_data = 0 ;
            case 2: m_subLink = NULL;
        }
        m_nextLink = nextLink;

    }
};


#endif // REFGENLISTNODE_H_INCLUDED
