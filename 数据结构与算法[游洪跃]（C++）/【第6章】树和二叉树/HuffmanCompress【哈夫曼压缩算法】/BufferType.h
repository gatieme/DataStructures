/**
******************************************************************************
*  CopyRight  : 2012-2013, HerBinUnversity, GatieMe                          *
*  File Name  : HuffmanTree.h                                                *
*  Description: 哈夫曼树压缩类HuffmanCompress字符缓冲器文件BufferType.h     *
*  Author     : Gatie_Me                                                     *
*  Version    : Copyright 2012 JULY_CITY                                     *
*  Data_Time  : 2012-11-6_10:21:43                                           *
*  Content    : 数据结构与算法（C++）版书上源码                             *
******************************************************************************
**/

#ifndef BUFFERTYPE_H_INCLUDED
#define BUFFERTYPE_H_INCLUDED



/// 字符缓存器
class BufferType
{
    /*===========================【PUBLIC：公共接口】============================*/
public :      // 公共接口
    BufferType( );              // 默认构造函数
    ~BufferType( );             // 析构函数

    char m_character;               // 字符信息
    unsigned int m_bits;            // 实际比特数目

    void InitBuffer( );             // 初始化缓存信息
};


BufferType::BufferType( )              // 默认构造函数
{
    this->InitBuffer( );
}


BufferType::~BufferType( )             // 析构函数
{

}
// 函数名称：void InitBuffer( );
// 操作结果：初始化缓存信息
void BufferType::InitBuffer( )             // 初始化缓存信息
{
    this->m_bits  = 0;          // 初始化缓存区大小[清0]
    this->m_character = 0;      // 初始化字符信息
}


#endif // HuffmanTree_H_INCLUDED
