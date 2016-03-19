/**
******************************************************************************
*  CopyRight  : 2012-2013, HerBinUnversity, GatieMe                          *
*  File Name  : BinaryTree.h                                                    *
*  Description: 二叉树链表类BinaryTree模版头文件                               *
*  Author     : Gatie_Me                                                     *
*  Version    : Copyright 2012 JULY_CITY                                     *
*  Data_Time  : 2012-11-6_10:21:43                                           *
*  Content    : 数据结构与算法（C++）版书上源码                             *
******************************************************************************
**/

/**
2012/11/13_15:41
发现重大问题:
正确使用&引用符号

在 -=> 递归建立函数
    void PreCreate(BinTreeNode<ElemType> * &root, void (* Visit)(ElemType &), bool (* IsNull)(ElemType &));  // 借助Visit函数前序建立一个以root为根的链式二叉树类
    void InCreate(BinTreeNode<ElemType> * &root, void (* Visit)(ElemType &), bool (* IsNull)(ElemType &));  // 借助Visit函数中序建立一个以root为根的链式二叉树类
    void PostCreate(BinTreeNode<ElemType> * &root, void (* Visit)(ElemType &), bool (* IsNull)(ElemType &));  // 借助Visit函数后序建立一个以root为根的链式二叉树类
中参数root如果不加引用符号‘&’, 您将不得不发现您的成序无法正确运行
解决这一个问题, 如果您不使用引用, 你会发现你将不得不使用指向指针的指针**root才可以直接对指针数据进行操作


但是在获取结点数目和树深度辅助函数模版中
    int Height(const BinTreeNode<ElemType> * &root) const;	// 返回二叉树的高
	int NodeCount(const BinTreeNode<ElemType> * &root) const;// 返回二叉树的结点个数
如果你加入了引用‘&’, 您将法相您的程序压根无法通过编译
**/


#ifndef BINARYTREE_H_INCLUDED
#define BINARYTREE_H_INCLUDED

#include <stdexcept>        // 标准异常处理类机制
#include <exception>
//using namespace std;

#include "BinTreeNode.h"    // 二叉树结点类
#include "LinkQueue.h"

//#define DEBUG           // 插桩调试信息[宏定义]
#define SHOW        // 遍历函数中帮忙显示空结点的信息

/// 链式二叉树类BinaryTree声明部分
template <class ElemType>
class BinaryTree
{
/*===========================【PUBLIC：公共接口】============================*/
  public :      // 公共接口
    // 链式二叉树类BinaryTree基本成员函数
    BinaryTree( ); // 默认构造函数模版

	BinaryTree(const ElemType &elem);							// 建立以e为根的二叉树

	BinaryTree(const BinTreeNode<ElemType> * &root);					// 建立以r为根的二叉树

    BinaryTree(const BinaryTree<ElemType> &copy);     // 复制构造函数

    virtual ~BinaryTree( );            // 虚析构函数模版

    BinaryTree<ElemType> &operator=(const BinaryTree<ElemType> &copy);

    // 链式二叉树类BinaryTree特征成员函数

    // 链式二叉树类BinaryTree的信息获取函数
    int NodeCount( ) const;         // 返回二叉树的结点个数

    int Height( ) const;            // 返回二叉树的深度

    bool Empty( ) const;            // 判断二叉树是否为空

    BinTreeNode<ElemType>* Search(const ElemType &elem);        // 寻找数据元素的值

    void DeleteNode(BinTreeNode<ElemType> *node); // 删除单个结点的函数
    // 链式二叉树类BinaryTree的结点信息处理函数
    BinTreeNode<ElemType> *GetRoot( ) const;         // 返回二叉树的根结点
    ElemType GetElem(BinTreeNode<ElemType> * &cur) const;               // 返回结点cur的元素值
    void SetElem(BinTreeNode<ElemType> * &cur, ElemType &elem) const;   //修改结点cur的元素值

    // 双亲的处理函数
    BinTreeNode<ElemType> *Parent(const BinTreeNode<ElemType> * &cur) const;      // 获取cue结点的双亲结点
    // 左结点的处理函数
    BinTreeNode<ElemType> *LeftChild(const BinTreeNode<ElemType> * &cur) const; // 获取cur结点的左子结点
    void InsertLeftChild(BinTreeNode<ElemType> * &cur, const ElemType &elem); // 插入cur结点的左子结点
    void DeleteLeftChild(BinTreeNode<ElemType> * &cur); // 删除cur结点的左子结点
    // 右结点的处理函数
    BinTreeNode<ElemType> *RightChild(const BinTreeNode<ElemType> * &cur) const; // 获取cur结点的右子结点
    void InsertRightChild(BinTreeNode<ElemType> * &cur, const ElemType &elem); // 插入cur结点的右子结点
    void DeleteRightChild(BinTreeNode<ElemType> * &cur); // 删除cur结点的右子结点

    // 链式二叉树类BinaryTree遍历函数
    // 递归建立算法
    void PreCreate(void (* Visit)(ElemType &), bool (* IsNull)(ElemType &));          // 二叉树的先序遍历
    void InCreate(void (* Visit)(ElemType &), bool (* IsNull)(ElemType &));           // 二叉树的中序遍历
    void PostCreate(void (* Visit)(ElemType &), bool (* IsNull)(ElemType &));         // 二叉树的后序遍历
    // 递归遍历算法
    void PreOrder(void (* Visit)(ElemType &));          // 二叉树的先序遍历
    void InOrder(void (* Visit)(ElemType &));           // 二叉树的中序遍历
    void PostOrder(void (* Visit)(ElemType &));         // 二叉树的后序遍历

