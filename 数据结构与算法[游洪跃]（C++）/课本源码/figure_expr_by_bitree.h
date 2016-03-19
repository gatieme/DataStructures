// 文件路径名:figure_expr_by_bitree\figure_expr_by_bitree.h
#ifndef __FIGURE_EXPR_BY_BI_TREE_H__
#define __FIGURE_EXPR_BY_BI_TREE_H__

#include "lk_stack.h"								// 链栈
#include "bin_tree_node.h"							// 二叉树结点类
#include "binary_tree.h"							// 二叉树类

// 表达式的二叉树表示类
class FigureExprByBiTree
{
private:
// 辅助函数:
	static bool IsOperator(char ch);				// 判断ch是否为运算符
	static int LeftPri(char op);					// 左边运算符的优先级
	static int RightPri(char op);					// 右边运算符的优先级

public:
// 接口方法声明:
	FigureExprByBiTree(){};							// 无参数的构造函数
	virtual ~FigureExprByBiTree(){};				// 析构函数
	static void Run();								// 将从键盘输入的中缀表达式用二叉树表示
};

// 表达式的二叉树表示类的实现部分
bool FigureExprByBiTree::IsOperator(char ch)
// 操作结果: 如果ch是运算符, 则返回true, 否则返回false
{	
	if (ch == '=' || ch == '(' || ch == '*' || ch == '/' || ch == '+' || ch == '-' || ch == ')') return true;
	else return false; 
}

int FigureExprByBiTree::LeftPri(char op)
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

int FigureExprByBiTree::RightPri(char op)
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

void FigureExprByBiTree::Run()
// 操作结果: 将从键盘中输入的中缀表达式转换为后缀表达式，用二叉树表示,并显示二叉树
{
	LinkStack<BinTreeNode<char> *> biTr;			// 二叉树栈
	LinkStack<char> optr;							// 操作符栈
	char ch, optrTop, theta;						// 输入的字符ch, 操作符栈optr栈顶操作符,操作符theta
	BinTreeNode<char> *r;							// 指向二叉树结构指针
	optr.Push('=');									// 为编程方便起见，在optr的栈底压入'='
	optr.Top(optrTop);								// 取出操作符栈optr的栈顶
	ch = GetChar();									// 从输入流cin中跳过空与换行符取出一个字符
	while (optrTop != '=' || ch != '=')
	{	//当optrTop等于'='且ch等于'='不成立时，表达式运算未结束
		if (!IsOperator(ch))
		{	// ch为操作数
			r = new BinTreeNode<char>(ch);			// 生成只含一个结点的二叉树
			biTr.Push(r);							// r进optr栈
			ch = GetChar();							// 从输入流cin中跳过空与换行符取出一个字符
		}
		else
		{	// ch为操作符
			if (LeftPri(optrTop) < RightPri(ch))
			{	// ch优先级更高
				optr.Push(ch);						// ch进optr栈
				ch = GetChar();						// 从输入流cin中跳过空与换行符取出一个字符
			}
			else if (LeftPri(optrTop) > RightPri(ch))
			{	// optrTop优先级更高
				BinTreeNode<char> *leftr, *rightr;	// 二叉树 
				if(biTr.Pop(rightr) == UNDER_FLOW) throw Error("表达式有错!");	// 抛出异常
				if(biTr.Pop(leftr) == UNDER_FLOW) throw Error("表达式有错!");	// 抛出异常
				optr.Pop(theta);					// 从optr栈退出theta
				r = new BinTreeNode<char>(theta, leftr, rightr);				// 生成新二叉树
				biTr.Push(r);						// r进biTr栈
			}
			else if (LeftPri(optrTop) == RightPri(ch) && ch == ')')
			{	// 表示optrTop等于'('与等于')'
				optr.Pop(ch);						// 从optr栈退出栈顶的'('
				ch = GetChar();						// 从输入流cin中跳过空与换行符取出一个字符
			}
		}
		optr.Top(optrTop);							// 取出操作符栈optr的栈顶
	}
	biTr.Pop(r);									// r为生成的二叉树的根
	BinaryTree<char> bt(r);							// 生成二叉树
	DisplayBTWithTreeShape(bt);						// 显示二叉树
}

#endif


