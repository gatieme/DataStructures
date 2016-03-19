#ifndef __LOWER_TRIANGULAR_MATRIX_H__
#define __LOWER_TRIANGULAR_MATRIX_H__

// 下三角矩阵类
template<class ElemType>
class LowerTriangularMatrix
{
protected:
//  下三角矩阵的数据成员:
	ElemType *elems;				// 存储矩阵元素
	int n;							// 下三角矩阵阶数

public:
// 抽象数据类型方法声明及重载编译系统默认方法声明:
	LowerTriangularMatrix(int sz);	// 构造一个sz行sz列的下三角矩阵
	~LowerTriangularMatrix();		// 析构函数
	int GetSize() const;			//返回下三角矩阵阶数
	ElemType &operator()(int i, int j);	// 重载函数运算符
	LowerTriangularMatrix(const LowerTriangularMatrix<ElemType> &copy);		// 复制构造函数
	LowerTriangularMatrix<ElemType> &operator =(const LowerTriangularMatrix<ElemType> &copy); 
		// 赋值语句重载
};

// 下三角矩阵类的实现部分
template <class ElemType>
LowerTriangularMatrix<ElemType>::LowerTriangularMatrix(int sz)
// 操作结果：构造一个sz行sz列的下三角矩阵
{
	if (sz < 1)							
		throw Error("行数或列数无效!");	// 抛出异常
	n = sz;								// sz为矩阵阶数
	elems = new ElemType[n * (n + 1) / 2 + 1];	// 分配存储空间
}

template <class ElemType>
LowerTriangularMatrix<ElemType>::~LowerTriangularMatrix()
// 操作结果：释放下三角矩阵所占用空间
{
	if (elems != NULL) delete []elems; 
}

template <class ElemType>
int LowerTriangularMatrix<ElemType>::GetSize() const
// 操作结果：返回下三角矩阵阶数
{
	return n;
}

template <class ElemType>
ElemType &LowerTriangularMatrix<ElemType>::operator()(int i, int j)
// 操作结果：重载函数运算符
{
	if (i < 1 || i > n || j < 1 || j > n)	
		throw Error("下标出界!");					// 抛出异常
	if (i >= j)	return elems[i * (i - 1) / 2 + j];	// 元素在下三角中
	else return elems[0];							// 元素在其它位置
}

template <class ElemType>
LowerTriangularMatrix<ElemType>::LowerTriangularMatrix(const LowerTriangularMatrix<ElemType> &copy)
// 操作结果：由下三角矩阵copy构造新下三对角矩阵——复制构造函数
{
	n = copy.n;							// 复制下三对角矩阵阶数
	elems = new ElemType[n * (n + 1) / 2 + 1];	// 为数据元素分配存储空间
	for (int i = 0; i < n * (n + 1) / 2 + 1; i++)
	{	// 复制数据元素值
		elems[i] = copy.elems[i];
	}
}

template <class ElemType>
LowerTriangularMatrix<ElemType> &LowerTriangularMatrix<ElemType>::operator =(const LowerTriangularMatrix<ElemType> &copy)
// 操作结果：将下三角矩阵copy赋值给当前下三对角矩阵——赋值语句重载
{
	if (&copy != this)
	{
		if (elems != NULL) delete []elems;	// 释放数据元素空间

		n = copy.n;							// 复制下三角矩阵阶数
		elems = new ElemType[n * (n + 1) / 2 + 1];	// 为数据元素分配存储空间
		for (int i = 0; i < n * (n + 1) / 2 + 1; i++)
		{	// 复制数据元素值
			elems[i] = copy.elems[i];
		}
	}
	return *this;
}

#endif