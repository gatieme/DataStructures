/********************************************************************************
CopyRight  : 2012-2013, HerBinUnversity, GatieMe
File Name  : SqStack.h
Description: 顺序栈SqStack实现头文件
Author     : Gatie_Me
Version    : Copyright 2012
Data_Time  : 20112-9-19 18:11:24
Content    : 数据结构与算法（C++）版书上
********************************************************************************/


/********************************************************************************
History    :C++顺序栈的实现

版本1.0.0
********************************************************************************/


#ifndef SQSTACK_H_INCLUDED
#define SQSTACK_H_INCLUDED

//#define DEBUG                     // 如果进行调试请将此注释打开
#define REMIND                    // 如果想输出提醒信息, 请将次注释打开

/// 顺序栈类SqStack定义部分
template <class ElemType>
class SqStack
{
/*===========================[Friend-=>友元声明]===========================*/
        ///暂时空缺
/*===========================[Friend-=>友元声明]===========================*/
/////////////////////////////////////////////////////////////////////////////
//
//
/////////////////////////////////////////////////////////////////////////////
/*===========================[PUBLIC-=>公共接口]===========================*/
  public :      ///公共接口
    // 顺序栈类基本成员函数[声明]
    SqStack(int size = 100);            // 顺序栈构造函数模版

    SqStack(const SqStack &copy);       // 顺序栈类复制构造函数

    virtual ~SqStack( );                // 顺序栈析构函数模版

    // 顺序栈类特征函数声明
    int Length( ) const;                // 获取当前顺序栈的栈长度

    void Clear( );                      // 清空当前顺序栈

    void Traverse(void(*Visit)(const ElemType &)) const;        //遍历当前顺序栈

    bool Empty( ) const;                // 判断当前顺序栈是否为空栈

    bool Full( ) const;                 // 判断栈是否已满

    bool Top(ElemType &elem) const;           // 返回栈顶数据

    bool Push(const ElemType &elem);    // 将数据elem入栈

    bool Pop(ElemType &elem);           // 将数据elem出栈

    ElemType Pop( );              // 将数据弹出并且返回

    // 重载操作符函数
    SqStack<ElemType> &operator=(const SqStack<ElemType> &copy);        // 重载赋值运算符
/*===========================[PUBLIC-=>公共接口]===========================*/


/*==========================[PROTECTED-=>保护对象]==========================*/
  protected :   /// 顺序栈的保护成员
    // 顺序栈的数据成员
    ElemType *m_elems;            // 元素存储的空间
    int m_maxSize;                // 最大元素个数
    int m_length;                 // 栈当前元素个数

    // 辅助函数模版
    void Init(int size = 100);        // 初始化当前栈信息


/*==========================[PROTECTED-=>保护对象]==========================*/
};


/// 顺序栈类SqStack实现部分
/**辅助函数模版【实现】**************************************************************
    void Init(int size);        // 初始化当前栈信息
**************************************************************【实现】辅助函数模版**/
// 函数名称：void Init(int size)
// 初始条件：顺序栈信息需要初始化
// 操作结果：将顺序表各个数据元素初始化
template <class ElemType>
void SqStack<ElemType>::Init(int size/*= 100*/)         // 初始化当前线性栈信息
{
    if(m_elems != NULL)                       // 如果当前区域不为空
    {
        delete []m_elems;                     // 就删除原来的区域信息
    }
    this->m_maxSize = size;                 // 依据参数确定最大元素的信息
    this->m_elems = new ElemType[m_maxSize];        // 同时开辟新的区域
    this->m_length = 0;
}


/**顺序栈类基本成员函数【实现】******************************************************
    SqStack(int size = 100);            // 顺序栈构造函数模版
    SqStack(const SqStack &copy);       // 顺序栈类复制构造函数
    virtual ~SqStack( );                // 顺序栈析构函数模版
******************************************************【实现】顺序栈类基本成员函数**/
// 函数名称：SqStack(int size = 100)
// 初始条件：顺序栈对象未创建
// 操作结果：创建一个新的顺序栈对象
template <class ElemType>
SqStack<ElemType>::SqStack(int size/* = 100*/)         // 顺序栈构造函数模版
{
    this->m_maxSize = size;                 // 依据参数确定最大元素的信息
    this->m_elems = new ElemType[m_maxSize];        // 同时开辟新的区域
    this->m_length = 0;
}

