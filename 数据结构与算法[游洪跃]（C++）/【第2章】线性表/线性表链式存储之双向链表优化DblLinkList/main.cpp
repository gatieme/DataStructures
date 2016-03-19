/********************************************************************************
CopyRight  : 2012-2013, HerBinUnversity, GatieMe
File Name  : SqList.h
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

#include "DblLinkList.h"
using namespace std;

//#define DEBUG                     // 如果进行调试请将此注释打开
#define VERSION  1                  // 如果不想显示版本以及编译信息请将该宏定义置为0
#define REMIND                    // 如果想输出提醒信息, 请将次注释打开

/// 外部函数（所在文件Other.cpp）
void Welcome( );        // 欢迎函数
void Menu( );       // 菜单显示函数
void Delay( );      // 延时函数
void Lording( );    // 载入函数
void Stop( );       // 终止函数

///// 内部函数
//template <class ElemType>
//void Display(const DblLinkList<ElemType> &list)    // 显示函数
//


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
    cout <<"\t\t**            Test DblLinkList Of              **" <<endl;
    cout <<"\t\t****************************************************" <<endl;
    #endif

    Welcome( );         // 欢迎界面

    // 程序初始化部分
    int choice, length, temp, position;
    int leftPosition, rightPosition, leftItem, rightItem;                // 分支选择信息
    DblLinkList<int> list;       // 新建一个线性链表序列

    Lording( );         // 载入函数

    while( 1 )
    {

        Menu( );        // 系统菜单

        cin >>choice;         //输入您的选择
        switch(choice)
        {
            /// 1 -=> 新建一整形线性表
          case 1:
            system("cls");
            // 系统信息提示
            cout <<"******************************************" <<endl;
            cout <<"** 您当前的选择1 -=> 新建一整形线性链表 **" <<endl;
            cout <<"******************************************" <<endl <<endl <<endl;

            // 信息输入
            cout <<"系统将新建一个线性链表, 并插入一些随机数据" <<endl <<endl;
            cout <<"请输入当前线性链表的表长" <<endl <<"length = ";     // 输入信息学提示
            cin >>length;                           // 输入数据

            // DblLinkList测试信息
            srand(time(NULL));          // 设置随机数种子
            for(int i = 1; i <= length; i++)
            {
                temp = rand() %100 + 1;             // 设置一个1-100的随机数
                list.Inlist(temp);     // 直接将设置的随机元素temp插入线性链表的末尾
                //list.Insert(i, temp);       //也可以将设置的随机数, 插入当前线性链表的第i个位置

                // 输出提示信息
              //  #if define REMIND                    // 如果定义了REMIND宏, 将编译如下信息
                cout <<"将数据" <<temp <<"插在线性链表的第" <<i <<"个位置" <<endl <<endl;     // 提示信息
              //  #endif              // 宏编译结束

            }

            // 系统信息提示
            cout <<"数据插入完毕" <<endl <<endl;
            cout <<"即将返回主菜单" <<endl <<endl;
            cout <<"Please ent any key to continue" <<endl;
            //getchar( );
            system("pause");
            break;

          /// 2 -=> 显示建立的线性链表
          case 2:
            // 系统提示信息
            system("cls");
            cout <<"******************************************" <<endl;
            cout <<"** 您当前的选择2 -=> 显示建立的线性链表 **" <<endl;
            cout <<"******************************************" <<endl <<endl <<endl;

            // 输出线性表中的数据


            // DblLinkList测试信息
            length = list.Length( );

            cout <<"当前线性链表中有" <<length <<"个数据" <<endl;
            cout <<"依次取出并且输出线性表中的每个数" <<endl;
            for(int i = 1; i <= length; i++)
            {
               // system("pause");
                if(list.GetElem(i, temp) == true)      // 取出线性链表的第i个元素, 并将取出的数据存在变量temp中
                {
                    cout <<setw(4)<<temp;
                }
                else
                {
                    cout <<"取出数据失败" <<endl;
                }
            }
            cout <<endl <<endl;     // 执行换行信息

            // 系统提示信息
            cout <<"数据输出完毕" <<endl <<endl;
            cout <<"即将返回主菜单" <<endl <<endl;
            cout <<"Please ent any key to continue" <<endl;
            system("pause");
            break;

          case 3:
            // 系统提示信息
            system("cls");
            cout <<"****************************************" <<endl;
            cout <<"** 您当前的选择3 -=> 排序建立的线性表 **" <<endl;
            cout <<"****************************************" <<endl <<endl <<endl;

            // 程序测试部分
            // 插入前的输出
            cout <<"当前线性链表中的数据为:" <<endl;
            for(int i = 1; i <= length; i++)
            {
               // system("pause");
                if(list.GetElem(i, temp) == true)      // 取出线性链表的第i个元素, 并将取出的数据存在变量temp中
                {
                    cout <<setw(4)<<temp;
                }
                else
                {
                    cout <<"取出数据失败" <<endl;
                }
            }
            cout <<endl <<endl;     // 执行换行信息

            cout <<"排序后的数据元素为：" <<endl;
            if((list.SelectSort( ) == true) && (list.BubbleSort() == true))
            {
                cout <<"从小到大排序后的结果为：" <<endl;
                for(int i = 1; i <= length; i++)
                {
                // system("pause");
                    if(list.GetElem(i, temp) == true)      // 取出线性链表的第i个元素, 并将取出的数据存在变量temp中
                    {
                        cout <<setw(4)<<temp;
                    }
                    else
                    {
                        cout <<"取出数据失败" <<endl;
                    }
                }
                cout <<endl <<endl;     // 执行换行信息
            }

            // 系统提示信息
            cout <<"数据排序完毕" <<endl <<endl;
            cout <<"即将返回主菜单" <<endl <<endl;
            cout <<"Please ent any key to continue" <<endl;
            system("pause");
            break;

          /// 4 -=> 将线性表分成奇偶两部分
          case 4:
            // 系统提示信息
            system("cls");
            cout <<"**********************************************" <<endl;
            cout <<"** 您当前的选择4 -=> 将线性表分成奇偶两部分 **" <<endl;
            cout <<"**********************************************" <<endl <<endl <<endl;

            cout <<"当前线性链表中的原有数据的顺序为:" <<endl;
            for(int i = 1; i <= length; i++)
            {
               // system("pause");
                if(list.GetElem(i, temp) == true)      // 取出线性链表的第i个元素, 并将取出的数据存在变量temp中
                {
                    cout <<setw(4)<<temp;
                }
                else
                {
                    cout <<"取出数据失败" <<endl;
                }
            }
            cout <<endl <<endl;     // 执行换行信息

            leftPosition = 1;
            rightPosition = list.Length( );
            while(leftPosition < rightPosition)
            {
                list.GetElem(leftPosition, leftItem);   //取出list左边的数据leftItem
                list.GetElem(rightPosition, rightItem); //取出list右边的数据rightItem

                if(leftItem % 2 == 1)   //如果左边的数leftItem是奇数
                {
                    leftPosition++;    //符合结果要求, 于是将leftPosition右移到下一个数
                    //cout <<leftItem <<"  " <<rightItem <<"右移A"<<endl;
                }
                else if(rightItem % 2 == 0)   //如果右边的数rightItem是偶数
                {
                    rightPosition--;    //符合结果要求, 于是将rightPosition前移到上一个数
                   // cout <<leftItem <<"  " <<rightItem <<"左移B"<<endl;
                }
                else //如果list左边的数leftItem为偶数, 且右边的数rightItem为奇数
                {   //这种情况不满足结果要求需要 -=> 将两个数交换
                   // list.SetElem(leftPosition++, rightItem);
                    //list.SetElem(rightPosition--, leftItem);
                    list.Swap(leftPosition++, rightPosition--);
                    //cout <<leftItem <<"  " <<rightItem <<"交换C"<<endl;
                //    if(leftPosition == rightPosition)  break;
                }
            }

            cout <<"分离后的顺序为：" <<endl;
            for(int i = 1; i <= length; i++)
            {
               // system("pause");
                if(list.GetElem(i, temp) == true)      // 取出线性链表的第i个元素, 并将取出的数据存在变量temp中
                {
                    cout <<setw(4)<<temp;
                }
                else
                {
                    cout <<"取出数据失败" <<endl;
                }
            }
            cout <<endl <<endl;     // 执行换行信息

            // 系统提示信息
            cout <<"数据分割完毕" <<endl <<endl;
            cout <<"即将返回主菜单" <<endl <<endl;
            cout <<"Please ent any key to continue" <<endl;
            system("pause");
            break;

          /// 5 -=> 添加元素
          case 5:
            // 系统提示信息
            system("cls");
            cout <<"************************************" <<endl;
            cout <<"**   您当前的选择5 -=> 添加元素   **" <<endl;
            cout <<"*************************************" <<endl <<endl <<endl;


            // 程序测试部分
            length = list.Length( );
            // 插入前的输出
            cout <<"当前线性链表中的数据为:" <<endl;
            for(int i = 1; i <= length; i++)
            {
               // system("pause");
                if(list.GetElem(i, temp) == true)      // 取出线性链表的第i个元素, 并将取出的数据存在变量temp中
                {
                    cout <<setw(4)<<temp;
                }
                else
                {
                    cout <<"取出数据失败" <<endl;
                }
            }
            cout <<endl <<endl;     // 执行换行信息
            while( 1 )
            {
                cout <<"添加线性链表的元素[输入0 0结束添加]" <<endl;
                cout <<"请问您要添加出第几个元素和想要添加的数据" <<endl;
                cin >>position >>temp;
                if(position == 0 && temp == 0 )
                {
                    break;
                }

                if(list.Insert(position, temp) == true)
                {
                    length++;
                    cout <<"被添加的元素" <<temp <<"当前线性链表中共计" <<length <<"个元素" <<endl;
                    cout <<"添加元素后, 当前线性表的信息如下" <<endl;
                }

                for(int i = 1; i <= length; i++)
                {
                    list.GetElem(i, temp);
                    cout <<setw(4)<<temp;
                }
                cout <<endl <<endl;
            }

            // 系统提示信息
            cout <<"数据添加完毕" <<endl <<endl;
            cout <<"即将返回主菜单" <<endl <<endl;
            cout <<"Please ent any key to continue" <<endl;
            system("pause");
            break;

          /// 6 -=> 删除元素
          case 6:
            // 系统提示信息
            system("cls");
            cout <<"************************************" <<endl;
            cout <<"**   您当前的选择6 -=> 删除元素   **" <<endl;
            cout <<"*************************************" <<endl <<endl <<endl;

            // 程序测试部分
            length = list.Length( );
            // 删除前的输出
            cout <<"当前线性链表中的数据为:" <<endl;
            for(int i = 1; i <= length; i++)
            {
               // system("pause");
                if(list.GetElem(i, temp) == true)      // 取出线性链表的第i个元素, 并将取出的数据存在变量temp中
                {
                    cout <<setw(4)<<temp;
                }
                else
                {
                    cout <<"取出数据失败" <<endl;
                }
            }
            cout <<endl <<endl;     // 执行换行信息
            while( 1 )
            {
                cout <<"删除线性表的元素[输入0结束删除]" <<endl;
                cout <<"请问您要删除出第几个元素" <<endl;
                cin >>position;
                if(position == 0)       // 输入0时结束删除操作
                {
                    break;
                }

                if(list.Delete(position, temp) == true)
                {
                    length--;
                    cout <<"被删除的元素" <<temp <<", 当前线性链表中还剩下" <<length <<"个元素" <<endl;
                    cout <<"删除掉元素后, 当前线性表的信息如下" <<endl;
                }
                else
                {
                    cout <<"插入失败...." <<endl;           // 提示信息
                }

                // 输出当前的元素信息
                for(int i = 1; i <= length; i++)
                {
                    list.GetElem(i, temp);
                    cout <<setw(4)<<temp;
                }
                cout <<endl <<endl;
            }

            // 系统提示信息
            cout <<"数据删除完毕" <<endl <<endl;
            cout <<"即将返回主菜单" <<endl <<endl;
            cout <<"Please ent any key to continue" <<endl;
            system("pause");
            break;

          /// 7 -=> 清空线性链表
          case 7:
            // 系统提示信息
            system("cls");
            cout <<"**************************************" <<endl;
            cout <<"**   您当前的选择7 -=> 清空线性表   **" <<endl;
            cout <<"**************************************" <<endl <<endl <<endl;

            cout <<"线性表中原有数据" <<endl;
            length = list.Length( );
            // 删除前的输出
            cout <<"当前线性链表中的数据为:" <<endl;
            for(int i = 1; i <= length; i++)
            {
               // system("pause");
                if(list.GetElem(i, temp) == true)      // 取出线性链表的第i个元素, 并将取出的数据存在变量temp中
                {
                    cout <<setw(4)<<temp;
                }
                else
                {
                    cout <<"取出数据失败" <<endl;
                }
            }
            cout <<endl <<endl;     // 执行换行信息

            cout <<"清空数据" <<endl <<endl;
            list.Clean( );          // 清空线性链表

            cout <<"清空成功后, 线性链表为空, 无法访问" <<endl;

            // 系统提示信息
            cout <<"线性链表清空成功" <<endl <<endl;
            cout <<"即将返回主菜单" <<endl <<endl;
            cout <<"Please ent any key to continue" <<endl;
            system("pause");

          /// 0 -=> 退出程序
          case 0:
            // 系统提示信息
            system("cls");
            cout <<"***********************************" <<endl;
            cout <<"**   您当前的选择0 -=> 退出程序  **" <<endl;
            cout <<"***********************************" <<endl <<endl <<endl;            // 系统提示信息

            Stop( );
//            #if (VERSION)     // 程序编译信息输出
//            cout <<"\t\t**************************************************" <<endl;
//            cout <<"\t\t**  Wacky Window (c) 2012 Wacky SoftWare. Inc.  **"<<endl;
//            cout <<"\t\t**     Complied on " <<__DATE__ <<" at " <<__TIME__ <<"      **"<<endl;
//            cout <<"\t\t**************************************************" <<endl;
//
//            system("pause");
//            #endif

        Lording( );         // 载入函数
        }
    }

    return 0;
}



//// 函数名称：void Display(const DblLinkList<ElemType> &list)
//// 初始条件：线性表已经建立, 并且数据已经插入
//// 操作结果：输出元素对象
//template <class ElemType>
//void Display(const DblLinkList<ElemType> &list)    // 显示函数
//{
//    int length = list.Length( );
//
//    if(length == 0)
//    {
//        cout <<"当前线性链表表长为" <<length <<", 数据显示失败" <<endl;
//        return;
//    }
//
//    ElemType temp;
//    for(int i = 1; i < length; i++)
//    {
//        if(list.GetElem(i, temp) == true)      // 取出线性链表的第i个元素, 并将取出的数据存在变量temp中
//        {
//            cout <<setw(4)<<temp;
//        }
//        else
//        {
//            cout <<"取出数据失败" <<endl;
//        }
//    }
//    cout <<endl <<endl;     // 执行换行信息
//}
