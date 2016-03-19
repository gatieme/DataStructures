/**
******************************************************************************
*  CopyRight  : 2012-2013, HerBinUnversity, GatieMe                          *
*  File Name  : main.cpp                                                     *
*  Description: 邻接表无向图类AdjListUndirGraphAdjListUndirGraph声明头文件                               *
*  Author     : Gatie_Me                                                     *
*  Version    : Copyright 2012 JULY_CITY                                     *
*  Data_Time  : 2012-11-6_10:21:43                                           *
*  Content    : 数据结构与算法（C++）版书上源码                             *
******************************************************************************
**/

#ifndef ADJLISTUNDIRGRAPH_H_INCLUDED
#define ADJLISTUNDIRGRAPH_H_INCLUDED



#include <stdexcept>
#include <iomanip>
#include <list>
#include <cstring>
#include <queue>
#include "AdjListGraphVertexNode.h"
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


/// 邻接表无向图类AdjListUndirGraphAdjListUndirGraph声明部分
template <class ElemType>
class AdjListUndirGraph
{
    /*===========================【PUBLIC：公共接口】============================*/
public :      // 公共接口
    // 邻接表无向图类AdjListUndirGraphAdjListUndirGraph基本成员函数
    AdjListUndirGraph( );         // 默认构造函数模版

    AdjListUndirGraph(ElemType *vertex, int vexNum);  // 构造顶点数据为vertex, 顶点个数为vexNum的无向图

    AdjListUndirGraph(int vexNum);                    // 构造顶点个数为vexNum的无向图

    AdjListUndirGraph(const AdjListUndirGraph<ElemType> &copy); // 复制构造函数

    AdjListUndirGraph<ElemType>& operator=(const AdjListUndirGraph<ElemType> &copy);    // 重载赋值运算符函数

    ~AdjListUndirGraph( );                            // 析构函数

    // 邻接表无向图类AdjListUndirGraphAdjListUndirGraph特征成员函数
    int GetVertex(ElemType &elem);      // 获取当前顶点信息在原图中的位置

    void ShowMarix( );      // 显示图的邻接矩阵信息

    void SetGraph(ElemType *vertexs, int edge);            // 修改图的顶点数和边数

    ElemType GetVertexElem(int vertex);                       // 求顶点的元素值

    bool SetElem(int vertex, const ElemType elem);      // 设置顶点的元素值

    int GetVertexCount( );               // 获取顶点的数目

    int GetEdgeCount( );                // 获取边的数目

    int FirstAdjVertex(int vertex);     // 获取顶点vertex的第一个邻接点

    int NextAdjVertex(int vertex1, int vertex2);    // 返回顶点vertex1相对于vertex2的下一个邻接点

    bool InsertEdge(int &vertex1, int &vertex2);            // 插入vertex1与vertex2的边

    bool DeleteEdge(int vertex1, int vertex2);          // 删除vertex1与vertex2的边

    bool GetVisited(int vertex);                         // 返回顶点vertex的访问标识信息

    void SetVisited(int vertex, bool isVisited);        // 设置顶点vertex的访问信息

    void DFSTraverse(void (*Visit)(ElemType &));      // 深度优先搜素

    void BFSTraverse(void (*Visit)(ElemType &));      // 广度优先搜素

    void DFSTraverse(int vertex, void (*Visit)(ElemType &));      // 深度优先搜素

    void BFSTraverse(int vertex, void (*Visit)(ElemType &));      // 广度优先搜素
    /*===========================【PUBLIC：公共接口】============================*/
///////////////////////////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////////
    /*=========================【PROTECTED：保护成员】===========================*/
protected ://summit, peak, apex, zenith, acme, vertex
    // 邻接表无向图类AdjListUndirGraphAdjListUndirGraph数据成员
    int m_vertexSize;                       // 顶点个数
    int m_edgeSize;                      // 边数
    AdjListGraphVertexNode<ElemType> *m_vertexTable;        // 顶点邻接表
    mutable bool *m_visited;              // 用于标识当前顶点是否被访问

