// 文件路径名:cstring\cstring.h
#ifndef __CString_H__
#define __CString_H__

#include "lk_list.h"							// 线性链表

// 串类
class CString 
{
protected:
//  串实现的数据成员:
	mutable char *strVal;						// 串值
	int length;									// 串长	

public:                           
//  抽象数据类型方法声明及重载编译系统默认方法声明:
	CString();									// 构造函数 
	virtual ~CString();							// 析构函数
	CString(const CString &copy);				// 复制构造函数
	CString(const char *copy);					// 从C风格串转换的构造函数
	CString(LinkList<char> &copy);				// 从线性表转换的构造函数
	int Length() const;							// 求串长度			 
	bool Empty() const;							// 判断串是否为空
	CString &operator =(const CString &copy);	// 赋值语句重载
	const char *CStr() const;					// 将串转换成C风格串
	char &CString::operator [](int pos) const;	// 重载下标运算符
};

// 串相关操作
CString operator +(const CString &strFirst, const CString &strSecond);
	// 重载加法运算符+
ostream &operator <<(ostream &outStream, const CString &outStr);
	// 重载运算符<<
istream &operator >>(istream &inStream, CString &inStr);
	// 重载运算符>>
CString Read(istream &input);					// 从输入流读入串
CString Read(istream &input, char &terminalChar);
	// 从输入流读入串，并用terminalChar返回串结束字符
void Write(CString &s);							// 输出串
void Concat(CString &addTo, const CString &addOn);
	// 将串addOn连接到addTo串的后面
void Copy(CString &copy, const CString &original);
	// 将串original复制到串copy
void Copy(CString &copy, const CString &original, int n);
	// 将串original复制n个字符到串copy 
int Index(const CString &target, const CString &pattern, int pos = 0);
	// 查找模式串pattern第一次在目标串target中从第pos个字符开始出现的位置
CString SubString(const CString &s, int pos, int len);	
	// 求串s的第pos个字符开始的长度为len的子串
bool operator ==(const CString &first, const CString &second);
	// 重载关系运算符==
bool operator <(const CString &first, const CString &second);
	// 重载关系运算符<
bool operator >(const CString &first, const CString &second);
	// 重载关系运算符>
bool operator <=(const CString &first, const CString &second);
	// 重载关系运算符<=
bool operator >=(const CString &first, const CString &second);
	// 重载关系运算符>=
bool operator !=(const CString &first, const CString &second);
	// 重载关系运算符!=

// 串类及相关操作的实现部分
CString::CString()
//  操作结果：初始化串 
{
	length = 0;									// 串长度为0
	strVal = NULL;								// 空串
}

CString::~CString()
// 操作结果：销毁串，释放串所占用空间
{
	delete []strVal;							// 释放串strVal
}

CString::CString(const CString &copy)
// 操作结果：由串copy构造新串——复制构造函数
{
	length = strlen(copy.CStr());				// 串长
	strVal = new char[length + 1];				// 分配存储空间
	strcpy(strVal, copy.CStr());				// 复制串值
}

CString::CString(const char *copy)
// 操作结果：从C风格串转换构造新串——转换构造函数
{
	length = strlen(copy);						// 串长
	strVal = new char[length + 1];				// 分配存储空间 
	strcpy(strVal, copy);						// 复制串值
}

CString::CString(LinkList<char> &copy)
// 操作结果：从线性表转换构造新串——转换构造函数
{
	length = copy.Length();						// 串长
	strVal = new char[length + 1];				// 分配存储空间 
	for (int i = 0; i < length; i++) 
	{	// 复制串值
		copy.GetElem(i + 1, strVal[i]);
	}
	strVal[length] = '\0';						// 串值以'\0'结束	
}

int CString::Length() const
// 操作结果：返回串长度			 
{
	return length;
}

bool CString::Empty() const
// 操作结果：如果串为空，返回true，否则返回false
{
	return length == 0;
}

