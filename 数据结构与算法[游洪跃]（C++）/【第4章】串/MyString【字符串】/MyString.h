/********************************************************************************
CopyRight  : 2012-2013, HerBinUnversity, GatieMe
File Name  : MyString.h
Author     : Gatie_Me
Version    : 版本声明
Data_Time  : 20112-9-27 19:1:24
********************************************************************************/

/********************************************************************************
History    :修改历史记录列表, 每条修改记录应包括修改日期、修改者以及修改内容
********************************************************************************/

#ifndef MYSTRING_H_INCLUDED
#define MYSTRING_H_INCLUDED



#include <cstring>
#include <cassert>
#include "LinkList.h"
#include <iostream>

//#define DEBUG                     // 如果进行调试请将此注释打开
#define REMIND                    // 如果想输出提醒信息, 请将次注释打开


/// 我的字符串声明部分
class MyString
{
/*===========================【PUBLIC：公共接口】============================*/
/*===========================【PUBLIC：公共接口】============================*/
//friend istream &operator>>(istream &in, MyString &rhs)          //重载输入操作符
//{
//    std::cout <<"Please enter your string\nstring=" <<std::endl; //输入信息提示
//    in >>rhs.m_length;           //输入字符串【从字符串输入流中提取strAdd所指向的字符串】
//    rhs.m_length = strlen(rhs.m_length);  //确定字符串大小
//
//    return in;           //流信息返回
//}
//
//friend ostream &operator<<(ostream &out, const MyString &rhs)    //重载输出函数
//{
//   // out <<"the string is " <<endl;
//    out <<rhs.m_strVal;   //输出字符串【将strAdd所指向的字符串插入流】
//
//    return out;           //流信息返回
//}
///////////////////////////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////////
/*===========================【PUBLIC：公共接口】============================*/
  public :      // 公共接口
    // 字符串类基本成员函数
    MyString( );              // 默认构造函数

    MyString(const LinkList<char> &copy);   //带参数构造函数：用一个字符串链表初始化当前串值

    MyString(const char* copy);       // 带参数构造函数：用一个指针指向字符串初始化当前串值
    MyString(const MyString &copy);   // 赋值构造函数：用一个串对象初始化当前串对象

    MyString( const MyString &rhs, unsigned int pos, unsigned int n );   //将对象rhs中的串从位置pos开始取n个字符,用来初始化MyString类的对象
    MyString( const char *str, unsigned int pos, unsigned int n );       //将指针str所指向的字符串从位置pos开始取n个字符用来初始化MyString类的对象

    MyString( const MyString &rhs, unsigned int n );         //用对象rhs的前n个对象初始化MyString对象
    MyString( const char *str, unsigned int n );     //用指针str所指向的字符串的前n个字符初始化MyString类的对象

    MyString( const char op, unsigned int n );         //将参数op重复n次初始化MyString类对象


    virtual ~MyString( ){  delete[] m_strVal;  }               // 虚析构函数

    // 字符串类的特性函数
    void GetStr( )
    {
        m_strVal = new char[81];
        std::cin >>m_strVal;
        m_length = strlen(m_strVal);
    }

    void PutStr( ) const
    {
        std::cout <<m_strVal <<std::endl;
    }
    int Length( ) const;                      // 计算串长

    bool Empty( ) const;                        // 判断当前字符串是不是空串

    const char* CStr( ) const;      // 将串转换为C风格串, 等价于‘*’操作符
    //特殊操作符重载：*, [], =
    char* operator*( );      //【重载指针操作符】==*rhs可以直接访问MyString类对象的地址

    char& operator[]( int index ) const;    //【重载[]操作符】rhs[n]指针访问第n-1个字符

    MyString& operator=( const MyString &rhs );   //【重载=操作符】rhs1=rhs2直接用另一个类对象rhs2为rhs1赋值
    MyString& operator=( const char *str );      //【重载=操作符】rhs=str直接用指针str所指向的字符串为rhs赋值

    //重载运算符：+, +=
    MyString operator+( const MyString &rhs ) const;          //【重载+操作符】rhs1 + rhs2
    MyString operator+( const char *str ) const;              //【重载+操作符】rhs + str

