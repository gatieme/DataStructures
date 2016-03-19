/********************************************************************************
CopyRight  : 2012-2013, HerBinUnversity, GatieMe
File Name  : SqDoubleStack.h
Description: 顺序栈SqDoubleStack实现头文件
Author     : Gatie_Me
Version    : Copyright 2012
Data_Time  : 20112-9-19 18:11:24
Content    : 数据结构与算法（C++）版书上
********************************************************************************/


/********************************************************************************
History    :C++顺序栈的实现

版本1.0.0
********************************************************************************/




#ifndef SQDOUBLESTACK_H_INCLUDED
#define SQDOUBLESTACK_H_INCLUDED



//#define DEBUG                     // 如果进行调试请将此注释打开
#define REMIND                    // 如果想输出提醒信息, 请将次注释打开

/// 顺序栈类SqDoubleStack定义部分
template <class ElemType>
class SqDoubleStack
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
    SqDoubleStack(int size = 100);            // 顺序栈构造函数模版

    SqDoubleStack(const SqDoubleStack &copy);       // 顺序栈类复制构造函数

    virtual ~SqDoubleStack( );                // 顺序栈析构函数模版

    // 顺序栈类特征函数声明
    int Length(int index = 0) const;                // 获取当前顺序栈的栈长度

    void Clear(int index = 0);                      // 清空当前顺序栈

    void Traverse(void(*Visit)(const ElemType &)) const;        //遍历当前顺序栈

    bool Empty(int index = 0) const;                // 判断当前顺序栈是否为空栈

    bool Full( ) const;                 // 判断栈是否已满

    bool Top(int index, ElemType &elem) const;           // 返回栈顶数据

    bool Push(int index, const ElemType &elem);    // 将数据elem入栈

    bool Pop(int index, ElemType &elem);           // 将数据elem出栈

    ElemType Pop(int index);              // 将数据弹出并且返回

    // 重载操作符函数
    SqDoubleStack<ElemType> &operator=(const SqDoubleStack<ElemType> &copy);        // 重载赋值运算符
/*===========================[PUBLIC-=>公共接口]===========================*/


/*==========================[PROTECTED-=>保护对象]==========================*/
  protected :   /// 顺序栈的保护成员
    // 顺序栈的数据成员
    ElemType *m_elems;            // 元素存储的空间
    int m_maxSize;                // 栈最大空间即最大元素个数
    int m_leftLen;                // 左栈元素个数
    int m_rightLen;               // 右栈元素个数

    // 辅助函数模版
    void Init(int size = 100);        // 初始化当前栈信息
/*==========================[PROTECTED-=>保护对象]==========================*/
};


/// 顺序栈类SqDoubleStack实现部分
/**辅助函数模版【实现】**************************************************************
    void Init(int size);        // 初始化当前栈信息
**************************************************************【实现】辅助函数模版**/
// 函数名称：void Init(int size)
// 初始条件：顺序栈信息需要初始化
// 操作结果：将顺序表各个数据元素初始化
template <class ElemType>
void SqDoubleStack<ElemType>::Init(int size/*= 100*/)         // 初始化当前线性栈信息
{
#ifdef DEBUG           // 如果宏定义了DEBUG, 执行一下语句
std::cout <<"Length..." <<std::endl;
#endif
    m_elems = new ElemType[size];    // 开辟空间
    if(m_elems == NULL)
    {
        #ifdef REMIND
        std::cout <<"内存空间不足..." <<std::endl;
        #endif
        exit(-1);
    }
    this->m_maxSize = size;
    this->m_leftLen = 0;
    this->m_rightLen = 0;
}


