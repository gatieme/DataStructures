#ifndef __ADJ_MATRIX_DIR_GRAPH_H__
#define __ADJ_MATRIX_DIR_GRAPH_H__

// 有向图的邻接矩阵类
template <class ElemType>
class AdjMatrixDirGraph 
{
protected:
// 邻接矩阵的数据成员:
	int vexNum, edgeNum;						// 顶点个数和边数
	int **Matrix;								// 邻接矩阵
	ElemType *elems;							// 顶点元素
	mutable StatusCode *tag;					// 指向标志数组的指针

// 辅助函数
	void DestroyHelp();							// 销毁有向图,释放有向图占用的空间

public:
// 抽象数据类型方法声明及重载编译系统默认方法声明:
	AdjMatrixDirGraph(ElemType es[], int vertexNum = DEFAULT_SIZE);	
		// 构造数据元素es[],顶点个数为vertexNum,边数为0的有向图
	AdjMatrixDirGraph(int vertexNum = DEFAULT_SIZE);	
		// 构造顶点个数为vertexNum,边数为0的有向图
	~AdjMatrixDirGraph();						// 析构函数
	StatusCode GetElem(int v, ElemType &e) const;// 求顶点的元素	
	StatusCode SetElem(int v, const ElemType &e);// 设置顶点的元素值
	int GetVexNum() const;						// 返回顶点个数			 
	int GetEdgeNum() const;						// 返回边数个数			 
	int FirstAdjVex(int v) const;				// 返回顶点v的第一个邻接点			 
	int NextAdjVex(int v1, int v2) const;		// 返回顶点v1的相对于v2的下一个邻接点			 
	void InsertEdge(int v1, int v2);			// 插入顶点为v1和v2的边			 
	void DeleteEdge(int v1, int v2);			// 删除顶点为v1和v2的边			 
	StatusCode GetTag(int v) const;				// 返回顶点v的标志		 
	void SetTag(int v, StatusCode val) const;	// 设置顶点v的标志为val		 
	AdjMatrixDirGraph(const AdjMatrixDirGraph<ElemType> &copy);	// 复制构造函数
	AdjMatrixDirGraph<ElemType> &operator =(const AdjMatrixDirGraph<ElemType> &copy); 
		// 赋值语句重载
}; 

#ifndef _MSC_VER					// 表示非VC 

// 非VC需要在函数声明时写上参数缺省值 
template <class ElemType>
void Display(const AdjMatrixDirGraph<ElemType> &g, bool showVexElem = true);// 显示邻接矩阵有向图

#else								// 表示VC 

// VC不必在函数声明时写上参数缺省值 
template <class ElemType>
void Display(const AdjMatrixDirGraph<ElemType> &g, bool showVexElem);	// 显示邻接矩阵有向图

#endif


template <class ElemType>
void Display(const AdjMatrixDirGraph<ElemType> &g, bool showVexElem);	// 显示邻接矩阵有向图


