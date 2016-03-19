#ifndef __ADJ_MATRIX_UNDIR_GRAPH_H__
#define __ADJ_MATRIX_UNDIR_GRAPH_H__

// 无向图的邻接矩阵类
template <class ElemType>
class AdjMatrixUndirGraph 
{
protected:
// 邻接矩阵的数据成员:
	int vexNum, edgeNum;						// 顶点个数和边数
	int **Matrix;								// 邻接矩阵
	ElemType *elems;							// 顶点数据
	mutable StatusCode *tag;					// 指向标志数组的指针

// 辅助函数
	void DestroyHelp();							// 销毁无向图,释放无向图占用的空间

public:
// 抽象数据类型方法声明及重载编译系统默认方法声明:
	AdjMatrixUndirGraph(ElemType es[], int vertexNum = DEFAULT_SIZE);	
		// 构造数据元素es[],顶点个数为vertexNum,边数为0的无向图
	AdjMatrixUndirGraph(int vertexNum = DEFAULT_SIZE);	
		// 构造顶点个数为vertexNum,边数为0的无向图
	~AdjMatrixUndirGraph();						// 析构函数
	StatusCode GetElem(int v, ElemType &e) const;// 求顶点的元素	
	StatusCode SetElem(int v, const ElemType &e);// 设置顶点的元素值
	int GetVexNum() const;						// 返回顶点个数			 
	int GetEdgeNum() const;						// 返回边数			 
	int FirstAdjVex(int v) const;				// 返回顶点v的第一个邻接点			 
	int NextAdjVex(int v1, int v2) const;		// 返回顶点v1的相对于v2的下一个邻接点			 
	void InsertEdge(int v1, int v2);			// 插入顶点为v1和v2的边			 
	void DeleteEdge(int v1, int v2);			// 删除顶点为v1和v2的边			 
	StatusCode GetTag(int v) const;				// 返回顶点v的标志		 
	void SetTag(int v, StatusCode val) const;	// 设置顶点v的标志为val		 
	AdjMatrixUndirGraph(const AdjMatrixUndirGraph<ElemType> &copy);	// 复制构造函数
	AdjMatrixUndirGraph<ElemType> &operator =(const AdjMatrixUndirGraph<ElemType> &copy); 
		// 赋值语句重载
};

template <class ElemType>
void Display(const AdjMatrixUndirGraph<ElemType> &g, bool showVexElem);	// 显示邻接矩阵无向图


// 无向图的邻接矩阵类的实现部分
template <class ElemType>
AdjMatrixUndirGraph<ElemType>::AdjMatrixUndirGraph(ElemType es[], int vertexNum)
// 操作结果：构造数据元素es[],顶点个数为vertexNum,边数为0的无向图
{
	if (vertexNum < 0)	throw Error("顶点个数不能为负!");// 抛出异常

	vexNum = vertexNum;							// 顶点数为vertexNum
	edgeNum = 0;								// 边数为0

	elems = new ElemType[vexNum];				// 生成顶点数据标数组
	
	int u, v;									// 临时变量 
	for (v = 0; v < vexNum; v++)
	{	// 初始化标志数组
		elems[v] = es[v];
	}

	tag = new StatusCode[vexNum];				// 生成标志数组
	for (v = 0; v < vexNum; v++)
	{	// 初始化标志数组
		tag[v] = UNVISITED;
	}

	Matrix = (int **)new int *[vexNum];// 生成邻接矩阵
	for (v = 0; v < vexNum; v++)
	{	// 生成邻接矩阵的行
		Matrix[v] = new int[vexNum];	
	}

	for (u = 0; u < vexNum; u++)
	{
		for (v = 0; v < vexNum; v++)
		{	// 为邻接矩阵元素赋值
			Matrix[u][v] = 0;
		}
	}
}

