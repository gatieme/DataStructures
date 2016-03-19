/**
******************************************************************************
*  CopyRight  : 2012-2013, HerBinUnversity, GatieMe                          *
*  File Name  : Game.cpp                                                     *
*  Description: 游戏控制类                                                  *
*  Author     : Gatie_Me                                                     *
*  Version    : Copyright 2012 JULY_CITY                                     *
*  Data_Time  : 2012-11-6_10:21:43                                           *
*  Content    : 数据结构与算法（C++）版石头剪刀布                          *
******************************************************************************
**/

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstdio>
#include "Game.h"



bool SayYes( );
void Game::InitComPuter( )               // 初始化滑稽的电脑
{
    this->m_computer.InitPlayer( );
}

void Game::InitPerson( )              // 初始化诚实的电脑
{
    this->m_person.InitPlayer( );
    std::cout <<"您的注册姓名: " <<this->m_person.GetName( ) <<std::endl;
    this->m_gameCount = 0;
    system("pause");
    system("cls");
}

void Game::Delay( )
{
    for(int i = 0; i < 1000000; i++);
}

// 载入函数
void Game::Lording( )
{
    system("cls");

    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 100000000; j++);
        std::cout <<"□";
    }
    std::cout <<std::endl;

    system("cls");
}

void Game::Stop( )        // 停止函数
{
    char answer;

    do
    {	// 循环直到用户输入恰当的回答为止
        std::cout << "(y, n)?";
        std::cout << "用y或n回答:";
        while ((answer = getchar( )) == '\n');	// 跳过空格,制表符及换行符获取一字符

    }while (answer != 'y' && answer != 'Y' && answer != 'n' && answer != 'N');

    //#if (VERSION)     // 程序编译信息输出
    //Version( );         // 显示程序的编译信息
  //  #endif

    if(answer == 'y' || answer == 'Y')
    {
    std::cout <<"**********************" <<std::endl;
    std::cout <<"**玩家选择结束了游戏**" <<std::endl;
    std::cout <<"**********************" <<std::endl;
        exit(0);
    }
    else
    {
        std::cout <<"用户取消" <<std::endl;
    }
}

void Game::InitGame( )            // 初始化游戏信息
{
    if(this->m_person.GetName( ) == "NULLNAME")
    {
        this->m_person.InitPlayer( );       // 初始化玩家信息
    }

    this->m_person.SelectCharacter( );

    this->m_computer.InitPlayer( );     // 初始化电脑信息

    std::cout <<std::endl <<"********************" <<std::endl;
    std::cout <<"**参加游戏玩家信息**" <<std::endl;
    std::cout <<"姓名：" <<std::setw(10)<<this->m_person.GetName( ) <<"性格：";
    this->m_person.ShowCharacter( );
    std::cout <<"姓名：" <<std::setw(10)<<this->m_computer.GetName( ) <<"性格：";
    this->m_computer.ShowCharacter( );
    std::cout <<"********************" <<std::endl;

    this->m_timeCount = 0;      // 游戏计数器进1
}

int Game::Menu( )                // 游戏菜单
{

    system("cls");
    int choice;
    const int SIZE = 6;
    const char *menu[SIZE] = {
        "\t\t********************************************",
        "\t\t**             1 -=> 游戏注册             **",
        "\t\t**             2 -=> 进行游戏             **",
        "\t\t**             3-=>  游戏帮助             **",
        "\t\t**          0 -=> 退出程序                **",
        "\t\t********************************************",
        };

    for(int i = 0; i < SIZE; i++)
    {
        for(int j = 0; menu[i][j] != '\0'; j++)
        {
            std::cout <<menu[i][j];
        }
        std::cout <<std::endl;
    }
    std::cout <<"请输入您的选择" <<std::endl;

    while( 1 )
    {
        std::cin >>choice;
        if(choice >= 0 && choice < 4)
        {
            break;
        }
        std::cout <<"输入错误,请重新输入" <<std::endl;
    }
    //system("cls");
    this->Lording( );

    return choice;
}


void Game::Help( )                // 帮助信息
{
    std::cout <<"=====================游戏帮助菜单=====================" <<std::endl;

    std::cout <<"==============游戏开始之前需要先进行注册==============" <<std::endl;

    std::cout <<"=注册以后可以开始游戏, 游戏过程中玩家选择加入一名电脑=" <<std::endl;

    std::cout <<"=========玩家和电脑均可以以两种身份加入游戏:.=========" <<std::endl;\
    std::cout <<"1-=>诚实稳重的    2-=>滑稽贪玩的" <<std::endl;
    std::cout <<"诚实稳重：以这种身份加入游戏,　在出拳时是不可以出空拳的," <<std::endl;
    std::cout <<"          如果玩家除了空拳, 会被系统认为是误操作, 而要求再次输入" <<std::endl;
    std::cout <<"滑稽贪玩：这种身份的玩家或者电脑, 可以出空拳, " <<std::endl;
    std::cout <<"因此键入其他的键, 是会被任务是除了空拳的" <<std::endl;


    std::cout <<"Please enter any key to continue" <<std::endl;
    system("pause");
    system("cls");
}


