/********************************************************************************
CopyRight  : 2012-2013, HerBinUnversity, GatieMe
File Name  : SqList.h
Description: 顺序栈主函数源代码文件
Author     : Gatie_Me
Version    : Copyright 2012
Data_Time  : 20112-8-29 10:28:43
Content    : 数据结构与算法（C++）版书上源码
********************************************************************************/
#include <iostream>
#include <ctime>
#include <windows.h>
#include <cstdlib>
#include <cstdio>
#include <iomanip>
#include <fstream>


#include "TriSparseMatrix.h"
using namespace std;

#define SIZE 81



/// 外部函数（所在文件Other.cpp）
void Welcome( );        // 欢迎函数
void Menu( );       // 菜单显示函数
void Delay( );      // 延时函数
void Lording( );    // 载入函数
void Stop( );       // 终止函数


void ShowMatrix(TriSparseMatrix<int> &matrix);      // 输出稀疏矩阵的信息
void ReadMatrix(TriSparseMatrix<int> &matrix);  // 从文件中读取稀疏矩阵的信息
void WriteMatrix(TriSparseMatrix<int> &matrix); // 向文件中写入稀疏矩阵的信息
void SetMatrixData(TriSparseMatrix<int> &matrix);  // 测试4更改数据
void OperatorMatrix( );         // 运算矩阵
/// 主函数
int main( )
{
    // 调试状态下的输出信息
    #ifdef DEBUG           // 如果宏定义了DEBUG, 执行一下语句
    cout <<"\t\tHello World*****************************************" <<endl;
    cout <<"\t\t**              Now Start Debug                   **" <<endl;
    cout <<"\t\t*****************************************Hello World" <<endl;
    #endif

    // 非调试状态下的输出信息
    #ifndef DEBUG        // 如果宏定义了DEBUG, 执行一下语句
    cout <<"\t\t**************************************************** " <<endl;
    cout <<"\t\t**           Test TriSparseMatrix Of              **" <<endl;
    cout <<"\t\t****************************************************" <<endl;
    #endif

    Welcome( );         // 欢迎界面

    // 程序初始化部分
    int choice, rows/*行*/, cols/*列*/, size, temp;

    TriSparseMatrix<int> matrix;         // 矩阵函数
    TriSparseMatrix<int> newMatrix;
    Lording( );         // 载入函数

    while( 1 )
    {

        Menu( );        // 系统菜单

        cin >>choice;         //输入您的选择
        system("cls");
        switch(choice)
        {
          /// 1 -=> 建立稀疏矩阵
          case 1:
            // 系统信息提示
            cout <<"\t\t******************************************" <<endl;
            cout <<"\t\t**   您当前的选择 1 -=> 建立稀疏矩阵    **" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl <<endl;

            // 程序测试部分
            cout <<"请输入稀疏矩阵的行row和列col数据:" <<endl;
            cout <<"ROWS = ";
            cin >>rows;
            cout <<"COLS = ";
            cin >>cols;
            matrix.SetMatrix(rows, cols);       // 更改原矩阵的行列和元素个数信息
            cout <<endl <<"已经更新自矩阵信息" <<endl;
            cout <<"当前矩阵Matrix行：" <<matrix.Rows() <<", 列：" <<matrix.Cols( ) <<", 当前非0元素个数：" <<matrix.Size( ) <<endl <<endl;

            // 系统信息提示
            cout <<"\t\t******************************************" <<endl;
            cout <<"\t\t**              矩阵建立完毕            **" <<endl;
            cout <<"\t\t**             即将返回主菜单           **" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl;
            cout <<"Please ent any key to continue........................" <<endl;
            //getchar( );
            system("pause");
            break;

          /// 2 -=> 从文件读取稀疏矩阵
          case 2:
            // 系统提示信息
            system("cls");
            cout <<"\t\t********************************************" <<endl;
            cout <<"\t\t**  您当前的选择2 -=> 从文件读取稀疏矩阵  **" <<endl;
            cout <<"\t\t********************************************" <<endl <<endl <<endl;

            // 程序测试部分
            ReadMatrix(matrix);

            // 系统提示信息
            cout <<"\t\t********************************************" <<endl;
            cout <<"\t\t**              矩阵读入完毕              **" <<endl;
            cout <<"\t\t**             即将返回主菜单             **" <<endl;
            cout <<"\t\t********************************************" <<endl <<endl;
            cout <<"Please ent any key to continue........................" <<endl;
            system("pause");
            break;

          /// 3 -=> 输出稀疏矩阵
          case 3:
            // 系统提示信息
            cout <<"\t\t******************************************" <<endl;
            cout <<"\t\t**   您当前的选择 3 -=> 输出稀疏矩阵    **" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl <<endl;


            ShowMatrix(matrix);

            // 系统提示信息
            cout <<"\t\t******************************************" <<endl;
            cout <<"\t\t**              矩阵输出完毕            **" <<endl;
            cout <<"\t\t**             即将返回主菜单           **" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl;
            cout <<"Please ent any key to continue........................" <<endl;
            system("pause");
            break;

          /// 4 -=> 更改矩阵数据
          case 4:
            // 系统提示信息
            system("cls");
            cout <<"\t\t******************************************" <<endl;
            cout <<"\t\t**    您当前的选择4 -=> 更改矩阵数据    **" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl <<endl;

            // 程序测试部分

            SetMatrixData(matrix);

            // 系统提示信息
            cout <<"\t\t******************************************" <<endl;
            cout <<"\t\t**              数据更改完毕            **" <<endl;
            cout <<"\t\t**             即将返回主菜单           **" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl;
            cout <<"Please ent any key to continue........................" <<endl;
            system("pause");
            break;



          /// 5 -=> 将稀疏矩阵的数据存入文件
          case 5:
            // 系统提示信息
            system("cls");
            cout <<"\t\t******************************************" <<endl;
            cout <<"\t\t**您当前的选择 5 -=> 将稀疏矩阵存入文件 **" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl <<endl;

            WriteMatrix(matrix);
            // 程序测试部分

            // 系统提示信息
            cout <<"\t\t******************************************" <<endl;
            cout <<"\t\t**              数据存储完毕            **" <<endl;
            cout <<"\t\t**             即将返回主菜单           **" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl;
            cout <<"Please ent any key to continue........................" <<endl;
            system("pause");
            break;

          /// 6 -=> 将稀疏矩阵转置
          case 6:
            // 系统提示信息
            system("cls");
            cout <<"\t\t******************************************" <<endl;
            cout <<"\t\t**   您当前的选择 6 -=> 将稀疏矩阵转置  **" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl <<endl;
            rows = matrix.Rows( );
            cols = matrix.Cols( );
            size = matrix.Size( );
            cout <<"当前矩阵Matrix行：" <<rows <<", 列：" <<cols <<", 非0元素个数：" <<size <<endl <<endl;

            cout <<"转置前的矩阵信息" <<endl <<endl;
            ShowMatrix(matrix);
            newMatrix.SetMatrix(rows, cols);
            //TriSparseMatrix<int>::FastTranspose(newMatrix, matrix);
            TriSparseMatrix<int>::SimpleTranspose(newMatrix, matrix);
            cout <<"转置前的矩阵信息" <<endl <<endl;
            ShowMatrix(newMatrix);
            // 程序测试部分

            // 系统提示信息
            cout <<"\t\t******************************************" <<endl;
            cout <<"\t\t**              矩阵转置完毕            **" <<endl;
            cout <<"\t\t**             即将返回主菜单           **" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl;
            cout <<"Please ent any key to continue........................" <<endl;
            system("pause");
            break;

          /// 7 -=> 矩阵的运算
          case 7:
            // 系统提示信息
            system("cls");
            cout <<"\t\t******************************************" <<endl;
            cout <<"\t\t**     您当前的选择 7 -=> 矩阵的运算    **" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl <<endl;

            // 程序测试部分
            OperatorMatrix( );
            // 系统提示信息
            cout <<"\t\t******************************************" <<endl;
            cout <<"\t\t**              矩阵运算完毕            **" <<endl;
            cout <<"\t\t**             即将返回主菜单           **" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl;
            cout <<"Please ent any key to continue........................" <<endl;
            system("pause");
            break;
          /// 0 -=> 退出程序
          case 0:
            // 系统提示信息
            cout <<"\t\t******************************************" <<endl;
            cout <<"\t\t**              数据插入完毕            **" <<endl;
            cout <<"\t\t**             即将返回主菜单           **" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl;
            cout <<"Please ent any key to continue........................" <<endl;          // 系统提示信息

            Stop( );

            Lording( );         // 载入函数
        }
    }

    return 0;
}

