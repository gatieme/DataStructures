/********************************************************************************
CopyRight  : 2012-2013, HerBinUnversity, GatieMe
File Name  : SqList.h
Description: 顺序栈主函数源代码文件
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

#include "LinkStack.h"
using namespace std;

/// 外部函数（所在文件Other.cpp）
void Welcome( );        // 欢迎函数
void Menu( );       // 菜单显示函数
void Delay( );      // 延时函数
void Lording( );    // 载入函数
void Stop( );       // 终止函数

/// 内部函数（所在文件当前文件main.cpp）
void MatchFile( );          // 初始括号匹配的文件函数
bool Match(char *s);        // 括号匹配

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
    char answer;
    int choice, length, temp;

    LinkStack<int> stack;     // 建立一个顺序栈

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
            cout <<"\t\t** 您当前的选择1 -=> 新建一整形线性链表 **" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl <<endl;

            // 程序测试部分
            cout <<"请输入您希望建立的顺序栈的栈宽" <<endl;
            cout <<"输入后系统会建立一个顺序栈数据随机" <<endl;
            cin >>length;       // 输入顺序栈的数据

            srand(time(NULL));              // 设置随机数种子
            for(int i = 0; i < length; i++) // 将系统设置的数据压入栈中
            {
                temp = rand() % 100 + 1;                    // 设置一个1-100的随机数
                stack.Push(temp);                           // 将数据压入栈中
                cout <<"将数据" <<temp <<"压入栈中" <<endl; // 提示信息
            }

            // 系统信息提示
            cout <<endl <<endl;
            cout <<"\t\t******************************************" <<endl;
            cout <<"\t\t**              数据插入完毕            **" <<endl;
            cout <<"\t\t**             即将返回主菜单           **" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl;
            cout <<"Please ent any key to continue........................" <<endl;
            system("pause");
            break;

          /// 2 -=> 显示建立的线性链表
          case 2:
            // 系统提示信息
            cout <<"\t\t********************************************" <<endl;
            cout <<"\t\t** 您当前的选择2 -=> 依次弹出顺序栈的数据 **" <<endl;
            cout <<"\t\t********************************************" <<endl <<endl <<endl;

            while(!stack.Empty())
            {
                cout <<"弹出的数据: "<<stack.Pop() <<endl;
            }

            // 系统提示信息
            cout <<"\t\t******************************************" <<endl;
            cout <<"\t\t**              数据插入完毕            **" <<endl;
            cout <<"\t\t**             即将返回主菜单           **" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl;
            cout <<"Please ent any key to continue........................" <<endl;
            system("pause");
            break;

          /// 3 -=> 括号匹配检查
          case 3:
            // 系统提示信息
            system("cls");
            cout <<"\t\t******************************************" <<endl;
            cout <<"\t\t**    您当前的选择3 -=> 括号匹配检查    **" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl <<endl;

            // 程序测试部分

            MatchFile( );
            // 系统提示信息
            cout <<"\t\t******************************************" <<endl;
            cout <<"\t\t**            括号检查进行完毕          **" <<endl;
            cout <<"\t\t**             即将返回主菜单           **" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl;
            cout <<"Please ent any key to continue........................" <<endl;
            system("pause");
            break;

          /// 4 -=> 元素入栈
          case 4:

            // 系统提示信息
            system("cls");
            cout <<"\t\t******************************************" <<endl;
            cout <<"\t\t**      您当前的选择5 -=> 元素入栈      **" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl <<endl;


            // 程序测试部分
            cout <<"由于这是栈数据结构, 无法设置插入位置" <<endl <<endl;
            while( 1 )
            {
                cout <<"请输入您要插入的数据[输入0结束插入]" <<endl;
                cin >>temp;
                if(temp == 0)
                {
                    break;
                }
                stack.Push(temp);
                cout <<"将数据" <<temp <<"扎入栈顶" <<endl;
            }
            // 系统提示信息
            cout <<"\t\t******************************************" <<endl;
            cout <<"\t\t**              数据添加完毕            **" <<endl;
            cout <<"\t\t**             即将返回主菜单           **" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl;
            cout <<"Please ent any key to continue........................" <<endl;
            system("pause");
            break;

          /// 5 -=> 元素出栈
          case 5:
            // 系统提示信息
            system("cls");
            cout <<"\t\t******************************************" <<endl;
            cout <<"\t\t**      您当前的选择5 -=> 元素出栈     **" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl <<endl;

            // 程序测试部分

            do
            {	// 循环直到用户输入恰当的回答为止
                cout <<"请问您是否确定需要弹出栈顶数据" <<endl;
                cout << "(y, n)?" << "用y或n回答:";
                while ((answer = getchar( )) == '\n');	// 跳过空格,制表符及换行符获取一字符
                if(answer == 'y' || answer == 'Y')         // 只要栈不是空的
                {
                    if(stack.Pop(temp) == true)     // 弹出栈顶元素
                    {
                        cout <<"弹出栈顶数据" <<temp <<endl;
                    }
                }
                else if(answer != 'n' && answer != 'N')
                {
                    cout <<"信息输入有误, 请重新输入" <<endl;
                }

                if(stack.Empty() == true)   // 如果当前顺序栈为空, 则系统将自动返回主菜单
                {
                    break;
                }
            }while (answer != 'n' && answer != 'N');

            // 系统提示信息
            cout <<"\t\t******************************************" <<endl;
            cout <<"\t\t**              数据出栈完毕            **" <<endl;
            cout <<"\t\t**             即将返回主菜单           **" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl;
            cout <<"Please ent any key to continue........................" <<endl;
            system("pause");
            break;

          /// 6 -=> 清空线性链表
          case 6:
            // 系统提示信息
            system("cls");
            cout <<"\t\t******************************************" <<endl;
            cout <<"\t\t**     您当前的选择6 -=> 清空顺序栈     **" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl <<endl;

            // 程序测试部分
            stack.Clear( );         // 将顺序栈清空
            cout <<"清空完毕, 当前顺序栈长度" <<stack.Length() <<endl <<endl;
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



// 检查括号是否匹配
void MatchFile( )
{
    char str[100], fName[] = "StackInput.txt";                 // 临时字符
    ifstream fpi;                  // 输入文件

    fpi.open(fName, ios::binary);     // 打开输入文件
    if(fpi.fail() == true)  exit(1);        // 打开文件失败关闭程序
    while( 1 )
    {
        fpi.getline(str, 1000);     // 读入一个字符串

        cout <<"当前需要判断的字符串\"" <<str <<"\""<<endl;     // 输出信息提示

        if(Match(str) == true)
        {
            cout <<"当前括号是匹配的" <<endl;
        }
        else
        {
            cout <<"当前括号不匹配" <<endl;
        }
        if(fpi.fail() == true || strcmp(str, "") == 0)
        {
            break;      // 遇见文件末尾的时候停止
        }
    }

}

// 检查括号是否匹配
bool Match(char *str)
{
    LinkStack<char> strStack;     // 字符串栈
    char tempCh;                // 临时字符

    for(int i = 0; str[i] != '\0'; i++)
    {
       /* switch(str[i])
        {
          //将括号中第一个括号入栈
          case '(':            // 如果遇见的字符是(
          case '[':             // 如果遇见的字符是[
          case '{':             // 如果遇见的字符是{
            strStack.Push(str[i]);  break;      // 就将字符压入栈中

          // 检查()是否匹配
          case ')':     // 检查当前的()是否匹配
            if(strStack.Empty())    // 如果是个空栈, 则括号坑定不匹配
            {
                return false;
            }
            else if(strStack.Top(tempCh), tempCh == ')')     // 如果当前这对括号匹配
            {
                strStack.Pop(tempCh);           // 将已经匹配的括号弹出
            }
            else
            {
                return false;
            }

            break;

          // 检查[]括号是否匹配
          case ']':
            if(strStack.Empty())    // 如果是个空栈, 则括号坑定不匹配
            {
                return false;
            }
            else if(strStack.Top(tempCh), tempCh == ']')     // 如果当前这对括号匹配
            {
                strStack.Pop(tempCh);           // 将已经匹配的括号弹出
            }
            else
            {
                return false;
            }

            break;

          // 检查{ }是否匹配
          case '}':
            if(strStack.Empty())    // 如果是个空栈, 则括号坑定不匹配
            {
                return false;
            }
            else if(strStack.Top(tempCh), tempCh == '}')     // 如果当前这对括号匹配
            {
                strStack.Pop(tempCh);           // 将已经匹配的括号弹出
            }
            else
            {
                return false;
            }
        }*/
        if(str[i] == '(' || str[i] == '[' || str[i] == '{')     //将括号中第一个括号入栈
        {
            strStack.Push(str[i]);    // 就将字符压入栈中
        }
        else if(str[i] == ')')  // 检查()是否匹配// 检查当前的()是否匹配
        {
            if(strStack.Empty())    // 如果是个空栈, 则括号坑定不匹配
            {
                return false;
            }
            else if(strStack.Top(tempCh), tempCh == '(')     // 如果当前这对括号匹配
            {
                strStack.Pop(tempCh);           // 将已经匹配的括号弹出
            }
            else
            {
                return false;
            }
        }
        else if(str[i] == ']')  // 检查[]括号是否匹配
        {
            if(strStack.Empty())    // 如果是个空栈, 则括号坑定不匹配
            {
                return false;
            }
            else if(strStack.Top(tempCh), tempCh == '[')     // 如果当前这对括号匹配
            {
                strStack.Pop(tempCh);           // 将已经匹配的括号弹出
            }
            else
            {
                return false;
            }
        }
        else if(str[i] == '}')
        {
            if(strStack.Empty())    // 如果是个空栈, 则括号坑定不匹配
            {
                return false;
            }
            else if(strStack.Top(tempCh), tempCh == '{')     // 如果当前这对括号匹配
            {
                strStack.Pop(tempCh);           // 将已经匹配的括号弹出
            }
            else
            {
                return false;
            }
        }
    }

    if(strStack.Empty())        // 检查是否匹配
    {
        return true;
    }
    else
    {
        return false;
    }
}



