// 文件路径名: park_dragoman\park_dragoman.h
#ifndef __PARK_DRAGOMAN_H__
#define __PARK_DRAGOMAN_H__

#include "adj_list_undir_network.h"			// 无向网的邻接表类
#include "lk_stack.h"						// 链栈
#include "string.h"							// 串类

// 公园导游类
class ParkDragoman
{
private:
// 公园导游类的数据成员:
	AdjListUndirNetwork<String, double> *pNet;	// 由公园信息所建立的网 
	ifstream *pInFile;						// 输入流 
	int maxNumOfShowPath;					// 最多显示路线条数
	double **dist;							// 各对顶点u和v之间的最短路径长度dist[u][v]
	int **path;								// 各对顶点u和v之间的最短路径path[u][v]
	
// 辅助函数:
	int LocateVex(const String &e);			// 返回顶点元素在网中的位置
	void Readln();							// 跳过一行  
	void ShowTourismPath(int tourismPath[]);// 输出游览线路
	void CreateTourismPath(int to, int v, int tourismPath[], int pathVertexNum); 
		// tourismPath为游览路径, 出口为to, v为当前当前顶点, pathVertexNum为路径当前顶点数
	void ShortestPathFloyd();				// 用Floyd算法求有向网net中各对顶点的最短路径

public:
// 抽象数据类型方法声明及重载编译系统默认方法声明:
	ParkDragoman(ifstream *pIFile);			// 构造函数
	virtual ~ParkDragoman();				// 析构函数
	void Run();								// 公园导游
};

// 重载串输入/输出运算符
ostream &operator <<(ostream &outStream, const String &outStr);
	// 重载运算符<<
istream &operator >>(istream &inStream, String &inStr);
	// 重载运算符>>

// 公园导游类及相关函数的实现部分
int ParkDragoman::LocateVex(const String &e)
// 操作结果：返回顶点在网中的位置
{
	for (int v = 0; v < pNet->GetVexNum(); v++)
	{	// 依次查找课程
		String strTmp;						// 临时变量
		pNet->GetElem(v, strTmp);			// 返回顶点信息
		if (strTmp == e)
		{	// 查找成功
			return v;						// 非负表示查找成功
		}
	}
	
	return -1;								// -1表示查找失败
}

void ParkDragoman::Readln()
// 操作结果：跳过一行
{	
	char ch;								// 字符
	while ((ch = (*pInFile).peek()) != EOF	// 不为文件结束符
		&& (ch = (*pInFile).get()) != '\n');// 不为换行符
}
 
void ParkDragoman::ShowTourismPath(int tourismPath[])
// 操作结果：输出游览线路
{
	int pos;								// 临时变量

	cout << "线路:";
	cout << "入口 ";						// 入口			
	String e;								// 路径上顶点元素值
	for (pos = 1; pos < pNet->GetVexNum() - 1; pos++)
	{	// 输出路径上的中间顶点元素值
		pNet->GetElem(tourismPath[pos], e);	// 取出顶点元素值
		cout << e << " ";					// 输出路径上的中间点
	}
	cout << "出口" << endl;					// 出口
	
	double pathLength = 0;					// 线路长度
	for (pos = 1; pos < pNet->GetVexNum(); pos++)
	{	// 将每条边的长度求和
		pathLength = pathLength + pNet->GetWeight(tourismPath[pos - 1], tourismPath[pos]);
	}
	cout << "长度:" << pathLength << endl << endl;
}

void ParkDragoman::CreateTourismPath(int to, int v, int tourismPath[], int pathVertexNum) 
// 初始条件: tourismPath为游览路径, 出口为to, v为当前当前顶点, pathVertexNum为路径当前顶点数
// 操作结果: 生成并输出游览路径
{
	static int n = 0;						// 已输出的游览线路个数
	
	for (int w = pNet->FirstAdjVex(v); w >= 0; w = pNet->NextAdjVex(v, w))
	{	// 对v的所有邻接点进行循环
		if (n == maxNumOfShowPath)
		{	// 已输出最多显示路线数
			break;							// 退出循环
		}
		else if (pNet->GetTag(w) == UNVISITED && pathVertexNum == pNet->GetVexNum() - 1 && 
			w == to && n < maxNumOfShowPath)
		{	// 得到一条游览线路
			++n;							// 已输出的游览线路个数自加1
			tourismPath[pathVertexNum++] = w;	// 将w加入到游览线路中
			ShowTourismPath(tourismPath);	// 输出游览线路
		}
		else if	(pNet->GetTag(w) == UNVISITED)
		{	// w未被访问过
			tourismPath[pathVertexNum++] = w;	// 将w加入到游览线路中
			pNet->SetTag(w, VISITED);		// 置访问标志为VISITED
			CreateTourismPath(to, w, tourismPath, pathVertexNum);	
				// 将w作为新的当前结点建立游览线路
			pathVertexNum--;				// 恢复路径顶点个数，回溯
			pNet->SetTag(w, UNVISITED);		// 重置访问标志为UNVISITED,以便回溯
		}
	}
}

