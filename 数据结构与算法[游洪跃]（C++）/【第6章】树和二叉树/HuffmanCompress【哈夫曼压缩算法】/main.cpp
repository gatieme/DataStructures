/**
******************************************************************************
*  CopyRight  : 2012-2013, HerBinUnversity, GatieMe                          *
*  File Name  : main.cpp                                                     *
*  Description: 二叉树链表BinTree主函数源文件                               *
*  Author     : Gatie_Me                                                     *
*  Version    : Copyright 2012 JULY_CITY                                     *
*  Data_Time  : 2012-11-6_10:21:43                                           *
*  Content    : 数据结构与算法（C++）版书上源码                             *
******************************************************************************
**/
/*
终端读入字符集及其相应的频度，建立哈夫曼树；
显示各字符的哈夫曼编码
利用已建成的哈夫曼树进行编码；
给定一串二进制编码，可以利用哈夫曼树进行译码
*/

#include <iostream>
#include <ctime>
#include <windows.h>
#include <cstdlib>
#include <cstdio>
#include <iomanip>
#include <algorithm>



#include "HuffmanCompress.h"

#ifdef DEBUG
#undef DEBUG
//#define DEBUG
#endif

using namespace std;

/// 外部函数（所在文件Other.cpp）
void Welcome( );        // 欢迎函数
void Menu( );       // 菜单显示函数
void Delay( );      // 延时函数
void Lording( );    // 载入函数
void Stop( );       // 终止函数



// 内部函数(main.cpp)


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
    HuffmanCompress huffman;

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
            cout <<"\t\t**      您当前的选择1 -=> 压缩文件      **" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl <<endl;


            // 程序测试部分
            huffman.EnCompress( );

            // 系统信息提示
            cout <<"\t\t******************************************" <<endl;
            cout <<"\t\t**              数据插入完毕            **" <<endl;
            cout <<"\t\t**             即将返回主菜单           **" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl;
            cout <<"Please ent any key to continue........................" <<endl;
            //getchar( );
            system("pause");
            break;



            /// 打印字符编码信息
        case 2:
            // 系统提示信息
            system("cls");
            cout <<"\t\t******************************************" <<endl;
            cout <<"\t\t**     您当前的选择2 -=> 解压缩文件     **" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl <<endl;

            // 程序测试部分
            huffman.UnCompress( );

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



