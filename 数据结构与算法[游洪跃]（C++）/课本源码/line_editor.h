// 文件路径名:line_LineEditor\line_LineEditor.h
#ifndef __LINE_LineEditor_H__
#define __LINE_LineEditor_H__

#include "dbl_lk_list.h"				// 双向链表
#include "string.h"						// 字符串

// 文本编辑类
class LineEditor
{
private:
// 文本编辑类的数据成员:
	DblLinkList<String> textBuffer;		// 文本缓存
	int curLineNo;						// 当前行号
	DblLinkList<String> textUndoBuffer;	// 用于恢复的文本缓存
	int curUndoLineNo;					// 用于恢复的当前行号
	ifstream inFile;					// 输入文件
	ofstream outFile;					// 输出文件

// 辅助函数:
	StatusCode NextLine();				// 转到下一行
	StatusCode PreviousLine();			// 转到前一行
	StatusCode GotoLine();				// 转到指定行
	StatusCode InsertLine();			// 插入一行	
	void ChangeLine();					// 替换当前行或所有行的指定文本串
	void ReadFile();					// 读入文本文件
	void WriteFile();					// 写文本文件
	void FindString();					// 查找串

public:
//  方法声明:
	LineEditor(char infName[], char outfName[]);	// 构造函数
	void Run();							// 运行文本编辑器
};

// 文本编辑类的实现部分
LineEditor::LineEditor(char infName[], char outfName[]):inFile(infName), outFile(outfName)
// 操作结果: 用输入文件名infName和输出文件名outfName构造编辑器——构造函数
{
	if (inFile == NULL) throw Error("打开输入文件失败!");	// 抛出异常
	if (outFile == NULL) throw Error("打开输出文件失败!");	// 抛出异常
	ReadFile();												// 读入文本件
}

void LineEditor::Run()
// 操作结果: 运行文本编辑器
{
	char userCommand;							// 用户命令

	do
	{
		String tempString;						// 临时串
		String curLine;							// 当前行

		if (curLineNo != 0)
		{	// 存在当前行
			textBuffer.GetElem(curLineNo, curLine);	// 取出当前行
			cout << curLineNo << " : "			// 显示行号
				<< curLine.CStr() << endl << "?";	// 显示当前行及问号?
		}
		else
		{	// 不存在当前行
			cout << "文件缓存空" << endl << "?";
		}

		userCommand = GetChar();				// 忽略空格并取得操作命令字符
		userCommand = tolower(userCommand);		// 转换为小字字母
		while (cin.get() != '\n');				// 忽略用户输入的其他字符

		if (userCommand != 'u' && userCommand != 'h' && 
			userCommand != '?' && userCommand != 'v')
		{	// 存储撤消信息
			textUndoBuffer = textBuffer;		// 用于撤消的缓存
			curUndoLineNo = curLineNo;			// 用于撤消的行号
		}
		// 运行操作命令
		switch (userCommand) 
		{
		case 'b':	// 转到第1行b(egin)
			if (textBuffer.Empty())
			{	// 文本缓存空
				cout << " 警告: 文本缓存空 " << endl;
			}
			else
			{	// 文本缓存非空, 转到第1行
				curLineNo = 1;
			}
			break;
		case 'c':	// 替换当前行或所有行c(hange)
			if (textBuffer.Empty())
			{
				cout << " 警告: 文本缓存空" << endl;
			}
			else
			{	// 替换操作
				ChangeLine();
			}
			break;
		case 'd':	// 删除当前行d(elelete)
			if (textBuffer.Delete(curLineNo, tempString) != SUCCESS)
			{	// 删除当前行失败
				cout << " 错误: 删除失败 " << endl;
			}
			break;
		case 'e':	// 转到最后一行e(nd)
			if (textBuffer.Empty())
			{
				cout << " 警告: 文本缓存空 " << endl;
			}
			else
			{	// 转到最后第一行
				curLineNo = textBuffer.Length();
			}
			break;
		case 'f':	// 从当前行或第1行开始查找指定文本f(ind)
			if (textBuffer.Empty())
			{
				cout << " 警告: 文本缓存空 " << endl;
			}
			else
			{	// 从当前行开始查找指定文本
				FindString();
			}
			break;
		case 'g':	// 转到指定行g(o)
			if (GotoLine() != SUCCESS)
			{	// 转到指定行失败
				cout << " 警告: 没有那样的行" << endl;
			}
			break;
		case '?':	// 获得帮助?
		case 'h':	// 获得帮助h(elp)
			cout << "有效命令: b(egin) c(hange) d(el) e(nd)" << endl
				<< "f(ind) g(o) h(elp) i(nsert) n(ext) p(rior)" << endl
				<< "q(uit) r(ead) u(ndo) v(iew) w(rite) " << endl;
			break;
		case 'i':	// 插入指定行i(nsert)
			if (InsertLine() != SUCCESS)
				cout << " 错语: 插入行出错 " << endl;
			break;
		case 'n':	// 转到下一行n(ext)
			if (NextLine() != SUCCESS)
			{	// 无下一行
				cout << " 警告: 当前行已是最后一行" << endl;
			}
			break;
		case 'p':	// 转到前一行p(rior)
			if (PreviousLine() != SUCCESS)
			{	// 无前一行
				cout << " 警告: 当前行已是第一行" << endl;
			}
			break;
		case 'q':	// 退出p(uit)
			break;
		case 'r':	// 读入文本件r(ead)
			ReadFile();
			break;
		case 'u':	// 撤消上次操作u(ndo)
			Swap(textUndoBuffer, textBuffer);	// 交换textUndoBuffer与textBuffer
			Swap(curUndoLineNo, curLineNo);		// 交换curUndoLineNo与curLineNo
			break;
		case 'v':	// 显示文本v(iew)
			textBuffer.Traverse(Write);
			break;
		case 'w':	// 写文本缓存到输出文件中w(rite)
			if (textBuffer.Empty())
			{	// 文本缓存空
				cout << " 警告: 文本缓存空" << endl;
			}
			else
			{	// 写文本缓存到输出文件中
				WriteFile();
			}
			break;
		default :
			cout << "输入h或?获得帮助或输入有效命令字符: \n";
		}
	}
	while (userCommand != 'q');
}

