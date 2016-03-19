/********************************************************************************
CopyRight  : 2012-2013, HerBinUnversity, GatieMe
File Name  : SqList.h
Description: 奖励一个整形int的顺序表, 设计算法将其调整为左右两部分
             左边部分全为奇数,右边部分全为偶数, 并且要求算法的时间复杂度为O(n)
Dssign     : 本题的主要思路如下：
                设置leftPosition = 1, rightPosition = list.length;
                list的第leftPosition个元素为leftItem, list的第rightPosition个元素为rightItem,
                当list左边的数leftItem为奇数时, 则leftPosition++;
                当list右边的数rightItem为偶数时, 则rightPosition--;
                而当list左边的数leftItem为偶数, 且右边的数rightItem为奇数时,
                就交换leftItem和rightItem, 同时leftPosition++, rightPosition--;
                直到leftPosition == rightPosition时为止;
                算法复杂度为O(n)
Author     : Gatie_Me
Version    : Copyright 2012
Data_Time  : 20112-8-29 10:28:43
Content    : 数据结构与算法（C++）版书上源码
********************************************************************************/


/********************************************************************************
History    :修改历史记录列表, 每条修改记录应包括修改日期、修改者以及修改内容
********************************************************************************/

#include <iostream>
#include "SqList.h"
using namespace std;


int main()
{
    cout <<"**********************************" <<endl;
    cout <<"**       Test Sqlist Of         **" <<endl;
    cout <<"**********************************" <<endl;
    cout << "Hello world!" << endl;

    SqList<int> list;   //创建一个整形顺序表

    int leftPosition = 1, rightPosition = list.Length( );   //下标标记信息
    int leftItem, rightItem;                                //标记数据

    while(leftPosition == rightPosition)
    {
        list.GetElem(leftPosition, leftItem);   //取出list左边的数据leftItem
        list.GetElem(rightPosition, rightItem); //取出list右边的数据rightItem
        if(leftItem % 2 == 1)   //如果左边的数leftItem是奇数
        {
            leftPosition++;    //符合结果要求, 于是将leftPosition右移到下一个数
        }
        if(rightPosition % 2 == 0)   //如果右边的数rightItem是偶数
        {
            rightPosition--;    //符合结果要求, 于是将rightPosition前移到上一个数
        }

        if(leftItem % 2 == 0 && rightItem % 2 == 1)  //如果list左边的数leftItem为偶数, 且右边的数rightItem为奇数
        {   //这种情况不满足结果要求需要 -=> 将两个数交换
            list.SetElem(leftPosition, rightItem);
            list.SetElem(rightPosition, leftItem);
        }
    }

    return 0;
}