void Game::PlayGame( )            // 进行游戏的函数
{
    this->InitGame( );          // 游戏初始化
    while( 1 )
    {
        this->m_computer.Select( );     // 电脑出拳
        this->m_person.Select( );       // 玩家出拳

        this->ShowResult( );            // 结果判断
        std::cout <<std::endl <<"**请问你是否继续**" <<std::endl;
        this->m_timeCount++;        // 回合计数器进1
        if(SayYes( ) == false)
        {
            break;
        }
    }
    this->m_gameCount++;            // 没进行一场游戏游戏计数器进1
    this->m_person.AddTotalCount( );
    this->m_computer.AddTotalCount( );
    std::cout <<"本回合结束" <<std::endl;
    std::cout <<"共计进行" <<std::setw(2)<<this->m_gameCount <<"场比赛, 本场" <<this->m_timeCount <<"回合" <<std::endl;
    std::cout <<"玩家" <<this->m_person.GetName( );
    std::cout <<"本场获胜" <<this->m_person.GetWinCount( ) <<"回合, 总计获胜" <<this->m_person.GetTotalCount( ) <<"回合" <<std::endl <<std::endl;
    system("pause");
}


void Game::EndGame( )             // 游戏结束
{
    this->Stop( );

    system("pause");
}


int Game::DisResult( )         // 显示比赛结果
{   // 1玩家赢, -1电脑赢, 0平局
    //   石头 > 剪刀 > 布 》 石头
    //   1      2      3      1
    //%2  1     0
    // return = （man - computer+4）%3 - 1
//    11    0
//    12  3  >
//    13  4  <
//    21  3  <
//    22  4  0
//    23  5  >
//    31  4  >
//    32  5  <
//    33  6  0
    std::cout <<std::endl <<"RESULT :" <<std::endl;
    std::cout <<"****************************************" <<std::endl;
    this->m_person.ShowSelect( );
    this->m_computer.ShowSelect( );

    if(this->m_computer.GetSelect( ) == NULLOUT
       //&& this->m_computer.GetCharacter( ) == Funny
       && this->m_person.GetSelect( )  != NULLOUT)       // 滑稽的电脑出了空拳但是玩家没有出空拳
    {

        //std::cout <<"**************************************" <<std::endl;
        std::cout <<"电脑" <<std::setw(10)<<this->m_computer.GetName( ) <<"刚刚开了一个玩笑" <<std::endl;
        //std::cout <<"**************************************" <<std::endl;

        return 1;       // 判定电脑输了
    }
    else if(this->m_person.GetSelect( ) == NULLOUT
       //&& this->m_person.GetCharacter( ) == Funny
       && this->m_computer.GetSelect( ) != NULLOUT)     // 滑稽的玩家出了空拳但是电脑没有出空拳
    {
        //this->m_computer.ShowSelect( );
        std::cout <<"您可真能玩, 你出空拳可是会输掉的" <<std::endl;
        return -1;       // 判断玩家输了
    }
    else if(this->m_computer.GetSelect( ) == NULLOUT        // 玩家和电脑都出了空拳
         && this->m_person.GetSelect( ) == NULLOUT)
    {

        std::cout <<"你们再这样系统可就死机了" <<std::endl;
        return 0;               // 平局吧
    }
    else
    {
        //this->m_person.ShowSelect( );       // 显示玩家出拳
        //this->m_computer.ShowSelect( );     // 显示电脑出拳
        return ((this->m_computer.GetSelect( ) - this->m_person.GetSelect( ) + 4) % 3 - 1);     // 返回结果
    }

}

void Game::ShowResult( )      //
{
    std::cout <<std::endl;
    switch(this->DisResult( ))
    {
    case -1:
        //std::cout <<"****************************************" <<std::endl;
        std::cout <<"==========" <<std::setw(10)<<this->m_computer.GetName( ) <<"WIN...==========*" <<std::endl;
        std::cout <<"看来你技术是真的不行啊......." <<std::endl;
        std::cout <<"****************************************" <<std::endl;
        this->m_computer.AddWinCount( );
        break;
    case  0:
        //std::cout <<"****************************************" <<std::endl;
        std::cout <<"==========平局==========" <<std::endl;
        std::cout <<"你们两个搞什么呢, 老是这样我们怎么赚钱啊" <<std::endl;
        std::cout <<"****************************************" <<std::endl;
        break;
    case  1:
        //std::cout <<"****************************************" <<std::endl;
        std::cout <<"==========" <<std::setw(10)<<this->m_person.GetName( ) <<"WIN...==========" <<std::endl;
        std::cout <<"你真是大神级别...." <<std::endl;
        std::cout <<"****************************************" <<std::endl;
        this->m_person.AddWinCount( );
        break;
    }
}


void Game::Gaming( )         // 整个游戏运行过程
{
    while( 1 )
    {
        int choice = this->Menu( );      // 显示游戏菜单
        switch(choice)
        {
        case 1:
            this->InitPerson( );        // 注册玩家信息
            system("cls");

            break;
        case 2:
            this->PlayGame( );          // 游戏进行
            break;
        case 3:
            this->Help( );
            break;
        case 0:
            this->EndGame( );
            break;
        default:
            break;
        }
    }
}
