/**
******************************************************************************
*  Copymatrix  : 2012-2013, HerBinUnversity, GatieMe                          *
*  File Name  : TriSparseMatrix<ElemType>.h                                  *
*  Description: 三元组顺序表[稀疏矩阵]类TriSparseMatrix<ElemType>头文件     *
*  Author     : Gatie_Me                                                     *
*  Version    : Copyright 2012 JULY_CITY                                     *
*  Data_Time  : 23/10/12 10:23                                               *
*  Content    : 数据结构与算法（C++）版书上源码                             *
******************************************************************************
**/

#ifndef TRISPARSEMATRIX_H_INCLUDED
#define TRISPARSEMATRIX_H_INCLUDED


#include "Triple.h"


#define  ROW_SIZE  10
#define  COL_SIZE  10
#define  NUM_SIZE   0


/// 三元组顺序表[稀疏矩阵]类TriSparseMatrix<ElemType>声明部分
template <class ElemType>
class TriSparseMatrix       /// 带头结点
{
/*===========================【PUBLIC：公共接口】============================*/
  public :      // 公共接口
    // 三元组顺序表[稀疏矩阵]类基本成员函数
    TriSparseMatrix(int rows = ROW_SIZE, int cols = COL_SIZE, int size = NUM_SIZE);// 构造函数

    TriSparseMatrix(const TriSparseMatrix<ElemType> &copy);     // 复制构造函数

    virtual ~TriSparseMatrix( );

    TriSparseMatrix<ElemType> &operator=(const TriSparseMatrix<ElemType> &copy);
    // 三元组顺序表[稀疏矩阵]类特征成员函数
    int Rows( ) const;       // 获取稀疏矩阵的行数

    int Cols( ) const;       // 获取稀疏矩阵的列数

    int Size( ) const;       // 获取稀疏矩阵的元素个数

    Triple<ElemType> GetTriple(int index);      // 获取第index个三元组的信息

    bool IsTripleIn(int row, int col) const;        // 判断当前位置是否在序列中,也就是当前位置数据是否不为0

    void SetMatrix(int rows, int cols);       // 重新设置当前矩阵的信息

    bool SetElem(int row, int col, const ElemType &elem);  // 设置对应row行col列元素的值

    bool GetElem(int row, int col, ElemType &elem) const;     // 获取对应row行col列元素的值

    // 稀疏矩阵转置函数函数
    static void SimpleTranspose(TriSparseMatrix<ElemType> &dest, const TriSparseMatrix<ElemType> &source);
    static void FastTranspose(TriSparseMatrix<ElemType> &dest, const TriSparseMatrix<ElemType> &source);

    TriSparseMatrix<ElemType> operator+(const TriSparseMatrix<ElemType> &matrix);
    TriSparseMatrix<ElemType> operator-(const TriSparseMatrix<ElemType> &matrix);
    // 重载矩阵的加减法运算
    //friend TriSparseMatrix<ElemType> operator+(const TriSparseMatrix<ElemType> &this, const TriSparseMatrix<ElemType> &right);
    //friend TriSparseMatrix<ElemType> operator-(const TriSparseMatrix<ElemType> &this, const TriSparseMatrix<ElemType> &right);
/*===========================【PUBLIC：公共接口】============================*/
///////////////////////////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////////
/*=========================【PROTECTED：保护成员】===========================*/
  protected :
    // 三元组顺序表[稀疏矩阵]类数据成员
    int m_rows, m_cols, m_size;         // 稀疏矩阵的行数, 列数以及非0元素的个数
    int m_maxSize;                    // 稀疏矩阵的最大元素个数
    Triple<ElemType> *m_triElems;   // 存储稀疏矩阵元素的三元素数组地址
/*=========================【PROTECTED：：保护成员】=========================*/
};



