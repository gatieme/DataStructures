// 文件路径名: call_simulation\call_simulation.h 
#ifndef __CALL_SIMULATION_H__
#define __CALL_SIMULATION_H__

#include "lk_queue.h"							// 链队列类

// 客户类型
struct CustomerType
{
	int arrivalTime;							// 客户到达时刻
	int duration;								// 客户接受服务所需的时间
	int curServiceTime;							// 当前接受服务的时间
};

// 电话客户服务模拟类
class CallSimulation
{
private:
//  电话客户服务模拟类的数据成员:
	LinkQueue<CustomerType> *callsWaitingQueue;	// 客服电话等待队列
	CustomerType *customerServed;				// 客服人员正在服务的客户
	int curTime;								// 当前时间
	int totalWaitingTime;						// 总等待时间
	int numOfCalls;								// 处理的电话数
	int numOfCustomerServiceStaffs;				// 客服人员的人数
	int limitTime;								// 时间限制(不再接受更多电话)
	double arrivalRate;							// 客户到达率
	int averageServiceTime;						// 平均服务时间

// 辅助函数
	void Service();								// 服务当前电话(有果有电话)
	void CheckForNewCall();						// 检查是否有新电话,如果有,则将电话添加到电话队列
	void Display();								// 显示模拟结果
	int GetNumOfWaitingCall();					// 得到电话队列中等待的电话数
	int MinLengthCallsWaitingQueue();			// 最短客服电话等待队列
	int MaxLengthCallsWaitingQueue();			// 最长客服电话等待队列

public:
// 电话客户服务模拟类方法声明:
	CallSimulation();							// 无参数的构造函数
	virtual ~CallSimulation();					// 析构函数
	void Run();									// 模拟电话客户服务
};

// 电话客户服务模拟类的实现部分
CallSimulation::CallSimulation()
// 操作结果：初始化数据成员
{
	// 初始化数据成员
	curTime = 0;								// 当前时间初值为0
	totalWaitingTime = 0;						// 总等待时间初值为0
	numOfCalls = 0;								// 处理的电话数初值为0

	// 获得模拟参数
	cout << "输入客服人员的人数:";
	cin >> numOfCustomerServiceStaffs;			// 输入客服人员的人数 
	cout << "输入时间限制:";
	cin >> limitTime;							// 不再接受新电话的时间
	int callsPerHour;							// 每小时电话数
	cout << "输入每小时电话数:";
	cin >> callsPerHour;						// 输入每小时电话数
	arrivalRate = callsPerHour / 60.0;			// 转换为每分钟电话数
	cout << "输入平均服务时间:";
	cin >> averageServiceTime;					// 输入平均服务时间

	// 分配动态存储空间
	callsWaitingQueue = new LinkQueue<CustomerType>[numOfCustomerServiceStaffs];
		// 为客服电话等待队列数组分配存储空间
	customerServed = new CustomerType[numOfCustomerServiceStaffs];	
		// 为客服人员正在服务的客户分配存储空间

	// 初始化客服人员正在服务的客户
	for (int i = 0; i < numOfCustomerServiceStaffs; i++)
	{	// 初始化每个客服人员正在服务的客户
		customerServed[i].curServiceTime = customerServed[i].duration = 0;	
			// 表示还没人接受服务
	}

	// 设置随机数种子
	SetRandSeed();								// 以当前时间值为随机数种子
}

CallSimulation::~CallSimulation()
// 操作结果：释放存储空间
{
	delete []callsWaitingQueue;					// 释放分客服电话等待队列数组所占用的存储空间
	delete []customerServed;					// 释放客服人员正在服务的客户所占用的存储空间
}

