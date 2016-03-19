#ifndef __SYMMETRY_MATRIX_H__
#define __SYMMETRY_MATRIX_H__

// 对称矩阵类
template<class ElemType>
class SymmtryMatrix
{
protected:
//  对称矩阵的数据成员:
	ElemType *elems;			// 存储矩阵元素
	int n;						// 对称矩阵阶数

public:
// 抽象数据类型方法声明及重载编译系统默认方法声明:
	SymmtryMatrix(int sz);		// 构造一个sz行sz列的对称矩阵
	~SymmtryMatrix();			// 析构函数
	int GetSize() const;		// 返回对称矩阵阶数
	ElemType &operator()(int i, int j);	// 重载函数运算符
	SymmtryMatrix(const SymmtryMatrix<ElemType> &copy);		// 复制构造函数
	SymmtryMatrix<ElemType> &operator =(const SymmtryMatrix<ElemType> &copy); 
		// 赋值语句重载
};

// 对称矩阵类的实现部分
template <class ElemType>
SymmtryMatrix<ElemType>::SymmtryMatrix(int sz)
// 操作结果：构造一个sz行sz列的对称矩阵
{
	if (sz < 1)							
		throw Error("行数或列数无效!");	// 抛出异常
	n = sz;								// sz为矩阵阶数
	elems = new ElemType[n * (n + 1) / 2];	// 分配存储空间
}

template <class ElemType>
SymmtryMatrix<ElemType>::~SymmtryMatrix()
// 操作结果：释放对称矩阵所占用空间
{
	if (elems != NULL) delete []elems; 
}

template <class ElemType>
int SymmtryMatrix<ElemType>::GetSize() const
// 操作结果：返回对称矩阵阶数
{
	return n;
}

template <class ElemType>
ElemType &SymmtryMatrix<ElemType>::operator()(int i, int j)
// 操作结果：重载函数运算符
{
	if (i < 1 || i > n || j < 1 || j > n)	
		throw Error("下标出界!");						// 抛出异常
	if (i >= j)	return elems[i * (i - 1) / 2 + j - 1];	// 元素在下三角中
	else return elems[j * (j - 1) / 2 + i - 1];			// 元素在上三角中
}

template <class ElemType>
SymmtryMatrix<ElemType>::SymmtryMatrix(const SymmtryMatrix<ElemType> &copy)
// 操作结果：由下对称矩阵copy构造对称矩阵矩阵——复制构造函数
{
	n = copy.n;							// 复制对称矩阵矩阵阶数
	elems = new ElemType[n * (n + 1) / 2];	// 为数据元素分配存储空间
	for (int i = 0; i < n * (n + 1) / 2; i++)
	{	// 复制数据元素值
		elems[i] = copy.elems[i];
	}
}

template <class ElemType>
SymmtryMatrix<ElemType> &SymmtryMatrix<ElemType>::operator =(const SymmtryMatrix<ElemType> &copy)
// 操作结果：将对称矩阵copy赋值给当前对称矩阵矩阵——赋值语句重载
{
	if (&copy != this)
	{
		if (elems != NULL) delete []elems;	// 释放数据元素空间

		n = copy.n;							// 复制对称矩阵矩阵阶数
		elems = new ElemType[n * (n + 1) / 2];	// 为数据元素分配存储空间
		for (int i = 0; i < n * (n + 1) / 2; i++)
		{	// 复制数据元素值
			elems[i] = copy.elems[i];
		}
	}
	return *this;
}

#endif