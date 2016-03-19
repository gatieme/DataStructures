/**
******************************************************************************
*  CopyRight  : 2012-2013, HerBinUnversity, GatieMe                          *
*  File Name  : BinTreeNode.h                                                *
*  Description: 二叉树链表BinTree二叉树结点类模版头文件                    *
*  Author     : Gatie_Me                                                     *
*  Version    : Copyright 2012 JULY_CITY                                     *
*  Data_Time  : 2012-11-6_10:21:43                                           *
*  Content    : 数据结构与算法（C++）版书上源码                             *
******************************************************************************
**/

#ifndef BINTREENODE_H_INCLUDED
#define BINTREENODE_H_INCLUDED


/// 二叉树结点类模版声明部分
template <class ElemType>
class BinTreeNode
{
/*===========================【PUBLIC：公共接口】============================*/
  public :      // 公共接口

    // 二叉树结点类BinTreeNode数据成员
    ElemType m_data;                        // 结点数据域
    BinTreeNode<ElemType> *m_leftChild;     // 左子结点指针域
    BinTreeNode<ElemType> *m_rightChild;    // 右子结点指针域

    // 二叉树结点类BinTreeNode基本成员函数
    BinTreeNode( );     // 默认构造函数模版

    BinTreeNode(const ElemType &data, BinTreeNode<ElemType> *leftChild = NULL, BinTreeNode<ElemType> *rightChild = NULL);     // 复制构造函数

    virtual ~BinTreeNode( );

    BinTreeNode<ElemType> &operator=(const BinTreeNode<ElemType> &copy);        // 重载赋值运算符

    // 三元组顺序表[稀疏矩阵]类特征成员函数
    /*--------------暂时空缺--------------*/
/*===========================【PUBLIC：公共接口】============================*/
};



/// 二叉树结点类模版实现部分

// 函数名称：BinTreeNode( );
// 操作结果：建立一个叶子节点, 将指针域正确初始化
template <class ElemType>
BinTreeNode<ElemType>::BinTreeNode( )       // 默认构造函数模版
{
    m_leftChild = m_rightChild = NULL;  // 叶子结点的指针域为空
}

// 函数名称：BinTreeNode(const ElemType &data, BinTreeNode<ElemType> *leftChild = NULL, BinTreeNode<ElemType> *rightChild = NULL);
// 操作结果：建立一个叶子节点, 将指针域正确初始化
template <class ElemType>
BinTreeNode<ElemType>::BinTreeNode(const ElemType &data, BinTreeNode<ElemType> *leftChild/*= NULL*/, BinTreeNode<ElemType> *rightChild/*= NULL*/)    // 复制构造函数
{
    m_data = data;
    m_leftChild = leftChild;
    m_rightChild = rightChild;
}

// 函数名称：virtual ~BinTreeNode( );
// 操作结果：正确删除已经分配的内存空间
template <class ElemType>
BinTreeNode<ElemType>::~BinTreeNode( )      // 虚析构函数模版
{
    if(m_leftChild != NULL)
    {
        delete m_leftChild;
    }
    if(m_rightChild != NULL)
    {
        delete m_rightChild;
    }
}


// 函数名称：BinTreeNode<ElemType> &operator=(const BinTreeNode<ElemType> &copy);
template <class ElemType>
BinTreeNode<ElemType>& BinTreeNode<ElemType>::operator=(const BinTreeNode<ElemType> &copy) // 重载赋值运算符
{
    this.m_data = copy.m_data;
    /**
            暂时空缺的函数信息
    **/
}

#endif // BINTREENODE_H_INCLUDED