void ParkDragoman::ShortestPathFloyd()
// 操作结果: 用Floyd算法求有向网net中各对顶点u和v之间的最短路径path[u][v]和路径长度
//	dist[u][v],path[u][v]存储从u到v的最短路径上至此顶点的前一顶点的顶点号,dist[u][v]
//	存储从u到v的最短路径的长度
{
	for (int u = 0; u < pNet->GetVexNum(); u++)
		for (int v = 0; v < pNet->GetVexNum(); v++)
		{	// 初始化path和dist
			dist[u][v] = (u != v && pNet->GetWeight(u, v) == 0 ) ? pNet->GetInfinity() : pNet->GetWeight(u, v);
			if (u != v && dist[u][v] < pNet->GetInfinity()) path[u][v] = u;	// 存在边(u,v)
			else path[u][v] = -1;											// 不存在边(u,v)
		}

	for (int k = 0; k < pNet->GetVexNum(); k++)
		for (int i = 0; i < pNet->GetVexNum(); i++)
			for (int j = 0; j < pNet->GetVexNum(); j++)
				if (dist[i][k] + dist[k][j] < dist[i][j])
				{	// 从i到k再到j的路径长度更短
					dist[i][j] = dist[i][k] + dist[k][j]; 
					path[i][j] = path[k][j];
				}
}

ParkDragoman::ParkDragoman(ifstream *pIFile)
// 操作结果: 由输入文件建立表示公园信息的网
{
	pInFile = pIFile;						// 输入文件
	char ch;								// 临时变量

	// 从输入流中输入景点数, 景点数"n="后面
	(*pInFile).seekg(0);					// 定位到文件开始处
	ch = GetChar(*pInFile);					// 读字符
	while (ch != 'n')
	{	// 查找以'n'开始的行
		if (ch != '\n') Readln();			// 跳行
		ch = GetChar(*pInFile);				// 读入字符
	}
	GetChar(*pInFile);						// 跳过"="
	int n;									// 景点数
	*pInFile >> n;							// 读入景点数

	String *es = new String[n + 2];			// 网顶点元素, 包括景点与出/入口
	// 从输入流中输入景点名称, 景点数在"v="后面, 假设景点名不含空格，不同景点名之
	// 间用空格分隔
	(*pInFile).seekg(0);					// 定位到文件开始处
	ch = GetChar(*pInFile);					// 读字符
	while (ch != 'v')
	{	// 查找以'v开始的行
		if (ch != '\n') Readln();			// 跳行
		ch = GetChar(*pInFile);				// 读入字符
	}
	ch=GetChar(*pInFile);					// 跳过"="
	int i;									// 临时变量
	for (i = 0; i < n; i++)
	{	// 读入景点名称
		*pInFile >> es[i];					// 从输入流*pInFile中输入景点名称
	}
	es[n] = "入口";							// 入口
	es[n + 1] = "出口";						// 出口

	// 从输入流中输入最多显示路线条数, 最后显示路线条数在"s="后面 
	(*pInFile).seekg(0);					// 定位到文件开始处
	ch = GetChar(*pInFile);					// 读字符
	while (ch != 's')
	{	// 查找以's'开始的行
		if (ch != '\n') Readln();			// 跳行
		ch = GetChar(*pInFile);				// 读入字符
	}
	GetChar(*pInFile);						// 跳过"="
	*pInFile >> maxNumOfShowPath;			// 读入最多显示路线条数

	pNet = new AdjListUndirNetwork<String, double>(es, n + 2);
		// 生成网

	// 从输入流中输入边信息
	(*pInFile).seekg(0);					// 定位到文件开始处
	ch = GetChar(*pInFile);					// 读字符
	while (true)
	{	// 文件未结束
		while (ch != '(' && ch != EOF)
		{	// 查找以'('开始的行或输入流已结束
			if (ch != '\n') Readln();		// 跳行
			ch = GetChar(*pInFile);			// 读入字符
		}
		if (ch == EOF) break;				// 输入流已结束
		String e1, e2;				 		// 边顶点元素
		int v1, v2;							// 边顶点
		double w;							// 权值
		(*pInFile) >> e1 >> e2 >> w;		// 读入顶点元素及权值
		if ((v1 = LocateVex(e1)) == -1) throw Error("边顶点元素错!");// 抛出异常
		if ((v2 = LocateVex(e2)) == -1) throw Error("边顶点元素错!");// 抛出异常
		pNet->InsertEdge(v1, v2, w);		// 插入边
		ch = GetChar(*pInFile);				// 读入字符
	}

	dist = new double *[pNet->GetVexNum()], path = new int *[pNet->GetVexNum()];
		// 分配存储空间
	for (i = 0; i < pNet->GetVexNum(); i++)
	{	// 对二维数组的每一行分配存储空间
		dist[i] = new double[pNet->GetVexNum()]; path[i] = new int[pNet->GetVexNum()]; 
	}
	ShortestPathFloyd();					// 用Floyd算法求无向网net中各对顶点u和v之间的最短路径
}

