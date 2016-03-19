/********************************************************************************
CopyRight  : 2012-2013, HerBinUnversity, GatieMe
File Name  : 显示文本文件
Description: 显示文本文件
Author     : Gatie_Me
Version    : 版本声明
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

#include <fstream>          //包含文件流
#include <cstdlib>

const int MAX_LINE_LENGTH = 100;
//#define  MAX_LINE_LENGTH    100
//主函数
int main(int argc, char *argv[])  //
{
    cout <<"******************************" <<endl;
    cout<<"**       Show The File       **" <<endl;
    cout <<"******************************" <<endl;

    if(argc != 2)
    {
        cout <<"用法：ShowSFile文本文件名" <<endl;
        system("pause");                //调用库函数, 等待用户反应
        exit(1);                        //非正常退出1-主函数传参有误
    }

    ifstream inFile(argv[1]);     //输入文本文件
    if(inFile.fail())
    {
        cout <<"打开文件" <<argv[1] <<"失败!" <<endl;
        system("pause");                //调用库函数, 等待用户反应
        exit(2);                      //非正常退出2-打开文件失败
    }

    char str[MAX_LINE_LENGTH];
    inFile>>str;        //向文件中输入字符串

    while(inFile.eof())
    {
        cout <<str <<endl;        //输出字符串
        inFile>>str;              //输入字符串
    }

    inFile.close( );     //关闭文件


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
