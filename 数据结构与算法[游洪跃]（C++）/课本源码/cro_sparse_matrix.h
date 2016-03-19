#ifndef __CRO_SPARSE_MATRIX_H__
#define __CRO_SPARSE_MATRIX_H__

#include "cro_node.h"				// 十字链表三元组结点类
#include "triple.h"					// 三元组类

// 稀疏矩阵十字链表类
template<class ElemType>
class CLkSparseMatrix
{
protected:
//  稀疏矩阵十字链的数据成员:
	CLkTriNode<ElemType> **rightHead, **downHead;// 行列链表表头数组
	int rows, cols, num;			// 稀疏矩阵的行数,列数及非零元个数

// 辅助函数
	void DestroyHelp();					// 清空稀疏矩阵
	StatusCode InsertHelp(const Triple<ElemType> &e);	// 插入十字链表三元组结点

public:
// 抽象数据类型方法声明及重载编译系统默认方法声明:
	CLkSparseMatrix(int rs = DEFAULT_SIZE, int cs = DEFAULT_SIZE);
		// 构造一个rs行cs列的空稀疏矩阵
	~CLkSparseMatrix();				// 析构函数
	int GetRows() const;			// 返回稀疏矩阵行数
    int GetCols() const;			// 返回稀疏矩阵列数
    int GetNum() const;				// 返回稀疏矩阵非零元个数
	StatusCode SetElem(int r, int c, const ElemType &v);	// 设置指定位置的元素值
	StatusCode GetElem(int r, int c, ElemType &v);			// 求指定位置的元素值
	CLkSparseMatrix(const CLkSparseMatrix<ElemType> &copy);	// 复制构造函数
	CLkSparseMatrix<ElemType> &operator =(const CLkSparseMatrix<ElemType> &copy); 
		// 赋值语句重载
};

// 稀疏矩阵十字链表类的实现部分
template <class ElemType>
CLkSparseMatrix<ElemType>::CLkSparseMatrix(int rs, int cs)
// 操作结果：构造一个rs行cs列的空稀疏矩阵
{
	if (rs < 1 || cs < 1)							
		throw Error("行数或列数无效!");	// 抛出异常
	rows = rs;							// 行数
	cols = cs;							// 列数
	num = 0;							// 非零元个数
	rightHead = new CLkTriNode<ElemType> *[rows + 1];	// 分配行链表表头数组存储空间
	downHead = new CLkTriNode<ElemType> *[cols + 1];	// 分配行链表表头数组存储空间
	for (int row = 1; row <= rows; row++) 
		rightHead[row] = NULL;			// 初始化行链表表头数组
	for (int col = 1; col <= cols; col++) 
		downHead[col] = NULL;			// 初始化行链表表头数组
}

template <class ElemType>
void CLkSparseMatrix<ElemType>::DestroyHelp()
// 操作结果：清空稀疏矩阵
{
	for (int row = 1; row <= rows; row++)
	{	// 释放第row行的结点所点用空间
		if (rightHead[row] != NULL)
		{
			CLkTriNode<ElemType> *tmpPtr =  rightHead[row];	// 指向第row行的首结点	
			rightHead[row] = tmpPtr->right;					// 第row行首结点变为tmpPtr后继
			delete tmpPtr;				// 释放原第row行首结点
		}
	}

	delete []rightHead;					// 释放行链表表头数组
	delete []downHead;					// 释放列链表表头数组
}

template <class ElemType>
CLkSparseMatrix<ElemType>::~CLkSparseMatrix()
// 操作结果：稀疏矩阵所占用空间
{
	DestroyHelp();
}

template <class ElemType>
int CLkSparseMatrix<ElemType>::GetRows() const
// 操作结果：返回稀疏矩阵行数
{
	return rows;						// 返回行数
}

template <class ElemType>
int CLkSparseMatrix<ElemType>::GetCols() const
// 操作结果：返回稀疏矩阵列数
{
	return cols;						// 返回列数
}

template <class ElemType>
int CLkSparseMatrix<ElemType>::GetNum() const
// 操作结果：返回稀疏矩阵非零元个数
{
	return num;							// 返回非零元个数
}