void ParkDragoman::Run()
// 操作结果: 公园导游
{
	LinkStack<int> s;						// 存储路上的顶点
	String e1, e2, e;						// 顶点元素
	int v1, v2, v;							// 顶点号
	int *tourismPath = new int[pNet->GetVexNum()];	 // 游览线路
	int pathVertexNum;						// 路径当前顶点数
	int from = LocateVex("入口");			// 入口顶点号
	int to = LocateVex("出口");				// 出口顶点号
	char select;							// 临时变量

	do 
	{
		cout << "1.最短路径" << endl;
		cout << "2.游览线路" << endl;
		cout << "3.退出" << endl;
		cin >> select;						// 输入选项
		while (cin.get() != '\n');			// 跳过此行后面的字符(也就是换行)

		switch (select)
		{
		case '1':
			cout << "起点:";
			cin >> e1;						// 起点 
			cout << "终点:";
			cin >> e2;						// 终点 
			if ((v1 = LocateVex(e1)) == -1)  throw Error("顶点元素错!");// 抛出异常
			if ((v2 = LocateVex(e2)) == -1)  throw Error("顶点元素错!");// 抛出异常
			cout << "最短路径长度为:" << dist[v1][v2] << endl;	// 输出路径长度
			cout << "最短路径:";
			s.Clear();						// 清空s
			v = v2;							// 路径上当前顶点
			while (v != v1)
			{	// 从终点回溯到起点
				s.Push(v);					// v为路径上的顶点
				v = path[v1][v];			// 取上路径上的前一个顶点
			}

			s.Push(v1);						// v是路径上起始点
			while (!s.Empty())
			{	// 输出路上的顶点
				s.Pop(v);					// 路径上顶点出栈
				pNet->GetElem(v, e);		// 取出顶点元素
				cout << e << " ";			// 输出顶点元素
			}
			cout << endl << endl;			// 换行
			break;
		case '2':
			pathVertexNum = 0;				// 路径当前顶点数
			tourismPath[pathVertexNum++] = from;//路径起点
			v = from;						// from为路径上当前顶点
			cout << "游览线路及长度:" << endl;
			CreateTourismPath(to, v, tourismPath, pathVertexNum);	// 生成并输出游览线路
			break;
		}
	} while (select != '3');
	delete []tourismPath;					// 释放存储空间
}

ParkDragoman::~ParkDragoman()
// 操作结果: 释放存储空间 
{

	if (pNet != NULL) delete pNet;			// 释放pNet
	for (int i = 0; i < pNet->GetVexNum(); i++)
	{	// 释放二维数组的第j行
		if (dist != NULL && dist[i] != NULL) delete []dist[i]; 
		if (path != NULL && path[i] != NULL) delete []path[i]; 
	}
	if (dist != NULL) delete []dist;		// 释放dist
	if (path != NULL) delete []path;		// 释放path
}

ostream &operator <<(ostream &outStream, const String &outStr)
// 操作结果：重载运算符<<
{
	outStream << outStr.CStr();				// 输出串值
	return outStream;						// 返回输出流对象
}

istream &operator >>(istream &inStream, String &inStr)
// 操作结果：重载运算符>>
{
	LinkList<char> temp;					// 临时线性表
	int size = 0;							// 初始线性表长度
	char ch= GetChar(inStream);				// 从输入流inStream中跳过空格及制表符获取一字符
	inStream.putback(ch);					// 将ch回送输入流
	while ((ch = inStream.peek()) != EOF &&	// peek()从输入流中取一个字符
											// 输入流指针不变
		(ch = inStream.get()) != '\n'		// get()从输入流中取一个字符ch
											// 输入流指针指向下一字符,ch不为换行符
		&& ch != '\t' && ch != ' ')			// ch也不为制表符与空格	
	{	// 将输入的字符追加到线性表中
		temp.Insert(++size, ch);
	}
	String answer(temp);					// 构造串
	inStr = answer;							// 用inStr返回串
	return inStream;						// 返回输入流对象
}

#endif
