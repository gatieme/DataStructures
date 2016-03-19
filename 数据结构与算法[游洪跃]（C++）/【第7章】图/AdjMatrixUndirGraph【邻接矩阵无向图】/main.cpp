/**
******************************************************************************
*  CopyRight  : 2012-2013, HerBinUnversity, GatieMe                          *
*  File Name  : main.cpp                                                     *
*  Description: 邻接矩阵无向图类AdjMatrixUndirGraph主函数源文件                               *
*  Author     : Gatie_Me                                                     *
*  Version    : Copyright 2012 JULY_CITY                                     *
*  Data_Time  : 2012-11-6_10:21:43                                           *
*  Content    : 数据结构与算法（C++）版书上源码                             *
******************************************************************************
**/


#include <iostream>
#include <fstream>
#include <ctime>
#include <windows.h>
#include <cstdlib>
#include <cstdio>
#include <iomanip>
#include <algorithm>

#include "AdjMatrixUndirGraph.h"

#ifdef DEBUG
#undef DEBUG
//#define DEBUG
#endif

using namespace std;

/// 外部函数（所在文件Other.cpp）
void Read(char &);
void Write(const char &);
void Welcome( );        // 欢迎函数
void Menu( );       // 菜单显示函数
void Delay( );      // 延时函数
void Lording( );    // 载入函数
void Stop( );       // 终止函数



// 内部函数(main.cpp)
// 建立一个邻接矩阵无向图
void CreateGraph(AdjMatrixUndirGraph<char> &graph);
// 修改图的信息
void InsertGraph(AdjMatrixUndirGraph<char> &graph);
void DeleteGraph(AdjMatrixUndirGraph<char> &graph);
// 遍历图的信息
void Travel(AdjMatrixUndirGraph<char> &graph);


/// 主函数
int main( )
{
    system("title 哈夫曼树");     // 调用系统命令更改DOS窗口名称

    // 调试状态下的输出信息
#ifdef DEBUG           // 如果宏定义了DEBUG, 执行一下语句
    cout <<"\t\tHello World*****************************************" <<endl;
    cout <<"\t\t**              Now Start Debug                   **" <<endl;
    cout <<"\t\t*****************************************Hello World" <<endl;
#else
    cout <<"\t\t****************************************************" <<endl;
    cout <<"\t\t**             Test HufffmanTree Of               **" <<endl;
    cout <<"\t\t****************************************************" <<endl;
#endif

    Welcome( );         // 欢迎界面

    // 程序初始化部分
    int choice;
    AdjMatrixUndirGraph<char> graph;
    Lording( );         // 载入函数

    while( 1 )
    {

        Menu( );        // 系统菜单

        cin >>choice;         //输入您的选择
        system("cls");
        switch(choice)
        {
            /// 1 -=> 新建一整形线性表
        case 1:
            // 系统信息提示
            cout <<"\t\t******************************************" <<endl;
            cout <<"\t\t** 您当前的选择1 -=> 新建邻接矩阵无向图 **" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl <<endl;


            // 程序测试部分
            cout <<"程序将从文件中读入图的信息, 为你建立一个无向图" <<endl;
            cout <<"输入文件MatrixGraph.txt" <<endl;
            CreateGraph(graph);

            // 系统信息提示
            cout <<"\t\t******************************************" <<endl;
            cout <<"\t\t**              数据插入完毕            **" <<endl;
            cout <<"\t\t**             即将返回主菜单           **" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl;
            cout <<"Please ent any key to continue........................" <<endl;
            //getchar( );
            system("pause");
            break;

            /// 2 -=> 输出无向图的邻接矩阵信息
        case 2:
            // 系统提示信息
            system("cls");
            cout <<"\t\t********************************************" <<endl;
            cout <<"\t\t**您当前的选择2-=>输出无向图的邻接矩阵信息**" <<endl;
            cout <<"\t\t********************************************" <<endl <<endl <<endl;

            // 程序测试部分
            graph.ShowMarix( );

            // 系统提示信息
            cout <<"\t\t********************************************" <<endl;
            cout <<"\t\t**              数据插入完毕              **" <<endl;
            cout <<"\t\t**             即将返回主菜单             **" <<endl;
            cout <<"\t\t********************************************" <<endl <<endl;
            cout <<"Please ent any key to continue........................" <<endl;
            system("pause");
            break;

            /// 3 -=> 增加无向图的边
        case 3:
            // 系统提示信息
            system("cls");
            cout <<"\t\t******************************************" <<endl;
            cout <<"\t\t**   您当前的选择3 -=> 增加无向图的边   **" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl <<endl;

            // 程序测试部分
            InsertGraph(graph);

            // 系统提示信息
            cout <<"\t\t******************************************" <<endl;
            cout <<"\t\t**              数据插入完毕            **" <<endl;
            cout <<"\t\t**             即将返回主菜单           **" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl;
            cout <<"Please ent any key to continue........................" <<endl;
            system("pause");
            break;

            /// 4 -=> 删除五向图的边
        case 4:
            // 系统提示信息
            system("cls");
            cout <<"\t\t******************************************" <<endl;
            cout <<"\t\t**   您当前的选择4 -=> 删除五向图的边   **" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl <<endl;


            // 程序测试部分
            DeleteGraph(graph);


            // 系统提示信息
            cout <<"\t\t******************************************" <<endl;
            cout <<"\t\t**              数据插入完毕            **" <<endl;
            cout <<"\t\t**             即将返回主菜单           **" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl;
            cout <<"Please ent any key to continue........................" <<endl;
            system("pause");
            break;



            /// 5 -=>进行图的遍历搜索
        case 5:
            // 系统提示信息
            system("cls");
            cout <<"\t\t********************************************" <<endl;
            cout <<"\t\t**   您当前的选择5 -=>进行图的遍历搜索    **" <<endl;
            cout <<"\t\t********************************************" <<endl <<endl <<endl;

            // 程序测试部分
           // graph.DFSTraverse(Write);
            Travel(graph);

            // 系统提示信息
            cout <<"\t\t********************************************" <<endl;
            cout <<"\t\t**              数据插入完毕              **" <<endl;
            cout <<"\t\t**             即将返回主菜单             **" <<endl;
            cout <<"\t\t********************************************" <<endl <<endl;
            cout <<"Please ent any key to continue........................" <<endl;
            system("pause");
            break;

            /// 0 -=> 退出程序
        case 0:
            // 系统提示信息
            cout <<"\t\t******************************************" <<endl;
            cout <<"\t\t**              数据插入完毕            **" <<endl;
            cout <<"\t\t**             即将返回主菜单           **" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl;
            cout <<"Please ent any key to continue........................" <<endl;          // 系统提示信息

            Stop( );

            Lording( );         // 载入函数
        }
    }

    return 0;
}




