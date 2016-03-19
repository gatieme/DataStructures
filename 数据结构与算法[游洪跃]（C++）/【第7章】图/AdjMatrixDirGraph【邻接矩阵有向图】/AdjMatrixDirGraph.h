/**
******************************************************************************
*  CopyRight  : 2012-2013, HerBinUnversity, GatieMe                          *
*  File Name  : main.cpp                                                     *
*  Description: 邻接矩阵无向图类AdjMatrixDirGraph声明头文件                               *
*  Author     : Gatie_Me                                                     *
*  Version    : Copyright 2012 JULY_CITY                                     *
*  Data_Time  : 2012-11-6_10:21:43                                           *
*  Content    : 数据结构与算法（C++）版书上源码                             *
******************************************************************************
**/

#ifndef ADJMATRIXDIRGRAPH_H_INCLUDED
#define ADJMATRIXDIRGRAPH   _H_INCLUDED



#include <stdexcept>
#include <iomanip>
#include <queue>

/*
/// 定义一个访问标识枚举变量
#ifndef ISVISITED_DEFINE_INCLUDE
#define ISVISITED_DEFINE_INCLUDE
// 0表示未被访问, 1标识访问过了
typedef enum{UNVISITED = 0, VISITED = 1}IsVisited;
#endif
*/
// 宏定义了标识信息
#ifndef ISVISITED_DEFINE_INCLUDE
#define ISVISITED_DEFINE_INCLUDE
// 0表示未被访问, 1标识访问过了

#define UNVISITED  false
#define   VISITED  true

#endif


/// 邻接矩阵无向图类AdjMatrixDirGraph声明部分
template <class ElemType>
class AdjMatrixDirGraph
{
    /*===========================【PUBLIC：公共接口】============================*/
public :      // 公共接口
    // 邻接矩阵无向图类AdjMatrixDirGraph基本成员函数
    AdjMatrixDirGraph( );         // 默认构造函数模版

    AdjMatrixDirGraph(ElemType *vertex, int vexNum);  // 构造顶点数据为vertex, 顶点个数为vexNum的无向图

    AdjMatrixDirGraph(int vexNum);                    // 构造顶点个数为vexNum的无向图

    AdjMatrixDirGraph(const AdjMatrixDirGraph<ElemType> &copy); // 复制构造函数

    AdjMatrixDirGraph<ElemType>& operator=(const AdjMatrixDirGraph<ElemType> &copy);    // 重载赋值运算符函数

    ~AdjMatrixDirGraph( );                            // 析构函数

    // 邻接矩阵无向图类AdjMatrixDirGraph特征成员函数
    int GetVertex(ElemType &elem);      // 获取当前顶点信息在原图中的位置

    void ShowMarix( );      // 显示图的邻接矩阵信息

    void SetGraph(ElemType *vertexs, int edge);            // 修改图的顶点数和边数

    ElemType GetVertexElem(int vertex);                       // 求顶点的元素值

    bool SetElem(int vertex, const ElemType elem);      // 设置顶点的元素值

    int GetVertexCount( );               // 获取顶点的数目

    int GetEdgeCount( );                // 获取边的数目

    int FirstAdjVertex(int vertex);     // 获取顶点vertex的第一个邻接点

    int NextAdjVertex(int vertex1, int vertex2);    // 返回顶点vertex1相对于vertex2的下一个邻接点

    bool InsertEdge(int vertex1, int vertex2);            // 插入vertex1与vertex2的边

    bool DeleteEdge(int vertex1, int vertex2);          // 删除vertex1与vertex2的边

    bool GetVisited(int vertex);                         // 返回顶点vertex的访问标识信息

    void SetVisited(int vertex, bool isVisited);        // 设置顶点vertex的访问信息

    void DFSTraverse(void (*Visit)(const ElemType &));      // 深度优先搜素

    void BFSTraverse(void (*Visit)(const ElemType &));      // 广度优先搜素

    void DFSTraverse(int vertex, void (*Visit)(const ElemType &));      // 深度优先搜素

    void BFSTraverse(int vertex, void (*Visit)(const ElemType &));      // 广度优先搜素
    /*===========================【PUBLIC：公共接口】============================*/
///////////////////////////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////////
    /*=========================【PROTECTED：保护成员】===========================*/
protected ://summit, peak, apex, zenith, acme, vertex
    // 邻接矩阵无向图类AdjMatrixDirGraph数据成员
    int m_vertexSize;                       // 顶点个数
    int m_edgeSize;                      // 边数
    int **m_matrix;                     // 邻接矩阵
    ElemType *m_elems;                 // 顶点元素
    //mutable IsVisited *m_visited;
    mutable bool *m_visited;              // 用于标识当前顶点是否被访问