StatusCode LineEditor::NextLine()
// 操作结果: 转到下一行
{
	if( curLineNo >= textBuffer.Length())
	{	// 当前行号已是最后一行
		return FAIL;
	}
	else
	{	// 当前行号不是最后一行
		curLineNo++;
		return SUCCESS;
	}
}

StatusCode LineEditor::PreviousLine()
// 操作结果: 转到前一行
{
	if(curLineNo <= 1)
	{	// 当前行号已是第一行
		return FAIL;
	}
	else
	{	// 当前行号不是第一行
		curLineNo--;
		return SUCCESS;
	}
}

StatusCode LineEditor::GotoLine()
// 操作结果: 转到指定行
{
	int lineNumber;
	cout << " 输入指定的行号: ";
	cin  >> lineNumber;
	if(lineNumber < 1 || lineNumber > textBuffer.Length())
	{	// 行号范围错
		return RANGE_ERROR;
	}
	else
	{	// 行号范围正确
		curLineNo = lineNumber;
		return SUCCESS;
	}
}

StatusCode LineEditor::InsertLine()
// 操作结果: 插入指定行
{
	int lineNumber;	
	cout << " 输入指定行号? ";
	cin  >> lineNumber;
	while (cin.get() != '\n');			// 跳过其他字符
	cout << " 输入新行文本串: ";
	String toInsert = Read(cin);		// 插入行
	if (textBuffer.Insert(lineNumber, toInsert) == SUCCESS)
	{	// 插入成功
		curLineNo = lineNumber;
		return SUCCESS;
	}
	else
	{	// 插入失败
		return RANGE_ERROR;
	}
}

void LineEditor::ChangeLine()
// 操作结果: 用户输入指定文本串，在当前行或所有行中用输入的新文本串替换指定文本串
//	替换成功返回SUCCESS，否则返回FAIL
{
	char answer;						// 用户回答字符
	bool initialResponse = true;		// 初始回答

	do
	{	// 循环直到用户输入恰当的回答为止
		if (initialResponse)
		{	// 初始回答
			cout << "替换当前行c(urrent)或替换所有行a(ll):";
		}
		else
		{	// 非初始回答
			cout << "用c或a回答:";
		}
		
		answer = GetChar();				// 从输入流跳过空格及制表符获取一字符
		while (cin.get() != '\n');		// 忽略用户输入的其他字符
		answer = tolower(answer);		// 转换为小字字母
		initialResponse = false;
	} while (answer != 'c' && answer != 'a');

	cout << " 输入要被替换的指定文本串: ";
	String strOld = Read(cin);			// 旧串
	cout << " 输入新文本串:";
	String strNew = Read(cin);			// 新串

	for (int row = 1; row <= textBuffer.Length(); row++)
	{
		if (answer == 'c' && row != curLineNo)
		{	// 只替换当前行,row不为当前行
			continue;							// 进入下一趟循环
		}

		String strRow;							// 行	
		textBuffer.GetElem(row, strRow);		// 取出行
		int index = Index(strRow, strOld);		// 在当前行中查找旧文本	
		if (index != -1) 
		{	// 模式匹配成功
			String newLine;						// 新行
			Copy(newLine, strRow, index);		// 复制指定文本前的串
			Concat(newLine, strNew);			// 连接新文本串
			const char *oldLine = strRow.CStr();// 旧行
			Concat(newLine, (String)(oldLine + index + strlen(strOld.CStr())));
				// 连接指定文本串后的串,oldLine + index + strlen(oldText.CStr())用于计算一个
				// 临时指针，指向紧跟在被替换字符串后的字符, 然后将C风格串转换成String，并
				// 被连接到newline的后面。
			textBuffer.SetElem(row, newLine);		// 设置当前行新串
		}
	}
}

