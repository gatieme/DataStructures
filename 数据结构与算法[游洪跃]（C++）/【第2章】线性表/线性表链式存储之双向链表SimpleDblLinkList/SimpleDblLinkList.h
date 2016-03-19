/********************************************************************************
CopyRight  : 2012-2013, HerBinUnversity, GatieMe
File Name  : Mym_headFile.h
Description: 实用程序软件包
Author     : Gatie_Me
Version    : Copyright 2012
Data_Time  : 20112-8-4 15:36:24
********************************************************************************/


/********************************************************************************
Problem    :单链表是一种最简单的线性表的链式存储结构, 单链表也称为线性链表
            用它来存储线性表时, 每个数据元素用一个结点（DblNode）来存储, 一个结点
            又分为两个域组成, 一个是存放数据元素的data, 另一个是存储下一个结点
            地址信息的指针域next,

            单链表的存储在最前面增加了一个头结点, 这个结点没有存储任何数据元素
            我们称为头结点m_head, 在单链表中增加头结点虽然增加了存储空间, 但算法实现
            更加简单, 效率更高,
********************************************************************************/

/********************************************************************************
History    :修改历史记录列表, 每条修改记录应包括修改日期、修改者以及修改内容

版本1.0.0  :新增#define DEBUG, #define REMIND两个可选择宏[2012/9/14 15:47:34]

版本1.0.1  :修改Delete函数中出现的错误[2012/9/15 11:27]
********************************************************************************/


#ifndef SIMPLEDBLLINKLIST_H_INCLUDED
#define SIMPLEDBLLINKLIST_H_INCLUDED

#include "DblNode.h"



//#define DEBUG                     // 如果进行调试请将此注释打开
#define REMIND                    // 如果想输出提醒信息, 请将次注释打开

///单链表类模版定义部分
// 带头结点
template <class ElemType>
class SimpleDblLinkList
{
/*=========================【PUBLIC：公共接口】=========================*/
  public :
  // 类的基本成员函数
    SimpleDblLinkList( );     // 默认构造函数模版

    SimpleDblLinkList(const SimpleDblLinkList<ElemType> &copy);   //赋值构造函数模版

    virtual ~SimpleDblLinkList( );     // 虚析构函数模版

  // 类的特征成员函数
    int Length( ) const;            // 获取线性链表的长度

    bool Empty( ) const;            // 判断线性链表是否为空

    void Clean( );            // 清空当前线性链表

    void Traverse(void(*visit)(const ElemType &)) const;    // 遍历线性表

    bool GetElem(int position, ElemType &elem);              // 获取第position个结点的数据

    bool SetElem(int position, const ElemType &elem);       // 设置第position个结点的数据域为elem

    bool Delete(int position, ElemType &elem);              // 删除链表第position个结点的数据, 并将此数据返回给elem

    bool Insert(int position, const ElemType &elem);        // 将数据elem插入到第position个结点

    void Inlist(const ElemType &elem);        // 将数据elem插入到线性链表的末尾

  // 重载函数模版
    SimpleDblLinkList<ElemType> &operator=(const SimpleDblLinkList<ElemType> &copy);  // 重载赋值运算符

  // 特殊处理模版
    bool Swap(int positionA, int positionB);                   // 交换函数 、

    bool BubbleSort(bool minTomax = true);     //冒泡法排序

    bool SelectSort(bool minTomax = true);      //选择法排序

    bool QuickSort(int start, int end);         // 快速排序函数
/*=========================【PUBLIC：公共接口】=========================*/
//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
/*========================【PROTECTED：保护成员】========================*/
  protected :
  // 保护函数成员【辅助函数】
    DblNode<ElemType> *GetElemPtr(int position) const; // 返回指向第position个结点的指针

    void Init( );               // 初始化线性表

  // 保护数据成员
    DblNode<ElemType> *m_head;        // 头结点指针域
/*========================【PROTECTED：保护成员】========================*/
};



