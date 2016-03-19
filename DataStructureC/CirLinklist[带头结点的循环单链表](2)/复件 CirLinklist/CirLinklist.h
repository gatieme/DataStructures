#ifndef __CIRCirLinkList_H__
#define __CIRCirLinkList_H__


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>



#define DEBUG				// 调试插桩信息宏

///*////////////////////////////////////////////////////////////////////////////
///
///	带头结点的单链表结构体
///
///*////////////////////////////////////////////////////////////////////////////
typedef int ElemType;		// 自定义数据类型

//typedef struct CirLinkListNode*	PCirLinkListNode;			// 链表结点指针域

// 链表结点数据域
typedef struct CirLinkListNode
{
	ElemType				m_data;			// 数据域
	struct CirLinkListNode	*m_next;		// 指针域
}CirLinkListNode;

// 带头结点的单项链表
typedef struct CirLinkListNode* CirLinkList;




///*////////////////////////////////////////////////////////////////////////////
///
///	创建和初始化单链表
///
///	开辟一个单链表数据结构，并初始化头结点，然后将创建好的单链表指针返回
///	CirLinkList* CreatCirLinkList(void)
///
///	初始化单链表
///	void InitCirLinkList(CirLinkList *list)
///*///////////////////////////////////////////////////////////////////////////

/**
CirLinkList* CreatCirLinkList(void)
参数
	list	:	指向一个链表指针，此处传入表头地址
返回值
	若成功返回创建好的单链表的指针
功能
	开辟一个单链表数据结构，并初始化头结点，然后将创建好的单链表指针返回
注意
	使用CreateCirLinkList创建的单链表，需要用DestroyCirLinkList来销毁
	以免发生内存泄漏
*/
CirLinkList* CreateCirLinkList(void);



/**
void InitCirLinkList(CirLinkList *list)
参数
	list	:	指向一个链表指针，此处传入表头地址
返回值
	无
功能
	初始化单链表， 执行以下操作
	①开辟头结点的空间 ②进行必要的初始化[头结点的初始化和单链表结点数目的初始化]
注意
	使用InitCirLinkList初始化的单链表(初始化时malloc了头结点m_head的空间)
	而使用用FinitCirLinkList来进行后处理(后处理时free了头结点的m_head空间)
	以免发生内存泄漏
*/
void InitCirLinkList(CirLinkList *tail);

///*////////////////////////////////////////////////////////////////////////////
///
///	销毁以及后处理单链表
///
///	销毁用CreateCirLinkList创建的单链表
///	void DestroyCirLinkList(CirLinkList *list)
///
///	后处理单链表，
///	void FinitCirLinkList(CirLinkList *list)
///
/// 清空单链表中的所有元素
///	void ClearCirLinkList(CirLinkList *list)
///*////////////////////////////////////////////////////////////////////////////

/**
void DestroyCirLinkList(CirLinkList *list)
参数
	list	:	指向一个链表指针，此处传入表头地址
返回值
	无
功能
	销毁用CreateCirLinkList创建的单链表，执行以下操作
	①清空单链表	②释放头结点	③释放单链表
注意
	使用CreateCirLinkList创建的单链表，需要用DestroyCirLinkList来销毁
	以免发生内存泄漏
*/
CirLinkList* DestroyCirLinkList(CirLinkList *list);





/**
void FinitCirLinkList(CirLinkList *list)
参数
	list	:	指向一个链表指针，此处传入表头地址
返回值
	无
功能
	后处理单链表， 执行以下操作
	①开辟头结点的空间 ②进行必要的初始化[头结点的初始化和单链表结点数目的初始化]
注意
	使用InitCirLinkList初始化的单链表(初始化时malloc了头结点m_head的空间)
	而使用用FinitCirLinkList来进行后处理(后处理时free了头结点的m_head空间)
	以免发生内存泄漏
*/
void FinitCirLinkList(CirLinkList *list);



/**
void ClearCirLinkList(CirLinkList *list)
参数
	list	:	指向一个链表指针，此处传入表头地址
返回值
	无
功能
	清空单链表中的所有元素
*/
void ClearCirLinkList(CirLinkList *list);



