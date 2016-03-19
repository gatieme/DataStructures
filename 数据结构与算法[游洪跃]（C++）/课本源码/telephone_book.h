// 文件路径名: telephone_book\telephone_book.h
#ifndef __TELEPHONE_BOOK_H__
#define __TELEPHONE_BOOK_H__

// 电话结构
struct TelephoneType
{	
	char teleNo[18];					// 电话号码
	char name[16];						// 用户名
	char addr[18];						// 地址
	bool isEmpty;						// 是否为空
};

// 电话号码簿类(m表示桶容量, b表示基桶数)
template <int m, int b>
class TelephoneBook
{
private:
// 数据成员
	fstream hashFile;					// 电话号码簿文件

	// 桶结构
	struct BucketType
	{
		TelephoneType records[m];		// 存储电话记录
		long next;						// 表示后继的地址
	};

// 辅助函数
	long Hash(const char teleNo[18]);	// 散列函数
	int LocateHelp(const BucketType &bucket, char teleNo[18]);					// 定位辅助函数
	void Locate(BucketType &bucket, long &offset, int &pos, char teleNo[18]);	// 定位函数
	int LocateEmptyRecordHelp(const BucketType &bucket);						// 定位空记录辅助函数
	void LocateEmptyRecord(BucketType &bucket, long &offset, int &pos, char teleNo[18]);
		// 定位空记录
	void Input();						// 输入记录
	void Delete();						// 删除记录
	void Serach();						// 查询记录

public:
// 构造函数, 析构函数与方法
	TelephoneBook();					// 无参数的构造函数
	virtual ~TelephoneBook();			// 析构函数
	void Run();							// 处理电话号码簿
};

// 电话号码簿类的实现
template <int m, int b>
long TelephoneBook<m, b>::Hash(const char teleNo[18])
// 操作结果: 返回散列函数值
{
	long h = 0;							// 散列函数值
	for (int pos = 0; pos < (int)strlen(teleNo); pos++)
	{	// 依次处理各数字字符
		h = (h * 10 + teleNo[pos] - '0') % b;
	}
	return h;							// 返回散列函数值
}

template <int m, int b>
int TelephoneBook<m, b>::LocateHelp(const BucketType &bucket, char teleNo[18])
// 操作结果: 返回电话号码teleNo在桶bucket中的位置
{
	
	for (int pos = 0; pos < m; pos++)
	{	// 依次比较桶中各电话记录
		if (!bucket.records[pos].isEmpty &&
			strcmp(bucket.records[pos].teleNo, teleNo) == 0) return pos; // 定位成功
	}
	return -1;							// 定位失败
}

template <int m, int b>
void TelephoneBook<m, b>::Locate(BucketType &bucket, long &offset, 
	int &pos, char teleNo[18])
// 操作结果: 定位电话号码teleNo所在的桶bucket, 在桶中的位置pos, 桶在文件
//	中的位置位置offset
{
	long h = Hash(teleNo);								// 散列函数值
	offset = sizeof(BucketType) * h;					// 桶在文件中的位置
	hashFile.clear();									// 清除标志	
	hashFile.seekg(offset, ios::beg);					// 文件定位
	hashFile.read((char *)&bucket, sizeof(BucketType));	// 读取基桶
	pos = LocateHelp(bucket, teleNo);					// 定位电话记录在桶中的位置
	if (pos == -1) offset = bucket.next;				// 溢出桶的位置
	while (pos == -1 && offset != -1)
	{	// 继续在溢出桶中查找
		hashFile.clear();								// 清除标志	
		hashFile.seekg(offset, ios::beg);				// 文件定位
		hashFile.read((char *)&bucket, sizeof(BucketType));	// 读到基桶
		pos = LocateHelp(bucket, teleNo);				// 定位电话记录在桶中的位置
		if (pos == -1) offset = bucket.next;			// 后继溢出桶的位置
	}
}

