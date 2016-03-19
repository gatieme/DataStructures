/**
******************************************************************************
*  CopyRight  : 2012-2013, HerBinUnversity, GatieMe                          *
*  File Name  : ComputerPlayer.h                                             *
*  Description: 电脑玩家定义文件                                            *
*  Author     : Gatie_Me                                                     *
*  Version    : Copyright 2012 JULY_CITY                                     *
*  Data_Time  : 2012-11-6_10:21:43                                           *
*  Content    : 数据结构与算法（C++）版石头剪刀布                          *
******************************************************************************
**/



#ifndef COMPUTERPLAYER_H_INCLUDED
#define COMPUTERPLAYER_H_INCLUDED


#include "Player.h"



class ComputerPlayer : public Player
{
    public :
    ComputerPlayer( )       // 构造函数
    :Player( )
    {

    }

    virtual ~ComputerPlayer( ){ };  // 析构函数

    void InitPlayer( );       // 基类虚函数

    SelectType Select( );       // 基类虚函数
};

#endif // COMPUTERPLAYER_H_INCLUDED
