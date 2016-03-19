#ifndef __HOSPITALIZE_H__
#define __HOSPITALIZE_H__

#include "lk_queue.h"					// 链队列

// 行医类
class Hospitalize
{
private:
//  行医类的数据成员:
	LinkQueue <unsigned int> queue;					// 病人队列

// 辅助函数
	void StandInALine();							// 排队
	void Cure();									// 就诊
	void Display();									// 查看排队

public:
//  方法声明及重载编译系统默认方法声明:
	Hospitalize(){};								// 无参数的构造函数
	~Hospitalize(){};								// 析构函数
	void Work();									// 医生工作
};

// 行医类的实现部分
void Hospitalize::StandInALine()
// 操作结果: 输入排队病人的病历号，加入到病人排队队列中
{
	unsigned int num;								// 病历号
	
	cout << "请输入病历号:"; 
	cin >> num;										// 输入排队病人
	queue.InQueue(num);								// 将病历号加入到病人排队队列中
}

void Hospitalize::Cure()
// 操作结果: 病人排队队列中最前面的病人就诊，并将其从队列中删除
{
	if (queue.Empty())
	{	// 无病人
		cout << "现已没有病人在排队了!" << endl;
	}
	else
	{
		unsigned int num;							// 病历号
		queue.OutQueue(num);						// 病人排队队列中最前面的病人就诊，并将其从队列中删除
		cout << num << "号病人现在就医." << endl;
	}
}

void Hospitalize::Display()
// 操作结果: 从队首到队尾列出所有的排队病人的病历号
{
	queue.Traverse(Write);							// 从队首到队尾列出所有的排队病人的病历号
	cout << endl;
}

void Hospitalize::Work()
// 操作结果: 医生工作
{
	int select = 0;

	while (select != 4)
	{
		cout << "1. 排队--输入病人的病历号，加入到病人队列中" << endl;
		cout << "2. 就诊--病人排队队列中最前面的病人就诊，并将其从队列中删除" << endl;
		cout << "3. 查看排队--从队首到队尾列出所有的排队病人的病历号" << endl;
		cout << "4. 下班--退出运行" << endl;
		cout << "请选择:";
		cin >> select;								// 选择功能
		switch(select)
		{
		case 1:
			StandInALine();		// 排队--输入病人的病历号，加入到病人队列中
			break;
		case 2:
			Cure();				// 就诊--病人排队队列中最前面的病人就诊，并将其从队列中删除
			break;
		case 3:
			Display();			// 查看排队--从队首到队尾列出所有的排队病人的病历号
			break;
		}
	}
}

#endif