    // 邻接矩阵无向图类AdjMatrixDirGraph辅助函数模版
    void DestroyGraph( );                // 销毁无向图, 释放无向图的空间

    void DFS(int vertex, void (* Visit)(const ElemType &));     // 从顶点vertex出发进行深度优先搜索

    void BFS(int veretx, void (* Visit)(const ElemType &));     // 从顶点vertex出发进行广度优先搜索
};



/**邻接矩阵无向图类AdjMatrixDirGraph辅助函数模版[实现]***********************************
    void DestroyGraph( );                // 销毁无向图, 释放无向图的空间
    void BFS(int vertex, void (* Visit)(const ElemType &));     // 从顶点vertex出发进行深度优先搜索
    void DFS(int veretx, void (* Visit)(const ElemType &));     // 从顶点vertex出发进行广度优先搜索
***********************************[实现]邻接矩阵无向图类AdjMatrixDirGraph辅助函数模版**/
//// 函数名称：void DestroyGraph( );
//// 操作结果：销毁无向图, 释放无向图的空间
//template <class ElemType>
//void AdjMatrixDirGraph<ElemType>::CreateGraph(int vertexNum)
//{
//#ifdef DEBUG    // 插桩调试信息
//std::cout <<"FUN:"<<__func__  <<", LINE:" <<__LINE__ <<std::endl;   // 输出函数信息
//#endif
//    // 函数实现部分
//	if (vertexNum < 0)
//	{
//        throw std::out_of_range("顶点数目不能为负数\n");;// 抛出异常
//	}
//
//	this->m_vertexSize = vertexNum;			// 顶点数为vertexNum
//	this->m_edgeSize = 0;							// 初始化边数为0
//
//    // 开辟顶点数据的数组, 但是不需要初始化
//	this->m_elems = new ElemType[vertexNum];
//
//
//	int v/*循环顶点信息*/,u/*循环边信息*/;
//
//	this->m_visited = new bool[vertexNum];				// 生成标志数组
//	for (v = 0; v < vertexNum; v++)
//	{	// 初始化标志数组
//		this->m_visited[v] = UNVISITED;
//	}
//
//	this->m_matrix = (int **)new int *[vertexNum];  // 开辟无向图邻接矩阵
//	for (v = 0; v < vertexNum; v++)     // 为每个顶点的邻接信息
//	{
//		this->m_matrix[v] = new int[vertexNum];
//	}
//
//	for (u = 0; u < vertexNum; u++)            // 循环每条边
//	{
//		for (v = 0; v < vertexNum; v++)        // 循环每个顶点
//		{
//			this->m_matrix[u][v] = 0;             // 初始化为0
//		}
//	}
//}



// 函数名称：void DestroyGraph( );
// 操作结果：销毁无向图, 释放无向图的空间
template <class ElemType>
void AdjMatrixDirGraph<ElemType>::DestroyGraph( )
{
#ifdef DEBUG    // 插桩调试信息
    std::cout <<"FUN:"<<__func__  <<", LINE:" <<__LINE__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现部分
    if(m_elems != NULL)
    {
        delete[] m_elems;          // 删除图的邻接矩阵存储信息
    }
    m_elems = NULL;

    if(m_visited != NULL)
    {
        delete[] m_visited;         // 删除图的顶点访问标识信息
    }
    m_visited = NULL;

    if(m_matrix != NULL)
    {
        for(int i = 0; i < this->m_vertexSize; i++)
        {
            delete[] m_matrix[i];       // 删除第i个顶点的存储信息
        }

        delete[] m_matrix;              // 删除邻接矩阵
        m_matrix = NULL;
    }
}

// 函数名称：void DFS(int veretx, void (* Visit)(const ElemType &));
// 操作结果：从顶点vertex出发进行深度度优先搜索
template <class ElemType>
void AdjMatrixDirGraph<ElemType>::DFS(int vertex, void (* Visit)(const ElemType &))     // 从顶点vertex出发进行深度优先搜索
{
#ifdef DEBUG    // 插桩调试信息
    std::cout <<"FUN:"<<__func__  <<", LINE:" <<__LINE__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现部分
    this->SetVisited(vertex, VISITED);      // 将veretx访问标识标识为已访问
    /*上面代码等价于*/this->m_visited[vertex] = VISITED;

    ElemType elem = this->GetVertexElem(vertex);        // 获取当前第vertex个顶点的顶点数据
    (* Visit)(elem);            // 用Visit函数当前顶点信息

    int vexTemp;
    for(vexTemp = this->FirstAdjVertex(vertex);    /*当前顶点的第一个邻接点开始搜索*/
            vexTemp != -1/*查询不到邻接点时会返回-1*/;
            vexTemp = this->NextAdjVertex(vertex, vexTemp))
    {
        //if(this->GetVisited() == UNVISITED) // 只要当前点还未被访问
        if(this->m_visited[vexTemp] == UNVISITED)
        {
            DFS(vexTemp, Visit);        // 递归访问vexTemp
        }
    }
}


