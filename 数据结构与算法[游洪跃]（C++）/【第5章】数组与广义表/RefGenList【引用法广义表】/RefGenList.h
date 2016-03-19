/**
*********************************************************************************
*   CopyRight  : 2012-2013, HerBinUnversity, GatieMe                            *
*   File Name  : RefGenList.cpp                                             *
*   Description: 引用数法广义表类RefGenList头文件                      *
*   Author     : Gatie_Me                                                       *
*   Version    : Copyright 2012                                                 *
*   Data_Time  : 20112-10-30 18:43:34                                           *
*   Content    : 数据结构与算法（C++）版书上源码                               *
*********************************************************************************
**/



#ifndef REFGENLIST_H_INCLUDED
#define REFGENLIST_H_INCLUDED

#include "RefGenListNode.h"

/// 引用数法广义表类模版
template <class ElemType>
class RefGenList
{
/*===========================【PUBLIC：公共接口】============================*/
  public :      // 公共接口
    // RefGenList[引用数法广义表类]类基本成员函数
    RefGenList( );      // 默认构造函数模版

    RefGenList(const RefGenListNode<ElemType> * &head); // 由头结点指针构造引用数法广义表

    RefGenList(const RefGenList<ElemType> &copy);       // 复制构造函数模版

    RefGenList<ElemType> &operator=(const RefGenList<ElemType> &copy);  // 重载=赋值运算符

    virtual ~RefGenList( );         // 析构函数模版

    // RefGenList[引用数法广义表类]特征成员函数
    RefGenListNode<ElemType> *First( ) const;       // 返回表头：引用数法广义表的第一个元素的结点

    RefGenListNode<ElemType> *End( ) const;        // 返回表尾：

    RefGenListNode<ElemType> *Next(const RefGenListNode<ElemType> *elemPtr) const;// 返回elemPtr指向的引用数法广义表元素的后继

    bool Empty( ) const;                // 判断当前引用数法广义表是否为空

    int Depth( ) const;             // 计算当前引用数法广义表的深度

    void Input( ) const;              // 输入广义表

    void Show( ) const;             // 输出广义表

    void Push(const ElemType &elem);        // 将原子元素elem作为表头加入到引用数法广义表最前面

    void Push(const RefGenList<ElemType> &subList); // 将子表subList作为表头加入到引用数法广义表最前面

/*===========================【PUBLIC：公共接口】============================*/
///////////////////////////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////////
/*=========================【PROTECTED：保护成员】===========================*/
  protected :   // 保护成员
    // RefGenList[引用数法广义表类]类数据成员
    RefGenListNode<ElemType> *m_head;     // 引用数发广义表的头指针

    // 辅助成员函数模版
    void ShowHelp(RefGenListNode<ElemType> * &head) const;    // 显示以head为头结点的引用数法广义表

    int DepthHelp(const RefGenListNode<ElemType> * &head) const;    // 计算以head为表头的引用数法广义表的深度

    void ClearHelp(RefGenListNode<ElemType> * &head); // 释放以head为有结点的引用数发广义表的以分配内存空间

    void CopyHelp(const RefGenListNode<ElemType> *sourceHead,
                  const RefGenListNode<ElemType> * &destHead);  // 将以destHead为头结点的引用数法广义表复制成以sourceHead为头结点的引用数法广义表

    void CreateHelp(RefGenListNode<ElemType> * &first); // 创建以first为头结点的引用数法广义表
/*=========================【PROTECTED：：保护成员】=========================*/
};



/**辅助成员函数模版[实现]************************************************************************
    void ShowHelp(RefGenListNode<ElemType> *head) const;    // 显示以head为头结点的引用数法广义表
    int DepthHelp(const RefGenListNode<ElemType> *head);    // 计算以head为表头的引用数法广义表的深度
    void ClearHelp(RefGenListNode<ElemType> *head); // 释放以head为有结点的引用数发广义表的以分配内存空间
    void CopyHelp(const RefGenListNode<ElemType> *sourceHead,
                  const RefGenListNode<ElemType> * &destHead);  // 将以destHead为头结点的引用数法广义表复制成以sourceHead为头结点的引用数法广义表
    void CreateHelp(RefGenListNode<ElemType> * &first); // 创建以first为头结点的引用数法广义表
************************************************************************[实现]辅助成员函数模版**/
// 函数名称：void ShowHelp(RefGenListNode<ElemType> *head) const;
// 函数功能：输出广义表:void Show( ) const的辅助函数
// 操作结果：显示输出以head为头结点的引用数法广义表
template <class ElemType>
void RefGenList<ElemType>::ShowHelp(RefGenListNode<ElemType> * &head) const     // 显示以head为头结点的引用数法广义表
{
}

