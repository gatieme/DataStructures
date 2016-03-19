#ifndef __EXPRESSION_VALUE_H__
#define __EXPRESSION_VALUE_H__

#include "lk_stack.h"								// 链栈

// 表达式求值类
template<class ElemType>
class ExpressionValue
{
private:
// 辅助函数:
	static bool IsOperator(char ch);				// 判断ch是否为运算符
	static int LeftPri(char op);					// 左边运算符的优先级
	static int RightPri(char op);					// 右边运算符的优先级
	static void Get2Operands(LinkStack<ElemType> &opnd, ElemType &a1, ElemType &a2);			
		// 从opnd栈中取出两个操作数
	static void DoOperator(LinkStack<ElemType> &opnd, const ElemType &a1, 
		char op, const ElemType &a2);				// 形成运算指令 (a1)op(a2)，结果进opnd栈
	static void PostfixExpression(ofstream &outFile);		
		// 将从键盘中输入的中缀表达式转换为后缀表达式，再存入输出流文件outFile中
	static void PostfixExpressionValue(ifstream &inFile);
		// 从输入文件inFile中输入后缀表达式, 并求后缀表达式的值

public:
// 接口方法声明:
	ExpressionValue(){};							// 无参数的构造函数
	virtual ~ExpressionValue(){};					// 析构函数
	static void Run();								// 求从键盘输入的中缀表达式之值
};

// 表达式求值类的实现部分
template<class ElemType>
bool ExpressionValue<ElemType>::IsOperator(char ch)
// 操作结果: 如果ch是运算符, 则返回true, 否则返回false
{	
	if (ch == '=' || ch == '(' || ch == '*' || ch == '/' || ch == '+' || ch == '-' || ch == ')') return true;
	else return false; 
}

template<class ElemType>
int ExpressionValue<ElemType>::LeftPri(char op)
// 操作结果: 左边运算符的优先级	
{
	int result;										// 优先级
	if (op == '=') result = 0;
	else if (op == '(') result = 1;
	else if (op == '*' || op == '/') result = 5;
	else if (op == '+' || op == '-') result = 3;
	else if (op == ')') result = 6;
	return result;									// 返回优先级
}

template<class ElemType>
int ExpressionValue<ElemType>::RightPri(char op)
// 操作结果: 右边运算符的优先级	
{
	int result;										// 优先级
	if (op == '=') result = 0;
	else if (op == '(') result = 6;
	else if (op == '*' || op == '/') result = 4;
	else if (op == '+' || op == '-') result = 2;
	else if (op == ')') result = 1;
	return result;									// 返回优先级

}

template<class ElemType>
void ExpressionValue<ElemType>::Get2Operands(LinkStack<ElemType> &opnd, 
	ElemType &a1, ElemType &a2)
// 操作结果: 从opnd栈中取出两个操作数
{
	if(opnd.Pop(a2) == UNDER_FLOW) throw Error("表达式有错!");	// 抛出异常
	if(opnd.Pop(a1) == UNDER_FLOW) throw Error("表达式有错!");	// 抛出异常
}

template<class ElemType>
void ExpressionValue<ElemType>::DoOperator(LinkStack<ElemType> &opnd, 
	const ElemType &a1, char op, const ElemType &a2)
// 操作结果: 形成运算指令 (a1) op (a2)，结果进opnd栈
{
	switch(op)
	{
	case '+':
		opnd.Push(a1 + a2);							// 加法+运算
		break;
	case '-':
		opnd.Push(a1 - a2);							// 减法-运算
		break;
	case '*':
		opnd.Push(a1 * a2);							// 乘法*运算
		break;
	case '/':
		if (a2==0)  throw Error("除数为0!");		// 抛出异常
		opnd.Push(a1 / a2);							// 除法/运算
		break;
	}
}

