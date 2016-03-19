/**
******************************************************************************
*  CopyRight  : 2012-2013, HerBinUnversity, GatieMe                          *
*  File Name  : HuffmanTree.h                                                *
*  Description: 哈夫曼树HuffmanTree类模版头文件                    *
*  Author     : Gatie_Me                                                     *
*  Version    : Copyright 2012 JULY_CITY                                     *
*  Data_Time  : 2012-11-6_10:21:43                                           *
*  Content    : 数据结构与算法（C++）版书上源码                             *
******************************************************************************
**/

#ifndef HUFFMANTREE_H_INCLUDED
#define HUFFMANTREE_H_INCLUDED

#include <algorithm>
#include <string>
#include <iomanip>


#include "HuffmanTreeNode.h"

/// 哈夫曼树类模版声明部分
template <class CharType, class WeightType>
class HuffmanTree
{
    /*===========================【PUBLIC：公共接口】============================*/
public :      // 公共接口
    // 哈夫曼树类HuffmanTree基本成员函数
    HuffmanTree( );                     // 默认构造函数模版

    HuffmanTree(CharType *chars, WeightType *weight, int size); //  由字符chars[], 权值weight[]和字符个数size构造哈夫曼树

    HuffmanTree(const HuffmanTree<CharType, WeightType> &copy);     // 复制构造函数

    ~HuffmanTree( );            // 析构函数模版

    HuffmanTree<CharType, WeightType> &operator=(const HuffmanTree<CharType, WeightType> &copy);

    // 特征成员函数实现
    void CreateHuffmanTree(CharType *chars, WeightType *weight, int size);   // 由字符chars[], 权值weight[]和字符个数size构造哈夫曼树

    std::string EnCode(CharType chType);               // 编码函数

  //  std::string EnCode(std::String charCode);             // 编码函数

    std::string DeCode(std::string strCode);                  // 译码函数

    int Size( );                         // 获取当前哈夫曼树的结点数目

    CharType Char(int pos);             // 获取当前哈夫曼编码的第pos个字符编码

    void DisplayWithShape( );
/*===========================【PUBLIC：公共接口】============================*/
///////////////////////////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////////
    /*=========================【PROTECTED：保护成员】===========================*/
protected :
    // 哈夫曼树类HuffmanTree数据成员
    HuffmanTreeNode<WeightType> *m_nodes;   // 存储结点信息, m_nodes[0]不使用
    CharType *m_leafChars;                  // 叶结点字符信息, m_LeafChars[0]不使用
    std::string *m_leafCharCodes;                 // char **m_leafCharCodes叶结点字符的编码信息, m_leafCharCodes[0]不使用
    int m_curPos;                           // 译码时从根结点到叶结点路径的当前结点
    int m_size;                              // 叶结点的数目

    // 哈夫曼树类HuffmanTree辅助函数
    void Select(int cur, int &minOne, int &minTwo); // 从m_nodes[0~curPos-1]中选择双亲为0[也就是还没有加入哈夫曼树中的编码], 权值

    void DisplayWithShape(int root, int level);                // 树形显示哈夫曼树
};


