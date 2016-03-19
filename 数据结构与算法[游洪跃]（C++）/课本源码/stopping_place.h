#ifndef __STOPPING_PLACE_H__
#define __STOPPING_PLACE_H__

#include "lk_list.h"							// 链表
#include "lk_stack.h"							// 链栈

// 文件路径名:stopping_place\stopping_place.h
struct VehicleType
{	// 车辆类型
	unsigned int num;							// 车辆编号
	unsigned int time;							// 到达/离开时间
};
ostream &operator <<(ostream &outStream, const VehicleType &vehicle);
	// 重载输出运算符<<	

// 停车场类
class StoppingPlace
{
private:
// 停车场类的数据成员:
	LinkStack<VehicleType> *pStopPath;			// 停车场的停车道
	LinkList<VehicleType> *pShortcutPath;		// 便道
	int maxNumOfStopVehicle;					// 停车场的停车道停放车辆的最大数
	int rate;									// 停单位时间的收费值

// 辅助函数
	bool ExistVehicleInStopPath(const VehicleType &vehicle) const;
		// 停车场的停车道中是否存在车辆vehicle
	int LocateInpShortcutPath(const VehicleType &vehicle) const;		
		// 在便道中查找车辆vehicle的位置

public:
//  方法声明及重载编译系统默认方法声明:
	StoppingPlace(int n, int r);				// 构造函数
	virtual ~StoppingPlace();					// 析构函数
	void DisplayStatus() const;					// 显示停车道与便道中车辆状态
	void Arrive(const VehicleType &vehicle);	// 处理车辆到达的情形
	void Leave(const VehicleType &vehicle);		// 处理车辆离开的情形
};

// 停车场类及相关函数的实现部分
ostream &operator <<(ostream &outStream, const VehicleType &vehicle) 
// 操作结果: 重载输出运算符<<
{
	cout << "(" << vehicle.num << "," << vehicle.time << ")  "; 
		// 输出车辆编号与到达时间
	return outStream;
}

bool StoppingPlace::ExistVehicleInStopPath(const VehicleType &vehicle) const
// 操作结果: 停车场的停车道中是否存在车辆vehicle
{
	VehicleType ve;								// 临时元素
	LinkStack<VehicleType> tmpS;				// 临时栈
	bool found = false;							// 表示是否找到车辆
	
	while (!pStopPath->Empty() && !found)
	{	// 检查停车场的停车道的车辆
		pStopPath->Pop(ve);						// 车辆出栈
		tmpS.Push(ve);							// 车辆入临时栈
		if (vehicle.num == ve.num)
		{	// 已找到车辆
			found = true;
		}
	}
	while (!tmpS.Empty())
	{	// 将临时栈中的车辆送回停车道pStopPath
		tmpS.Pop(ve);							// 车辆出栈
		pStopPath->Push(ve);					// 车辆入栈
	}

	return found;
}

int StoppingPlace::LocateInpShortcutPath(const VehicleType &vehicle) const
// 操作结果: 在便道中查找车辆vehicle的位置, 查找成功,返回正数,否则返回0
{
	VehicleType ve;								// 临时元素
	
	for (int pos = 1; pos <= pShortcutPath->GetElem(pos, ve); pos++)
	{	// 查找在便道中的车辆
		if (vehicle.num == ve.num)
		{	// 已找到车辆
			return pos;							// 返回车辆位置
		}
	}

	return 0;									// 查找失败
}

StoppingPlace::StoppingPlace(int n, int r)
// 操作结果: 停车道停放车辆的最大数为n, 停单位时间的收费值为r的停车场对象
{
	pStopPath = new LinkStack<VehicleType>;		// 生成停车场的停车道
	pShortcutPath = new LinkList<VehicleType>;	// 生成便道
	maxNumOfStopVehicle = n;					// 停车场的停车道停放车辆的最大数
	rate = r;									// 停单位时间的收费值
}

StoppingPlace::~StoppingPlace()
// 操作结果: 释放存储空间
{
	delete pStopPath;							// 释放停车场的停车道
	delete pShortcutPath;						// 释放便道
}


void StoppingPlace::DisplayStatus() const
// 操作结果: 显示停车道与便道中车辆状态
{
	cout << "停车道中的车辆:";
	pStopPath->Traverse(Write);
	cout << endl;

	cout << "便道中的车辆:";
	pShortcutPath->Traverse(Write);
	cout << endl << endl;
}

void StoppingPlace::Arrive(const VehicleType &vehicle)
// 操作结果: 处理车辆到达的情形
{
	if (pStopPath->Length() < maxNumOfStopVehicle)
	{	// 停车场未满
		pStopPath->Push(vehicle);				// 车辆进入停车场的停车道
	}
	else
	{	// 停车场已满
		pShortcutPath->Insert(pShortcutPath->Length() + 1, vehicle);	
			// 车辆进入便道
	}
}

void StoppingPlace::Leave(const VehicleType &vehicle)
// 操作结果: 处理车辆离开的情形
{
	LinkStack<VehicleType> tmpS;				// 临时栈
	VehicleType ve;								// 临时元素

	if (ExistVehicleInStopPath(vehicle))
	{	// 车辆在停车道中
		for (pStopPath->Pop(ve); vehicle.num != ve.num; pStopPath->Pop(ve))
		{	// 在停车道中查找车辆
			tmpS.Push(ve);						// 车辆入栈
		}
		cout << "在停车道中存在编号为" << vehicle.num << "的车辆" << endl;
		cout << "此车将离开, 应收停车费" << (vehicle.time - ve.time) * rate << "元." << endl;
		while (!tmpS.Empty())
		{	// 将临时栈中的车辆送回停车道pStopPath
			tmpS.Pop(ve);						// 车辆出栈
			pStopPath->Push(ve);				// 车辆入栈
		}
		if (!pShortcutPath->Empty())
		{	// 便道中有车辆 
			pShortcutPath->Delete(1, ve);		// 取出便道中的第1辆车 
			pStopPath->Push(ve);				// 将此车放到停车道中
		}
	}
	else if (LocateInpShortcutPath(vehicle) != 0)
	{	// 车辆在便道中 
		int pos = LocateInpShortcutPath(vehicle);// 车辆在便道中的位置
		cout << "在便道中存在编号为" << vehicle.num << "的车辆" << endl;
		cout << "此车将离开, 不收停车费." << endl;
		pShortcutPath->Delete(pos, ve);			// 在便道中开走车辆 
	}
	else
	{	// 在停车道与便道中无车辆vehicle
		cout << "在停车道与便道中不存在编号为" << vehicle.num << "的车辆" << endl;
	}
}

#endif