// 建立一个邻接矩阵无向图
void CreateGraph(AdjMatrixUndirGraph<char> &graph)
{
    int vertexNum, temp;
    char *vertexs;
    fstream cin("MatrixGraph.txt");
    cin >>vertexNum/*顶点数目*/;
    cout <<"当前图的顶点数目" <<vertexNum <<endl;
    //char vertexs[vertexNum];
    vertexs = new char[vertexNum];  // 开辟结点信息
//   int matrix[vertexNum][vertexNum];


    cout <<"图的边信息" <<endl;
    for(int i = 0; i < vertexNum; i++)
    {
        cin >>vertexs[i];       // 输入顶点信息
        // cout <<setw(5)<<vertexs[i];
    }
    cout <<endl;
    // 图的顶点为ertexs, 边信息为edgeNum

    graph.SetGraph(vertexs, vertexNum);      // 修改图的信息);

    for(int i = 0; i < vertexNum; i++)
    {
        for(int j = 0; j < vertexNum; j++)
        {
            cin >>temp;
            cout <<setw(4)<<temp;
            if(temp == 1)
            {
                graph.InsertEdge(i, j);
            }
        }
        cout <<endl;
    }

//    for(int i = 0; i < vertexNum; i++)
//    {
//        for(int j = 0; j < vertexNum; j++)
//        {
//            cin >>matrix[i][j];
//            cout <<setw(4)<<matrix[i][j];
//        }
//        cout <<endl;
//    }
//
//    for(int i = 0; i < vertexNum; i++)
//    {
//        for(int j = 0; j <= i; j++)
//        {
//            if(matrix[i][j] == 1)
//            {
//                graph.InsertEdge(i, j);
//            }
//        }
//    }
}


