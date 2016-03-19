/**
******************************************************************************
*  CopyRight  : 2012-2013, HerBinUnversity, GatieMe                          *
*  File Name  : Player.cpp                                                   *
*  Description: 玩家抽象接口类                                              *
*  Author     : Gatie_Me                                                     *
*  Version    : Copyright 2012 JULY_CITY                                     *
*  Data_Time  : 2012-11-6_10:21:43                                           *
*  Content    : 数据结构与算法（C++）版石头剪刀布                          *
******************************************************************************
**/


#include "Player.h"
#include <iostream>
#include <algorithm>
#include <iomanip>
using namespace std;

// 看用户是否输入了ye
bool SayYes( );




int Player::AddWinCount( )         // 获胜数目增加1
{
    return ++this->m_winCount;             // 获胜次数增加1
}

void Player::SetName(std::string name)             // 更改玩家的姓名
{
    this->m_name = name;
}


std::string Player::GetName( )                 // 获取玩家的姓名
{
    return this->m_name;                // 玩家的名字
}


int Player::GetWinCount( )             // 获取玩家的分数
{
    return this->m_winCount;               // 获取玩家的分数
}


void Player::ShowCharacter( )      // 显示玩家的性格
{
    if(this->m_character == Honest)
    {
        std::cout <<"诚实稳健" <<std::endl;
    }
    else
    {
        std::cout <<"滑稽贪玩" <<std::endl;
    }
}

SelectType Player::GetSelect( )        // 获取玩家的出拳信息
{
    return this->m_select;
}

bool Player::GetCharacter( )           // 获取玩家的性格信息
{
    return this->m_character;
}

void Player::ShowSelect( )         // 显示玩家的出拳信息
{
    switch((int)this->m_select)
    {
    case ROCK:
        std::cout <<"姓名：" <<std::setw(10)<<this->GetName( ) <<" 出拳：石头" <<std::endl;
        break;
    case SCISSOR:
        std::cout <<"姓名：" <<std::setw(10)<<this->GetName( ) <<" 出拳：剪刀" <<std::endl;
        break;
    case CLOTH:
        std::cout <<"姓名：" <<std::setw(10)<<this->GetName( ) <<"出拳：布子" <<std::endl;
        break;
    case NULLOUT:
        std::cout <<"姓名：" <<std::setw(10)<<this->GetName( ) <<"选择不出" <<std::endl;
        break;
    }

}


bool Player::SelectCharacter( )        // 修改任务的性格
{
    std::cout <<std::endl;
    std::cout <<"******************************************" <<std::endl;
    std::cout <<"**请问你是否同意以一个诚实的玩家参加游戏**" <<std::endl;
    std::cout <<"**诚实的玩家出空拳会被游戏认为是误操作..**" <<std::endl;
    std::cout <<"******************************************" <<std::endl;
    if(SayYes( ) == true)
    {
        this->m_character = Honest;     // 诚实的玩家
    }
    else
    {
        this->m_character = Funny;      // 滑稽的玩家
    }

    return this->m_character;
}

int Player::AddTotalCount( )      // 获胜总计
{
    this->m_totalCount += this->m_winCount;

    return this->m_totalCount;
}


int Player::GetTotalCount( )
{
    return this->m_totalCount;
}