    // 非递归遍历算法
    void NonRecurPreOrder(const BinaryTree<ElemType> &root, void (* Visit)(ElemType &));  // 非递归先序遍历算法
    void NonRecurInOrder(const BinaryTree<ElemType> &root, void (* Visit)(ElemType &));   // 非递归中序遍历算法
    void NonRecurPostPrder(const BinaryTree<ElemType> &root, void (* Visit)(ElemType &)); // 非递归后序遍历算法
    void LevelOrder(void (* Visit)(ElemType &));        // 二叉树的层次遍历
/*===========================【PUBLIC：公共接口】============================*/
///////////////////////////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////////
/*=========================【PROTECTED：保护成员】===========================*/
  protected :
    // 链式二叉树类BinaryTree数据成员
    BinTreeNode<ElemType> *m_root;      // 根结点信息


    // 辅助成员函数模版[类似与C语言实现方法]

    // 基本成员函数辅助信息

	BinTreeNode<ElemType> *CopyTree(BinTreeNode<ElemType> * &copy);	// 复制二叉树链表的辅助函数
	void Destroy(BinTreeNode<ElemType> * &root);						// 销毁以root为根二叉树链表的辅助函数


    // 处理结点的辅助函数
	BinTreeNode<ElemType> *Search(BinTreeNode<ElemType> *&root, const ElemType &elem) const;	        // 搜索函数查找数据域为elem的都一个结点
		// 查找关键字为key的数据元素
    // 遍历成员函数辅助信息
    // 递归建立函数
    void PreCreate(BinTreeNode<ElemType> * &root, void (* Visit)(ElemType &), bool (* IsNull)(ElemType &));  // 借助Visit函数前序建立一个以root为根的链式二叉树类
    void InCreate(BinTreeNode<ElemType> * &root, void (* Visit)(ElemType &), bool (* IsNull)(ElemType &));  // 借助Visit函数中序建立一个以root为根的链式二叉树类
    void PostCreate(BinTreeNode<ElemType> * &root, void (* Visit)(ElemType &), bool (* IsNull)(ElemType &));  // 借助Visit函数后序建立一个以root为根的链式二叉树类

	// 递归函数的辅助函数
	void PreOrder(BinTreeNode<ElemType> * &root, void (* Visit)(ElemType &)) const;	// 先序遍历辅助函数
	void InOrder(BinTreeNode<ElemType> * &root, void (* Visit)(ElemType &)) const;	// 中序遍历辅助函数
	void PostOrder(BinTreeNode<ElemType> * &root, void (* Visit)(ElemType &)) const;// 后序遍历辅助函数
    // 非递归函数的辅助函数
    //BinTreeNode<ElemType>* GoFarLeft(BinaryTree<ElemType> *root, LinkStack<BinTreeNode<ElemType>* > &stack);
    void LevelOrder(BinTreeNode<ElemType> * &root, void (* Visit)(ElemType &)) const;        // 二叉树的层次遍历
    // 获取结点数目和树深度辅助模版
    int Height(const BinTreeNode<ElemType> *root) const;	// 返回二叉树的高
	int NodeCount(const BinTreeNode<ElemType> *root) const;// 返回二叉树的结点个数

    // 获取结点信息辅助函数
	BinTreeNode<ElemType> *Parent(BinTreeNode<ElemType> * &root, const BinTreeNode<ElemType> * &cur) const;			// 返回cur的双亲
};

/**辅助成员函数模版[实现]****************************************************************************
    // 基本成员函数辅助信息
	BinTreeNode<ElemType> *CopyTree(BinTreeNode<ElemType> *copy);	// 复制二叉树
	void Destroy(BinTreeNode<ElemType> * &root);						// 销毁以r为根二叉树
	// 处理结点的辅助函数
    void DeleteNode(BinTreeNode<ElemType> * &node); // 删除单个结点的函数
	BinTreeNode<ElemType> *SearchHelp(BinTreeNode<ElemType> *&root, const ElemType &elem) const;	        // 搜索函数查找数据域为elem的都一个结点
    // 递归建立函数
    void PreCreate(BinTreeNode<ElemType> * &root, void (* Visit)(ElemType &), bool (* IsNull)(ElemType &));  // 借助Visit函数前序建立一个以root为根的链式二叉树类
    void InCreate(BinTreeNode<ElemType> * &root, void (* Visit)(ElemType &), bool (* IsNull)(ElemType &));  // 借助Visit函数中序建立一个以root为根的链式二叉树类
    void PostCreate(BinTreeNode<ElemType> * &root, void (* Visit)(ElemType &), bool (* IsNull)(ElemType &));  // 借助Visit函数后序建立一个以root为根的链式二叉树类
    // 遍历成员函数辅助信息
	void PreOrder(BinTreeNode<ElemType> * &root, void (* Visit)(const ElemType &)) const;	// 先序遍历辅助函数
	void InOrder(BinTreeNode<ElemType> * &root, void (* Visit)(const ElemType &)) const;	// 中序遍历辅助函数
	void PostOrder(BinTreeNode<ElemType> * &root, void (* Visit)(const ElemType &)) const;// 后序遍历辅助函数
    // 获取结点数目和树深度辅助模版
    int Height(const BinTreeNode<ElemType> * &root) const;	// 返回二叉树的高
	int NodeCount(const BinTreeNode<ElemType> * &root) const;// 返回二叉树的结点个数
    // 获取结点信息辅助函数
	BinTreeNode<ElemType> *ParentHelp(BinTreeNode<ElemType> * &root, const BinTreeNode<ElemType> * &cur) const;			// 返回cur的双亲
****************************************************************************[实现]辅助成员函数模版**/
/// 基本成员函数辅助信息
// 函数名称：BinTreeNode<ElemType> *CopyTree(BinTreeNode<ElemType> *copy);
// 操作结果：递归复制每个结点的信息
template <class ElemType>
BinTreeNode<ElemType>* BinaryTree<ElemType>::CopyTree(BinTreeNode<ElemType> * &copy)	// 复制二叉树辅助函数
{
#ifdef DEBUG    // 插桩调试信息
std::cout <<"FUN:"<<__func__  <<", LINE:" <<__line__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现信息
    if(copy != NULL)    // 只要当前结点不为空
    {
        BinTreeNode<ElemType> *leftChild  = CopyTree(copy->m_leftChild);  // 搜索并复制当前结点的左子树信息
        BinTreeNode<ElemType> *rightChild = CopyTree(copy->m_rightChild); // 搜获并复制当前结点的右子树信息

		BinTreeNode<ElemType> *node = new BinTreeNode<ElemType>(copy->data, leftChild, rightChild); // 复制结点信息
        return node;        // 返回当前结点
    }
    else
    {
        return NULL;   // 结点信息为空时开始回溯
    }
}