/// 三元组顺序表[稀疏矩阵]类TriSparseMatrix<ElemType>实现部分
/**三元组顺序表[稀疏矩阵]类基本成员函数[实现]************************************************
    TriSparseMatrix<ElemType>(int rows = ROW_SIZE, int cols = COL_SIZE, int size = NUM_SIZE);// 构造函数
    TriSparseMatrix<ElemType>(const TriSparseMatrix<ElemType> &copy);     // 复制构造函数
    virtual ~TriSparseMatrix<ElemType>( );
    TriSparseMatrix<ElemType> &operator=(const TriSparseMatrix<ElemType> &copy);
************************************************[实现]三元组顺序表[稀疏矩阵]类基本成员函数**/

// 函数名称：TriSparseMatrix<ElemType>(int rows = ROW_SIZE, int cols = COL_SIZE, int size = NUM_SIZE);
// 操作结果：建立一个新的稀疏矩阵对象
template <class ElemType>
TriSparseMatrix<ElemType>::TriSparseMatrix(int rows/* = ROW_SIZE*/, int cols/* = COL_SIZE*/, int size/* = NUM_SIZE*/) // 构造函数
{
    m_rows = rows;
    m_cols = cols;
    m_maxSize = m_rows * m_cols;
    m_size = 0;         // 元素个数为0

    m_triElems = new Triple<ElemType>[m_maxSize];        // 开辟内存空间
}

// 函数名称：TriSparseMatrix<ElemType>(const TriSparseMatrix<ElemType> &copy);
// 操作结果：建立一个新的稀疏矩阵对象
template <class ElemType>
TriSparseMatrix<ElemType>::TriSparseMatrix(const TriSparseMatrix<ElemType> &copy) // 复制构造函数
{
    m_rows = copy.m_rows;
    m_cols = copy.m_cols;
    m_size = copy.m_size;
    m_maxSize = m_rows * m_cols;        // 确定组嗲元素个数

    m_triElems = new Triple<ElemType>[copy.m_maxSize];        // 开辟内存空间

    for(int position = 1; position <= m_size; position++)   // 确定每个三元组元素的信息
    {
        m_triElems[position] = copy.m_triElems[position];
    }
}

// 函数名称：virtual ~TriSparseMatrix<ElemType>( );
// 操作结果：销毁对象的信息
template <class ElemType>
TriSparseMatrix<ElemType>::~TriSparseMatrix( )
{
    if(m_triElems != NULL)
    {
        delete[] m_triElems;
    }
}

// 函数名称：TriSparseMatrix<ElemType> &operator=(const TriSparseMatrix<ElemType> &copy);
// 操作结果：重载=
template <class ElemType>
TriSparseMatrix<ElemType>& TriSparseMatrix<ElemType>::operator=(const TriSparseMatrix<ElemType> &copy)
{
    m_rows = copy.m_rows;
    m_cols = copy.m_cols;
    m_size = copy.m_size;
    m_maxSize = m_rows * m_cols;
    if(m_triElems != NULL)  // 如果当前目的对象已经分配率空间删除原有的空间
    {
        delete[] m_triElems;
    }
    m_triElems = new Triple<ElemType>[copy.m_maxSize];        // 重新开辟内存空间

    for(int position = 0; position < m_size; position++)   // 确定每个三元组元素的信息
    {
        m_triElems[position] = copy.m_triElems[position];
    }

    return (*this);
}


/**三元组顺序表[稀疏矩阵]类特征成员函数[实现]************************************************
    int Rows( ) const;       // 获取稀疏矩阵的行数
    int Cols( ) const;       // 获取稀疏矩阵的列数
    int Size( ) const;       // 获取稀疏矩阵的元素个数
    Triple<ElemType> GetTriple(int index);      // 获取第index个三元组的信息
    bool SetMatrix(int rows, int cols, int size);       // 重新设置当前矩阵的信息
    bool SetElem(int row, int col, const ElemType &elem);  // 设置对应row行col列元素的值
    bool GetElem(int row, int col, ElemType &elem);     // 获取对应row行col列元素的值
************************************************[实现]三元组顺序表[稀疏矩阵]类特征成员函数**/

