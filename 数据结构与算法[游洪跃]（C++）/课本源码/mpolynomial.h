#ifndef __MPOLYNOMIAL_H__
#define __MPOLYNOMIAL_H__

#include "mpolynomial_node.h"					// m元多项式结点类

// m元多项式类
template<class CoefType>
class MPolynomial
{
protected:
// m元多项式类的数据成员:
	MPolynomialNode<CoefType> *head;			// m元多项式头指针

// 辅助函数
	void ShowHelp(MPolynomialNode<CoefType> *hd) const;	
		// 显示以hd为头结点的m元多项式
	void CopyHelp(const MPolynomialNode<CoefType> *sourceHead, 
		 MPolynomialNode<CoefType> *&destHead);
		// 将以destHead为头结点的m元多项式复制成以sourceHead为头结点的m元多项式
	static void CreateHelp(MPolynomialNode<CoefType> *&first);
		// 创建以first为头结点的m元多项式

public:
// 抽象数据类型方法声明及重载编译系统默认方法声明:
	MPolynomial();								// 无参数的构造函数
	MPolynomial(MPolynomialNode<CoefType> *hd);	// 由头结点指针构造m元多项式
	~MPolynomial(){};							// 析构函数
	MPolynomialNode<CoefType> *First() const;	// 返回m元多项式的第一个结点
	MPolynomialNode<CoefType> *Next(MPolynomialNode<CoefType> *elemPtr) const;	                                                                               
		// 返回elemPtr指向的m元多项式项的后继
	bool Empty() const;							// 判断m元多项式是否为空(0多项式)
	MPolynomial(const MPolynomial<CoefType> &copy);		// 复制构造函数
	MPolynomial<CoefType> &operator =(const MPolynomial<CoefType> &copy);// 赋值语句重载
	void Input(void);						// 输入广义表	
	void Show(void);						// 显示广义表	
};

// m元多项式类的实现部分
template <class CoefType>
MPolynomial<CoefType>::MPolynomial()
// 操作结果：构造一个空m元多项式
{
	head = new MPolynomialNode<CoefType>(HEAD);
}

template <class CoefType>
MPolynomial<CoefType>::MPolynomial(MPolynomialNode<CoefType> *hd)
// 操作结果：由头结点指针构造m元多项式
{
	head = hd;								// 头结点
}

template <class CoefType>
MPolynomialNode<CoefType> *MPolynomial<CoefType>::First() const
// 操作结果：返回m元多项式的第一个结点
{
	return head->nextLink;
}

template <class CoefType>
MPolynomialNode<CoefType> *MPolynomial<CoefType>::Next(MPolynomialNode<CoefType> *elemPtr) const
// 操作结果：返回elemPtr指向的m元多项式项的后继
{
	return elemPtr->nextLink;
}

template <class CoefType>
bool MPolynomial<CoefType>::Empty() const
// 操作结果：如m元多项式为空(0多项式)，则返回true，否则返回false
{
	return head->nextLink == NULL;
}

template <class CoefType>
void MPolynomial<CoefType>::ShowHelp(MPolynomialNode<CoefType> *hd) const
// 操作结果：显示以hd为头结点的m元多项式
{
	bool frist = true;
	if (hd->nextLink != NULL) cout << hd->var;	// 显示非空m元多项式的主变量
	cout << "(";								// m元多项式以(开始
	for (MPolynomialNode<CoefType> *tmpPtr = hd->nextLink; tmpPtr != NULL; 
		tmpPtr = tmpPtr->nextLink)
	{	// 依次处理m元多项式各项
		if (frist) frist = false;				// 第一项
		else cout << ",";						// 不同项之间用逗号隔开
		if (tmpPtr->tag == ATOM)
		{	// 原子结点
			cout << tmpPtr->atom.coef;			// 显示系数
			cout << "^" << tmpPtr->atom.exp;	// 显示指数
		}
		else
		{	// 表结点
			ShowHelp(tmpPtr->list.subLink);		// 显示子表
			cout << "^" << tmpPtr->list.exp;	// 显示指数
		}
	}
	cout << ")";								// m元多项式以)结束
}

template <class CoefType>
void MPolynomial<CoefType>::Show(void)
// 操作结果：显示广义表	
{
	ShowHelp(head);						// 调用辅助函数显示广义表
}

template <class CoefType>
void MPolynomial<CoefType>::CopyHelp(const MPolynomialNode<CoefType> *sourceHead, MPolynomialNode<CoefType> *&destHead)	
// 初始条件: 以sourceHead为头结点的m元多项式为非递归m元多项式
// 操作结果：将以sourceHead为头结点的m元多项式复制成以destHead为头结点的m元多项式
{
	destHead = new MPolynomialNode<CoefType>(HEAD);			// 复制头结点
	destHead->var = sourceHead->var;						// 复制头结点的主变量
	MPolynomialNode<CoefType> *destPtr = destHead;			// destHead的当前结点
	for (MPolynomialNode<CoefType> *tmpPtr = sourceHead->nextLink; tmpPtr != NULL; 
		tmpPtr = tmpPtr->nextLink)
	{	// 扫描m元多项式sourceHead的顶层
		destPtr = destPtr->nextLink = new MPolynomialNode<CoefType>(tmpPtr->tag);	// 生成新结点
		if (tmpPtr->tag == LIST)
		{	// 子表
			CopyHelp(tmpPtr->list.subLink, destPtr->list.subLink);	// 复制子表
			destPtr->list.exp = tmpPtr->list.exp;			// 复制指数
		}
		else
		{	// 原子结点
			destPtr->atom.coef = tmpPtr->atom.coef;			// 复制系数
			destPtr->atom.exp = tmpPtr->atom.exp;			// 复制指数
		}
	}
}

