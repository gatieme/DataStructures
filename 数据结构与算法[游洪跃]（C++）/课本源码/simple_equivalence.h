#ifndef __SIMPLE_EQUIVALENCE_H__				// 如果没有定义__SIMPLE_EQUIVALENCE_H__
#define __SIMPLE_EQUIVALENCE_H__				// 那么定义__SIMPLE_EQUIVALENCE_H__

// 等价类
class SimpleEquivalence
{
protected:
// 等价类的数据成员:
	int *parent;								// 存储结点的双亲
	int size;									// 结点个数

// 辅助函数
int Find(int cur) const;						// 查找结点cur所在树的根

public:
// 抽象数据类型方法声明及重载编译系统默认方法声明:
	SimpleEquivalence(int sz);					// 构造sz个单结点树(等价类)
	virtual ~SimpleEquivalence();				// 析构函数
	void Union(int a, int b);					// 合并a与b所在的等价类
	bool Differ(int a, int b);					// 如果a与b不在同一棵树上，返回true，否则返回false
	SimpleEquivalence(const SimpleEquivalence &copy);				// 复制构造函数
	SimpleEquivalence &operator =(const SimpleEquivalence &copy);	// 赋值运算符
};

                                                                                                                                       
// 等价类的实现部分
SimpleEquivalence::SimpleEquivalence(int sz)
// 操作结果：构造sz个单结点树(等价类)
{
	size = sz;									// 容量
	parent = new int[size];						// 分配空间
	for (int i = 0; i < size; i++) 
		parent[i] = -1;							// 每个结点构成单结点树形成的等价类
}

int SimpleEquivalence::Find(int cur) const
// 操作结果：查找结点cur所在树的根
{
	if (cur < 0 || cur >= size)
		throw Error("范围错!");					// 抛出异常
	while (parent[cur] != -1) cur = parent[cur];// 查找根
	return cur;									// 返回根
}

SimpleEquivalence::~SimpleEquivalence()
// 操作结果：释放对象占用的空间——析构函数
{
	delete []parent;							// 释放数组parent
}

void SimpleEquivalence::Union(int a, int b)
// 操作结果：合并a与b所在的等价类
{
	if (a < 0 || a >= size || b < 0 || b >= size)
		throw Error("范围错!");					// 抛出异常
	int root1 = Find(a);						// 查找a所在树(等价类)的根		
	int root2 = Find(b);						// 查找b所在树(等价类)的根		
	if (root1 != root2) parent[root2] = root1;	// 合并树(等价类)
}

bool SimpleEquivalence::Differ(int a, int b)
// 操作结果：如果a与b不在同一棵树上，返回true，否则返回false
{
	if (a < 0 || a >= size || b < 0 || b >= size)
		throw Error("范围错!");					// 抛出异常
	int root1 = Find(a);						// 查找a所在树(等价类)的根		
	int root2 = Find(b);						// 查找b所在树(等价类)的根		
	return root1 != root2;						// 比较树(等价类)的根
}

SimpleEquivalence::SimpleEquivalence(const SimpleEquivalence &copy)
// 操作结果：由copy构造新对象——复制构造函数
{
	size = copy.size;							// 容量
	parent = new int[size];						// 分配空间
	for (int i = 0; i < size; i++) 
		parent[i] = copy.parent[i];				// 复制parent的每个元素

}

SimpleEquivalence &SimpleEquivalence::operator =(const SimpleEquivalence &copy)
// 操作结果：将copy赋值给当前对象——赋值运算符
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