/**保护函数成员【实现】******************************************************
    DblNode<ElemType> *GetElemPtr(int position) const;返回指向第position个结点的指针
    void Init( );               初始化线性表
******************************************************保护函数成员【实现】**/

//函数名称：DblNode<ElemType> *GetElemPtr(int position) const
//初始条件：线性链表已经建立, 且不为空
//操作结果：返回指向第position个结点的指针
template <class ElemType>
DblNode<ElemType>* SimpleDblLinkList<ElemType>::GetElemPtr(int position) const // 返回指向第position个结点的指针
{
    // 调试信息
#if defined DEBUG           // 如果宏定义了DEBUG, 执行一下语句
std::cout <<"GetElemPtr..." <<std::endl;
#endif

    // 函数实现
    if(position == 0)  // 如果是想要查找第零个元素的信息, 也就是头指针
    {
        return this->m_head;        // 序号为0的是头结点
    }
    // 否则的话寻找的是以后的接待你
    DblNode<ElemType> *tempPtr = this->m_head->m_next;  // 将数据
    int curPosition = 1;

    while(tempPtr != this->m_head && curPosition < position)
    {   // 用tempPtr指针依次指向每个结点指针域
        tempPtr = tempPtr->m_next;      // 让tempPtr指向下一个结点
        curPosition++;          // 计数器进1
    }

    if(tempPtr != this->m_head && curPosition == position)
    {   // 查找成功
        return tempPtr;
    }
    else
    {   // 否则查找失败
        return NULL;
    }
}

//函数名称： void Init( );
//初始条件：线性表信息未初始化
//操作结果：初始化线性链表的数据信息
template <class ElemType>
void SimpleDblLinkList<ElemType>::Init( )  // 初始化线性表
{
    // 调试信息
#if defined DEBUG           // 如果宏定义了DEBUG, 执行一下语句
std::cout <<"Init..." <<std::endl;
#endif

    // 函数实现
    if(this->Length() > 0)      // 如果当前线性链表不为空
    {
        this->Clean( );               // 清空当前线性表
    }
    // 当循环列表为空时, 头结点的指针域指向头结点
    this->m_head = new DblNode<ElemType>;      // 首先构造头指针
    // 空双向链表-=>头结点前后驱均指向头结点本身
    this->m_head->m_next =  this->m_head;
    this->m_head->m_back = this->m_head;
}


/**类的基本成员函数【实现】************************************************
    SimpleDblLinkList( );     // 默认构造函数模版
    SimpleDblLinkList(const SimpleDblLinkList<ElemType> &copy);//赋值构造函数模版
    virtual ~SimpleDblLinkList( );     // 虚析构函数模版
************************************************【实现】类的基本成员函数**/
//函数名称： SimpleDblLinkList( );
//初始条件：线性表未建立
//操作结果：建立一个空链表
template <class ElemType>
SimpleDblLinkList<ElemType>::SimpleDblLinkList( )     // 默认构造函数模版
{
    // 当循环列表为空时, 头结点的指针域指向头结点
    this->m_head = new DblNode<ElemType>;      // 构造头指针

    // 空双向链表-=>头结点前后驱均指向头结点本身
    this->m_head->m_next =  this->m_head;
    this->m_head->m_back = this->m_head;
}

