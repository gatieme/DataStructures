// 文件路径名: student_infor_manage\student_infor_manage.h
#ifndef __STUDENT_INFOR_MANAGE_H__
#define __STUDENT_INFOR_MANAGE_H__

#include "bin_serach.h"		// 二分查找算法

// 学生信息记录结构
struct StuInforType
{
	char num[7];			// 学号
	char name[9];			// 姓名
	char sex[3];			// 性别
	int age;				// 年龄
	char dep[19];			// 系
	bool isDeleted;			// 是否被删除
};

// 索引项结构
struct IndexItemType
{
	char num[7];			// 学号
	long offset;			// 学生基本情况记录在数据主文件中的相应位置
};

// 重载排序与查找需要的关系运算符
bool operator <=(const char num[7], const IndexItemType &item);
	// 重载关系运算符<=
bool operator <(const char num[7], const IndexItemType &item);
	// 重载关系运算符<
bool operator ==(const char num[7], const IndexItemType &item);
	// 重载关系运算符==
bool operator <(const IndexItemType &first, const IndexItemType &second);
	// 重载关系运算符<

static const long INCREMENT_OF_INDEX_TABLE = 100;// 索引表增量

// 学生信息管理类
class StudentInforManage
{
private:
// 学生信息管理类的数据成员:
	FILE *pFStuData;							// 学生数据文件
	IndexItemType *pIndexTable;					// 索引表
	long size;									// 索引表当前索引项数
	long maxSize;								// 索引表最大索引项数

//	辅助函数:
	void Display(const StuInforType &stuInfor);	// 显示记录
	void DisplayALL();							// 显示所有记录
	void Serach();								// 查找记录
	void Input();								// 输入记录
	void Delete();								// 删除记录
	void Update();								// 更新记录

public:
// 公有函数:
	StudentInforManage();						// 无参数的构造函数
	virtual ~StudentInforManage();				// 析构函数
	void Run();									// 学生信息管理
};

// 学生信息管理类及相关函数的实现部分
bool operator <=(const char num[7], const IndexItemType &item)
// 操作结果: 重载关系运算符<=
{
	return strcmp(num, item.num) <= 0;
}

bool operator <(const char num[7], const IndexItemType &item)
// 操作结果: 重载关系运算符<
{
	return strcmp(num, item.num) < 0;
}

bool operator ==(const char num[7], const IndexItemType &item)
// 操作结果: 重载关系运算符==
{
	return strcmp(num, item.num) == 0;
}

bool operator <(const IndexItemType &first, const IndexItemType &second)
// 操作结果: 重载关系运算符<
{
	return strcmp(first.num, second.num) < 0;
}

StudentInforManage::StudentInforManage()
// 操作结果: 构造索引表及初始化相关信息
{
	if ((pFStuData = fopen("student.dat", "rb+")) == NULL)
	{	// 不存在文件student.dat
		if ((pFStuData = fopen("student.dat", "wb+")) == NULL)
			throw Error("打开数据文件失败!");		// 抛出异常
	}
	
	FILE *pFStuIndex;								// 索引文件
	if ((pFStuIndex = fopen("student.idx", "rb+")) == NULL)
	{	// 不存在文件student.idx
		size = 0;									// 无索引项
		maxSize = INCREMENT_OF_INDEX_TABLE;			// 索引表最大索引项数
		pIndexTable = new IndexItemType[maxSize];		// 分配存储空间
	}
	else
	{
		fseek(pFStuIndex, 0, SEEK_END);				// 使文件指针指向文件尾
		size = ftell(pFStuIndex) / sizeof(IndexItemType);// 索引项数
		maxSize = size + INCREMENT_OF_INDEX_TABLE;	// 索引表最大索引项数
		pIndexTable = new IndexItemType[maxSize];		// 分配存储空间
		fseek(pFStuIndex, 0, SEEK_SET);				// 使文件指针指向文件头
		for (int pos = 0; pos < size; pos++)
		{	// 读出索引项
			fread(&pIndexTable[pos], sizeof(IndexItemType), 1, pFStuIndex);	// 读索引项
		}
		fclose(pFStuIndex);							// 关闭文件
	}
}

