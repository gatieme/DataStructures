/********************************************************************************
CopyRight  : 2012-2013, HerBinUnversity, GatieMe
File Name  :【00】ACM模版
Description:
Author     : Gatie_Me
Version    : 版本声明
Data_Time  : 20112-8-4 15:36:24
********************************************************************************/

/********************************************************************************
History    :修改历史记录列表, 每条修改记录应包括修改日期、修改者以及修改内容
********************************************************************************/

#ifndef POLYNOMIAL_H_INCLUDED
#define POLYNOMIAL_H_INCLUDED


#include "LinkList.h"
#include "PolyItem.h"


#define DEBUG       // 调试输出信息

/// 多项数的声明部分
class Polynomail
{
/*============================[PUBLIC-=>公共接口]============================*/
  protected:        // 保护成员
    LinkList<PolyItem> polyList;        // 多项式组成的线性表
/*============================[PUBLIC-=>公共接口]============================*/
///////////////////////////////////////////////////////////////////////////////
//
//
////////////////////////////////////////////////////////////////////////////////
/*===========================[PROTECTED-=>保护成员]===========================*/

  public  :// 公共接口
    // 多项式类基本成员函数[声明]
    Polynomail( );                // 无参数多项式类构造函数

    Polynomail(const Polynomail &copy); // 复制构造函数

    Polynomail(const LinkList<PolyItem> &copyLinkList); // 由多项式组成的线性表构造多项式

    ~Polynomail( );                // 析构函数

    // 类的特征函数[声明]
    int Length( ) const;                // 求多项式的项数

    bool IsZero( ) const;               // 判断多项式是否为0

    void SetZero( );                    // 将多项式置0

    void Display( );                    // 显示多项式

    void InsItem(const PolyItem &item); // 插入一项

    Polynomail operator+(const Polynomail &polynomail) const; // 加法运算符重载

    Polynomail operator-(const Polynomail &Polynomail) const; // 减法运算符

    Polynomail operator*(const Polynomail &Polynomail) const; // 乘法运算符

    // 重载运算符函数
    Polynomail &operator=(const Polynomail &copy);      // 赋值运算符重载

    Polynomail &operator=(const LinkList<PolyItem> &copyLinkList);  // 赋值运算符重载
/*===========================[PROTECTED-=>保护成员]]==========================*/
};





/// 多项式类Polynomial定义部分
/**多项式类基本成员函数[实现]*************************************************************
    Polynomail( );                // 无参数多项式类构造函数
    Polynomail(const Polynomail &copy); // 复制构造函数
    Polynomail(const LinkList<PolyItem> &copyLinkList); // 由多项式组成的线性表构造多项式
    ~Polynomail( );                // 析构函数
*************************************************************[实现]多项式类基本成员函数**/
// 函数名称：Polynomail( );                // 无参数多项式类构造函数
// 初始条件：当前多项式未建立
// 操作结果：建立一个空的多项式信息
Polynomail::Polynomail( )                // 无参数多项式类构造函数
: polyList( )       // 直接建立一个空的多项式链表
{
}

// 函数名称：Polynomail(const Polynomail &copy);
// 初始条件：当前多项式未建立
// 操作结果：建立一个与参数多项式完全相同的多项式
Polynomail::Polynomail(const Polynomail &copy)      // 复制构造函数
: polyList(copy.polyList)                // 直接调用对象成员的复制构造函数
{
}

// 函数名称：Polynomail(const LinkList<PolyItem> &copyLinkList); // 由多项式组成的线性表构造多项式
// 初始条件：当前多项式未建立
// 操作结果：建立一个空的多项式信息
Polynomail::Polynomail(const LinkList<PolyItem> &copyLinkList)
: polyList(copyLinkList)
{
}

// 函数名称：~Polynomail( );
// 初始条件：当前多项式未建立
// 操作结果：建立一个空的多项式信息
Polynomail::~Polynomail( )            // 析构函数
{
}



/**类的特征函数[实现]**********************************************************************
    int Length( ) const;                // 求多项式的项数
    bool IsZero( ) const;               // 判断多项式是否为0
    void SetZero( );                    // 将多项式置0
    void Display( );                    // 显示多项式
    void InsItem(const PolyItem &item); // 插入一项
    Polynomail operator+(const Polynomail &polynomail) const; // 加法运算符重载
    Polynomail operator-(const Polynomail &Polynomail) const; // 减法运算符
    Polynomail operator*(const Polynomail &Polynomail) const; // 乘法运算符
**********************************************************************[实现]类的特征函数**/
// 函数名称：int Length( ) const;
// 初始条件：链式多项式已经建立
// 操作结果：返回链式多项式的长度
int Polynomail::Length( ) const           // 求多项式的项数
{
    return polyList.Length( );      // 返回线性多项式的表长
}


// 函数名称：bool IsZero( ) const;               // 判断多项式是否为0
// 初始条件：链式多项式已经建立
// 操作结果：如果多项式为0, 返回True, 否则为返回False
bool Polynomail::IsZero( ) const        // 判断多项式是否为0
{
#ifdef DEBUG
std::cout <<"InZero..." <<std::endl;
#endif
    int length = this->Length( );   // 先计算当前多项式的项数

    if(length == 0)
    {
        std::cout <<"当前多项式为空, 无法判断他是否为0" <<std::endl;
        return false;
    }

    PolyItem tempItem;
    for(int curPosition = 1; curPosition <= length; curPosition++)
    {
        polyList.GetElem(curPosition, tempItem);        // 取出当前第i个结点的信息
        if(tempItem.m_coef != 0)                // 如果当前项的系数不为0
        {
            return false;        // 则这个多项式必定不为0
        }
    }

    return true;                // 当一直到循环结束, 都没有返回, 则次多项式的每一项系数都为0
    // 即次多项式值为0
}


/**重载运算符函数[实现]********************************************************************
    Polynomail &operator=(const Polynomail &copy);      // 赋值运算符重载
    Polynomail &operator=(const LinkList<PolyItem> &copyLinkList);  // 赋值运算符重载
********************************************************************[实现]重载运算符函数**/
// 函数名称：Polynomail &operator=(const Polynomail &copy);
// 初始条件：
// 操作结果：
Polynomail& Polynomail::operator=(const Polynomail &copy)       // 赋值运算符重载
{

}



#endif // POLYNOMIAL_H_INCLUDED
