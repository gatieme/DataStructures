/********************************************************************************
CopyRight  : 2012-2013, HerBinUnversity, GatieMe
File Name  : DblLinkQueue.h
Description: 链式队列定义头文件
Author     : Gatie_Me
Version    : 版本声明
Data_Time  : 20112-9-27 19:1:24
********************************************************************************/

/********************************************************************************
History    :修改历史记录列表, 每条修改记录应包括修改日期、修改者以及修改内容
********************************************************************************/

#ifndef DblLinkQueue_H_INCLUDED
#define DblLinkQueue_H_INCLUDED


#include "DblNode.h"


//#define DEBUG                     // 如果进行调试请将此注释打开
#define REMIND                    // 如果想输出提醒信息, 请将次注释打开


/// 链式栈类模版
template <class ElemType>
class DblLinkQueue        /// 带头结点
{
/*===========================【PUBLIC：公共接口】============================*/
  public :      // 公共接口
    // 链式栈基本成员函数
    DblLinkQueue( );               // 无参数的构造函数模版

    DblLinkQueue(const DblLinkQueue<ElemType> &copy);     // 复制构造函数模版

    virtual ~DblLinkQueue( );      // 析构函数模版

    // 链式栈特征成员函数
    int Length( ) const;            // 获取当前链式栈的长度

    bool Empty( ) const;                // 判断当前链式队列是否为空栈

    void Clear( );                      // 清空当前链式队列

    bool GetHead(ElemType &elem) const;           // 返回栈顶数据

    bool InQueue(const ElemType &elem);    // 将数据elem入栈

    bool OutQueue(ElemType &elem);           // 将数据elem出栈

    ElemType OutQueue( );              // 将数据弹出并且返回

    // 重载操作符函数
    DblLinkQueue<ElemType> &operator=(const DblLinkQueue<ElemType> &copy);        // 重载赋值运算符
/*===========================【PUBLIC：公共接口】============================*/
///////////////////////////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////////
/*=========================【PROTECTED：保护成员】===========================*/
  protected :
  // 链式栈数据成员
    DblNode<ElemType> *m_rear/*队尾*/;      // 栈顶指针

  // 赋辅助函数模版
    void Init( );               // 初始化栈
/*=========================【PROTECTED：：保护成员】=========================*/
};


/**辅助函数模版【实现】**************************************************************
    void Init(int size);        // 初始化当前栈信息
**************************************************************【实现】辅助函数模版**/
// 函数名称：void Init(int size)
// 初始条件：链式队列信息需要初始化
// 操作结果：将顺序表各个数据元素初始化
template <class ElemType>
void DblLinkQueue<ElemType>::Init( )         // 初始化当前线性栈信息
{
    // 初始化对头m_front与队尾m_rear为同一个内存空间

}


/**链式队列类基本成员函数【实现】******************************************************
    DblLinkQueue( );            // 链式队列构造函数模版
    DblLinkQueue(const DblDblLinkQueue&copy);       // 链式队列类复制构造函数
    virtual ~DblLinkQueue( );                // 链式队列析构函数模版
******************************************************【实现】链式队列类基本成员函数**/
// 函数名称：DblLinkQueue(int size = 100)
// 初始条件：链式队列对象未创建
// 操作结果：创建一个新的链式队列对象空栈
template <class ElemType>
DblLinkQueue<ElemType>::DblLinkQueue( )         // 链式队列构造函数模版
{
    // 初始化队头队尾指向同一个单元
    //this->Init( );
}

// 函数名称：DblLinkQueue(const DblDblLinkQueue&copy)
// 初始条件：暂时空缺
// 操作结果：用一个链式队列对象copy创建当前链式队列对象
template <class ElemType>
DblLinkQueue<ElemType>::DblLinkQueue(const DblLinkQueue<ElemType> &copy)     // 链式队列类复制构造函数
{

}


// 函数名称：virtual ~DblLinkQueue( );
// 初始条件：暂时空缺
// 操作结果：用一个链式队列对象copy创建当前链式队列对象
template <class ElemType>
DblLinkQueue<ElemType>::~DblLinkQueue( )      // 链式队列析构函数模版
{

}


