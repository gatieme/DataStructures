/********************************************************************************
CopyRight  : 2012-2013, HerBinUnversity, GatieMe
File Name  : SqQueue.h
Description: 顺序循环队列定义头文件
Author     : Gatie_Me
Version    : 版本声明
Data_Time  : 20112-9-27 19:1:24
********************************************************************************/

/********************************************************************************
History    :修改历史记录列表, 每条修改记录应包括修改日期、修改者以及修改内容
********************************************************************************/

#ifndef SqQueue_H_INCLUDED
#define SqQueue_H_INCLUDED



//#define DEBUG                     // 如果进行调试请将此注释打开
#define REMIND                    // 如果想输出提醒信息, 请将次注释打开
#define DEFAULT_SIZE  100

/// 顺序循环队列类模版
template <class ElemType>
class SqQueue        /// 带头结点
{
/*===========================【PUBLIC：公共接口】============================*/
  public :      // 公共接口
    // 顺序循环队列基本成员函数
    SqQueue(int size = DEFAULT_SIZE);               // 无参数的构造函数模版

    SqQueue(const SqQueue<ElemType> &copy);     // 复制构造函数模版

    virtual ~SqQueue( );      // 析构函数模版

    // 顺序循环队列特征成员函数
    int Length( ) const;            // 获取当前顺序循环队列的长度

    bool Empty( ) const;                // 判断当前顺序循环队列是否为空

    bool Full( ) const;                 // 判断当前顺序循环队列是否已满

    void Clear( );                      // 清空当前顺序循环队列

    bool GetHead(ElemType &elem) const;           // 返回队列顶数据

    bool InQueue(const ElemType &elem);    // 将数据elem入队列

    bool OutQueue(ElemType &elem);           // 将数据elem出队列

    ElemType OutQueue( );              // 将数据弹出并且返回

    // 重载操作符函数
    SqQueue<ElemType> &operator=(const SqQueue<ElemType> &copy);        // 重载赋值运算符
/*===========================【PUBLIC：公共接口】============================*/
///////////////////////////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////////
/*=========================【PROTECTED：保护成员】===========================*/
  protected :
    // 顺序循环队列数据成员
    int m_front/*队头*/, m_rear/*队尾*/;     // 队列顶指针
    int m_maxSize;                          // 数组最大元素个数
    ElemType *m_elems;                        // 元素存储空间


    // 赋辅助函数模版
    void Init( );               // 初始化队列
/*=========================【PROTECTED：：保护成员】=========================*/
};


/**辅助函数模版【实现】**************************************************************
    void Init(int size);        // 初始化当前队列信息
**************************************************************【实现】辅助函数模版**/
// 函数名称：void Init(int size)
// 初始条件：顺序循环队列信息需要初始化
// 操作结果：将顺序表各个数据元素初始化
template <class ElemType>
void SqQueue<ElemType>::Init( )         // 初始化当前线性队列信息
{
    this->m_front = this->m_rear = 0;       // 初始化当前队头和队尾都指向初始0下标
}


/**顺序循环队列类基本成员函数【实现】******************************************************
    SqQueue( );            // 顺序循环队列构造函数模版
    SqQueue(const SqQueue&copy);       // 顺序循环队列类复制构造函数
    virtual ~SqQueue( );                // 顺序循环队列析构函数模版
******************************************************【实现】顺序循环队列类基本成员函数**/
// 函数名称：SqQueue(int size = DEFAULT_SIZE)
// 初始条件：顺序循环队列对象未创建
// 操作结果：创建一个新的顺序循环队列对象空队列
template <class ElemType>
SqQueue<ElemType>::SqQueue(int size/* = DEFAULT_SIZE*/)         // 顺序循环队列构造函数模版
{
    this->m_elems =  new ElemType[size];    // 为队列开辟内存空间
    if(this->m_elems == NULL)
    {
        #ifdef REMIND
        std::cout <<"系统内存不足" <<std::endl;
        #endif
        exit(-1);
    }
    this->m_maxSize = size-1;           // 设置队列的最大元素值
    this->m_front = this->m_rear = 0;   // 初始化当前队头和队尾都指向初始0下标
}

