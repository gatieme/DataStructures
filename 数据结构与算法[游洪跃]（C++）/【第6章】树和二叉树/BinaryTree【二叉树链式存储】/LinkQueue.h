/********************************************************************************
CopyRight  : 2012-2013, HerBinUnversity, GatieMe
File Name  : LinkQueue.h
Description: 链式队列定义头文件
Author     : Gatie_Me
Version    : 版本声明
Data_Time  : 20112-9-27 19:1:24
********************************************************************************/

/********************************************************************************
History    :修改历史记录列表, 每条修改记录应包括修改日期、修改者以及修改内容
********************************************************************************/

#ifndef LINKQUEUE_H_INCLUDED
#define LINKQUEUE_H_INCLUDED


#include "Node.h"


//#define DEBUG                     // 如果进行调试请将此注释打开
#define REMIND                    // 如果想输出提醒信息, 请将次注释打开


/// 链式栈类模版
template <class ElemType>
class LinkQueue         /// 带头结点
{
/*===========================【PUBLIC：公共接口】============================*/
  public :      // 公共接口
    // 链式栈基本成员函数
    LinkQueue( );               // 无参数的构造函数模版

    LinkQueue(const LinkQueue<ElemType> &copy);     // 复制构造函数模版

    virtual ~LinkQueue( );      // 析构函数模版

    // 链式栈特征成员函数
    int Length( ) const;            // 获取当前链式栈的长度

    bool Empty( ) const;                // 判断当前链式队列是否为空栈

    void Clear( );                      // 清空当前链式队列

    bool GetHead(ElemType &elem) const;           // 返回栈顶数据

    bool InQueue(const ElemType &elem);    // 将数据elem入栈

    bool OutQueue(ElemType &elem);           // 将数据elem出栈

    ElemType OutQueue( );              // 将数据弹出并且返回

