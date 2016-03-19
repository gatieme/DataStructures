#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

//#define DEBUG				// 调试插桩信息宏

///*////////////////////////////////////////////////////////////////////////////
///
///	不带头结点的单链表结构体
///
///*////////////////////////////////////////////////////////////////////////////

typedef int ElemType;		// 自定义数据类型

//typedef struct LinkListNode*	PLinkListNode;			// 链表结点指针域

// 链表结点数据域
typedef struct LinkListNode
{
	ElemType			m_data;			// 数据域
	struct LinkListNode	*m_next;			// 指针域
}LinkListNode;

// 不带头结点的单项链表
typedef struct LinkListNode*  LinkList;


///*////////////////////////////////////////////////////////////////////////////
///
///	初始化单链表
///
///	初始化单链表
///	void InitLinkList(LinkList *list)
///*///////////////////////////////////////////////////////////////////////////

/**
void InitLinkList(LinkList *list)
参数
	list	:	指向一个链表指针，此处传入表头地址
返回值
	无
功能
	初始化单链表， 执行以下操作
	①开辟头结点的空间 ②进行必要的初始化[头结点的初始化和单链表结点数目的初始化]
注意
	使用InitLinkList初始化的单链表(初始化时malloc了头结点m_head的空间)
	而使用用FinitLinkList来进行后处理(后处理时free了头结点的m_head空间)
	以免发生内存泄漏
*/
void InitLinkList(LinkList *list)
{
	(*list) = NULL;			// 初始化只头指针
}


///*////////////////////////////////////////////////////////////////////////////
///
///	销毁以及后处理单链表
///
///	后处理单链表，
///	void FinitLinkList(LinkList *list)
///
/// 清空单链表中的所有元素
///	void ClearLinkList(LinkList *list)
///*////////////////////////////////////////////////////////////////////////////

/**
void FinitLinkList(LinkList *list)
参数
	list	:	指向一个链表指针，此处传入表头地址
返回值
	无
功能
	后处理单链表， 执行以下操作
	①开辟头结点的空间 ②进行必要的初始化[头结点的初始化和单链表结点数目的初始化]
注意
	使用InitLinkList初始化的单链表(初始化时malloc了头结点m_head的空间)
	而使用用FinitLinkList来进行后处理(后处理时free了头结点的m_head空间)
	以免发生内存泄漏
*/
void FinitLinkList(LinkList *list)
{
	(*list) = NULL;
}



/**
void ClearLinkList(LinkList *list)
参数
	list	:	指向一个链表指针，此处传入表头地址
返回值
	无
功能
	清空单链表中的所有元素
*/
void ClearLinkList(LinkList *list)
{
    while((*list) != NULL)
	{
        DeleteNode(list, 0);
	}
}


///*////////////////////////////////////////////////////////////////////////////
///
///	查找函数
///
///	查找到链表list中第position个结点
///	LinkListNode* FindPosNode(LinkList *list, int position)
///
///	在链表list中找到currNode的前一个结点
///	LinkListNode *FindPrevNode(LinkList *list, LinkListNode *currNode)
///
/// 判断结点node指向的区域是不是链表中的结点
///	int IsNodeInList(LinkList *list, LinkListNode *node)
///
///	找到数据域为data的结点首次出现的位置并返回结点信息
///	LinkListNode* FindDataNode(LinkList *list, ElemType data, int *position)
///*////////////////////////////////////////////////////////////////////////////

/**
LinkListNode* FindPosNode(LinkList *list, int position)

参数
	list	:	指向一个链表指针，此处传入表头地址
	positon	:	带查找的链表指针的位置
返回值
	若成功返回指向待查找结点的指针
	若失败返回NULL
功能
	该函数的功能是:	查找到链表list中第position个结点
*/
LinkListNode* FindPosNode(LinkList *list, int position)
{
	assert(list != NULL);
	assert((*list) != NULL);									// 链表不能为空
	assert(position >= 0 && position < LengthLinkList(list));		// 查找的位置只能在[0, length)

	LinkListNode 	*pNode	= (LinkListNode *)(*list);
    int 			pos 	= 0;

    while(pNode != NULL && pos < position)		// 遍历单链表，找到第position个结点的位置
	{
		pNode = pNode->m_next;
		pos++;
	}

	if(pNode == NULL || pos < position)
	{
		return NULL;
	}
	else
	{
#ifdef DEBUG
		printf("Find the %d point SUCCESS...[%p]\n", position, pNode);
#endif // DEBUG
		return pNode;
	}
}

