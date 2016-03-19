/**
******************************************************************************
*  CopyRight  : 2012-2013, HerBinUnversity, GatieMe                          *
*  File Name  : Other.cpp                                                    *
*  Description: 二叉树链表实现外部函数文件                                  *
*  Author     : Gatie_Me                                                     *
*  Version    : Copyright 2012 JULY_CITY                                     *
*  Data_Time  : 2012-11-6_10:21:43                                           *
*  Content    : 数据结构与算法（C++）版书上源码                             *
******************************************************************************
**/


#include <iostream>
#include <ctime>
#include <conio.h>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cstring>
#include <ctime>

using namespace std;


// 函数名称：template <class ElemType> void Write(const ElemType &e)
// 操作结果: 输入数据元素
//template <class ElemType>
//void Read(ElemType &elem)
//{
//    cin >>elem;    //输入元素的信息
//}


void Read(char &elem)
{
    cin >>elem;    //输入元素的信息
}

void Write(char &elem)
{
    cout <<elem;     //输出元素的信息
}
// 函数名称：template <class ElemType> void Write(const ElemType &e)
// 操作结果: 显示数据元素
//template <class ElemType>
//void Write(ElemType &elem)
//{
//    cout <<elem;     //输出元素的信息
//}

bool IsNull(char &temp)  // CreateTree函数的辅助函数
{
    return (temp == '#');
}

void Welcome( )
{
    const char *inFor[11];
    inFor[0] = "                ****************************************************              ";
    inFor[1] = "                *          Welcome To The Hufffman World!          *              ";
    inFor[2] = "                *       You Will Fall In Love In This World!       *              ";
    inFor[3] = "                *       We All Hope That Which Is Said To Us       *              ";
    inFor[4] = "                *        List's Strory Is Only The Begining        *              ";
    inFor[5] = "                ****************************************************              ";

    for(int i = 0; i < 6; i++)
    {
        for(int j = 0; inFor[i][j] != '\0'; j++)
        {
            cout <<inFor[i][j];
        }
        cout <<endl;
    }

    cout <<"Please enter any key to continue" <<endl;
    getchar( );
    system("cls");
}



void Menu( )
{
    system("cls");
    const char *menu[8] = {
        "\t\t********************************************",
        "\t\t**      1 -=> 新建字符型哈夫曼编码        **",
        "\t\t**         2 -=> 显示字符编码信息         **",
        "\t\t**           3-=>哈夫曼树编码             **",
        "\t\t**           4 -=> 哈夫曼译码             **",
        "\t\t**         5-=>树形显示哈夫曼树           **",
        "\t\t**          0 -=> 退出程序                **",
        "\t\t********************************************",
        };

    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; menu[i][j] != '\0'; j++)
        {
            cout <<menu[i][j];
        }
        cout <<endl;
    }
    cout <<"请输入您的选择" <<endl;
}


// 延时函数
void Delay( )
{
    for(int i = 0; i < 1000000; i++);
}

// 载入函数
void Lording( )
{
    system("cls");

    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10000000; j++);
        cout <<"□";
    }
    cout <<endl;

    system("cls");
}

void Version( )
{
    cout <<"\t\t**************************************************" <<endl;
    cout <<"\t\t**  Wacky Window (c) 2012 Wacky SoftWare. Inc.  **"<<endl;
    cout <<"\t\t**     Complied on " <<__DATE__ <<" at " <<__TIME__ <<"      **"<<endl;
    cout <<"\t\t**************************************************" <<endl;
    system("pause");
}





//
//// 判断用户的输入信息
//char GetChar(istream &in)
//{
//    char ch;
//
//    while((ch = in.peek( )) != EOF
//        && (ch = in.get( )) == ' '
//        || ch == '\t')
//    {
//        return ch;
//    }
//}

// 看用户是否输入了ye
 bool SayYes( )
{
    char ch;
    bool response = true;

    do
    {
        if(response == true)
        {
            cout <<"(y, n)???: ";
        }
        else
        {
            cout <<"请用(y, n)回答";
        }
        cin >>ch;
        response = false;
    }while(ch != 'y' && ch != 'Y' && ch != 'n' && ch != 'N');
    //while(GetChar(cin) != '\n');

    if(ch == 'y' || ch == 'Y')
    {
        return true;
    }
    else
    {
        return false;
    }
}
