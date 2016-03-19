// 文件路径名: game_of_animal\game_of_animal.h
#ifndef __GAME_OF_ANIMAL_H__
#define __GAME_OF_ANIMAL_H__

#include "string.h"								// 串类
#include "binary_tree.h"						// 二叉树类
#include "lk_stack.h"							// 链栈

// 动物游戏类
class GameOfAnimal
{
private:
// 动物游戏类的数据成员:
	BinaryTree<String> *pDTree;					// 决策树

//	辅助函数:
	void WriteHelp(BinTreeNode<String> *root, ofstream &outFile);	// 写决策树信息
	bool IsQuestion(String strSentence);		// 是否为疑问句

public:
// 公有函数:
	GameOfAnimal();								// 构造函数
	virtual ~GameOfAnimal();					// 析构函数
	void Run();									// 运行动物游戏
};

// 重载串输入/输出运算符
ostream &operator <<(ostream &outStream, const String &outStr);
	// 重载运算符<<
istream &operator >>(istream &inStream, String &inStr);
	// 重载运算符>>

// 动物游戏类及相关函数的实现部分
void GameOfAnimal::WriteHelp(BinTreeNode<String> *root, ofstream &outFile)
// 操作结果: 将决策树信息写到文件outFile
{
	if (root != NULL)
	{
		WriteHelp(root->leftChild, outFile);	// 写左子树
		WriteHelp(root->rightChild, outFile);	// 写右子树
		outFile << root->data << endl;			// 写根信息
	}
}

bool GameOfAnimal::IsQuestion(String strSentence)
// 操作结果: 是否为疑问句
{
	return strSentence[strSentence.Length() - 1] == '?';// 以问号结束为疑问句
}


GameOfAnimal::GameOfAnimal()
// 操作结果: 由知识库文件建立决策树
{
	ifstream inFile("animal.dat");				// 输入文件流
	if (inFile == NULL) throw Error("不能打开知识库文件!");	// 抛出异常
	String strElem;								// 决策树元素
	LinkStack<BinTreeNode<String> *> s;			// 栈
	BinTreeNode<String> *r, *r1, *r2;			// 指向二叉树结点的指针 

	inFile >> strElem;							// 读入决策树元素
	while (!strElem.Empty())
	{	// 存在决策树元素, 循环
		if (IsQuestion(strElem))
		{	// 疑问句, 为决策树分支结点
			s.Pop(r2);	s.Pop(r1);				// 从栈中弹出左右孩子 
			r = new BinTreeNode<String>(strElem, r1, r2);// 构造新结点
			s.Push(r);							// 入新结点入栈
		}
		else
		{	// 非疑问句, 表示动物名, 为决策树叶子结点
			r = new BinTreeNode<String>(strElem);		// 构造新结点
			s.Push(r);							// 入新结点入栈
		}
		inFile >> strElem;						// 读入决策树元素
	}
	s.Top(r);									// 取出栈顶元素
	pDTree = new BinaryTree<String>(r);			// 生成决策树
	inFile.close();								// 关闭文件
}

GameOfAnimal::~GameOfAnimal()
// 操作结果: 决策树信息并释放存储空间
{
	ofstream outFile("animal.dat");				// 输出文件流
	if (outFile == NULL) throw Error("不能打开知识库文件!");	// 抛出异常
	WriteHelp(pDTree->GetRoot(), outFile);		//  将决策树信息写到文件outFile
	outFile.close();							// 关闭文件
	delete pDTree;								// 释放存储空间
}

void GameOfAnimal::Run()
// 操作结果: 运行动物游戏
{
	cout << "欢迎来到动物游戏!" << endl;
	do
	{
		cout << "想出一个动物, 我将尽力猜它..." << endl;
		BinTreeNode<String> *p = pDTree->GetRoot();	// 根结点开始进行处理
		String strElem = p->data;					// 决策树元素
		while (IsQuestion(strElem))
		{	// 疑问句, 为决策树分支结点
			cout << strElem;						// 显示疑问句 
			cout << "请回答";
			if (UserSaysYes()) p = p->leftChild;	// 肯定回答为左孩子
			else p = p->rightChild;					// 否定回答为右孩子
			strElem = p->data;						// 决策树元素
		}

		cout << "你想的动物是" << strElem << "吗? 请回答";
		if (UserSaysYes())
		{ 	// 肯定回答
			cout << "哈! 一台计算机都打败了你..." << endl;
		}
		else
		{ 	// 否定回答
			cout << "你是幸运的..." << endl;
			cout << "你想的什么动物呢?" << endl;
			String strNewAnimal, strOldAnimal = strElem;// 动物名词
			cin >> strNewAnimal;				// 输入动物名称
			cout << "请输入一个疑问句, 肯定回答为" << strNewAnimal 
				<< ", 否定回答为" << strOldAnimal << endl; 
			cin >> strElem;						// 输入疑问句
			p->data = strElem;					// 改为疑问句
			p->leftChild = new BinTreeNode<String>(strNewAnimal);	// 左孩子
			p->rightChild = new BinTreeNode<String>(strOldAnimal);	// 右孩子
		}
		
		cout << "想再玩一次吗? 请回答";
	}while (UserSaysYes());
}

ostream &operator <<(ostream &outStream, const String &outStr)
// 操作结果：重载运算符<<
{
	outStream << outStr.CStr();				// 输出串值
	return outStream;						// 返回输出流对象
}

istream &operator >>(istream &inStream, String &inStr)
// 操作结果：重载运算符>>
{
	LinkList<char> temp;					// 临时线性表
	int size = 0;							// 初始线性表长度
	char ch= GetChar(inStream);				// 从输入流inStream中跳过空格及制表符获取一字符
	inStream.putback(ch);					// 将ch回送输入流
	while ((ch = inStream.peek()) != EOF &&	// peek()从输入流中取一个字符
											// 输入流指针不变
		(ch = inStream.get()) != '\n'		// get()从输入流中取一个字符ch
											// 输入流指针指向下一字符,ch不为换行符
		&& ch != '\t' && ch != ' ')			// ch也不为制表符与空格	
	{	// 将输入的字符追加到线性表中
		temp.Insert(++size, ch);
	}
	String answer(temp);					// 构造串
	inStr = answer;							// 用inStr返回串
	return inStream;						// 返回输入流对象
}

#endif
