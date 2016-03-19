#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__

// 散列表类
template <class ElemType, class KeyType>
class HashTable
{
protected:
//  散列表的的数据成员:
	ElemType *ht;								// 散列表
	bool *empty;								// 空元素
	int m;										// 散列表容量
	int p;										// 除留余数法的除数

//	辅助函数:
	int H(KeyType key) const;					// 散列函数
	int Collision(KeyType key, int i) const;	// 处理冲突的函数
	bool SearchHelp(const KeyType &key, int &pos) const;	// 查寻关键字为key的元素的位置

public:
//  二叉树方法声明及重载编译系统默认方法声明:
    HashTable(int size, int divisor);			// 构造函数
    ~HashTable();								// 析造函数
    void Traverse(void (*Visit)(const ElemType &)) const;	// 遍历散列表
	bool Search(const KeyType &key, ElemType &e) const ;	// 查寻关键字为key的元素的值
	bool Insert(const ElemType &e);				// 插入元素e
	bool Delete(const KeyType &key);			// 删除关键字为key的元素
    HashTable(const HashTable<ElemType, KeyType> &copy);	// 复制构造函数
    HashTable<ElemType, KeyType> &operator=
		(const HashTable<ElemType, KeyType> &copy);			// 赋值语句重载
};

// 散列表类的实现部分
template <class ElemType, class KeyType>
int HashTable<ElemType, KeyType>::H(KeyType key) const
//操作结果: 返回散列地址
{
	return key % p;
}

template <class ElemType, class KeyType>
int HashTable<ElemType, KeyType>::Collision(KeyType key, int i) const
//操作结果: 返回第i次冲突的探查地址
{
	return (H(key) + i) % m;
}

template <class ElemType, class KeyType>
HashTable<ElemType, KeyType>::HashTable(int size, int divisor)
// 操作结果: 以size为散列表容量, divisor为除留余数法的除数构造一个空的散表表
{
	m = size;								// 赋值散列表容量
	p = divisor;							// 赋值除数
	ht = new ElemType[m];					// 分配存储空间
	empty = new bool[m];					// 分配存储空间

	for (int pos = 0; pos < m; pos++)
	{	// 将所有元素置空
		empty[pos] = true;
	}
}

template <class ElemType, class KeyType>
HashTable<ElemType, KeyType>::~HashTable()
// 操作结果: 销毁散列表
{
	delete []ht;							// 释放ht
	delete []empty;							// 释放empty
}

template <class ElemType, class KeyType>
void HashTable<ElemType, KeyType>::Traverse(void (*Visit)(const ElemType &)) const
// 操作结果: 依次对散列表的每个元素调用函数(*visit)
{
	for (int pos = 0; pos < m; pos++)
	{	// 对散列表的每个元素调用函数(*visit)
		if (!empty[pos])
		{	// 数据元素非空
			(*Visit)(ht[pos]);
		}
	}
}

template <class ElemType, class KeyType>
bool HashTable<ElemType, KeyType>::SearchHelp(const KeyType &key, int &pos) const
// 操作结果: 查寻关键字为key的元素的位置,如果查找成功,返回true,并用pos指示待查数据
//	元素在散列表的位置,否则返回false
{	
	int c = 0;							// 冲突次数
	pos = H(key);						// 散列表地址

	while (c < m &&						// 冲突次数应小于m
		!empty[pos] &&					// 元素ht[pos]非空
		ht[pos] != key)					// 关键字值不等
	{	
		pos = Collision(key, ++c);		//求得下一个探查地址
	}

	if (c >= m || empty[pos])
	{	// 查找失败
		return false;
	}
	else
	{	// 查找成功
		return true;
	}
}

template <class ElemType, class KeyType>
bool HashTable<ElemType, KeyType>::Search(const KeyType &key, ElemType &e) const
// 操作结果: 查寻关键字为key的元素的值,如果查找成功,返回true,并用e返回元素的值,
//	否则返回false
{
	int pos;							// 元素的位置
	if (SearchHelp(key, pos))
	{	// 查找成功
		e = ht[pos];					// 用e返回元素值
		return true;					// 返回true
	}
	else
	{	// 查找失败
		return false;					// 返回false
	}
}

template <class ElemType, class KeyType>
bool HashTable<ElemType, KeyType>::Insert(const ElemType &e)
// 操作结果: 在散列表中插入数据元素e,插入成功返回true,否则返回false
{
	int pos;							// 插入位置
	if (!SearchHelp(e, pos) && empty[pos])
	{	// 插入成功
		ht[pos] = e;					// 数据元素	
		empty[pos] = false;				// 表示非空
		return true;
	}
	else
	{	// 插入失败
		return false;
	}
}

template <class ElemType, class KeyType>
bool HashTable<ElemType, KeyType>::Delete(const KeyType &key)
// 操作结果: 删除关键字为key的数据元素,删除成功返回true,否则返回false
{
	int pos;							// 数据元素位置
	if (SearchHelp(key, pos))
	{	// 删除成功
		empty[pos] = true;				// 表示元素为空
		return true;
	}
	else
	{	// 删除失败
		return false;
	}
}

template <class ElemType, class KeyType>
HashTable<ElemType, KeyType>::HashTable(const HashTable<ElemType, KeyType> &copy)
// 操作结果：由散列表copy构造新散列表--复制构造函数
{
	m = copy.m;										// 散列表容量
	p = copy.p;										// 除留余数法的除数
	ht = new ElemType[m];							// 分配存储空间
	empty = new bool[m];							// 分配存储空间

	for (int curPosition = 0; curPosition < m; curPosition++)
	{	// 复制数据元素
		ht[curPosition] = copy.ht[curPosition];		// 复制元素
		empty[curPosition] = copy.empty[curPosition];// 复制元素是否为空值
	}
}

template <class ElemType, class KeyType>
HashTable<ElemType, KeyType> &HashTable<ElemType, KeyType>::
operator=(const HashTable<ElemType, KeyType> &copy)
// 操作结果：将散列表copy赋值给当前散列表--赋值语句重载
{
	if (&copy != this)
	{
		delete []ht;								// 释放当前散列表存储空间
		m = copy.m;									// 散列表容量
		p = copy.p;									// 除留余数法的除数
		ht = new ElemType[m];						// 分配存储空间
		empty = new bool[m];						// 分配存储空间

		for (int curPosition = 0; curPosition < m; curPosition++)
		{	// 复制数据元素
			ht[curPosition] = copy.ht[curPosition];	// 复制元素
			empty[curPosition] = copy.empty[curPosition];// 复制元素是否为空值
		}
	}
	return *this;
}

#endif