    MyString& operator+=( const MyString &rhs );         //【重载+=操作符】rhs1 += rhs2
    MyString& operator+=( const char *str );         //【重载+=操作符】rhs += str

    //重载关系运算符：==, != , >, <, >=, <=
    bool operator==( const MyString &rhs ) const;          //【重载==操作符】rhs1 == rhs2
    bool operator==( const char *str ) const;              //【重载==操作符】rhs == str

    bool operator!=( const MyString &rhs ) const;          //【重载==操作符】rhs1 != rhs2
    bool operator!=( const char *str ) const;              //【重载==操作符】rhs != str

    bool operator>( const MyString &rhs ) const;         //【重载>操作符】rhs1 > rhs2
    bool operator>( const char *str ) const;         //【重载>操作符】rhs > str

    bool operator<( const MyString &rhs ) const;          //【重载<操作符】rhs1 < rhs2
    bool operator<( const char *str ) const;              //【重载<操作符】rhs < str

    bool operator>=( const MyString &rhs ) const;         //【重载>=操作符】rhs1 >= rhs2
    bool operator>=( const char *str ) const;         //【重载>=操作符】rhs >= str

    bool operator<=( const MyString &rhs ) const;         //【重载<=操作符】rhs1 <= rhs2
    bool operator<=( const char *str ) const;         //【重载<=操作符】rhs <= str
/*===========================【PUBLIC：公共接口】============================*/
///////////////////////////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////////
/*=========================【PROTECTED：保护成员】===========================*/
  protected :   // 保护数据成员
    mutable char *m_strVal;     // 串值：字符串指针
    int m_length;               // 串长：字符串长度
/*=========================【PROTECTED：：保护成员】=========================*/
};


/// 我的字符串MyString实现部分

/**字符串类基本成员函数【实现】***************************************************************
    MyString( );              // 默认构造函数
    MyString(const LinkList<char> &copy);   //带参数构造函数：用一个字符串链表初始化当前串值
    MyString(const char* copy);       // 带参数构造函数：用一个指针指向字符串初始化当前串值
    MyString(const MyString &copy);   // 赋值构造函数：用一个串对象初始化当前串对象
    MyString( const MyString &rhs, unsigned int pos, unsigned int n );   //将对象rhs中的串从位置pos开始取n个字符,用来初始化MyString类的对象
    MyString( const char *str, unsigned int pos, unsigned int n );       //将指针str所指向的字符串从位置pos开始取n个字符用来初始化MyString类的对象
    MyString( const MyString &rhs, unsigned int n );         //用对象rhs的前n个对象初始化MyString对象
    MyString( const char *str, unsigned int n );     //用指针str所指向的字符串的前n个字符初始化MyString类的对象
    MyString( const char op, unsigned int n );         //将参数op重复n次初始化MyString类对象
    virtual ~MyString( );               // 虚析构函数
***************************************************************【实现】字符串类基本成员函数**/

// 函数名称：MyString( );
// 初始条件：字符串未建立
// 操作结果：建立一个空的字符串
MyString::MyString( )       // 默认构造函数
{
//    this->m_strVal = new char[1];
//    if(this->m_strVal == NULL)      // 如果未正确开辟空间
//    {
//        std::cout <<"内存不足" <<std::endl;
//        exit(-1);       // 程序退出
//    }
//    else
//    {
//       // this->m_strVal = "\0";
//        strcpy(this->m_strVal, "\0");   // 空串的信息为字符串结束标志
//        this->m_length = 0;         // 空串的长度为0
//    }
      this->m_strVal = NULL;
      this->m_length = 0;
}

// 函数名称：MyString::MyString(const LinkList<char> &copy)
// 初始条件：字符串未建立
// 操作结果：依据参数字符链表, 创建一个新的字符串对象
MyString::MyString(const LinkList<char> &copy)   //带参数构造函数：用一个字符串链表初始化当前串值
{
    m_strVal = new char[copy.Length()+1];     // 开辟内存空间

    if(this->m_strVal == NULL)      // 如果未正确开辟空间
    {
        std::cout <<"内存不足" <<std::endl;
        exit(-1);       // 程序退出
    }
    else        // 否则开辟内存失败
    {
        char temp;
        int cur;
        for(cur = 0; cur < copy.Length(); cur++)
        {
            copy.GetElem(cur + 1, temp);    // 将字符链表中的第cur个元素取出来
            *(m_strVal + cur) = temp;       // 将字符放入开辟的内存中合适的位置
        }
        *(m_strVal + cur) = '\0';         // 添加字符串结束标志
    }
}


