/**
******************************************************************************
*  CopyRight  : 2012-2013, HerBinUnversity, GatieMe                          *
*  File Name  : HuffmanTree.h                                                *
*  Description: 哈夫曼树压缩类HuffmanCompress类头文件HuffmanCompress.h      *
*  Author     : Gatie_Me                                                     *
*  Version    : Copyright 2012 JULY_CITY                                     *
*  Data_Time  : 2012-11-6_10:21:43                                           *
*  Content    : 数据结构与算法（C++）版书上源码                             *
******************************************************************************
**/


#ifndef HUFFMANCOMPRESS_H_INCLUDED
#define HUFFMANCOMPRESS_H_INCLUDED

#include <ios>
#include <iostream>

#include "Error.h"
#include "BufferType.h"
#include "HuffmanTree.h"


/// 哈夫曼树压缩类HuffmanCompress类声明部分
class HuffmanCompress
{

/*==============================[公共接口:PUBLIC]============================*/
public:
    // 哈夫曼压缩类方法方法声明

    // 哈夫曼压缩类节基本成员函数
    HuffmanCompress( );         // 无参数的构造函数

    HuffmanCompress(const HuffmanCompress &copy);   // 复制构造函数

    ~HuffmanCompress( );        // 析构函数

    // 运算符重载函数=
    HuffmanCompress& operator=(const HuffmanCompress &copy);    // 重载赋值运算符=

    // 哈夫曼压缩类节特征成员函数
    void EnCompress( );           // 压缩算法

    void UnCompress( );         // 解压缩算法
/*==============================[公共接口:PUBLIC]============================*/
/*============================[保护成员:PROTECTED]===========================*/
protected:
    // 哈夫曼树压缩类HuffmanCompress保护数据成员
    HuffmanTree<char, unsigned long> *m_pHuffmanTree;       // 哈夫曼树类指针
    FILE *m_infp, *m_outfp;                             // 输入/输出文件
    BufferType m_buffer;                            // 字符缓冲区

    // 辅助成员函数
    void Write(unsigned int bit);                   // 向目标文件中写入一个bit
    void WriteOutfp( );                             // 强行将字符缓冲写入目标文件
/*============================[保护成员:PROTECTED]===========================*/

};



/// 哈夫曼树压缩类HuffmanCompress类实现部分


/**辅助成员函数[实现]**********************************************************
    void Write(unsigned int bit);   // 向目标文件中写入一个bit
    void WriteOutfp( );             // 强行将字符缓冲写入目标文件
**********************************************************[实现]辅助成员函数**/
// 函数名称：void Write(unsigned int bit);
// 操作结果：向目标文件中写入一个bit
// Write用于依次向字符缓存中写入一比特,
// 当缓存器中的比特数为8(也就是一个字节时)
// 将缓存中的字符写入目标文件
void HuffmanCompress::Write(unsigned int bit)          // 向目标文件中写入一个bit
{
    this->m_buffer.m_bits++;            // 每写入一个bit位, 就让缓存比特数增加1
    this->m_buffer.m_character = (this->m_buffer.m_character << 1) | bit;

    if(m_buffer.m_bits == 8)            // 8位为一个字节, 缓存区满了
    {       // 将信息写入目标文件
        fputc(this->m_buffer.m_character, m_outfp);

        m_buffer.InitBuffer( );         // 初始化缓存区
    }
}


// 函数名称：void WriteOutfp( );
// 操作结果：向目标文件中写入一个bit
// WriteOutfp用于在哈夫曼编码结束时, 强行将缓存写入目标文件中,
// 也就是不管够不够8位[一个字节],
// 在哈夫曼编码结束时, 都要将信息写入目标文件
void HuffmanCompress::WriteOutfp( )         // 强行将字符缓冲写入目标文件
{
    unsigned int len = m_buffer.m_bits;     // 当前缓存中实际比特数目

    if(len > 0)     // 只要缓冲区不是空的
    {   // 就将缓存周边的比特数目增加到8, 自动写入文件中
        for(unsigned int i = 0; i < 8-len; i++)
        {
            Write(0);
        }

    }
}


/**哈夫曼压缩类节基本成员函数[实现]********************************************
    HuffmanCompress( );         // 无参数的构造函数
    HuffmanCompress(const HuffmanCompress &copy);   // 复制构造函数
    ~HuffmanCompress( );        // 析构函数
********************************************[实现]哈夫曼压缩类节基本成员函数**/
// 函数名称：HuffmanCompress( );
// 操作结果：建立一个空的哈夫曼压缩类对象, 开辟出必要的空间
HuffmanCompress::HuffmanCompress( )     // 无参数的构造函数
{
    this->m_pHuffmanTree = NULL;          // 哈夫曼树类指针
    this->m_infp = NULL;                  // 输入文件
    this->m_outfp = NULL;                  // 输出文件
}