/**链式队列类特征函数【实现】******************************************************
    int Length( ) const;                // 获取当前链式队列的栈长度
    void Clear( );                      // 清空当前链式队列
    bool Empty( ) const;                // 判断当前链式队列是否为空栈
    bool OutQueue(ElemType) const;           // 返回栈顶数据
    bool InQueue(const ElemType &elem);    // 将数据elem入栈
    bool OutQueue(ElemType &elem);           // 将数据elem出栈
    ElemType OutQueue( ) const;              // 将数据弹出并且返回
******************************************************【实现】链式队列类特征函数**/
// 函数名称：int Length( ) const;
// 初始条件：链式队列已经建立
// 操作结果：返回当前链式队列的栈长度
template <class ElemType>
int DblLinkQueue<ElemType>::Length( ) const      // 获取当前链式队列的栈长度
{
    // 调试信息
#ifdef DEBUG           // 如果宏定义了DEBUG, 执行一下语句
std::cout <<"Length..." <<std::endl;
#endif
    // 函数实现
}

// 函数名称：void Clear( );
// 初始条件：链式队列已经建立
// 操作结果：返回当前链式队列的栈长度
template <class ElemType>
void DblLinkQueue<ElemType>::Clear( )            // 清空当前链式队列
{
    // 调试信息
#ifdef DEBUG           // 如果宏定义了DEBUG, 执行一下语句
std::cout <<"Clear..." <<std::endl;
#endif
    // 函数实现
}


// 函数名称：bool Empty( ) const;
// 初始条件：链式队列已经建立
// 操作结果：判断当前链式队列是否为空栈
template <class ElemType>
bool DblLinkQueue<ElemType>::Empty( ) const          // 判断当前链式队列是否为空栈
{
    // 调试信息
#ifdef DEBUG           // 如果宏定义了DEBUG, 执行一下语句
std::cout <<"Empty..." <<std::endl;
#endif
    // 函数实现

}

// 函数名称：bool OutQueue(ElemType &elem);
// 初始条件：链式队列已经建立
// 操作结果：判断当前链式队列已满
template <class ElemType>
bool DblLinkQueue<ElemType>::GetHead(ElemType &elem)  const       // 将数据elem出栈
{
    // 调试信息
#ifdef DEBUG           // 如果宏定义了DEBUG, 执行一下语句
std::cout <<"GetHead..." <<std::endl;
#endif
    // 函数实现
}

// 函数名称：bool InQueue(const ElemType &elem);
// 初始条件：链式队列已经建立
// 操作结果：判断当前链式队列已满
template <class ElemType>
bool DblLinkQueue<ElemType>::InQueue(const ElemType &elem)    // 将数据elem入栈
{
    // 调试信息
#ifdef DEBUG           // 如果宏定义了DEBUG, 执行一下语句
std::cout <<"InQueue..." <<std::endl;
#endif
    // 函数实现
}


// 函数名称：bool OutQueue(ElemType) const;
// 初始条件：链式队列已经建立
// 操作结果：判断当前链式队列已满
template <class ElemType>
bool DblLinkQueue<ElemType>::OutQueue(ElemType &elem)         // 返回栈顶数据
{
    // 调试信息
#ifdef DEBUG           // 如果宏定义了DEBUG, 执行一下语句
std::cout <<"OutQueue..." <<std::endl;
#endif
    // 函数实现
}

// 函数名称：ElemType OutQueue( ) const;
// 初始条件：链式队列已经建立, 并且插入数据
// 操作结果：将栈顶的数据返回
template <class ElemType>
ElemType DblLinkQueue<ElemType>::OutQueue( )
{
    // 调试信息
#ifdef DEBUG           // 如果宏定义了DEBUG, 执行一下语句
std::cout <<"OutQueue..." <<std::endl;
#endif
    // 函数实现
}

// 将数据弹出并且返回
/**重载操作符函数【实现】****************************************************************
    DblLinkQueue<EelmType> &operator=(const DblLinkQueue<ElemType> &copy);        // 重载赋值运算符
****************************************************************【实现】重载操作符函数**/
template <class ElemType>
DblLinkQueue<ElemType>& DblLinkQueue<ElemType>::operator=(const DblLinkQueue<ElemType> &copy)
{
    // 调试信息
#ifdef DEBUG           // 如果宏定义了DEBUG, 执行一下语句
std::cout <<"OutQueue..." <<std::endl;
#endif
    // 函数实现
}


#endif // DblLinkQueue_H_INCLUDED