/**
LinkListNode *FindPrevNode(LinkList *list, LinkListNode *currNode);

参数
	list		:	指向一个链表指针，此处传入表头地址
	currNode	:	待查找的链表指针的位置
返回值
	若成功返回指向待查找结点的指针
	若失败返回NULL
功能
	在链表list中找到currNode的前一个结点
*/

LinkListNode *FindPrevNode(LinkList *list, LinkListNode *currNode)
{
	assert(list != 	NULL);
	assert(currNode != NULL);

	LinkListNode *pNode = (LinkListNode *)(*list);

	while(pNode->m_next != NULL && pNode->m_next != currNode)
	{
		pNode = pNode->m_next;
	}

	if(pNode->m_next == currNode)				// 查找成功
	{
		return pNode;
	}
	else										// 查找失败
	{
		return NULL;
	}
}

/**
int IsNodeInList(LinkList *list, LinkListNode *node)

参数
	list	:	指向一个链表指针，此处传入表头地址
	node	:	指向待查找的结点的指针
返回值
	若成功 返回结点node在链表中的位置
	若失败 返回-1
功能
	判断结点node指向的区域是不是链表中的结点
*/
int IsNodeInList(LinkList *list, LinkListNode *node)
{
	assert(list != NULL);									// 链表不能为空	assert(Node != NULL);									// 待查找的指针不能为空

	LinkListNode 	*pNode	= (LinkListNode *)(*list);
    int 			pos 	= -1;

    while(pNode != NULL && pNode != node)		// 遍历单链表，找到第position个结点的位置
	{
		pNode = pNode->m_next;
		pos++;
	}

	if(pNode == NULL)
	{	// 查找成功
		return -1;
	}
	else
	{	// 查找失败
#ifdef DEBUG
		printf("Find the [%p] point in the first %d pointer of the list...\n", node, pos);
#endif // DEBUG
		return pos;
	}
}


/**
LinkListNode* FindDataNode(LinkList *list, ElemType data, int *position

参数
	list	:	指向一个链表指针，此处传入表头地址
	data	:	待查找的结点的数据信息
返回值
	若成功 返回结点node在链表中的位置
	若失败 返回-1
功能
	找到数据域为data的结点首次出现的位置并返回结点信息
*/
LinkListNode* FindDataNode(LinkList *list, ElemType data, int *position)
{
	LinkListNode *node = (LinkListNode *)(*list);
	int pos = 0;
	while(node != NULL && node->m_data != data)
	{
		node = node->m_next;
		pos++;
	}
	*position = pos;				// 将出现的位置传递回去

	return node;					// 返回结点的信息
}


///*////////////////////////////////////////////////////////////////////////////
///
///	插入函数
///
///	将数据data插入链表的prevNode结点的下一个位置个位置
///	LinkListNode *AddNode(LinkList *list, LinkListNode *prevNode, ElemType data)
///
///	将数据data插入链表的第position个位置
///	LinkListNode *InsertNode(LinkList *list, int position, ElemType data)
///*////////////////////////////////////////////////////////////////////////////

