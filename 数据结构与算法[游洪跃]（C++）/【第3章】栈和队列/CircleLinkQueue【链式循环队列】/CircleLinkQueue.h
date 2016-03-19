/********************************************************************************
CopyRight  : 2012-2013, HerBinUnversity, GatieMe
File Name  : CircleLinkQueue.h
Description: 链式循环队列定义头文件
Author     : Gatie_Me
Version    : 版本声明
Data_Time  : 20112-9-27 19:1:24
********************************************************************************/

/********************************************************************************
History    :

********************************************************************************/


#ifndef CIRCLELINKQUEUE_H_INCLUDED
#define CIRCLELINKQUEUE_H_INCLUDED


#include "Node.h"


//#define DEBUG                     // 如果进行调试请将此注释打开
#define REMIND                    // 如果想输出提醒信息, 请将次注释打开


/// 链式栈类模版
template <class ElemType>
class CircleLinkQueue        /// 带头结点[但是没有队头数据成员]
{
/*===========================【PUBLIC：公共接口】============================*/
  public :      // 公共接口
    // 链式栈基本成员函数
    CircleLinkQueue( );               // 无参数的构造函数模版

    CircleLinkQueue(const CircleLinkQueue<ElemType> &copy);     // 复制构造函数模版

    virtual ~CircleLinkQueue( );      // 析构函数模版

    // 链式栈特征成员函数
    int Length( ) const;            // 获取当前链式栈的长度

    bool Empty( ) const;                // 判断当前链式循环队列是否为空栈

    bool Full( ) const;                 // 判断当前链式循环队列是否已满

    void Clear( );                      // 清空当前链式循环队列

    bool GetHead(ElemType &elem) const;           // 返回栈顶数据

    bool InQueue(const ElemType &elem);    // 将数据elem入栈

    bool OutQueue(ElemType &elem);           // 将数据elem出栈

    ElemType OutQueue( );              // 将数据弹出并且返回

    // 重载操作符函数
    CircleLinkQueue<ElemType> &operator=(const CircleLinkQueue<ElemType> &copy);        // 重载赋值运算符
/*===========================【PUBLIC：公共接口】============================*/
///////////////////////////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////////
/*=========================【PROTECTED：保护成员】===========================*/
  protected :
  // 链式栈数据成员
    Node<ElemType> *m_rear/*队尾*/;      // 栈顶指针
  //  int m_length;      // 保存当前队列元素个数的信号
  // 赋辅助函数模版
    void Init( );               // 初始化栈

    Node<ElemType>* GetFrontPtr( ) const;     // 获取当前的队头元素信息

    Node<ElemType>* GetHeadPtr( ) const;      // 获取当前的头结点的信息
/*=========================【PROTECTED：：保护成员】=========================*/
};


/**辅助函数模版【实现】**************************************************************
    void Init(int size);        // 初始化当前栈信息
    Node<ElemType>* GetFrontPtr( );     // 获取当前的队头元素信息
    Node<ElemType>* GetHeadPtr( );      // 获取当前的头结点的信息
**************************************************************【实现】辅助函数模版**/
// 函数名称：void Init(int size)
// 初始条件：链式循环队列信息需要初始化
// 操作结果：将顺序表各个数据元素初始化
template <class ElemType>
void CircleLinkQueue<ElemType>::Init( )         // 初始化当前线性栈信息
{
    // 初始化对头m_front与队尾m_rear为同一个内存空间
    this->m_rear = new Node<ElemType>;          // 为结点开辟空间
    this->m_rear->m_next = m_rear;              // 空队列的尾结点指向自己本身
   // this->m_length = 0;
}


//// 函数名称：Node<ElemType>* GetFrontPtr( );
//// 初始条件：链式循环队列信息已经建立
//// 操作结果：返回当前队列元素的队头指针
//template <class ElemType>
//Node<ElemType>* CircleLinkQueue<ElemType>::GetFrontPtr( ) const  // 获取当前的队头元素信息
//{
//    return this->m_rear->m_next->m_next;        // 返回当前队列的队头元素
//}
//
//// 函数名称：Node<ElemType>* GetHeafPtr06( );
//// 初始条件：链式循环队列信息已经建立
//// 操作结果：返回当前队列元素的头结点指针
//template <class ElemType>
//Node* CircleLinkQueue<ElemType>::GetFrontPtr( ) const   // 获取当前的头结点元素信息
//{
//    return this->m_rear->m_next;        // 返回当前队列的头结点
//}


