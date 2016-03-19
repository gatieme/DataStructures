/**
******************************************************************************
*  CopyRight  : 2012-2013, HerBinUnversity, GatieMe                          *
*  File Name  : main.cpp                                                     *
*  Description: 主函数为文件                                                *
*  Author     : Gatie_Me                                                     *
*  Version    : Copyright 2012 JULY_CITY                                     *
*  Data_Time  : 2012-11-6_10:21:43                                           *
*  Content    : 数据结构与算法（C++）版石头剪刀布                          *
******************************************************************************
**/

#include <iostream>

#include <stdlib.h>
#include "Game.h"

using namespace std;

int main( )
{

//    for(int i = 1; i < 4; i++)
//    {
//        for(int j = 1; j < 4; j++)
//        {
//            cout <<(j - i+4)%3 - 1 <<endl;
//        }
//    }
    Game game;

//game.InitGame( );
    //game.PlayGame( );
    game.Gaming( );
    return EXIT_SUCCESS;
}