template <int m, int b>
int TelephoneBook<m, b>::LocateEmptyRecordHelp(const BucketType &bucket)
// 操作结果: 返回空记录位位置
{
	for (int pos = 0; pos < m; pos++)
	{	// 依次比较桶中各电话记录
		if (bucket.records[pos].isEmpty) return pos;	// 定位成功
	}
	return -1;											// 定位失败
}

template <int m, int b>
void TelephoneBook<m, b>::LocateEmptyRecord(BucketType &bucket, long &offset, 
	int &pos, char teleNo[18])
// 操作结果: 定位电话号码teleNo所在的具有空记录的桶bucket, 桶中的空记录位置pos, 桶
//	在文件中的位置位置offset
{
	long h = Hash(teleNo);								// 散列函数值
	offset = sizeof(BucketType) * h;					// 桶在文件中的位置
	hashFile.clear();									// 清除标志	
	hashFile.seekg(offset, ios::beg);					// 文件定位
	hashFile.read((char *)&bucket, sizeof(BucketType));	// 读到基桶
	pos = LocateEmptyRecordHelp(bucket);				// 定位桶中空记录的位置
	if (pos == -1) offset = bucket.next;				// 溢出桶的位置
	while (pos == -1 && offset != -1)
	{	// 继续在溢出桶中查找
		hashFile.clear();								// 清除标志	
		hashFile.seekg(offset, ios::beg);				// 文件定位
		hashFile.read((char *)&bucket, sizeof(BucketType));	// 读到基桶
		pos = LocateEmptyRecordHelp(bucket);			// 定位桶中空记录的位置
		if (pos == -1) offset = bucket.next;			// 后继溢出桶的位置
	}
}

template <int m, int b>
void TelephoneBook<m, b>::Input()
// 操作结果: 输入记录
{
	TelephoneType telph;								// 电话号码记录
	telph.isEmpty = false;								// 标记

	cout << "输入电话号码:";
	cin >> telph.teleNo;
	cout << "输入用户名:";
	cin >> telph.name;
	cout << "输入地址:";
	cin >> telph.addr;
	BucketType bucket;									// 桶
	long offset;										// 桶在文件中的相应位置
	int pos;											// 电话记录在桶中的位置
	Locate(bucket, offset, pos, telph.teleNo);			// 定位电话记录的位置
	if (pos != -1) 
	{	// 定位成功
		cout << "电话已在散列文件中!" << endl;
	}
	else
	{	// 定位失败
		LocateEmptyRecord(bucket, offset, pos, telph.teleNo);// 定位空记录位置
		if (pos != -1)
		{	// 找到空记录
			bucket.records[pos] = telph;				// 将电话记录赋值给bucket.records[pos]
			hashFile.clear();							// 清除标志	
			hashFile.seekg(offset, ios::beg);			// 定位文件
			hashFile.write((char *)&bucket, sizeof(BucketType));// 写桶
		}
		else
		{
			hashFile.clear();							// 清除标志	
			hashFile.seekg(0, ios::end);				// 定位到文件尾
			bucket.next = hashFile.tellg();				// 后继溢出桶位置
			hashFile.clear();							// 清除标志	
			hashFile.seekg(offset, ios::beg);			// 定位文件
			hashFile.write((char *)&bucket, sizeof(BucketType));// 写桶
			offset = bucket.next;						// 新溢出桶在文件中的位置
			for (pos = 1; pos < m; pos++)
			{	// 设置空记录
				bucket.records[pos].isEmpty = true;
			}
			pos = 0;									// 电话记录的位置
			bucket.records[pos] = telph;				// 将电话记录赋值给bucket.records[pos]
			hashFile.clear();							// 清除标志	
			hashFile.seekg(offset, ios::beg);			// 定位文件
			hashFile.write((char *)&bucket, sizeof(BucketType));// 写桶
		}
	}
}