template <class ElemType>
AdjMatrixUndirGraph<ElemType>::AdjMatrixUndirGraph(int vertexNum)
// 操作结果：构造顶点个数为vertexNum,边数为0的无向图
{
	if (vertexNum < 0)	throw Error("顶点个数不能为负!");// 抛出异常

	vexNum = vertexNum;							// 顶点数为vertexNum
	edgeNum = 0;								// 边数为0

	elems = new ElemType[vexNum];				// 生成顶点数据标数组

	int u, v;									// 临时变量 
	tag = new StatusCode[vexNum];				// 生成标志数组
	for (v = 0; v < vexNum; v++)
	{	// 初始化标志数组
		tag[v] = UNVISITED;
	}

	Matrix = (int **)new int *[vexNum];// 生成邻接矩阵
	for (v = 0; v < vexNum; v++)
	{	// 生成邻接矩阵的行
		Matrix[v] = new int[vexNum];	
	}

	for (u = 0; u < vexNum; u++)
	{
		for (v = 0; v < vexNum; v++)
		{	// 为邻接矩阵元素赋值
			Matrix[u][v] = 0;
		}
	}
}

template <class ElemType>
void AdjMatrixUndirGraph<ElemType>::DestroyHelp()
// 操作结果：销毁无向图,释放无向图占用的空间
{
	delete []elems;							// 释放顶点数据
	delete []tag;								// 释放标志

	for (int iPos = 0; iPos < vexNum; iPos++)
	{	// 释放邻接矩阵的行
		delete []Matrix[iPos];
	}
	delete []Matrix;							// 释放邻接矩阵
}

template <class ElemType>
AdjMatrixUndirGraph<ElemType>::~AdjMatrixUndirGraph()
// 操作结果：释放对象所占用空间
{
	DestroyHelp();
}

template <class ElemType>
StatusCode AdjMatrixUndirGraph<ElemType>::GetElem(int v, ElemType &e) const
// 操作结果：求顶点v的元素, v的取值范围为0 ≤ v ＜ vexNum, v合法时函数返回
//	SUCCESS, 否则函数返回RANGE_ERROR
{
	if (v < 0 || v >= vexNum)
	{	// v范围错
		return NOT_PRESENT;	// 元素不存在
	}
	else
	{	// v合法
		e = elems[v];		// 将顶点v的元素值赋给e
		return ENTRY_FOUND;	// 元素存在
	}
}	

template <class ElemType>
StatusCode AdjMatrixUndirGraph<ElemType>::SetElem(int v, const ElemType &e)
// 操作结果：设置顶点的元素值v的取值范围为0 ≤ v ＜ vexNum, v合法时函数返回
//	SUCCESS, 否则函数返回RANGE_ERROR
{
	if (v < 0 || v >= vexNum)
	{	// v范围错
		return RANGE_ERROR;	// 位置错
	}
	else
	{	// v合法
		elems[v] = e;		// 顶点元素
		return SUCCESS;		// 成功
	}
}

template <class ElemType>
int AdjMatrixUndirGraph<ElemType>::GetVexNum() const
// 操作结果：返回顶点个数			 
{
	return vexNum;
}

template <class ElemType>
int AdjMatrixUndirGraph<ElemType>::GetEdgeNum() const
// 操作结果：返回边数个数
{
	return edgeNum;
}		 

template <class ElemType>
int AdjMatrixUndirGraph<ElemType>::FirstAdjVex(int v) const
// 操作结果：返回顶点v的第1个邻接点			 
{
	if (v < 0 || v >= vexNum) throw Error("v不合法!");// 抛出异常

	for (int cur = 0; cur < vexNum; cur++)
	{	// 查找邻接点
		if (Matrix[v][cur] != 0) return cur;
	}

	return -1;									// 返回-1表示无邻接点
}