//函数名称： SimpleDblLinkList(const SimpleDblLinkList<ElemType> &copy);
//初始条件：线性表未建立
//操作结果：建立一个空链表
template <class ElemType>
SimpleDblLinkList<ElemType>::SimpleDblLinkList(const SimpleDblLinkList<ElemType> &copy)
{
    // 首先构造头指针
    this->Init( );     //首先调用初始化函数构造当前链表的头指针
    // this->m_head = new DblNode<ElemType>

//    DblNode<ElemType> *copyPtr = copy.m_head->m_next;    // 建立一个结点指向初始化对象的第一个信息
//    DblNode<ElemType> *tempPtr;                          // 新建一个结点, 作为循环结点域
//    this->m_head->m_next = tempPtr;                   // 将当前结点域与头指针建立联系
//    this->m_head->m_back =
//    while(copyPtr != copy.m_head)   // 控制循环
//    {
//        // 首先建立一个结点存放下一个数据　
//        DblNode<ElemType> *nextPtr, *backPtr;     // 新建的一个结点为下一个结点做准备
//
//        // 为当前循环结点域的数据域赋值
//        tempPtr->m_data = copyPtr->m_data;        // 当前循环结点的数据域为当前被赋值链表对象对应位置的数据域
//        // 当前循环结点的指针域
//        tempPtr->m_next = nextPtr;
//        tempPtr->m_back =
//        // 将结点指向下一个结点
//        tempPtr = nextPtr; //tempPtr->m_next;              // 将当前循环结点的指针域指向下一个结点
//        copyPtr = copyPtr->m_next;                        // 将被赋值结点的指向下一个指针域
//    }
//
//    tempPtr->m_next = this->m_head;     // 构造循环

// 另一种写法是
    ElemType elem;
    for (int curPosition = 1; curPosition <= copy.Length( ); curPosition++)
	{	// 复制数据元素
		copy.GetElem(curPosition, elem);	// 取出第curPosition个元素
		Insert(Length() + 1, elem);		// 将e插入到当前线性表
	}
}

//函数名称： virtual ~SimpleDblLinkList( );     // 虚析构函数模版
//初始条件：线性表建立
//操作结果：销毁线性表
template <class ElemType>
SimpleDblLinkList<ElemType>::~SimpleDblLinkList( )        // 虚析构函数模版
{
    Clean( );
    delete this->m_head;
}


/**类的特征成员函数【实现】**************************************************
    int Length( ) const;            // 获取线性链表的长度
    bool Empty( ) const;            // 判断线性链表是否为空
    void Clean( ) const;            // 清空当前线性链表
    void Traverse(void(*visit)(const ElemType &)) const;//遍历线性表
    bool GetElem(int psition, ElemType &elem);//获取第position个结点的数据
    bool SetElem(int position, const ElemType &elem);// 设置第position个结点的数据域为elem
    bool Delete(int position, ElemType &elem);// 删除链表第position个结点的数据, 并将此数据返回给elem
    bool Insert(int position, const ElemType &elem);// 将数据elem插入到第position个结点
    bool Inlist(int position, const ElemType &elem);// 将数据elem插入到线性链表的末尾
**************************************************【实现】类的特征成员函数*/
//函数名称：int Length( ) const;
//初始条件：线性链表已经建立
//操作结果：返回当前链表的表长
template <class ElemType>
int SimpleDblLinkList<ElemType>::Length( ) const // 获取线性链表的长度
{
    // 调试信息
#if defined DEBUG           // 如果宏定义了DEBUG, 执行一下语句
std::cout <<"Length..." <<std::endl;
#endif
    // 函数实现
    int len = 0;          // 计数器

    for(DblNode<ElemType> *tempPtr = m_head->m_next; tempPtr != this->m_head; tempPtr = tempPtr->m_next)
    {   // 用tempPtr依次指向每个元素
        len++;
    }
//    下面这个方法见C语言程序设计：现代方法
//    for(DblNode<ElemType> *tempPtr = m_head->m_next; count < position; tempPtr = tempPtr->m_next, count++)
//    {
//        continue;
//    }
    return len;             // 返回结束
}

//函数名称：bool Empty( ) const;
//初始条件：线性链表已经建立
//操作结果：如果当前线性链表为空, 返回True, 否则返回False
template <class ElemType>
bool SimpleDblLinkList<ElemType>::Empty( )const    // 判断线性链表是否为空
{
    // 调试信息
#if defined DEBUG           // 如果宏定义了DEBUG, 执行一下语句
std::cout <<"Empty..." <<std::endl;
#endif
    // 函数实现
    return ((this->m_head->m_next == this->m_head)
         && (this->m_head->m_back == this->m_head));   // 如果头指针的下一个结点位置为仍是头结点, 则循环链表为空
}



