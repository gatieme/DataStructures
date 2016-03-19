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

#include "SqList.h"
using namespace std;

//#define DEBUG                     // 如果进行调试请将此注释打开
#define VERSION  1                  // 如果不想显示版本以及编译信息请将该宏定义置为0


/// 外部函数（所在文件Other.cpp）
template <class ElemType>
void Read(ElemType &elem);        // 输入数据元素

template <class ElemType>
void Write(ElemType &elem);       // 输入数据元素

//void Read(const int);        // 输入数据元素
////
////
//void Write(const int);       // 输入数据元素

void Menu( );
void Delay( );   // 延时函数
void Lording( );   // 载入函数

// 主函数
int main( )
{

    // 预编译处理
 //   typedef void (*FunctionPoint)(int);
    // 调试状态下的输出信息
    #if defined DEBUG           // 如果宏定义了DEBUG, 执行一下语句
    cout <<"\t\t\tHello World***********************" <<endl;
    cout <<"\t\t\t**     Now Start Debug          **" <<endl;
    cout <<"\t\t\t***********************Hello World" <<endl;
    #endif

    // 非调试状态下的输出信息
    #ifndef DEBUG                // 如果宏定义了DEBUG, 执行一下语句
    cout <<"\t\t\t**********************************" <<endl;
    cout <<"\t\t\t**       Test Sqlist Of         **" <<endl;
    cout <<"\t\t\t**********************************" <<endl;
    #endif

    cout <<"Please any key to continue";
    getchar( );
    system("cls");

    int choice = 1, temp, lenList; /*表长*/;
    int leftPosition, rightPosition;   //下标标记信息
    int leftItem, rightItem;
    SqList<int> list;   //创建一个整形顺序表[默认创建最大元素单元]


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
            cout <<"****************************************" <<endl;
            cout <<"** 您当前的选择1 -=> 新建一整形线性表 **" <<endl;
            cout <<"****************************************" <<endl <<endl <<endl;

            cout <<"选择后系统将自动建立一个线性表[数据随机]" <<endl;

            // 输入表长
            cout <<"请输入即将测试线性表的表长" <<endl;
            cin >>lenList;          // 输入表长

            srand( time(NULL) );     // 设置随即种子
            cout <<"显示插入数据的情况" <<endl;
            for(int i = 1; i <= lenList; i++)         // 插入数据
            {
                temp = rand() %100 + 1;
                if(list.Insert(i, temp) == true)        // 将数据插入
                {
                    cout <<"将数据" <<temp <<"插入线性表的第" <<i <<"个位置" <<endl;
                    cout <<"当前线性表的长度为：" <<list.Length( ) <<endl <<endl;
                    Delay( );
                }
            }

            cout <<"数据插入完毕" <<endl <<endl;
            cout <<"即将返回主菜单" <<endl <<endl;
            cout <<"Please ent any key to continue" <<endl;
            //getchar( );
            system("pause");
            break;

          case 2:
            // 系统提示信息
            system("cls");
            cout <<"****************************************" <<endl;
            cout <<"** 您当前的选择2 -=> 显示建立的线性表 **" <<endl;
            cout <<"****************************************" <<endl <<endl <<endl;
            // 输出线性表中的数据
            cout <<endl <<"这个线性表中" <<list.Length( ) <<"个数据为：" <<endl;     // 测试遍历函数
            //  list.Traverse(Write<int>);

            cout <<"依次取出并且输出线性表中的每个数" <<endl;
            for(int i = 1; i <= lenList; i++)
            {
                list.GetElem(i, temp);
                cout <<temp <<" ";
            }
            cout <<endl <<endl;

            // 系统提示信息
            cout <<"数据输出完毕" <<endl <<endl;
            cout <<"即将返回主菜单" <<endl <<endl;
            cout <<"Please ent any key to continue" <<endl;
            //getchar( );
            system("pause");
            break;

          case 3:
            // 系统提示信息
            system("cls");
            cout <<"****************************************" <<endl;
            cout <<"** 您当前的选择3 -=> 排序建立的线性表 **" <<endl;
            cout <<"****************************************" <<endl <<endl <<endl;
            list.SelectSort( );
            // list.BubbleSort( );

            cout <<"排序后线性表中" <<list.Length( ) <<"个数据为：" <<endl;     // 测试遍历函数
            cout <<"依次取出并且输出线性表中的每个数" <<endl;
            //  list.Traverse(Write<int>);
            for(int i = 1; i <= lenList; i++)
            {
                list.GetElem(i, temp);
                cout <<temp <<" ";
            }
            cout <<endl <<endl;

            // 系统提示信息
            cout <<"数据排序完毕" <<endl <<endl;
            cout <<"即将返回主菜单" <<endl <<endl;
            cout <<"Please ent any key to continue" <<endl;
            system("pause");
            break;

          case 4:
            // 系统提示信息
            system("cls");
            cout <<"**********************************************" <<endl;
            cout <<"** 您当前的选择4 -=> 将线性表分成奇偶两部分 **" <<endl;
            cout <<"**********************************************" <<endl <<endl <<endl;
//本题的主要思路如下：
//                设置leftPosition = 1, rightPosition = list.lenList;
//                list的第leftPosition个元素为leftItem, list的第rightPosition个元素为rightItem,
//                当list左边的数leftItem为奇数时, 则leftPosition++;
//                当list右边的数rightItem为偶数时, 则rightPosition--;
//                而当list左边的数leftItem为偶数, 且右边的数rightItem为奇数时,
//                就交换leftItem和rightItem, 同时leftPosition++, rightPosition--;
//                直到leftPosition == rightPosition时为止;
//                算法复杂度为O(n)
            // 一个整形int的顺序表, 设计算法将其调整为左右两部分
            // 左边部分全为奇数,右边部分全为偶数, 并且要求算法的时间复杂度为O(n)

            // 实现将测试整形线性表分隔为两个部分的算法
                             //标记数据
            leftPosition = 1;
            rightPosition = list.Length( );   //下标标记信息

            while(leftPosition < rightPosition)
            {
                list.GetElem(leftPosition, leftItem);   //取出list左边的数据leftItem
                list.GetElem(rightPosition, rightItem); //取出list右边的数据rightItem

                // 调试信息
                #if defined DEBUG           // 如果宏定义了DEBUG, 执行一下语句
                cout <<leftItem <<"  " <<rightItem <<endl;
                //    system("pause");
                #endif

                if(leftItem % 2 == 1)   //如果左边的数leftItem是奇数
                {
                    leftPosition++;    //符合结果要求, 于是将leftPosition右移到下一个数
                //    if(leftPosition == rightPosition)  break;
                }
                else if(rightItem % 2 == 0)   //如果右边的数rightItem是偶数
                {
                    rightPosition--;    //符合结果要求, 于是将rightPosition前移到上一个数
                   // if(leftPosition == rightPosition)  break;
                }
                else //如果list左边的数leftItem为偶数, 且右边的数rightItem为奇数
                {   //这种情况不满足结果要求需要 -=> 将两个数交换
                    //list.SetElem(leftPosition, rightItem);
                    // list.SetElem(rightPosition, leftItem);
                    list.Swap(leftPosition++, rightPosition--);
                //    if(leftPosition == rightPosition)  break;
                }
            }

            cout <<"将线性表分割为奇数偶数的两个部分以后";
            cout <<"现在数据的排列情况为：" <<endl;     // 测试遍历函数
            //  list.Traverse(Write<int>);
            for(int i = 1; i <= lenList; i++)
            {
                list.GetElem(i, temp);
                cout <<temp <<" ";
            }
            cout <<endl <<endl;

            // 系统提示信息
            cout <<"数据分割完毕" <<endl <<endl;
            cout <<"即将返回主菜单" <<endl <<endl;
            cout <<"Please ent any key to continue" <<endl;
            system("pause");
            break;

          case 5:
            // 系统提示信息
            system("cls");
            cout <<"************************************" <<endl;
            cout <<"**   您当前的选择5 -=> 删除元素   **" <<endl;
            cout <<"*************************************" <<endl <<endl <<endl;

            int position;
            while( 1 )
            {
                cout <<"删除线性表的元素[输入0结束删除]" <<endl;
                cout <<"请问您要删除出第几个元素" <<endl;
                cin >>position;
                if(position == 0)
                {
                    break;
                }

                if(list.Delete(position, temp) == true)
                {
                    cout <<"被删除的元素" <<temp <<endl;
                    cout <<"删除掉元素后, 当前线性表的信息如下" <<endl;
                }
                for(int i = 1; i <= list.Length( ); i++)
                {
                    list.GetElem(i, temp);
                    cout <<temp <<" ";
                }
                cout <<endl <<endl;
            }

            // 系统提示信息
            cout <<"数据删除完毕" <<endl <<endl;
            cout <<"即将返回主菜单" <<endl <<endl;
            cout <<"Please ent any key to continue" <<endl;
            system("pause");
            break;

          case 6:
            // 系统提示信息
            system("cls");
            cout <<"**************************************" <<endl;
            cout <<"**   您当前的选择6 -=> 清空线性表   **" <<endl;
            cout <<"**************************************" <<endl <<endl <<endl;
            list.Clean( );
            cout <<"清空成功" <<endl;
            cout <<"当前线性表的长度为" <<list.Length( ) <<endl;

            // 系统提示信息
            cout <<"数据删除完毕" <<endl <<endl;
            cout <<"即将返回主菜单" <<endl <<endl;
            cout <<"Please ent any key to continue" <<endl;
            system("pause");
          case 0:
            // 系统提示信息
            system("cls");
            cout <<"***********************************" <<endl;
            cout <<"**   您当前的选择0 -=> 退出程序  **" <<endl;
            cout <<"***********************************" <<endl <<endl <<endl;            // 系统提示信息

            char answer;
            do
            {	// 循环直到用户输入恰当的回答为止

                cout << "(y, n)?";
                cout << "用y或n回答:";
                while ((answer = getchar( )) == '\n');	// 跳过空格,制表符及换行符获取一字符
            }while (answer != 'y' && answer != 'Y' && answer != 'n' && answer != 'N');

            #if (VERSION)     // 程序编译信息输出
            cout <<"\t\t**************************************************" <<endl;
            cout <<"\t\t**  Wacky Window (c) 2012 Wacky SoftWare. Inc.  **"<<endl;
            cout <<"\t\t**     Complied on " <<__DATE__ <<" at " <<__TIME__ <<"      **"<<endl;
            cout <<"\t\t**************************************************" <<endl;

            system("pause");
            #endif
            if(answer == 'y' || answer == 'Y')
            {
                cout <<"用户选择退出";
                exit(0);
            }
            else
            {
                cout <<"用户取消" <<endl;
            }
    //        break;

        }
        Lording( );         // 载入函数
    }

    return 0;
}

