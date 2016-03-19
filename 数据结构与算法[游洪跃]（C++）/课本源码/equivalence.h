#ifndef __EQUIVALENCE_H__				// 如果没有定义__EQUIVALENCE_H__
#define __EQUIVALENCE_H__				// 那么定义__EQUIVALENCE_H__

// 等价类
class Equivalence
{
protected:
// 等价类的数据成员:
	int *parent;								// 存储结点的双亲
	int size;									// 结点个数

// 辅助函数
int Find(int cur) const;						// 查找结点cur所在树的根

public:
// 抽象数据类型方法声明及重载编译系统默认方法声明:
	Equivalence(int sz);						// 构造sz个单结点树(等价类)
	virtual ~Equivalence();						// 析构函数
	void Union(int a, int b);					// 合并a与b所在的等价类
	bool Differ(int a, int b);					// 如果a与b不在同一棵树上，返回true，否则返回false
	Equivalence(const Equivalence &copy);				// 复制构造函数
	Equivalence &operator =(const Equivalence &copy);	// 赋值语句重载
};


// 等价类的实现部分
Equivalence::Equivalence(int sz)
// 操作结果：构造sz个单结点树(等价类)
{
	size = sz;									// 容量
	parent = new int[size];						// 分配空间
	for (int i = 0; i < size; i++) 
		parent[i] = -1;							// 每个结点构成单结点树(等价类)
}

int Equivalence::Find(int cur) const
// 操作结果：查找结点cur所在树的根
{
	if (cur < 0 || cur >= size)
		throw Error("范围错!");					// 抛出异常
	int root = cur;								// 根
	while (parent[root] > 0) root = parent[root];// 查找根
	for (int p, i = cur; i != root; i = p)
	{	// 将从cur到根路径上的所有结点都变成根的孩子结点
		p = parent[i];							// 用p暂存i的双亲
		parent[i] = root;						// 将i变为root的孩子
	}
	return root;								// 返回根
}

Equivalence::~Equivalence()
// 操作结果：释放对象点用的空间——析构函数
{
	delete []parent;							// 释放数组parent
}

void Equivalence::Union(int a, int b)
// 操作结果：合并a与b所在的等价类
{
	if (a < 0 || a >= size || b < 0 || b >= size)
		throw Error("范围错!");					// 抛出异常
	int root1 = Find(a);						// 查找a所在树(等价类)的根		
	int root2 = Find(b);						// 查找b所在树(等价类)的根		
	if (parent[root1] < parent[root2])
	{	// root1所含结点数较多,将root2合并到root1
		parent[root1] = parent[root1] + parent[root2];
			// root1的结点个数为原root1与root2结点个数之和
		parent[root2] = root1;					// 将root2合并到root1
	}
	else
	{	// root2所含结点数较多,将root1合并到root2
		parent[root2] = parent[root1] + parent[root2];
			// root2的结点个数为原root1与root2结点个数之和
		parent[root1] = root2;					// 将root1合并到root2
	}
}

bool Equivalence::Differ(int a, int b)
// 操作结果：如果a与b不在同一棵树上，返回true，否则返回false
{
	if (a < 0 || a >= size || b < 0 || b >= size)
		throw Error("范围错!");					// 抛出异常
	int root1 = Find(a);						// 查找a所在树(等价类)的根		
	int root2 = Find(b);						// 查找b所在树(等价类)的根		
	return root1 != root2;						// 比较树(等价类)的根
}

Equivalence::Equivalence(const Equivalence &copy)
// 操作结果：由copy构造新对象——复制构造函数
{
	size = copy.size;							// 容量
	parent = new int[size];						// 分配空间
	for (int i = 0; i < size; i++) 
		parent[i] = copy.parent[i];				// 复制parent的每个元素

}

Equivalence &Equivalence::operator =(const Equivalence &copy)
// 操作结果：将copy赋值给当前对象——赋值语句重载
{
	if (&copy != this)
	{
		size = copy.size;						// 容量
		delete []parent;						// 释放空间
		parent = new int[size];					// 分配空间
		for (int i = 0; i < size; i++) 
			parent[i] = copy.parent[i];			// 复制parent的每个元素
	}
	return *this;
}

#endif