// 函数名称：int DepthHelp(const RefGenListNode<ElemType> *head);    // 计算以head为表头的引用数法广义表的深度
// 函数功能：计算当前引用数法广义表的深度:int Depth( ) const的辅助函数
// 操作结果：返回当前引用数法广义表的深度
template <class ElemType>
int RefGenList<ElemType>::DepthHelp(const RefGenListNode<ElemType> * &head) const
{
}

// 函数名称：void ClearHelp(RefGenListNode<ElemType> *head); // 释放以head为有结点的引用数发广义表的以分配内存空间
// 函数功能：~RefGenList( )析构函数模版的辅助函数
// 操作结果：删除当前目的广义表以分配的内存空间
template <class ElemType>
void RefGenList<ElemType>::ClearHelp(RefGenListNode<ElemType> * &head)
{
}

// 函数名称：void RefGenList<ElemType>::CopyHelp(const RefGenListNode<ElemType> *sourceHead,
//                                               const RefGenListNode<ElemType> * &destHead);
// 函数功能：赋值构造函数以及赋值运算符重载函数的辅助函数
// 将以destHead为头结点的引用数法广义表复制成以sourceHead为头结点的引用数法广义表
template <class ElemType>
void RefGenList<ElemType>::CopyHelp(const RefGenListNode<ElemType> *sourceHead,
                                    const RefGenListNode<ElemType> * &destHead)
{
}

// 函数名称：void CreateHelp(RefGenListNode<ElemType> * &first);
// 函数功能：构造函数的辅助函数以及Input输入函数的辅助函数
// 操作结果：创建以first为头结点的引用数法广义表
template <class ElemType>
void CreateHelp(RefGenListNode<ElemType> * &first) // 创建以first为头结点的引用数法广义表
{
}

/**RefGenList[引用数法广义表类]类基本成员函数[实现]**********************************************
    RefGenList( );      // 默认构造函数模版
    RefGenList(const RefGenListNode<ElemType> * &head); // 由头结点指针构造引用数法广义表
    RefGenList(const RefGenList<ElemType> &copy);       // 复制构造函数模版
    RefGenList<ElemType> &operator=(const RefGenList<ElemType> &copy);  // 重载=赋值运算符
    virtual ~RefGenList( );         // 析构函数模版
**********************************************RefGenList[引用数法广义表类]类基本成员函数[实现]**/
// 函数名称：RefGenList( );
// 操作结果：初始化一个空的引用数法广义表
template <class ElemType>
RefGenList<ElemType>::RefGenList( )     // 默认构造函数模版
{
    m_head = new RefGenListNode<ElemType>(HEAD);
    m_head->m_ref = 1;      // 空引用数法广义表的引用数为1
}


// 函数名称：RefGenList(const RefGenListNode<ElemType> * &head);
// 操作结果：由头结点指针构造引用数法广义表
template <class ElemType>
RefGenList<ElemType>::RefGenList(const RefGenListNode<ElemType> * &head)    // 带参数的构造函数
{
}


// 函数名称：RefGenList(const RefGenList<ElemType> &copy);
// 操作结果：由参数引用数法广义表copy创建当前目的广义表
template <class ElemType>
RefGenList<ElemType>::RefGenList(const RefGenList<ElemType> &copy)    // 复制构造函数模版
{

}

// 函数名称：RefGenList<ElemType> &operator=(const RefGenList<ElemType> &copy);
// 操作结果：用参数引用数法广义表copy给当前目的广义表赋值
template <class ElemType>
RefGenList<ElemType>& RefGenList<ElemType>::operator=(const RefGenList<ElemType> &copy) // 重载=赋值运算符
{

}

// 函数名称：virtual ~RefGenList( );
// 操作结果：销毁目的广义表已经分配的内存空间
template <class ElemType>
RefGenList<ElemType>::~RefGenList( )    // 析构函数模版
{
}

/**RefGenList[引用数法广义表类]特征成员函数[实现]*************************************************
    RefGenListNode<ElemType> *First( ) const;       // 返回表头：引用数法广义表的第一个元素的结点
    RefGenListNode<ElemType> *End( ) const;        // 返回表尾：
    RefGenListNode<ElemType> *Next(const RefGenListNode<ElemType> *elemPtr) const;// 返回elemPtr指向的引用数法广义表元素的后继
    bool Empty( ) const;                // 判断当前引用数法广义表是否为空
    int Depth( ) const;             // 计算当前引用数法广义表的深度
    void Input( ) const;              // 输入广义表
    void Show( ) const;             // 输出广义表
    void Push(const ElemType &elem);        // 将原子元素elem作为表头加入到引用数法广义表最前面
    void Push(const RefGenList<ElemType> &subList); // 将子表subList作为表头加入到引用数法广义表最前面
*************************************************[实现]RefGenList[引用数法广义表类]特征成员函数**/

#endif // REFGENLIST_H_INCLUDED