    // 重载操作符函数
    LinkQueue<ElemType> &operator=(const LinkQueue<ElemType> &copy);        // 重载赋值运算符
/*===========================【PUBLIC：公共接口】============================*/
///////////////////////////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////////
/*=========================【PROTECTED：保护成员】===========================*/
  protected :
  // 链式栈数据成员
    Node<ElemType> *m_front/*队头*/, *m_rear/*队尾*/;      // 栈顶指针
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
void LinkQueue<ElemType>::Init( )         // 初始化当前线性栈信息
{
    // 初始化对头m_front与队尾m_rear为同一个内存空间
    this->m_rear = this->m_front = new Node<ElemType>;       // 生成头结点,
}


/**链式队列类基本成员函数【实现】******************************************************
    LinkQueue( );            // 链式队列构造函数模版
    LinkQueue(const LinkQueue &copy);       // 链式队列类复制构造函数
    virtual ~LinkQueue( );                // 链式队列析构函数模版
******************************************************【实现】链式队列类基本成员函数**/
// 函数名称：LinkQueue(int size = 100)
// 初始条件：链式队列对象未创建
// 操作结果：创建一个新的链式队列对象空栈
template <class ElemType>
LinkQueue<ElemType>::LinkQueue( )         // 链式队列构造函数模版
{
    // 初始化队头队尾指向同一个单元
    //this->Init( );
    this->m_front = this->m_rear = new Node<ElemType>;

}

// 函数名称：LinkQueue(const LinkQueue &copy)
// 初始条件：暂时空缺
// 操作结果：用一个链式队列对象copy创建当前链式队列对象
template <class ElemType>
LinkQueue<ElemType>::LinkQueue(const LinkQueue<ElemType> &copy)     // 链式队列类复制构造函数
{
    this->Init( );         // 生成头结点, 是队头队尾指向同意内存单元

    for(Node<ElemType> *tempPtr = copy.m_front->m_next; tempPtr != NULL; tempPtr = tempPtr->m_next)
    {   // 对copy队列每个元素依次入队
        this->InQueue(tempPtr->m_data);
    }
}


// 函数名称：virtual ~LinkQueue( );
// 初始条件：暂时空缺
// 操作结果：用一个链式队列对象copy创建当前链式队列对象
template <class ElemType>
LinkQueue<ElemType>::~LinkQueue( )      // 链式队列析构函数模版
{
    this->Clear( );                     // 清空链式表
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
int LinkQueue<ElemType>::Length( ) const      // 获取当前链式队列的栈长度
{
    // 调试信息
#ifdef DEBUG           // 如果宏定义了DEBUG, 执行一下语句
std::cout <<"Length..." <<std::endl;
#endif
    // 函数实现
    int count = 0;
    for(Node<ElemType> *tempPtr = this->m_front->m_next; tempPtr != NULL; tempPtr = tempPtr->m_next)
    {
        count++;
    }
    return count;
}

// 函数名称：void Clear( );
// 初始条件：链式队列已经建立
// 操作结果：返回当前链式队列的栈长度
template <class ElemType>
void LinkQueue<ElemType>::Clear( )            // 清空当前链式队列
{
    // 调试信息
#ifdef DEBUG           // 如果宏定义了DEBUG, 执行一下语句
std::cout <<"Clear..." <<std::endl;
#endif
    // 函数实现
    ElemType elem;
    while(this->Length() > 0)       // 只要当前队列不是空队
    {
        this->OutQueue(elem);       // 就将数据出队
    }
}


// 函数名称：bool Empty( ) const;
// 初始条件：链式队列已经建立
// 操作结果：判断当前链式队列是否为空栈
template <class ElemType>
bool LinkQueue<ElemType>::Empty( ) const          // 判断当前链式队列是否为空栈
{
    // 调试信息
#ifdef DEBUG           // 如果宏定义了DEBUG, 执行一下语句
std::cout <<"Empty..." <<std::endl;
#endif
    // 函数实现
    return this->m_front == this->m_rear;        // 空栈的一个特性就是队头队尾都是指向同一个内存单元
}

// 函数名称：bool OutQueue(ElemType &elem);
// 初始条件：链式队列已经建立
// 操作结果：判断当前链式队列已满
template <class ElemType>
bool LinkQueue<ElemType>::GetHead(ElemType &elem)  const       // 将数据elem出栈
{
    // 调试信息
#ifdef DEBUG           // 如果宏定义了DEBUG, 执行一下语句
std::cout <<"GetHead..." <<std::endl;
#endif
    // 函数实现
    if(this->Empty() == true)       // 如果当前链式队列为空
    {
        #if define REMIND
        std::cout <<"当前链式表为空, 无法将数据出队" <<std::endl;
        #endif

        return false;
    }
    else
    {
        // 指向链式队列的队头, 出队肯定是打对头开始的
        elem = this->m_front->m_next->m_data;                             // 取出队头的数据

        return true;
    }

}

// 函数名称：bool InQueue(const ElemType &elem);
// 初始条件：链式队列已经建立
// 操作结果：判断当前链式队列已满
template <class ElemType>
bool LinkQueue<ElemType>::InQueue(const ElemType &elem)    // 将数据elem入栈
{
    // 调试信息
#ifdef DEBUG           // 如果宏定义了DEBUG, 执行一下语句
std::cout <<"InQueue..." <<std::endl;
#endif
    // 函数实现

    // [入队只需要将结点追加在在当前链表的尾部, 然后让队尾后移]
    Node<ElemType> *newRear = new Node<ElemType>(elem);    // 新队尾的下一个指向域必然为空
    this->m_rear->m_next = newRear;                         // 新的结点追加在链表的末尾
    this->m_rear = newRear;                                 // 将队尾后移到新建的队尾

    return true;
}


// 函数名称：bool OutQueue(ElemType) const;
// 初始条件：链式队列已经建立
// 操作结果：判断当前链式队列已满
template <class ElemType>
bool LinkQueue<ElemType>::OutQueue(ElemType &elem)         // 返回栈顶数据
{
    // 调试信息
#ifdef DEBUG           // 如果宏定义了DEBUG, 执行一下语句
std::cout <<"OutQueue..." <<std::endl;
#endif
    // 函数实现

    if(this->Empty() == true)       // 如果当前链式队列为空
    {
        #ifdef REMIND
        std::cout <<"当前链式表为空, 无法将数据出队" <<std::endl;
        #endif

        return false;
    }
    else
    {
        Node<ElemType> *oldHead = this->m_front->m_next;     // 指向链式队列的队头, 出队肯定是打对头开始的
        elem = oldHead->m_data;                             // 取出队头的数据
        this->m_front->m_next = oldHead->m_next;

        if(this->m_rear == oldHead)             // 如果原本链式队列中只有一个元素
        {   // 出队以后链式队列为空
            this->m_rear = this->m_front;        // 设置队列为空
        }

        //delete oldHead;     // 释放出队的结点

        return true;
    }
}

// 函数名称：ElemType OutQueue( ) const;
// 初始条件：链式队列已经建立, 并且插入数据
// 操作结果：将栈顶的数据返回
template <class ElemType>
ElemType LinkQueue<ElemType>::OutQueue( )
{
    // 调试信息
#ifdef DEBUG           // 如果宏定义了DEBUG, 执行一下语句
std::cout <<"OutQueue..." <<std::endl;
#endif
    // 函数实现
    ElemType elem;
    if(this->OutQueue(elem) == true)
    {
        return elem;
    }
    else
    {
        return -1;
    }
}

// 将数据弹出并且返回
/**重载操作符函数【实现】****************************************************************
    LinkQueue<EelmType> &operator=(const LinkQueue<ElemType> &copy);        // 重载赋值运算符
****************************************************************【实现】重载操作符函数**/
template <class ElemType>
LinkQueue<ElemType>& LinkQueue<ElemType>::operator=(const LinkQueue<ElemType> &copy)
{
    // 调试信息
#ifdef DEBUG           // 如果宏定义了DEBUG, 执行一下语句
std::cout <<"OutQueue..." <<std::endl;
#endif
    // 函数实现
    if(copy != this)
    {
        this->Clear( );     // 先清空

        for(Node<ElemType> *tempPtr = copy.m_front->m_next; tempPtr != NULL; tempPtr = tempPtr->m_next)
        {   // 用tempPtr指针依次访问copy中的每个元素信息
            this->InQueue(tempPtr->m_data);     // 将元素信息入队
        }
    }
}


#endif // LinkQueue_H_INCLUDED