/// 哈夫曼树类模版实现部分
/**函数辅助函数信息[实现]************************************************************************************************************
    void Select(int cur, int &minOne, int &minTwo); // 从m_nodes[0~curPos-1]中选择双亲为0[也就是还没有加入哈夫曼树中的编码], 权值
    void DisplayWithShape(int root);                // 树形显示哈夫曼树
************************************************************************************************************函数辅助函数信息[实现]**/
// 函数名称：void Select(int cur, int &minOne, int &minTwo)
// 操作结果：递归复制每个结点的信息
template <class CharType, class WeightType>
void HuffmanTree<CharType, WeightType>::Select(int cur, int &minOne, int &minTwo) // 从m_nodes[0~curPos-1]中选择双亲为0[也就是还没有加入哈夫曼树中的编码], 权值
{
#ifdef DEBUG    // 插桩调试信息
    std::cout <<"FUN:"<<__func__  <<", LINE:" <<__LINE__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现部分
    minOne = minTwo = 0;
    //len = 2*cur;
    for (int pos = 1; pos <= cur; pos++)        // 循环所有的结点
    {
        if (m_nodes[pos].m_parent != 0)
        {
            continue;	// 双亲是0的结点已经加入到哈夫曼树中了不需要在添加
        }

        if(minOne == 0)     // minOne为初值空,将pos赋值给minOne[最小]
        {
            minOne = pos;
        }

        if(m_nodes[pos].m_weight < m_nodes[minOne].m_weight)  // m_nodes[pos]权值比m_nodes[minOne]更小,将pos赋为minOne
        {
            // 查找当前未加入哈夫曼树中的权值最小的
            minOne = pos;
        }
    }

    for (int pos = 1; pos <= cur; pos++)        // 循环所有的结点
    {
        if(m_nodes[pos].m_parent != 0)
        {
            continue;	// 双亲是0的结点已经加入到哈夫曼树中了不需要在添加
        }

        if(minTwo == 0 && m_nodes[minOne].m_weight != m_nodes[pos].m_weight)       // minTwo为初值空,将pos赋值给minTwo[次小]
        {
            minTwo = pos;
        }
        else if((m_nodes[pos].m_weight < m_nodes[minTwo].m_weight) && pos != minOne)// m_nodes[pos]权值比m_nodes[minOne]更小,将pos赋为minOne
        {
            // 查找当前未加入哈夫曼树中的权值最小的
            minTwo = pos;
        }
        //std::cout <<"minOne = " <<minOne <<", minTwo = " <<minTwo <<std::endl;
    }
}

template <class CharType, class WeightType>
void HuffmanTree<CharType, WeightType>::DisplayWithShape(int root, int level)  // 树形显示哈夫曼树
{
    if(m_nodes[root].m_leftChild == 0 && m_nodes[root].m_rightChild == 0)
    {
        std::cout <<std::endl;
        for(int i = 0; i < level-1; i++)
        {
            std::cout <<"   ";
        }
        if(root > m_size)
        {
            std::cout <<std::setw(2)<<m_nodes[root].m_weight <<"#";
        }
        else
        {
            std::cout <<std::setw(2)<<m_nodes[root].m_weight <<m_leafChars[root];
        }
        //return ;
    }
    else //(m_nodes[m_curPos].m_rightChild == 0))
    {
        // 显示右子树
        DisplayWithShape(this->m_nodes[root].m_rightChild, level+1);

        std::cout <<std::endl;
        for(int i =0; i  < level-1; i++)
        {
            std::cout <<"   ";
        }
        if(root > m_size)
        {
            std::cout <<std::setw(2)<<m_nodes[root].m_weight <<"#";
        }
        else
        {
            std::cout <<std::setw(2)<<m_nodes[root].m_weight <<m_leafChars[root];
        }
        // 显示左子树
        DisplayWithShape(this->m_nodes[root].m_leftChild, level+1);

    }

}

/**哈夫曼树类HuffmanTree基本成员函数[实现]********************************************************************************
    HuffmanTree( );                     // 默认构造函数模版
    HuffmanTree(CharType *chars, WeightType *weight, int size); //  由字符chars[], 权值weight[]和字符个数size构造哈夫曼树
    HuffmanTree(const HuffmanTree<CharType, WeightType> &copy);     // 复制构造函数
    ~HuffmanTree( );            // 析构函数模版
    HuffmanTree<CharType, WeightType> &operator=(const HuffmanTree<CharType, WeightType> &copy);
    void CreatHuffmanTree(CharType *chars, WeightType *weight, int size);   // 由字符chars[], 权值weight[]和字符个数size构造哈夫曼树
    int getSize( );                         // 获取当前哈夫曼树的结点数目
    charType Char(int pos);             // 获取当前哈夫曼编码的第pos个字符编码
********************************************************************************[实现]哈夫曼树类HuffmanTree基本成员函数**/
// 函数名称：HuffmanTree( );                     // 默认构造函数模版
// 操作结果：创建一个空的对象
template <class CharType, class WeightType>
HuffmanTree<CharType, WeightType>::HuffmanTree( )                     // 默认构造函数模版
{
#ifdef DEBUG    // 插桩调试信息
    std::cout <<"FUN:"<<__func__  <<", LINE:" <<__LINE__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现部分
    this->m_nodes = NULL;   // 存储结点信息, m_nodes[0]不使用
    this->m_leafChars = NULL;                  // 叶结点字符信息, m_LeafChars[0]不使用
    this->m_leafCharCodes = NULL;                 // char **m_leafCharCodes叶结点字符的编码信息, m_leafCharCodes[0]不使用
}


