#ifndef __TRI_DIAGONAL_H__
#define __TRI_DIAGONAL_H__

// 三对角矩阵类
template<class ElemType>
class TriDiagonalMatrix
{
protected:
//  三对角矩阵的数据成员:
	ElemType *elems;			// 存储矩阵元素
	int n;						// 三对角矩阵阶数

public:
// 抽象数据类型方法声明及重载编译系统默认方法声明:
	TriDiagonalMatrix(int sz);	// 构造一个sz行sz列的三对角矩阵
	~TriDiagonalMatrix();		// 析构函数
    int GetSize() const;		// 返回三对角矩阵阶数
	ElemType &operator()(int i, int j);	// 重载函数运算符
	TriDiagonalMatrix(const TriDiagonalMatrix<ElemType> &copy);		// 复制构造函数
	TriDiagonalMatrix<ElemType> &operator =(const TriDiagonalMatrix<ElemType> &copy); 
		// 赋值语句重载
};

// 三对角矩阵类的实现部分
template <class ElemType>
TriDiagonalMatrix<ElemType>::TriDiagonalMatrix(int sz)
// 操作结果：构造一个sz行sz列的三对角矩阵
{
	if (sz < 1)							
		throw Error("行数或列数无效!");	// 抛出异常
	n = sz;								// sz为矩阵阶数
	elems = new ElemType[3 * n - 1];	// 分配存储空间
}

template <class ElemType>
TriDiagonalMatrix<ElemType>::~TriDiagonalMatrix()
// 操作结果：释放三对角矩阵所占用空间
{
	if (elems != NULL) delete []elems; 
}

template <class ElemType>
int TriDiagonalMatrix<ElemType>::GetSize() const
// 操作结果：返回三对角矩阵阶数
{
	return n;
}

template <class ElemType>
ElemType &TriDiagonalMatrix<ElemType>::operator()(int i, int j)
// 操作结果：重载函数运算符
{
	if (i < 1 || i > n || j < 1 || j > n)
		throw Error("下标出界!");					// 抛出异常
	if (i - j == 1)	return elems[2 * n + i - 2];	// 元素在低对象线上
	else if (i - j == 0) return elems[n + i - 1];	// 元素在主对象线上
	else if (i - j == -1) return elems[i];			// 元素在高对象线上
	else return elems[0];							// 元素在其它位置
}

template <class ElemType>
TriDiagonalMatrix<ElemType>::TriDiagonalMatrix(const TriDiagonalMatrix<ElemType> &copy)
// 操作结果：由三对角矩阵copy构造新三对角矩阵——复制构造函数
{
	n = copy.n;							// 复制三对角矩阵阶数
	elems = new ElemType[3 * n - 1];	// 为数据元素分配存储空间
	for (int i = 0; i < 3 * n - 1; i++)
	{	// 复制数据元素值
		elems[i] = copy.elems[i];
	}
}

template <class ElemType>
TriDiagonalMatrix<ElemType> &TriDiagonalMatrix<ElemType>::operator =(const TriDiagonalMatrix<ElemType> &copy)
// 操作结果：将三对角矩阵copy赋值给当前三对角矩阵——赋值语句重载
{
	if (&copy != this)
	{
		if (elems != NULL) delete []elems;	// 释放数据元素空间

		n = copy.n;							// 复制三对角矩阵阶数
		elems = new ElemType[3 * n - 1];	// 为数据元素分配存储空间
		for (int i = 0; i < 3 * n - 1; i++)
		{	// 复制数据元素值
			elems[i] = copy.elems[i];
		}
	}
	return *this;
}

#endif