// 函数名称：SqStack(const SqStack &copy)
// 初始条件：暂时空缺
// 操作结果：用一个顺序栈对象copy创建当前顺序栈对象
template <class ElemType>
SqStack<ElemType>::SqStack(const SqStack<ElemType> &copy)     // 顺序栈类复制构造函数
{
    this->Init(copy.m_maxSize);     // 以赋值对象顺序栈的最大元素值初始化当前顺序栈的最大元素

    for(int curPosition = 0; curPosition < this->m_length; curPosition++)
    {       // 用curPosition遍历copy顺序栈的每个元素
        this->m_elems[curPosition] = copy.elems[curPosition];      // 同时将copy的每个元素赋给当前顺序栈
    }
}


// 函数名称：virtual ~SqStack( );
// 初始条件：暂时空缺
// 操作结果：用一个顺序栈对象copy创建当前顺序栈对象
template <class ElemType>
SqStack<ElemType>::~SqStack( )      // 顺序栈析构函数模版
{
    if(m_elems != NULL)             // 如果当前线性栈空间不为空
    {
        delete []m_elems;           // 就删除当前栈信息的已分配堆空间
    }
}


/**顺序栈类特征函数【实现】******************************************************
    int Length( ) const;                // 获取当前顺序栈的栈长度
    void Clear( );                      // 清空当前顺序栈
    void Traverse(void(*Visit)(const ElemType<ElemType> &)) const//遍历当前顺序栈
    bool Empty( ) const;                // 判断当前顺序栈是否为空栈
    bool Full( ) const;                 // 判断栈是否已满
    bool Top(ElemType) const;           // 返回栈顶数据
    bool Push(const ElemType &elem);    // 将数据elem入栈
    bool Pop(ElemType &elem);           // 将数据elem出栈
    ElemType Pop( ) const;              // 将数据弹出并且返回
******************************************************【实现】顺序栈类特征函数**/
// 函数名称：int Length( ) const;
// 初始条件：顺序栈已经建立
// 操作结果：返回当前顺序栈的栈长度
template <class ElemType>
int SqStack<ElemType>::Length( ) const      // 获取当前顺序栈的栈长度
{
    // 调试信息
#if defined DEBUG           // 如果宏定义了DEBUG, 执行一下语句
std::cout <<"Length..." <<std::endl;
#endif
    // 函数实现
    return m_length;                      // 返回当前顺序栈的栈长
}

// 函数名称：void Clear( );
// 初始条件：顺序栈已经建立
// 操作结果：返回当前顺序栈的栈长度
template <class ElemType>
void SqStack<ElemType>::Clear( )            // 清空当前顺序栈
{
    // 调试信息
#if defined DEBUG           // 如果宏定义了DEBUG, 执行一下语句
std::cout <<"Clear..." <<std::endl;
#endif
    // 函数实现
    this->m_length = 0;                             // 直接将顺序栈的栈宽置为0即可
}

// 函数名称：void Traverse(void(*Visit)(const ElemType<ElemType> &)) const//遍历当前顺序栈
// 初始条件：顺序栈已经建立
// 操作结果：从栈底到栈顶依次对栈的每个元素调用函数(*visit)
template <class ElemType>
void SqStack<ElemType>::Traverse(void(*Visit)(const ElemType &)) const       //遍历当前顺序栈
{
    // 调试信息
#if defined DEBUG           // 如果宏定义了DEBUG, 执行一下语句
std::cout <<"Traverse..." <<std::endl;
#endif
    // 函数实现
    // 从栈底到栈顶依次对栈的每个元素调用函数(*visit)
    for(int curPosition = 0; curPosition < this->m_length; curPosition++)
    {
        (*Visit)(m_elems[curPosition]);
    }
}


// 函数名称：bool Empty( ) const;
// 初始条件：顺序栈已经建立
// 操作结果：判断当前顺序栈是否为空栈
template <class ElemType>
bool SqStack<ElemType>::Empty( ) const          // 判断当前顺序栈是否为空栈
{
    // 调试信息
#if defined DEBUG           // 如果宏定义了DEBUG, 执行一下语句
std::cout <<"Empty..." <<std::endl;
#endif
    // 函数实现
    return m_length == 0;           // 如果顺序栈为空(m_length == 0)则返回true, 否则返回false
}


