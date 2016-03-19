/**
******************************************************************************
*  CopyRight  : 2012-2013, HerBinUnversity, GatieMe                          *
*  File Name  : HuffmanTreeNode.h                                                    *
*  Description: 哈夫曼树结点类HuffmanTreeNode模版头文件                               *
*  Author     : Gatie_Me                                                     *
*  Version    : Copyright 2012 JULY_CITY                                     *
*  Data_Time  : 2012-11-6_10:21:43                                           *
*  Content    : 数据结构与算法（C++）版书上源码                             *
******************************************************************************
**/



#ifndef HUFFMANTREENODE_H_INCLUDED
#define HUFFMANTREENODE_H_INCLUDED

#include <stdexcept>        // 标准异常处理类机制
#include <exception>
//using namespace std;

#include "HuffmanTreeNode.h"    // 二叉树结点类


//#define DEBUG           // 插桩调试信息[宏定义]
#define SHOW        // 遍历函数中帮忙显示空结点的信息

/// 哈夫曼树结点类HuffmanTreeNode声明部分
template <class WeightType>
class HuffmanTreeNode
{
/*===========================【PUBLIC：公共接口】============================*/
  public :      // 公共接口
    // 哈夫曼树结点类HuffmanTreeNode基本成员函数
    HuffmanTreeNode( ); // 默认构造函数模版

	HuffmanTreeNode(WeightType weight, int parent = 0, int leftChild = 0, int rightChild = 0);	// 带参数的构造函数

    HuffmanTreeNode(const HuffmanTreeNode<WeightType> &copy);     // 复制构造函数

    ~HuffmanTreeNode( );            // 虚析构函数模版

    // 哈夫曼树结点类HuffmanTreeNode特征成员函数
    HuffmanTreeNode<WeightType> &operator=(const HuffmanTreeNode<WeightType> &copy);

    // 哈夫曼树结点类HuffmanTreeNode数据成员
    WeightType m_weight;            // 编码信息的权值[比如压缩编码中编码出现的频率]
    unsigned int m_parent, m_leftChild, m_rightChild;       // 存储当前编码信息双亲, 左右孩子位置的数据域
};



/**哈夫曼树结点类HuffmanTreeNode基本成员函数[实现]*****************************************************
    HuffmanTreeNode( ); // 默认构造函数模版
	HuffmanTreeNode(WeightType weight, int parent, int leftChild, int rightChild);	// 带参数的构造函数
    HuffmanTreeNode(const HuffmanTreeNode<WeightType> &copy);     // 复制构造函数
    ~HuffmanTreeNode( );            // 虚析构函数模版
    // 哈夫曼树结点类HuffmanTreeNode特征成员函数
    HuffmanTreeNode<WeightType> &operator=(const HuffmanTreeNode<WeightType> &copy);
*****************************************************[实现]哈夫曼树结点类HuffmanTreeNode基本成员函数**/
// 函数名称：HuffmanTreeNode( );
// 操作结果：创建一个哈夫曼树结点对象, 开辟其必要空间
template <class WeightType>
HuffmanTreeNode<WeightType>::HuffmanTreeNode( )     // // 默认构造函数模版
{
#ifdef DEBUG    // 插桩调试信息
std::cout <<"FUN:"<<__func__  <<", LINE:" <<__LINE__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现部分
    this->m_parent = 0;     // 初始化所有的结点指示域为0
    this->m_leftChild = 0;
    this->m_rightChild = 0;
}

// 函数名称：HuffmanTreeNode(WeightType weight, int parent = 0, int leftChild = 0, int rightChild = 0);
// 操作结果：创建一个哈夫曼结点对象
template <class WeightType>
HuffmanTreeNode<WeightType>::HuffmanTreeNode(WeightType weight, int parent/* = 0*/, int leftChild/* = 0*/, int rightChild/* = 0*/)	// 带参数的构造函数
{
#ifdef DEBUG    // 插桩调试信息
std::cout <<"FUN:"<<__func__  <<", LINE:" <<__LINE__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现部分
    this->m_weight = weight;        // 权值信息
    this->m_parent = parent;        // 双亲结点
    this->m_leftChild = leftChild;  // 左孩子
    this->m_rightChild = rightChild;// 右孩子
}

// 函数名称：HuffmanTreeNode(const HuffmanTreeNode<WeightType> &copy);
template <class WeightType>
HuffmanTreeNode<WeightType>::HuffmanTreeNode(const HuffmanTreeNode<WeightType> &copy)  // 复制构造函数    // 复制构造函数
{
#ifdef DEBUG    // 插桩调试信息
std::cout <<"FUN:"<<__func__  <<", LINE:" <<__LINE__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现部分
    this->m_weight = copy.weight;        // 权值信息
    this->m_parent = copy.parent;        // 双亲结点
    this->m_leftChild = copy.leftChild;  // 左孩子
    this->m_rightChild = copy.rightChild;// 右孩子
}


// 函数名称：~HuffmanTreeNode( );
template <class WeightType>
HuffmanTreeNode<WeightType>::~HuffmanTreeNode( )            // 析构函数模版
{
#ifdef DEBUG    // 插桩调试信息
std::cout <<"FUN:"<<__func__  <<", LINE:" <<__LINE__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现部分
}

/**哈夫曼树结点类HuffmanTreeNode特征成员函数[实现]*****************************************************
    HuffmanTreeNode<WeightType> &operator=(const HuffmanTreeNode<WeightType> &copy);
*****************************************************[实现]哈夫曼树结点类HuffmanTreeNode特征成员函数**/
// 函数名称：HuffmanTreeNode<WeightType> &operator=(const HuffmanTreeNode<WeightType> &copy);
template <class WeightType>
HuffmanTreeNode<WeightType>& HuffmanTreeNode<WeightType>::operator=(const HuffmanTreeNode<WeightType> &copy)
{
#ifdef DEBUG    // 插桩调试信息
std::cout <<"FUN:"<<__func__  <<", LINE:" <<__LINE__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现部分
    this->m_weight = copy.weight;        // 权值信息
    this->m_parent = copy.parent;        // 双亲结点
    this->m_leftChild = copy.leftChild;  // 左孩子
    this->m_rightChild = copy.rightChild;// 右孩子
}



#endif // HuffmanTreeNode_H_INCLUDED