/**顺序栈类基本成员函数【实现】******************************************************
    SqDoubleStack(int size = 100);            // 顺序栈构造函数模版
    SqDoubleStack(const SqDoubleStack &copy);       // 顺序栈类复制构造函数
    virtual ~SqDoubleStack( );                // 顺序栈析构函数模版
******************************************************【实现】顺序栈类基本成员函数**/
// 函数名称：SqDoubleStack(int size = 100)
// 初始条件：顺序栈对象未创建
// 操作结果：创建一个新的顺序栈对象
template <class ElemType>
SqDoubleStack<ElemType>::SqDoubleStack(int size/* = 100*/)         // 顺序栈构造函数模版
{
    this->m_elems = new ElemType[size];    // 开辟空间
    if(m_elems == NULL)
    {
        #ifdef REMIND
        std::cout <<"内存空间不足..." <<std::endl;
        #endif
        exit(-1);
    }
    this->m_maxSize = size;
    this->m_leftLen = 0;
    this->m_rightLen = 0;
}

// 函数名称：SqDoubleStack(const SqDoubleStack &copy)
// 初始条件：暂时空缺
// 操作结果：用一个顺序栈对象copy创建当前顺序栈对象
template <class ElemType>
SqDoubleStack<ElemType>::SqDoubleStack(const SqDoubleStack<ElemType> &copy)     // 顺序栈类复制构造函数
{
    this->Init(copy.m_maxSize);     // 以赋值对象顺序栈的最大元素值初始化当前顺序栈的最大元素
    ///
}


// 函数名称：virtual ~SqDoubleStack( );
// 初始条件：暂时空缺
// 操作结果：用一个顺序栈对象copy创建当前顺序栈对象
template <class ElemType>
SqDoubleStack<ElemType>::~SqDoubleStack( )      // 顺序栈析构函数模版
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
int SqDoubleStack<ElemType>::Length(int index/* = 0*/) const      // 获取当前顺序栈的栈长度
{
    // 调试信息
#ifdef DEBUG           // 如果宏定义了DEBUG, 执行一下语句
std::cout <<"Length..." <<std::endl;
#endif
    // 函数实现
    if(index == 0)      // 要求返回总栈的空间
    {
        return m_leftLen + m_rightLen;
    }
    else if(index == -1)    // 要求返回左栈的空间
    {
        return m_leftLen;
    }
    else if(index == 1)     // 要求返回右栈的空间
    {
        return m_rightLen;
    }
    else                    // 否则参数有问题
    {
        #ifdef REMIND
        std::cout <<"Length()参数故障..." <<std::endl;
        #endif
        int in;
        std::cout <<"请重新输入参数index" <<std::endl;
        std::cout <<"-1 -= 获取左栈元素个数" <<std::endl;
        std::cout <<" 0 -= 获取总栈元素个数" <<std::endl;
        std::cout <<" 1 -= 获取右栈元素个数" <<std::endl <<std::endl;
        std::cin >>in;
        this->Length(in);
    }
    return false;
}

// 函数名称：void Clear( );
// 初始条件：顺序栈已经建立
// 操作结果：返回当前顺序栈的栈长度
template <class ElemType>
void SqDoubleStack<ElemType>::Clear(int index/* = 0*/)            // 清空当前顺序栈
{
    // 调试信息
#ifdef DEBUG           // 如果宏定义了DEBUG, 执行一下语句
std::cout <<"Clear..." <<std::endl;
#endif
    // 函数实现
    if(index == 0)
    {
        this->m_leftLen = 0;                             // 直接将顺序栈的栈宽置为0即可
        this->m_rightLen = 0;
    }
    else if(index == -1)
    {
        this->m_leftLen = 0;
    }
    else if(index == 1)
    {
        this->m_rightLen = 0;
    }
    else                    // 否则参数有问题
    {
        #ifdef REMIND
        std::cout <<"Clear()参数故障..." <<std::endl;
        #endif
        int in;
        std::cout <<"请重新输入参数index" <<std::endl;
        std::cout <<"-1 -= 清空左栈" <<std::endl;
        std::cout <<" 0 -= 清空总栈" <<std::endl;
        std::cout <<" 1 -= 清空右栈" <<std::endl <<std::endl;
        std::cin >>in;
        this->Clear(in);
    }
}