// 修改图的信息
void InsertGraph(AdjMatrixUndirGraph<char> &graph)
{
    char vertex1, vertex2;
    int v1, v2;
    cout <<"请输入您要添加的边两个顶点的信息" <<endl;
    cout <<"任何一个输入, 结束输入" <<endl;

    while( 1 )
    {
        while( 1 )
        {
            cout <<"VERTEX:";
            cin >>vertex1 >>vertex2;
            if(vertex1 == '#' || vertex2 == '#')
            {
                break;
            }
            //cout <<vertex1 <<vertex2 <<endl;
            //system("pause");
            v1 = graph.GetVertex(vertex1);
            v2 = graph.GetVertex(vertex2);
            //system("pause");
            // cout <<v1 <<v2 <<endl;
            if(v1 != -1 && v2 != -1)
            {
                break;
            }

            cout <<"输入的顶点信息有误, 请重新输入" <<endl;
        }

        if(vertex1 == '#' || vertex2 == '#')
        {
            cout <<"用户终止输入" <<endl;
            break;
        }

        if(graph.InsertEdge(v1, v2) == true)
        {
            cout <<"添加顶点" <<vertex1 <<"与顶点" <<vertex2 <<"的边信息" <<endl <<endl <<endl;
        }
        else
        {
            cout <<"无向图中该边已经存在, 无需再添加" <<endl;
        }
    }
}



void DeleteGraph(AdjMatrixUndirGraph<char> &graph)
{
    char vertex1, vertex2;
    int v1, v2;
    cout <<"请输入您要删除的边两个顶点的信息" <<endl;
    cout <<"任何一个输入, 结束输入" <<endl;

    while( 1 )
    {
        while( 1 )
        {
            cout <<"VERTEX:";
            cin >>vertex1 >>vertex2;
            if(vertex1 == '#' || vertex2 == '#')
            {
                break;
            }
            //cout <<vertex1 <<vertex2 <<endl;
            //system("pause");
            v1 = graph.GetVertex(vertex1);
            v2 = graph.GetVertex(vertex2);
            //system("pause");
            // cout <<v1 <<v2 <<endl;
            if(v1 != -1 && v2 != -1)
            {
                break;
            }

            cout <<"输入的顶点信息有误, 请重新输入" <<endl;
        }

        if(vertex1 == '#' || vertex2 == '#')
        {
            cout <<"用户终止输入" <<endl;
            break;
        }


        if(graph.DeleteEdge(v1, v2) == true)
        {
            cout <<"删除顶点" <<vertex1 <<"与顶点" <<vertex2 <<"的边信息" <<endl <<endl <<endl;
        }
        else
        {
            cout <<"无向图中该边本就不存在, 无需再删除" <<endl;
        }
    }
}


// 遍历图的信息
void Travel(AdjMatrixUndirGraph<char> &graph)
{
    cout <<"************************" <<endl;
    cout <<"** 1 -=> 深度搜索算法 **" <<endl;
    cout <<"** 2 -=> 广度搜索算法 **" <<endl;
    cout <<"************************" <<endl;

    int choice, vex;
    //char vertex;

    cin >>choice;

    switch(choice)
    {
//      case 1:
//        while( 1 )
//        {
//            cout <<"请选择您要开始搜索的顶点" <<endl;
//            cin >>vertex;
//            if((vex = graph.GetVertex(vertex)) != -1)
//            {
//                break;
//            }
//            else
//            {
//                cout <<"输入的结点有误, 请重新输入" <<endl;
//            }
//        }
//        graph.DFSTraverse(vex, Write);
//        // 如果向直接从从默认顶点开始访问,
//        // 则可直接用函数graph.DFSTraverse(Write);
//        // 也可以graph.DFSTraverse(0, Write);
//        cout <<endl;
//        break;
//      case 2:
//        while( 1 )
//        {
//            cout <<"请选择您要开始搜索的顶点" <<endl;
//            cin >>vertex;
//            if((vex = graph.GetVertex(vertex)) != -1)
//            {
//                break;
//            }
//            else
//            {
//                cout <<"输入的结点有误, 请重新输入" <<endl;
//            }
//        }
//        graph.BFSTraverse(vertex, Write);
//        break;
        case 1:
          cout <<"当前深度优先搜索DFS" <<endl <<endl;
          for(vex = 0; vex < graph.GetVertexCount(); vex++)
          {

              cout <<"从第" <<vex+1 <<"个顶点" <<graph.GetVertexElem(vex)<<"开始访问" <<endl;
              cout <<"DFS结果为：";
              graph.DFSTraverse(vex, Write);        // 进行访问
              cout <<endl <<endl;
          }
          break;
        case 2:
          cout <<"当前广度优先搜索BFS" <<endl <<endl;
          for(vex = 0; vex < graph.GetVertexCount(); vex++)
          {

              cout <<"从第" <<vex+1 <<"个顶点" <<graph.GetVertexElem(vex)<<"开始访问" <<endl;
              cout <<"BFS结果为：";
              graph.BFSTraverse(vex, Write);        // 进行访问
              cout <<endl <<endl;
          }
          break;
    }
}