// 函数名称：SqQueue(const SqQueue&copy)
// 初始条件：暂时空缺
// 操作结果：用一个顺序循环队列对象copy创建当前顺序循环队列对象
template <class ElemType>
SqQueue<ElemType>::SqQueue(const SqQueue<ElemType> &copy)     // 顺序循环队列类复制构造函数
{
    this->m_elems = new ElemType[copy.m_maxSize+1]; // 依照赋值队列的大小信息开辟空间

    if(this->m_elems == NULL)
    {
        #ifdef REMIND
        std::cout <<"系统内存不足" <<std::endl;
        #endif
        exit(-1);
    }

    this->m_maxSize = copy.m_maxSize;
    this->m_front = copy.m_front;
    this->m_rear = copy.m_rear;

    // 为队列的每个元素赋值
    for(int curPosition = this->m_front;
            curPosition != this->m_rear;
            curPosition = (curPosition+1)%(this->m_maxSize+1))
    {
        this->elems[curPosition] = this->copy.m_elems[curPosition];
    }
}


// 函数名称：virtual ~SqQueue( );
// 初始条件：暂时空缺
// 操作结果：销毁对象的内存空间
template <class ElemType>
SqQueue<ElemType>::~SqQueue( )      // 顺序循环队列析构函数模版
{
    delete[] this->m_elems;     // 删除内存空间
}


/**顺序循环队列类特征函数【实现】******************************************************
    int Length( ) const;                // 获取当前顺序循环队列的队列长度
    void Clear( );                      // 清空当前顺序循环队列
    bool Empty( ) const;                // 判断当前顺序循环队列是否为空队列
    bool OutQueue(ElemType) const;           // 返回队列顶数据
    bool InQueue(const ElemType &elem);    // 将数据elem入队列
    bool OutQueue(ElemType &elem);           // 将数据elem出队列
    ElemType OutQueue( ) const;              // 将数据弹出并且返回
******************************************************【实现】顺序循环队列类特征函数**/
// 函数名称：int Length( ) const;
// 初始条件：顺序循环队列已经建立
// 操作结果：返回当前顺序循环队列的队列长度
template <class ElemType>
int SqQueue<ElemType>::Length( ) const      // 获取当前顺序循环队列的队列长度
{
    // 调试信息
#ifdef DEBUG           // 如果宏定义了DEBUG, 执行一下语句
std::cout <<"Length..." <<std::endl;
#endif
    // 函数实现
    return (m_rear - m_front + m_maxSize + 1) % (m_maxSize+1);
}

// 函数名称：void Clear( );
// 初始条件：顺序循环队列已经建立
// 操作结果：返回当前顺序循环队列的队列长度
template <class ElemType>
void SqQueue<ElemType>::Clear( )            // 清空当前顺序循环队列
{
    // 调试信息
#ifdef DEBUG           // 如果宏定义了DEBUG, 执行一下语句
std::cout <<"Clear..." <<std::endl;
#endif
    // 函数实现
    m_front = m_rear = 0;

}


// 函数名称：bool Empty( ) const;
// 初始条件：顺序循环队列已经建立
// 操作结果：判断当前顺序循环队列是否为空队列
template <class ElemType>
bool SqQueue<ElemType>::Empty( ) const          // 判断当前顺序循环队列是否为空队列
{
    // 调试信息
#ifdef DEBUG           // 如果宏定义了DEBUG, 执行一下语句
std::cout <<"Empty..." <<std::endl;
#endif
    // 函数实现
    return (m_rear == m_front);
}


// 函数名称：bool Full( ) const;
// 初始条件：顺序循环队列已经建立
// 操作结果：判断当前顺序循环队列是否为空队列
template <class ElemType>
bool SqQueue<ElemType>::Full( ) const
{
    return (m_rear+1)%(m_maxSize + 1) == m_front;
}