// 函数名称：MyString::MyString(const char* copy)
// 初始条件：字符串未建立
// 操作结果：用一个指针指向字符串初始化当前串值
MyString::MyString(const char* copy)       // 带参数构造函数：用一个指针指向字符串初始化当前串值)
{
    m_strVal = new char[strlen(copy)+1];     // 开辟内存空间

    if(this->m_strVal == NULL)      // 如果未正确开辟空间
    {
        std::cout <<"内存不足" <<std::endl;
        exit(-1);       // 程序退出
    }
    else
    {
        strcpy(this->m_strVal, copy);  // 复制新串的数据对象
        this->m_length = strlen(copy);         // 确定新串的长度
    }
}

// 函数名称：MyString(const MyString &copy)
// 初始条件：字符串未建立
// 操作结果：用一个指针指向字符串初始化当前串值
MyString::MyString(const MyString &copy)   // 复制构造函数：用一个串对象初始化当前串对象
{
    m_strVal = new char[copy.m_length + 1];     // 开辟内存空间

    if(this->m_strVal == NULL)      // 如果未正确开辟空间
    {
        std::cout <<"内存不足" <<std::endl;
        exit(-1);       // 程序退出
    }
    else
    {
        strcpy(this->m_strVal, copy.m_strVal);      // 复制新串的数据对象
        this->m_length = copy.m_length;     // 确定新串的长度
    }
}


// 函数名称：MyString( const MyString &rhs, unsigned int pos, unsigned int n )
// 初始条件：字符串未建立
// 操作结果：将对象rhs中的串从位置pos开始取n个字符,用来初始化MyString类的对象
MyString::MyString( const MyString &rhs, unsigned int pos, unsigned int n )   //将对象rhs中的串从位置pos开始取n个字符,用来初始化MyString类的对象
{
    this->m_strVal = new char[n+1];
    if(this->m_strVal == NULL)      // 如果未正确开辟空间
    {
        std::cout <<"内存不足" <<std::endl;
        exit(-1);       // 程序退出
    }
    else
    {
        unsigned int i = pos, j = 0;

        while(j < n)        // 循环控制赋值所需的n个字符
        {
            this->m_strVal[j++] = *(rhs.m_strVal+i++);
        }
        m_strVal[j] = '\0';   // 字符串结束标志
        this->m_length = n;
    }
/*  char *pStart = rhs.strAdd + pos;           //赋值开始位置
    char *pEnd = rhs.m_strVal + pos + n;         //赋值结束位置

    m_strVal = new char[n+1];             //开辟空间
    m_length = n;                           //确定串的长度

    char *pThis = strAdd;               //保存目的串位置
    while( (pStart < pEnd) &&  *pThis++ = *pStart++ );      //循环控制赋值同时赋值
    *(pThis) = '\0';
*/
}


// 函数名称：MyString( const char *str, unsigned int pos, unsigned int n )
// 初始条件：字符串未建立
// 操作结果：将指针str所指向的字符串从位置pos开始取n个字符用来初始化MyString类的对象
MyString::MyString( const char *str, unsigned int pos, unsigned int n )       //将指针str所指向的字符串从位置pos开始取n个字符用来初始化MyString类的对象
{
    this->m_strVal = new char[n+1];
    if(this->m_strVal == NULL)      // 如果未正确开辟空间
    {
        std::cout <<"内存不足" <<std::endl;
        exit(-1);       // 程序退出
    }
    else
    {
        unsigned int i = pos, j = 0;

        while(j < n)        // 循环控制赋值所需的n个字符
        {
            this->m_strVal[j++] = *(str+i++);
        }
        m_strVal[j] = '\0';   // 字符串结束标志
        this->m_length = n;
    }
}