CString &CString::operator =(const CString &copy)
// 操作结果：赋值语句重载
{
	if (&copy != this)
	{
		delete []strVal;						// 释放原串存储空间
		length = strlen(copy.CStr());			// 串长
		strVal = new char[length + 1];			// 分配存储空间 
		strcpy(strVal, copy.CStr());			// 复制串值
	}
	return *this;
}

const char *CString::CStr() const
// 操作结果：将串转换成C风格串
{
	return (const char *)strVal;				// 串值类型转换
}

char &CString::operator [](int pos) const
// 操作结果：重载下标运算符
{
	return strVal[pos];
}

void Concat(CString &addTo, const CString &addOn)
// 操作结果：将串addOn连接到addTo串的后面
{
	const char *cFirst = addTo.CStr();			// 指向第一个串
	const char *cSecond = addOn.CStr();			// 指向第二个串
	char *copy = new char[strlen(cFirst) + strlen(cSecond) + 1];// 分配存储空间
	strcpy(copy, cFirst);						// 复制第一个串
	strcat(copy, cSecond);						// 连接第二个串
	addTo = copy;								// 串赋值
	delete []copy;								// 释放copy
}

CString operator +(const CString &strFirst, const CString &strSecond)
// 操作结果：重载加法运算符+
{
	const char *cFirst = strFirst.CStr();		// 指向第一个串
	const char *cSecond = strSecond.CStr();		// 指向第二个串
	char *copy = new char[strlen(cFirst) + strlen(cSecond) + 1];// 分配存储空间
	strcpy(copy, cFirst);						// 复制第一个串
	strcat(copy, cSecond);						// 连接第二个串
	CString answer(copy);						// 构造串
	delete []copy;								// 释放copy
	return answer;								// 返回串
}

ostream &operator <<(ostream &outStream, const CString &outStr)
// 操作结果：重载运算符<<
{
	cout << outStr.CStr();						// 输出串值
	return outStream;							// 返回输出流对象
}

istream &operator >>(istream &inStream, CString &inStr)
// 操作结果：重载运算符>>
{
	LinkList<char> temp;						// 临时线性表
	int size = 0;								// 初始线性表长度
	char ch= GetChar(inStream);					// 从输入流inStream中跳过空格及制表符获取一字符
	inStream.putback(ch);						// 将ch回送输入流
	while ((ch = inStream.peek()) != EOF &&		// peek()从输入流中取一个字符
												// 输入流指针不变
		(ch = inStream.get()) != '\n'			// get()从输入流中取一个字符ch
												// 输入流指针指向下一字符,ch不为换行符
		&& ch != '\t' && ch != ' ')				// ch也不为制表符与空格	
	{	// 将输入的字符追加到线性表中
		temp.Insert(++size, ch);
	}
	CString answer(temp);						// 构造串
	inStr = answer;								// 用inStr返回串
	return inStream;							// 返回输入流对象
}

CString Read(istream &input)
// 操作结果：从输入流读入串
{
	LinkList<char> temp;						// 临时线性表
	int size = 0;								// 初始线性表长度
	char c;										// 临时字符
	while ((c = input.peek()) != EOF &&			// peek()从输入流中取一个字符
												// 输入流指针不变
		(c = input.get()) != '\n')				// get()从输入流中取一个字符
												// 输入流指针指向下一字符
	{	// 将输入的字符追加线性表中
		temp.Insert(++size, c);
	}
	CString answer(temp);						// 构造串
	return answer;								// 返回串
}

CString Read(istream &input,char &terminalChar)
// 操作结果：从输入流读入串，并用terminalChar返回串结束字符
{
	LinkList<char> temp;						// 临时线性表
	int size = 0;								// 初始线性表长度
	char c;										// 临时字符
	while ((c = input.peek()) != EOF &&			// peek()从输入流中取一个字符
												// 输入流指针不变
		(c = input.get()) != '\n')				// get()从输入流中取一个字符
												// 输入流指针指向下一字符
	{	// 将输入的字符追加线性表中
		temp.Insert(++size, c);
	}
	terminalChar=c;	// 用terminalChar返回串结束字符
	CString answer(temp);						// 构造串
	return answer;								// 返回串
}