// 函数名称：int Rows( ) const;
// 操作结果：获取稀疏矩阵的行数
template <class ElemType>
int TriSparseMatrix<ElemType>::Rows( ) const      // 获取稀疏矩阵的行数
{
    return m_rows;
}

// 函数名称：int Cols( ) const;
// 操作结果：获取稀疏矩阵的列数
template <class ElemType>
int TriSparseMatrix<ElemType>::Cols( ) const      // 获取稀疏矩阵的列数
{
    return m_cols;
}

// 函数名称：int Size( ) const;
// 操作结果：获取稀疏矩阵的元素个数
template <class ElemType>
int TriSparseMatrix<ElemType>::Size( ) const      // 获取稀疏矩阵的元素个数
{
    return m_size;
}

// 函数名称：Triple<ElemType> GetTriple(int index);
// 操作结果：获取第index个三元组的信息
template <class ElemType>
Triple<ElemType> TriSparseMatrix<ElemType>::GetTriple(int index)      // 获取第index个三元组的信息
{
    return m_triElems[index-1];
}

// 函数名称：SetMatrix(int rows, int cols, int size/*= NOT_DEFINE*/) const
// 操作结果：更改原矩阵的行列和元素个数信息,
//           如果当前函数size参数默认则默认只更改行列数据
template <class ElemType>
void TriSparseMatrix<ElemType>::SetMatrix(int rows, int cols)     // 获取稀疏矩阵的元素个数
{
    m_rows = rows;
    m_cols = cols;
    m_size = 0;
    m_maxSize = m_rows * m_cols;

    if(m_triElems != NULL)
    {
        delete[] m_triElems;    // 删除原有空间
    }
    m_triElems = new Triple<ElemType>[m_maxSize];
}

template <class ElemType>
bool TriSparseMatrix<ElemType>::IsTripleIn(int row, int col) const       // 判断当前位置是否在序列中,也就是当前位置数据是否不为0
{
//    int i;
//     首先判断当前设置位置是否已在三元组序列中
//    for(i = 0; i < m_size; i++)
//    {
//        if(m_triElems[i].IsThisPoint(row, col) == true)     // 查找到当前信息设置位
//        {
//            return true;
//        }
//    }
//    return false;
    int j;
    // 首先循环判断当前设置为[row, col]是否已经存在原三元组序列中
    for(j = m_size-1; j >= 0
                   && (row <= m_triElems[j].m_row && col < m_triElems[j].m_col); j--);

    // 当循环结束时, 如果在原三元组序列中找到了指定位置的三元组
    if(j >= 0 && row == m_triElems[j].m_row && col == m_triElems[j].m_col)
    {
        return true;
    }
    return false;
}