StudentInforManage::~StudentInforManage()
// 操作结果: 关闭文件与释放存储空间
{
	fclose(pFStuData);							// 关闭文件
	FILE *pFStuIndex;							// 索引文件
	if ((pFStuIndex = fopen("student.idx", "wb")) == NULL)
		throw Error("打开索引文件失败!");		// 抛出异常
	for (int pos = 0; pos < size; pos++)
	{	// 写索引项
		fwrite(&pIndexTable[pos], sizeof(IndexItemType), 1, pFStuIndex);
	}
	fclose(pFStuIndex);							// 关闭文件
	delete []pIndexTable;						// 释放存储空间
}

void StudentInforManage::Display(const StuInforType &stuInfor)
// 操作结果: 显示记录
{
	cout << "学号:" << stuInfor.num << endl;
	cout << "姓名:" << stuInfor.name << endl;
	cout << "性别:" << stuInfor.sex << endl;
	cout << "年龄:" << stuInfor.age << endl;
	cout << "系:" << stuInfor.dep << endl;
}

void StudentInforManage::DisplayALL()
// 操作结果: 显示所有记录
{
	cout << setw(8) << "学号" << setw(10) << "姓名" << setw(6) << "性别" 
		<< setw(6) << "年龄" << setw(16) << "系" << endl;
	for (int pos = 0; pos < size; pos++)
	{	// 显示所有记录
		StuInforType stuInfor;					// 学生信息
		fseek(pFStuData, pIndexTable[pos].offset, SEEK_SET);	// 定位主文件记录
		fread(&stuInfor, sizeof(StuInforType), 1, pFStuData);	// 读记录
		cout << setw(8) << stuInfor.num << setw(10) << stuInfor.name << setw(6) << stuInfor.sex 
			<< setw(6) << stuInfor.age << setw(16) << stuInfor.dep << endl;
	}
}

void StudentInforManage::Serach()
// 操作结果: 查找记录
{
	char num[7];
	cout << "输入学号:";
	cin >> num;
	while (GetChar() != '\n');					// 跳过当前行的其它字符
	int pos = BinSerach(pIndexTable, size, num);// 二分查找
	if (pos == -1)
	{	// 查找失败
		cout << "查无此学号!" << endl;
	}
	else
	{	// 查找成功
		StuInforType stuInfor;					// 学生信息
		fseek(pFStuData, pIndexTable[pos].offset, SEEK_SET);	// 定位主文件记录
		fread(&stuInfor, sizeof(StuInforType), 1, pFStuData);	// 读记录
		Display(stuInfor);						// 显示记录
	}
}

void StudentInforManage::Input()
// 操作结果: 输入记录
{
	StuInforType stuInfor;						// 学生信息
	stuInfor.isDeleted = false;					// 删除标记
	cout << "学号:"; cin >> stuInfor.num;
	cout << "姓名:"; cin >> stuInfor.name;
	cout << "性别:"; cin >> stuInfor.sex;
	cout << "年龄:"; cin >> stuInfor.age;
	cout << "系:"; cin >>stuInfor.dep;
	while (GetChar() != '\n');					// 跳过当前行的其它字符
	if (BinSerach(pIndexTable, size, stuInfor.num) >= 0)
	{	// 查找成功
		cout << "学号重复, 插入失败!" << endl;
		return;
	}

	fseek(pFStuData, 0, SEEK_END);				// 定位主文件当前位置为文件尾
	long offset = ftell(pFStuData);				// 学生基本情况记录在数据主文件中的相应位置
	fwrite(&stuInfor, sizeof(StuInforType), 1, pFStuData);		// 写记录

	if (size >= maxSize)
	{	// 索引项已达到最大容量
		maxSize += INCREMENT_OF_INDEX_TABLE;	// 扩大最大容量
		IndexItemType *pTmp;					// 临时索引表
		pTmp = new IndexItemType[maxSize];		// 重新分配存储空间
		for (int pos = 0; pos < size; pos++)
			pTmp[pos] = pIndexTable[pos];		// 复制索引项
		delete []pIndexTable;					// 释放pIndexTable
		pIndexTable = pTmp;						// pIndexTable指向新存储空间
	}

	int j;
	for (j = size - 1; j >= 0 && stuInfor.num < pIndexTable[j]; j--)
	{	// 将比stuInfor.num大的索引项后移
		pIndexTable[j + 1] = pIndexTable[j];
	}
	strcpy(pIndexTable[j + 1].num, stuInfor.num);	// 学号
	pIndexTable[j + 1].offset = offset;			// 学生基本情况记录在数据主文件中的相应位置
	size++;										// 索引项个数自加1
}