template <class ElemType>
StatusCode CLkSparseMatrix<ElemType>::SetElem(int r, int c, const ElemType &v)
// 操作结果：如果下标范围错,则返回RANGE_ERROR,否则返回SUCCESS
{
	if (r > rows || c > cols || r < 1 || c < 1)
		return RANGE_ERROR;				// 下标范围错
	
	CLkTriNode<ElemType> *pre, *p;
	Triple<ElemType> e(r, c, v);		// 三元组

	CLkTriNode<ElemType> *ePtr = new CLkTriNode<ElemType>(e);//生成结点

	if (rightHead[r] == NULL ||  rightHead[r]->triElem.col >= c)
	{	// ePtr插在第row行链表的表头处
		ePtr->right = rightHead[r];	 
		rightHead[r] = ePtr;
	}
	else
	{	// 寻找在第r行链表中的三元组位置
		pre = NULL; p=rightHead[r];	// 初始化p和pre
		while (p != NULL && p->triElem.col < c)
		{	// p与pre右移
			pre = p;	p = p->right;
		}

		if (p != NULL && p->triElem.row == r && p->triElem.col == c)
		{	// 找到三元组
			if (v != 0)
			{	// 设置非零元素值
				p->triElem.value = v;
				delete ePtr;			// 释放ePtr
				return SUCCESS;
			}
			else
			{	// 删除结点
				pre->right = p->right;
			}
		}
		else
		{	// 将ePtr插入在p与pre之间
			pre->right = ePtr;	ePtr->right = p;	
		}
	}

	if (downHead[c] == NULL || downHead[c]->triElem.row >= r)
	{	// ePtr插在第c列链表的表头处
		ePtr->down = downHead[c];	 
		downHead[c] = ePtr;
		num++;							// 插入结点,非零元素个数自加1
	}
	else
	{	// 寻找在第col列链表中的三元组位置
		pre = NULL; p=downHead[c];	// 初始化p和pre
		while (p != NULL && p->triElem.row < r)
		{	// p与pre下移
			pre = p;	p = p->down;
		}
		if (p != NULL && p->triElem.row == r && p->triElem.col == c)
		{	// 找到三元组
			if (v != 0)
			{	// 设置非零元素值
				p->triElem.value = v;
				delete ePtr;			// 释放ePtr
			}
			else
			{	// 删除结点
				pre->down = p->down;
				delete p; delete ePtr;	// 释放存储空间
				num++;					// 删除结点,非零元素个数自减1
			}
		}
		else
		{	// 将ePtr插入在p与pre之间
			pre->down = ePtr;	ePtr->down = p;	
		}
		num++;							// 插入结点,非零元素个数自加1
	}

	return SUCCESS;							// 成功
}

template <class ElemType>
StatusCode CLkSparseMatrix<ElemType>::GetElem(int r, int c, ElemType &v)
// 操作结果：如果下标范围错,则返回RANGE_ERROR,否则返回SUCCESS,并用v返回指定位置元素值
{
	if (r > rows || c > cols || r < 1 || c < 1)
		return RANGE_ERROR;			// 下标范围错
	
	CLkTriNode<ElemType> *p;
	for (p=rightHead[r]; p != NULL && p->triElem.col < c; p = p->right);
		// 寻找在第r行链表中的三元组位置
	if (p != NULL && p->triElem.row == r && p->triElem.col == c)
	{	// 找到三元组
		v = p->triElem.value;
	}
	else
	{	// 未找到三元组
		v = 0;						// 不存在指定位置(r, c)的三元组,表示0元素
	}

	return SUCCESS;					// 成功
}

