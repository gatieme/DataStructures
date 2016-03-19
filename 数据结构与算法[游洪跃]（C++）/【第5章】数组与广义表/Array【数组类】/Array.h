/**
******************************************************************************
*  Copyright  : 2012-2013, HerBinUnversity, GatieMe                          *
*  File Name  : Array.h                                                      *
*  Description: 数组类头文件                                                *
*  Author     : Gatie_Me                                                     *
*  Version    : Copyright 2012 JULY_CITY                                     *
*  Data_Time  : 25/10/12 17:20                                              *
*  Content    : 数据结构与算法（C++）版书上源码                             *
******************************************************************************
**/

#ifndef ARRAY_H_INCLUDED
#define ARRAY_H_INCLUDED


#include "Error.h"
// 数组类模版
template <class ElemType>
class Array
{
/*===========================【PUBLIC：公共接口】============================*/
  public :      // 公共接口
    // 抽象数据类型方法声明以及重载编辑系统默认方法声明
    Array(int dim,...);       // 由维数dim与随后的各个维度长度构造数组

    Array(const Array<ElemType> &copy);     // 复制构造函数

    ~Array( );                  // 析构函数模版

    Array<ElemType> &operator=(const Array<ElemType> &copy);    // 重载赋值运算符

    ElemType &operator()(int sub,...);     // 重载函数运算符
/*===========================【PUBLIC：公共接口】============================*/
///////////////////////////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////////
/*=========================【PROTECTED：保护成员】===========================*/
  protected :       // 保护数据成员
    ElemType *m_arr;        // 数组的首地址
    int m_dim;              // 数组的维度
    int *m_bounds;          // 数组各维的长度
    int *m_constants;       // 数组映象函数常量

    // 保护函数成员
    int Locate(int sub, va_list &va);       // 求元素在顺序存储中的位置
/*=========================【PROTECTED：：保护成员】=========================*/
};


/**辅助成员函数[实现]*********************************************************
int Locate(int sub, va_list &va);       // 求元素在顺序存储中的位置
*********************************************************[实现]辅助成员函数**/
// 求元素在顺序存储中的位置
int Array<ElemTYpe>::Locate(inr sub, va_list &va)
{
    if(sub >= 0 && sub < m_bounds)
    {
        throw Error("下标出界!");   // 抛出异常
    }

    int off = m_constants[0]*sub;   // 初始化元素在顺序存储中的位置

}

/**数组类的基本成员函数[实现]*************************************************
    Array(int dim,...);       // 由维数dim与随后的各个维度长度构造数组
    Array(const Array<ElemType> &copy);     // 复制构造函数
    ~Array( );                  // 析构函数模版
*************************************************[实现]数组类的基本成员函数**/
// 函数名称：Array(int dim,...);
// 操作结果：由维数dim与随后的各维长度构造一个新的数组
template <class ElemType>
Array<ElemType>::Array(int dim,...)     // 由维数dim与随后的各个维度长度构造数组
{
    if(dim < 1)
    {
        throw Error("数组Array维度不能小于1!"); // 抛出异常
    }

    m_dim = dim;    // 数组维度
    m_bounds = new int[dim];        // 分配空间存储每个维度的的长度信息
    va_list va;                 // 变长参数变量
    int elemTotal = 1;      // 元素总量计算器
    int i;                  // 循环变量

    va_start(va, dim);    // 初始化变长参数变量va, 用于存储变长参数的信息, dim为省略号左侧最右边的参数标识

    for(i = 0; i < m_dim; i++)
    {   // 为各维长度赋值并计算数组总元素个数
        m_bounds[i] = va_arg(va, int);      // 取出变长参数作为各维长度
        elemTotal *= m_bounds[i];           // 统计数组中的总元素个数
    }
    va_end(va);     // 结束变长参数的引用

    m_arr = new ElemType[elemTotal];    // 开辟数组的内存空间

    m_constants =  new int[m_dim];      // 分配函数映射常量的内存空间
    // 计算数组影射函数常量
    m_constants[m_dim-1] = 1;
    for(i = m_dim-2; i >= 0; i--)
    {
        m_constants[i] = m_bounds[i+1] * m_constants[i+1];  //
    }
}

// 函数名称：Array(const Array<ElemType> &copy);
// 操作结果：由数组copy构造新数组, 复制构造函数模版
Array<ElemType>::Array(const Array<ElemType> &copy)    // 复制构造函数
{
    m_dim = copy.m_dim;

    int elemTotal = 1;      //  数组元素总数
    int i;                  //  循环变量

    m_bounds = new int[m_dim];      // 开辟存储各维数据的内存空间
    m_constants = new int[m_dim];   // 存储数组映射函数常量的内存空间
    for(i = 0; i < m_dim; i++)
    {   // 统计数组总元素
        m_bounds[i] = copy.m_bounds[i];         // 各个维的长度
        m_constants[i] = copy.m_constants[i];   // 数组映射函数常量

        elemTotal *= m_bounds[i];       // 计算数组总元素的长度
    }

    m_arr = new ElemType[elemTotal];        // 数组的内存空间
    for(i = 0; i < elemTotal; i++)      // 依次为每个元素赋值
    {
        m_arr[i] = copy.m_arr[i];
    }
}


// 函数名称：~Array( );
// 操作结果：销毁数组的对象空间
template <class ElemType>
Array<ElemType>::~Array( )
{
    if(m_arr != NULL)       // 释放数组内存空间
    {
        delete[] m_arr;
    }
    if(m_bounds != NULL)        // 删除各维度长度的存储信息
    {
        delete[] m_bounds;
    }
    if(m_constants != NULL)     // 删除映射函数变量空间
    {
        delete[] m_constants;
    }
}

/**数组的特征成员函数成员[实现]**************************************************
    Array<ElemType> &operator=(const Array<ElemType> &copy);    // 重载赋值运算符
    ElemType &operator()(int sub,...);     // 重载函数运算符
**************************************************[实现]数组的特征成员函数成员**/
// 函数名称：Array<ElemType> &operator=(const Array<ElemType> &copy);
// 操作结果：
Array<ElemType>& Array<ElemType>::operator=(const Array<ElemType> &copy)
{
    if(&copy != this)
    {
        if(m_arr != NULL)       // 释放数组内存空间
        {
            delete[] m_arr;
        }
        if(m_bounds != NULL)        // 删除各维度长度的存储信息
        {
            delete[] m_bounds;
        }
        if(m_constants != NULL)     // 删除映射函数变量空间
        {
            delete[] m_constants;
        }

        m_dim = copy.m_dim;

        int elemTotal = 1;      //  数组元素总数
        int i;                  //  循环变量

        m_bounds = new int[m_dim];      // 开辟存储各维数据的内存空间
        m_constants = new int[m_dim];   // 存储数组映射函数常量的内存空间
        for(i = 0; i < m_dim; i++)
        {   // 统计数组总元素
            m_bounds[i] = copy.m_bounds[i];         // 各个维的长度
            m_constants[i] = copy.m_constants[i];   // 数组映射函数常量

            elemTotal *= m_bounds[i];       // 计算数组总元素的长度
        }

        m_arr = new ElemType[elemTotal];        // 数组的内存空间
        for(i = 0; i < elemTotal; i++)      // 依次为每个元素赋值
        {
            m_arr[i] = copy.m_arr[i];
        }
    }

    return (*this);
}
#endif // ARRAY_H_INCLUDED