template <class CoefType>
MPolynomial<CoefType>::MPolynomial(const MPolynomial<CoefType> &copy)
// 操作结果：由m元多项式copy构造新m元多项式--复制构造函数
{
	CopyHelp(copy.head, head);			// 由m元多项式copy构造新m元多项式
}

template<class CoefType>
MPolynomial<CoefType> &MPolynomial<CoefType>::operator =(const MPolynomial<CoefType> &copy)
// 操作结果：将m元多项式copy赋值给当前m元多项式--赋值语句重载
{
	if (&copy != this)
	{
		CopyHelp(copy.head, head);		// 复制m元多项式
	}
	return *this;
}

template<class CoefType>
void MPolynomial<CoefType>::CreateHelp(MPolynomialNode<CoefType> *&first)
// 操作结果：创建以first为头结点的m元多项式
{
	CoefType tmpCoef;							// 原子结点的临时系数
	int tmpExp;									// 原子结点的临时指数
	char ch = tolower(GetChar());				// 读入字符
	switch (ch)
	{
	case ')':									// m元多项式建立完毕
		return;									// 结束
	case 'a':									// 主变量
	case 'b':									// 主变量
	case 'c':									// 主变量
	case 'd':									// 主变量
	case 'e':									// 主变量
	case 'f':									// 主变量
	case 'g':									// 主变量
	case 'h':									// 主变量
	case 'i':									// 主变量
	case 'j':									// 主变量
	case 'k':									// 主变量
	case 'l':									// 主变量
	case 'm':									// 主变量
	case 'n':									// 主变量
	case 'o':									// 主变量
	case 'p':									// 主变量
	case 'q':									// 主变量
	case 'r':									// 主变量
	case 's':									// 主变量
	case 't':									// 主变量
	case 'u':									// 主变量
	case 'v':									// 主变量
	case 'w':									// 主变量
	case 'x':									// 主变量
	case 'y':									// 主变量
	case 'z':									// 主变量
		// 表头为子表
		GetChar();								// 跳过'('
		first = new MPolynomialNode<CoefType>(LIST);// 生成表结点
		
		MPolynomialNode<CoefType> *subHead;		// 子表指针
		subHead = new MPolynomialNode<CoefType>(HEAD);// 生成子表的头结点
		subHead->var = ch;						// 子表的主变量	
		first->list.subLink = subHead;			// subHead为子表
		CreateHelp(subHead->nextLink);			// 递归建立子表
		GetChar();								// 跳过'^'
		cin >> tmpExp;							// 输入表结点的指数
		first->list.exp = tmpExp;				// 表结点的指数
		
		ch = GetChar();							// 跳过','
		if (ch != ',') cin.putback(ch);			// 如不是','，则将ch回退到输入流
		CreateHelp(first->nextLink);			// 建立m元多项式下一结点
		break;
	default:									// 原子
		// 表头为原子
		cin.putback(ch);						// 将ch回退到输入流
		cin >> tmpCoef;							// 输入原子结点的系数
		GetChar();								// 跳过'^'
		cin >> tmpExp;							// 输入原子结点的指数
		first = new MPolynomialNode<CoefType>(ATOM);// 生成原表结点
		first->atom.coef = tmpCoef;				// 原子结点的系数
		first->atom.exp = tmpExp;				// 原子结点的指数
		
		ch = GetChar();							// 跳过','
		if (ch != ',') cin.putback(ch);			// 如不是','，则将ch回退到输入流
		CreateHelp(first->nextLink);			// 建立m元多项式下一结点
		break;
	}
}

template<class CoefType>
istream &operator >>(istream &inStream, MPolynomial<CoefType> &in)
// 操作结果：重载运算符>>
{
	MPolynomialNode<CoefType> *head;			// 头结点
	head = new MPolynomialNode<CoefType>(HEAD);	// 生成m元多项式头结点
	
	char ch = tolower(GetChar(inStream));		// 读入主变量或第一个'('
	if (ch >= 'a' && ch <= 'z') 
	{	// 读入的是主变量
		head->var = ch;							// 主变量
		GetChar(inStream);						// 读入第一个'('
	}
	MPolynomial<CoefType>::CreateHelp(inStream, head->nextLink);
		// 创建以head->nextLink为表头的m元多项式
	
	in = (MPolynomial<CoefType>)head;			// 建立m元多项式
	
	return inStream;
}

template<class CoefType>
void MPolynomial<CoefType>::Input(void)
// 操作结果：输入广义表	
{
	head = new MPolynomialNode<CoefType>(HEAD);	// 生成m元多项式头结点
	
	char ch = tolower(GetChar());				// 读入主变量或第一个'('
	if (ch >= 'a' && ch <= 'z') 
	{	// 读入的是主变量
		head->var = ch;							// 主变量
		GetChar();								// 读入第一个'('
	}
	MPolynomial<CoefType>::CreateHelp(head->nextLink);
		// 创建以head->nextLink为表头的m元多项式
}


#endif