// 函数名称：void BFS(int veretx, void (* Visit)(const ElemType &));
// 操作结果：从顶点vertex出发进行广度优先搜索
template <class ElemType>
void AdjMatrixDirGraph<ElemType>::BFS(int vertex, void (* Visit)(const ElemType &))     // 从顶点vertex出发进行广度优先搜索
{
#ifdef DEBUG    // 插桩调试信息
    std::cout <<"FUN:"<<__func__  <<", LINE:" <<__LINE__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现部分
    //this->SetVisited(vertex, VISITED);      // 将veretx访问标识标识为已访问
    /*上面代码等价于*/this->m_visited[vertex] = VISITED;

    //ElemType elem = this->GetVertexElem(vertex);        // 获取当前第vertex个顶点的顶点数据

    (* Visit)(this->m_elems[vertex]);            // 用Visit函数当前顶点信息


    std::queue<int> myQueue;           // 一个队列
    int vex, vexTemp;
    myQueue.push(vertex);

    while(!myQueue.empty())
    {
        vex = myQueue.front( );
        myQueue.pop( );

        for(vexTemp = this->FirstAdjVertex(vex);        // 从当前结点的的第一个邻接点开始
            vexTemp != -1;      // 如果没有邻接点是停止
            vexTemp = this->NextAdjVertex(vex, vexTemp))    // 寻找下一个邻接点
        {
            if(this->m_visited[vexTemp] == UNVISITED)
            {
                this->m_visited[vexTemp] = VISITED;

                (* Visit)(this->m_elems[vexTemp]);      // 访问当前顶点

                myQueue.push(vexTemp);            // 将当前顶点入队
            }
        }

    }

}

/**邻接矩阵无向图类AdjMatrixDirGraph基本成员函数[实现]***********************************
    AdjMatrixDirGraph( );         // 默认构造函数模版
    AdjMatrixDirGraph(ElemType *vertex, int vexNum);  // 构造顶点数据为vertex, 顶点个数为vexNum的无向图
    AdjMatrixDirGraph(int vexNum);                    // 构造顶点个数为vexNum的无向图
    AdjMatrixDirGraph(const AdjMatrixDirGraph<ElemType> &copy); // 复制构造函数
    AdjMatrixDirGraph<ElemType>& operator=(const AdjMatrixDirGraph<ElemType> &copy);    // 重载赋值运算符函数
    ~AdjMatrixDirGraph( );                            // 析构函数
***********************************[实现]邻接矩阵无向图类AdjMatrixDirGraph基本成员函数**/
// 函数名称：AdjMatrixDirGraph( );         // 默认构造函数模版
// 操作方法：构造顶点数据为vertex, 顶点个数为vexNum的无向图
template <class ElemType>
AdjMatrixDirGraph<ElemType>::AdjMatrixDirGraph( )         // 默认构造函数模版
{
    m_vertexSize = 0;                       // 顶点个数
    m_edgeSize = 0;                      // 边数
    m_matrix = NULL;                     // 邻接矩阵
    m_elems = NULL;                 // 顶点元素
    m_visited = NULL;              // 用于标识当前顶点是否被访问
}


