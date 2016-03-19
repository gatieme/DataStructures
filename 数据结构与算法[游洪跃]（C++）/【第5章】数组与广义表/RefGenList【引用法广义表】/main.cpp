/**
*********************************************************************************
*   CopyRight  : 2012-2013, HerBinUnversity, GatieMe                            *
*   File Name  : main.cpp                                                       *
*   Description: RefGenList[引用法广义表]主函数文件                            *
*   Author     : Gatie_Me                                                       *
*   Version    : Copyright 2012                                                 *
*   Data_Time  : 20112-10-30 18:43:34                                           *
*   Content    : 数据结构与算法（C++）版书上源码                               *
*********************************************************************************
**/


#include <iostream>
#include <ctime>
#include <windows.h>
#include <cstdlib>
#include <cstdio>
#include <iomanip>
#include <fstream>


#include "RefGenList.h"


using namespace std;

#define SIZE 81



/// 外部函数（所在文件Other.cpp）
void Welcome( );        // 欢迎函数
void Menu( );       // 菜单显示函数
void Delay( );      // 延时函数
void Lording( );    // 载入函数
void Stop( );       // 终止函数


/// 主函数
int main( )
{
    // 调试状态下的输出信息
    #ifdef DEBUG           // 如果宏定义了DEBUG, 执行一下语句
    cout <<"\t\tHello World*****************************************" <<endl;
    cout <<"\t\t**              Now Start Debug                   **" <<endl;
    cout <<"\t\t*****************************************Hello World" <<endl;
    #endif

    // 非调试状态下的输出信息
    #ifndef DEBUG        // 如果宏定义了DEBUG, 执行一下语句
    cout <<"\t\t**************************************************** " <<endl;
    cout <<"\t\t**           Test TriSparseMatrix Of              **" <<endl;
    cout <<"\t\t****************************************************" <<endl;
    #endif

    Welcome( );         // 欢迎界面

    // 程序初始化部分
    int choice;
    Lording( );         // 载入函数

    while( 1 )
    {

        Menu( );        // 系统菜单

        cin >>choice;         //输入您的选择
        system("cls");
        switch(choice)
        {
          /// 1 -=> 建立稀疏矩阵
          case 1:
            // 系统信息提示
            cout <<"\t\t******************************************" <<endl;
            cout <<"\t\t**   您当前的选择 1 -=> 建立稀疏矩阵    **" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl <<endl;

            // 程序测试部分

            // 系统信息提示
            cout <<"\t\t******************************************" <<endl;
            cout <<"\t\t**              矩阵建立完毕            **" <<endl;
            cout <<"\t\t**             即将返回主菜单           **" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl;
            cout <<"Please ent any key to continue........................" <<endl;
            //getchar( );
            system("pause");
            break;

          /// 2 -=> 从文件读取稀疏矩阵
          case 2:
            // 系统提示信息
            system("cls");
            cout <<"\t\t********************************************" <<endl;
            cout <<"\t\t**  您当前的选择2 -=> 从文件读取稀疏矩阵  **" <<endl;
            cout <<"\t\t********************************************" <<endl <<endl <<endl;

            // 程序测试部分

            // 系统提示信息
            cout <<"\t\t********************************************" <<endl;
            cout <<"\t\t**              矩阵读入完毕              **" <<endl;
            cout <<"\t\t**             即将返回主菜单             **" <<endl;
            cout <<"\t\t********************************************" <<endl <<endl;
            cout <<"Please ent any key to continue........................" <<endl;
            system("pause");
            break;

          /// 3 -=> 输出稀疏矩阵
          case 3:
            // 系统提示信息
            cout <<"\t\t******************************************" <<endl;
            cout <<"\t\t**   您当前的选择 3 -=> 输出稀疏矩阵    **" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl <<endl;


            // 系统提示信息
            cout <<"\t\t******************************************" <<endl;
            cout <<"\t\t**              矩阵输出完毕            **" <<endl;
            cout <<"\t\t**             即将返回主菜单           **" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl;
            cout <<"Please ent any key to continue........................" <<endl;
            system("pause");
            break;

          /// 4 -=> 更改矩阵数据
          case 4:
            // 系统提示信息
            system("cls");
            cout <<"\t\t******************************************" <<endl;
            cout <<"\t\t**    您当前的选择4 -=> 更改矩阵数据    **" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl <<endl;

            // 程序测试部分


            // 系统提示信息
            cout <<"\t\t******************************************" <<endl;
            cout <<"\t\t**              数据更改完毕            **" <<endl;
            cout <<"\t\t**             即将返回主菜单           **" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl;
            cout <<"Please ent any key to continue........................" <<endl;
            system("pause");
            break;



          /// 5 -=> 将稀疏矩阵的数据存入文件
          case 5:
            // 系统提示信息
            system("cls");
            cout <<"\t\t******************************************" <<endl;
            cout <<"\t\t**您当前的选择 5 -=> 将稀疏矩阵存入文件 **" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl <<endl;


            // 程序测试部分

            // 系统提示信息
            cout <<"\t\t******************************************" <<endl;
            cout <<"\t\t**              数据存储完毕            **" <<endl;
            cout <<"\t\t**             即将返回主菜单           **" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl;
            cout <<"Please ent any key to continue........................" <<endl;
            system("pause");
            break;

          /// 6 -=> 将稀疏矩阵转置
          case 6:
            // 系统提示信息
            system("cls");
            cout <<"\t\t******************************************" <<endl;
            cout <<"\t\t**   您当前的选择 6 -=> 将稀疏矩阵转置  **" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl <<endl;

            // 程序测试部分

            // 系统提示信息
            cout <<"\t\t******************************************" <<endl;
            cout <<"\t\t**              矩阵转置完毕            **" <<endl;
            cout <<"\t\t**             即将返回主菜单           **" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl;
            cout <<"Please ent any key to continue........................" <<endl;
            system("pause");
            break;

          /// 7 -=> 矩阵的运算
          case 7:
            // 系统提示信息
            system("cls");
            cout <<"\t\t******************************************" <<endl;
            cout <<"\t\t**     您当前的选择 7 -=> 矩阵的运算    **" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl <<endl;

            // 程序测试部分

            // 系统提示信息
            cout <<"\t\t******************************************" <<endl;
            cout <<"\t\t**              矩阵运算完毕            **" <<endl;
            cout <<"\t\t**             即将返回主菜单           **" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl;
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