void CallSimulation::Run()
// 操作结果：模拟电话客户服务
{
	while (curTime < limitTime)
	{	// 未到达时间限制, 可检查新电话
		CheckForNewCall();						// 检查是否有新电话,如果有,则将电话添加到电话队列
		Service();								// 进行服务
		curTime++;								// 增加时间
	}

	while (callsWaitingQueue[MaxLengthCallsWaitingQueue()].Length() > 0)
	{	// 在服电话等待队列中还有客户在等待服务
		Service();								// 进行服务
		curTime++;								// 增加时间
	}

	Display();									// 显示模拟结果
}

void CallSimulation::Service()
// 操作结果：服务当前电话(有果有电话)
{
	for (int i = 0; i < numOfCustomerServiceStaffs; i++)
	{	// 处理每个客服工作人员提供的服务
		if (customerServed[i].curServiceTime < customerServed[i].duration)
		{	// 未到达客户接受服务所需的时间, 正在为客户提供服备
			customerServed[i].curServiceTime++;	// 增加客户接受服务时间	
		}
		else
		{	// 已到达客户接受服务所需的时间, 为下一客户提供服务
			if (!callsWaitingQueue[i].Empty())
			{	// 有客户在等待
				callsWaitingQueue[i].OutQueue(customerServed[i]);	// 从等待队列中取出新客户进行服务
				totalWaitingTime += curTime - customerServed[i].arrivalTime;	// 更新总等待时间
			}
		}
	}
}

void CallSimulation::CheckForNewCall()
// 操作结果：检查是否有新电话,如果有,则将电话添加到电话队列
{
	int calls = GetPoissionRand(arrivalRate);	// 当前时间打进电话的人数
	
	for (int i = 1; i <= calls; i++)
	{	// 第i个电话
		CustomerType customer;					// 客户
		customer.arrivalTime = curTime;			// 客户到达时间
		customer.duration = GetPoissionRand(averageServiceTime);	// 客户接受服务所需的时间
		customer.curServiceTime = 0;			// 当前接受服务的时间
		int pos = MinLengthCallsWaitingQueue();	// 最短客服电话等待队列的位置
		callsWaitingQueue[pos].InQueue(customer);	// 客户入等待队列
		numOfCalls++;							// 处理的电话数
	}
}

void CallSimulation::Display()
// 操作结果：显示模拟结果
{
	cout << "处理的总电话数:" << numOfCalls << endl;
	cout << "平均等待时间:" << (double)totalWaitingTime / numOfCalls << endl << endl;
}

int CallSimulation::GetNumOfWaitingCall()
// 操作结果：得到电话队列中等待的电话数
{
	int n = 0;									// 电话数初始化为0
	
	for (int i = 0; i < numOfCustomerServiceStaffs; i++)
	{	// 第i个最短客服电话队列
		n += callsWaitingQueue[i].Length();		// 累加第i个电话队列中的等待人数
	}

	return n;									// 返回电话队列中等待的电话数
}

int CallSimulation::MinLengthCallsWaitingQueue()
// 操作结果：得到最短客服电话等待队列
{
	int pos = 0;								// 当前最短客服电话等待队列

	for (int i = 1; i < numOfCustomerServiceStaffs; i++)
	{	// 第i个客服电话队列
		if (callsWaitingQueue[i].Length() < callsWaitingQueue[pos].Length())
		{	// 第i个客服电话队列更短
			pos = i;							// 第i个客服电话队列为新的最短客服电话等待队列
		}
	}

	return pos;									// 返回最短客服电话等待队列
}

int CallSimulation::MaxLengthCallsWaitingQueue()
// 操作结果：得到最长客服电话等待队列
{
	int pos = 0;								// 当前最短客服电话等待队列

	for (int i = 1; i < numOfCustomerServiceStaffs; i++)
	{	// 第i个客服电话队列
		if (callsWaitingQueue[i].Length() > callsWaitingQueue[pos].Length())
		{	// 第i个客服电话队列更短
			pos = i;							// 第i个客服电话队列为新的最短客服电话等待队列
		}
	}

	return pos;									// 返回最短客服电话等待队列
}

#endif