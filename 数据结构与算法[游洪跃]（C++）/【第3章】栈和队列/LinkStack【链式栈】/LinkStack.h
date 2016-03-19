/********************************************************************************
CopyRight  : 2012-2013, HerBinUnversity, GatieMe
File Name  : LinkStack.h
Author     : Gatie_Me
Version    : 版本声明
Data_Time  : 20112-9-27 19:1:24
********************************************************************************/

/********************************************************************************
History    :修改历史记录列表, 每条修改记录应包括修改日期、修改者以及修改内容
********************************************************************************/

#ifndef LINKSTACK_H_INCLUDED
#define LINKSTACK_H_INCLUDED


#include "Node.h"


//#define DEBUG                     // 如果进行调试请将此注释打开
#define REMIND                    // 如果想输出提醒信息, 请将次注释打开


/// 链式栈类模版
template <class ElemType>
class LinkStack         /// 不带头结点
{
/*===========================【PUBLIC：公共接口】============================*/
  public :      // 公共接口
    // 链式栈基本成员函数
    LinkStack( );               // 无参数的构造函数模版

    LinkStack(const LinkStack<ElemType> &copy);     // 复制构造函数模版

    virtual ~LinkStack( );      // 析构函数模版

    // 链式栈特征成员函数
    int Length( ) const;            // 获取当前链式栈的长度

    bool Empty( ) const;                // 判断当前链式栈是否为空栈

    void Clear( );                      // 清空当前链式栈

    bool Top(ElemType &elem) const;           // 返回栈顶数据

    bool Push(const ElemType &elem);    // 将数据elem入栈

    bool Pop(ElemType &elem);           // 将数据elem出栈

    ElemType Pop( );              // 将数据弹出并且返回

    // 重载操作符函数
    LinkStack<ElemType> &operator=(const LinkStack<ElemType> &copy);        // 重载赋值运算符
/*===========================【PUBLIC：公共接口】============================*/
///////////////////////////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////////
/*=========================【PROTECTED：保护成员】===========================*/
  protected :
  // 链式栈数据成员
    Node<ElemType> *m_top;      // 栈顶指针
  // 赋辅助函数模版
    void Init( );               // 初始化栈
/*=========================【PROTECTED：：保护成员】=========================*/
};


/**辅助函数模版【实现】**************************************************************
    void Init(int size);        // 初始化当前栈信息
**************************************************************【实现】辅助函数模版**/
// 函数名称：void Init(int size)
// 初始条件：链式栈信息需要初始化
// 操作结果：将链式表各个数据元素初始化
template <class ElemType>
void LinkStack<ElemType>::Init( )         // 初始化当前线性栈信息
{
    this->m_top = NULL;     // 构造顶指针
}


/**链式栈类基本成员函数【实现】******************************************************
    LinkStack( );            // 链式栈构造函数模版
    LinkStack(const LinkStack &copy);       // 链式栈类复制构造函数
    virtual ~LinkStack( );                // 链式栈析构函数模版
******************************************************【实现】链式栈类基本成员函数**/
// 函数名称：LinkStack(int size = 100)
// 初始条件：链式栈对象未创建
// 操作结果：创建一个新的链式栈对象空栈
template <class ElemType>
LinkStack<ElemType>::LinkStack( )         // 链式栈构造函数模版
{
    this->Init( );          // 调用初始化函数, 构造一个空栈表
}

// 函数名称：LinkStack(const LinkStack &copy)
// 初始条件：暂时空缺
// 操作结果：用一个链式栈对象copy创建当前链式栈对象
template <class ElemType>
LinkStack<ElemType>::LinkStack(const LinkStack<ElemType> &copy)     // 链式栈类复制构造函数
{
    if(copy.Empty() == true)            // 如果copy字符串为空
    {
        this->Init( );                  // 直接调用初始化函数将目的线性栈设计为空串
    }
    else        // 否则复制链式栈cop不是空串
    {
        this->m_top = new Node<ElemType>(copy.top->data);       // 生成当前栈顶信息
        Node<ElemType> *buttomPtr = this->m_top;                    // 当前栈底信息

        for(Node<ElemType> *tempPtr = copy.m_top->m_next; tempPtr != NULL; tempPtr = tempPtr->m_next)
        {   // 用指针tempPtr依次访问到copy栈中的元素
            buttomPtr->m_next = new Node<ElemType>(tempPtr->data);      // 向栈底依次添加元素
            buttomPtr = buttomPtr->m_next;          // buttomPtr指向新的栈底
        }
    }
}