// 函数名称：AdjMatrixDirGraph(ElemType *vertex, int vexNum);
// 操作方法：构造顶点数据为vertex, 顶点个数为vexNum的无向图
template <class ElemType>
AdjMatrixDirGraph<ElemType>::AdjMatrixDirGraph(ElemType *vertexs, int vertexNum)  // 构造顶点数据为vertex, 顶点个数为vexNum的无向图
{
#ifdef DEBUG    // 插桩调试信息
    std::cout <<"FUN:"<<__func__  <<", LINE:" <<__LINE__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现部分
    if (vertexNum < 0)
    {
        throw std::out_of_range("顶点数目不能为负数\n");;// 抛出异常
    }
    this->m_vertexSize = vertexNum;		// 顶点数为vertexNum
    this->m_edgeSize = 0;				// 边数为0

    this->m_elems = new ElemType[vertexNum];    // 开辟顶点数据标数组
    this->m_visited = new bool[vertexNum];		// 开辟访问标识数组

    int v/*循环顶点信息*/,u/*循环边信息*/;

    for (v = 0; v < vertexNum; v++)     // 初始化
    {
        // 循环每个顶点
        this->m_elems[v] = vertexs[v];          // 存储顶点的信息
        this->m_visited[v] = UNVISITED;         // 默认每个顶点的为未访问
    }

    m_matrix = (int **)new int *[vertexNum];   // 开盘当前无向图的邻接矩阵

    for (v = 0; v < vertexNum; v++)         // 循环每个顶点
    {
        // 生成邻接矩阵的行
        this->m_matrix[v] = new int[vertexNum];
    }

    for (u = 0; u < vertexNum; u++)         // 循环每条边
    {
        for (v = 0; v < vertexNum; v++)        // 循环每个顶点
        {
            m_matrix[u][v] = 0;         // 为邻接矩阵元素赋值
        }
    }
}

// 函数名称：AdjMatrixDirGraph(int vexNum);
// 操作方法：构造顶点个数为vexNum的无向图
template <class ElemType>
AdjMatrixDirGraph<ElemType>::AdjMatrixDirGraph(int vertexNum)                    // 构造顶点个数为vexNum的无向图
{
#ifdef DEBUG    // 插桩调试信息
    std::cout <<"FUN:"<<__func__  <<", LINE:" <<__LINE__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现部分
    if (vertexNum < 0)
    {
        throw std::out_of_range("顶点数目不能为负数\n");;// 抛出异常
    }

    this->m_vertexSize = vertexNum;			// 顶点数为vertexNum
    this->m_edgeSize = 0;							// 初始化边数为0

    // 开辟顶点数据的数组, 但是不需要初始化
    this->m_elems = new ElemType[vertexNum];


    int v/*循环顶点信息*/,u/*循环边信息*/;

    this->m_visited = new bool[vertexNum];				// 生成标志数组
    for (v = 0; v < vertexNum; v++)
    {
        // 初始化标志数组
        this->m_visited[v] = UNVISITED;
    }

    this->m_matrix = (int **)new int *[vertexNum];  // 开辟无向图邻接矩阵
    for (v = 0; v < vertexNum; v++)     // 为每个顶点的邻接信息
    {
        this->m_matrix[v] = new int[vertexNum];
    }

    for (u = 0; u < vertexNum; u++)            // 循环每条边
    {
        for (v = 0; v < vertexNum; v++)        // 循环每个顶点
        {
            this->m_matrix[u][v] = 0;             // 初始化为0
        }
    }
}


// 函数名称：AdjMatrixDirGraph(const AdjMatrixDirGraph<ElemType> &copy);
// 操作结果：复制构造函数
template <class ElemType>
AdjMatrixDirGraph<ElemType>::AdjMatrixDirGraph(const AdjMatrixDirGraph<ElemType> &copy) // 复制构造函数
{
#ifdef DEBUG    // 插桩调试信息
    std::cout <<"FUN:"<<__func__  <<", LINE:" <<__LINE__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现部分
    this->m_vertexSize = copy.m_vertexSize;			// 顶点数为vertexNum
    this->m_edgeSize = copy.m_edgeSize;							// 初始化边数为0

    // 开辟顶点数据的数组, 但是不需要初始化
    this->m_elems = new ElemType[this->m_vertexSize];


    int v/*循环顶点信息*/,u/*循环边信息*/;

    this->m_visited = new bool[this->m_vertexSize];				// 生成标志数组
    for (v = 0; v < this->m_vertexSize; v++)
    {
        // 初始化标志数组
        this->m_visited[v] = UNVISITED;
    }

    this->m_matrix = (int **)new int *[this->m_vertexSize];  // 开辟无向图邻接矩阵
    for (v = 0; v < this->m_vertexSize; v++)     // 为每个顶点的邻接信息
    {
        this->m_matrix[v] = new int[this->m_vertexSize];
    }

    for (u = 0; u < this->m_vertexSize; u++)            // 循环每条边
    {
        for (v = 0; v < this->m_vertexSize; v++)        // 循环每个顶点
        {
            this->m_matrix[u][v] = copy.m_matrix[u][v];             // 初始化为0
        }
    }
}