///*////////////////////////////////////////////////////////////////////////////
///
///	查找函数
///
///	查找到链表list中第position个结点
///	CirLinkListNode* FindPosNode(CirLinkList *list, int position)
///
///	在链表list中找到currNode的前一个结点
///	CirLinkListNode *FindPrevNode(CirLinkList *list, CirLinkListNode *currNode)
///
/// 判断结点node指向的区域是不是链表中的结点
///	int IsNodeInList(CirLinkList *list, CirLinkListNode *node)
///
///	找到数据域为data的结点首次出现的位置并返回结点信息
///	CirLinkListNode* FindDataNode(CirLinkList *list, ElemType data, int *position)
///*////////////////////////////////////////////////////////////////////////////
/**
CirLinkListNode* FindPosNode(CirLinkList *list, int position)

参数
	list	:	指向一个链表指针，此处传入表头地址
	positon	:	带查找的链表指针的位置
返回值
	若成功返回指向待查找结点的指针
	若失败返回NULL
功能
	该函数的功能是:	查找到链表list中第position个结点
*/
CirLinkListNode* FindPosNode(CirLinkList *list, int position);


/**
CirLinkListNode *FindPrevNode(CirLinkList *list, CirLinkListNode *currNode);

参数
	list		:	指向一个链表指针，此处传入表头地址
	currNode	:	待查找的链表指针的位置
返回值
	若成功返回指向待查找结点的指针
	若失败返回NULL
功能
	在链表list中找到currNode的前一个结点
*/

CirLinkListNode *FindPrevNode(CirLinkList *list, CirLinkListNode *currNode);



/**
int IsNodeInList(CirLinkList *list, CirLinkListNode *node)

参数
	list	:	指向一个链表指针，此处传入表头地址
	node	:	指向待查找的结点的指针
返回值
	若成功 返回结点node在链表中的位置
	若失败 返回-1
功能
	判断结点node指向的区域是不是链表中的结点
*/
int IsNodeInList(CirLinkList *list, CirLinkListNode *node);


/**
CirLinkListNode* FindDataNode(CirLinkList *list, ElemType data, int *position

参数
	list	:	指向一个链表指针，此处传入表头地址
	data	:	待查找的结点的数据信息
返回值
	若成功 返回结点node在链表中的位置
	若失败 返回-1
功能
	找到数据域为data的结点首次出现的位置并返回结点信息
*/
CirLinkListNode* FindDataNode(CirLinkList *list, ElemType data, int *position);



///*////////////////////////////////////////////////////////////////////////////
///
///	插入函数
///
///	将数据data插入链表的prevNode结点的下一个位置个位置
///	CirLinkListNode *AddNode(CirLinkList *list, CirLinkListNode *prevNode, ElemType data)
///
///	将数据data插入链表的第position个位置
///	CirLinkListNode *InsertNode(CirLinkList *list, int position, ElemType data)
///*////////////////////////////////////////////////////////////////////////////
/**
void InsertNode(CirLinkList *list, int position, ElemType data)
参数
	list	:	指向一个链表指针，此处传入表头地址
	positon	:	待插入结点的位置
	data	:	待插入结点的数据
返回值
	无
功能
	该函数的功能是:	将数据data插入链表的第position个位置
*/
CirLinkListNode* InsertNode(CirLinkList *list, int position, ElemType data);


/**
CirLinkListNode* AddNode(CirLinkList *list, CirLinkListNode *prevNode, ElemType data);
参数
	list		:	指向一个链表指针，此处传入表头地址
	prevNode	:	待插入位置的前一个结点
	data		:	待插入结点的数据
返回值
	无
功能
	该函数的功能是:	将数据data插入链表的prevNode结点的下一个位置个位置
*/
CirLinkListNode* AddNode(CirLinkList *list, CirLinkListNode *prevNode, ElemType data);


///*////////////////////////////////////////////////////////////////////////////
///
///	删除函数
///
///	删除链表list中prevNode结点之后的指针个指针
///	void DeleteNode(CirLinkList *list, int position)
///
///	删除链表list中prevNode结点之后的指针个指针
///	ElemType SubNode(CirLinkList *list, CirLinkListNode *prevNode)
///
///	删除链表list中prevNode结点之后的指针个指针
///	ElemType DeleteCurrNode(CirLinkList *list, CirLinkListNode *currNode)
///*////////////////////////////////////////////////////////////////////////////