// 函数名称：bool Empty( ) const;
// 初始条件：顺序栈已经建立
// 操作结果：判断当前顺序栈是否为空栈
template <class ElemType>
bool SqDoubleStack<ElemType>::Empty(int index/* = 0*/) const          // 判断当前顺序栈是否为空栈
{
    // 调试信息
#ifdef DEBUG           // 如果宏定义了DEBUG, 执行一下语句
std::cout <<"Empty..." <<std::endl;
#endif
    // 函数实现
    if(index == 0)
    {
        return (this->m_leftLen == 0                              // 直接将顺序栈的栈宽置为0即可
               && this->m_rightLen == 0);
    }
    else if(index == -1)
    {
        return (this->m_leftLen == 0);
    }
    else if(index == 1)
    {
        return (this->m_rightLen == 0);
    }
    else                    // 否则参数有问题
    {
        #ifdef REMIND
        std::cout <<"Empty()参数故障..." <<std::endl;
        #endif
        int in;
        std::cout <<"请重新输入参数index" <<std::endl;
        std::cout <<"-1 -= 判断左栈是否为空" <<std::endl;
        std::cout <<" 0 -= 判断总栈是否为空" <<std::endl;
        std::cout <<" 1 -= 判断右栈是否为空" <<std::endl <<std::endl;
        std::cin >>in;
        this->Empty(in);
    }
    return false;
}


// 函数名称：bool Full( ) const;
// 初始条件：顺序栈已经建立
// 操作结果：判断当前顺序栈已满
template <class ElemType>
bool SqDoubleStack<ElemType>::Full( ) const                 // 判断栈是否已满
{
    return (this->m_leftLen + this->m_rightLen == m_maxSize);
}

// 函数名称：bool Top(ElemType) const;
// 初始条件：顺序栈已经建立
// 操作结果：判断当前顺序栈已满
template <class ElemType>
bool SqDoubleStack<ElemType>::Top(int index/* = 0*/, ElemType &elem) const           // 返回栈顶数据
{
    // 调试信息
#ifdef DEBUG           // 如果宏定义了DEBUG, 执行一下语句
std::cout <<"Top..." <<std::endl;
#endif
    // 函数实现
    if(index == -1)
    {
        if(this->m_leftLen == 0)//this->Empty( ) == true // 如果当前顺序栈是空的
        {
            std::cout <<"当前左栈为空, 无法返回栈顶数据" <<std::endl;

            return false;       // 无法获取栈顶数据
        }
        else
        {
            elem = this->m_elems[m_leftLen-1];       // 用elems返回栈顶元素
            return true;        // 获取栈顶数据成功
        }
    }
    else if(index == 1)
    {
        if(this->m_rightLen == 0)//this->Empty( ) == true // 如果当前顺序栈是空的
        {
            std::cout <<"当前右栈为空, 无法返回栈顶数据" <<std::endl;
            return false;       // 无法获取栈顶数据
        }
        else
        {
            elem = this->m_elems[m_maxSize-m_rightLen];       // 用elems返回栈顶元素
            return true;        // 获取栈顶数据成功
        }
    }
    else
    {
        #ifdef REMIND
        std::cout <<"Top()参数故障..." <<std::endl;
        #endif
        int in;
        std::cout <<"请重新输入参数index" <<std::endl;
        std::cout <<"-1 -= 获取左栈栈顶元素" <<std::endl;
        std::cout <<" 1 -= 判断右栈栈顶元素" <<std::endl <<std::endl;
        std::cin >>in;
        this->Top(in, elem);
    }
    return false;
}