// 有向图的邻接矩阵类的实现部分
template <class ElemType>
AdjMatrixDirGraph<ElemType>::AdjMatrixDirGraph(ElemType es[], int vertexNum)
// 操作结果：构造数据元素es[],顶点个数为vertexNum,边数为0的有向图
{
	if (vertexNum < 0)	throw Error("顶点个数不能为负!");// 抛出异常

	vexNum = vertexNum;							// 顶点数为vertexNum
	edgeNum = 0;								// 边数为0

	elems = new ElemType[vexNum];				// 生成顶点元素标数组
	
	int u, v;									// 临时变量 
	for (v = 0; v < vexNum; v++)
	{	// 初始化数据元素
		elems[v] = es[v];
	}

	tag = new StatusCode[vexNum];				// 生成标志数组
	for (v = 0; v < vexNum; v++)
	{	// 初始化标志数组
		tag[v] = UNVISITED;
	}

	Matrix = (int **)new int *[vexNum];			// 生成邻接矩阵
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
AdjMatrixDirGraph<ElemType>::AdjMatrixDirGraph(int vertexNum)
// 操作结果：构造顶点个数为vertexNum,边数为0的有向图
{
	if (vertexNum < 0)	throw Error("顶点个数不能为负!");// 抛出异常

	vexNum = vertexNum;							// 顶点数为vertexNum
	edgeNum = 0;								// 边数为0

	elems = new ElemType[vexNum];				// 生成顶点元素标数组

	int u, v;									// 临时变量 
	tag = new StatusCode[vexNum];				// 生成标志数组
	for (v = 0; v < vexNum; v++)
	{	// 初始化标志数组
		tag[v] = UNVISITED;
	}

	Matrix = (int **)new int *[vexNum];			// 生成邻接矩阵
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
void AdjMatrixDirGraph<ElemType>::DestroyHelp()
// 操作结果：销毁有向图,释放有向图占用的空间
{
	delete []elems;								// 释放元素
	delete []tag;								// 释放标志

	for (int iPos = 0; iPos < vexNum; iPos++)
	{	// 释放邻接矩阵的行
		delete []Matrix[iPos];
	}
	delete []Matrix;							// 释放邻接矩阵
}

template <class ElemType>
AdjMatrixDirGraph<ElemType>::~AdjMatrixDirGraph()
// 操作结果：释放对象所占用空间
{
	DestroyHelp();
}

template <class ElemType>
StatusCode AdjMatrixDirGraph<ElemType>::GetElem(int v, ElemType &e) const
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
StatusCode AdjMatrixDirGraph<ElemType>::SetElem(int v, const ElemType &e)
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
int AdjMatrixDirGraph<ElemType>::GetVexNum() const
// 操作结果：返回顶点个数			 
{
	return vexNum;
}

template <class ElemType>
int AdjMatrixDirGraph<ElemType>::GetEdgeNum() const
// 操作结果：返回边数个数
{
	return edgeNum;
}		 

template <class ElemType>
int AdjMatrixDirGraph<ElemType>::FirstAdjVex(int v) const
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
int AdjMatrixDirGraph<ElemType>::NextAdjVex(int v1, int v2) const
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
void AdjMatrixDirGraph<ElemType>::InsertEdge(int v1, int v2)
// 操作结果：插入顶点为v1和v2,权为w的边			 
{
	if (v1 < 0 || v1 >= vexNum) throw Error("v1不合法!");	// 抛出异常
	if (v2 < 0 || v2 >= vexNum) throw Error("v2不合法!");	// 抛出异常
	if (v1 == v2) throw Error("v1不能等于v2!");				// 抛出异常

	if (Matrix[v1][v2] == 0)
	{	// 原有向图无边<v1, v2>,插入后边数自增1
		edgeNum++;
	}
	Matrix[v1][v2] = 1;					// 修改<v1, v2>对应的邻接矩阵元素值
}

template <class ElemType>
void AdjMatrixDirGraph<ElemType>::DeleteEdge(int v1, int v2)
// 操作结果：删除顶点为v1和v2的边			 
{
	if (v1 < 0 || v1 >= vexNum) throw Error("v1不合法!");	// 抛出异常
	if (v2 < 0 || v2 >= vexNum) throw Error("v2不合法!");	// 抛出异常
	if (v1 == v2) throw Error("v1不能等于v2!");				// 抛出异常

	if (Matrix[v1][v2] != 0)
	{	// 原有向图存在边<v1, v2>,删除后边数自减1
		edgeNum--;
	}
	Matrix[v1][v2] = 0;					// 修改<v1, v2>对应的邻接矩阵元素值
}

template <class ElemType>
StatusCode AdjMatrixDirGraph<ElemType>::GetTag(int v) const
// 操作结果：返回顶点v的标志		 
{
	if (v < 0 || v >= vexNum) throw Error("v不合法!");		// 抛出异常

	return tag[v];
}

template <class ElemType>
void AdjMatrixDirGraph<ElemType>::SetTag(int v, StatusCode val) const 
// 操作结果：设置顶点v的标志为val		 
{
	if (v < 0 || v >= vexNum) throw Error("v不合法!");		// 抛出异常

	tag[v] = val;
}

template <class ElemType>
AdjMatrixDirGraph<ElemType>::AdjMatrixDirGraph(const AdjMatrixDirGraph<ElemType> &copy)
// 操作结果：由有向图的邻接矩阵copy构造新有向图的邻接矩阵copy——复制构造函数
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

	Matrix = (int **)new int *[vexNum];			// 生成邻接矩阵
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
AdjMatrixDirGraph<ElemType> &AdjMatrixDirGraph<ElemType>::operator =(const AdjMatrixDirGraph<ElemType> &copy)
// 操作结果：将有向图的邻接矩阵copy赋值给当前有向图的邻接矩阵——赋值语句重载
{
	if (&copy != this)
	{
		DestroyHelp();							// 释放当前有向图占用空间

		int iPos, jPos;							// 临时变量
		vexNum = copy.vexNum;					// 复制顶点数
		edgeNum = copy.edgeNum;					// 复制边数

		elems = new ElemType[vexNum];		// 生成顶点数据数组
		for (iPos = 0; iPos < vexNum; iPos++)
		{	// 复制顶点数据数组
			elems[iPos] = copy.elems[iPos];
		}

		tag = new StatusCode[vexNum];			// 生成标志数组
		for (iPos = 0; iPos < vexNum; iPos++)
		{	// 复制标志数组
			tag[iPos] = copy.tag[iPos];
		}

		Matrix = (int **)new int*[vexNum];		// 生成邻接矩阵
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

#ifndef _MSC_VER					// 表示非VC 

// 非VC不能在函数定义时写上参数缺省值 
template <class ElemType>
void Display(const AdjMatrixDirGraph<ElemType> &g, bool showVexElem)
// 操作结果: 显示邻接矩阵有向图
{
	int **Matrix;									// 邻接矩阵
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
	{	// 查找有向图中v的邻接点
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

#else								// 表示VC 

// VC可以在函数定义时写上参数缺省值 
template <class ElemType>
void Display(const AdjMatrixDirGraph<ElemType> &g, bool showVexElem = true)
// 操作结果: 显示邻接矩阵有向图
{
	int **Matrix;									// 邻接矩阵
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
	{	// 查找有向图中v的邻接点
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

#endif
