/********************************************************************************
CopyRight  : 2012-2013, HerBinUnversity, GatieMe
File Name  : main.h
Description: 链式队列主函数源代码文件
Author     : Gatie_Me
Version    : Copyright 2012
Data_Time  : 20112-8-29 10:28:43
Content    : 数据结构与算法（C++）版书上源码
********************************************************************************/
#include <iostream>
#include <ctime>
#include <windows.h>
#include <cstdlib>
#include <cstdio>
#include <iomanip>
#include <fstream>

#include "LinkQueue.h"


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
    #ifdef DEBUG           // 如果宏定义了DEBUG, 执行一下语句
    cout <<"\t\tHello World*****************************************" <<endl;
    cout <<"\t\t**              Now Start Debug                   **" <<endl;
    cout <<"\t\t*****************************************Hello World" <<endl;
    #endif

    // 非调试状态下的输出信息
    #ifndef DEBUG                // 如果宏定义了DEBUG, 执行一下语句
    cout <<"\t\t**************************************************** " <<endl;
    cout <<"\t\t**               Test SqQueue Of                  **" <<endl;
    cout <<"\t\t****************************************************" <<endl;
    #endif

    Welcome( );         // 欢迎界面



    // 程序初始化部分
    char answer;
    int choice, length, temp;

    LinkQueue<int> queue;     // 建立一个顺序队

    Lording( );         // 载入函数
    while( 1 )
    {

        Menu( );        // 系统菜单

        cin >>choice;         // 输入您的选择

        system("cls");        // 确认自己的选择后清屏

        // 分支语句进行判断
        switch(choice)
        {
            /// 1 -=> 新建一整形线性表
          case 1:
            // 系统信息提示
            cout <<"\t\t******************************************" <<endl;
            cout <<"\t\t** 您当前的选择1 -=> 新建一整形顺序循环队列 **" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl <<endl;

            // 程序测试部分
            cout <<"请输入您希望建立的顺序队的队宽" <<endl;
            cout <<"输入后系统会建立一个顺序队数据随机" <<endl;
            cin >>length;       // 输入顺序队的数据

            srand(time(NULL));              // 设置随机数种子
            for(int i = 0; i < length; i++) // 将系统设置的数据压入队中
            {
                temp = rand() % 100 + 1;                    // 设置一个1-100的随机数
                queue.InQueue(temp);                           // 将数据压入队中
                cout <<"将数据" <<temp <<"压入队中" <<endl; // 提示信息
            }
            cout <<"当前链式循环队列的长度" <<queue.Length( ) <<endl;
            // 系统信息提示
            cout <<endl <<endl;
            cout <<"\t\t******************************************" <<endl;
            cout <<"\t\t**              数据入队完毕            **" <<endl;
            cout <<"\t\t**             即将返回主菜单           **" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl;
            cout <<"Please ent any key to continue........................" <<endl;
            system("pause");
            break;

          /// 2 -=> 显示建立的顺序循环队列
          case 2:
            // 系统提示信息
            cout <<"\t\t********************************************" <<endl;
            cout <<"\t\t** 您当前的选择2 -=> 依次弹出顺序队的数据 **" <<endl;
            cout <<"\t\t********************************************" <<endl <<endl <<endl;

            while(!queue.Empty())
            {
                cout <<"弹出的数据: " <<queue.OutQueue() <<endl;
            }
            cout <<"当前链式循环队列的长度" <<queue.Length( ) <<endl;

            // 系统提示信息
            cout <<"\t\t******************************************" <<endl;
            cout <<"\t\t**              数据入队完毕            **" <<endl;
            cout <<"\t\t**             即将返回主菜单           **" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl;
            cout <<"Please ent any key to continue........................" <<endl;
            system("pause");
            break;

          /// 3 -=> 元素入队
          case 3:

            // 系统提示信息
            system("cls");
            cout <<"\t\t******************************************" <<endl;
            cout <<"\t\t**      您当前的选择5 -=> 元素入队      **" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl <<endl;


            // 程序测试部分
            cout <<"由于这是队数据结构, 无法设置入队位置" <<endl <<endl;
            while( 1 )
            {
                cout <<endl <<endl <<"请输入您要入队的数据[输入0结束入队]" <<endl;
                cin >>temp;
                if(temp == 0)
                {
                    break;
                }
                queue.InQueue(temp);
                cout <<"将数据" <<temp <<"扎入队顶" <<endl;
            }
            // 系统提示信息
            cout <<"\t\t******************************************" <<endl;
            cout <<"\t\t**              数据入队完毕            **" <<endl;
            cout <<"\t\t**             即将返回主菜单           **" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl;
            cout <<"Please ent any key to continue........................" <<endl;
            system("pause");
            break;

          /// 4 -=> 元素出队
          case 4:
            // 系统提示信息
            system("cls");
            cout <<"\t\t******************************************" <<endl;
            cout <<"\t\t**      您当前的选择5 -=> 元素出队     **" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl <<endl;

            // 程序测试部分

            do
            {	// 循环直到用户输入恰当的回答为止
                cout <<endl <<endl <<"请问您是否确定需要弹出队顶数据" <<endl;
                cout << "(y, n)?" << "用y或n回答:";
                while ((answer = getchar( )) == '\n');	// 跳过空格,制表符及换行符获取一字符
                if(answer == 'y' || answer == 'Y')         // 只要队不是空的
                {
                    if(queue.OutQueue(temp) == true)     // 弹出队顶元素
                    {
                        cout <<"弹出队顶数据" <<temp <<endl;
                    }
                }
                else if(answer != 'n' && answer != 'N')
                {
                    cout <<"信息输入有误, 请重新输入" <<endl;
                }

                if(queue.Empty() == true)   // 如果当前顺序队为空, 则系统将自动返回主菜单
                {
                    cout <<"队列中元素全部出队, 无法继续出队" <<endl;
                    break;
                }
            }while (answer != 'n' && answer != 'N');

            // 系统提示信息
            cout <<"\t\t******************************************" <<endl;
            cout <<"\t\t**              数据出队完毕            **" <<endl;
            cout <<"\t\t**             即将返回主菜单           **" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl;
            cout <<"Please ent any key to continue........................" <<endl;
            system("pause");
            break;

          /// 5 -=> 清空顺序循环队列
          case 5:
            // 系统提示信息
            system("cls");
            cout <<"\t\t******************************************" <<endl;
            cout <<"\t\t**     您当前的选择6 -=> 清空顺序队     **" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl <<endl;

            // 程序测试部分
            queue.Clear( );         // 将顺序队清空
            cout <<"清空完毕, 当前顺序队长度" <<queue.Length() <<endl <<endl;
            // 系统提示信息
            cout <<"\t\t******************************************" <<endl;
            cout <<"\t\t**              队列清空完毕            **" <<endl;
            cout <<"\t\t**             即将返回主菜单           **" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl;
            cout <<"Please ent any key to continue........................" <<endl;
            system("pause");
            break;

          /// 0 -=> 退出程序
          case 0:
            // 系统提示信息
            cout <<"\t\t******************************************" <<endl;
            cout <<"\t\t**              玩家选择结束            **" <<endl;
            cout <<"\t\t**           系统正在做返回处理         **" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl;
            cout <<"Please ent any key to continue........................" <<endl;          // 系统提示信息

            Stop( );

            Lording( );         // 载入函数
        }
    }

    return 0;
}