// 函数名称：virtual ~LinkStack( );
// 初始条件：暂时空缺
// 操作结果：用一个链式栈对象copy创建当前链式栈对象
template <class ElemType>
LinkStack<ElemType>::~LinkStack( )      // 链式栈析构函数模版
{
    this->Clear( );             // 将栈清空
}


/**链式栈类特征函数【实现】******************************************************
    int Length( ) const;                // 获取当前链式栈的栈长度
    void Clear( );                      // 清空当前链式栈
    bool Empty( ) const;                // 判断当前链式栈是否为空栈
    bool Top(ElemType) const;           // 返回栈顶数据
    bool Push(const ElemType &elem);    // 将数据elem入栈
    bool Pop(ElemType &elem);           // 将数据elem出栈
    ElemType Pop( ) const;              // 将数据弹出并且返回
******************************************************【实现】链式栈类特征函数**/
// 函数名称：int Length( ) const;
// 初始条件：链式栈已经建立
// 操作结果：返回当前链式栈的栈长度
template <class ElemType>
int LinkStack<ElemType>::Length( ) const      // 获取当前链式栈的栈长度
{
    // 调试信息
#if defined DEBUG           // 如果宏定义了DEBUG, 执行一下语句
std::cout <<"Length..." <<std::endl;
#endif
    // 函数实现
    int len = 0;
    for(Node<ElemType> *tempPtr = this->m_top; tempPtr != NULL; tempPtr = tempPtr->m_next)
    {   // 用tempPtr依次指向每个元素
        len++;          // 对栈中的元素进行计数
    }

    return len;         // 返回计数信息
}

// 函数名称：void Clear( );
// 初始条件：链式栈已经建立
// 操作结果：返回当前链式栈的栈长度
template <class ElemType>
void LinkStack<ElemType>::Clear( )            // 清空当前链式栈
{
    // 调试信息
#if defined DEBUG           // 如果宏定义了DEBUG, 执行一下语句
std::cout <<"Clear..." <<std::endl;
#endif
    // 函数实现
    ElemType elem;
    while(this->m_top != NULL)      // 只要链式栈不畏空
    {
        this->Pop(elem);            //将元素信息弹出, 即可实现清空
    }
}


// 函数名称：bool Empty( ) const;
// 初始条件：链式栈已经建立
// 操作结果：判断当前链式栈是否为空栈
template <class ElemType>
bool LinkStack<ElemType>::Empty( ) const          // 判断当前链式栈是否为空栈
{
    // 调试信息
#if defined DEBUG           // 如果宏定义了DEBUG, 执行一下语句
std::cout <<"Empty..." <<std::endl;
#endif
    // 函数实现
    return this->m_top == NULL;         // 如果栈顶指着为空, 则说明当前链式栈为空
}

// 函数名称：bool Top(ElemType) const;
// 初始条件：链式栈已经建立
// 操作结果：判断当前链式栈已满
template <class ElemType>
bool LinkStack<ElemType>::Top(ElemType &elem) const           // 返回栈顶数据
{
    // 调试信息
#if defined DEBUG           // 如果宏定义了DEBUG, 执行一下语句
std::cout <<"Top..." <<std::endl;
#endif
    // 函数实现
    if(this->m_top == NULL)     // 如果当前链式栈为空栈
    {
        // 如果想输出提醒信息
        #if define REMIND       // 如果前面定义了REMIND宏, 则此信息将参加编译
        cout <<"当前链式栈为空, 无法获取栈顶元素的信息" <<endl;
        #endif

        return false;           // 无法获取栈顶元素
    }
    else        // 否则当前链式栈不是空的
    {
        elem = this->m_top->m_data;         // 获取链式栈栈顶元素的信息
        return true;            // 获取陈功
    }

}