// 函数名称：HuffmanTree(CharType *chars, WeightType *weight, int size);
// 操作结果：由字符chars[], 权值weight[]和字符个数size构造哈夫曼树
template <class CharType, class WeightType>
HuffmanTree<CharType, WeightType>::HuffmanTree(CharType *chars, WeightType *weight, int size) //  由字符chars[], 权值weight[]和字符个数size构造哈夫曼树
{
#ifdef DEBUG    // 插桩调试信息
    std::cout <<"FUN:"<<__func__  <<", LINE:" <<__LINE__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现部分
    this->CreateHuffmanTree(chars, weight, size);       // 由字符编码chars, 权值数组weight, 和字符数目size构造哈夫曼树;
}

template <class CharType, class WeightType>
HuffmanTree<CharType, WeightType>::HuffmanTree(const HuffmanTree<CharType, WeightType> &copy)     // 复制构造函数
{
#ifdef DEBUG    // 插桩调试信息
    std::cout <<"FUN:"<<__func__  <<", LINE:" <<__LINE__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现部分
    this->m_size = copy.m_size;
    this->m_curPos = copy.m_curPos;
    this->m_size = copy.m_size;						// 叶结点个数
    int len = 2 * m_size - 1;				// 结点个数

    // 开辟必要空间
    m_nodes = new HuffmanTreeNode<WeightType>[len + 1];	        // 开辟哈夫曼树结点信息数组
    m_leafChars = new CharType[m_size + 1];				            // 开辟字符信息数组
    m_leafCharCodes = new std::string[m_size + 1];				            //开辟哈夫曼字符编码数组

    int curPos;
    for(curPos = 1; curPos < len; curPos++)
    {
        this->m_nodes = copy.m_nodesp[curPos];   // 存储结点信息, m_nodes[0]不使用
    }

    for(curPos = 1; curPos <= m_size; curPos++)
    {

        this->m_leafChars = copy.m_leafChars[curPos];                  // 叶结点字符信息, m_LeafChars[0]不使用
        this->m_leafCharCodes = copy.m_leafCharCode[curPos];                 // char **m_leafCharCodes叶结点字符的编码信息, m_leafCharCodes[0]不使用
    }
}

// 函数名称：~HuffmanTree( )
template <class CharType, class WeightType>
HuffmanTree<CharType, WeightType>::~HuffmanTree( )            // 析构函数模版
{
#ifdef DEBUG    // 插桩调试信息
    std::cout <<"FUN:"<<__func__  <<", LINE:" <<__LINE__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现部分
    delete[] this->m_nodes;   // 存储结点信息, m_nodes[0]不使用
    delete[] this->m_leafChars;                  // 叶结点字符信息, m_LeafChars[0]不使用
    delete[] this->m_leafCharCodes;                 // char **m_leafCharCodes叶结点字符的编码信息, m_leafCharCodes[0]不使用

}

template <class CharType, class WeightType>
HuffmanTree<CharType, WeightType>& HuffmanTree<CharType, WeightType>::operator=(const HuffmanTree<CharType, WeightType> &copy)
{
#ifdef DEBUG    // 插桩调试信息
    std::cout <<"FUN:"<<__func__  <<", LINE:" <<__LINE__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现部分
    this->m_size = copy.m_size;
    this->m_curPos = copy.m_curPos;
    this->m_size = copy.m_size;						// 叶结点个数
    int len = 2 * m_size - 1;				// 结点个数

    // 开辟必要空间
    m_nodes = new HuffmanTreeNode<WeightType>[len + 1];	        // 开辟哈夫曼树结点信息数组
    m_leafChars = new CharType[m_size + 1];				            // 开辟字符信息数组
    m_leafCharCodes = new std::string[m_size + 1];				            //开辟哈夫曼字符编码数组

    int curPos;
    for(curPos = 1; curPos < len; curPos++)
    {
        this->m_nodes = copy.m_nodesp[curPos];   // 存储结点信息, m_nodes[0]不使用
    }

    for(curPos = 1; curPos <= m_size; curPos++)
    {

        this->m_leafChars = copy.m_leafChars[curPos];                  // 叶结点字符信息, m_LeafChars[0]不使用
        this->m_leafCharCodes = copy.m_leafCharCode[curPos];                 // char **m_leafCharCodes叶结点字符的编码信息, m_leafCharCodes[0]不使用
    }

    return (*this);
}



