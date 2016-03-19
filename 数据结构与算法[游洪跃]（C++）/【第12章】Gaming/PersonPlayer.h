/**
******************************************************************************
*  CopyRight  : 2012-2013, HerBinUnversity, GatieMe                          *
*  File Name  : PersonPlayer.h                                               *
*  Description: 人物玩家定义文件                                            *
*  Author     : Gatie_Me                                                     *
*  Version    : Copyright 2012 JULY_CITY                                     *
*  Data_Time  : 2012-11-6_10:21:43                                           *
*  Content    : 数据结构与算法（C++）版石头剪刀布                          *
******************************************************************************
**/


#ifndef PERSONPLAYER_H_INCLUDED
#define PERSONPLAYER_H_INCLUDED


#include "Player.h"

class PersonPlayer : public Player
{
    public :
    PersonPlayer( )         // 构造函数
    :Player( )
    {
    }

    virtual ~PersonPlayer( ){ }       // 析构函数

    void InitPlayer( );         // 玩家信息初始化

    // 玩家选择自己的出拳
    SelectType Select( );

    protected:
    bool CheckSelect(char temp);            // 看用户输入是否合法
};

#endif // PERSONPLAYER_H_INCLUDED