    // 邻接矩阵无向图类AdjListUndirGraph辅助函数模版
    void DestroyGraph( );                // 销毁无向图, 释放无向图的空间

    void DFS(int vertex, void (* Visit)(ElemType &));     // 从顶点vertex出发进行深度优先搜索

    void BFS(int veretx, void (* Visit)(ElemType &));     // 从顶点vertex出发进行广度优先搜索
};



/**邻接表无向图类AdjListUndirGraphAdjListUndirGraph辅助函数模版[实现]***********************************
    void DestroyGraph( );                // 销毁无向图, 释放无向图的空间
    void BFS(int vertex, void (* Visit)(const ElemType &));     // 从顶点vertex出发进行深度优先搜索
    void DFS(int veretx, void (* Visit)(const ElemType &));     // 从顶点vertex出发进行广度优先搜索
***********************************[实现]邻接表无向图类AdjListUndirGraphAdjListUndirGraph辅助函数模版**/
//// 函数名称：void DestroyGraph( );
//// 操作结果：销毁无向图, 释放无向图的空间
//template <class ElemType>
//void AdjListUndirGraph<ElemType>::CreateGraph(int vertexNum)
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
void AdjListUndirGraph<ElemType>::DestroyGraph( )
{
#ifdef DEBUG    // 插桩调试信息
    std::cout <<"FUN:"<<__func__  <<", LINE:" <<__LINE__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现部分
    if(this->m_visited != NULL)
    {   // 删除访问标识域的空间
        delete[] this->m_visited;
    }
	for(int vex = 0; vex < this->m_vertexSize; vex++)       // 循环每个顶点
	{
		if(this->m_vertexTable[vex].m_adjLink != NULL)      // 如果当前顶点的邻接表信息的链表信息不为空
        {
            delete this->m_vertexTable[vex].m_adjLink;      // 删除其邻接表信息
        }
	}
}

// 函数名称：void DFS(int veretx, void (* Visit)(const ElemType &));
// 操作结果：从顶点vertex出发进行深度度优先搜索
template <class ElemType>
void AdjListUndirGraph<ElemType>::DFS(int vertex, void (* Visit)(ElemType &))     // 从顶点vertex出发进行深度优先搜索
{
#ifdef DEBUG    // 插桩调试信息
    std::cout <<"FUN:"<<__func__  <<", LINE:" <<__LINE__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现部分
    //this->SetVisited(vertex, VISITED);      // 将veretx访问标识标识为已访问
    /*上面代码等价于*/this->m_visited[vertex] = VISITED;

    //ElemType elem = this->GetVertexElem(vertex);        // 获取当前第vertex个顶点的顶点数据
    //std::cout <<this->m_vertexTable[vertex].m_data;
    (* Visit)(this->m_vertexTable[vertex].m_data);            // 用Visit函数当前顶点信息

    int vexTemp;
    for(vexTemp = this->FirstAdjVertex(vertex);    /*当前顶点的第一个邻接点开始搜索*/
            vexTemp != -1/*查询不到邻接点时会返回-1*/;
            vexTemp = this->NextAdjVertex(vertex, vexTemp))
    {
        //if(this->GetVisited() == UNVISITED) // 只要当前点还未被访问
        if(this->m_visited[vexTemp] == UNVISITED)
        {
            system("pause");
            DFS(vexTemp, Visit);        // 递归访问vexTemp
        }
    }
}


// 函数名称：void BFS(int veretx, void (* Visit)(const ElemType &));
// 操作结果：从顶点vertex出发进行广度优先搜索
template <class ElemType>
void AdjListUndirGraph<ElemType>::BFS(int vertex, void (* Visit)(ElemType &))     // 从顶点vertex出发进行广度优先搜索
{
#ifdef DEBUG    // 插桩调试信息
    std::cout <<"FUN:"<<__func__  <<", LINE:" <<__LINE__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现部分
    //this->SetVisited(vertex, VISITED);      // 将veretx访问标识标识为已访问
    /*上面代码等价于*/this->m_visited[vertex] = VISITED;

    //ElemType elem = this->GetVertexElem(vertex);        // 获取当前第vertex个顶点的顶点数据

    (* Visit)(this->m_vertexTable[vertex].m_data);            // 用Visit函数当前顶点信息


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

                (* Visit)(this->m_vertexTable[vertex].m_data);      // 访问当前顶点

                myQueue.push(vexTemp);            // 将当前顶点入队
            }
        }

    }
}