/// 处理结点的辅助函数
// 函数名称：void DeleteNode(BinTreeNode<ElemType> *&node)
// 操作结果：删除node结点的信息
template <class ElemType>
void BinaryTree<ElemType>::DeleteNode(BinTreeNode<ElemType> *node)
{
#ifdef DEBUG    // 插桩调试信息
std::cout <<"FUN:"<<__func__  <<", LINE:" <<__line__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现信息
	BinTreeNode<ElemType> *tempPtr, *tmpF;
	if (node->m_leftChild == NULL && node->m_rightChild == NULL)
	{	// node为叶结点
		delete node;
		node = NULL;
	}
	else if (node->m_leftChild == NULL)
	{	// node只有左子树为空
		tempPtr = node;
		node = node->m_rightChild;
		delete tempPtr;
	}
	else if (node->m_rightChild == NULL)
	{	// node只有右子树非空
		tempPtr = node;
		node = node->m_leftChild;
		delete tempPtr;
	}
	else
	{	// node左右子非空
		tmpF = node;
		tempPtr = node->m_leftChild;
		while (tempPtr->m_rightChild != NULL)
		{	// 查找node在中序序列中直接前驱tempPtr及其双亲tmpF,直到tempPtr右子树为空
			tmpF = tempPtr;
			tempPtr = tempPtr->m_rightChild;
		}
		node->m_data = tempPtr->m_data;
			// 将tempPtr指向结点的数据元素值赋值给tmpF指向结点的数据元素值

		// 删除tempPtr指向的结点
		if (tmpF->m_rightChild == tempPtr)
		{	// 删除tmpF的右孩子
			DeleteNode(tmpF->m_rightChild);
		}
		else
		{	// 删除tmpF的左孩子
			DeleteNode(tmpF->m_leftChild);
		}
	}
}


// 函数名称：BinTreeNode<ElemType>* Search(BinTreeNode<ElemType> * &root, const ElemType &elem) const // 搜索函数查找数据域为elem的都一个结点
// 操作结果：按层次搜索数据域elem的结点
// 实现方法：实现方法与层次遍历的方法相同, 只需要判断数据域为elem返回就可以
template <class ElemType>
BinTreeNode<ElemType>* BinaryTree<ElemType>::Search(BinTreeNode<ElemType> * &root, const ElemType &elem) const // 搜索函数查找数据域为elem的都一个结点
{
#ifdef DEBUG    // 插桩调试信息
std::cout <<"FUN:"<<__func__  <<", LINE:" <<__line__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现信息
    if(root == NULL)
    {
        throw std::invalid_argument("参数cur为空, 无法开始层次遍历的信息\n");
    }

    LinkQueue<BinTreeNode<ElemType> *> queue;   // 建立一个数据域为当前结点类指针类型的队列
    BinTreeNode<ElemType> *node = root;          // 从当前根结点开始进行层次遍历

    queue.InQueue(node);            // 将根结点入队

    while(queue.Empty() != true)    // 只要当前队列不为空, 说明二叉树未遍历完
    {
        queue.OutQueue(node);

        //(* Visit)(node->m_data);     // 访问当前结点的数据域
        if(node->m_data == elem)        // 如果当前结点的数据域为elem
        {
            return node;
        }

        if(node->m_leftChild != NULL)   // 只要该结点左孩子存在
        {
            queue.InQueue(node->m_leftChild);   // 让左孩子入队
        }

        if(node->m_rightChild != NULL)   // 只要该结点右孩子存在
        {
            queue.InQueue(node->m_rightChild);   // 让右孩子入队
        }
    }

    return NULL;
}

// 函数名称：void Destroy(BinTreeNode<ElemType> * &root);
// 操作结果：递归销毁当前结点root的子树
template <class ElemType>
void BinaryTree<ElemType>::Destroy(BinTreeNode<ElemType> * &root)	// 销毁以r为根二叉树
{
#ifdef DEBUG    // 插桩调试信息
std::cout <<"FUN:"<<__func__  <<", LINE:" <<__line__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现信息
    if(root != NULL)    // 只要当前结点不为空
    {
        Destroy(root->m_leftChild);     // 递归销毁左子树结点
        Destroy(root->m_rightChild);    // 递归销毁右子树结点
        delete root;
        root = NULL;            // 防止出现野指针
    }
    else
    {
        return;     // 结点为空时开始回溯
    }
}

