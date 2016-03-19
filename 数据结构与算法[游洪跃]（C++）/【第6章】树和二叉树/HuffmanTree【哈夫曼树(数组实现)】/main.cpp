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

#include "HuffmanTree.h"

#ifdef DEBUG
#undef DEBUG
//#define DEBUG
#endif

using namespace std;

/// 外部函数（所在文件Other.cpp）
void Read(char &);
void Write(char &);
bool IsNull(char &);
void Welcome( );        // 欢迎函数
void Menu( );       // 菜单显示函数
void Delay( );      // 延时函数
void Lording( );    // 载入函数
void Stop( );       // 终止函数



// 内部函数(main.cpp)

int DisStr(char *str, char chars[], int weight[]);  // 将输入的字符串转换为为带权值的字符信息
void CreateTree(HuffmanTree<char, int> &tree); // 新建字符型哈夫曼编码
void ShowTree(HuffmanTree<char, int> &tree);       // 打印字符编码信息
void EnHuffman(HuffmanTree<char, int> &tree);       // 哈夫曼树编码
void DeHuffman(HuffmanTree<char, int> &tree);   // 哈夫曼译码

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
    //HuffmanTreeNode<int> node;
    HuffmanTree<char, int> tree;
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
            cout <<"\t\t**您当前的选择1 -=> 新建字符型哈夫曼编码**" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl <<endl;


            // 程序测试部分
            CreateTree(tree);

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
            cout <<"\t\t**  您当前的选择2 -=> 打印字符编码信息  **" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl <<endl;

            // 程序测试部分
            ShowTree(tree);

            // 系统提示信息
            cout <<"\t\t******************************************" <<endl;
            cout <<"\t\t**              数据插入完毕            **" <<endl;
            cout <<"\t\t**             即将返回主菜单           **" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl;
            cout <<"Please ent any key to continue........................" <<endl;
            system("pause");
            break;

            /// 3 -=> 清空哈夫曼
        case 3:
            // 系统提示信息
            system("cls");
            cout <<"\t\t******************************************" <<endl;
            cout <<"\t\t**     您当前的选择3-=>哈夫曼树编码     **" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl <<endl;


            // 程序测试部分
            EnHuffman(tree);


            // 系统提示信息
            cout <<"\t\t******************************************" <<endl;
            cout <<"\t\t**              数据插入完毕            **" <<endl;
            cout <<"\t\t**             即将返回主菜单           **" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl;
            cout <<"Please ent any key to continue........................" <<endl;
            system("pause");
            break;
            /// 4 -=> 哈夫曼译码
        case 4:
            // 系统提示信息
            system("cls");
            cout <<"\t\t********************************************" <<endl;
            cout <<"\t\t**      您当前的选择4 -=> 哈夫曼译码      **" <<endl;
            cout <<"\t\t********************************************" <<endl <<endl <<endl;

            // 程序测试部分
            DeHuffman(tree);     // 输入编码进行译码

            // 系统提示信息
            cout <<"\t\t********************************************" <<endl;
            cout <<"\t\t**              数据插入完毕              **" <<endl;
            cout <<"\t\t**             即将返回主菜单             **" <<endl;
            cout <<"\t\t********************************************" <<endl <<endl;
            cout <<"Please ent any key to continue........................" <<endl;
            system("pause");
            break;

            /// 5-=>树形显示哈夫曼树
        case 5:
            // 系统提示信息
            system("cls");
            cout <<"\t\t********************************************" <<endl;
            cout <<"\t\t**    您当前的选择5-=>树形显示哈夫曼树    **" <<endl;
            cout <<"\t\t********************************************" <<endl <<endl <<endl;

            // 程序测试部分
            tree.DisplayWithShape( );

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


// 将输入的字符串转换为为带权值的字符信息
int DisStr(char *str, char chars[], int weight[])
{
    int i, j, count;
    sort(str, str + strlen(str));     // 将字符传播进行排序

    i = 0;
    j = 0;
    count = 1;
    while(str[i] != '\0')
    {
        if(str[i] == str[i+1])
        {
            count++;            // 将计数器进1
        }
        else
        {
            chars[j] = str[i];        // 将当前字符存入字符信息数组
            weight[j] = count;        // 将当前字符的权值存入字符信息数组
            j++;
            count = 1;
        }
        i++;
    }

//    #ifdef DEBUG
//    for(int i = 0; i < j; i++)
//    {
//        cout <<weight[i]<<chars[i];
//    }
//    #endif

    return j;
}


void CreateTree(HuffmanTree<char, int> &tree) // 构建哈夫曼编码
{
    char str[81];
    char chars[100];
    int weight[100];
    int size;

    cout <<"请输入需要编码的字符串" <<endl;
    cin >>str;
    size = DisStr(str, chars, weight);      // 处理输入的字符串

    tree.CreateHuffmanTree(chars, weight, size);        // 构造哈夫曼编码
}

void ShowTree(HuffmanTree<char, int> &tree)       // 显示各字符的哈夫曼编码
{
    for(int i = 1; i <= tree.Size( ); i++)
    {
        cout <<tree.Char(i) <<" : "  <<tree.EnCode(tree.Char(i)) <<endl;
    }
}

void EnHuffman(HuffmanTree<char, int> &tree)     // 输入编码进行译码
{
    cout <<"当恰哈夫曼的编码序列为:" <<endl;
    ShowTree(tree);     // 首先显示编码信息

    string huffman;
    string strCode;
    while( 1 )
    {

        cout <<endl <<endl <<"请输入您要编码的编码串[输入\"#\"停止译码]" <<endl <<"huffman =";
        cin >>strCode;

        if(strCode == "#")      // 输入#停止译码
        {
            break;
        }

        huffman = "";
        for(unsigned int pos = 0; pos < strCode.size(); pos++)
        {
            huffman += tree.EnCode(strCode[pos]);
        }

        cout <<"当前串被编码后的哈夫曼编码信息为：" <<endl;
        cout <<huffman <<endl;
    }
}

void DeHuffman(HuffmanTree<char, int> &tree)     // 输入编码进行译码
{
    cout <<"当恰哈夫曼的编码序列为:" <<endl;
    ShowTree(tree);     // 首先显示编码信息

    string huffman;
    while( 1 )
    {
        cout <<endl <<endl <<"请输入您要译码的编码串[输入\"#\"停止译码]" <<endl <<"huffman =";
        cin >>huffman;

        if(huffman == "#")      // 输入#停止译码
        {
            break;
        }

        cout <<"当前编码的哈夫曼序列为:" <<endl;
        cout <<tree.DeCode(huffman);
    }
}