//函数名称：bool Clean( ) const;
//初始条件：线性链表已经建立
//操作结果：如果当前线性链表为空, 返回True, 否则返回False
template <class ElemType>
void SimpleDblLinkList<ElemType>::Clean( )            // 清空当前线性链表
{
    // 调试信息
#if defined DEBUG           // 如果宏定义了DEBUG, 执行一下语句
std::cout <<"Clean..." <<std::endl;
#endif
    // 函数实现
    ElemType tempElem;      // 临时元素值

    //while(this->Length() > 0)
    while(this->m_head->m_next != this->m_head)   // 只要线性链表不为空
    {
        this->Delete(1, tempElem);     // 就删除第一个元素
    }
}

//函数名称：void Traverse(void(*visit)(const ElemType &)) const;
//初始条件：线性链表已经建立
//操作结果：如果当前线性链表为空, 返回True, 否则返回False
template <class ElemType>
void SimpleDblLinkList<ElemType>::Traverse(void(*visit)(const ElemType &)) const        //遍历线性表
{
    // 调试信息
#if defined DEBUG           // 如果宏定义了DEBUG, 执行一下语句
std::cout <<"Traverse..." <<std::endl;
#endif
    // 函数实现
    for(DblNode<ElemType> *tempPtr = this->m_head->m_next; tempPtr != this->m_head; tempPtr = tempPtr->m_next)
    {
        // 用temp依次指向每个元素
        (*visit)(tempPtr->m_next);     // 访问每一个元素
    }
}

//函数名称：bool GetElem(int psition, ElemType &elem);
//初始条件：线性链表已经建立
//操作结果：获取第position个结点的数据
template <class ElemType>
bool SimpleDblLinkList<ElemType>::GetElem(int position, ElemType &elem)     //获取第position个结点的数据
{
    // 调试信息
#if defined DEBUG           // 如果宏定义了DEBUG, 执行一下语句
std::cout <<"GetElem..." <<std::endl;
#endif
    // 函数实现
    int length = this->Length( );

    if(position < 1 || position > length)   // 如果索引值不合法
    {
        // 输出提示信息
        #if define REMIND
        if(position < 1)
        {
            std::cout <<"索引值" <<position <<"为零或者负" <<std::endl;
        }
        else
        {
            std::cout <<"当前线性链表表长" <<length <<", 索引值" <<position <<"越界." <<std::endl;
        }
        #endif
        return false;
    }
    else        // 否则如果position合法
    {
        DblNode<ElemType> *tempPtr;
        tempPtr = this->GetElemPtr(position);  // 取出指向第position个结点的指针
        elem = tempPtr->m_data;            // 用e返回第podition个元素的值
// 下面的代码也是蛮可以的
//        int curPosition = 0;
//        DblNode<ElemeType> *tempPtr = head->m_next;  // 用tempPtr指向多指的结点
//        while( position <tempPtr != this->m_head; )
//        {   // 用tempPtr依次指向每个元素
//            curPosition++;
//            tempPtr = tempPtr->m_next；
//        }
//        elem = tempPtr->m_data;
        return true;
    }
}