// 函数名称：bool Push(const ElemType &elem);
// 初始条件：顺序栈已经建立
// 操作结果：判断当前顺序栈已满
template <class ElemType>
bool SqDoubleStack<ElemType>::Push(int index, const ElemType &elem)    // 将数据elem入栈
{
    // 调试信息
#ifdef DEBUG           // 如果宏定义了DEBUG, 执行一下语句
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
        if(index == -1)
        {
            m_elems[m_leftLen++] = elem;
            return true;
        }
        else if(index == 1)
        {
            m_elems[m_maxSize-m_rightLen-1] = elem;
            m_rightLen++;
            return true;
        }
        else
        {
            #ifdef REMIND
            std::cout <<"Push()参数故障..." <<std::endl;
            #endif
            int in;
            std::cout <<"请重新输入参数index" <<std::endl;
            std::cout <<"-1 -= 元素压入左栈" <<std::endl;
            std::cout <<" 1 -= 元素压入右栈" <<std::endl <<std::endl;
            std::cin >>in;
            this->Push(in, elem);
        }
    }

    return false;
}

// 函数名称：bool Pop(ElemType &elem);
// 初始条件：顺序栈已经建立
// 操作结果：判断当前顺序栈已满
template <class ElemType>
bool SqDoubleStack<ElemType>::Pop(int index, ElemType &elem)          // 将数据elem出栈
{
    // 调试信息
#ifdef DEBUG           // 如果宏定义了DEBUG, 执行一下语句
std::cout <<"Pop..." <<std::endl;
#endif
    // 函数实现
    if(index == -1)
    {
        if(this->m_leftLen == 0)//this->Empty( ) == true // 如果当前顺序栈是空的
        {
            std::cout <<"当前左栈为空, 无法返回栈顶数据" <<std::endl;

            return false;       // 无法获取栈顶数据
        }
        else
        {
            elem = m_elems[--m_leftLen];       // 用elems返回栈顶元素
            return true;        // 获取栈顶数据成功
        }
    }
    else if(index == 1)
    {
        if(this->m_rightLen == 0) // 如果当前顺序栈是空的
        {
            std::cout <<"当前右栈为空, 无法返回栈顶数据" <<std::endl;
            return false;       // 无法获取栈顶数据
        }
        else
        {
            elem = this->m_elems[m_maxSize-m_rightLen];       // 用elems返回栈顶元素
            m_rightLen--;
            return true;        // 获取栈顶数据成功
        }
    }
    else
    {
        #ifdef REMIND
        std::cout <<"Top()参数故障..." <<std::endl;
        #endif
        int in;
        std::cout <<"请重新输入参数index" <<std::endl;
        std::cout <<"-1 -= 获取左栈栈顶元素" <<std::endl;
        std::cout <<" 1 -= 判断右栈栈顶元素" <<std::endl <<std::endl;
        std::cin >>in;
        this->Pop(in, elem);
    }

   return false;
}


// 函数名称：ElemType Pop( ) const;
// 初始条件：顺序栈已经建立, 并且插入数据
// 操作结果：将栈顶的数据返回
template <class ElemType>
ElemType SqDoubleStack<ElemType>::Pop(int index)
{
    ElemType elem;
    if(this->Pop(index, elem) == true)
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
    SqDoubleStack<EelmType> &operator=(const SqDoubleStack<ElemType> &copy);        // 重载赋值运算符
****************************************************************【实现】重载操作符函数**/
template <class ElemType>
SqDoubleStack<ElemType>& SqDoubleStack<ElemType>::operator=(const SqDoubleStack<ElemType> &copy)
{
    // 调试信息
#ifdef DEBUG           // 如果宏定义了DEBUG, 执行一下语句
std::cout <<"Pop..." <<std::endl;
#endif
    // 函数实现
    this->Init(copy.m_maxSize);     // 以赋值对象顺序栈的最大元素值初始化当前顺序栈的最大元素

    for(int curPosition = 0; curPosition < this->m_length; curPosition++)
    {       // 用curPosition遍历copy顺序栈的每个元素
        this->m_elems[curPosition] = copy.elems[curPosition];      // 同时将copy的每个元素赋给当前顺序栈
    }
}


/*

将数据24压入栈中
将数据46压入栈中
将数据30压入栈中
将数据17压入栈中
将数据33压入栈中
*/
#endif // SqDoubleStack_H_INCLUDED