// 函数名称：bool SetElem(int row, int col, const ElemType &elem);
// 操作结果：设置对应row行col列元素的值
// 算法实现：首先循环判断当前设置为[row, col]是否已经存在原三元组序列中
//           如果在序列中则是修改原位置的值, 包括置空和修改
//               如果elem数据为0则是将原设置为清除, 此时需要将元素在三元组蓄序列中删除
//               否则只需要修改数据即可
//           否则在序列中找不到当前设置位
template <class ElemType>
bool TriSparseMatrix<ElemType>::SetElem(int row, int col, const ElemType &elem)
{
    // 判断参数的合法性
    if(row > this->m_rows || col > this->m_cols || row < 1 || col < 1)
    {
        std::cerr <<"当前索引行" <<row <<"列" <<col <<"参数设置错误" <<std::endl;
        return false;
    }

    // 如果原来稀疏矩阵是空的, 需要特殊设置
//    if(m_size == 0)
//    {
//        m_triElems[0] = Triple<ElemType>(row, col, elem);
//        m_size++;
//        return true;
//    }

    int i, j;
    // 首先循环判断当前设置为[row, col]是否已经存在原三元组序列中
    for(j = m_size-1; j >= 0
                   && (row <= m_triElems[j].m_row && col < m_triElems[j].m_col); j--);

    // 当循环结束时, 如果在原三元组序列中找到了指定位置的三元组
    if(j >= 0 && row == m_triElems[j].m_row && col == m_triElems[j].m_col)
    {

        /// 下面这一步其实是有点危险的因为我们并不确定ElemType类型一定是整形所以elem== 0 有一定问题
        if(elem == 0)   // 如果设置数据为0
        {               // 则需要将当前位置元素删除
            for(i = j+1; i < m_size; i++)   // 将后续元素依次前移
            {
                m_triElems[i-1] = m_triElems[i];
            }
            m_size--;           // 三元组元素个数减少1
            std::cout <<"当前位置[" <<row <<", " <<col <<"]" <<"数据信息已经清除" <<std::endl;
        }
        else    // 否则的设置指定位置的三元组数据值为elem
        {
            m_triElems[j].m_data = elem;
            std::cout <<"当前位置[" <<row <<", " <<col <<"]" <<"数据信息更改" <<std::endl;
        }

        return true;            // 操作成功
    }
    else if(elem != 0)      // 否则当前设置位不在三元组序列中
    {
        if(m_size < m_maxSize)  // 当前三元组序列未满
        {   // 需要将当前设置位的信息插入三元组序列中
            for(i = m_size-1; i > j; i--)       // 将后面的元素依次后移
            {
                m_triElems[i+1] = m_triElems[i];
            }
            m_triElems[j+1] = Triple<ElemType>(row, col, elem);       // 插入当前三元组的信息
            // 也可以执行m_triElems[i].SetTriple(row, col, elem);
            m_size++;
            std::cout <<"当前位置[" <<row <<", " <<col <<"]" <<"数据信息已经添加" <<std::endl;
        }
        else
        {
            std::cerr <<"当前稀疏矩阵序列已满, 无法再填入数据" <<std::endl;
            return false;
        }
    }

    return true;
}

// 函数名称：bool GetElem(int row, int col, ElemType &elem);
// 操作结果：获取对应row行col列元素的值
template <class ElemType>
bool TriSparseMatrix<ElemType>::GetElem(int row, int col, ElemType &elem) const
{
    // 判断参数的合法性
    if(row > this->m_rows || col > this->m_cols || row < 1 || col < 1)
    {
        std::cerr <<"当前索引行" <<row <<"列" <<col <<"参数设置错误" <<std::endl;
        return false;
    }

    int i;
    // 首先判断当前设置位置是否已在三元组序列中
    for(i = 0; i < m_size; i++)
    {
        if(m_triElems[i].IsThisPoint(row, col) == true)     // 查找到当前信息设置位

        {
            elem =  m_triElems[i].m_data;               // 返回元素设置
            break;
        }
    }
    if(i == m_size)
    {
        elem = 0;
       // return false;
    }
    return true;
//    int j;
//    // 首先循环判断当前设置为[row, col]是否已经存在原三元组序列中
//    for(j = m_size-1; j >= 0
//                   && (row <= m_triElems[j].m_row && col < m_triElems[j].m_col); j--);
//
//    // 当循环结束时, 如果在原三元组序列中找到了指定位置的三元组
//    if(j >= 0 && (row == m_triElems[j].m_row && col == m_triElems[j].m_col))
//    {
//        elem = m_triElems[j].m_data;
//        //return true;
//    }
//    else
//    {
//        elem = 0;
//        //return false;
//    }
//    return true;
}