// 函数名称：AdjMatrixDirGraph<ElemType>& operator=(const AdjMatrixDirGraph<ElemType> &copy);
// 操作结果：重载赋值运算符函数
template <class ElemType>
AdjMatrixDirGraph<ElemType>& AdjMatrixDirGraph<ElemType>::operator=(const AdjMatrixDirGraph<ElemType> &copy)    // 重载赋值运算符函数
{
#ifdef DEBUG    // 插桩调试信息
    std::cout <<"FUN:"<<__func__  <<", LINE:" <<__LINE__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现部分
    if(this == &copy)
    {
        return *this;
    }


    this->m_vertexSize = copy.m_vertexSize;			// 顶点数为vertexNum
    this->m_edgeSize = copy.m_edgeSize;							// 初始化边数为0

    // 开辟顶点数据的数组, 但是不需要初始化
    this->m_elems = new ElemType[this->m_vertexSize];


    int v/*循环顶点信息*/,u/*循环边信息*/;

    this->m_visited = new bool[this->m_vertexSize];				// 生成标志数组
    for (v = 0; v < this->m_vertexSize; v++)
    {
        // 初始化标志数组
        this->m_visited[v] = UNVISITED;
    }

    this->m_matrix = (int **)new int *[this->m_vertexSize];  // 开辟无向图邻接矩阵
    for (v = 0; v < this->m_vertexSize; v++)     // 为每个顶点的邻接信息
    {
        this->m_matrix[v] = new int[this->m_vertexSize];
    }

    for (u = 0; u < this->m_vertexSize; u++)            // 循环每条边
    {
        for (v = 0; v < this->m_vertexSize; v++)        // 循环每个顶点
        {
            this->m_matrix[u][v] = copy.m_matrix[u][v];             // 初始化为0
        }
    }

    return (*this);
}


// 函数名称：~AdjMatrixDirGraph( );
// 操作结果：析构函数
template <class ElemType>
AdjMatrixDirGraph<ElemType>::~AdjMatrixDirGraph( )                            // 析构函数
{
#ifdef DEBUG    // 插桩调试信息
    std::cout <<"FUN:"<<__func__  <<", LINE:" <<__LINE__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现部分
    this->DestroyGraph( );
}


/**邻接矩阵无向图类AdjMatrixDirGraph特征成员函数[实现]***********************************
    int GetVertex(ElemType &elem);      // 获取当前顶点信息在原图中的位置
    void Showtarix( );      // 显示图的邻接矩阵信息
    bool SetGraph(int vertex, int edge);            // 修改图的顶点数和边数
    ElemType GetElem(int vertex);                       // 求顶点的元素值
    bool SetElem(int vertex, const ElemType elem);      // 设置顶点的元素值
    int GetVertexCount( );               // 获取顶点的数目
    int GetEdgeCount( );                // 获取边的数目
    int FirstAdjVertex(int vertex);     // 获取顶点vertex的第一个邻接点
    int NextAdjVertex(int vertex1, int vertex2);    // 返回顶点vertex1相对于vertex2的下一个邻接点
    bool InsertEdge(int vertex1, int vertex2);            // 插入vertex1与vertex2的边
    bool DeleteEdge(int vertex1, int vertex2);          // 删除vertex1与vertex2的边
    bool GetVisited(int vertex);                         // 返回顶点vertex的访问标识信息
    bool SetVisited(int vertex, bool isVisited);        // 设置顶点vertex的访问信息
    void BFSTraverse(void (*Visit)(const ElemType &));      // 深度优先搜素
    void DFSTraverse(void (*Visit)(const ElemType &));      // 广度优先搜素
***********************************[实现]邻接矩阵无向图类AdjMatrixDirGraph特征成员函数**/
//函数名称：int GetVertex(ElemType &elem);
//操作结果：获取当前顶点信息在原图中的位置
template <class ElemType>
int AdjMatrixDirGraph<ElemType>::GetVertex(ElemType &elem)      // 获取当前顶点信息在原图中的位置
{
    for(int v = 0; v < this->m_vertexSize; v++)
    {
        if(elem == this->m_elems[v])
        {
            return v;
        }
    }
    return -1;
}



//函数名称：void Showtarix( );
//操作结果：显示图的邻接矩阵信息
template <class ElemType>
void AdjMatrixDirGraph<ElemType>::ShowMarix( )      // 显示图的邻接矩阵信息
{
    std::cout <<"当前图的顶点数目" <<this->m_vertexSize <<", 边数目" <<m_edgeSize <<std::endl;

    std::cout <<"图的邻接矩阵信息" <<std::endl;
    for(int i = 0; i < this->m_vertexSize; i++)
    {
        for(int j = 0; j < this->m_vertexSize; j++)
        {
            std::cout <<std::setw(4)<<m_matrix[i][j];
        }
        std::cout <<std::endl;
    }
}