// 函数名称：bool Full( ) const;
// 初始条件：顺序栈已经建立
// 操作结果：判断当前顺序栈已满
template <class ElemType>
bool SqStack<ElemType>::Full( ) const                 // 判断栈是否已满
{
    return m_length == m_maxSize;       // 如果顺序栈已满(m_length == m_maxSize)则返回true, 否则返回false
}

// 函数名称：bool Top(ElemType) const;
// 初始条件：顺序栈已经建立
// 操作结果：判断当前顺序栈已满
template <class ElemType>
bool SqStack<ElemType>::Top(ElemType &elem) const           // 返回栈顶数据
{
    // 调试信息
#if defined DEBUG           // 如果宏定义了DEBUG, 执行一下语句
std::cout <<"Top..." <<std::endl;
#endif
    // 函数实现
    if(this->m_length == 0)//this->Empty( ) == true // 如果当前顺序栈是空的
    {
        std::cout <<"当前线性表为空, 无法返回栈顶数据" <<std::endl;

        return false;       // 无法获取栈顶数据
    }
    else
    {
        elem = this->m_elems[m_length-1];       // 用elems返回栈顶元素

        return true;        // 获取栈顶数据成功
    }
}

// 函数名称：bool Push(const ElemType &elem);
// 初始条件：顺序栈已经建立
// 操作结果：判断当前顺序栈已满
template <class ElemType>
bool SqStack<ElemType>::Push(const ElemType &elem)    // 将数据elem入栈
{
    // 调试信息
#if defined DEBUG           // 如果宏定义了DEBUG, 执行一下语句
std::cout <<"Push..." <<std::endl;
#endif
    // 函数实现
    if(this->Full( ))//this->m_length == this->m_maxSize       // 如果当前栈是满栈
    {
        std::cout <<"当前顺序栈已经满了, 无法再将数据压入栈..." <<std::endl; // 提示信息
        return false;                   // 入栈失败
    }
    else
    {
        this->m_elems[m_length++] = elem;           // 将数据elem压入栈顶
        return true;                        // 入栈成功
    }
}

// 函数名称：bool Pop(ElemType &elem);
// 初始条件：顺序栈已经建立
// 操作结果：判断当前顺序栈已满
template <class ElemType>
bool SqStack<ElemType>::Pop(ElemType &elem)          // 将数据elem出栈
{
    // 调试信息
#if defined DEBUG           // 如果宏定义了DEBUG, 执行一下语句
std::cout <<"Pop..." <<std::endl;
#endif
    // 函数实现
    if(this->Empty( ))//this->m_length == 0     // 如果当前顺序栈为空
    {
        std::cout <<"当前顺序栈为空, 无法将数据弹出栈..." <<std::endl;
        return false;           // 出栈失败
    }
    else
    {
        elem = this->m_elems[--m_length];   // 用elem返回即将弹出的元素
        return true;                // 出栈成功
    }
}


// 函数名称：ElemType Pop( ) const;
// 初始条件：顺序栈已经建立, 并且插入数据
// 操作结果：将栈顶的数据返回
template <class ElemType>
ElemType SqStack<ElemType>::Pop( )
{
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
    SqStack<EelmType> &operator=(const SqStack<ElemType> &copy);        // 重载赋值运算符
****************************************************************【实现】重载操作符函数**/
template <class ElemType>
SqStack<ElemType>& SqStack<ElemType>::operator=(const SqStack<ElemType> &copy)
{
    // 调试信息
#if defined DEBUG           // 如果宏定义了DEBUG, 执行一下语句
std::cout <<"Pop..." <<std::endl;
#endif
    // 函数实现
    this->Init(copy.m_maxSize);     // 以赋值对象顺序栈的最大元素值初始化当前顺序栈的最大元素

    for(int curPosition = 0; curPosition < this->m_length; curPosition++)
    {       // 用curPosition遍历copy顺序栈的每个元素
        this->m_elems[curPosition] = copy.elems[curPosition];      // 同时将copy的每个元素赋给当前顺序栈
    }
}





#endif // SQSTACK_H_INCLUDED
