/**
******************************************************************************
*  CopyRight  : 2012-2013, HerBinUnversity, GatieMe                          *
*  File Name  : TriSparseMatrix.cpp                                            *
*  Description: 三元组顺序表[稀疏矩阵]类TriSparseMatrix源文件               *
*  Author     : Gatie_Me                                                     *
*  Version    : Copyright 2012 JULY_CITY                                     *
*  Data_Time  : 23/10/12 10:23                                               *
*  Content    : 数据结构与算法（C++）版书上源码                             *
******************************************************************************
**/


#ifndef TRIPLE_H_INCLUDED
#define TRIPLE_H_INCLUDED


#include <iostream>

/// 三元组类模版声明部分
template <class ElemType>
class Triple
{
//  friend istream &operator>>(istream &in, Triple<ElemType> &triple);
//  friend ostream &operator<<(ostream &in, const Triple<ElemType> &triple);
  public :
    // 三元组类成员函数模版
    Triple( );                       // 默认构造函数

    Triple(int row, int col, const ElemType &data); // 待参数的构造函数

    Triple &operator=(const Triple<ElemType> &copy); // 重载=操作符

    void SetTriple(int row, int col, const ElemType &elem);     // 设置三元组数据信息

    bool IsThisPoint(int row, int col);             // 判断当前三元素的位置信息是否为row行col列
    // 数据成员
    int m_row, m_col;           // 非0元素的行序号row与列序列
    ElemType m_data;           // 非0元素的值
};



/// 三元组类模版实现部分
/**三元组类成员函数模版[实现]*********************************************************
    Triple( );                       // 默认构造函数
    Triple(int row, int col, const ElemType &data); // 带参数的构造函数
    Triple &operator=(const Triple<ElemType> &copy); // 重载=操作符
    void SetTriple(int row, int col, const ElemType &elem);     // 设置三元组数据信息
    bool IsThisPoint(int row, int col);             // 判断当前三元素的位置信息是否为row行col列
*********************************************************[实现]三元组类成员函数模版**/
// 函数名称：Triple( );
// 操作结果：创建空的三元组对象
template <class ElemType>
Triple<ElemType>::Triple( )                        // 默认构造函数
{
}

// 函数名称：Triple(int row, int col, const ElemType &data);
// 操作结果：创建空的三元组对象
template <class ElemType>
Triple<ElemType>::Triple(int row, int col, const ElemType &data) // 待参数的构造函数
{
    m_row = row;
    m_col = col;
    m_data = data;
}

// 函数名称：Triple &operator=(const Triple<ElemType> &copy);
// 操作结果：创建空的三元组对象
template <class ElemType>
Triple<ElemType>& Triple<ElemType>::operator=(const Triple<ElemType> &copy) // 重载=操作符
{
    m_row = copy.m_row;
    m_col = copy.m_col;
    m_data = copy.m_data;

    return (*this);
}

// 函数名称：void SetTriple(int row, int col, const ElemType &elem);
// 操作结果：更改三元组的数据信息
template <class ElemType>
void Triple<ElemType>::SetTriple(int row, int col, const ElemType &elem)
{
    m_row = row;
    m_col = col;
    m_data = elem;      // 需要ElemType类型的数据支持=操作符运算
}

// 函数名称：bool IsThisPoint(int row, int col)
// 操作结果：判断当前三元素的位置信息是否为row行col列
template <class ElemType>
bool Triple<ElemType>::IsThisPoint(int row, int col)     // 判断当前三元素的位置信息是否为row行col列
{
    return (m_row == row && m_col == col);
}

#endif // TRIPLE_H_INCLUDED