template <int m, int b>
void TelephoneBook<m, b>::Delete()
// 操作结果: 删除记录
{
	char teleNo[18];					// 电话号码
	cout << "输入电话号码:";
	cin >> teleNo;
	BucketType bucket;					// 桶
	long offset;						// 桶在文件中的相应位置
	int pos;							// 电话记录在桶中的位置
	Locate(bucket, offset, pos, teleNo);// 定位电话记录的位置
	if (pos == -1)
	{	// 定位失败
		cout << "删除记录失败!" << endl;
	}
	else
	{
		hashFile.clear();									// 清除标志	
		hashFile.seekg(offset, ios::beg);					// 定位文件
		hashFile.read((char *)&bucket, sizeof(BucketType));	// 读桶
		bucket.records[pos].isEmpty = true;					// 空记录
		hashFile.clear();									// 清除标志	
		hashFile.seekg(offset, ios::beg);					// 定位文件
		hashFile.write((char *)&bucket, sizeof(BucketType));// 写桶
		cout << "电话号码:" << bucket.records[pos].teleNo << endl;
		cout << "用户名:" << bucket.records[pos].name << endl;
		cout << "地址:" << bucket.records[pos].addr << endl;
		cout << "删除成功!" << endl;
	}
}

template <int m, int b>
void TelephoneBook<m, b>::Serach()
// 操作结果: 查找记录
{
	char teleNo[18];					// 电话号码
	cout << "输入电话号码:";
	cin >> teleNo;
	BucketType bucket;					// 桶
	long offset;						// 桶在文件中的相应位置
	int pos;							// 电话记录在桶中的位置
	Locate(bucket, offset, pos, teleNo);// 定位电话记录的= -1)
	if (pos == -1)
	{	// 定位失败
		cout << "查找失败!" << endl;
	}
	else
	{
		hashFile.clear();									// 清除标志	
		hashFile.seekg(offset, ios::beg);					// 定位文件
		hashFile.read((char *)&bucket, sizeof(BucketType));	// 读桶
		cout << "电话号码:" << bucket.records[pos].teleNo << endl;
		cout << "用户名:" << bucket.records[pos].name << endl;
		cout << "地址:" << bucket.records[pos].addr << endl;
	}
}

template <int m, int b>
TelephoneBook<m, b>::TelephoneBook()
// 操作结果: 初始化电话号码簿
{
	ifstream iFile("telph.dat");					// 建立输入文件
	if (iFile.fail())
	{	// 打开文件失败,表示不存在文件
		ofstream oFile("telph.dat");				// 建立输出文件
		if (oFile.fail()) throw("打开文件失败!");	// 抛出异常 
		oFile.close();								// 关闭文件
	}
	else
	{	// 存在文件
		iFile.close();								// 关闭文件
	}

	hashFile.open("telph.dat", ios::in|ios::out|ios::binary);	// 以读写方式打开文件
	if (hashFile.fail()) throw("打开文件失败!");	// 抛出异常 

	hashFile.seekg(0, ios::end);					// 定位到文件尾
	int bucketNum = hashFile.tellg() / sizeof(BucketType);	// 桶数
	
	if (bucketNum < b)
	{	// 桶数不于基桶数,说明文件不完整或已被破坏, 应初始化基桶
		BucketType bucket;
		int pos;									// 临时变量
		for (pos = 0; pos < m; pos++)
		{	// 初始化基桶
			bucket.records[pos].isEmpty = true;		// 空记录
			bucket.next = -1;						// 无溢出
		}
		hashFile.clear();							// 清除标志	
		hashFile.seekg(0, ios::beg);				// 定位到文件头
		for (pos = 0; pos < b; pos++)
		{	// 写基桶到文件中
			hashFile.write((char *)&bucket, sizeof(BucketType));// 写入基桶
		}
	}
}

template <int m, int b>
TelephoneBook<m, b>::~TelephoneBook()
// 操作结果: 关闭文件
{
	hashFile.close();											// 关闭文件
}

template <int m, int b>
void TelephoneBook<m, b>::Run()
// 操作结果: 处理电话号码簿
{
	int select;									// 临时变量
	do
	{
		cout << "1.输入记录 2.删除记录 3.查找记录 4.退出" << endl;
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
			Serach();							// 查找记录
			break;
		}
	} while (select != 4);
}

#endif