//函数名称：bool SetGraph(int vertex, int edge);            // 修改图的顶点数和边数
//操作结果：修改图的顶点数和边数
template <class ElemType>
void AdjMatrixDirGraph<ElemType>::SetGraph(ElemType *vertexs, int vertexNum)            // 修改图的顶点数和边数
{
#ifdef DEBUG    // 插桩调试信息
    std::cout <<"FUN:"<<__func__  <<", LINE:" <<__LINE__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现部分
    if (vertexNum < 0)
    {
        throw std::out_of_range("顶点数目不能为负数\n");;// 抛出异常
    }
    this->m_vertexSize = vertexNum;		// 顶点数为vertexNum
    this->m_edgeSize = 0;				// 边数为0

    this->m_elems = new ElemType[vertexNum];    // 开辟顶点数据标数组
    this->m_visited = new bool[vertexNum];		// 开辟访问标识数组

    int v/*循环顶点信息*/,u/*循环边信息*/;

    for (v = 0; v < vertexNum; v++)     // 初始化
    {
        // 循环每个顶点
        this->m_elems[v] = vertexs[v];          // 存储顶点的信息
        this->m_visited[v] = UNVISITED;         // 默认每个顶点的为未访问
    }

    this->m_matrix = (int **)new int *[vertexNum];   // 开盘当前无向图的邻接矩阵

    for (v = 0; v < vertexNum; v++)         // 循环每个顶点
    {
        // 生成邻接矩阵的行
        this->m_matrix[v] = new int[vertexNum];
    }

    for (u = 0; u < vertexNum; u++)         // 循环每条边
    {
        for (v = 0; v < vertexNum; v++)        // 循环每个顶点
        {
            m_matrix[u][v] = 0;         // 为邻接矩阵元素赋值
        }
    }
}


// 函数名称：ElemType GetElem(int vertex);
// 操作结果：求顶点的元素值
template <class ElemType>
ElemType AdjMatrixDirGraph<ElemType>::GetVertexElem(int vertex)                       // 求顶点的元素值
{
#ifdef DEBUG    // 插桩调试信息
    std::cout <<"FUN:"<<__func__  <<", LINE:" <<__LINE__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现部分
    if (vertex < 0 || vertex >= this->m_vertexSize)
    {
        // 参数不合法
        throw std::out_of_range("参数范围不正确\n");
    }
    else
    {
        return this->m_elems[vertex];
    }

}

// 函数名称：bool SetElem(int vertex, const ElemType elem);
// 操作结果： 设置顶点的元素值
template <class ElemType>
bool AdjMatrixDirGraph<ElemType>::SetElem(int vertex, const ElemType elem)      // 设置顶点的元素值
{
#ifdef DEBUG    // 插桩调试信息
    std::cout <<"FUN:"<<__func__  <<", LINE:" <<__LINE__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现部分
    if (vertex < 0 || vertex >= this->m_vertexSize)
    {
        // 参数不合法
        throw std::out_of_range("参数范围不正确\n");
    }
    else
    {
        this->m_elems[vertex] = elem;
    }
}


// 函数名称：int GetVertexCount( );
// 操作结果： 获取顶点的数目
template <class ElemType>
int AdjMatrixDirGraph<ElemType>::GetVertexCount( )               // 获取顶点的数目
{
#ifdef DEBUG    // 插桩调试信息
    std::cout <<"FUN:"<<__func__  <<", LINE:" <<__LINE__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现部分
    return this->m_vertexSize;
}

// 函数名称：int GetEdgeCount( );
// 操作结果： 获取边的数目
template <class ElemType>
int AdjMatrixDirGraph<ElemType>::GetEdgeCount( )                // 获取边的数目
{
#ifdef DEBUG    // 插桩调试信息
    std::cout <<"FUN:"<<__func__  <<", LINE:" <<__LINE__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现部分
    return this->m_edgeSize;
}

// 函数名称：int FirstAdjVertex(int vertex);
// 操作结果： 获取顶点vertex的第一个邻接点
template <class ElemType>
int AdjMatrixDirGraph<ElemType>::FirstAdjVertex(int vertex)     // 获取顶点vertex的第一个邻接点
{
#ifdef DEBUG    // 插桩调试信息
    std::cout <<"FUN:"<<__func__  <<", LINE:" <<__LINE__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现部分
    if (vertex < 0 || vertex >= this->m_vertexSize)
    {
        throw std::out_of_range("参数不在正常范围!");// 抛出异常
    }

    for (int i = 0; i < this->m_vertexSize; i++)
    {   // 查找邻接点
        // 在邻接矩阵中第vertex+1行的元素标识了vertex与其他顶点的关系
        if (m_matrix[vertex][i] != 0)       // 第一个不为0的元素, 就是其第一个邻接点
        {
            return i;
        }
    }

    return -1;
}

