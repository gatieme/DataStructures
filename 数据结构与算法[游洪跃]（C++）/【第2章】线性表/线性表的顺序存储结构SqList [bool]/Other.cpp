/********************************************************************************
CopyRight  : 2012-2013, HerBinUnversity, GatieMe
File Name  : SqList.h
Description: 线性表顺序存储结构[外部函数实现]
Author     : Gatie_Me
Version    : Copyright 2012
Data_Time  : 20112-8-29 10:28:43
Content    : 数据结构与算法（C++）版书上源码
********************************************************************************/

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
template <class ElemType>
void Read(ElemType &elem)
{
    cin >>elem;    //输入元素的信息
}

// 函数名称：template <class ElemType> void Write(const ElemType &e)
// 操作结果: 显示数据元素
template <class ElemType>
void Write(ElemType &elem)
{
    cout <<elem <<"  ";     //输出元素的信息
}

void Welcome( )    //选择1人与人对抗时候的场景信息
{
    const char *inFor[11];
    inFor[0] = "               ****************************************************              ";
    inFor[1] = "               *                                                  *              ";
    inFor[2] = "               *========Welcome To The Quick Hit World!!!=========*              ";
    inFor[3] = "               *                                                  *              ";
    inFor[4] = "               *The Result is Not Only You Win But Only Also I Win*              ";
    inFor[5] = "               *                                                  *              ";
    inFor[6] = "               *=======We All Hope That Which Is Said To Us=======*              ";
    inFor[7] = "               *                                                  *              ";
    inFor[8] = "               *===========Success Is Only The Begining===========*              ";
    inFor[9] = "               *                                                  *              ";
    inFor[10] = "              ****************************************************              ";

	int i,j;

	long start;

    cout <<endl <<endl;
    for ( i = 0; i < 11; i++ )        //循环11行
	{
		for ( j = 0; j < 68; j++ )           //循环每行68个字符
		{
			if( inFor[i][j] == ' ' )           //如果当前字符为空格
				cout <<( inFor[i][j] );
			else if( inFor[i][j]=='*' )              //如果当前字符为*
			{
				start = clock();
				while ( clock()-start < 20 );
                cout <<( *(inFor[i]+j) );
			}
			else                   //否则当前字符为英文字符
			{
				start = clock();
				while(clock()-start<300);
				cout <<( *(inFor[i]+j) ) <<"\a";
			}
		}
		cout <<endl;
	}

	cout <<"Press any key to continue..." <<endl;
	//while (!kbhit());
	getch();
    system("cls");
}


void Menu( )
{
    system("cls");
    const char *menu[9] = {
        "\t\t********************************************",
        "\t\t**        1 -=> 新建一整形线性表          **",
        "\t\t**        2 -=> 显示建立的线性表          **",
        "\t\t**        3 -=> 排序建立的线性表          **",
        "\t\t**     4 -=> 将线性表分成奇偶两部分       **",
        "\t\t**           5 -=> 删除元素               **",
        "\t\t**          6 -=> 清空线性表              **",
        "\t\t**          0 -=> 退出程序                **",
        "\t\t********************************************",
        };

    for(int i = 0; i < 9; i++)
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

void Stop( )        // 停止函数
{
    char answer;

    do
    {	// 循环直到用户输入恰当的回答为止
        cout << "(y, n)?";
        cout << "用y或n回答:";
        while ((answer = getchar( )) == '\n');	// 跳过空格,制表符及换行符获取一字符

    }while (answer != 'y' && answer != 'Y' && answer != 'n' && answer != 'N');

    #if (VERSION)     // 程序编译信息输出
    Version( );         // 显示程序的编译信息
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
}


void Version( )
{

    cout <<"\t\t**************************************************" <<endl;
    cout <<"\t\t**  Wacky Window (c) 2012 Wacky SoftWare. Inc.  **"<<endl;
    cout <<"\t\t**     Complied on " <<__DATE__ <<" at " <<__TIME__ <<"      **"<<endl;
    cout <<"\t\t**************************************************" <<endl;
    system("pause");

}