/**稀疏矩阵转置函数函数[实现]****************************************************************************
    static void SimpleTranspose(TriSparseMatrix<ElemType> &dest, const TriSparseMatrix<ElemType> &source);
    static void FastTranspose(TriSparseMatrix<ElemType> &dest, const TriSparseMatrix<ElemType> &source);
****************************************************************************稀疏矩阵转置函数函数[实现]**/
//函数名称：static void SimpleTranspose(TriSparseMatrix<ElemType> &dest, const TriSparseMatrix<ElemType> &source);
//操作结果：将稀疏矩阵source转置成稀疏矩阵dest的简单方法
//算法实现：只需要将原来三元组的行元素与列元素位置互换,
//          并在稀疏矩阵的存储三元组中按列标由小到大排序
template <class ElemType>
/*static*/void TriSparseMatrix<ElemType>::SimpleTranspose(TriSparseMatrix<ElemType> &dest, const TriSparseMatrix<ElemType> &source)
{
    dest.m_rows = source.m_cols;
    dest.m_cols = source.m_rows;
    dest.m_size = source.m_size;
    dest.m_maxSize = source.m_maxSize;

    if(dest.m_triElems != NULL)     // 删除目的稀疏矩阵原有的内存空间
    {
        delete[] dest.m_triElems;
    }
    dest.m_triElems = new Triple<ElemType>[dest.m_maxSize]; // 开辟空间空间

    if(dest.m_size > 0)
    {
        int destPos = 0;            // 稀疏矩阵dest的三元组存放位置

        for(int col = 1; col <= source.m_cols; col++)       // 循环每一列的信息
        {
            for(int sourcePos = 0; sourcePos < source.m_size; sourcePos++)
            {   // 在源矩阵中查找col列的三元组信息
                if(source.m_triElems[sourcePos].m_col == col)
                {   // 找到第col列的三元组信息
                    dest.m_triElems[destPos].m_row = source.m_triElems[sourcePos].m_col;  // 转置后的行数为原来的列数
                    dest.m_triElems[destPos].m_col = source.m_triElems[sourcePos].m_row;  // 转置后的列数为原来的行数
                    dest.m_triElems[destPos].m_data = source.m_triElems[sourcePos].m_data;  // 转置后元素的数据值不会变
                    destPos++;          // 计数器进1
                }
            }
        }
    }
}


//函数名称：static TriSparseMatrix<ElemType>::FastTranspose(TriSparseMatrix<ElemType> &dest, const TriSparseMatrix<ElemType> &source)
//操作结果：将稀疏矩阵source转置成稀疏矩阵dest的简单方法
//算法实现：只需要将原来三元组的行元素与列元素位置互换,
//          并在稀疏矩阵的存储三元组中按列标由小到大排序
template <class ElemType>
/*static*/void TriSparseMatrix<ElemType>::FastTranspose(TriSparseMatrix<ElemType> &dest, const TriSparseMatrix<ElemType> &source)
{
    dest.m_rows = source.m_cols;
    dest.m_cols = source.m_rows;
    dest.m_size = source.m_size;
    dest.m_maxSize = source.m_maxSize;

    if(dest.m_triElems != NULL)     // 删除目的稀疏矩阵原有的内存空间
    {
        delete[] dest.m_triElems;
    }
    dest.m_triElems = new Triple<ElemType>[dest.m_maxSize]; // 开辟空间空间

    int col;                // 列信息
    int sourcePos, destPos;          // 遍历稀疏矩阵source和dest的变量
    int cNum[dest.m_rows];  //
    int cPos[dest.m_cols];  // cPos[col]=source第col列上第一个非0元素在dest中应放置的位置
    if(dest.m_size > 0)
    {
        for(col = 1; col <= source.m_cols; col++)   // 初始化cNum
        {
            cNum[col] = 0;
        }

        for(sourcePos = 0; sourcePos < source.m_size; sourcePos++)
        {   // 统计源矩阵source中每一列的非0元素个数
            ++cNum[source.m_triElems[sourcePos].m_col];
        }

        cPos[1] = 0;        // 前一列的第一个非0元素在dest存储的起始位置

        for(col = 2; col <= source.m_cols; col++)
        {   // 循环求每一列的第一个非0元素在dest存储的起始位置
            cPos[col] = cPos[col-1] + cNum[col-1];
        }

        for(sourcePos = 0; sourcePos < source.m_size; sourcePos++)
        {   // 循环遍历source的三元组
            destPos = cPos[source.m_triElems[sourcePos].m_col];  // 计算目的稀疏矩阵的当前存储位置

            dest.m_triElems[destPos].m_row = source.m_triElems[sourcePos].m_col;    // 转置后列变行
            dest.m_triElems[destPos].m_col = source.m_triElems[sourcePos].m_row;    // 转置后行变列
            dest.m_triElems[destPos].m_data = source.m_triElems[sourcePos].m_data;  // 转置后数据不变
        }
    }
}