void ShowMatrix(TriSparseMatrix<int> &matrix)
{
    int rows, cols, size, temp;
    rows = matrix.Rows( );      // 获取行信息
    cols = matrix.Cols( );      // 获取列信息
    size = matrix.Size( );

    cout <<"当前矩阵Matrix行：" <<rows <<", 列：" <<cols <<", 非0元素个数：" <<size <<endl <<endl;

    for(int row = 1; row <= rows; row++)
    {
        for(int col = 1; col <= cols; col++)
        {
            matrix.GetElem(row, col, temp);    // 更改数据
            printf("%4d", temp);
        }
        cout <<endl;
    }
    cout <<endl <<endl;
}

void ReadMatrix(TriSparseMatrix<int> &matrix)
{
    int choice, rows, cols, temp, size;
    char fName[SIZE];
    FILE *fpi/*输入文件*/;

    cout <<"****************************" <<endl;
    cout <<"** 1 -=> 文件中存储三元组 **" <<endl;
    cout <<"**2 -=> 文件中存储稀疏矩阵**" <<endl;
    cout <<"****************************" <<endl;
    cout <<"Please entere your choic...." <<endl;
    cin >>choice;
    switch(choice)
    {
      // 如果文件中存储的是三元组序列
      case 1:
        strcpy(fName, "InTriple.txt");    // 设置文件名
        if((fpi = fopen(fName, "r")) == NULL)   // 打开文件并判断打开是否成功
        {
            printf("can't open the input file %s", fName);
            exit(-1);
        }
        fscanf(fpi, "%d%d%d", &rows, &cols, &size);
        matrix.SetMatrix(rows, cols);       // 更改原矩阵的行列和元素个数信息
        cout <<endl <<"已经更新自矩阵信息" <<endl;
        cout <<"当前矩阵Matrix行：" <<matrix.Rows() <<", 列：" <<matrix.Cols( ) <<endl <<endl;
        while( 1 )
        {
            if(fscanf(fpi, "%d%d%d", &rows, &cols, &temp) == EOF) // 读入数据
            {
                break;
            }
            if(matrix.SetElem(rows, cols, temp) == true)       // 更改数据
            {
                cout <<"程序状态, 数据更新成功..." <<endl;
            }
            else
            {
                cout <<"程序状态, 数据更新失败..." <<endl;
            }
//            if(feof(fpi) == true)
//            {
//                break;
//            }
        }
        cout <<"当前矩阵Matrix行：" <<matrix.Rows() <<", 列：" <<matrix.Cols( ) <<", 非0元素个数：" <<matrix.Size( ) <<endl <<endl;
        fclose(fpi);
        break;

      // 如果文件中存储的是矩阵的信息
      case 2:
        strcpy(fName, "InMatrix.txt");    // 设置文件名
        if((fpi = fopen(fName, "r")) == NULL)   // 打开文件并判断打开是否成功
        {
            printf("can't open the input file %s", fName);
            exit(-1);
        }
        fscanf(fpi, "%d%d%d", &rows, &cols, &size);
        matrix.SetMatrix(rows, cols);       // 更改原矩阵的行列和元素个数信息
        cout <<endl <<"已经更新自矩阵信息" <<endl;
        cout <<"当前矩阵Matrix行：" <<matrix.Rows() <<", 列：" <<matrix.Cols( ) <<", 非0元素个数：" <<matrix.Size( ) <<endl <<endl;

        for(int row = 1; row <= rows; row++)
        {
            for(int col = 1; col <= cols; col++)
            {
                if(fscanf(fpi, "%d", &temp) == EOF)
                {
                    break;
                }
                if(temp != 0)
                {
                    matrix.SetElem(row, col, temp);      // 更改数据
                    cout <<"设置的数据" <<temp <<endl <<endl;
                }
            }
        }
        fclose(fpi);
        //break;
      default:
        cout <<"选择错误" <<endl;
    }
}


