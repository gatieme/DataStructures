// 文件路径名: dictionary_anagram_search_system\dictionary_anagram_search_system.h
#ifndef __DICTIONARY_ANAGRAM_SEARCH_SYSTEM_H__
#define __DICTIONARY_ANAGRAM_SEARCH_SYSTEM_H__

#include "string.h"								// 串
#include "quick_sort.h"							// 快速排序
#include "bin_serach.h"							// 折半查找

// 词典变位词检索系统类
class DictionaryAnagramSearchSystem
{
private:
// 词典变位词检索系统类的数据成员
	String *dict;								// 词典
	int size;									// 单词数

// 辅助函数
	void AllArrageCreateAnagram(String word, String &anagram, int curLen = 0);
		// 由word各字符的全排列产生变位词

public:
//  公共函数
	DictionaryAnagramSearchSystem();			// 无参数的构造函数
	virtual ~DictionaryAnagramSearchSystem();	// 析构函数
	void Run();									// 运行词典变位词检索系统

};

// 相关函数
istream &operator >>(istream &inStream, String &inStr);			// 重载输入运算符>>
ostream &operator <<(ostream &outStream, const String &outStr);	// 重载输出运算符<<
void readln(istream &inStream);	// 从输入流inStream跳过一行

// 词典变位词检索系统类及相关函数的实现部分
void DictionaryAnagramSearchSystem::AllArrageCreateAnagram(String word, String &anagram, int curLen)
// 操作结果：由word各字符的全排列产生变位词
{
	if (curLen == anagram.Length())
	{	// 产生一个可能的变位词
		if (anagram != word && BinSerach(dict, size, anagram) >= 0)
		{	// word为词典中的单词
			cout << anagram << " ";				// 输出变位词
		}
	}
	else
	{	// 对解空间进行前序遍历，anagram[curLen..anagram.Length()-1]有多个排列，递归
		// 的生成排列j
		for (int pos = curLen; pos < anagram.Length(); pos++)
		{	// 依次取出anagram[curLen..anagram.Length()-1]中的字符
			Swap(anagram[curLen], anagram[pos]);// 交换anagram[curLen]与anagram[pos]
			AllArrageCreateAnagram(word, anagram, curLen + 1);	// 递归的生成排列
			Swap(anagram[curLen], anagram[pos]);// 交换anagram[curLen]与anagram[pos]
		}
	}
}

DictionaryAnagramSearchSystem::DictionaryAnagramSearchSystem()
// 操作结果：读词典文件
{
	ifstream dictFile("diction.txt");			// 词典文件
	if (dictFile == NULL) throw Error("打开文件失败!");	// 抛出异常
	size = 0;									// 统计单词数
	char ch;									// 临时变量
	
	cout << "正在统计词典包含的单词数..." << endl;
	while ((ch = dictFile.peek()) != EOF && ch != '\n')
	{	// 当前行的第一个字符不是文件结束符与换行符, 统计单词数
		readln(dictFile);						// 跳过一行
		size++;									// 一个单一行
	}
	cout << "词典包含有" << size << "个单词" << endl;

	cout << "正在读取词典..." << endl;
	dict = new String[size];					// 分配存储空间
	dictFile.clear();							// 清除EOF标志
	dictFile.seekg(0);							// 定位到文件头
	for (int pos = 0; pos < size; pos++)
	{	// 读入单词
		dictFile >> dict[pos];
	}

	cout << "正在进行排序..." << endl;
	QuickSort(dict, size);						// 对单词进行排序

	dictFile.close();							// 关闭文件
}

DictionaryAnagramSearchSystem::~DictionaryAnagramSearchSystem()
// 操作结果：释放读词典信息
{
	delete []dict;
}				

void DictionaryAnagramSearchSystem::Run()
// 操作结果：运行词典变位词检索系统
{
	do 
	{
		String word;
		cout << "输入单词:";
		cin >> word;
		cout << word << "的变位词有:";
		AllArrageCreateAnagram(word, word);		// 由word各字符的全排列产生变位词
		cout << endl;
		cout << "是否继续";
	} while (UserSaysYes());
}

istream &operator >>(istream &inStream, String &inStr)
// 操作结果：重载运算符>>
{
	LinkList<char> temp;						// 临时线性表
	int length = 0;								// 初始线性表长度
	char ch= GetChar(inStream);					// 从输入流inStream中跳过空格及制表符获取一字符
	inStream.putback(ch);						// 将c回送输入流
	while ((ch = inStream.peek()) != EOF &&		// peek()从输入流中取一个字符
												// 输入流指针不变
		(ch = inStream.get()) != '\n')			// get()从输入流中取一个字符ch,ch不为换行符
	{	// 将输入的字符追加到线性表中
		temp.Insert(++length, ch);
	}
	String answer(temp);						// 构造串
	inStr = answer;								// 用inStr返回串
	return inStream;							// 返回输入流对象
}

ostream &operator <<(ostream &outStream, const String &outStr)
// 操作结果：重载运算符<<
{
	cout << outStr.CStr();						// 输出串值
	return outStream;							// 返回输出流对象
}

void readln(istream &inStream)
// 操作结果：从输入流inStream跳过一行
{
	char ch;									// 临时变量
	while ((ch = inStream.peek()) != EOF &&		// peek()从输入流中取一个字符
												// 输入流指针不变
		(ch = inStream.get()) != '\n');			// get()从输入流中取一个字符ch,ch不为换行符与文件结束符
}

#endif

