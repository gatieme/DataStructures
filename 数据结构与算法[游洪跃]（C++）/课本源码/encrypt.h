// 文件路径名: encrypt\encrypt.h 
#ifndef __ENCRYPT_H__
#define __ENCRYPT_H__

#include "string.h"								// 串类
#include "lk_list.h"							// 线性链表

// 加密类
class Encrypt
{
private:
//  加密类的数据成员:
	String letters;								// 大小写字母表
	String map;									// 字母映射表

public:
// 加密类方法声明:
	Encrypt();									// 无参数的构造函数
	virtual ~Encrypt(){};						// 析构函数
	String Encode(const String &str);			// 返回文本串进行加密后的文本串
	String Decode(const String &str);			// 返回已加密的文本串进行解密后的文本串
};

// 加密类的实现部分
Encrypt::Encrypt()
// 操作结果：初始化数据成员
{
	letters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";	// 字母表
	map = "NgzQTCobmUHelkPdAwxfYIvrsJGnZqtcOBMuhELKpaDWXFyiVRjS";		// 字母映射表
}

String Encrypt::Encode(const String &str)
// 操作结果：返回文本串进行加密后的文本串
{
	LinkList<char> lk_tem;						// 临时线性链表,用于存储加密后的文本串

	for (int i = 0; i < str.Length(); i++)
	{	// 处理文本串str的每个字符
		int pos;								// 位置			
		for (pos = 0; pos < 52; pos++)
		{	// 查找字符str[i]在字符表中的位置
			if (str[i] == letters[pos])
			{	// 查找成功
				lk_tem.Insert(lk_tem.Length() + 1, map[pos]);	// 将加密后的字母存入lk_tem;
				break;							// 退出内层for循环
			}
		}
		if (pos == 52)
		{	// 查找失败
			lk_tem.Insert(lk_tem.Length() + 1, str[i]);	// 未被映射的字符不加以改变存入lk_tem;
		}
	}
	String result(lk_tem);						// 生成加密文本串
	return result;								// 返回加密文本串
}

String Encrypt::Decode(const String &str)
// 操作结果：返回加密文本串进行解密后的文本串
{
	LinkList<char> lk_tem;						// 临时线性链表,用于存储解密后的文本串

	for (int i = 0; i < str.Length(); i++)
	{	// 处理文本串str的每个字符
		int pos;								// 位置			
		for (pos = 0; pos < 52; pos++)
		{	// 查找字符str[i]在字母映射表中的位置
			if (str[i] == map[pos])
			{	// 查找成功
				lk_tem.Insert(lk_tem.Length() + 1, letters[pos]);	// 将解密后的字母存入膨胀lk_tem;
				break;							// 退出内层for循环
			}
		}
		if (pos == 52)
		{	// 查找失败
			lk_tem.Insert(lk_tem.Length() + 1, str[i]);	// 未被映射的字符不加以改变存入lk_tem;
		}
	}

	String result(lk_tem);						// 生成解密文本串
	return result;								// 返回解密文本串
}

#endif