/// 递归建立函数
// 函数名称：void CreateTree(BinTreeNode<ElrmType> *root, void (* Visit)(ElemType &));
// 操作结果：借助Visit函数建立一个以root为根的链式二叉树类
template <class ElemType>
void BinaryTree<ElemType>::PreCreate(BinTreeNode<ElemType> * &root, void (* Visit)(ElemType &), bool (* IsNull)(ElemType &))  // 借助Visit函数建立一个以root为根的链式二叉树类
{
#ifdef DEBUG    // 插桩调试信息
std::cout <<"FUN:"<<__func__  <<", LINE:" <<__line__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现信息
    ElemType elem;
    (* Visit)(elem);     // 输入当前节点的数据域

    if(IsNull(elem) == true)     // 输入的结点数据域为空
    {
        root = NULL;
    }
    else
    {
        root = new BinTreeNode<ElemType>(elem);
        if(root == NULL)
        {
            std::cout <<"内存不足" <<std::endl;
            exit(-1);
        }
        else
        {
            PreCreate(root->m_leftChild, Visit, IsNull);   // 递归建立左子树
            PreCreate(root->m_rightChild, Visit, IsNull);  // 递归建立右子树
        }
    }
}
// 函数名称：void CreateTree(BinTreeNode<ElrmType> *root, void (* Visit)(ElemType &));
// 操作结果：借助Visit函数建立一个以root为根的链式二叉树类
template <class ElemType>
void BinaryTree<ElemType>::InCreate(BinTreeNode<ElemType> * &root, void (* Visit)(ElemType &), bool (* IsNull)(ElemType &))  // 借助Visit函数建立一个以root为根的链式二叉树类
{
#ifdef DEBUG    // 插桩调试信息
std::cout <<"FUN:"<<__func__  <<", LINE:" <<__line__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现信息
    ElemType elem;
    (* Visit)(elem);     // 输入当前节点的数据域

    if(IsNull(elem) == true)     // 输入的结点数据域为空
    {
        return;
    }
    else
    {
        root = new BinTreeNode<ElemType>( );
        if(root == NULL)
        {
            std::cout <<"内存不足" <<std::endl;
            exit(-1);
        }
        else
        {
            InCreate(root->m_leftChild, Visit, IsNull);   // 递归建立左子树
            root->m_data = elem;
            InCreate(root->m_rightChild, Visit, IsNull);  // 递归建立右子树
        }
    }
}
// 函数名称：void CreateTree(BinTreeNode<ElrmType> *root, void (* Visit)(ElemType &));
// 操作结果：借助Visit函数建立一个以root为根的链式二叉树类
template <class ElemType>
void BinaryTree<ElemType>::PostCreate(BinTreeNode<ElemType> * &root, void (* Visit)(ElemType &), bool (* IsNull)(ElemType &))  // 借助Visit函数建立一个以root为根的链式二叉树类
{
#ifdef DEBUG    // 插桩调试信息
std::cout <<"FUN:"<<__func__  <<", LINE:" <<__line__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现信息
    ElemType elem;
    (* Visit)(elem);     // 输入当前节点的数据域

    if(IsNull(elem) == true)     // 输入的结点数据域为空
    {
        root = NULL;
    }
    else
    {
        root = new BinTreeNode<ElemType>( );
        if(root == NULL)
        {
            std::cout <<"内存不足" <<std::endl;
            exit(-1);
        }
        else
        {
            PostCreate(root->m_leftChild, Visit, IsNull);   // 递归建立左子树
            PostCreate(root->m_rightChild, Visit, IsNull);  // 递归建立右子树
            root->m_data = elem;
        }
    }
}


/// 获取结点数目和树深度辅助模版
// 函数名称：int Height(const BinTreeNode<ElemType> * &root) const;	// 返回二叉树的高
// 操作结果：计算二叉树的深度的辅助函数[返回以root为头的二叉树的深度]
template <class ElemType>
int BinaryTree<ElemType>::Height(const BinTreeNode<ElemType> *root) const	// 返回二叉树的高
{
#ifdef DEBUG    // 插桩调试信息
std::cout <<"FUN:"<<__func__  <<", LINE:" <<__line__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现信息
    if(root != NULL)    // 只要根结点不是空的
    {
        int leftHeight = Height(root->m_leftChild);
        int rightHeight = Height(root->m_rightChild);
        return 1/*加上根结点*/ + (leftHeight > rightHeight ? leftHeight : rightHeight);
    }
    else    // 空二叉树深度为0
    {
        return 0;
    }
}


// 函数名称：int NodeCount(const BinTreeNode<ElemType> * &root) const;// 返回二叉树的结点个数
// 操作结果：计算二叉树链表结点数目的辅助函数[返回以root为头的二叉树的结点数目]
template <class ElemType>
int BinaryTree<ElemType>::NodeCount(const BinTreeNode<ElemType> *root) const// 返回二叉树的结点个数
{
#ifdef DEBUG    // 插桩调试信息
std::cout <<"FUN:"<<__func__  <<", LINE:" <<__line__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现信息
    if(root == NULL)
    {
        return 0;
    }
    else
    {
        int leftCount = NodeCount(root->m_leftChild);
        int rightCount = NodeCount(root->m_rightChild);

        return leftCount + rightCount + 1/*加上根结点*/;
    }
}


/// 遍历成员函数辅助信息
// 函数名称：void PreOrder(BinTreeNode<ElemType> * &root, void (* Visit)(const ElemType &)) const;	// 先序遍历辅助函数
// 操作结果：前序递归遍历二叉树
template <class ElemType>
void BinaryTree<ElemType>::PreOrder(BinTreeNode<ElemType> * &root, void (* Visit)(ElemType &)) const	// 先序遍历辅助函数
{
#ifdef DEBUG    // 插桩调试信息
std::cout <<"FUN:"<<__func__  <<", LINE:" <<__line__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现信息
    if(root != NULL)
    {
         (*Visit)(root->m_data);       // 先访问结点的信息
         PreOrder(root->m_leftChild, Visit);   // 递归访问其左子树
         PreOrder(root->m_rightChild, Visit);  // 递归访问其右子树
    }
    else
    {
        #ifdef SHOW     // 帮忙显示空结点的信息
        std::cout <<'#';
        #endif
        return ;        // 结点为空时开始回溯
    }
}



// 函数名称：void InOrder(BinTreeNode<ElemType> * &root, void (* Visit)(const ElemType &)) const;	// 先序遍历辅助函数
// 操作结果：中序递归遍历二叉树
template <class ElemType>
void BinaryTree<ElemType>::InOrder(BinTreeNode<ElemType> * &root, void (* Visit)(ElemType &)) const	// 中序遍历辅助函数
{
#ifdef DEBUG    // 插桩调试信息
std::cout <<"FUN:"<<__func__  <<", LINE:" <<__line__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现信息
    if(root != NULL)
    {
         InOrder(root->m_leftChild, Visit);   // 递归访问其左子树
         (*Visit)(root->m_data);       // 先访问结点的信息
         InOrder(root->m_rightChild, Visit);  // 递归访问其右子树
    }
    else
    {
        #ifdef SHOW     // 帮忙显示空结点的信息
        std::cout <<'#';
        #endif
        return ;        // 结点为空时开始回溯
    }
}