template<class ElemType>
void ExpressionValue<ElemType>::PostfixExpression(ofstream &outFile)
// 操作结果: 将从键盘中输入的中缀表达式转换为后缀表达式，再存入输出流
//	文件outFile中
{
	LinkStack<char> optr;							// 操作符栈optr
	char ch, optrTop, op;							// 输入的字符ch, 操作符栈optr栈顶操作符,操作符op
	ElemType operand;								// 操作数
	optr.Push('=');									// 为编程方便起见，在optr的栈底压入'='
	optr.Top(optrTop);								// 取出操作符栈optr的栈顶
	ch = GetChar();									// 从输入流cin中跳过空格与制表符取出一个字符
	while (optrTop != '=' || ch != '=')
	{	//当optrTop等于'='且ch等于'='不成立时，表达式运算未结束
		if (isdigit(ch) || ch=='.')
		{	// ch为数字或句点时的处理 
			cin.putback(ch);						// 将ch放回输入流
			cin >> operand;							// 读操作数operand
			outFile << operand << " ";				// 将operand输出到文件outFile中
			ch = GetChar();							// 从输入流cin中跳过空格与制表符取出一个字符
		}
		else if (!IsOperator(ch))
		{	// ch为非法字符
			throw Error("非法字符!");				// 抛出异常
		}
		else
		{
			if (LeftPri(optrTop) < RightPri(ch))
			{	
				optr.Push(ch);						// ch进optr栈
				ch = GetChar();						// 从输入流cin中跳过空格与制表符取出一个字符
			}
			else if (LeftPri(optrTop) > RightPri(ch))
			{	
				optr.Pop(op);						// 从optr栈退出op
				outFile << op << " ";				// 将运算符op输出到outFile中
			}
			else if (LeftPri(optrTop) == RightPri(ch) && ch == ')')
			{	// 表示optrTop等于'('与ch等于')'
				optr.Pop(ch);						// 从optr栈退出栈顶的'('
				ch = GetChar();						// 从输入流cin中跳过空格与制表符取出一个字符
			}
		}
		optr.Top(optrTop);							// 取出操作符栈optr的栈顶
	}
	outFile << '=';									// 输入流文件outFile以'='结束，以便编程实现
}

template<class ElemType>
void ExpressionValue<ElemType>::PostfixExpressionValue(ifstream &inFile)
// 操作结果: 从输入文件inFile中输入后缀表达式, 并求后缀表达式的值
{
	LinkStack<ElemType> opnd;						// 操作数栈opnd
	char ch;										// 当前字符
	double operand;									// 操作数
	
	while (inFile >> ch, ch != '=')
	{	// 只要从输入流文件inFile取得的字符不为'='就循循环
		if (IsOperator(ch))
		{	// ch为操作符，进行相关运算
			ElemType a1, a2;						// 操作数
			Get2Operands(opnd, a1, a2);				// 从opnd栈中取出两个操作数
			DoOperator(opnd, a1, ch, a2);			// 形成运算指令 (a1) op (a2)，结果进opnd栈
		}
		else
		{	// ch不是操作符
			inFile.putback(ch);						// 将ch放回输入流文件inFile
			inFile >> operand;						// 从输入流文件inFile输入操作数
			opnd.Push(operand);						// 将operand入栈opnd
		}
	}
	opnd.Top(operand);								// 取得opnd的栈顶元素作为表达式运算结果
	cout << operand << endl;						// 显示运算结果
}

template<class ElemType>
void ExpressionValue<ElemType>::Run()
// 操作结果: 求从键盘输入的中缀表达式之值
{
		ofstream outFile("temp.dat");				//定义输出流文件
		PostfixExpression(outFile);	
			// 将从键盘所输入的中缀表达式转换为后缀表达式，将结果存入输出流文件中
			//（以'='结束）
		outFile.close();							//关闭输出流文件

		ifstream inFile("temp.dat");				//定义输入流文件
		PostfixExpressionValue(inFile);		
			// 计算从输入流文件中输入的后缀表达式（以'='结束）的，并将结果在屏幕
			// 上显示出来
		inFile.close();								//关闭输入流文件

		remove("temp.dat");							//删除临时文件temp.dat
}

#endif


