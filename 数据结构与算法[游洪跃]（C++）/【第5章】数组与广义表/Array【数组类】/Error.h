/**
******************************************************************************
*  Copyright  : 2012-2013, HerBinUnversity, GatieMe                          *
*  File Name  : Error.h                                                      *
*  Description: 异常处理类                                               *
*  Author     : Gatie_Me                                                     *
*  Version    : Copyright 2012 JULY_CITY                                     *
*  Data_Time  : 25/10/12 17:20                                              *
*  Content    : 数据结构与算法（C++）版书上源码                             *
******************************************************************************
**/

#ifndef ERROR_H_INCLUDED
#define ERROR_H_INCLUDED


// 通用异常类
#define MAX_ERROR_MESSAGE_LEN 81

class Error
{
  private:
// 数据成员
	char m_message[MAX_ERROR_MESSAGE_LEN];// 异常信息

  public:
//  方法声明
	Error(char *message = "一般性异常!");	// 构造函数

	~Error( ){ };					// 析构函数

	void Show( ) const;					// 显示异常信息
};


/// 通用异常类的实现部分
/**Error类基本成员函数[实现]**********************************
	Error(char *message = "一般性异常!");	// 构造函数
	~Error( ){ };					// 析构函数
	void Show( ) const;					// 显示异常信息
**********************************[实现]Error类基本成员函数**/
// 操作结果：由mes构构通用异常对象
Error::Error(char *mes)
{
	strcpy(m_message, mes);				// 复制异常信息
}


// 操作结果：显示异常信息
void Error::Show()const
{
	std::cout <<m_message <<std::endl;			// 显示异常信息
}


#endif // ERROR_H_INCLUDED
