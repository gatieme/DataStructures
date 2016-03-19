// 文件路径名: stat_char\stat_char.h
#ifndef __STAT_CHAR_H__
#define __STAT_CHAR_H__

#include "binary_sort_tree.h"				// 二叉排序树类

// 元素类
struct ElemType
{
// 数据成员:
	char ch;								// 字符
	int num;								// 出现次数

// 成员函数:
	ElemType(){};							// 无参数的构造函数 
	virtual ~ElemType(){};					// 析构函数
	ElemType(char c, int n = 1);			// 构造函数 
	operator char() const;					// 类类型转换函数
};

// 二叉树元素类及相关函数的实现部分
ElemType::ElemType(char c, int n)
// 操作结果：由字符c与出现次数n构造元素
{
	ch = c;									// 字符
	num = n;								// 出现次数
}

ElemType::operator char() const
// 操作结果：将数据元素类型转换为字符类型--类类型转换函数
{
	return ch;								// 返回字符
}

void DisplayElem(const ElemType &e)
// 操作结果: 显示元素
{
	cout << e.ch << ":" << e.num << endl;	// 显行元素所含的字符及出现次数
}

void StatChar(char *str)
// 操作结果: 统计并显示字符串str中各字符出现的次数
{
	BinarySortTree<ElemType, char> t;		// 二叉排序树
	for (unsigned int i = 0; i < strlen(str); i++)
	{	// 依次统计各字符出现的次数
		BinTreeNode<ElemType> *p = t.Search(str[i]);	// 查找字符str[i]
		if (p != NULL)
		{	// 查找成功
			p->data.num++;					// 字符出现次数自加1 
		}
		else
		{	// 查找失败
			ElemType e(str[i]);				// 生成元素
			t.Insert(e);					// 插入元素
		}
	}

	// 显示字符统计信息
	t.InOrder(DisplayElem);					// 按中序遍历显示出字符及出现次数
}

#endif