//函数名称：bool SetElem(int position, const ElemType &elem);
//初始条件：线性链表已经建立,
//操作结果：设置第position个结点的数据域为elem
template <class ElemType>
bool SimpleDblLinkList<ElemType>::SetElem(int position, const ElemType &elem)  // 设置第position个结点的数据域为elem
{
    // 调试信息
#if defined DEBUG           // 如果宏定义了DEBUG, 执行一下语句
std::cout <<"Traverse..." <<std::endl;
#endif
    // 函数实现
    // 函数实现
    int length = this->Length( );
    if(position < 1 || position > length)   // 如果索引值不合法
    {
        // 输出提示信息
        #if define REMIND
        if(position < 1)
        {
            std::cout <<"索引值" <<position <<"为零或者负" <<std::endl;
        }
        else
        {
            std::cout <<"当前线性链表表长" <<length <<", 索引值" <<position <<"越界." <<std::endl;
        }
        #endif
        return false;
    }
    else        // 否则如果position合法
    {
        DblNode<ElemType> *tempPtr;
        tempPtr = GetElemPtr(position);  // 取出指向第position个结点的指针
        tempPtr->m_data = elem;            // 用e返回第podition个元素的值
// 下面的代码也是蛮可以的
//        int curPosition = 0;
//        DblNode<ElemeType> *tempPtr = head->m_next;  // 用tempPtr指向多指的结点
//        while( position <tempPtr != NULL; )
//        {   // 用tempPtr依次指向每个元素
//            curPosition++;
//            tempPtr = tempPtr->m_next；
//        }
//        elem = tempPtr->m_data;
        return true;
    }
}


//函数名称：bool Delete(int position, ElemType &elem);// 删除链表第position个结点的数据, 并将此数据返回给elem
//初始条件：线性链表已经建立, 且索引position合法
//操作结果：删除链表第position个结点的数据, 并将此数据返回给elem
template <class ElemType>
bool SimpleDblLinkList<ElemType>::Delete(int position, ElemType &elem)         // 删除链表第position个结点的数据, 并将此数据返回给elem
{
    // 调试信息
#if defined DEBUG           // 如果宏定义了DEBUG, 执行一下语句
std::cout <<"Delete..." <<std::endl;
#endif
    // 函数实现
    int length = this->Length( );   // 首先保存当前线性表的表长, 因为此数据可能多次用到, 防止因为函数多次调用增加时间复杂度

    if(position < 1 || position > length)     // 插入索引不合法
    {
        // 输出提示信息
        if(position < 1)
        {
            std::cout <<"索引值" <<position <<"为零或者负" <<std::endl;
        }
        else
        {
            std::cout <<"当前线性链表表长" <<length <<", 索引值" <<position <<"越界." <<std::endl;
        }
        return false;
    }
    else            // 否则索引position合法
    {
        //tempPtr   nextPtr
        //□■ →→→→→→→→ □■ →→→→→→ □■
        //        position
        DblNode<ElemType> *tempPtr;
        tempPtr = this->GetElemPtr(position);     // 找到要删除位置的结点域
        // 实现目标结点的删除工作
        tempPtr->m_back->m_next = tempPtr->m_next;  // 修改前一个结点的后继
        tempPtr->m_next->m_back = tempPtr->m_back;  // 修改后一个结点的前驱

        // 返回值信息处理
        elem = tempPtr->m_data;                     // 用elem返删结点的数据域
       // delete tempPtr;                             // 删除目的结点

        return true;
    }
}

//函数名称：bool Inlist(int position, const ElemType &elem);
//初始条件：线性链表已经建立
//操作结果：将数据elem插入到线性链表的末尾
template <class ElemType>
bool SimpleDblLinkList<ElemType>::Insert(int position, const ElemType &elem)  // 将数据elem插入到线性链表的末尾
{
    // 调试信息
#if defined DEBUG           // 如果宏定义了DEBUG, 执行一下语句
std::cout <<"Insert..." <<std::endl;
#endif
    // 函数实现
    int length = this->Length( );   // 首先保存当前线性表的表长, 因为此数据可能多次用到, 防止因为函数多次调用增加时间复杂度

    if(position < 1 || position > length+1)     // 插入索引不合法
    {
        // 输出提示信息
        if(position < 1)
        {
            std::cout <<"索引值" <<position <<"为零或者负" <<std::endl;
        }
        else
        {
            std::cout <<"当前线性链表表长" <<length <<", 索引值" <<position <<"越界." <<std::endl;
        }
        return false;
    }
    else            // 否则索引position合法
    {
        //□■ →→→→→→→→ □■ →→→→→→ □■
        //        position
        DblNode<ElemType> *tempPtr, *nextPtr, *newPtr;   //

        tempPtr = this->GetElemPtr(position-1);   // 找到要插入位置的前一个结点域
        nextPtr = tempPtr->m_next;                // nextPtr指向第position个结点
        newPtr = new DblNode<ElemType>(elem, tempPtr, nextPtr); // 构造插入结点
        tempPtr->m_next = newPtr;           // 将前一个结点与插入结点建立必然联系
        nextPtr->m_back = newPtr;           // 将后一个结点域插入结点建立必然联系

        return true;
    }
}