/**邻接表无向图类AdjListUndirGraphAdjListUndirGraph基本成员函数[实现]***********************************
    AdjListUndirGraph( );         // 默认构造函数模版
    AdjListUndirGraph(ElemType *vertex, int vexNum);  // 构造顶点数据为vertex, 顶点个数为vexNum的无向图
    AdjListUndirGraph(int vexNum);                    // 构造顶点个数为vexNum的无向图
    AdjListUndirGraph(const AdjListUndirGraph<ElemType> &copy); // 复制构造函数
    AdjListUndirGraph<ElemType>& operator=(const AdjListUndirGraph<ElemType> &copy);    // 重载赋值运算符函数
    ~AdjListUndirGraph( );                            // 析构函数
***********************************[实现]邻接表无向图类AdjListUndirGraphAdjListUndirGraph基本成员函数**/
// 函数名称：AdjListUndirGraph( );         // 默认构造函数模版
// 操作方法：构造顶点数据为vertex, 顶点个数为vexNum的无向图
template <class ElemType>
AdjListUndirGraph<ElemType>::AdjListUndirGraph( )         // 默认构造函数模版
{
    this->m_vertexSize = 0;
    this->m_edgeSize = 0;

    this->m_vertexTable = NULL;
    this->m_visited = 0;
}


// 函数名称：AdjListUndirGraph(ElemType *vertex, int vexNum);
// 操作方法：构造顶点数据为vertex, 顶点个数为vexNum的无向图
template <class ElemType>
AdjListUndirGraph<ElemType>::AdjListUndirGraph(ElemType *vertexs, int vertexNum)  // 构造顶点数据为vertex, 顶点个数为vexNum的无向图
{
#ifdef DEBUG    // 插桩调试信息
    std::cout <<"FUN:"<<__func__  <<", LINE:" <<__LINE__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现部分
	if(vertexNum < 0 || vertexs == NULL)       // 参数不合法
	{
	    throw std::out_of_range("参数不能为负\n");
	}

	this->m_vertexSize = vertexNum;		// 顶点数为vertexNum
	this->m_edgeSize = 0;				// 边数为0

	this->m_visited = new bool[vertexNum];      // 开辟访问信息标识数组

	int vex;									// 临时变量
	for(vex = 0; vex < this->m_vertexSize; vex++)       // 循环所有顶点
	{
		this->m_visited[vex] = UNVISITED;   // 每个顶点的访问信息设为未访问
	}

	this->m_vertexTable = new AdjListGraphVertexNode<ElemType>[this->m_vertexSize];    // 生成邻接表
	for (vex = 0; vex < this->m_vertexSize; vex++)      // 循环每个顶点
	{
		this->m_vertexTable[vex].m_data = vertexs[vex];     // 设置邻接表的数据域为顶点数据
	}
}

// 函数名称：AdjListUndirGraph(int vexNum);
// 操作方法：构造顶点个数为vexNum的无向图
template <class ElemType>
AdjListUndirGraph<ElemType>::AdjListUndirGraph(int vertexNum)                    // 构造顶点个数为vexNum的无向图
{
#ifdef DEBUG    // 插桩调试信息
    std::cout <<"FUN:"<<__func__  <<", LINE:" <<__LINE__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现部分
	if(vertexNum < 0)       // 参数不合法
	{
	    throw std::out_of_range("参数不能为负\n");
	}

	this->m_vertexSize = vertexNum;		// 顶点数为vertexNum
	this->m_edgeSize = 0;				// 边数为0

	this->m_visited = new bool[vertexNum];      // 开辟访问信息标识数组

	int vex;									// 临时变量
	for(vex = 0; vex < this->m_vertexSize; vex++)       // 循环所有顶点
	{
		this->m_visited[vex] = UNVISITED;   // 每个顶点的访问信息设为未访问
	}

	this->m_vertexTable = new AdjListGraphVertexNode<ElemType>[this->m_vertexSize];// 生成邻接表信息为空
}