// 函数名称：(const MyString &rhs, unsigned int n)
// 初始条件：字符串未建立
// 操作结果：用对象rhs的前n个对象初始化MyString对象
MyString::MyString(const MyString &rhs, unsigned int n)         //用对象rhs的前n个对象初始化MyString对象
{
    this->m_strVal = new char[n+1];
    if(this->m_strVal == NULL)      // 如果未正确开辟空间
    {
        std::cout <<"内存不足" <<std::endl;
        exit(-1);       // 程序退出
    }
    else
    {
        unsigned int i = 0;

        while(i < n)        // 循环控制赋值所需的n个字符
        {
            this->m_strVal[i] = *(rhs.m_strVal+i);
            i++;
        }
        m_strVal[i] = '\0';   // 字符串结束标志

        this->m_length = n;
    }
}

// 函数名称：MyString( const char *str, unsigned int pos, unsigned int n )
// 初始条件：字符串未建立
// 操作结果：将指针str所指向的字符串从位置pos开始取n个字符用来初始化MyString类的对象
MyString::MyString( const char *str, unsigned int n)     //用指针str所指向的字符串的前n个字符初始化MyString类的对象
{
    this->m_strVal = new char[n+1];
    if(this->m_strVal == NULL)      // 如果未正确开辟空间
    {
        std::cout <<"内存不足" <<std::endl;
        exit(-1);       // 程序退出
    }
    else
    {
        unsigned int i = 0;

        while(i < n)        // 循环控制赋值所需的n个字符
        {
            this->m_strVal[i] = *(str+i);
            i++;
        }
        m_strVal[i] = '\0';   // 字符串结束标志

        this->m_length = n;
    }
}

// 函数名称：MyString( const char op, unsigned int n )
// 初始条件：字符串未建立
// 操作结果：将参数op重复n次初始化MyString类对象
MyString::MyString( const char op, unsigned int n )         //将参数op重复n次初始化MyString类对象
{
    unsigned int i  = 0;

    this->m_strVal = new char[n+1];
    if(this->m_strVal == NULL)      // 如果未正确开辟空间
    {
        std::cout <<"内存不足" <<std::endl;
        exit(-1);       // 程序退出
    }
    else
    {
        while(i < n)
        {
            this->m_strVal[i++] = op;
        }
        m_strVal[i] = '\0';

        m_length = n;
    }
}

/**字符串类的特性函数【实现】*****************************************************************
    int Length( ) const;                      // 计算串长

    bool Empty( ) const;                        // 判断当前字符串是不是空串

    const char* CStr( ) const;      // 将串转换为C风格串, 等价于‘*’操作符
*****************************************************************【实现】字符串类的特性函数**/
// 函数名称：int Length( ) const;
// 初始条件：字符串就已经建立
// 操作结果：返回当前字符串的串长
int MyString::Length( ) const
{
    return m_length;
}

// 函数名称：bool Empty( ) const;
// 初始条件：字符串对象已经建立
// 操作结果：判断当前字符串是否为空
bool MyString::Empty( ) const
{
    return m_length == 0;
}

// 函数名称：bool Empty( ) const;
// 初始条件：字符串对象已经建立
// 操作结果：将串转换为C风格串, 等价于‘*’操作符
const char* MyString::CStr( ) const
{
    return m_strVal;        // 返回字符串的地址指针
}