void LineEditor::ReadFile()
// 操作结果: 读入文本件
{
	bool proceed = true;
	if (!textBuffer.Empty()) 
	{	// 文本缓存非空
		cout << "文本缓存非空; 读入文件时将复盖它." << endl;
		cout << " 回答yes将执行此操作? " << endl;
		if (proceed = UserSaysYes()) 
		{	// 回答yes
			textBuffer.Clear();	// 清空缓存
		}
	}

	int lineNumber = 1;			// 起始行号	
	char terminalChar;			// 行终止字符
	while (proceed) 
	{
		String inString = Read(inFile, terminalChar);	// 读入一行文本
		if (terminalChar == EOF) 
		{	// 以文件结束符结束, 输入已结束
			proceed = false;
			if (strlen(inString.CStr()) > 0) 
			{	// 插入非空行
				textBuffer.Insert(lineNumber , inString);		
			}
		}
		else
		{	// 输入未结束
			textBuffer.Insert(lineNumber++, inString);
		}
	}

	textUndoBuffer = textBuffer;	// 用于撤消的缓存
	if (textBuffer.Empty())
	{	// 当前文本缓存为空
		curLineNo = 0;				// 表示缓存为空
		curUndoLineNo = 0;			// 用于撤消的行号
	}
	else
	{	// 当前文本缓存非空
		curLineNo = 1;				// 表示缓存非空
		curUndoLineNo = 1;			// 用于撤消的行号
	}
}

void LineEditor::WriteFile()
// 操作结果: 写文本缓存到输出文件中
{
	String curLine;			// 当前行
    int lineNumber;			// 行号
	for(lineNumber=1; lineNumber <= textBuffer.Length(); lineNumber++)
	{	// 写文本缓存各行到输出文件中
		textBuffer.GetElem(lineNumber, curLine);	// 取出当前行
		outFile << curLine.CStr() << endl;	// 输出当前行
	}
}

void LineEditor::FindString()
// 操作结果: 从当前行或第1行开始查找指定文本
{
	char answer;						// 用户回答字符
	bool initialResponse = true;		// 初始回答

	do
	{	// 循环直到用户输入恰当的回答为止
		if (initialResponse)
		{	// 初始回答
			cout << "从第1行开始f(irst)或从当行开始c(urrent):";
		}
		else
		{	// 非初始回答
			cout << "用f或c回答:";
		}
		
		answer = GetChar();				// 从输入流跳过空格及制表符获取一字符
		while (cin.get() != '\n');		// 忽略用户输入的其他字符
		answer = tolower(answer);		// 转换为小字字母
		initialResponse = false;
	} while (answer != 'f' && answer != 'c');
	if (answer == 'f') curLineNo = 1;	// 从第1行开始
	
	int index;
	cout << "输入被查找的文本串:";
	String searchString = Read(cin);		// 输入查找文本串
	String curLine;							// 当前行	
	textBuffer.GetElem(curLineNo, curLine);	// 取出当前行
	while ((index = Index(curLine, searchString)) == -1)
	{	// 查找指定文本串
		if (curLineNo < textBuffer.Length()) 
		{	// 查找下一行
			curLineNo++;					// 下一行
			textBuffer.GetElem(curLineNo, curLine);// 取出下一行
		}
		else
		{	// 已查找完所有行
			break;
		}
	}
	
	if (index == -1) 
	{	// 查找失败
		cout << "查找串失败.";
	}
	else 
	{	// 查找成功
		cout << curLine.CStr() << endl;		// 显示行
		for (int i = 0; i < index; i++)
		{	// 在查找串前的位置显行空格
			cout << " ";
		}
		for (int j = 0; j < (int)strlen(searchString.CStr()); j++)
		{	// 在查找串前的位置显行^
			cout << "^";
		}
   }
   cout << endl;
}

#endif