// 函数名称：HuffmanCompress(const HuffmanCompress &copy);
// 操作结果：建立一个空的哈夫曼压缩类对象, 开辟出必要的空间
HuffmanCompress::HuffmanCompress(const HuffmanCompress &copy)   // 复制构造函数
{
    this->m_pHuffmanTree = copy.m_pHuffmanTree;          // 哈夫曼树类指针
    this->m_infp = copy.m_infp;                  // 输入文件
    this->m_outfp = copy.m_outfp;                  // 输出文件
    this->m_buffer = copy.m_buffer;                // 缓冲区
}

// 函数名称：~HuffmanCompress( );        // 析构函数
// 操作结果：释放必要的空间
HuffmanCompress::~HuffmanCompress( )        // 析构函数
{

}

/**运算符重载函数=[实现]********************************************************
    HuffmanCompress& operator=(const HuffmanCompress &copy);  // 重载赋值运算符=
********************************************************[实现]运算符重载函数=**/
// 函数名称：HuffmanCompress& operator=(const HuffmanCompress &copy);    // 重载赋值运算符=
HuffmanCompress& HuffmanCompress::operator=(const HuffmanCompress &copy)    // 重载赋值运算符=
{
    this->m_pHuffmanTree = copy.m_pHuffmanTree;          // 哈夫曼树类指针
    this->m_infp = copy.m_infp;                  // 输入文件
    this->m_outfp = copy.m_outfp;                  // 输出文件
    this->m_buffer = copy.m_buffer;                // 缓冲区

    return (*this);
}


/**哈夫曼压缩类节特征成员函数[实现]********************************************
    void EnCompress( );           // 压缩算法
    void UnCompress( );         // 解压缩算法
********************************************[实现]哈夫曼压缩类节特征成员函数**/
// 函数名称：void EnCompress( );
// 操作结果：应哈夫曼进行压缩
void HuffmanCompress::EnCompress( )           // 压缩算法
{
    const unsigned long maxSize = 256;
    char infName[maxSize], outfName[maxSize];       // 输入输出文件名

    std::cout <<"请输入源文件名[<4GB]:" <<std::endl;     // 提示信息
    std::cin >>infName;                              // 输入源文件名
    if((this->m_infp = fopen(infName, "rb")) == NULL)
    {
        std::cout <<"打开源文件失败" <<std::endl;
        throw Error("打开源文件失败\n");
    }

    //fgetc(this->m_infp);              // 取出源文件中的第一个字符
    /*if(ftell(this->m_infp) <= 0)         // 如果当前文件是空的
    {
        std::cout <<"空文件" <<std::endl;
        throw Error("空文件\n");
    }*/
    if(fgetc(m_infp) == EOF)
    {
        throw Error("空文件\n");
    }
    rewind(m_infp);
//    while( 1 )
//    {
//        char choice;
//        std::cout <<"请输入目标文件名:" <<std::endl;
//        std::cin >>outfName;                 // 输入目标文件名
//        if((this->m_outfp = fopen(outfName, "wb")) == NULL)
//        {
//            throw Error("打开目标文件失败\n");
//        }
//
//        if(ftell(this->m_outfp) > 0)            // 如果目标文件不是空的
//        {               // 询问是否覆盖
//            while( 1 )
//            {
//                std::cout <<"目标文件不为空..." <<std::endl;
//                std::cout <<"确任覆盖此文件么[y/Y  OR  n/N]:" <<std::endl;
//
//                std::cin >>choice;
//                if(choice == 'y' || choice == 'Y' || choice == 'N' || choice == 'n')
//                {
//                    break;
//                }
//                std::cout <<"输入有误, 请重新输入" <<std::endl;
//            }
//
//            if(choice == 'y' || choice == 'Y')      // 如果确认覆盖就停止
//            {
//                break;
//            }
//
//        }
//        else
//        {
//            break;
//        }
//    }

    std::cout <<"请输入目标文件名:" <<std::endl;
    std::cin >>outfName;                 // 输入目标文件名
    if((this->m_outfp = fopen(outfName, "wb")) == NULL)
    {
        throw Error("打开目标文件失败\n");
    }

    std::cout <<"正在压缩中, 请稍后..." <<std::endl;

    char chars[maxSize];                // 字符数组
    unsigned long weight[maxSize];         // 字符出现的
    unsigned long i, size = 0;
    char charType;

    rewind(m_infp);
    for(i = 0; i < maxSize; i++)
    {
        chars[i] = (char)(i);           // 初始化字符数组
        weight[i] = 0;                  // 初始化权值数组
    }

    while((charType = fgetc(this->m_infp)) != EOF)  // 取出文件中的每个字符
    {
        weight[(unsigned char)charType]++;            // 字符charType出现的频率增加1
        size++;                                       // 文件大小自加1
    }

    if(m_pHuffmanTree != NULL)      // 如果当前哈夫曼编码类信息不为空
    {
        delete m_pHuffmanTree;    // 删除空间
    }
system("pause");
    this->m_pHuffmanTree = new HuffmanTree<char, unsigned long>(chars, weight, size);  // 生成哈夫曼编码
system("pause");

    rewind(m_outfp);
    fwrite(&size, sizeof(unsigned long), 1, m_outfp);   // 向目标文件中写入源文件大小
   // for(i = 0; i < size; i++)
    //{   // 向文件终不写入字符出现频率
        fwrite(&weight[0], sizeof(unsigned long), size, m_outfp);
    //}
system("pause");
    this->m_buffer.InitBuffer( );      // 初始化缓存区

    rewind(m_infp);                     // 使源文指针定位在文件的开始
    while((charType = fgetc(m_infp)) != EOF)
    {
        //对源文件字符进行编码, 并将编码信息写入目标文件
        std::string strTemp = m_pHuffmanTree->EnCode(charType);

        // 将编码谢瑞目标文件
        for(i = 0; i < strTemp.size(); i++)
        {
            if(strTemp[i] == '0')
            {
                this->Write(0);
            }
            else
            {
                this->Write(1);
            }
        }
    }
    this->WriteOutfp( );            // 强行将最后的信息写入目标文件
system("pause");

    // 关闭文件
    fclose(this->m_infp);       // 关闭源文件
    fclose(this->m_outfp);      // 关闭目标文件
    std::cout <<"处理结束..." <<std::endl;
}

