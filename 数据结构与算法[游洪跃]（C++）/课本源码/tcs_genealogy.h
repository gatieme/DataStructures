// 文件路径名: tcs_genealogy\tcs_genealogy.h
#ifndef __TCS_GENEALOGY__H__
#define __TCS_GENEALOGY__H__

#include "string.h"							// 串类
#include "parent_forest.h"					// 森林类

// 元素结构
struct ElemType
{
	String student;							// 学生姓名
	String adivisor;						// 学生论文导师姓名
	String place;							// 授予博士学位的大学名称缩写
	String dataOfPHD;						// 授予博士学位的年份
};

// 输出类型
enum OutputType {OUTPUT_TO_SCREEN, OUTPUT_TO_FILE};

// 理论计算机科学家族谱类
class TCSGenealogy
{
private:
// 公园导游类的数据成员:
	ParentForest<ElemType> *pForest;		// 由理论计算机科学家族谱组成的森林
	ifstream inFile;						// 输入流 
	
// 辅助函数:
	void Readln();							// 跳过一行  
	void BuildForest();						// 建立理论计算机科学家族谱组成的森林
	void OutputHelp(ostream &outStream, int r, int level);	
		// 输出理论计算机科学家族谱辅助函数，level为层次数，可设根结点的层次数为1

public:
// 抽象数据类型方法声明及重载编译系统默认方法声明:
	TCSGenealogy();							// 无参数的构造函数
	virtual ~TCSGenealogy();				// 析构函数
	void Output(OutputType tp);				// 输出理论计算机科学家族谱, tp为输出类型
};

// 重载串输入/输出运算符
ostream &operator <<(ostream &outStream, const String &outStr);
	// 重载运算符<<
istream &operator >>(istream &inStream, String &inStr);
	// 重载运算符>>

// 理论计算机科学家族谱类及相关函数的实现部分
void TCSGenealogy::Readln()
// 操作结果：跳过一行
{	
	char ch;								// 字符
	while ((ch = inFile.peek()) != EOF		// 不为文件结束符
		&& (ch = inFile.get()) != '\n');	// 不为换行符
}

void TCSGenealogy::BuildForest()
// 操作结果：建立由理论计算机科学家族谱组成的森林
{
	int n = 0;								// 森林包含的结点个数
	char ch;								// 临时字符

	while ((ch = inFile.peek()) != EOF)
	{	// 统计文件中包含结点信息的行数
		if (ch >= 'a' && ch <= 'z'			// 以小写字母
			|| ch >= 'A' && ch <= 'Z'		// 大小写字母
			|| ch == '?') n++;				// 和问号'?'开始的行为结点信息
		Readln();							// 跳过一行
	}

	ElemType *elems = new ElemType[2 * n];	// 结点元素
	int *parents = new int[2 * n];			// 结点双亲
	int count = 0;							// 当前结点数

	inFile.clear();							// 清除EOFf标志
	inFile.seekg(0);						// 将输入流定位到开始处
	while ((ch = inFile.peek()) != EOF)
	{	// 输入森林结点信息
		if (ch >= 'a' && ch <= 'z'			// 以小写字母
			|| ch >= 'A' && ch <= 'Z'		// 大小写字母
			|| ch == '?')					// 和问号'?'开始的行为结点信息
		{
			ElemType e;						// 数据元素
			inFile >> e.student;			// 输入学生姓名
			inFile >> e.adivisor;			// 输入学生论文导师姓名
			inFile >> e.place;				// 输入授予博士学位的大学名称缩写
			inFile >> e.dataOfPHD;			// 输入授予博士学位的年份
			elems[count++] = e;				// 将元素存入数组elems中
		}
		else
		{	// 非结点信息行
			Readln();						// 跳过一行
		}
	}

	for (int pos = 0; pos < n; pos++)
	{	// 第pos个元素elems[pos]
		if (elems[pos].adivisor == "---" || elems[pos].adivisor == "?")
		{	// elems[pos]无双亲
			parents[pos] = -1;							
		}
		else
		{
			int par;						// 双亲
			for (par = 0; par < n; par++)
			{	// 查找元素elems[pos]的双亲
				if (elems[pos].adivisor == elems[par].student)
				{	// 找到elems[pos]的双亲
					parents[pos] = par;		// 元素elems[pos]的双亲为par
					break;
				}
			}

			if (par >= n)
			{	// 表示导师elems[pos].adivisor没有包含在elems中
				// 将导师elems[pos].adivisor存入elems
				elems[n].student = elems[pos].adivisor;							// 导师名
				elems[n].adivisor = elems[n].place = elems[n].dataOfPHD = "---";
					// 无双亲的导师的其它部都为"---"
				parents[pos] = n;
				n++;						// 在导师elems[pos].adivisor插入在elems后,结点个数自加1
			}
		}

	}

	pForest = new ParentForest<ElemType>(elems, parents, n, n);	// 生成森林 
	
	delete []elems;							// 释放elems存储空间
	delete []parents;						// 释放parents存储空间
}

