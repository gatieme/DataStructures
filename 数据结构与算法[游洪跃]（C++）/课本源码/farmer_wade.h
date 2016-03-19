// 文件路径名: farmer_wade\farmer_wade.h
#ifndef __FARMER_WADE_H__
#define __FARMER_WADE_H__

#include "sq_list.h"								// 顺序表

// 过河对象枚举类型
enum Wader
{
	cabbage,	// 白菜
	goat,		// 羊
	wolf,		// 狼
	farmer		// 农夫
};

// 过河方向枚举类型
enum WadeDirection
{
	southToNorth,	// 由南岸到北岸
	northToSouth	// 由北岸到南岸
};


// 自定义串类 
class MyString
{
private:
// 串类的数据成员
	char strVal[5];									// 串值

public:                           
//  公共函数
	MyString(int value = 0);						// 构造函数
	MyString(char strValue[]);						// 构造函数
	virtual ~MyString(){};							// 析构函数
	operator int() const;							// 类类型转换函数
	char &operator [](int pos);						// 重载下标运算符
};

// 自定义串类的实现部分
MyString::MyString(int value)
// 操作结果：构造函数,将整数转换为二进制串 
{
	int mask = 1;									// 屏蔽字
	strVal[4] = '\0';								// 串结束符
	for (int pos = 3; pos >= 0; pos--)
	{	// 依次取出二进制的各位
		strVal[pos] = value & mask ? '1' : '0';		// 取出1位二进制数
		mask = mask << 1;							// 左移1位
	}
}

MyString::MyString(char strValue[])
// 操作结果：构造函数, 由C风格串构造C++风格串
{
	strcpy(strVal, strValue);
}

MyString::operator int() const
// 操作结果：类类型转换函数, 将二进制串类型转换为整型
{
	int val = 0;									// 整型值
	for (int pos = 0; pos < 4; pos++) 
	{	// 将二进制串类型转换为整型
		val = val * 2 + strVal[pos] - '0';
	}
	return val;										// 返回整型值
}

char &MyString::operator [](int pos)
// 操作结果：重载下标运算符
{
	return strVal[pos];					
}

// 农夫过河类
class FarmerWade
{
private:
// 农夫过河类的数据成员
	int path[16];							// 表示路径,如某状态state未出现过,用-1表示,则否为前驱状态

// 辅助函数
	bool WithFarmer(Wader wader, MyString &state) const;	// 过河者wader是否与farmer在河的同一侧
	bool IsSafe(MyString &state) const;		// 判断状态是否安全
	void DisplayRoute();					// 显示过河方案
	void Init();							// 初始化路径
	void DFS(MyString curState = "0000");	// 深度优先搜索过河的方案

public:
//  公共函数
	FarmerWade(){};							// 无参数的构造函数
	virtual ~FarmerWade(){};				// 析构函数
	void Run();								// 运行农夫过河

};

// 农夫过河类的实现部分
bool FarmerWade::WithFarmer(Wader wader, MyString &state) const
// 操作结果：过河者wader是否与农夫farmer在河的同一侧
{
	return (state[wader] == state[farmer]);
}

bool FarmerWade::IsSafe(MyString &state) const
// 操作结果：判断状态是否安全
{
	if (state[goat] == state[cabbage] && state[farmer] != state[cabbage] ||			// 羊吃白菜
		state[wolf] == state[goat] && state[farmer] != state[goat]) return false;	// 狼吃羊
	else return true;
}

void FarmerWade::DisplayRoute()
// 操作结果：显示过河方案
{
	if (path[15] == -1)
	{	// path[15]无前驱,表示不能成功到达目的状态
		cout << "农夫过河问题无解" << endl;
		return;
	}

	SqList<MyString> statePath;				// 用串存储状态路径
	int state;								// 临时变量 
	for (state = 15; state >= 0; state = path[state])
	{	// 反向插入,完成从初始状态到目的状态的转换
		statePath.Insert(1, state);			// 此状要用到MyString的构造函数,自动将整数转换为MyString的串
	}

	WadeDirection direction = southToNorth;	// 过河方向
	MyString current, next;					// 当前状态,下一状态
	for (int step = 1; step < statePath.Length(); step++)
	{	// 依次显示过河的每一步
		statePath.GetElem(step, current);	// 取出当前状态
		statePath.GetElem(step + 1, next);	// 取出下一状态
		Wader wader; 
		for (int w = 0; w <= 3; w++)
		{	// 获取状态发生变化的第1个过河者
			if (current[w] != next[w])
			{	// 状态发生变化
				wader = (Wader)w;		
				break;
			}
		}

		cout << "步骤" << step << ": ";
		switch (wader)
		{
		case cabbage:
			cout << "农夫把白菜带" << ((direction == southToNorth) ? "到北岸" : "回南岸") << endl;
			break;
		case goat:
			cout << "农夫把羊带" << ((direction == southToNorth) ? "到北岸" : "回南岸") << endl;
			break;
		case wolf:
			cout << "农夫把狼带" << ((direction == southToNorth) ? "到北岸" : "回南岸") << endl;
			break;
		case farmer:
			cout << "农夫独自" << ((direction == southToNorth) ? "到北岸" : "回南岸") << endl;
			break;
		}
		direction = ((direction == southToNorth) ? northToSouth : southToNorth);	// 改变方向
	}

	cout << "祝贺您! 过河问题求解成功!" << endl;
}

void FarmerWade::Init()
// 操作结果：初始化路径
{
	for (int pos = 0; pos < 16; pos++) path[pos] = -1;
}

void FarmerWade::DFS(MyString curState)
// 操作结果：深度优先搜索过河的方案
{
	if (path[15] == -1)
	{	// 尚未到达最终状态
		for (int companion = 0; companion <= 3; companion++)
		{	// 过河者
			if (WithFarmer((Wader)companion, curState))
			{	// 随农夫过河的只能与农夫在同一河岸
				MyString nextState = curState;	// 下一状态
				nextState[farmer] = ((nextState[farmer] == '0') ? '1' : '0');// 农夫必定过河
				if (companion != (int)farmer)
				{	// 不是农夫单独过河
					nextState[companion] = ((nextState[companion] == '0') ? '1' : '0');
				}
				if (IsSafe(nextState) && path[nextState] == -1 && nextState != 0)
				{	// 利用类类型转换函数自动进行MyString -> int
					path[nextState] = curState;	// 当前状态与下一状态的联系
					DFS(nextState);				// 从下一状态继续进行索搜
				}
			}
		}
	}
}

void FarmerWade::Run()
// 操作结果：运行农夫过河
{
	Init();			// 初始化路径
	DFS();			// 深度优先搜索过河的方案
	DisplayRoute();	// 显示过河方案
}

#endif
