/**
******************************************************************************
*  CopyRight  : 2012-2013, HerBinUnversity, GatieMe                          *
*  File Name  : Game.h                                                       *
*  Description: 游戏控制类                                                *
*  Author     : Gatie_Me                                                     *
*  Version    : Copyright 2012 JULY_CITY                                     *
*  Data_Time  : 2012-11-6_10:21:43                                           *
*  Content    : 数据结构与算法（C++）版石头剪刀布                          *
******************************************************************************
**/

#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED




#include "Gaming.h"
#include "PersonPlayer.h"
#include "ComputerPlayer.h"

class Game
{
   public :         // 公共函数结构
    Game( ):m_person( ), m_computer( )
    {
        this->m_gameCount = 0;
        this->m_timeCount = 0;
    }   // 构造函数

    virtual ~Game( ){ };            // 析构函数

    void InitGame( );            // 初始化游戏信息

    int Menu( );                // 游戏菜单

    void Help( );                // 帮助信息

    void PlayGame( );            // 进行游戏的函数

    void EndGame( );             // 游戏结束

    int DisResult( );         // 显示比赛结果

    void ShowResult( );      //

    void Gaming( );         // 整个游戏运行过程
protected :         // 保护数据成员以及函数信息
    // 函数成员
    void InitComPuter( );               // 初始化滑稽的电脑

    void InitPerson( );              // 初始化诚实的电脑

    void Delay( );

    void Stop( );
    void Lording( );
    // 数据成员
    PersonPlayer m_person;              // 玩家信息
    ComputerPlayer m_computer;          // 电脑信息
    int m_gameCount;                    // 游戏次数
    int m_timeCount;                  //   回合次数
};
#endif // GAME_H_INCLUDED