// 函数名称：void PoStrOrder(BinTreeNode<ElemType> * &root, void (* Visit)(const ElemType &)) const;	// 先序遍历辅助函数
// 操作结果：后序递归遍历二叉树
template <class ElemType>
void BinaryTree<ElemType>::PostOrder(BinTreeNode<ElemType> * &root, void (* Visit)(ElemType &)) const   // 后序遍历辅助函数
{
#ifdef DEBUG    // 插桩调试信息
std::cout <<"FUN:"<<__func__  <<", LINE:" <<__line__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现信息
    if(root != NULL)
    {
         PostOrder(root->m_leftChild, Visit);   // 递归访问其左子树
         PostOrder(root->m_rightChild, Visit);  // 递归访问其右子树
         (*Visit)(root->m_data);       // 先访问结点的信息
    }
    else
    {
        #ifdef SHOW     // 帮忙显示空结点的信息
        std::cout <<'#';
        #endif
        return ;        // 结点为空时开始回溯
    }
}


// 函数名称：void PoStrOrder(BinTreeNode<ElemType> * &root, void (* Visit)(const ElemType &)) const;	// 先序遍历辅助函数
// 操作结果：后序递归遍历二叉树
template <class ElemType>
void BinaryTree<ElemType>::LevelOrder(BinTreeNode<ElemType> * &root, void (* Visit)(ElemType &)) const   // 后序遍历辅助函数
{
#ifdef DEBUG    // 插桩调试信息
std::cout <<"FUN:"<<__func__  <<", LINE:" <<__line__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现信息
    if(root == NULL)
    {
        throw std::invalid_argument("参数cur为空, 无法开始层次遍历的信息\n");
    }

    LinkQueue<BinTreeNode<ElemType> *> queue;   // 建立一个数据域为当前结点类指针类型的队列
    BinTreeNode<ElemType> *node = root;          // 从当前根结点开始进行层次遍历

    queue.InQueue(node);            // 将根结点入队

    while(queue.Empty() != true)    // 只要当前队列不为空, 说明二叉树未遍历完
    {
        queue.OutQueue(node);

        (* Visit)(node->m_data);     // 访问当前结点的数据域

        if(node->m_leftChild != NULL)   // 只要该结点左孩子存在
        {
            queue.InQueue(node->m_leftChild);   // 让左孩子入队
        }
        if(node->m_rightChild != NULL)   // 只要该结点右孩子存在
        {
            queue.InQueue(node->m_rightChild);   // 让右孩子入队
        }
    }
}


/// 获取结点信息辅助函数
// 函数名称：BinTreeNode<ElemType> *ParentHelp(BinTreeNode<ElemType> * &root, const BinTreeNode<ElemType> * &cur) const;
// 操作结果：寻找cur结点的双亲的辅助函数
template <class ElemType>
BinTreeNode<ElemType>* BinaryTree<ElemType>::Parent(BinTreeNode<ElemType> * &root, const BinTreeNode<ElemType> * &cur) const			// 返回cur的双亲
{
#ifdef DEBUG    // 插桩调试信息
std::cout <<"FUN:"<<__func__  <<", LINE:" <<__line__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现信息
	if (root == NULL)
	{
        throw std::invalid_argument("参数cur为空, 无法获取其双亲的信息\n");
	}
	else if(root->m_leftChild == cur || root->m_rightChild == cur)
	{
	    return m_root; // 搜索找cur的双亲时返回
	}
	else
	{
		BinTreeNode<ElemType> *temp;

		temp = Parent(root->leftChild, cur);	// 在左子树上搜索cur的双亲
		if(temp != NULL)
		{
		    return temp;			// 双亲在左子树上
		}

		temp = Parent(root->rightChild, cur);	// 在右子树上搜索cur的双亲
		if(temp != NULL)
		{
		    return temp;			// 双亲在右子树上
		}
		// 如果在左右子树上都未找到则返回NULL
		else
		{
		    return NULL;						// 表示cur无双亲
	    }
	}
}


/// 链式二叉树类BinaryTree实现部分
/**链式二叉树类BinaryTree基本成员函数[实现]**********************************************************
    BinaryTree( ); // 默认构造函数模版
    BinaryTree(const ElemType &e);							// 建立以e为根的二叉树
    BinaryTree(BinTreeNode<ElemType> *r);					// 建立以r为根的二叉树
    BinaryTree(const BinaryTree<ElemType> &copy);     // 复制构造函数
    virtual ~BinaryTree( );                // 虚析构函数模版
    BinaryTree<ElemType> &operator=(const BinaryTree<ElemType> &copy);
    // 链式二叉树类BinaryTree的信息初始函数
    void CreateTree(void (* Visit)(ElemType &), bool (* IsNull)(ElemType &));         // 借助Visit函数建立一个链式二叉树类
**********************************************************[实现]链式二叉树类BinaryTree基本成员函数**/
// 函数名称：BinaryTree( ); // 默认构造函数模版
// 操作结果：建立一个空二叉树链表
template <class ElemType>
BinaryTree<ElemType>::BinaryTree( )
{
#ifdef DEBUG    // 插桩调试信息
std::cout <<"FUN:"<<__func__  <<", LINE:" <<__line__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现信息
    m_root = NULL;
}

// 函数名称：BinaryTree(const ElemType &elem);
// 操作结果：建立以e为根的二叉树
template <class ElemType>
BinaryTree<ElemType>::BinaryTree(const ElemType &elem)							// 建立根的数据域为elem二叉树
{
    this->m_root = new BinTreeNode<ElemType>(elem);
}