// 函数名称：AdjListUndirGraph(const AdjListUndirGraph<ElemType> &copy);
// 操作结果：复制构造函数
template <class ElemType>
AdjListUndirGraph<ElemType>::AdjListUndirGraph(const AdjListUndirGraph<ElemType> &copy) // 复制构造函数
{
#ifdef DEBUG    // 插桩调试信息
    std::cout <<"FUN:"<<__func__  <<", LINE:" <<__LINE__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现部分
	this->m_vertexSize = copy.m_vertexSize;		// 顶点数为vertexNum
	this->m_edgeSize = copy.m_edgeSize;				// 边数为0

	this->m_visited = new bool[this->m_vertexSize];      // 开辟访问信息标识数组


	for(int vex = 0; vex < this->m_vertexSize; vex++)       // 循环所有顶点
	{
		this->m_visited[vex] = copy.m_visited[vex];   // 每个顶点的访问信息设为未访问
	}

	this->m_vertexTable = new AdjListGraphVertexNode<ElemType>[this->m_vertexSize];// 生成邻接表
	for (int vex = 0; vex < this->m_vertexSize; vex++)
	{	// 复制邻接链表
		//this->m_vertexSize[vex].m_data = copy.m_vertexSize[vex].m_data;	// 复制顶点数据
		//this->m_vertexSize[vex].m_adjLink = new LinkList<int>(*copy.m_vertexSize[vex].m_adjLink);
        this->m_vertexTable[vex] = copy.m_vertexTable[vex];
	}
}


// 函数名称：AdjListUndirGraph<ElemType>& operator=(const AdjListUndirGraph<ElemType> &copy);
// 操作结果：重载赋值运算符函数
template <class ElemType>
AdjListUndirGraph<ElemType>& AdjListUndirGraph<ElemType>::operator=(const AdjListUndirGraph<ElemType> &copy)    // 重载赋值运算符函数
{
#ifdef DEBUG    // 插桩调试信息
    std::cout <<"FUN:"<<__func__  <<", LINE:" <<__LINE__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现部分
    if(this == &copy)
    {
        return;
    }

	this->m_vertexSize = copy.m_vertexSize;		// 顶点数为vertexNum
	this->m_edgeSize = copy.m_edgeSize;				// 边数为0

	this->m_visited = new bool[this->m_vertexSize];      // 开辟访问信息标识数组

	for(int vex = 0; vex < this->m_vertexSize; vex++)       // 循环所有顶点
	{
		this->m_visited[vex] = copy.m_visited[vex];   // 每个顶点的访问信息设为未访问
	}

	this->m_vertexTable = new AdjListGraphVertexNode<ElemType>[this->m_vertexSize];// 生成邻接表
	for (int vex = 0; vex < this->m_vertexSize; vex++)
	{	// 复制邻接链表
		//this->m_vertexSize[vex].m_data = copy.m_vertexSize[vex].m_data;	// 复制顶点数据
		//this->m_vertexSize[vex].m_adjLink = new LinkList<int>(*copy.m_vertexSize[vex].m_adjLink);
        // 以上代码等价于[由于结点类中重载了赋值运算符]
        this->m_vertexTable[vex] = copy.m_vertexTable[vex];
	}

	return (*this);
}


// 函数名称：~AdjListUndirGraph( );
// 操作结果：析构函数
template <class ElemType>
AdjListUndirGraph<ElemType>::~AdjListUndirGraph( )                            // 析构函数
{
#ifdef DEBUG    // 插桩调试信息
    std::cout <<"FUN:"<<__func__  <<", LINE:" <<__LINE__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现部分
    this->DestroyGraph( );      // 调用信息销毁函数
}