/**特殊操作符重载：*, [], =【实现】***********************************************************
    const char* operator*( ) const;      //【重载指针操作符】==*rhs可以直接访问MyString类对象的地址
    char& operator[]( int index ) const;    //【重载[]操作符】rhs[n]指针访问第n-1个字符
    MyString& operator=( const MyString &rhs );   //【重载=操作符】rhs1=rhs2直接用另一个类对象rhs2为rhs1赋值
    MyString& operator=( const char *str );      //【重载=操作符】rhs=str直接用指针str所指向的字符串为rhs赋值
    //重载运算符：+, +=
    MyString operator+( const MyString &rhs ) const;          //【重载+操作符】rhs1 + rhs2
    MyString operator+( const char *str ) const;              //【重载+操作符】rhs + str
    bool operator+=( const MyString &rhs );         //【重载+=操作符】rhs1 += rhs2
    bool operator+=( const char *str );         //【重载+=操作符】rhs += str
    //重载关系运算符：==, != , >, <, >=, <=
    bool operator==( const MyString &rhs ) const;          //【重载==操作符】rhs1 == rhs2
    bool operator==( const char *str ) const;              //【重载==操作符】rhs == str
    bool operator!=( const MyString &rhs ) const;          //【重载==操作符】rhs1 != rhs2
    bool operator!=( const char *str ) const;              //【重载==操作符】rhs != str
    bool operator>( const MyString &rhs ) const;         //【重载>操作符】rhs1 > rhs2
    bool operator>( const char *str ) const;         //【重载>操作符】rhs > str
    bool operator<( const MyString &rhs ) const;          //【重载<操作符】rhs1 < rhs2
    bool operator<( const char *str ) const;              //【重载<操作符】rhs < str
    bool operator>=( const MyString &rhs ) const;         //【重载>=操作符】rhs1 >= rhs2
    bool operator>=( const char *str ) const;         //【重载>=操作符】rhs >= str
    bool operator<=( const MyString &rhs ) const;         //【重载<=操作符】rhs1 <= rhs2
    bool operator<=( const char *str ) const;         //【重载<=操作符】rhs <= str
***********************************************************【实现】特殊操作符重载：*, [], =**/

/// 重载特殊运算符*, [], =
// 函数名称：const char* operator*( );
// 初始条件：字符串就已经建立
// 操作结果：重载‘*’操作符, 将当前操作符转换为C风格的串
char* MyString::operator*( )
{
    return m_strVal;
}


// 函数名称：char& operator[]( int index );
// 初始条件：字符串就已经建立
// 操作结果：[重载[]操作符]-=> rhs[n]指针访问第n-1个字符
char& MyString::operator[](int index) const
{
    assert(index >= 0 && index < this->m_length);   // 判断索引是否合法

    return m_strVal[index];     // 返回当前索引的元素
}


// 函数名称：MyString& operator=( const MyString &rhs );
// 初始条件：字符串就已经建立
// 操作结果：【重载=操作符】rhs1=rhs2直接用另一个类对象rhs2为rhs1赋值
MyString& MyString::operator=(const MyString &rhs)
{
    if(this == &rhs)    // 判断当前源目的串是否为同一目标
    {
        return (*this);     // 是同一目标只需要想直接返回
    }
    else
    {
        if(m_strVal != NULL)
        {
            delete[] m_strVal;
        }
        m_strVal = new char[rhs.m_length+1];
        strcpy(m_strVal, rhs.m_strVal);
        m_length = rhs.m_length;
    }

    return (*this);
}

// 函数名称：MyString& operator=( const char *str );
// 初始条件：字符串就已经建立
// 操作结果：【重载=操作符】rhs=str直接用指针str所指向的字符串为rhs赋值
MyString& MyString::operator=(const char *str)
{
    if(m_strVal != NULL)
    {
        delete[] m_strVal;
    }
    m_strVal = new char[strlen(str)+1];
    strcpy(m_strVal, str);
    m_length = strlen(str);

    return (*this);
}

//重载运算符：+, +=
MyString MyString::operator+(const MyString &rhs) const          //【重载+操作符】rhs1 + rhs2
{
    MyString strResult;

    if(rhs.m_strVal == NULL)    // 如果附加串为空
    {
        strResult = rhs;    // 结果串就是源串
    }
    else if(m_strVal == NULL)   // 否则附加串不为空, 但是源串为空, +的结果是附加串
    {
        strResult = rhs;
    }
    else
    {
//        strResut = *this;
//        strResult += rhs;
          strResult.m_strVal = new char[this->m_length+rhs.m_length+1];   // 删除结果串的空间
          strcpy(strResult.m_strVal, this->m_strVal);
          strcat(strResult.m_strVal, rhs.m_strVal);
    }

    return strResult;
}