// 函数名称：void CreatHuffmanTree(CharType *chars, WeightType *weight, int size)
// 操作结果：递归复制每个结点的信息
template <class CharType, class WeightType>
void HuffmanTree<CharType, WeightType>::CreateHuffmanTree(CharType *chars, WeightType *weight, int size)   // 由字符chars[], 权值weight[]和字符个数size构造哈夫曼树
{
#ifdef DEBUG    // 插桩调试信息
    std::cout <<"FUN:"<<__func__  <<", LINE:" <<__LINE__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现部分
    this->m_size = size;						// 叶结点个数
    int len = 2 * m_size - 1;				// 结点个数

    m_nodes = new HuffmanTreeNode<WeightType>[len + 1];	        // 开辟哈夫曼树结点信息数组
    m_leafChars = new CharType[m_size + 1];				            // 开辟字符信息数组
    m_leafCharCodes = new std::string[m_size + 1];				            //开辟哈夫曼字符编码数组

    int pos, minOne, minTwo;										// 临时变量
    for(pos = 1; pos <= m_size; pos++)
    {
        // 存储叶结点信息
        m_nodes[pos].m_weight = weight[pos - 1];				// 权值
        m_leafChars[pos] = chars[pos - 1];				// 字符
    }

    for(pos = size + 1; pos <= len; pos++)
    {
        // 建立哈夫曼树
        Select(pos - 1, minOne, minTwo);	// m_nodes[1 ~ pos - 1]中选择双亲为0,权值最小的两个结点minOne,minTwo

        // 合并以minOne,minTwo为根的树
        m_nodes[minOne].m_parent = m_nodes[minTwo].m_parent = pos;	// minOne,minTwo双亲为pos
        m_nodes[pos].m_leftChild = minOne;					// minOne为pos的左孩子
        m_nodes[pos].m_rightChild = minTwo;					// minTwo为pos的右孩子
        m_nodes[pos].m_weight = m_nodes[minOne].m_weight + m_nodes[minTwo].m_weight;//pos的权为minOne,minTwo的权值之和
    }

    for(pos = 1; pos <= m_size; pos++)
    {
        int j = 81;
        std::string charCode;			// 暂存叶结点字符编码信息
        charCode[j--] = '\0';

        for(unsigned int child = pos, parent = m_nodes[child].m_parent;
            parent != 0;
            child = parent, parent = m_nodes[child].m_parent)
        {
            // 从叶结点到根结点逆向求编码
            if (m_nodes[parent].m_leftChild == child)
            {
                charCode[j--]  = '0';
            }
            else
            {
                charCode[j--] = '1';	// 右分支编码为'1'
            }
        }
        this->m_leafCharCodes[pos] = &charCode[j+1];		// charCode中存储字符编码
    }

//        int len;
//        std::string charCode = "";			// 暂存叶结点字符编码信息
//
//        for(unsigned int child = pos, parent = m_nodes[child].m_parent;
//            parent != 0;
//            child = parent, parent = m_nodes[child].m_parent)
//        {
//            // 从叶结点到根结点逆向求编码
//            if (m_nodes[parent].m_leftChild == child)
//            {
//                len = charCode.size( );
//                while(len > 0)          // 将字符依次后移
//                {
//                    charCode[len] = charCode[len-1];
//                    len--;
//                }
//                charCode[len]  = '0';
//            }
//            else
//            {
//                len = charCode.size( );
//                while(len > 0)          // 将字符依次后移
//                {
//                    charCode[len] = charCode[len-1];
//                    len--;
//                }
//                charCode[len]  = '1';
//            }
//        }
//        this->m_leafCharCodes[pos] = &charCode[0];		// charCode中存储字符编码
//    }
    this->m_curPos = len;
}


// 函数名称：string Encode(CharType chType);               // 编码函数
// 操作结果：返回字符chType的哈夫曼编码
template <class CharType, class WeightType>
std::string HuffmanTree<CharType, WeightType>::EnCode(CharType chType)       // 编码函数
{
#ifdef DEBUG    // 插桩调试信息
    std::cout <<"FUN:"<<__func__  <<", LINE:" <<__LINE__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现部分
    for(int pos = 1; pos <= this->m_size; pos++)        // 循环存放编码的数组
    {
        if(m_leafChars[pos] == chType)
        {
            #ifdef DEBUG
            std::cout <<m_leafCharCodes[pos] <<std::endl;
            #endif
            return this->m_leafCharCodes[pos];
        }
    }
    throw  std::out_of_range("非法字符, 无法编码");
}