// 函数名称：int NextAdjVertex(int vertex1, int vertex2);
// 操作结果： 返回顶点vertex1相对于vertex2的下一个邻接点
template <class ElemType>
int AdjMatrixDirGraph<ElemType>::NextAdjVertex(int vertex1, int vertex2)    // 返回顶点vertex1相对于vertex2的下一个邻接点
{
#ifdef DEBUG    // 插桩调试信息
    std::cout <<"FUN:"<<__func__  <<", LINE:" <<__LINE__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现部分
    if (vertex1 < 0 || vertex1>= this->m_vertexSize)
    {
        throw std::out_of_range("第1个参数不在正常范围!");// 抛出异常
    }
    if (vertex2 < 0 || vertex2 >= this->m_vertexSize)
    {
        throw std::out_of_range("第2个参数不在正常范围!");// 抛出异常
    }

    if (vertex1 == vertex2)
    {
        throw std::out_of_range("两个参数不能等于!");				// 抛出异常
    }

    for (int i = vertex2 + 1/*从第veretx个元素开始查起*/; i < this->m_vertexSize; i++)
    {
        // 查找邻接点
        if (m_matrix[vertex1][i] != 0)
        {
            return i;
        }
    }

    return -1;									// 返回-1表示无邻接点
}

// 函数名称：bool InsertEdge(int vertex1, int vertex2);
// 操作结果： 插入vertex1与vertex2的边
template <class ElemType>
bool AdjMatrixDirGraph<ElemType>::InsertEdge(int vertex1, int vertex2)            // 插入vertex1与vertex2的边
{
#ifdef DEBUG    // 插桩调试信息
    std::cout <<"FUN:"<<__func__  <<", LINE:" <<__LINE__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现部分
    if (vertex1 < 0 || vertex1 >= this->m_vertexSize)
    {
        throw std::out_of_range("第1个参数不在正常范围!");// 抛出异常
    }
    if (vertex2 < 0 || vertex2 >= this->m_vertexSize)
    {
        throw std::out_of_range("第2个参数不在正常范围!");// 抛出异常
    }

    if (vertex1 == vertex2)
    {
        throw std::out_of_range("两个参数不能等于!");				// 抛出异常
    }

    if(m_matrix[vertex1][vertex2] == 0)
    {
        // 原无向图无边(v1, v2),插入后边数自增1
        this->m_edgeSize++;
        m_matrix[vertex1][vertex2] = 1;				// 修改(vertex1, vertex2)对应的邻接矩阵元素值
       // m_matrix[vertex2][vertex1] = 1;				// 修改(vertex2, vertex1)对应的邻接矩阵元素值

        return true;
    }
    else
    {
        #ifdef REMIND
        std::cout <<"无向图中该边已经存在, 无需再添加" <<std::endl;
        #endif
        return false;
    }
}

// 函数名称：bool DeleteEdge(int vertex1, int vertex2);
// 操作结果： 删除vertex1与vertex2的边
template <class ElemType>
bool AdjMatrixDirGraph<ElemType>::DeleteEdge(int vertex1, int vertex2)          // 删除vertex1与vertex2的边
{
#ifdef DEBUG    // 插桩调试信息
    std::cout <<"FUN:"<<__func__  <<", LINE:" <<__LINE__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现部分
    if (vertex1 < 0 || vertex1>= this->m_vertexSize)
    {
        throw std::out_of_range("第1个参数不在正常范围!");
    }
    if (vertex2 < 0 || vertex2 >= this->m_vertexSize)
    {
        throw std::out_of_range("第2个参数不在正常范围!");
    }

    if (vertex1 == vertex2)
    {
        throw std::out_of_range("两个参数不能等于!");
    }

    if(m_matrix[vertex1][vertex2] != 0)
    {
        // 原无向图无边(v1, v2),删除后边数自减少1
        this->m_edgeSize--;

        m_matrix[vertex1][vertex2] = 0;				// 清空(vertex1, vertex2)对应的邻接矩阵元素值
       // m_matrix[vertex2][vertex1] = 0;				// 清空(vertex2, vertex1)对应的邻接矩阵元素值

        return true;
    }
    else
    {
        #ifdef REMIND
        std::cout <<"无向图中该边本就不存在, 无需再删除" <<std::endl;
        #endif

        return false;
    }
}