template <class ElemType>
int AdjMatrixUndirGraph<ElemType>::NextAdjVex(int v1, int v2) const
// 操作结果：返回顶点v1的相对于v2的下1个邻接点			 
{
	if (v1 < 0 || v1 >= vexNum) throw Error("v1不合法!");	// 抛出异常
	if (v2 < 0 || v2 >= vexNum) throw Error("v2不合法!");	// 抛出异常
	if (v1 == v2) throw Error("v1不能等于v2!");				// 抛出异常

	for (int cur = v2 + 1; cur < vexNum; cur++)
	{	// 查找邻接点
		if (Matrix[v1][cur] != 0) return cur;
	}

	return -1;									// 返回-1表示无邻接点
}

template <class ElemType>
void AdjMatrixUndirGraph<ElemType>::InsertEdge(int v1, int v2)
// 操作结果：插入顶点为v1和v2,权为w的边			 
{
	if (v1 < 0 || v1 >= vexNum) throw Error("v1不合法!");	// 抛出异常
	if (v2 < 0 || v2 >= vexNum) throw Error("v2不合法!");	// 抛出异常
	if (v1 == v2) throw Error("v1不能等于v2!");				// 抛出异常

	if (Matrix[v1][v2] == 0 && Matrix[v2][v1] == 0)
	{	// 原无向图无边(v1, v2),插入后边数自增1
		edgeNum++;
	}
	Matrix[v1][v2] = 1;				// 修改<v1, v2>对应的邻接矩阵元素值
	Matrix[v2][v1] = 1;				// 修改<v2, v1>对应的邻接矩阵元素值
}

template <class ElemType>
void AdjMatrixUndirGraph<ElemType>::DeleteEdge(int v1, int v2)
// 操作结果：删除顶点为v1和v2的边			 
{
	if (v1 < 0 || v1 >= vexNum) throw Error("v1不合法!");	// 抛出异常
	if (v2 < 0 || v2 >= vexNum) throw Error("v2不合法!");	// 抛出异常
	if (v1 == v2) throw Error("v1不能等于v2!");				// 抛出异常

	if (Matrix[v1][v2] != 0 && Matrix[v2][v1] != 0)
	{	// 原无向图存在边(v1, v2),删除后边数自减1
		edgeNum--;
	}
	Matrix[v1][v2] = 0;				// 修改<v1, v2>对应的邻接矩阵元素值
	Matrix[v2][v1] = 0;				// 修改<v2, v1>对应的邻接矩阵元素值
}

template <class ElemType>
StatusCode AdjMatrixUndirGraph<ElemType>::GetTag(int v) const
// 操作结果：返回顶点v的标志		 
{
	if (v < 0 || v >= vexNum) throw Error("v不合法!");	// 抛出异常

	return tag[v];
}

template <class ElemType>
void AdjMatrixUndirGraph<ElemType>::SetTag(int v, StatusCode val) const 
// 操作结果：设置顶点v的标志为val		 
{
	if (v < 0 || v >= vexNum) throw Error("v不合法!");	// 抛出异常

	tag[v] = val;
}

template <class ElemType>
AdjMatrixUndirGraph<ElemType>::AdjMatrixUndirGraph(const AdjMatrixUndirGraph<ElemType> &copy)
// 操作结果：由无向图的邻接矩阵copy构造新无向图的邻接矩阵copy——复制构造函数
{
	int iPos, jPos;								// 临时变量
	vexNum = copy.vexNum;						// 复制顶点数
	edgeNum = copy.edgeNum;						// 复制边数

	elems = new ElemType[vexNum];			// 生成顶点数据数组
	for (iPos = 0; iPos < vexNum; iPos++)
	{	// 复制顶点数据数组
		elems[iPos] = copy.elems[iPos];
	}

	tag = new StatusCode[vexNum];				// 生成标志数组
	for (iPos = 0; iPos < vexNum; iPos++)
	{	// 复制标志数组
		tag[iPos] = copy.tag[iPos];
	}

	Matrix = (int **)new int *[vexNum];	// 生成邻接矩阵
	for (iPos = 0; iPos < vexNum; iPos++)
	{	// 生成邻接矩阵的行
		Matrix[iPos] = new int[vexNum];	
	}

	for (iPos = 0; iPos < vexNum; iPos++)
	{
		for (jPos = 0; jPos < vexNum; jPos++)
		{	// 复制邻接矩阵元素赋值
			Matrix[iPos][jPos] = copy.Matrix[iPos][jPos];
		}
	}
}

