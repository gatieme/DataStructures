/********************************************************************************
CopyRight  : 2012-2013, HerBinUnversity, GatieMe
File Name  : PolyItem.h
Description: 多项式的项类实现文件
Author     : Gatie_Me
Version    : 版本声明
Data_Time  : 20112-8-4 15:36:24
********************************************************************************/

/********************************************************************************
History    :修改历史记录列表, 每条修改记录应包括修改日期、修改者以及修改内容
********************************************************************************/



#ifndef POLYITEM_H_INCLUDED
#define POLYITEM_H_INCLUDED


/// 多项数PolyItem声明部分
class PolyItem
{
  // 数据成员:
  public :
    double m_coef;        // 系数
    int m_expn;           // 指数

  // 类的基本函数成员
    PolyItem( );          // 无数据的构造函数
    PolyItem(double coef, int expn);          // 已知系数域和指针域建立结构
};



/// 多项数PolyItem定义部分
/**类的基本函数成员[实现]***********************************************
    PolyItem( );          // 无数据的构造函数
    PolyItem( );          // 已知系数域和指针域建立结构
***********************************************[实现]类的基本函数成员**/
// 函数名称：PolyItem( );
// 初始条件：当前结点未创建
// 操作结果：创建一个多项数的项
PolyItem::PolyItem( )      // 无数据的构造函数
{
    this->m_expn = -1;
}

// 函数名称：PolyItem( );
// 初始条件：当前结点未创建
// 操作结果：创建一个多项数的项
PolyItem::PolyItem(double coef, int expn)
{
    this->m_coef = coef;
    this->m_expn = expn;
}



#endif // POLYITEM_H_INCLUDED