/**链式循环队列类基本成员函数【实现】******************************************************
    CircleLinkQueue( );            // 链式循环队列构造函数模版
    CircleLinkQueue(const DblCircleLinkQueue&copy);       // 链式循环队列类复制构造函数
    virtual ~CircleLinkQueue( );                // 链式循环队列析构函数模版
******************************************************【实现】链式循环队列类基本成员函数**/
// 函数名称：CircleLinkQueue(int size = 100)
// 初始条件：链式循环队列对象未创建
// 操作结果：创建一个新的链式循环队列对象空栈
template <class ElemType>
CircleLinkQueue<ElemType>::CircleLinkQueue( )         // 链式循环队列构造函数模版
{
    // 初始化对头m_front与队尾m_rear为同一个内存空间
    this->m_rear = new Node<ElemType>;          // 为结点开辟空间
    this->m_rear->m_next = m_rear;              // 空队列的尾结点指向自己本身
}

// 函数名称：CircleLinkQueue(const DblCircleLinkQueue&copy)
// 初始条件：暂时空缺
// 操作结果：用一个链式循环队列对象copy创建当前链式循环队列对象
template <class ElemType>
CircleLinkQueue<ElemType>::CircleLinkQueue(const CircleLinkQueue<ElemType> &copy)     // 链式循环队列类复制构造函数
{
    ///暂时空缺
    for()
}


// 函数名称：virtual ~CircleLinkQueue( );
// 初始条件：暂时空缺
// 操作结果：用一个链式循环队列对象copy创建当前链式循环队列对象
template <class ElemType>
CircleLinkQueue<ElemType>::~CircleLinkQueue( )      // 链式循环队列析构函数模版
{
    this->Clear( );
}


/**链式循环队列类特征函数【实现】******************************************************
    int Length( ) const;                // 获取当前链式循环队列的栈长度
    void Clear( );                      // 清空当前链式循环队列
    bool Empty( ) const;                // 判断当前链式循环队列是否为空栈
    bool OutQueue(ElemType) const;           // 返回栈顶数据
    bool InQueue(const ElemType &elem);    // 将数据elem入栈
    bool OutQueue(ElemType &elem);           // 将数据elem出栈
    ElemType OutQueue( ) const;              // 将数据弹出并且返回
******************************************************【实现】链式循环队列类特征函数**/
// 函数名称：int Length( ) const;
// 初始条件：链式循环队列已经建立
// 操作结果：返回当前链式循环队列的栈长度
template <class ElemType>
int CircleLinkQueue<ElemType>::Length( ) const      // 获取当前链式循环队列的栈长度
{
    // 调试信息
#ifdef DEBUG           // 如果宏定义了DEBUG, 执行一下语句
std::cout <<"Length..." <<std::endl;
#endif
    // 函数实现
    //return length;
    int count = 0;
    for(Node<ElemType> *tempPtr = m_rear->m_next;//Node<ElemType> *tempPtr = this->GetFrontPtr( );// 指向第一个元素
        tempPtr != this->m_rear;
        tempPtr = tempPtr->m_next)
    {
        count++;
    }

    return count;
}

// 函数名称：void Clear( );
// 初始条件：链式循环队列已经建立
// 操作结果：返回当前链式循环队列的栈长度
template <class ElemType>
void CircleLinkQueue<ElemType>::Clear( )            // 清空当前链式循环队列
{
    // 调试信息
#ifdef DEBUG           // 如果宏定义了DEBUG, 执行一下语句
std::cout <<"Clear..." <<std::endl;
#endif
    // 函数实现
    while(this->Empty() == false)
    {
        this->OutQueue( );
    }
}


// 函数名称：bool Empty( ) const;
// 初始条件：链式循环队列已经建立
// 操作结果：判断当前链式循环队列是否为空栈
template <class ElemType>
bool CircleLinkQueue<ElemType>::Empty( ) const          // 判断当前链式循环队列是否为空栈
{
    // 调试信息
#ifdef DEBUG           // 如果宏定义了DEBUG, 执行一下语句
std::cout <<"Empty..." <<std::endl;
#endif
    // 函数实现
    return (this->m_rear->m_next == this->m_rear); // 头结点与队尾指向同一区域
    //return (this->GetHead() == this->m_rear);
}


