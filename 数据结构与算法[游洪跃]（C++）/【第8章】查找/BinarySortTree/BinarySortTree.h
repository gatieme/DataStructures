/**
******************************************************************************
*  CopyRight  : 2012-2013, HerBinUnversity, GatieMe                          *
*  File Name  : BinTreeNode.h                                                *
*  Description: 二叉排序树BinarySortTree头文件                              *
*  Author     : Gatie_Me                                                     *
*  Version    : Copyright 2012 JULY_CITY                                     *
*  Data_Time  : 2012-11-6_10:21:43                                           *
*  Content    : 数据结构与算法（C++）版书上源码                             *
******************************************************************************
**/


#ifndef BINARYSORTTREE_H_INCLUDED
#define BINARYSORTTREE_H_INCLUDED

/// 二叉排序树BinarySortTree声明部分
template <class ElemType, class KeyType>
class BinarySortTree
{
/*===========================【PUBLIC：公共接口】============================*/
  public :      // 公共接口
    // 二叉排序树BinarySortTree基本成员函数
    BinarySortTree( );          // 默认构造函数

    BinarySortTree(BinTreeNode<ElemType> *root);        // 建立以root为根的二叉排序树

    BinarySortTree(const BinarySortTree<ElemType, KeyType> &copy); // 复制构造函数

    BinarySortTree<ElemType, KeyType> &operator=(const BinarySortTree<ElemType, KeyType> &copy);    // 重载赋值运算符
    virtual ~BinarySortTree( );         // 虚析构函数

    // 二叉排序树BinarySortTree特征成员函数
    BinTreeNode<ElemType>* GetRoot( ) const;      // 获取二叉排序树的根

    bool Empty( ) const;                // 判断当前二叉排序树是不是空

    int NodeCount( ) const;             // 求二叉排序树的结点个数

    int Height( ) const;                // 求二叉排序树的高度

    BinTreeNode<ElemType>* LeftChild(const BinTreeNode<ElemType> *cur) const;       // 返回二叉排序树的左孩子

    BinTreeNode<ElemType>* RightChild(const BinTreeNode<ElemType> *cur) const;       // 返回二叉排序树的左孩子

    BinTreeNode<ElemType>* Parent(const BinTreeNode<ElemType> *cur) const;       // 返回二叉排序树的左孩子

    bool GetElem(BinarySortTree<ElemType> *cur, ElemType &elem) const;  // 用elem返回结点数据元素值
    ElemType GetElem(BinarySortTree<ElemType> *cur) const;              // 直接返回结点数据元素值

    bool SetElem(BinarySortTree<ElemType> *cur, ElemType &elem) const;  // 更改cue结点数据元素值为elem

    // 二叉排序树BinarySortTree遍历函数
    void InOrder(void (* Visit)(const ElemType &)) const;               // 二叉排序树的中序遍历

    void PreOrder(void (* Visit)(const ElemType &)) const;               // 二叉排序树的先序遍历

    void PostOrder(void (* Visit)(const ElemType &)) const;               // 二叉排序树的后序遍历

    void LevelOrder(void (* Visit)(const ElemType &)) const;               // 二叉排序树的层次遍历
/*===========================【PUBLIC：公共接口】============================*/
///////////////////////////////////////////////////////////////////////////////
//
//
/////////////////////////////////////////////////////////////////////////////////
/*===========================【PROTECTED:保护成员】============================*/
  protected :   // 保护数据成员
    // 二叉排序树BinarySortTree数据成员
    BinTreeNode *m_root;          // 二叉树根结点

    // 二叉排序树BinarySortTree辅助函数模版
    BinTreeNode<ElemType> *CopyTree(BinarySortTree<ElemType> *copy);    // 复制二叉排序树

    void Destroy(BinTreeNode<ElemType> * &root);        // 销毁以root为根的二叉排序树

    void InOrder(const BinTreeNode<ElemType> * &root, void (* Visit)(const ElemType &)) const;               // 二叉排序树的中序遍历

    void PreOrder(const BinTreeNode<ElemType> * &root, void (* Visit)(const ElemType &)) const;               // 二叉排序树的先序遍历

    void PostOrder(const BinTreeNode<ElemType> * &root, void (* Visit)(const ElemType &)) const;               // 二叉排序树的后序遍历

    void LevelOrder(const BinTreeNode<ElemType> * &root, void (* Visit)(const ElemType &)) const;               // 二叉排序树的层次遍历

/*===========================【PROTECTED:保护成员】============================*/
};
#endif // BINARYSORTTREE_H_INCLUDED