void Write(CString &s)
// 操作结果：输出串
{
	cout << s.CStr() << endl;					// 输出串值
}

void Copy(CString &copy, const CString &original)
// 操作结果：将串original复制到串copy
{
	const char *cOriginal = original.CStr();	// 初始串
	char *cCopy = new char[strlen(cOriginal) + 1];// 分配存储空间
	strcpy(cCopy, cOriginal);					// 复制串
	copy = cCopy;								// 串赋值
	delete []cCopy;								// 释放串cCopy
}

void Copy(CString &copy, const CString &original, int n)
// 操作结果：将串original复制n个字符到串copy 
{
	const char *cOriginal = original.CStr();// 初始串
	int len = (int)strlen(cOriginal) < n ? (int)strlen(cOriginal) : n;//目标串长
	char *cCopy = new char[len + 1];			// 分配存储空间
	strncpy(cCopy, cOriginal, n);				// 复制串
	cCopy[len] = '\0';							// 串值以'\0'结束
	copy = cCopy;								// 串赋值
	delete []cCopy;								// 释放串cCopy
}

int Index(const CString &target, const CString &pattern, int pos)
// 操作结果：如果匹配成功，返回模式串pattern第一次在目标串target中从第pos
//	个字符开始出现的位置, 否则返回-1
{
	const char *cTarget = target.CStr();		// 目标串
	const char *cPattern = pattern.CStr();		// 模式串
	const char *ptr=strstr(cTarget + pos, cPattern);	// 模式匹配
	if (ptr == NULL)
	{	// 匹配失败	
		return -1; 
	}
	else
	{	// 匹配成功	
		return ptr - cTarget;
	}
}

CString SubString(const CString &s, int pos, int len)
// 初始条件：串s存在，0 <= pos < s.Length()且0 <= len <= s.Length() - pos
// 操作结果：返回串s的第pos个字符开始的长度为len的子串
{
	if  (0 <= pos && pos < s.Length() && 0 <= len)
	{	// 返回串s的第pos个字符开始的长度为len的子串
		len = (len < s.Length() - pos) ? len : (s.Length() - pos);// 子串长
		char *sub = new char[len + 1];			// 分配存储空间
		const char *str = s.CStr();				// 生成C风格串
		strncpy(sub, str + pos, len);			// 复制串
		sub[len] = '\0';						// 串值以'\0'结束
		CString tem(sub);						// 生成串对象
		return tem;
	}
	else
	{	// 返回空串
		CString tem("");						// 生成空串对象
		return tem;
	}
}

bool operator ==(const CString &first, const CString &second)
// 操作结果：重载关系运算符==
{
	return strcmp(first.CStr(), second.CStr()) == 0;
}

bool operator <(const CString &first, const CString &second)
// 操作结果：重载关系运算符<
{
	return strcmp(first.CStr(), second.CStr()) < 0;
}

bool operator >(const CString &first, const CString &second)
// 操作结果：重载关系运算符>
{
	return strcmp(first.CStr(), second.CStr()) > 0;
}

bool operator <=(const CString &first, const CString &second)
// 操作结果：重载关系运算符<=
{
	return strcmp(first.CStr(), second.CStr()) <= 0;
}

bool operator >=(const CString &first, const CString &second)
// 操作结果：重载关系运算符>=
{
	return strcmp(first.CStr(), second.CStr()) >= 0;
}

bool operator !=(const CString &first, const CString &second)
// 操作结果：重载关系运算符!=
{
	return strcmp(first.CStr(), second.CStr()) != 0;
}

#endif