// 函数名称：BinaryTree(BinTreeNode<ElemType> *root)
// 操作结果：建立以root为根的二叉树
template <class ElemType>
BinaryTree<ElemType>::BinaryTree(const BinTreeNode<ElemType> * &root)					// 建立以root为根的二叉树
{
    this->m_root = root;
}


// 函数名称：BinaryTree(const BinaryTree<ElemType> &copy);     // 复制构造函数
// 操作结果：依据copy对象创建一个二叉树链表
template <class ElemType>
BinaryTree<ElemType>::BinaryTree(const BinaryTree<ElemType> &copy)     // 复制构造函数
{
#ifdef DEBUG    // 插桩调试信息
std::cout <<"FUN:"<<__func__  <<", LINE:" <<__line__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现信息
    CopyTree(this->m_root);   // 调用辅助函数递归复制以m_root为根的二叉树
}

// 函数名称：virtual ~BinaryTree( );
// 操作结果；销毁二叉树链表的内存空间
template <class ElemType>
BinaryTree<ElemType>::~BinaryTree( )      // 虚析构函数模版
{
#ifdef DEBUG    // 插桩调试信息
std::cout <<"FUN:"<<__func__  <<", LINE:" <<__line__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现信息
    Destroy(this->m_root);
}

// 函数名称：BinaryTree<ElemType> &operator=(const BinaryTree<ElemType> &copy);
// 操作结果：赋值函数[虫子啊赋值运算符]
template <class ElemType>
BinaryTree<ElemType>& BinaryTree<ElemType>::operator=(const BinaryTree<ElemType> &copy)   // 赋值函数
{
#ifdef DEBUG    // 插桩调试信息
std::cout <<"FUN:"<<__func__  <<", LINE:" <<__line__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现信息
    if (this != &copy)
	{
		Destroy(this->m_root);				// 释放二叉树所占用的内存空间
		m_root = CopyTree(copy.root);	        // 复制二叉树新信息
	}

	return *this;
}

/**链式二叉树类BinaryTree的信息获取函数[实现]*********************************************************
    int NodeCount( ) const;         // 返回二叉树的结点个数
    int Height( ) const;            // 返回二叉树的深度
    bool Empty( ) const;            // 判断二叉树是否为空
    BinTreeNode<ElemType>* Search(const ElemType &elem);        // 寻找数据元素的值
*********************************************************链式二叉树类BinaryTree的信息获取函数[实现]**/
// 函数名称：int NodeCount( ) const;         // 返回二叉树的结点个数
// 操作结果：计算当前二叉树链表的结点个数
template <class ElemType>
int BinaryTree<ElemType>::NodeCount( ) const         // 返回二叉树的结点个数
{
#ifdef DEBUG    // 插桩调试信息
std::cout <<"FUN:"<<__func__  <<", LINE:" <<__line__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现信息
    return NodeCount(this->m_root);
}

// 函数名称：int Height( ) const;            // 返回二叉树的深度
// 操作结果：计算当前二叉树链表的深度
template <class ElemType>
int BinaryTree<ElemType>::Height( ) const            // 返回二叉树的深度
{
#ifdef DEBUG    // 插桩调试信息
std::cout <<"FUN:"<<__func__  <<", LINE:" <<__line__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现信息
    return Height(this->m_root);
}


// 函数名称：bool Empty( ) const;            // 判断二叉树是否为空
// 操作结果：判断当前二叉树链表是否为空
template <class ElemType>
bool BinaryTree<ElemType>::Empty( ) const
{
#ifdef DEBUG    // 插桩调试信息
std::cout <<"FUN:"<<__func__  <<", LINE:" <<__line__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现信息
    return (m_root == NULL);
}

// 函数名称： BinTreeNode<ElemType>*  Search(const ElemType &elem);        // 寻找数据元素的值
template <class ElemType>
BinTreeNode<ElemType>*  BinaryTree<ElemType>::Search(const ElemType &elem)        // 寻找数据元素的值
{
    return this->Search(m_root, elem);
}

/**链式二叉树类BinaryTree的结点信息获取函数[实现]*****************************************************
    BinTreeNode<ElemType> *GetRoot( ) const;         // 返回二叉树的根结点
    ElemType GetElem(BinTreeNode<ElemType> * &cur) const;               // 返回结点cur的元素值
    bool SetElem(BinTreeNode<ElemType> * &cur, ElemType &elem) const;   // 修改结点cur的元素值
    // 双亲的处理函数
    BinTreeNode<ElemType> *Parent(const BinTreeNode<ElemType> * &cur);      // 获取cue结点的双亲结点
    // 左结点的处理函数
    BinTreeNode<ElemType> *LeftChild(const BinTreeNode<ElemType> * &cur) const; // 获取cur结点的左子结点
    BinTreeNode<ElemType> *InsertLeftChild(const BinTreeNode<ElemType> * &cur) const; // 插入cur结点的左子结点
    BinTreeNode<ElemType> *DeleteLeftChild(const BinTreeNode<ElemType> * &cur) const; // 删除cur结点的左子结点
    // 右结点的处理函数
    BinTreeNode<ElemType> *RightChild(const BinTreeNode<ElemType> * &cur) const; // 获取cur结点的右子结点
    BinTreeNode<ElemType> *InsertRightChild(const BinTreeNode<ElemType> * &cur) const; // 插入cur结点的右子结点
    BinTreeNode<ElemType> *DeleteRightChild(const BinTreeNode<ElemType> * &cur) const; // 删除cur结点的右子结点
    // 链式二叉树类BinaryTree遍历函数
    void PreOrder(void (* Visit)(ElemType &));          // 二叉树的先序遍历
    void InOrder(void (* Visit)(ElemType &));           // 二叉树的中序遍历
    void PostOrder(void (* Visit)(ElemType &));         // 二叉树的后序遍历
    void LevelOrder(void (* Visit)(ElemType &));        // 二叉树的层次遍历
*****************************************************[实现]链式二叉树类BinaryTree的结点信息获取函数**/
template <class ElemType>
BinTreeNode<ElemType>* BinaryTree<ElemType>::GetRoot( ) const         // 返回二叉树的根结点
{
#ifdef DEBUG    // 插桩调试信息
std::cout <<"FUN:"<<__func__  <<", LINE:" <<__line__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现信息
    return m_root;      // 返回二叉树的根结点
}