// 函数名称：bool Push(const ElemType &elem);
// 初始条件：链式栈已经建立
// 操作结果：判断当前链式栈已满
template <class ElemType>
bool LinkStack<ElemType>::Push(const ElemType &elem)    // 将数据elem入栈
{
    // 调试信息
#if defined DEBUG           // 如果宏定义了DEBUG, 执行一下语句
std::cout <<"Push..." <<std::endl;
#endif
    // 函数实现
    Node<ElemType> *newTop = new Node<ElemType>(elem, m_top);     // 首先开辟新的结点空间, 该结点的next指针指向栈顶m
    if(newTop == NULL)
    {
        // 如果想输出提醒信息
        #if define REMIND       // 如果前面定义了REMIND宏, 则此信息将参加编译
        cout <<"动态内存耗尽..." <<endl;
        #endif

        return false;
    }
    else
    {
        this->m_top = newTop;     // 将开辟的新结点设置为新栈顶

        return true;
    }


}

// 函数名称：bool Pop(ElemType &elem);
// 初始条件：链式栈已经建立
// 操作结果：判断当前链式栈已满
template <class ElemType>
bool LinkStack<ElemType>::Pop(ElemType &elem)          // 将数据elem出栈
{
    // 调试信息
#if defined DEBUG           // 如果宏定义了DEBUG, 执行一下语句
std::cout <<"Pop..." <<std::endl;
#endif
    // 函数实现
    if(this->m_top == NULL)     // 如果当前链式栈为空栈
    {
        // 如果想输出提醒信息
        #if define REMIND       // 如果前面定义了REMIND宏, 则此信息将参加编译
        cout <<"当前链式栈为空, 无法获取栈顶元素的信息" <<endl;
        #endif

        return false;           // 无法获取栈顶元素
    }
    else
    {
        Node<ElemType> *oldTop = this->m_top;   // 保存旧栈顶
        elem = oldTop->m_data;          // 用elem返回旧栈顶的数据域
        m_top = m_top->m_next;              // 将栈顶设置为弹出栈顶数据后新的栈顶, 也就是旧栈顶的下一个结点信息

        return oldTop;          // 删除旧栈顶的信息
    }

}


// 函数名称：ElemType Pop( ) const;
// 初始条件：链式栈已经建立, 并且插入数据
// 操作结果：将栈顶的数据返回
template <class ElemType>
ElemType LinkStack<ElemType>::Pop( )
{
    // 调试信息
#if defined DEBUG           // 如果宏定义了DEBUG, 执行一下语句
std::cout <<"Pop..." <<std::endl;
#endif
    ElemType elem;
    if(this->Pop(elem) == true)
    {
        return elem;
    }
    else
    {
        return -1;      // 这是会出问题的但是我没办法了为消除一个警告
    }
}

// 将数据弹出并且返回
/**重载操作符函数【实现】****************************************************************
    LinkStack<EelmType> &operator=(const LinkStack<ElemType> &copy);        // 重载赋值运算符
****************************************************************【实现】重载操作符函数**/
template <class ElemType>
LinkStack<ElemType>& LinkStack<ElemType>::operator=(const LinkStack<ElemType> &copy)
{
    // 调试信息
#if defined DEBUG           // 如果宏定义了DEBUG, 执行一下语句
std::cout <<"Pop..." <<std::endl;
#endif
    // 函数实现
    if(copy.Empty() == true)            // 如果copy字符串为空
    {
        this->Init( );                  // 直接调用初始化函数将目的线性栈设计为空串
    }
    else        // 否则复制链式栈cop不是空串
    {
        this->m_top = new Node<ElemType>(copy.top->data);       // 生成当前栈顶信息
        Node<ElemType> *buttomPtr = this->m_top;                    // 当前栈底信息

        for(Node<ElemType> *tempPtr = copy.m_top->m_next; tempPtr != NULL; tempPtr = tempPtr->m_next)
        {   // 用指针tempPtr依次访问到copy栈中的元素
            buttomPtr->m_next = new Node<ElemType>(tempPtr->data);      // 向栈底依次添加元素
            buttomPtr = buttomPtr->m_next;          // buttomPtr指向新的栈底
        }
    }
}


#endif // LINKSTACK_H_INCLUDED