/**
void InsertNode(LinkList *list, int position, ElemType data)
参数
	list	:	指向一个链表指针，此处传入表头地址
	positon	:	待插入结点的位置
	data	:	待插入结点的数据
返回值
	无
功能
	该函数的功能是:	将数据data插入链表的第position个位置
*/
LinkListNode* InsertNode(LinkList *list, int position, ElemType data)
{
	assert(position >=0 && position < LengthLinkList(list) + 1);	// 插入的位置应该在[0-length]

	LinkListNode *pNode = NULL;
	LinkListNode *newNode = NULL;

	// 为新结点开辟空间并且
	if((newNode = (LinkListNode *)malloc(sizeof(LinkListNode))) == NULL)	// 为新结点开辟空间
	{	// 开辟新结点失败
		fprintf(stderr, "not enough memeory\n");
        exit(EXIT_FAILURE);
	}
	else
	{	// 开辟新结点成功并且赋值
		newNode->m_data = data;
		newNode->m_next = NULL;
	}

	// 将新结点添加在链表中
	if(position == 0)			// 如果要插入第一个元素
	{
		// 如果当前链表是空链表
		if(list != NULL && (*list) == NULL)	// LinkList list = NULL创建的空链表
		{	// 此时(*list)->m_next会出现ERROR
			(*list) = newNode;
		}
		else								// 否则链表不是空链表
		{
			newNode->m_next = (*list);
			(*list) = newNode;
		}
	}
	else								// 否则当前链表不是空链表
	{
		pNode = FindPosNode(list, position - 1);		// 找到待插入点的前一个指针
		// 将指针newNode连接在pNode的后面
		newNode->m_next = pNode->m_next;
		pNode->m_next = newNode;
	}
#ifdef DEBUG
	printf("Insert the value %d into list at position %d...\n", data, position);
#endif // DEBUG

	return newNode;					// 返回指向插入的新结点的指针
}

/**
LinkListNode* AddNode(LinkList *list, LinkListNode *prevNode, ElemType data);
参数
	list		:	指向一个链表指针，此处传入表头地址
	prevNode	:	待插入位置的前一个结点
	data		:	待插入结点的数据
返回值
	无
功能
	该函数的功能是:	将数据data插入链表的prevNode结点的下一个位置个位置
[注意]	由于单链表不存在链表头，那么第一个元素不存在前驱，因此插入第一个元素时，默认其prevNode是list
*/
LinkListNode *AddNode(LinkList *list, LinkListNode *prevNode, ElemType data)
{
	assert(prevNode != NULL);						// 插入点不能是空指针

	LinkListNode *newNode = NULL;
	if((newNode = (LinkListNode *)malloc(sizeof(LinkListNode))) == NULL)	// 为新结点开辟空间
	{	// 开辟新结点失败
		fprintf(stderr, "not enough memeory\n");
        exit(EXIT_FAILURE);
	}
	//else
	//{
	// 开辟新结点成功
	newNode->m_data = data;
	newNode->m_next = NULL;
	if(prevNode == (LinkListNode *)(*list))		// 如果要插入的元素是第一个元素
	{
		if(list != NULL && (*list) == NULL)	// 如果当前链表是空链表(LinkList list = NULL创建的空链表)
		{	// 此时(*list)->m_next会出现ERROR
			(*list) = newNode;
		}
		else								// 否则链表不是空链表
		{
			newNode->m_next = (*list)->m_next;
			(*list) = newNode;
		}
	}
	else
	{
		// 将指针newNode连接在pNode的后面
		newNode->m_next = prevNode->m_next;
		prevNode->m_next = newNode;
	}

#ifdef DEBUG
	printf("The new node is inserted after point pointer[%p]\n", prevNode);
#endif // DEBUG
	return newNode;
}

///*////////////////////////////////////////////////////////////////////////////
///
///	删除函数
///
///	删除链表list中prevNode结点之后的指针个指针
///	void DeleteNode(LinkList *list, int position)
///
///	删除链表list中prevNode结点之后的指针个指针
///	ElemType SubNode(LinkList *list, LinkListNode *prevNode)
///
///	删除链表list中prevNode结点之后的指针个指针
///	ElemType DeleteCurrNode(LinkList *list, LinkListNode *currNode)
///*////////////////////////////////////////////////////////////////////////////