////函数名称：operator+(const TriSparseMatrix<ElemType> &left, const TriSparseMatrix<ElemType> &right)
////操作结果：重载+法运算
//template <class ElemType>
//TriSparseMatrix<ElemType> operator+(const TriSparseMatrix<ElemType> &left, const TriSparseMatrix<ElemType> &right)
//{
//    if(left.m_rows != right.m_rows
//     ||right.m_rows != right.m_cols)
//    {
//        std::cerr <<"两个矩阵阶数不同, 无法进行+运算" <<std::endl;
//        exit(-2);
//    }
//    ElemType leftElem, rightElem;
//    TriSparseMatrix<ElemType> matrix(left.m_rows, left.m_cols, 0);
//    for(int row = 1; row <= left.m_rows; row++)
//    {
//        for(int col = 1; col <= left.m_cols; col++)
//        {
//            left.GetElem(row, col, leftElem);
//            right.GetElem(row, col, rightElem);
//            matrix.SetElem(row, col, leftElem+rightElem);
//        }
//    }
//
//    return matrix;
//}
//
//
//template <class ElemType>
//TriSparseMatrix<ElemType> operator-(const TriSparseMatrix<ElemType> &left, const TriSparseMatrix<ElemType> &right)
//{
//    if(left.m_rows != right.m_rows
//     ||right.m_rows != right.m_cols)
//    {
//        std::cerr <<"两个矩阵阶数不同, 无法进行+运算" <<std::endl;
//        exit(-2);
//    }
//    ElemType leftElem, rightElem;
//    TriSparseMatrix<ElemType> matrix(left.m_rows, left.m_cols, 0);
//    for(int row = 1; row <= left.m_rows; row++)
//    {
//        for(int col = 1; col <= left.m_cols; col++)
//        {
//            left.GetElem(row, col, leftElem);
//            right.GetElem(row, col, rightElem);
//            matrix.SetElem(row, col, leftElem-rightElem);
//        }
//    }
//
//    return matrix;
//}

template <class ElemType>
TriSparseMatrix<ElemType> TriSparseMatrix<ElemType>::operator+(const TriSparseMatrix<ElemType> &matrix)
{
    if(this->m_rows != matrix.m_rows
     ||matrix.m_rows != matrix.m_cols)
    {
        std::cerr <<"两个矩阵阶数不同, 无法进行+运算" <<std::endl;
        exit(-2);
    }
    ElemType thisElem, matrixElem;
    TriSparseMatrix<ElemType> result(this->m_rows, this->m_cols, 0);
    for(int row = 1; row <= this->m_rows; row++)
    {
        for(int col = 1; col <= this->m_cols; col++)
        {
            this->GetElem(row, col, thisElem);
            matrix.GetElem(row, col, matrixElem);
            result.SetElem(row, col, thisElem+matrixElem);
        }
    }

    return result;
}

template <class ElemType>
TriSparseMatrix<ElemType> TriSparseMatrix<ElemType>::operator-(const TriSparseMatrix<ElemType> &matrix)
{
    if(this->m_rows != matrix.m_rows
     ||matrix.m_rows != matrix.m_cols)
    {
        std::cerr <<"两个矩阵阶数不同, 无法进行+运算" <<std::endl;
        exit(-2);
    }
    ElemType thisElem, matrixElem;
    TriSparseMatrix<ElemType> result(this->m_rows, this->m_cols, 0);
    for(int row = 1; row <= this->m_rows; row++)
    {
        for(int col = 1; col <= this->m_cols; col++)
        {
            this->GetElem(row, col, thisElem);
            matrix.GetElem(row, col, matrixElem);
            result.SetElem(row, col, thisElem-matrixElem);
        }
    }

    return result;
}
#endif // TriSparseMatrix<ElemType>_H_INCLUDED