// 函数名称：ElemType GetElem(BinTreeNode<ElemType> * &cur) const;               // 返回结点cur的元素值
// 操作结果：返回结点cur的结点元素值
template <class ElemType>
ElemType BinaryTree<ElemType>::GetElem(BinTreeNode<ElemType> * &cur) const               // 返回结点cur的元素值
{
#ifdef DEBUG    // 插桩调试信息
std::cout <<"FUN:"<<__func__  <<", LINE:" <<__line__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现信息
    if(cur == NULL)
    {
        throw std::invalid_argument("参数cur为空, 无法获取其结点元素信息\n");
    }
    else
    {
        return cur->m_data;     // 返回元素值
    }
}


// 函数名称：bool SetElem(BinTreeNode<ElemType> * &cur, ElemType &elem) const;   // 修改结点cur的元素值
// 操作结果：更改cur结点的数据值
template <class ElemType>
void BinaryTree<ElemType>::SetElem(BinTreeNode<ElemType> * &cur, ElemType &elem) const   // 修改结点cur的元素值
{
#ifdef DEBUG    // 插桩调试信息
std::cout <<"FUN:"<<__func__  <<", LINE:" <<__line__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现信息
    if(cur == NULL)
    {
        throw std::invalid_argument("参数cur为空, 无法获取其结点元素信息\n");
    }
    else
    {
        cur->m_data = elem;     // 更改结点数据
    }
}


// 双亲的处理函数
// 函数名称：BinTreeNode<ElemType> *Parent(const BinTreeNode<ElemType> * &cur);      // 获取cue结点的双亲结点
// 操作结果：返回cur结点的父母结点
template <class ElemType>
BinTreeNode<ElemType>* BinaryTree<ElemType>::Parent(const BinTreeNode<ElemType> * &cur) const     // 获取cue结点的双亲结点
{
#ifdef DEBUG    // 插桩调试信息
std::cout <<"FUN:"<<__func__  <<", LINE:" <<__line__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现信息
    return ParentHelp(this->m_root, cur);      // 调用辅助函数
}



/// 左结点的处理函数
// 函数名称：BinTreeNode<ElemType> *LeftChild(const BinTreeNode<ElemType> * &cur) const; // 获取cur结点的左子结点
// 操作结果：返回cur的左子结点
template <class ElemType>
BinTreeNode<ElemType>* BinaryTree<ElemType>::LeftChild(const BinTreeNode<ElemType> * &cur) const // 获取cur结点的左子结点
{
#ifdef DEBUG    // 插桩调试信息
std::cout <<"FUN:"<<__func__  <<", LINE:" <<__line__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现信息
    if(cur == NULL)
    {
        throw std::invalid_argument("参数cur为空, 无法获取其左子节点的信息\n");
    }
    else
    {
        return cur->m_leftChild;     // 返回其左子节点的信息
    }
}


// 函数名称：BinTreeNode<ElemType> *InsertLeftChild(const BinTreeNode<ElemType> * &cur) const; // 插入cur结点的左子结点
// 操作结果：插入cur的左子结点, 如果cur的左子节点存在, 则cur原有左子树成为elem结点的左子树
template <class ElemType>
void BinaryTree<ElemType>::InsertLeftChild(BinTreeNode<ElemType> * &cur, const ElemType &elem) // 插入cur结点的左子结点
{
#ifdef DEBUG    // 插桩调试信息
std::cout <<"FUN:"<<__func__  <<", LINE:" <<__line__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现信息
	if(cur == NULL)
	{	// cur为空，返回
        throw std::invalid_argument("参数cur为空, 无法插入其左子节点的信息\n");
	}
	else
	{	// 插入右孩子
		BinTreeNode<ElemType> *newLeftChild =  new BinTreeNode<ElemType>(elem);// elem作为数据域的结点
		if (cur->m_leftChild != NULL)
		{	// cur的右孩子非空
			newLeftChild->m_leftChild = cur->m_leftChild;	// cur原有右子树成为e的右子树
		}
		cur->m_leftChild = newLeftChild;					// e成为cur的右孩子
	}
}


// 函数名称：BinTreeNode<ElemType> *DeleteLeftChild(const BinTreeNode<ElemType> * &cur) const; // 删除cur结点的左子树
// 操作结果：
template <class ElemType>
void BinaryTree<ElemType>::DeleteLeftChild(BinTreeNode<ElemType> * &cur)// 删除cur结点的左子树
{
#ifdef DEBUG    // 插桩调试信息
std::cout <<"FUN:"<<__func__  <<", LINE:" <<__line__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现信息
    if(cur == NULL)
    {
        throw std::invalid_argument("参数cur为空, 无法删除其左子树");
    }
	else
	{	// cur非空
		Destroy(cur->m_leftChild);	// 删除cur左子树
	}
}

/// 右结点的处理函数
// 函数名称：BinTreeNode<ElemType> *RightChild(const BinTreeNode<ElemType> * &cur) const; // 获取cur结点的右子结点
// 操作结果：删除二叉树结点cur的左子树
template <class ElemType>
BinTreeNode<ElemType>* BinaryTree<ElemType>::RightChild(const BinTreeNode<ElemType> * &cur) const // 获取cur结点的右子结点
{
#ifdef DEBUG    // 插桩调试信息
std::cout <<"FUN:"<<__func__  <<", LINE:" <<__line__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现信息
    if(cur == NULL)
    {
        throw std::invalid_argument("参数cur为空, 无法获取其左子结点的信息\n");
    }
    else
    {
        return cur->m_leftChild;     // 返回右子节点
    }
}