void WriteMatrix(TriSparseMatrix<int> &matrix)
{
    char fName[SIZE];
    int rows, cols, size, temp;
    FILE *fpo/*输出文件*/;

    strcpy(fName, "OutMatrix.txt");
    rows = matrix.Rows( );
    cols = matrix.Cols( );
    size = matrix.Size( );

    if((fpo = fopen(fName, "w")) == NULL)
    {
        printf("can't open the output file\n");
        exit(-1);
    }

    fprintf(fpo, "矩阵的ROW = %d, COL = %d, SIZE = %d, MAXSIZE = %d:\n", rows, cols, size, rows*cols);
    Triple<int> triple;
    fprintf(fpo, "矩阵的三元组序列信息为:\n");
    for(int pos = 1; pos <= size; pos++)
    {
        triple = matrix.GetTriple(pos);     // 获取第pos个三元组的信息
        fprintf(fpo, "[%2d,%2d,%2d]\n", triple.m_row, triple.m_col, triple.m_data);
    }
    for(int row = 1; row <= rows; row++)
    {
        for(int col = 1; col <= cols; col++)
        {
            matrix.GetElem(row, col, temp);      // 更改数据
            fprintf(fpo, "%4d", temp);
        }
        fprintf(fpo, "\n");
    }

    cout <<"已经将矩阵存入矩阵" <<endl <<endl;

    fclose(fpo);
}