void StudentInforManage::Delete()
// 操作结果: 删除记录
{
	char num[7];
	cout << "输入学号:";
	cin >> num;
	while (GetChar() != '\n');					// 跳过当前行的其它字符
	int pos = BinSerach(pIndexTable, size, num);// 二分查找
	if (pos == -1)
	{	// 查找失败
		cout << "查无此学号!" << endl;
	}
	else
	{	// 查找成功
		StuInforType stuInfor;					// 学生信息
		fseek(pFStuData, pIndexTable[pos].offset, SEEK_SET);	// 定位主文件记录
		fread(&stuInfor, sizeof(StuInforType), 1, pFStuData);	// 读记录
		stuInfor.isDeleted = true;				// 删除标记
		fseek(pFStuData, pIndexTable[pos].offset, SEEK_SET);	// 定位主文件记录
		fwrite(&stuInfor, sizeof(StuInforType), 1, pFStuData);	// 写记录
		
		for (int i = pos + 1; i < size; i++)
		{	// 在索引表中删除索引项
			pIndexTable[i - 1] = pIndexTable[i];
		}
		size--;									// 索引项个数自减1
		Display(stuInfor);						// 显示记录
		cout << "删除成功!" << endl;
	}
}

void StudentInforManage::Update()
// 操作结果: 更新记录
{
	char num[7];
	cout << "输入学号:";
	cin >> num;
	while (GetChar() != '\n');					// 跳过当前行的其它字符
	int pos = BinSerach(pIndexTable, size, num);// 二分查找
	if (pos == -1)
	{	// 查找失败
		cout << "查无此学号!" << endl;
	}
	else
	{	// 查找成功
		StuInforType stuInfor;					// 学生信息
		fseek(pFStuData, pIndexTable[pos].offset, SEEK_SET);	// 定位主文件记录
		fread(&stuInfor, sizeof(StuInforType), 1, pFStuData);	// 读记录
		Display(stuInfor);						// 显示记录

		cout << "学号:"; cin >>stuInfor.num;
		cout << "姓名:"; cin >> stuInfor.name;
		cout << "性别:"; cin >> stuInfor.sex;
		cout << "年龄:"; cin >> stuInfor.age;
		cout << "系:"; cin >>stuInfor.dep;
		while (GetChar() != '\n');				// 跳过当前行的其它字符
		fseek(pFStuData, pIndexTable[pos].offset, SEEK_SET);	// 定位主文件记录
		long offset = pIndexTable[pos].offset;	// 暂存offset
		if (strcmp(stuInfor.num, pIndexTable[pos].num) == 0)
		{	// 关键字没变, 索引表不变
			fwrite(&stuInfor, sizeof(StuInforType), 1, pFStuData);	// 写记录
		}
		else
		{	// 修改索引表
			if (BinSerach(pIndexTable, size, stuInfor.num) >= 0)
			{	// 更新后,学号重复
				cout << "学号重复, 更新失败!" << endl;
			}
			else
			{
				for (int i = pos + 1; i < size; i++)
				{	// 在索引表中删除索引项
					pIndexTable[i - 1] = pIndexTable[i];
				}
				strcpy(pIndexTable[size - 1].num, stuInfor.num);	// 学号
				pIndexTable[size - 1].offset = offset;	
					// 学生基本情况记录在数据主文件中的相应位置
				for (int j = size - 1; j > 0 && pIndexTable[j] < pIndexTable[j - 1]; j--)
				{	// 将pIndexTable[size-1]大的计录都交换到pIndexTable[size-1]的后面
					Swap(pIndexTable[j], pIndexTable[j - 1]);
				}
			}
		}
	}
}

void StudentInforManage::Run()
// 操作结果: 学生信息管理
{
	int select;									// 临时变量
	do
	{
		cout << "1.输入记录 2.删除记录 3.更新记录 4.查找记录 5.显示所有记录 6.退出" 
			<< endl;
		cout << "输入选择:";
		cin >> select;							// 输入选择
		while (GetChar() != '\n');				// 跳过当前行的其它字符
		switch (select)
		{
		case 1:
			Input();							// 输入记录
			break;
		case 2:
			Delete();							// 删除记录
			break;
		case 3:
			Update();							// 更新记录
			break;
		case 4:
			Serach();							// 查找记录
			break;
		case 5:
			DisplayALL();						// 显示所有记录
			break;
		}
	} while (select != 6);
}

#endif