//// 函数名称：std::string EnCode(std::String strCode)             // 编码函数
//// 操作结果：对strCode字符串进行编码
//template <class CharType, class WeightType>
//std::string EnCode(std::String charCode)             // 编码函数
//{
//#ifdef DEBUG    // 插桩调试信息
//    std::cout <<"FUN:"<<__func__  <<", LINE:" <<__LINE__ <<std::endl;   // 输出函数信息
//#endif
//    // 函数实现部分
//
//}


// 函数名称：string DeCode(string strCode)                  //译码函数
// 操作结果：返回字符chType的哈夫曼编码
template <class CharType, class WeightType>
std::string HuffmanTree<CharType, WeightType>::DeCode(std::string strCode)                 // 译码函数
{
#ifdef DEBUG    // 插桩调试信息
    std::cout <<"FUN:"<<__func__  <<", LINE:" <<__LINE__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现部分
    int charPos = 0;
    //std::string charStr;                 // 存放编码序列
    char charStr[81];

    #ifdef DEBUG
    std::cout <<strCode <<std::endl;
    #endif

    for(unsigned int pos = 0; pos < strCode.size(); pos++)         // 处理strCode的每个编码位
    {
        #ifdef DEBUG
        std::cout <<strCode[pos];
        #endif
        if(strCode[pos] == '0')     // 如果当前字符是0
        {
            this->m_curPos = m_nodes[m_curPos].m_leftChild;       // 寻找左分支
            #ifdef DEBUG
            std::cout <<"寻找左分支" <<std::endl;
            #endif
        }
        else if(strCode[pos] == '1')
        {
            this->m_curPos = m_nodes[m_curPos].m_rightChild;      // 寻找右分支
            #ifdef DEBUG
            std::cout <<"寻找右分支" <<std::endl;
            #endif
        }
        else
        {
            //throw std::invalid_argument("参数不合法\n");
            std::cout <<"当前编码信息有误, 请重新输入" <<std::endl;
            return "";
        }
        if(/*m_nodes[m_curPos].m_leftChild == 0 && */m_nodes[m_curPos].m_rightChild == 0)
        {
            charStr[charPos++] =  this->m_leafChars[m_curPos];      // 插入字符信息
            this->m_curPos = 2*this->m_size-1;                      // 让当前位置指针回到根结点的位置, 以便进行下一次的查找
        }
    }
   // system("pause");
    charStr[charPos] = '\0';

    //system("pause");
    return &charStr[0];
}

// 函数名称：int Size( )
// 操作结果：返回字符chType的哈夫曼编码
template <class CharType, class WeightType>
int HuffmanTree<CharType, WeightType>::Size( )                       // 获取当前哈夫曼树的结点数目
{
#ifdef DEBUG    // 插桩调试信息
    std::cout <<"FUN:"<<__func__  <<", LINE:" <<__LINE__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现部分
    return m_size;
}

// 函数名称：Char(int pos)
// 操作结果：返回对应的pos个字符信息
template <class CharType, class WeightType>
CharType HuffmanTree<CharType, WeightType>::Char(int pos)            // 获取当前哈夫曼编码的第pos个字符编码
{
#ifdef DEBUG    // 插桩调试信息
    std::cout <<"FUN:"<<__func__  <<", LINE:" <<__LINE__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现部分
    //assert(pos >= 1 && pos <= m_size);
    if(pos <= 0 || pos > m_size)
    {
        throw std::out_of_range("参数不合法\n");
    }

    return this->m_leafChars[pos];
}


template <class CharType, class WeightType>
void HuffmanTree<CharType, WeightType>::DisplayWithShape( )  // 树形显示哈夫曼树
{
    this->DisplayWithShape(this->m_curPos, 1);

    this->m_curPos = 2*this->m_size-1;
//    std::cout <<std::endl;
//    for(int i = 1; i <= m_size; i++)
//    {
//        std::cout <<m_nodes[i].m_weight;// <<endl;
//    }
//    std::cout <<std::endl;
//
//    for(int i = 1; i <= m_size; i++)
//    {
//        std::cout <<m_leafChars[i];
//    }
//    std::cout <<std::endl;


}



#endif // HuffmanTree_H_INCLUDED