//函数名称：Inlist(const ElemType &elem)
//初始条件：线性链表已经建立
//操作结果：如果当前线性链表为空, 返回True, 否则返回False
template <class ElemType>
void SimpleDblLinkList<ElemType>::Inlist(const ElemType &elem)   // 将数据elem插入到线性链表的末尾
{
    // 调试信息
#if defined DEBUG           // 如果宏定义了DEBUG, 执行一下语句
std::cout <<"Insert..." <<std::endl;
#endif
    // 函数实现
//    for(DblNode<ElemType> *tempPtr = this->m_head; tempPtr->m_next != NULL; tempPtr = tempPtr->m_next)       // 控制循环找到第Position个结点的位置
//    {   // tempPtr依次遍历线性链表
//        continue;
//    }       // 循环结束以后tempPt已经到了最后一个结点域
    DblNode<ElemType> *tempPtr = this->m_head;
    while(tempPtr->m_next != this->m_head)       // 控制循环找到第Position个结点的位置
    {   // tempPtr依次遍历线性链表
        tempPtr = tempPtr->m_next;
    }       // 循环结束以后tempPt已经到了最后一个结点域
    DblNode<ElemType> *newPtr = new DblNode<ElemType>(elem, tempPtr, this->m_head);   // 新建一个结点域
    tempPtr->m_next = newPtr;       // 将新建结点与原来的最后一个结点建立练习
    this->m_head->m_back = newPtr;  // 将插入的结点作为末尾指针即头结点的后继
    // 这样一来, 就把元素elem插在了线性链表的末尾
}


/*************************************************************************************************
    SimpleDblLinkList<ElemType> &operator=(const SimpleDblLinkList<ElemType> &copy);  // 重载赋值运算符
**************************************************************************【实现】重载函数模版**/
//函数名称：SimpleDblLinkList<ElemType> &operator=(const SimpleDblLinkList<ElemType> &copy);
//初始条件：线性链表已经建立
//操作结果：如果当前线性链表为空, 返回True, 否则返回False
template <class ElemType>
SimpleDblLinkList<ElemType>& SimpleDblLinkList<ElemType>::operator=(const SimpleDblLinkList<ElemType> &copy)     // 重载赋值运算符
{
    // 调试信息
#if defined DEBUG           // 如果宏定义了DEBUG, 执行一下语句
std::cout <<"operator=..." <<std::endl;
#endif
    // 函数实现
    if(&copy != this)
    {
        // 首先构造头指针
        this->Init( );     //首先调用初始化函数构造当前链表的头指针
        // this->m_head = new DblNode<ElemType>

//        DblNode<ElemType> *copyPtr = copy.m_head->m_next;    // 建立一个结点指向初始化对象的第一个信息
//        DblNode<ElemType> *tempPtr = new DblNode<ElemType>;   // 新建一个结点, 作为循环结点域
//        tempPtr = this->m_head->m_next;                   // 将当前结点域与头指针建立联系
//
//        while(tempPtr != copy.m_head)   // 控制循环
//        {
//            // 首先建立一个结点存放下一个数据　
//            DblNode<ElemType> *nextPtr;     // 新建的一个结点为下一个结点做准备
//
//            // 为当前循环结点域的数据域赋值
//            tempPtr = copyPtr->m_data;        // 当前循环结点的数据域为当前被赋值链表对象对应位置的数据域
//            tempPtr->m_next = nextPtr;        // 当前循环结点的指针域
//
//            // 将结点指向下一个结点
//            tempPtr = nextPtr; //tempPtr->m_next;              // 将当前循环结点的指针域指向下一个结点
//            copyPtr = copyPtr->m_next;                        // 将被赋值结点的指向下一个指针域
//        }
//
//        tempPtr = this->m_head;

        // 另一种写法是
        ElemType elem;
        for (int curPosition = 1; curPosition <= copy.Length( ); curPosition++)
        {	// 复制数据元素
            copy.GetElem(curPosition, elem);	// 取出第curPosition个元素
            this->Inlist(elem);		// 将e插入到当前线性表
        }
    }

    return *this;
}

