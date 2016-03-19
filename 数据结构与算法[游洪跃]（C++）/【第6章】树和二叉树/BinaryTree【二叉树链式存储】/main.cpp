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


#include <iostream>
#include <ctime>
#include <windows.h>
#include <cstdlib>
#include <cstdio>
#include <iomanip>

#include "BinaryTree.h"

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
void CreateTree(BinaryTree<char> &tree);    // 建立链式二叉树
void ShowTree(BinaryTree<char> &tree);  // 输出链式二叉树
void InsertTree(BinaryTree<char> &tree);        // 添加结点
void DeleteTree(BinaryTree<char> &tree);        // 删除结点
void Destroy(BinaryTree<char> &tree);     // 清空二叉树
/// 主函数
int main( )
{
    system("title 二叉树链表");     // 调用系统命令更改DOS窗口名称

    // 调试状态下的输出信息
#ifdef DEBUG           // 如果宏定义了DEBUG, 执行一下语句
    cout <<"\t\tHello World*****************************************" <<endl;
    cout <<"\t\t**              Now Start Debug                   **" <<endl;
    cout <<"\t\t*****************************************Hello World" <<endl;
#else
    cout <<"\t\t****************************************************" <<endl;
    cout <<"\t\t**              Test BinaryTree Of                **" <<endl;
    cout <<"\t\t****************************************************" <<endl;
#endif

    Welcome( );         // 欢迎界面

    // 程序初始化部分
    int choice;
    BinaryTree<char> tree;
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
            cout <<"\t\t**   您当前的选择1 -=> 新建链式二叉树   **" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl <<endl;


            // 程序测试部分
            cout <<"链式二叉树已经初始化\n请开始输入结点字符数据域\n输入'#'表示空" <<endl <<endl;
            cout <<"文件InPut.txt中给出了几组测试用例, 方便您记性测试" <<endl <<endl;
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



            /// 遍历链式二叉树
        case 2:
            // 系统提示信息
            system("cls");
            cout <<"\t\t******************************************" <<endl;
            cout <<"\t\t**   您当前的选择2 -=> 遍历链式二叉树   **" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl <<endl;

            // 程序测试部分
            cout <<"为了方便验证程序的正确性, 我们将依次显示出三种遍历方式" <<endl <<endl;
            ShowTree(tree);

            // 系统提示信息
            cout <<"\t\t******************************************" <<endl;
            cout <<"\t\t**              数据插入完毕            **" <<endl;
            cout <<"\t\t**             即将返回主菜单           **" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl;
            cout <<"Please ent any key to continue........................" <<endl;
            system("pause");
            break;

            /// 4 -=> 添加结点
        case 3:
            // 系统提示信息
            system("cls");
            cout <<"\t\t********************************************" <<endl;
            cout <<"\t\t**       您当前的选择3 -=> 添加结点       **" <<endl;
            cout <<"\t\t********************************************" <<endl <<endl <<endl;

            // 程序测试部分
            InsertTree(tree);

            // 系统提示信息
            cout <<"\t\t********************************************" <<endl;
            cout <<"\t\t**              数据插入完毕              **" <<endl;
            cout <<"\t\t**             即将返回主菜单             **" <<endl;
            cout <<"\t\t********************************************" <<endl <<endl;
            cout <<"Please ent any key to continue........................" <<endl;
            system("pause");
            break;

            /// 4 -=> 删除结点
        case 4:
            // 系统提示信息
            system("cls");
            cout <<"\t\t******************************************" <<endl;
            cout <<"\t\t**      您当前的选择4 -=> 删除结点      **" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl <<endl;


            // 程序测试部分
            DeleteTree(tree);


            // 系统提示信息
            cout <<"\t\t******************************************" <<endl;
            cout <<"\t\t**              数据插入完毕            **" <<endl;
            cout <<"\t\t**             即将返回主菜单           **" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl;
            cout <<"Please ent any key to continue........................" <<endl;
            system("pause");
            break;

            /// 5 -=> 清空链式二叉树
        case 5:
            // 系统提示信息
            system("cls");
            cout <<"\t\t******************************************" <<endl;
            cout <<"\t\t**   您当前的选择5 -=> 清空链式二叉树   **" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl <<endl;

            // 程序测试部分
            Destroy(tree);

            // 系统提示信息
            cout <<"\t\t******************************************" <<endl;
            cout <<"\t\t**              数据清空完毕            **" <<endl;
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



//template <class ElemType>
void CreateTree(BinaryTree<char> &tree) // 输入链式二叉树
{
/*
    int choice;
    cout <<"************************" <<endl;
    cout <<"** 请选择您的建立方式 **" <<endl;
    cout <<"** 1 -=> 前序方式建立 **" <<endl;
    cout <<"** 2 -=> 中序方式建立 **" <<endl;
    cout <<"** 3 -=> 后序方式建立 **" <<endl;
    cout <<"************************" <<endl;
    cout <<"Please enter tour choice" <<endl;

    cin >>choice;
    cout <<"请依次输入数据, 输入#标识结点为空" <<endl <<endl;
    switch(choice)
    {
    case 1:
        tree.PreCreate(Read, IsNull);
        break;
    case 2:
        tree.InCreate(Read, IsNull);
        break;
    case 3:
        tree.PostCreate(Read, IsNull);
        break;
    }*/
    cout <<"前序建立二叉树" <<endl;
    cout <<"请依次输入数据, 输入#标识结点为空" <<endl <<endl;
    tree.PreCreate(Read, IsNull);
}

void ShowTree(BinaryTree<char> &tree)       // 遍历链式二叉树
{
    cout <<"当前二叉树的深度HEIGHT: "<<tree.Height( ) <<", 结点数目" <<tree.NodeCount( ) <<endl <<endl;
    cout <<"前序遍历结果：" <<endl;
    tree.PreOrder(Write);          // 二叉树的先序遍历

    cout <<endl <<"中序遍历结果：" <<endl;
    tree.InOrder(Write);           // 二叉树的中序遍历

    cout <<endl <<"后序遍历结果：" <<endl;
    tree.PostOrder(Write);         // 二叉树的后序遍历

    cout <<endl <<"层次遍历结果：" <<endl;
    tree.LevelOrder(Write);        // 二叉树的层次遍历

    cout <<endl <<endl;
}


void InsertTree(BinaryTree<char> &tree)     // 插入二叉树的结点
{
    char elem, temp;
    BinTreeNode<char> *node;
    while( 1 )
    {
        // 输出插入后的结果
        cout <<endl <<"当前二叉树层次遍历结果：" <<endl;
        tree.LevelOrder(Write);        // 二叉树的层次遍历
        cout <<endl <<endl;

        // 查找信息提示
        cout <<"请输入您要添加的数据的位置, 直接输入结点位置的数据值" <<endl;
        cout <<"输入#结束插入" <<endl;
        cin >>elem;

        if(elem == '#')     // 循环终止控制
        {
            break;
        }
        node = tree.Search(elem);   // 查询到要插入的位置

        if(node == NULL)    // 如果查询失败
        {
            cout <<"输入的位置有误, 查询不到" <<temp <<"结点" <<endl <<endl;
            continue;
        }
        else        // 否则输入插入数据以及插入方式
        {
            cout <<"请输入想要输入的数据值, 以及插入的方式[作为左子结点插入l, 右子结点r]" <<endl;
            cout <<"ELEM = ";
            cin >>elem;
            cout <<"Ll or Rr: ";
            cin >>temp;

            switch(temp)
            {
            case 'l':
            case 'L':
                tree.InsertLeftChild(node, elem);   // 插入左结点
                break;
            case 'r':
            case 'R':
                tree.InsertRightChild(node, elem);  // 作为右结点插入
                break;
            }
            cout <<"插入成功" <<endl <<endl <<endl;
        }
    }
}



void DeleteTree(BinaryTree<char> &tree) // 删除二叉树的结点
{
    char elem, temp;
    BinTreeNode<char> *node;
    while( 1 )
    {
        // 输出插入后的结果
        cout <<endl <<"当前二叉树层次遍历结果：" <<endl;
        tree.LevelOrder(Write);        // 二叉树的层次遍历
        cout <<endl;

        // 查找信息提示
        cout <<"请输入您要删除的数据的父节点数据" <<endl;
        cout <<"输入#结束删除" <<endl;
        cin >>elem;

        if(elem == '#')     // 循环终止控制
        {
            break;
        }
        node = tree.Search(elem);   // 查询到要插入的位置
        if(node == NULL)    // 如果查询失败
        {
            cout <<"输入的位置有误, 查询不到" <<temp <<"结点" <<endl <<endl;
            continue;
        }
        else        // 否则输入插入数据以及插入方式
        {
            cout <<"请输入您要删除的位置[删除左子树l, 右子树r]" <<endl;
            cout <<"Ll or Rr: ";
            cin >>temp;

            switch(temp)
            {
            case 'l':
            case 'L':
                tree.DeleteLeftChild(node);     // 删除node的左子树
                break;
            case 'r':
            case 'R':
                tree.DeleteRightChild(node);     // 删除node的右子树
                break;
            }
            cout <<"删除成功" <<endl <<endl <<endl;
        }
    }
}


void Destroy(BinaryTree<char> &tree)     // 清空二叉树
{
    // 输出请空前的结果
    cout <<endl <<"当前二叉树层次遍历结果：" <<endl;
    tree.LevelOrder(Write);        // 二叉树的层次遍历
    cout <<endl;
    cout <<"当前二叉树的深度HEIGHT: "<<tree.Height( ) <<", 结点数目" <<tree.NodeCount( ) <<endl <<endl <<endl;


    cout <<"清空二叉树后" <<endl;
    tree.~BinaryTree( );
    cout <<"当前二叉树的深度HEIGHT: "<<tree.Height( ) <<", 结点数目" <<tree.NodeCount( ) <<endl <<endl;
}