// 函数名称：void UnCompress( );
// 操作结果：用哈夫曼树进行解压缩
void HuffmanCompress::UnCompress( )         // 解压缩算法
{
    const unsigned long maxSize = 256;
    char infName[maxSize], outfName[maxSize];       // 输入输出文件名

    std::cout <<"请输入压缩文件名:" <<std::endl;     // 提示信息
    std::cin >>infName;                              // 输入源文件名
    if((this->m_infp = fopen(infName, "rb")) == NULL)
    {
        throw Error("打开源文件失败\n");
    }

    if(fgetc(m_infp) == EOF)
    {
        throw Error("空文件\n");
    }

    rewind(m_infp);
//    while( 1 )
//    {
//        char choice;
//        std::cout <<"请输入目标文件名:" <<std::endl;
//        std::cin >>outfName;                 // 输入目标文件名
//        if((this->m_outfp = fopen(outfName, "wb")) == NULL)
//        {
//            throw Error("打开目标文件失败\n");
//        }
//
//        if(ftell(this->m_outfp) > 0)            // 如果目标文件不是空的
//        {               // 询问是否覆盖
//            while( 1 )
//            {
//                std::cout <<"目标文件不为空..." <<std::endl;
//                std::cout <<"确任覆盖此文件么[y/Y  OR  n/N]:" <<std::endl;
//
//                std::cin >>choice;
//                if(choice == 'y' || choice == 'Y' || choice == 'N' || choice == 'n')
//                {
//                    break;
//                }
//                std::cout <<"输入有误, 请重新输入" <<std::endl;
//            }
//
//            if(choice == 'y' || choice == 'Y')      // 如果确认覆盖就停止
//            {
//                break;
//            }
//        }
//        else
//        {
//            break;
//        }
//    }
    std::cout <<"请输入目标文件名:" <<std::endl;
    std::cin >>outfName;                 // 输入目标文件名
    if((this->m_outfp = fopen(outfName, "wb")) == NULL)
    {
        throw Error("打开目标文件失败\n");
    }
    std::cout <<"正在解压缩中, 请稍后..." <<std::endl;

    char chars[maxSize];                // 字符数组
    unsigned long weight[maxSize];         // 字符出现的
    unsigned long i, size = 0;
    char charType;

    rewind(m_infp);         // 使压缩文件定位在开头
    rewind(m_outfp);
    fread(&size, sizeof(unsigned long), 1, m_infp);     // 读取目标文件的大小
    for(i = 0; i < size; i++)                   //
    {
        chars[i] = (char)i;                 // 初始化chars[i]
        fread(&weight[i], sizeof(unsigned long), 1, m_infp);    // 读取字符频率
    }

    if(m_pHuffmanTree != NULL)
    {
        delete[] m_pHuffmanTree;// 释放已经分配的编码空间
    }
    m_pHuffmanTree = new HuffmanTree<char, unsigned long>(chars, weight, size);// 生成哈夫曼树


    unsigned long len = 0;
    while((charType = fgetc(m_infp)) != EOF)
    {   // 对文件进行解码
        std::string strTemp = "";
        unsigned char charTemp = (unsigned char)charType;

        for(i = 0; i < 8; i++)
        {
            if(charTemp < 128)
            {
                strTemp += '0';
            }
            else
            {
                strTemp += '1';
            }
            charTemp = charTemp<<1;     // 左移一位
        }

        std::string deString(m_pHuffmanTree->DeCode(strTemp));  // 对读出来的信息进行译码
        for(i = 1; i <= strTemp.size(); i++)
        {
            len++;
            fputc(strTemp[i-1], m_outfp);
            if(len == size)
            {
                break;
            }
        }
        if(len == size)
        {
            break;
        }
    }

    fclose(m_infp);
    fclose(m_outfp);

    std::cout <<"处理结束..." <<std::endl;
}

#endif // HUFFMANCOMPRESS_H_INCLUDED