/**
void DeleteNode(CirLinkList *list, int position)
参数
	list	:	指向一个链表指针，此处传入表头地址
	positon	:	待删除结点的位置
返回值
	返回待删除结点的数据域
功能
	将单链表的第position个结点删除
*/
ElemType DeleteNode(CirLinkList *list, int position);


/**
void DeleteNode(CirLinkList *list, int position)
参数
	list	:	指向一个链表指针，此处传入表头地址
	positon	:	待删除结点的位置
返回值
	返回待删除结点的数据域
功能
	删除链表list中prevNode结点之后的指针个指针
*/
ElemType SubNode(CirLinkList *list, CirLinkListNode *prevNode);

/**
ElemType DeleteCurrNode(CirLinkList *list, CirLinkListNode *currNode);
参数
	list	:	指向一个链表指针，此处传入表头地址
	positon	:	待删除结点的位置
返回值
	返回待删除结点的数据域
功能
	删除链表list中prevNode结点之后的指针个指针
*/
ElemType DeleteCurrNode(CirLinkList *list, CirLinkListNode *currNode);

/**
void ShowCirLinkList(CirLinkList *list)
参数
	list	:	指向一个链表指针，此处传入表头地址
返回值
	无
功能
	显示单链表的信息
*/


///*////////////////////////////////////////////////////////////////////////////
///
///	其他函数
///
///	显示单链表的信息
///	void ShowList(CirLinkList *list
///
///	删除链表list中prevNode结点之后的指针个指针
///	void SetNode(CirLinkList *list, int position, ElemType data)
///
///	获取单链表list第position个结点的数据域
/// ElemType GetNode(CirLinkList *list, int position)
///
///	获取单链表list的长度[即元素个数]
///	int LengthCirLinkList(CirLinkList *list)
///
///	判断当前链表是否是空链表
///	bool IsEmptyCirLinkList(CirLinkList *list)
///
///	获取循环链表的头指针
///	CirLinkListNode* GetFisrtNode(CirLinkList *list)
///
///	获取指向头结点的指针
///	CirLinkListNode* GetHeadNode(CirLinkList *list)
///*////////////////////////////////////////////////////////////////////////////

void ShowList(CirLinkList *list);

/**
void SetNode(CirLinkList *list, int position, ElemType data)
参数
	list	:	指向一个链表指针，此处传入表头地址
	positon :	待修改的结点的数据
	data	:	待更正的新数据域
返回值
	无
功能
	修改单链表list第position个结点的数据域为data
*/
void SetNode(CirLinkList *list, int position, ElemType data);


/**
ElemType GetNode(CirLinkList *list, int position
参数
	list	:	指向一个链表指针，此处传入表头地址
	positon :	待查询的结点的位置
返回值
	获取到的结点数据
功能
	获取单链表list第position个结点的数据域
*/
ElemType GetNode(CirLinkList *list, int position);

/**
int LengthCirLinkList(CirLinkList *list)
参数
	list	:	指向一个链表指针，此处传入表头地址
返回值
	单链表的长度
功能
	获取单链表的长度
*/
int LengthCirLinkList(CirLinkList *list);


/**
bool IsEmptyCirLinkList(CirLinkList *list)
参数
	list	:	指向一个链表指针，此处传入表头地址
返回值
	如果单链表是空表，返回true
	否则返回false
功能
	获取单链表的长度
*/
bool IsEmptyCirLinkList(CirLinkList *list);

/**
CirLinkListNode* GetFisrtNode(CirLinkList *list)
参数
	list	:	指向一个链表指针，此处传入表头地址
返回值
	返回头指针
功能
	获取循环链表的头指针
*/
CirLinkListNode* GetFisrtNode(CirLinkList *list);


/**
CirLinkListNode* GetHeadNode(CirLinkList *list)
参数
	list	:	指向一个链表指针，此处传入表头地址
返回值
	返回头结点的地址
功能
	获取指向头结点的指针
*/
CirLinkListNode* GetHeadNode(CirLinkList *list);

#endif // __CIRCirLinkList_H__
