/**
******************************************************************************
*  CopyRight  : 2012-2013, HerBinUnversity, GatieMe                          *
*  File Name  : Gaming.h                                                     *
*  Description: 其它接口部分                                                *
*  Author     : Gatie_Me                                                     *
*  Version    : Copyright 2012 JULY_CITY                                     *
*  Data_Time  : 2012-11-6_10:21:43                                           *
*  Content    : 数据结构与算法（C++）版石头剪刀布                          *
******************************************************************************
**/


#ifndef GAMING_H_INCLUDED
#define GAMING_H_INCLUDED


typedef enum SelectType
{

    ROCK = 1, // ²¼
    SCISSOR = 2, // ¼ôµ¶
    CLOTH = 3,  //
    NULLOUT = 4,
}SelectType;


typedef enum ResultType
{
    TIE = 0,    // Æ½¾Ö
    WIN = 1,    // Ó®
    LOSE = 2,   // Êä
}ResultType;



#endif // GAMING_H_INCLUDED