/**邻接表无向图类AdjListUndirGraphAdjListUndirGraph特征成员函数[实现]***********************************
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
***********************************[实现]邻接表无向图类AdjListUndirGraphAdjListUndirGraph特征成员函数**/
//函数名称：int GetVertex(ElemType &elem);
//操作结果：获取当前顶点信息在原图中的位置
template <class ElemType>
int AdjListUndirGraph<ElemType>::GetVertex(ElemType &elem)      // 获取当前顶点信息在原图中的位置
{
    int vex;
    for(vex = 0; vex < this->m_vertexSize; vex++)
    {
        if(this->m_vertexTable[vex].m_data == elem)        // 如果当前邻接表的顶点点信息是需要查询的信息
        {
            return vex;         // 返回下标也就是当前顶点在图中位置
        }
    }

    return -1;          // 查找不到返回-1;
}

//函数名称：void Showtarix( );
//操作结果：显示图的邻接矩阵信息
template <class ElemType>
void AdjListUndirGraph<ElemType>::ShowMarix( )      // 显示图的邻接矩阵信息
{
   /* for(int i = 0; i < this->m_vertexSize; i++)
    {
        std::cout <<this->m_vertexTable[i].m_adjLink->Length( );
    }*/
    int vex, i, j, len;
    int matrix[this->m_vertexSize][this->m_vertexSize];

    memset(matrix, 0, sizeof(&matrix[0][0])*m_vertexSize*m_vertexSize);
    for(i = 0; i < this->m_vertexSize; i++)     // 循环每个顶点
    {
        len = this->m_vertexTable[i].m_adjLink->Length( );
        std::cout <<"len = " <<len <<std::endl;
        for(j = 1; j <= len; j++)
        {
          //  system("pause");
            vex = this->m_vertexTable[i].m_adjLink->GetElem(j);

            std::cout <<"i = " <<i <<"j = " <<j <<"取出元素" <<vex <<std::endl;
            matrix[i][vex] = 1;
        }
    }

    for(i = 0; i < m_vertexSize; i++)
    {
        for(j = 0; j < m_vertexSize; j++)
        {
            std::cout <<std::setw(4)<<matrix[i][j];
        }
        std::cout <<std::endl;
    }
}

//函数名称：bool SetGraph(int vertex, int edge);            // 修改图的顶点数和边数
//操作结果：修改图的顶点数和边数
template <class ElemType>
void AdjListUndirGraph<ElemType>::SetGraph(ElemType *vertexs, int vertexNum)            // 修改图的顶点数和边数
{
#ifdef DEBUG    // 插桩调试信息
    std::cout <<"FUN:"<<__func__  <<", LINE:" <<__LINE__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现部分
    if(vertexNum < 0 || vertexs == NULL)
    {
        throw std::out_of_range("参数不能为负数\n");
    }

    this->DestroyGraph( ); // 首先销毁原有的空间

    // 开始新的赋值
	this->m_vertexSize = vertexNum;		// 顶点数为vertexNum
	this->m_edgeSize = 0;				// 边数为0

	this->m_visited = new bool[vertexNum];      // 开辟访问信息标识数组

	int vex;									// 临时变量
	for(vex = 0; vex < this->m_vertexSize; vex++)       // 循环所有顶点
	{
		this->m_visited[vex] = UNVISITED;   // 每个顶点的访问信息设为未访问
	}

	this->m_vertexTable = new AdjListGraphVertexNode<ElemType>[this->m_vertexSize];    // 生成邻接表
	for (vex = 0; vex < this->m_vertexSize; vex++)      // 循环每个顶点
	{
		this->m_vertexTable[vex].m_data = vertexs[vex];     // 设置邻接表的数据域为顶点数据
	}
}


// 函数名称：ElemType GetElem(int vertex);
// 操作结果：求顶点的元素值
template <class ElemType>
ElemType AdjListUndirGraph<ElemType>::GetVertexElem(int vertex)                       // 求顶点的元素值
{
#ifdef DEBUG    // 插桩调试信息
    std::cout <<"FUN:"<<__func__  <<", LINE:" <<__LINE__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现部分
    if(vertex < 0 || vertex >= this->m_vertexSize)
    {
        throw std::out_of_range("参数不在正常的下标索引范围\n");
    }

    return this->m_vertexTable[vertex].m_data;
}