template <class ElemType>
AdjMatrixUndirGraph<ElemType> &AdjMatrixUndirGraph<ElemType>::operator =(const AdjMatrixUndirGraph<ElemType> &copy)
// 操作结果：将无向图的邻接矩阵copy赋值给当前无向图的邻接矩阵——赋值语句重载
{
	if (&copy != this)
	{
		DestroyHelp();						// 释放当前无向图占用空间
		int iPos, jPos;						// 临时变量
		vexNum = copy.vexNum;				// 复制顶点数
		edgeNum = copy.edgeNum;				// 复制边数

		elems = new ElemType[vexNum];		// 生成顶点数据数组
		for (iPos = 0; iPos < vexNum; iPos++)
		{	// 复制顶点数据数组
			elems[iPos] = copy.elems[iPos];
		}

		tag = new StatusCode[vexNum];	// 生成标志数组
		for (iPos = 0; iPos < vexNum; iPos++)
		{	// 复制标志数组
			tag[iPos] = copy.tag[iPos];
		}

		Matrix = (int **)new int*[vexNum];	// 生成邻接矩阵
		for (iPos = 0; iPos < vexNum; iPos++)
		{	// 生成邻接矩阵的行
			Matrix[iPos] = new int[vexNum];	
		}

		for (iPos = 0; iPos < vexNum; iPos++)
		{
			for (jPos = 0; jPos < vexNum; jPos++)
			{	// 复制邻接矩阵元素赋值
				Matrix[iPos][jPos] = copy.Matrix[iPos][jPos];
			}
		}
	}
	return *this;
}

template <class ElemType>
void Display(const AdjMatrixUndirGraph<ElemType> &g, bool showVexElem = true)
// 操作结果: 显示邻接矩阵无向图
{
	int **Matrix;							// 邻接矩阵
	Matrix = (int **)new int *[g.GetVexNum()];		// 生成邻接矩阵
	int iPos;										// 临时变量 

	for (iPos = 0; iPos < g.GetVexNum(); iPos++)
	{	// 生成邻接矩阵的行
		Matrix[iPos] = new int[g.GetVexNum()];	
	}

	for (iPos = 0; iPos < g.GetVexNum(); iPos++)
	{
		for (int jPos = 0; jPos < g.GetVexNum(); jPos++)
		{	// 为邻接矩阵元素赋值
			Matrix[iPos][jPos] = 0;
		}
	}

	for (int v = 0; v < g.GetVexNum(); v++)
	{	// 查找无向图中v的邻接点
		for (int u = g.FirstAdjVex(v); u != -1; u = g.NextAdjVex(v, u))
		{	// u为v的邻接点
			Matrix[v][u] = 1;
		}
	}

	for (iPos = 0; iPos < g.GetVexNum(); iPos++)
	{	// 显示行
		if (showVexElem)
		{	// 显示顶点元素
			ElemType e;					// 数据元素
			g.GetElem(iPos, e);			// 取出元素值
			cout << e;					// 显示元素值
		}

		for (int jPos = 0; jPos < g.GetVexNum(); jPos++)
		{	// 显示元素
 			cout << "\t" << Matrix[iPos][jPos];
		}
		cout << endl;					// 换行 
	}

	for (iPos = 0; iPos < g.GetVexNum(); iPos++)
	{	// 释放邻接矩阵的行
		delete []Matrix[iPos];
	}
	delete []Matrix;					// 释放邻接矩阵
}

#endif