MyString MyString::operator+(const char *str) const             //【重载+操作符】rhs + str
{
    MyString strResult;

    if(str == NULL)    // 如果附加串为空
    {
        strResult = *this;    // 结果串就是源串
    }
    else if(m_strVal == NULL)   // 否则附加串不为空, 但是源串为空, +的结果是附加串
    {
        strResult = str;
    }
    else
    {
//        strResut = *this;
//        strResult += rhs;
          strResult.m_strVal = new char[this->m_length+strlen(str)+1];   // 删除结果串的空间
          strcpy(strResult.m_strVal, this->m_strVal);
          strcat(strResult.m_strVal, str);
    }

    return strResult;
}


MyString& MyString::operator+=(const MyString &rhs)         //【重载+=操作符】rhs1 += rhs2
{
    if(rhs.m_strVal != NULL)    // 附加字符串不问空
    {



        if(this->m_strVal == NULL)  // 如果源串为空
        {
            m_strVal = new char[rhs.m_length+1];
            strcpy(m_strVal, rhs.m_strVal);
            this->m_length = rhs.m_length;
        }
        else
        {
            char *temp = new char[m_length+1];
            strcpy(temp, this->m_strVal);
            delete[] m_strVal;
            this->m_strVal = new char[m_length+rhs.m_length+1];
            strcpy(m_strVal, temp);
            strcat(m_strVal, rhs.m_strVal);
            this->m_length += rhs.m_length;
        }
    }

    return (*this);
}


MyString& MyString::operator+=( const char *str )         //【重载+=操作符】rhs += str
{
    if(str != NULL)    // 附加字符串不问空
    {

        if(this->m_strVal == NULL)  // 如果源串不为空需要保存
        {
            m_strVal = new char[strlen(str)+1];
            strcpy(m_strVal, m_strVal);
            this->m_length = strlen(str);
        }
        else
        {

            char *temp = new char[m_length+1];
            strcpy(temp, this->m_strVal);
            delete[] m_strVal;
            this->m_strVal = new char[m_length+strlen(str)+1];
            strcpy(m_strVal, temp);
            strcat(m_strVal, str);
        }
    }

    return (*this);
}


bool MyString::operator==( const MyString &rhs ) const          //【重载==操作符】rhs1 == rhs2
{
    return (strcmp(m_strVal, rhs.m_strVal) == 0);
}
bool MyString::operator==( const char *str ) const              //【重载==操作符】rhs == str
{
    return (strcmp(m_strVal, str) == 0);
}
bool MyString::operator!=( const MyString &rhs ) const          //【重载==操作符】rhs1 != rhs2
{
    return !(*this == rhs);
}
bool MyString::operator!=( const char *str ) const              //【重载==操作符】rhs != str
{
    return !(*this == str);
}

bool MyString::operator>( const MyString &rhs ) const         //【重载>操作符】rhs1 > rhs2
{
    return (strcmp(m_strVal, rhs.m_strVal) > 0);
}


bool MyString::operator>( const char *str ) const         //【重载>操作符】rhs > str
{
    return (strcmp(m_strVal, str) > 0);
}

bool MyString::operator<( const MyString &rhs ) const          //【重载<操作符】rhs1 < rhs2
{
    return (strcmp(m_strVal, rhs.m_strVal) < 0);
}


bool MyString::operator<( const char *str ) const              //【重载<操作符】rhs < str
{
    return (strcmp(m_strVal, str) < 0);
}
bool MyString::operator>=( const MyString &rhs ) const         //【重载>=操作符】rhs1 >= rhs2
{
    return (strcmp(m_strVal, rhs.m_strVal) >= 0);
}


bool MyString::operator>=( const char *str ) const         //【重载>=操作符】rhs >= str
{
    return (strcmp(m_strVal, str) >= 0);
}
bool MyString::operator<=( const MyString &rhs ) const         //【重载<=操作符】rhs1 <= rhs2
{
    return (strcmp(m_strVal, rhs.m_strVal) <= 0);
}

bool MyString::operator<=( const char *str ) const         //【重载<=操作符】rhs <= str
{
    return (strcmp(m_strVal, str) <= 0);
}

#endif // MYSTRING_H_INCLUDED
