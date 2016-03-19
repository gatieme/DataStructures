/********************************************************************************
CopyRight  : 2012-2013, HerBinUnversity, GatieMe
File Name  : Cnew【1.3.9有关C++的动态存储分配】
Description: newd的使用方法
Author     : Gatie_Me
Version    : Copyright 2012
Data_Time  : 20112-8-4 15:36:24
********************************************************************************/

/********************************************************************************
History    :修改历史记录列表, 每条修改记录应包括修改日期、修改者以及修改内容
********************************************************************************/


#ifndef _MSC_VER            //如果当前编译环境是VC
#if _MSC_VER == 1200      //表示当前环境版本号为VC6.0
#include <iostream.h>       //以此种方式包含cout
#else                       //否则其他VC版本
#include <iostream>         //以此种方式包含cout
using namespace std;
#endif                      //否则_MSC_VER判断结束, 戒指判断其他编译环境
#else                       //非VC编译环境
#include <iostream>
using namespace std;
#endif                      //结束判断

#include <fstream>
#include <cstdlib>
#include <cstring>

#define MAX_LINE_LENGTH 100


int main(int argc, char *argv[])
{
    cout <<"***********************************" <<endl;
    cout <<"**  CPludPlus's new and delete   **" <<endl;
    cout <<"***********************************" <<endl;

    ifstream *inFilePtr;
    char *strPtr, *strFileNamePtr;
    strPtr = new char[MAX_LINE_LENGTH];         //动态分配内存
    strFileNamePtr = new char[MAX_LINE_LENGTH]; //动态分配内存

    if(argc != 2)
    {
        cout <<"请输入您要显示的文本文件名" <<endl;
        cin >>strFileNamePtr;  //输入文件名
    }
    else
    {
        strcpy(strFileNamePtr, argv[1]);
    }

    inFilePtr = new ifstream(strFileNamePtr);
    if(inFilePtr == NULL)
    {
        cout <<"打开文件" <<strFileNamePtr <<"失败" <<endl;
        exit(1);    //非正常退出
    }

    while(!inFilePtr->eof())   //当文件inFilePtr未结束时循环
    {
          inFilePtr->getline(strPtr, MAX_LINE_LENGTH);  //读入一行字符
          cout <<strPtr <<endl;                         //显示一行字符
    }

    delete []strPtr;   //动态释放字符串
    delete []strFileNamePtr;//动态释放字符串
    delete []inFilePtr;   //动态释放字符串


    system("pause");

    return 0;
}

///函数注释
/**********************************************************************
Function      :      ///函数名称
Description   :      ///函数功能、性能等的描述
Calls         :      ///被本函数调用的函数清单
Called By     :      ///调用本函数的函数清单
Table Accessed:      ///被反问的表（此项仅对于牵扯到数据库操作的程序）
Table Update  :      ///被修改的表（此项仅对于牵扯到数据库操作的程序）
Input         :      ///对输入参数的说明, 包括每个参数的作用、取值说明及参数间的关系
Output        :      ///对输出参数的说明
Return        :      ///函数返回值的说明
Others        :      ///其他说明
**********************************************************************/