// 更改矩阵的数据
void SetMatrixData(TriSparseMatrix<int> &matrix)
{
    int rows, cols, temp;
    cout <<"数据输入[行或者列输入0或者遇见文件末尾标志Ctrl+Z结束]";
    while( 1 )
    {
        // 用户输入数据
        cout <<"请输入数据的位置和数据" <<endl;        // 输入信息
        cout <<"ROW = ";
        if(scanf("%d", &rows) == EOF || rows == 0)
        {
            cout <<endl <<"用户终止输入" <<endl;
            break;
        }
        cout <<"COL = ";
        if(scanf("%d", &cols) == EOF || cols == 0)
        {
            cout <<endl <<"用户终止输入" <<endl;
            break;
        }
        cout <<"DATA = ";
        if(scanf("%d", &temp) == EOF)
        {
            cout <<endl <<"用户终止输入" <<endl;
            break;
        }

        // 系统更改信息
        if(matrix.SetElem(rows, cols, temp) == true)       // 更改数据
        {
            cout <<"程序状态, 数据更新成功..." <<endl;
        }
        else
        {
            cout <<"程序状态, 数据更新失败..." <<endl;
        }
    }
}


void OperatorMatrix( )
{
    int choice;
    TriSparseMatrix<int> leftMatrix;
    TriSparseMatrix<int> rightMatrix;
    TriSparseMatrix<int> matrix;

    ReadMatrix(leftMatrix);
    ShowMatrix(leftMatrix);
    ReadMatrix(rightMatrix);
    ShowMatrix(rightMatrix);

    cout <<"****************************" <<endl;
    cout <<"**   1 -=> 两个矩阵相加   **" <<endl;
    cout <<"**   2 -=> 两个矩阵相减   **" <<endl;
    cout <<"****************************" <<endl;
    cout <<"Please entere your choic...." <<endl;

    cin >>choice;
    switch(choice)
    {
        case 1:
           matrix = (leftMatrix + rightMatrix);
           break;
        case 2:
           matrix = (leftMatrix - rightMatrix);
           break;
    }
    ShowMatrix(matrix);
}
