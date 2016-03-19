/********************************************************************************
CopyRight  : 2012-2013, HerBinUnversity, GatieMe
File Name  : MyHeadFile.h
Description: 实用程序软件包
Author     : Gatie_Me
Version    : Copyright 2012
Data_Time  : 20112-8-4 15:36:24
********************************************************************************/

/********************************************************************************
History    :修改历史记录列表, 每条修改记录应包括修改日期、修改者以及修改内容
********************************************************************************/



#ifndef __ERROR_H__				// 如果没有定义__UTILITY_H__
#define __ERROR_H__				// 那么定义__UTILITY_H__

#include <cstring>



// 通用异常类
#define MAX_ERROR_MESSAGE_LEN 100
class Error
{
  private:
// 数据成员
	char m_message[MAX_ERROR_MESSAGE_LEN];// 异常信息
    //std::string m_message;
  public:
//  方法声明
	Error(char *message);//char *message = "一般性异常!");	// 构造函数
	~Error( ){ };					// 析构函数
	void Show( ) const;					// 显示异常信息
};


// 通用异常类的实现部分
// 操作结果：由mes构构通用异常对象
Error::Error(char *message)
{
	strcpy(m_message, message);				// 复制异常信息
//	m_message = message;
}


// 操作结果：显示异常信息
void Error::Show( )const
{
	std::cout <<m_message <<std::endl;			// 显示异常信息
}




#endif     //结束__MYHEADFILE_H__编译