// 函数名称：bool InQueue(const ElemType &elem);
// 初始条件：链式循环队列已经建立
// 操作结果：判断当前链式循环队列已满
template <class ElemType>
bool CircleLinkQueue<ElemType>::InQueue(const ElemType &elem)    // 将数据elem入栈
{
    // 调试信息
#ifdef DEBUG           // 如果宏定义了DEBUG, 执行一下语句
std::cout <<"InQueue..." <<std::endl;
#endif
    // 函数实现
//    if(m_length == 0)   // 如果当前顺序队列是空的
//    {
//        this->m_rear->m_data = elem;    // 直接将数据填入队列中
//        return true;                    //
//    }

    //■■■■----■■■■  ■■■■--{
    Node<ElemType> *newRear = new Node<ElemType>(elem);
    if(newRear == NULL)
    {
        #ifdef REMIND
        std::cout <<"系统内存已经用尽" <<std::endl;
        #endif
        //return false;
        exit(-1);
    }

    newRear->m_next = this->m_rear->m_next; // 始终保持当前顺序队列队尾与队列头的联系
    this->m_rear->m_next = newRear;
    this->m_rear = newRear;                 // rear指向新队尾
    //this->m_length++;
    return true;                            // 入队成功
}


// 函数名称：bool OutQueue(ElemType &elem);
// 初始条件：链式循环队列已经建立
// 操作结果：判断当前链式循环队列已满
template <class ElemType>
bool CircleLinkQueue<ElemType>::GetHead(ElemType &elem)  const       // 将数据elem出栈
{
    // 调试信息
#ifdef DEBUG           // 如果宏定义了DEBUG, 执行一下语句
std::cout <<"GetHead..." <<std::endl;
#endif
    // 函数实现
    if(this->Empty() == true)
    {
        #ifdef REMIND
        std::cout <<"当前链式循环队列为空, 无法获取队头信息..." <<std::endl;
        #endif
        return false;
    }
    elem = this->m_rear->m_next->m_next->m_data;    // 返回元素的信息
    //Node<ElemType> *tempPtr = this->GetFrontPtr();
    //Node<ElemType> *tempPtr = this->m_rear->m_next->m_next;
    //elem = tempPtr->m_data;
    return true;
}


// 函数名称：bool OutQueue(ElemType) const;
// 初始条件：链式循环队列已经建立
// 操作结果：判断当前链式循环队列已满
template <class ElemType>
bool CircleLinkQueue<ElemType>::OutQueue(ElemType &elem)         // 返回栈顶数据
{
    // 调试信息
#ifdef DEBUG           // 如果宏定义了DEBUG, 执行一下语句
std::cout <<"OutQueue..." <<std::endl;
#endif
    // 函数实现
    if(this->Empty() == true)
    {
        #ifdef REMIND
        std::cout <<"当前链式循环队列为空, 无法获取队头信息..." <<std::endl;
        #endif
        return false;
    }
    else
    {
        Node<ElemType> *tempPtr = this->m_rear->m_next->m_next; // 保存当前队头的指针
        elem = tempPtr->m_data;     // 返回队头的数据域
        this->m_rear->m_next->m_next = tempPtr->m_next;
        if(tempPtr == this->m_rear)  // 如果队头指针正好与队尾指针在同一位置说明当前队列只有一个元素
        {       // 那么出队后将没有元素
            this->m_rear = this->m_rear->m_next;
        }
        /// 在windows环境下, 下面的代码总是出错, 为了程序能够运行我将其注释
        //delete tempPtr;       // 删除掉结点的内存信息


        return true;
    }
}

// 函数名称：ElemType OutQueue( ) const;
// 初始条件：链式循环队列已经建立, 并且插入数据
// 操作结果：将栈顶的数据返回
template <class ElemType>
ElemType CircleLinkQueue<ElemType>::OutQueue( )
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
    CircleLinkQueue<EelmType> &operator=(const CircleLinkQueue<ElemType> &copy);        // 重载赋值运算符
****************************************************************【实现】重载操作符函数**/
template <class ElemType>
CircleLinkQueue<ElemType>& CircleLinkQueue<ElemType>::operator=(const CircleLinkQueue<ElemType> &copy)
{
    // 调试信息
#ifdef DEBUG           // 如果宏定义了DEBUG, 执行一下语句
std::cout <<"OutQueue..." <<std::endl;
#endif
    // 函数实现
}


#endif // CircleLinkQueue_H_INCLUDED