/**
ElemType DeleteNode(LinkList *list, int position);
参数
	list	:	指向一个链表指针，此处传入表头地址
	positon	:	待删除结点的位置
返回值
	返回待删除结点的数据域
功能
	将单链表的第position个结点删除
*/
ElemType DeleteNode(LinkList *list, int position)
{
	assert(list != NULL);									// 链表指针不能为空不能为空
	assert(position >=0 && position < LengthLinkList(list));		// 待删除的指针位置仅限于链表中存在的位置

	LinkListNode	*delNode = NULL;
	ElemType		delElem = -1;

	if(position == 0)				// 如果链表中仅剩最后一个元素
	{
		delNode = (*list);				// 待删除的结点就是头指针指向的结点
		if((*list)->m_next == NULL)	// 当前链表中仅剩最后一个元素
		{
			(*list) = NULL;			// 修改头指针为空[参数必须使用LinkListNode **形式， 因为修改了头指针的指向]
		}
		else						// 如果链表中有多个元素
		{
			(*list) = delNode->m_next;
		}
	}
	else								// 否则待删除的是其他结点
	{
		LinkListNode *pNode = FindPosNode(list, position - 1);			// 找到第position - 1个结点

		// 删除pNode的后一个结点
		delNode = pNode->m_next;
		pNode->m_next = delNode->m_next;
	}
	delElem = delNode->m_data;		// 保存待删除结点的数据域
	free(delNode);
#ifdef DEBUG
	printf("Delete the list in the first [%d, %d] node...\n", position, delElem);
#endif // DEBUG
	return delElem;
}

/**
ElemType SubNode(LinkList *list, LinkListNode *prevNode);)
参数
	list	:	指向一个链表指针，此处传入表头地址
	positon	:	待删除结点的位置
返回值
	返回待删除结点的数据域
功能
	删除链表list中prevNode结点之后的指针个指针
*/
ElemType SubNode(LinkList *list, LinkListNode *prevNode)
{
	assert(list != NULL);						// 链表不能为空
	assert(prevNode != NULL);						// 待删除结点的前一个位置不能为空
	assert(IsNodeInList(list, prevNode) != -1);	// 待删除位置的前一个结点必须在链表中

	LinkListNode	*delNode = NULL;
	ElemType		delElem = -1;

	if(prevNode == (*list))				// 如果待删除的元素是链表中第一个元素
	{
		delNode = (*list);				// 待删除的结点就是头指针指向的结点
		if((*list)->m_next == NULL)	// 当前链表中仅剩最后一个元素
		{
			(*list) = NULL;			// 修改头指针为空[参数必须使用LinkListNode **形式， 因为修改了头指针的指向]
		}
		else						// 如果链表中有多个元素
		{
			(*list) = delNode->m_next;
		}
	}
	else								// 否则待删除的是其他结点
	{
		// 删除prevode的后一个结点
		LinkListNode *delNode = prevNode->m_next;
		prevNode->m_next = delNode->m_next;
	}
	delElem = delNode->m_data;
	free(delNode);


	return delElem;
}


/**
ElemType DeleteCurrNode(LinkList *list, LinkListNode *currNode);
参数
	list	:	指向一个链表指针，此处传入表头地址
	positon	:	待删除结点的位置
返回值
	返回待删除结点的数据域
功能
	删除链表list中prevNode结点之后的指针个指针
*/
ElemType DeleteCurrNode(LinkList *list, LinkListNode *currNode)
{
	assert(list != NULL);							// 链表不能为空
	assert(currNode != NULL);							// 待删除结点的前一个位置不能为空
	assert(IsNodeInList(list, currNode) != -1);	// 待删除的结点必须在链表中

	ElemType delElem = -1;							// 待删除结点的数据域
	LinkListNode *delNode = NULL;					// 指向将要删除的结点的指针

	if(currNode->m_next != NULL)					// 如果待删除结点不是最后一个结点
	{
		// 将currNode的后一个结点delNode作为删除结点,
		delNode = currNode->m_next;
		currNode->m_next = delNode->m_next;			//从链表中删除delNode

		// 并将delNode的数据域保存到delNode中
		delElem = currNode->m_data;					// delElem保存currNode的数据域
		currNode->m_data = delNode->m_data;			// 真正删除的结点其实是currNode下一个结点, 因此用currNode保存下一个结点的数据域
	}
	else											// 否则待删除结点是最后一个结点
	{
		// 直接将最后一个结点删除即可， 应该把其前一个结点的指针域赋值为空
		delNode = currNode;
		// 下面应该将currnNode的前一个结点的指针域赋值为空[时间复杂度O(n)]
		LinkListNode *prevNode = FindPrevNode(list, currNode);
		prevNode->m_next = NULL;

	}
	free(delNode);

	return delElem;
}

