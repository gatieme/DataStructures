#include <iostream>
#include <fstream>
#include <ctime>
#include <windows.h>
#include <cstdlib>
#include <cstdio>
#include <iomanip>
#include <algorithm>



#define SIZE 10
// 快速排序还有归并
#include "Sort.h"

bool SmallThan(const void *a, const void *b)
{
    int *pa = (int *)a;
    int *pb = (int *)b;
    return (*pa < *pb);
}

bool BigThan(const void *a, const void *b)
{
    int *pa = (int *)a;
    int *pb = (int *)b;
    return (*pa > *pb);
}


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


/// 内部函数
// 初始化数组信息
void InitArray(int *array, int length);
// 进行函数测试
void ArrySortFunction(int *array, int length, int choice);
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
    cout <<"\t\t**               Test Sorting Of                  **" <<endl;
    cout <<"\t\t****************************************************" <<endl;
#endif

    Welcome( );         // 欢迎界面

    // 程序初始化部分
    int choice;
    int *array = new int[SIZE];           // 开辟待排序数据的信息


    InitArray(array, SIZE);
    system("pause");
    Lording( );         // 载入函数

    while( 1 )
    {
        Menu( );        // 系统菜单

        cin >>choice;         //输入您的选择
        system("cls");
        switch(choice)
        {
            /// 1 -=> 直接插入排序
        case 1:
            // 系统信息提示
            cout <<"\t\t******************************************" <<endl;
            cout <<"\t\t**    您当前的选择1 -=> 直接插入排序    **" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl <<endl;


            // 程序测试部分
            ArrySortFunction(array, SIZE, choice);

            // 系统信息提示
            cout <<"\t\t******************************************" <<endl;
            cout <<"\t\t**              数据插入完毕            **" <<endl;
            cout <<"\t\t**             即将返回主菜单           **" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl;
            cout <<"Please ent any key to continue........................" <<endl;
            //getchar( );
            system("pause");
            break;

            /// 2 -=> Shell排序算法
        case 2:
            // 系统提示信息
            system("cls");
            cout <<"\t\t********************************************" <<endl;
            cout <<"\t\t**     您当前的选择2 -=> Shell排序算法    **" <<endl;
            cout <<"\t\t********************************************" <<endl <<endl <<endl;

            // 程序测试部分
            ArrySortFunction(array, SIZE, choice);

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
            cout <<"\t\t**    您当前的选择3 -=> 冒泡排序算法    **" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl <<endl;

            // 程序测试部分
            ArrySortFunction(array, SIZE, choice);

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
            cout <<"\t\t**    您当前的选择4 -=> 快速排序算法    **" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl <<endl;


            // 程序测试部分
            ArrySortFunction(array, SIZE, choice);

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
            cout <<"\t\t**    您当前的选择5 -=> 简单选择排序      **" <<endl;
            cout <<"\t\t********************************************" <<endl <<endl <<endl;

            // 程序测试部分
            ArrySortFunction(array, SIZE, choice);

            // 系统提示信息
            cout <<"\t\t********************************************" <<endl;
            cout <<"\t\t**              数据插入完毕              **" <<endl;
            cout <<"\t\t**             即将返回主菜单             **" <<endl;
            cout <<"\t\t********************************************" <<endl <<endl;
            cout <<"Please ent any key to continue........................" <<endl;
            system("pause");
            break;


            /// 6 -=> 堆排序__算法
        case 6:
            // 系统提示信息
            system("cls");
            cout <<"\t\t********************************************" <<endl;
            cout <<"\t\t**    您当前的选择6 -=> 堆排序__算法      **" <<endl;
            cout <<"\t\t********************************************" <<endl <<endl <<endl;

            // 程序测试部分
            ArrySortFunction(array, SIZE, choice);

            // 系统提示信息
            cout <<"\t\t********************************************" <<endl;
            cout <<"\t\t**              数据插入完毕              **" <<endl;
            cout <<"\t\t**             即将返回主菜单             **" <<endl;
            cout <<"\t\t********************************************" <<endl <<endl;
            cout <<"Please ent any key to continue........................" <<endl;
            system("pause");
            break;

            /// 7 -=> 归并排序算法
        case 7:
            // 系统提示信息
            system("cls");
            cout <<"\t\t********************************************" <<endl;
            cout <<"\t\t**    您当前的选择7 -=> 归并排序算法      **" <<endl;
            cout <<"\t\t********************************************" <<endl <<endl <<endl;

            // 程序测试部分
            ArrySortFunction(array, SIZE, choice);

            // 系统提示信息
            cout <<"\t\t********************************************" <<endl;
            cout <<"\t\t**              数据插入完毕              **" <<endl;
            cout <<"\t\t**             即将返回主菜单             **" <<endl;
            cout <<"\t\t********************************************" <<endl <<endl;
            cout <<"Please ent any key to continue........................" <<endl;
            system("pause");
            break;

            /// 7 -=>进行图的遍历搜索
        case 8:
            // 系统提示信息
            system("cls");
            cout <<"\t\t********************************************" <<endl;
            cout <<"\t\t**    您当前的选择8 -=> 基数排序算法       **" <<endl;
            cout <<"\t\t********************************************" <<endl <<endl <<endl;

            // 程序测试部分
            ArrySortFunction(array, SIZE, choice);

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


// 初始化数组信息
void InitArray(int *array, int length)
{
    cout <<"正在初始化数组的信息" <<endl;

    srand(time(NULL));          // 用种子函数设随机数种子

    for(int i = 0; i < length; i++)
    {
        array[i] = rand( ) % 101;           // 设置0-100的随机数

        cout <<setw(4)<<array[i];
    }
    cout <<endl;
    cout <<"数组信息初始化完毕" <<endl <<endl;
}

// 进行函数测试
void ArrySortFunction(int *array, int length, int choice)
{
    bool outWay;
    //#define STEP false
    //#define NOMAL true
    cout <<"**************************" <<endl;
    cout <<"**  0-单步输出排序信息  **" <<endl;
    cout <<"**  1-直接输出排序结果  **" <<endl;
    cout <<"**************************" <<endl;
    cin >>outWay;

    switch(choice)
    {
        case 1: StraightInsertSort(array, length, BigThan, Write, outWay);
                break;
        case 2: ShellSort(array, length, BigThan, Write, outWay);
                break;
        case 3: BubbleUpSort(array, length, BigThan, Write, outWay);
                break;
        case 4: QuickSort(array, length, BigThan, outWay);
                break;
        case 5: SelectSort(array, length, BigThan, Write, outWay);
                break;
        case 6: HeapSort(array, length, BigThan, Write, outWay);
                break;
        case 7: MergeSort(array, length, BigThan, outWay);
                break;
        case 8: RadixSort(array, length, 9, 3, outWay);

    }
    cout <<"排序结果 ：";
    for(int i = 0; i < length; i++)
    {
        cout <<setw(4)<<array[i];
    }
    cout <<endl;
}