template <class ElemType>
StatusCode CLkSparseMatrix<ElemType>::InsertHelp(const Triple<ElemType> &e)
// 操作结果：如果下标范围错,则返回RANGE_ERROR,如果三元组下标重复,则返回
//	DUPLICATE_ERROR,如果插入成功,则返回SUCCESS
{
	if (e.row > rows || e.col > cols || e.row < 1 || e.col < 1)
		return RANGE_ERROR;				// 下标范围错
		return RANGE_ERROR;				// 下标范围错
	
	CLkTriNode<ElemType> *pre, *p;
	int row = e.row, col = e.col;

	CLkTriNode<ElemType> *ePtr = new CLkTriNode<ElemType>(e);

	// 将ePtr插入第row行链表的适当位置
	if (rightHead[row] == NULL ||  rightHead[row]->triElem.col >= col)
	{	// ePtr插在第row行链表的表头处
		ePtr->right = rightHead[row];	 
		rightHead[row] = ePtr;
	}
	else
	{	// 寻找在第row行链表中的插入位置
		pre = NULL; p=rightHead[row];	// 初始化p和pre
		while (p != NULL && p->triElem.col < col)
		{	// p与pre右移
			pre = p;	p = p->right;
		}
		if (p != NULL && p->triElem.row == row && p->triElem.col == col)
		{	// 三元组下标重复
			return DUPLICATE_ERROR;			
		}
		pre->right = ePtr;	ePtr->right = p;	// 将ePtr插入在p与pre之间
	}

	// 将ePtr插入在第col列链表的适当位置
	if (downHead[col] == NULL || downHead[col]->triElem.row >= row)
	{	// ePtr插在第col列链表的表头处
		ePtr->down = downHead[col];	 
		downHead[col] = ePtr;
	}
	else
	{	// 寻找在第col列链表中的插入位置
		pre = NULL; p=downHead[col];	// 初始化p和pre
		while (p != NULL && p->triElem.row < row)
		{	// p与pre下移
			pre = p;	p = p->down;
		}
		if (p != NULL && p->triElem.row == row && p->triElem.col == col)
		{	// 三元组下标重复
			return DUPLICATE_ERROR;			
		}
		pre->down = ePtr;	ePtr->down = p;	// 将ePtr插入在p与pre之间
	}

	num++;								// 非零元素个数自加1
	return SUCCESS;						// 插入成功
}

template <class ElemType>
CLkSparseMatrix<ElemType>::CLkSparseMatrix(const CLkSparseMatrix<ElemType> &copy)
// 操作结果：由稀疏矩阵copy构造新稀疏矩阵——复制构造函数
{
	rows = copy.rows;					// 复制行数
	cols = copy.cols;					// 复制列数
	num = 0;							// 初始化非零元个数
	rightHead = new CLkTriNode<ElemType> *[rows + 1];	// 分配行链表表头数组存储空间
	downHead = new CLkTriNode<ElemType> *[cols + 1];	// 分配行链表表头数组存储空间
	int row;											// 行 
	int col;											// 列 
	for (row = 1; row <= rows; row++) 
		rightHead[row] = NULL;			// 初始化行链表表头数组
	for (col = 1; col <= cols; col++) 
		downHead[col] = NULL;			// 初始化行链表表头数组
	
	for (row = 1; row <= rows; row++)
	{	// 复制第row行的三元组
		for (CLkTriNode<ElemType> *p = copy.rightHead[row]; p != NULL; p = p->right)
		{	// 复制第row行的三元组
			InsertHelp(p->triElem);
		}
	}
}

template <class ElemType>
CLkSparseMatrix<ElemType> &CLkSparseMatrix<ElemType>::operator =(const CLkSparseMatrix<ElemType> &copy)
// 操作结果：将稀疏矩阵copy赋值给当前稀疏矩阵——赋值语句重载
{
	if (&copy != this)
	{
		DestroyHelp();						// 清空稀疏矩阵

		rows = copy.rows;				// 复制行数
		cols = copy.cols;				// 复制列数
		num = 0;						// 初始化非零元个数
		rightHead = new CLkTriNode<ElemType> *[rows + 1];	// 分配行链表表头数组存储空间
		downHead = new CLkTriNode<ElemType> *[cols + 1];	// 分配行链表表头数组存储空间
		int row;											// 行 
		int col;											// 列 
		for (row = 1; row <= rows; row++) 
			rightHead[row] = NULL;			// 初始化行链表表头数组
		for (col = 1; col <= cols; col++) 
			downHead[col] = NULL;			// 初始化行链表表头数组

		for (row = 1; row <= rows; row++)
		{	// 复制第row行的三元组
			for (CLkTriNode<ElemType> *p = copy.rightHead[row]; p != NULL; p = p->right)
			{	// 复制第row行的三元组
				InsertHelp(p->triElem);
			}
		}
	}
	return *this;
}
#endif