// 函数名称：bool SetElem(int vertex, const ElemType elem);
// 操作结果： 设置顶点的元素值
template <class ElemType>
bool AdjListUndirGraph<ElemType>::SetElem(int vertex, const ElemType elem)      // 设置顶点的元素值
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

    this->m_vertexTable[vertex].m_data = elem;
}


// 函数名称：int GetVertexCount( );
// 操作结果： 获取顶点的数目
template <class ElemType>
int AdjListUndirGraph<ElemType>::GetVertexCount( )               // 获取顶点的数目
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
int AdjListUndirGraph<ElemType>::GetEdgeCount( )                // 获取边的数目
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
int AdjListUndirGraph<ElemType>::FirstAdjVertex(int vertex)     // 获取顶点vertex的第一个邻接点
{
#ifdef DEBUG    // 插桩调试信息
    std::cout <<"FUN:"<<__func__  <<", LINE:" <<__LINE__ <<std::endl;   // 输出函数信息
#endif

    // 函数实现部分
    if(vertex < 0 || vertex >= this->m_vertexSize)
    {
        std:: out_of_range("查找不到当前小标的顶点信息\n");
    }

    if(this->m_vertexTable[vertex].m_adjLink == NULL)   // 如果当前顶点的邻接表信息为空
    {
        return -1;          // 返回-1
    }
    else
    {
        return this->m_vertexTable[vertex].m_adjLink->GetElem(1);
    }
}

// 函数名称：int NextAdjVertex(int vertex1, int vertex2);
// 操作结果： 返回顶点vertex1相对于vertex2的下一个邻接点
template <class ElemType>
int AdjListUndirGraph<ElemType>::NextAdjVertex(int vertex1, int vertex2)    // 返回顶点vertex1相对于vertex2的下一个邻接点
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

    if(this->m_vertexTable[vertex1].m_adjLink == NULL)   // 如果当前顶点的邻接表信息为空
    {
        return -1;          // 返回-1
    }

	int vex = m_vertexTable[vertex1].m_adjLink->FindElem(vertex2);		// 取出vertex2在vertex1邻接链表中的位置
	if(vex < this->m_vertexTable[vertex1].m_adjLink->Length( )) // 质押品当前元素还有后继
	{	// 即当前信息还有下一个邻接点
		return this->m_vertexTable[vertex1].m_adjLink->GetElem(vex + 1);
	}
	else
	{
		return -1;      // 不存在下一个邻接点
	}
}

// 函数名称：bool InsertEdge(int vertex1, int vertex2);
// 操作结果： 插入vertex1与vertex2的边
template <class ElemType>
bool AdjListUndirGraph<ElemType>::InsertEdge(int &vertex1, int &vertex2)            // 插入vertex1与vertex2的边
{
#ifdef DEBUG    // 插桩调试信息
    std::cout <<"FUN:"<<__func__  <<", LINE:" <<__LINE__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现部分
    if(vertex1 < 0 || vertex1 >= this->m_vertexSize)
    {
        throw std::out_of_range("第1个参数不在正常范围!");// 抛出异常
    }
    if(vertex2 < 0 || vertex2 >= this->m_vertexSize)
    {
        throw std::out_of_range("第2个参数不在正常范围!");// 抛出异常
    }
    //system("pause");
    if(vertex1 == vertex2)
    {
        throw std::out_of_range("两个参数不能等于!");				// 抛出异常
    }

    int vex;
	// 插入(vertex1, vertex2)的边信息
	if(this->m_vertexTable[vertex1].m_adjLink == NULL) // 如果当前顶点的链表信息为空, 则新建一个链表信息
	{
		this->m_vertexTable[vertex1].m_adjLink = new LinkList<int>;
	}

    vex = this->m_vertexTable[vertex1].m_adjLink->FindElem(vertex2);// 查找vertex2在顶点vertex1的邻接链表中的位置
	if(vex == -1)      // 如果不存在边(v1, v2)
	{
		this->m_vertexTable[vertex1].m_adjLink->Inlist(vertex2);				// 插入边
	  //  std::cout <<m_vertexTable[vertex1].m_data <<"  " <<m_vertexTable[vertex2].m_data <<std::endl;
	}
	else
	{
	    return false;
	   // std::cout <<"该边已经存在无需重复插入" <<std::endl;
	}


	// 插入(v2, v1)
	if(this->m_vertexTable[vertex2].m_adjLink == NULL) // 如果当前顶点的链表信息为空, 则新建一个链表信息
	{
		this->m_vertexTable[vertex2].m_adjLink = new LinkList<int>;
	}

	vex = this->m_vertexTable[vertex2].m_adjLink->FindElem(vertex1);// 查找vertex2在顶点vertex1的邻接链表中的位置

	if(vex == -1)      // 如果不存在边(v1, v2)
	{
		this->m_vertexTable[vertex2].m_adjLink->Inlist(vertex1);				// 插入边										// 边数自增1
	  //  std::cout <<m_vertexTable[vertex2].m_data <<"  " <<m_vertexTable[vertex1].m_data <<std::endl;
	}

    this->m_edgeSize++;											// 边数自增1

    return true;
}