/**特殊处理模版【实现】******************************************************
    void Swap( );                   // 交换函数
    bool BubbleSort(bool minTomax = true);     //冒泡法排序
    bool SelectSort(bool minTomax = true);      //选择法排序
    bool QuickSort(int start, int end);         // 快速排序函数
    bool SimpleDblLinkList<ElemType>::CutOddEven( )         // 快速排序函数
******************************************************【实现】特殊处理模版**/
//函数名称：void Swap( )
//初始条件：线性链表已经建立
//操作结果：交换线性链表第positionA个位置的元素和第positionB个位置的元素
template <class ElemType>
bool SimpleDblLinkList<ElemType>::Swap(int positionA, int positionB)                // 交换函数
{
    // 调试信息
#if defined DEBUG           // 如果宏定义了DEBUG, 执行一下语句
std::cout <<"Swap..." <<std::endl;
#endif
    // 函数实现
    int length = this->Length( );                  // 首先保存

    if(positionA < 1 || positionA > length
    || positionB < 1 || positionB > length)
    {
        std::cout <<"参数下标不合法" <<std::endl;
        return false;
    }

    // 实现交换
    DblNode<ElemType> *ptrA = this->GetElemPtr(positionA);     // 获取第positionA个指针
    DblNode<ElemType> *ptrB = this->GetElemPtr(positionB);     // 获取第positionB个指针

    // 实现第position个元素与第position个元素的交换
    ElemType temp;          // 交换中间变量
    temp = ptrA->m_data;
    ptrA->m_data = ptrB->m_data;
    ptrB->m_data = temp;

//    // 实现交换的另一种写法
//    ElemType tempElem, elemA, elemB;      // 交换中间变量
//
//    // 取出对应元素
//    this->GetElem(positionA, elemA);        // 将线性链表的第positionA个元素取出来存在elemA中
//    this->GetElem(positionB, elemB);        // 将线性链表的第positionB个元素取出来存在elemB中
//    // 存放对应元素
//    this->SetElem(positionA, elemB);        // 将数据elemB存放在线性表的第positionA个位置
//    this->SetElem(positionB, elemA);        // 将数据elemB存放在线性表的第positionA个位置
    return true;            // 交换成功
}