// 函数名称：bool GetVisited(int vertex);
// 操作结果： 返回顶点vertex的访问标识信息
template <class ElemType>
bool AdjMatrixDirGraph<ElemType>::GetVisited(int vertex)                        // 返回顶点vertex的访问标识信息
{
#ifdef DEBUG    // 插桩调试信息
    std::cout <<"FUN:"<<__func__  <<", LINE:" <<__LINE__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现部分
    if (vertex < 0 || vertex >= this->m_vertexSize)
    {
        throw std::out_of_range("参数不在正常范围!");
    }

    return m_visited[vertex];
}


// 函数名称：bool SetVisited(int vertex, bool isVisited);
// 操作结果： 设置顶点vertex的访问信息
template <class ElemType>
void AdjMatrixDirGraph<ElemType>::SetVisited(int vertex, bool isVisited)        // 设置顶点vertex的访问信息
{
#ifdef DEBUG    // 插桩调试信息
    std::cout <<"FUN:"<<__func__  <<", LINE:" <<__LINE__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现部分
    if (vertex < 0 || vertex >= this->m_vertexSize)
    {
        throw std::out_of_range("参数不在正常范围!");
    }

    this->m_visited[vertex] = isVisited;
}

// 函数名称：void DFSTraverse(void (*Visit)(const ElemType &));
// 操作结果：默认从第0个结点开始进行搜索, 深度优先搜素
template <class ElemType>
void AdjMatrixDirGraph<ElemType>::DFSTraverse(void (* Visit)(const ElemType &))      // 深度优先搜素
{
#ifdef DEBUG    // 插桩调试信息
    std::cout <<"FUN:"<<__func__  <<", LINE:" <<__LINE__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现部分
    int vex;      /*循环搜友顶点*/
    for(vex = 0; vex < this->m_vertexSize; vex++)
    {   // 将每个顶点的访问标识设未访问
        this->SetVisited(vex, UNVISITED);
        // this->m_visited[vertex] = UNVISITED;
    }
    DFS(0, Visit);             // 从第一个顶点开始访问访问
}

// 函数名称：void DFSTraverse(void (*Visit)(const ElemType &));
// 操作结果：用户选择从何任意顶点开始搜索, 深度优先搜素
template <class ElemType>
void AdjMatrixDirGraph<ElemType>::DFSTraverse(int vertex, void (* Visit)(const ElemType &))      // 深度优先搜素
{
#ifdef DEBUG    // 插桩调试信息
    std::cout <<"FUN:"<<__func__  <<", LINE:" <<__LINE__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现部分
    int vex;      /*循环搜友顶点*/
    for(vex = 0; vex < this->m_vertexSize; vex++)
    {   // 将每个顶点的访问标识设未访问
        //this->SetVisited(vex, UNVISITED);
        this->m_visited[vex] = UNVISITED;
    }

    this->DFS(vertex, Visit);             // 从第一个顶点开始访问访问
}


// 函数名称：void BFSTraverse(void (*Visit)(const ElemType &));
// 操作结果：广度优先搜素
template <class ElemType>
void AdjMatrixDirGraph<ElemType>::BFSTraverse(void (*Visit)(const ElemType &))      // 广度优先搜素
{
#ifdef DEBUG    // 插桩调试信息
    std::cout <<"FUN:"<<__func__  <<", LINE:" <<__LINE__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现部分
    int vex;      /*循环搜友顶点*/
    for(vex = 0; vex < this->m_vertexSize; vex++)
    {   // 将每个顶点的访问标识设未访问
        this->SetVisited(vex, UNVISITED);
        // this->m_visited[vertex] = UNVISITED;
    }
    BFS(0, Visit);             // 从第一个顶点开始访问访问
}



// 函数名称：void BFSTraverse(void (*Visit)(const ElemType &));
// 操作结果：广度优先搜素
template <class ElemType>
void AdjMatrixDirGraph<ElemType>::BFSTraverse(int vertex, void (*Visit)(const ElemType &))      // 广度优先搜素
{
#ifdef DEBUG    // 插桩调试信息
    std::cout <<"FUN:"<<__func__  <<", LINE:" <<__LINE__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现部分
    int vex;      /*循环搜友顶点*/
    for(vex = 0; vex < this->m_vertexSize; vex++)
    {   // 将每个顶点的访问标识设未访问
        this->SetVisited(vex, UNVISITED);
        // this->m_visited[vertex] = UNVISITED;
    }
    BFS(vertex, Visit);             // 从第一个顶点开始访问访问
}


#endif // AdjMatrixDirGraph_H_INCLUDED/**