// 函数名称：bool OutQueue(ElemType &elem);
// 初始条件：顺序循环队列已经建立
// 操作结果：判断当前顺序循环队列已满
template <class ElemType>
bool SqQueue<ElemType>::GetHead(ElemType &elem)  const       // 将数据elem出队列
{
    // 调试信息
#ifdef DEBUG           // 如果宏定义了DEBUG, 执行一下语句
std::cout <<"GetHead..." <<std::endl;
#endif
    // 函数实现
    if(this->Empty() == true)   // 如果当前队列是空的
    {
        #ifdef REMIND
        std::cout <<"当前顺序循环队列为空, 无法获取对头元素" <<std::endl;
        #endif
        return false;
    }
    else
    {
        elem = this->m_elems[m_front];
        return true;
    }
}

// 函数名称：bool OutQueue(ElemType) const;
// 初始条件：顺序循环队列已经建立
// 操作结果：判断当前顺序循环队列已满
template <class ElemType>
bool SqQueue<ElemType>::OutQueue(ElemType &elem)         // 返回队列顶数据
{
    // 调试信息
#ifdef DEBUG           // 如果宏定义了DEBUG, 执行一下语句
std::cout <<"OutQueue..." <<std::endl;
#endif
    // 函数实现
    if(this->Full( ) == true)   // 如果当前队列是空的
    {
        #ifdef REMIND
        std::cout <<"当前顺序循环队列已满, 无法获将当前元素入队" <<std::endl;
        #endif
        return false;
    }
    else
    {
        elem = this->m_elems[m_front];
        this->m_front = (m_front + 1) % (m_maxSize + 1);

        return true;
    }
}

// 函数名称：ElemType OutQueue( ) const;
// 初始条件：顺序循环队列已经建立, 并且插入数据
// 操作结果：将队列顶的数据返回
template <class ElemType>
ElemType SqQueue<ElemType>::OutQueue( )
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


// 函数名称：bool InQueue(const ElemType &elem);
// 初始条件：顺序循环队列已经建立
// 操作结果：判断当前顺序循环队列已满
template <class ElemType>
bool SqQueue<ElemType>::InQueue(const ElemType &elem)    // 将数据elem入队列
{
    // 调试信息
#ifdef DEBUG           // 如果宏定义了DEBUG, 执行一下语句
std::cout <<"InQueue..." <<std::endl;
#endif
    // 函数实现
    if(this->Full( ) == true)   // 如果当前队列是空的
    {
        #ifdef REMIND
        std::cout <<"当前顺序循环队列已满, 无法获将当前元素入队" <<std::endl;
        #endif
        return false;
    }
    else
    {
        this->m_elems[m_rear] = elem;
        this->m_rear = (m_rear + 1) % (m_maxSize + 1);

        return true;
    }
}
// 将数据弹出并且返回
/**重载操作符函数【实现】****************************************************************
    SqQueue<EelmType> &operator=(const SqQueue<ElemType> &copy);        // 重载赋值运算符
****************************************************************【实现】重载操作符函数**/
template <class ElemType>
SqQueue<ElemType>& SqQueue<ElemType>::operator=(const SqQueue<ElemType> &copy)
{
    // 调试信息
#ifdef DEBUG           // 如果宏定义了DEBUG, 执行一下语句
std::cout <<"OutQueue..." <<std::endl;
#endif
    // 函数实现
    this->m_elems = new ElemType[copy.m_maxSize + 1];
    if(m_elems == NULL)
    {
        #ifdef REMIND
        std::cout <<"系统内存不足" <<std::endl;
        #endif
        exit(-1);
    }

    this->m_maxSize = copy.m_maxSize;
    this->m_front = copy.m_front;
    this->m_rear = copy.m_rear;

    for(int curPosition = m_front;
            curPosition != m_rear;
            curPosition = (curPosition + 1) % (m_maxSize + 1))
    {
        m_elems[curPosition] = copy.m_elems[curPosition];
    }
}


#endif // SqQueue_H_INCLUDED