///*////////////////////////////////////////////////////////////////////////////
///
///	其他函数
///
///	显示单链表的信息
///	void ShowList(LinkList *list
///
///	删除链表list中prevNode结点之后的指针个指针
///	void SetNode(LinkList *list, int position, ElemType data)
///
///	获取单链表list第position个结点的数据域
/// ElemType GetNode(LinkList *list, int position)
///
///	获取单链表list的长度[即元素个数]
///	int LengthLinkList(LinkList *list)
///
///	判断当前链表是否是空链表
///	bool IsEmptyLinkList(LinkList *list)
///*////////////////////////////////////////////////////////////////////////////


/**
void ShowLinkList(LinkList *list)
参数
	list	:	指向一个链表指针，此处传入表头地址
返回值
	无
功能
	显示单链表的信息
*/
void ShowList(LinkList *list)
{
	printf("there are %d data in list\n", LengthLinkList(list));

	LinkListNode *pNode = (LinkListNode *)(*list);			// 从头指针开始遍历

	while(pNode != NULL)								//开始遍历单链表
	{
		printf("%d  ", pNode->m_data);
        pNode = pNode->m_next;
	}
	printf("\n");

//	ElemType data;
//	for(int pos = 0; pos < list->m_length; pos++)
//	{
//		data = GetNode(list, pos);
//		printf("%d  ", data);
//	}
//	printf("\n");
}


/**
void SetNode(LinkList *list, int position, ElemType data)
参数
	list	:	指向一个链表指针，此处传入表头地址
	positon :	待修改的结点的数据
	data	:	待更正的新数据域
返回值
	无
功能
	修改单链表list第position个结点的数据域为data
*/
void SetNode(LinkList *list, int position, ElemType data)
{
	LinkListNode *pNode = FindPosNode(list, position);		// 找到单链表的第position个结点

	pNode->m_data = data;
}

/**
ElemType GetNode(LinkList *list, int position
参数
	list	:	指向一个链表指针，此处传入表头地址
	positon :	待查询的结点的位置
返回值
	获取到的结点数据
功能
	获取单链表list第position个结点的数据域
*/
ElemType GetNode(LinkList *list, int position)
{
	LinkListNode *pNode = FindPosNode(list, position);		// 找到单链表的第position个结点

	return pNode->m_data;
}

/**
int LengthLinkList(LinkList *list)
参数
	list	:	指向一个链表指针，此处传入表头地址
返回值
	单链表的长度
功能
	获取单链表的长度
*/
int LengthLinkList(LinkList *list)
{
	assert(list != NULL);

	int length = 0;
	LinkListNode *pNode = (LinkListNode *)(*list);

	while(pNode != NULL)
	{
		pNode = pNode->m_next;
		length++;
	}
	return length;
}



/**
bool IsEmptyLinkList(LinkList *list)
参数
	list	:	指向一个链表指针，此处传入表头地址
返回值
	如果单链表是空表，返回true
	否则返回false
功能
	获取单链表的长度
*/
bool IsEmptyLinkList(LinkList *list)
{
	return (list == NULL);
	// return (list->m_head == NULL);
}


#define LIST_SIZE 7
// MAIN
int main(void)
{
	int pos;

	printf("TEST 1...\n");
//	LinkList *plist = NULL;				// ERROR创建单链表


	printf("\n\nTEST 2...\n");
	LinkList list = NULL;
	InitLinkList(&list);								// 初始化单链表
	for(int pos = 0; pos < LIST_SIZE; pos++)			// 训话向单链表中插入数据
	{
		InsertNode(&list, 0, pos + 1);
	}
	ShowList(&list);									// 显示单链表
	ClearLinkList(&list);								// 清空单链表
	FinitLinkList(&list);		// ERROR== list->m_head->m_next == NULL
	ShowList(&list);

	return 	EXIT_SUCCESS;
}