//函数名称：bool BubbleSort(bool minTomax = true)
//初始条件：线性链表已经建立
//操作结果：马泡泡发排序线性链表
template <class ElemType>
bool SimpleDblLinkList<ElemType>::BubbleSort(bool minTomax/*= true*/)     //冒泡法排序
{
    // 调试信息
#if defined DEBUG           // 如果宏定义了DEBUG, 执行一下语句
std::cout <<"BubbleSort..." <<std::endl;
#endif
    // 函数实现
    // 写法一：链表的实现方法

    int length = this->Length( );
    if(length == 0)
    {
        std::cout <<"当前线性链表为空, 无法进行排序" <<std::endl;
        return false;
    }

    for(int j = 1; j < length; j++)         // 冒泡发共需要进行length-1趟排序
    {
        int i = 1;
        DblNode<ElemType> *tempPtr = this->m_head->m_next;
        while(i < length-j && tempPtr != NULL)            //每趟循环比较length-1-j趟
        {
//            #if defined DEBUG
//            system("pause");
//            #endif
              // 依次比较相邻的两个数
            if( ((tempPtr->m_data > tempPtr->m_next->m_data) && (minTomax)) // 如果相邻的两个数前一个数比后一个数大, 满足从小到大排序的需求
             || ((tempPtr->m_data < tempPtr->m_next->m_data) && !(minTomax)) )  // 如果相邻的两个数前一个数比后一个数小, 满足从大到小排序的需求
             {
                 this->Swap(i, i+1);
             }
            // 循环控制
            i++, tempPtr = tempPtr->m_next;        // 循环控制, 计数七进1, 同时量表遍历指针往下走
        }
    }

    return true;            // 排序成功
//    // 写法二: 正常写法, 这种写法思路简单, 但是效率低, 函数调用太多
//    ElemType lastItem, nextItem;
//    int length = this->Length( );
//    for(int j = 1; j < length; j++)
//    {
//        for(int i = 1; i < length-j; i++)
//        {
//            // 取出两个相邻的元素
//            this->GetElem(i, lastItem);
//            this->GetElem(i+1, nextItem);
//
//            if( ((lastItem > nextItem) && (minTomax))   // 满足从小到大排序要求的
//             || ((lastItem < nextItem) && !(minTomax)) ) // 满足从大到排序要求的
//            {
//                this->Swap(i, i+1);             // 交换第i个数和第i+1个数
//            }
//        }
//    }
    return true;
}

//函数名称：bool SelectSort(bool minTomax = true)
//初始条件：线性链表已经建立
//操作结果：马泡泡发排序线性链表
template <class ElemType>
bool SimpleDblLinkList<ElemType>::SelectSort(bool minTomax/*= true*/)      //选择法排序
{
    // 调试信息
#if defined DEBUG           // 如果宏定义了DEBUG, 执行一下语句
std::cout <<"SelectSort..." <<std::endl;
#endif
    // 函数实现
    int length = this->Length( );
    if(length == 0)
    {
        std::cout <<"当前线性链表为空, 无法进行排序" <<std::endl;
        return false;
    }
    // 符合排序的前提条件
    ElemType tempItem, sortItem;
   // ElemType elem;
    for(int i = 1; i < length; i++)
    {
        int k = i;      // 用k保存当前比较位置[数据待存放]
        this->GetElem(i, tempItem);
      //  elem = tempItem;         // tempptr用来打擂台保存当前过程中的极值

        for(int j = i+1; j < length; j++)
        {
            this->GetElem(j, sortItem);         // 取出当前待取出比较的元素
            if( ((sortItem < tempItem) && (minTomax))       // 如果带比较的元素[j]符合要求
             || ((sortItem > tempItem) && !(minTomax)) )
            {
                k = j;                  // 用k保存当前符合要求数据的位置
                tempItem = sortItem;    // 同时用tempItem保存当前符合要求的数据
            }
        }       // 一次循环后, k就保存了当前最小元素的位置, tempPtr就保存了当前极值元素的值
                // 而这个数是需要放在第i个位置

        if(k != i/*tempItem != elem*/)
        {
            this->Swap(k, i);
            //this->SetElem(i, tempItem);
            //this->SetElem(k, elem);
        }
    }
    return true;
}

//函数名称：bool QuickSort(bool minTomax = true)
//初始条件：线性链表已经建立
//操作结果：快速排序排序线性链表
template <class ElemType>
bool SimpleDblLinkList<ElemType>::QuickSort(int start, int end)         // 快速排序函数
{
    // 调试信息
#if defined DEBUG           // 如果宏定义了DEBUG, 执行一下语句
std::cout <<"QuickSort..." <<std::endl;
#endif
    // 函数实现
    /// 函数待完善...
    return true;
}


#endif