// 函数名称：bool DeleteEdge(int vertex1, int vertex2);
// 操作结果： 删除vertex1与vertex2的边
template <class ElemType>
bool AdjListUndirGraph<ElemType>::DeleteEdge(int vertex1, int vertex2)          // 删除vertex1与vertex2的边
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


    int vex;
    vex = this->m_vertexTable[vertex1].m_adjLink->FindElem(vertex1);	// 取出v2在邻接链表中的位置
	if(vex != -1)   // 查找到vertex1的邻接表中存在与vertex2的边
	{
		this->m_vertexTable[vertex1].m_adjLink->Delete(vex+1);		// 删除<v1, v2>
	}
	else
	{
	    std::cout <<"当前边不在图中, 无法进行删除" <<std::endl;
	    return false;
	}

    vex = this->m_vertexTable[vertex2].m_adjLink->FindElem(vertex1);	// 取出v2在邻接链表中的位置
	if(vex != -1)   // 查找到vertex1的邻接表中存在与vertex2的边
	{
		this->m_vertexTable[vertex1].m_adjLink->Delete(vex+1);		// 删除<v1, v2>
	}

    this->m_edgeSize--;									// 边数自减1

    return true;
}


// 函数名称：bool GetVisited(int vertex);
// 操作结果： 返回顶点vertex的访问标识信息
template <class ElemType>
bool AdjListUndirGraph<ElemType>::GetVisited(int vertex)                        // 返回顶点vertex的访问标识信息
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
void AdjListUndirGraph<ElemType>::SetVisited(int vertex, bool isVisited)        // 设置顶点vertex的访问信息
{
#ifdef DEBUG    // 插桩调试信息
    std::cout <<"FUN:"<<__func__  <<", LINE:" <<__LINE__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现部分
    if (vertex < 0 || vertex >= this->m_vertexSize)
    {
        throw std::out_of_range("参数不在正常范围!");
    }

    this->m_visited[vertex] = VISITED;
}

// 函数名称：void DFSTraverse(void (*Visit)(const ElemType &));
// 操作结果：默认从第0个结点开始进行搜索, 深度优先搜素
template <class ElemType>
void AdjListUndirGraph<ElemType>::DFSTraverse(void (* Visit)(ElemType &))      // 深度优先搜素
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
void AdjListUndirGraph<ElemType>::DFSTraverse(int vertex, void (* Visit)(ElemType &))      // 深度优先搜素
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
void AdjListUndirGraph<ElemType>::BFSTraverse(void (*Visit)(ElemType &))      // 广度优先搜素
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
void AdjListUndirGraph<ElemType>::BFSTraverse(int vertex, void (*Visit)(ElemType &))      // 广度优先搜素
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


#endif // AdjListUndirGraph_H_INCLUDED