// 函数名称：BinTreeNode<ElemType> *InsertRightChild(const BinTreeNode<ElemType> * &cur) const; // 插入cur结点的右子结点
// 操作结果：插入cur的右子结点, 如果cur的右子节点存在, 则cur原有右子树成为elem结点的右子树
template <class ElemType>
void BinaryTree<ElemType>::InsertRightChild(BinTreeNode<ElemType> * &cur, const ElemType &elem) // 插入cur结点的右子结点
{
#ifdef DEBUG    // 插桩调试信息
std::cout <<"FUN:"<<__func__  <<", LINE:" <<__line__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现信息
	if(cur == NULL)
	{	// cur为空，返回
        throw std::invalid_argument("参数cur为空, 无法插入其右子结点的信息\n");
	}
	else
	{	// 插入右孩子
		BinTreeNode<ElemType> *newRightChild =  new BinTreeNode<ElemType>(elem);// elem作为数据域的结点
		if (cur->m_rightChild != NULL)
		{	// cur的右孩子非空
			newRightChild->m_rightChild = cur->m_rightChild;	// cur原有右子树成为e的右子树
		}
		cur->m_rightChild = newRightChild;					// e成为cur的右孩子
	}
}

// 函数名称：BinTreeNode<ElemType> *DeleteRightChild(const BinTreeNode<ElemType> * &cur) const; // 删除cur结点的右子结点
// 操作结果：删除二叉树结点cur的右子树
template <class ElemType>
void BinaryTree<ElemType>::DeleteRightChild(BinTreeNode<ElemType> * &cur) // 删除cur结点的右子结点
{
#ifdef DEBUG    // 插桩调试信息
std::cout <<"FUN:"<<__func__  <<", LINE:" <<__line__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现信息
    if(cur == NULL)
    {
        throw std::invalid_argument("参数cur为空, 无法删除其右子树");
    }
	else
	{	// cur非空
		Destroy(cur->m_rightChild);	// 删除cur左子树
	}
}

// 递归建立算法
// 函数名称：void PreCreate(void (* Visit)(ElemType &), bool (* IsNull)(ElemType &))
// 操作结果：前序建立链式二叉树
template <class ElemType>
void BinaryTree<ElemType>::PreCreate(void (* Visit)(ElemType &), bool (* IsNull)(ElemType &))         // 借助Visit函数建立一个链式二叉树类
{
#ifdef DEBUG    // 插桩调试信息
std::cout <<"FUN:"<<__func__  <<", LINE:" <<__line__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现信息
    PreCreate(this->m_root, Visit, IsNull);
}

// 函数名称：void PreCreate(void (* Visit)(ElemType &), bool (* IsNull)(ElemType &))
// 操作结果：中序建立链式二叉树
template <class ElemType>
void BinaryTree<ElemType>::InCreate(void (* Visit)(ElemType &), bool (* IsNull)(ElemType &))           // 二叉树的中序遍历
{
#ifdef DEBUG    // 插桩调试信息
std::cout <<"FUN:"<<__func__  <<", LINE:" <<__line__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现信息
    InCreate(this->m_root, Visit, IsNull);
}

// 函数名称：void PreCreate(void (* Visit)(ElemType &), bool (* IsNull)(ElemType &))
// 操作结果：后序建立链式二叉树
template <class ElemType>
void BinaryTree<ElemType>::PostCreate(void (* Visit)(ElemType &), bool (* IsNull)(ElemType &))        // 二叉树的后序遍历
{
#ifdef DEBUG    // 插桩调试信息
std::cout <<"FUN:"<<__func__  <<", LINE:" <<__line__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现信息
    PostCreate(this->m_root, Visit, IsNull);
}
/// 链式二叉树类BinaryTree遍历函数

// 函数名称：void PreOrder(void (* Visit)(ElemType &));          // 二叉树的先序遍历
// 操作结果：先序遍历二叉树
template <class ElemType>
void BinaryTree<ElemType>::PreOrder(void (* Visit)(ElemType &))          // 二叉树的先序遍历
{
#ifdef DEBUG    // 插桩调试信息
std::cout <<"FUN:"<<__func__  <<", LINE:" <<__line__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现信息
    PreOrder(this->m_root, Visit);      // 先序遍历
}


// 函数名称：void InOrder(void (* Visit)(ElemType &));           // 二叉树的中序遍历
// 操作结果：中序遍历二叉树
template <class ElemType>
void BinaryTree<ElemType>::InOrder(void (* Visit)(ElemType &))           // 二叉树的中序遍历
{
#ifdef DEBUG    // 插桩调试信息
std::cout <<"FUN:"<<__func__  <<", LINE:" <<__line__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现信息
    InOrder(this->m_root, Visit);
}


// 函数名称：void PostOrder(void (* Visit)(ElemType &));         // 二叉树的后序遍历
// 操作结果：后序遍历二叉树
template <class ElemType>
void BinaryTree<ElemType>::PostOrder(void (* Visit)(ElemType &))          // 二叉树的后序遍历
{
#ifdef DEBUG    // 插桩调试信息
std::cout <<"FUN:"<<__func__  <<", LINE:" <<__line__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现信息
    PostOrder(this->m_root, Visit); // 先序遍历
}


// 函数名称：void LevelOrder(void (* Visit)(ElemType &));        // 二叉树的层次遍历
// 操作结果：层次遍历二叉树
template <class ElemType>
void BinaryTree<ElemType>::LevelOrder(void (* Visit)(ElemType &))           // 二叉树的中序遍历
{
#ifdef DEBUG    // 插桩调试信息
std::cout <<__func__ <<std::endl;   // 输出函数信息
#endif
    // 函数实现信息
    LevelOrder(m_root, Visit); // 中序遍历
}


#endif // BinaryTree_H_INCLUDED