TCSGenealogy::TCSGenealogy(): inFile("database.txt")
// 操作结果：建立理论计算机科学家族谱
{
	BuildForest();							// 建立由理论计算机科学家族谱组成的森林
}

TCSGenealogy::~TCSGenealogy()
// 操作结果：释放存储空间及关闭输入流
{
	delete pForest;							// 释放森林
	inFile.close();							// 关闭输入流
}

void TCSGenealogy::OutputHelp(ostream &outStream, int r, int level)
// 操作结果：输出理论计算机科学家族谱辅助函数，level为层次数，可设根结点的层次数为1
{
	if (r >= 0 && r < pForest->NodeCount())
	{	// 存在结点r,才显示r的信息
		outStream<<endl;					// 输出新行	
		for(int i = 0; i< level - 1; i++)
			outStream << "   ";				// 输出位置
		ElemType e;
		pForest->GetElem(r, e);				// 取出结点r的元素值

		outStream << e.student;				// 输出学生姓名
		outStream << "(";					// 输出插号"("
		if (e.place != "---") outStream << e.place << " ";
			// 输出授予博士学位的大学名称缩写
		if (e.dataOfPHD != "---") outStream << e.dataOfPHD;
			// 输出授予博士学位的年份
		outStream << ")";					// 输出插号")"

		for (int child = pForest->FirstChild(r); child != -1; child = pForest->RightSibling(child))
		{	// 依次显示各棵子树
			OutputHelp(outStream, child, level + 1);
		}
	}
}

void TCSGenealogy::Output(OutputType tp)
// 操作结果：输出理论计算机科学家族谱, tp为输出类型
{
	bool isFirstTree = true;				// 是否是第1棵树
	ofstream *pOutFile = NULL;				// 输出流 

	if (tp == OUTPUT_TO_FILE) 
	{	// 建立输出流
		pOutFile = new ofstream("viewtree.txt");
	}

	for (int cur = 0; cur < pForest->NodeCount(); cur++)
	{	// 查找森林中各棵树的根结点
		if (pForest->Parent(cur) == -1)				
		{	// 根结点
			if (isFirstTree) isFirstTree = false;
			else if (tp == OUTPUT_TO_SCREEN) system("PAUSE");

			if (tp == OUTPUT_TO_SCREEN) 
			{	// 在屏幕上输出理论计算机科学家族谱
				OutputHelp(cout, cur, 1);
				cout << endl;				// 换行
			}
			else 
			{	// 在输出流上输出理论计算机科学家族谱
				OutputHelp(*pOutFile, cur, 1);
				*pOutFile << endl;			// 换行
			}
		}
	}

	if (tp == OUTPUT_TO_FILE) 
	{	// 输出到文件
		pOutFile->close();					// 关闭文件
		delete pOutFile;					// 释放存储空间
	}
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
		&& ch != '\t')						// ch也不为制表符	
	{	// 将输入的字符追加到线性表中
		temp.Insert(++size, ch);
	}
	String answer(temp);					// 构造串
	inStr = answer;							// 用inStr返回串
	return inStream;						// 返回输入流对象
}

#endif
