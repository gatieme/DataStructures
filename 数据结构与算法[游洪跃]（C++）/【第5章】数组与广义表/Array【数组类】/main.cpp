/**
*******************************************************************************
*   CopyRight  : 2012-2013, HerBinUnversity, GatieMe                          *
*   File Name  : main.cpp                                                     *
*   Description: 数组的类模版main.cpp                                        *
*   Author     : Gatie_Me                                                     *
*   Version    : Copyright 2012                                               *
*   Data_Time  : 25/10/12 17:20                                          *
*   Content    : 数据结构与算法（C++）版书上源码                             *
*******************************************************************************
**/
#include <iostream>
#include <ctime>
#include <windows.h>
#include <cstdlib>
#include <cstdio>
#include <iomanip>

#include "Array.h"
using namespace std;

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
    #if defined DEBUG           // 如果宏定义了DEBUG, 执行一下语句
    cout <<"\t\tHello World*****************************************" <<endl;
    cout <<"\t\t**              Now Start Debug                   **" <<endl;
    cout <<"\t\t*****************************************Hello World" <<endl;
    #endif

    // 非调试状态下的输出信息
    #ifndef DEBUG                // 如果宏定义了DEBUG, 执行一下语句
    cout <<"\t\t**************************************************** " <<endl;
    cout <<"\t\t**            Test SimpleLinkList Of              **" <<endl;
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
            /// 1 -=> 新建一整形线性表
          case 1:
            // 系统信息提示
            cout <<"\t\t******************************************" <<endl;
            cout <<"\t\t** 您当前的选择1 -=> 新建一整形线性链表 **" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl <<endl;

            // 程序测试部分

            // 系统信息提示
            cout <<"\t\t******************************************" <<endl;
            cout <<"\t\t**              数据插入完毕            **" <<endl;
            cout <<"\t\t**             即将返回主菜单           **" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl;
            cout <<"Please ent any key to continue........................" <<endl;
            //getchar( );
            system("pause");
            break;

          /// 2 -=> 显示建立的线性链表
          case 2:
            // 系统提示信息
            cout <<"\t\t******************************************" <<endl;
            cout <<"\t\t** 您当前的选择2 -=> 显示建立的线性链表 **" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl <<endl;



            // 系统提示信息
            cout <<"\t\t******************************************" <<endl;
            cout <<"\t\t**              数据插入完毕            **" <<endl;
            cout <<"\t\t**             即将返回主菜单           **" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl;
            cout <<"Please ent any key to continue........................" <<endl;
            system("pause");
            break;

          case 3:
            // 系统提示信息
            system("cls");
            cout <<"\t\t******************************************" <<endl;
            cout <<"\t\t**  您当前的选择3 -=> 排序建立的线性表  **" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl <<endl;

            // 程序测试部分


            // 系统提示信息
            cout <<"\t\t******************************************" <<endl;
            cout <<"\t\t**              数据插入完毕            **" <<endl;
            cout <<"\t\t**             即将返回主菜单           **" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl;
            cout <<"Please ent any key to continue........................" <<endl;
            system("pause");
            break;

          /// 4 -=> 将线性表分成奇偶两部分
          case 4:
            // 系统提示信息
            system("cls");
            cout <<"\t\t********************************************" <<endl;
            cout <<"\t\t**您当前的选择4 -=> 将线性表分成奇偶两部分**" <<endl;
            cout <<"\t\t********************************************" <<endl <<endl <<endl;

            // 程序测试部分

            // 系统提示信息
            cout <<"\t\t********************************************" <<endl;
            cout <<"\t\t**              数据插入完毕              **" <<endl;
            cout <<"\t\t**             即将返回主菜单             **" <<endl;
            cout <<"\t\t********************************************" <<endl <<endl;
            cout <<"Please ent any key to continue........................" <<endl;
            system("pause");
            break;

          /// 5 -=> 添加元素
          case 5:
            // 系统提示信息
            system("cls");
            cout <<"\t\t******************************************" <<endl;
            cout <<"\t\t**      您当前的选择5 -=> 添加元素      **" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl <<endl;


            // 程序测试部分

            // 系统提示信息
            cout <<"\t\t******************************************" <<endl;
            cout <<"\t\t**              数据插入完毕            **" <<endl;
            cout <<"\t\t**             即将返回主菜单           **" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl;
            cout <<"Please ent any key to continue........................" <<endl;
            system("pause");
            break;

          /// 6 -=> 删除元素
          case 6:
            // 系统提示信息
            system("cls");
            cout <<"\t\t******************************************" <<endl;
            cout <<"\t\t**      您当前的选择6 -=> 删除元素      **" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl <<endl;

            // 程序测试部分

            // 系统提示信息
            cout <<"\t\t******************************************" <<endl;
            cout <<"\t\t**              数据插入完毕            **" <<endl;
            cout <<"\t\t**             即将返回主菜单           **" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl;
            cout <<"Please ent any key to continue........................" <<endl;
            system("pause");
            break;

          /// 7 -=> 清空线性链表
          case 7:
            // 系统提示信息
            system("cls");
            cout <<"\t\t******************************************" <<endl;
            cout <<"\t\t**     您当前的选择7 -=> 清空线性表     **" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl <<endl;

            // 程序测试部分

            // 系统提示信息
            cout <<"\t\t******************************************" <<endl;
            cout <<"\t\t**              数据插入完毕            **" <<endl;
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
