#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>



//#define DEBUG				// 调试插桩信息宏

///	版本V0.0.2更新
///	①将InsertNode重新实现为两个函数
//	将数据data插入链表的第position个位置
//	LinkListNode* InsertNode(LinkList *list, int position, ElemType data)
//	将数据data插入链表的pNode结点的下一个位置个位置
//	LinkListNode* AddNode(LinkList *list, LinkListNode *prevNode, ElemType data)

///	②将DelNode重新实现为三个函数
//	删除链表list中第position个指针
//	ElemType DeleteNode(LinkList *list, int position)
//	删除链表list中prevNode结点之后的指针个指针
//	ElemType SubNode(LinkListNode *prevNode)
//	删除链表list中currNode指针所指向的那个结点
//	ElemType DeleteCurrNode(LinkList *list, LinkListNode *currNode)

/// ③将FindNode重新实现为三个函数
//	查找到链表list中第position个结点
//	LinkListNode* FindPosNode(LinkList *list, int position);
//	在链表list中找到currNode的前一个结点
//	LinkListNode *FindPrevNode(LinkList *list, LinkListNode *currNode);
//	判断结点node指向的区域是不是链表中的结点
//	int IsNodeInList(LinkList *list, LinkListNode *node);



///*////////////////////////////////////////////////////////////////////////////
///
///	带头结点的单链表结构体
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

// 带头结点的单项链表
typedef struct LinkList
{
	LinkListNode	*m_head;				// 链表头结点
	int				m_length;			// 单链表数据结点个数指针域
}LinkList;



///*////////////////////////////////////////////////////////////////////////////
///
///	创建和初始化单链表
///
///	开辟一个单链表数据结构，并初始化头结点，然后将创建好的单链表指针返回
///	LinkList* CreatLinkList(void)
///
///	初始化单链表
///	void InitLinkList(LinkList *list)
///*////////////////////////////////////////////////////////////////////////////
/**
LinkList* CreatLinkList(void)
参数
	list	:	指向一个链表指针，此处传入表头地址
返回值
	若成功返回创建好的单链表的指针
功能
	开辟一个单链表数据结构，并初始化头结点，然后将创建好的单链表指针返回
注意
	使用CreateLinkList创建的单链表，需要用DestroyLinkList来销毁
	以免发生内存泄漏
*/
LinkList* CreateLinkList(void)
{
	LinkList *list = NULL;
	if((list = (LinkList *)malloc(sizeof(LinkList))) == NULL)		// 开辟单链表的空间
	{	// 开辟失败
        fprintf(stderr, "not enough memory when CREATE LIST...\n");
        exit(EXIT_FAILURE);
	}

	InitLinkList(list);				// 初始化单链表

	return list;
}

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
	if((list->m_head = malloc(sizeof(LinkListNode))) == NULL)		// 为头结点开辟空间
	{	// 开辟失败
        fprintf(stderr, "not enough memory when MALLOC HEAD...");
        exit(EXIT_FAILURE);
	}
	list->m_head->m_next = NULL;			// 初始化只有头结点
	list->m_head->m_data = 0;				// 数据元素个数为0
	list->m_length = 0;						// 数据元素个数为0
}


///*////////////////////////////////////////////////////////////////////////////
///
///	销毁以及后处理单链表
///
///	销毁用CreateLinkList创建的单链表
///	void DestroyLinkList(LinkList *list)
///
///	后处理单链表，
///	void FinitLinkList(LinkList *list)
///
/// 清空单链表中的所有元素
///	void ClearLinkList(LinkList *list)
///*////////////////////////////////////////////////////////////////////////////
/**
void DestroyLinkList(LinkList *list)
参数
	list	:	指向一个链表指针，此处传入表头地址
返回值
	无
功能
	销毁用CreateLinkList创建的单链表，执行以下操作
	①清空单链表	②释放头结点	③释放单链表
注意
	使用CreateLinkList创建的单链表，需要用DestroyLinkList来销毁
	以免发生内存泄漏
*/
LinkList* DestroyLinkList(LinkList *list)
{
	ClearLinkList(list);			// 清空链表
	FinitLinkList(list);			// 销毁头结点
	if(list != NULL)				// 销毁链表的空间
	{
		free(list);
		list = NULL;
	}
}


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
	assert(list->m_head->m_next == NULL);		// 后处理指针针对空链表
	// assert(list->m_length == 0);
	if(list->m_head != NULL)			// 如果此时头结点空间未被销毁
	{
		free(list->m_head);

		list->m_head = NULL;
		list->m_length = -1;			// 未经初始化的单链表元素个数记为-1
	}
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
    while(list->m_head->m_next != NULL)
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
	查找到链表list中第position个结点
*/
LinkListNode* FindPosNode(LinkList *list, int position)
{
	assert(list != NULL);									// 链表不能为空
	assert(position >= -1 && position < list->m_length);	// 插入的w位置只能在[-1~length]

	LinkListNode 	*pNode	= list->m_head;
    int 			pos 	= -1;

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

	LinkListNode *pNode = list->m_head;

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

	LinkListNode 	*pNode	= list->m_head;
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
		printf("Find the [%p] point in the first %d pointer of the list...\n", fNode, pos);
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
	LinkListNode *node = list->m_head->m_next;
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
LinkListNode* AddNode(LinkList *list, LinkListNode *prevNode, ElemType data);
参数
	list		:	指向一个链表指针，此处传入表头地址
	prevNode	:	待插入位置的前一个结点
	data		:	待插入结点的数据
返回值
	无
功能
	将数据data插入链表的prevNode结点的下一个位置个位置
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

	// 将指针newNode连接在pNode的后面
	newNode->m_next = prevNode->m_next;
	prevNode->m_next = newNode;

	list->m_length++;				// 结点数目增加一个
	list->m_head->m_data++;			// 头结点的数据域同样存储着结点总数
	//}
#ifdef DEBUG
	printf("The new node is inserted after point pointer[%p]\n", pNode);
#endif // DEBUG
	return newNode;
}

/**
void InsertNode(LinkList *list, int position, ElemType data)
参数
	list	:	指向一个链表指针，此处传入表头地址
	positon	:	待插入结点的位置
	data	:	待插入结点的数据
返回值
	无
功能
	将数据data插入链表的第position个位置
*/
LinkListNode *InsertNode(LinkList *list, int position, ElemType data)
{
	assert(list != NULL);
	assert(position >=0 && position < list->m_length + 1);

	LinkListNode *prevNode = FindPosNode(list, position - 1);			// 找到待插入位置的前一个结点
	LinkListNode *newNode = NULL;

	// 下面调用InsertPointNode直接将结点插入到pNode结点后面
	if((newNode = AddNode(list, prevNode, data)) != NULL)	// 将新的结点插入到待插入前一个指针的后面
	{	// 插入成功
		return newNode;								// 返回新插入的结点
#ifdef DEBUG
		printf("Insert the value %d into list at position %d...\n", data, position);
#endif // DEBUG
	}
	else
	{
		return NULL;								// 插入失败返回NULL
	}

//	//	以可以使用下面的代码
//	if((newNode = (LinkListNode *)malloc(sizeof(LinkListNode))) == NULL)	// 为新结点开辟空间
//	{	// 开辟新结点失败
//		fprintf(stderr, "not enough memeory\n");
//        exit(EXIT_FAILURE);
//	}
//	else
//	{	// 开辟新结点成功
//	newNode->m_data = data;
//	newNode->m_next = NULL;
//
//	// 将指针newNode连接在pNode的后面
//	newNode->m_next = prevNode->m_next;
//	prevNode->m_next = newNode;
//
//	list->m_length++;				// 结点数目增加一个
//	list->m_head->m_data++;			// 头结点的数据域同样存储着结点总数
//	}
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
void DeleteNode(LinkList *list, int position)
参数
	list	:	指向一个链表指针，此处传入表头地址
	positon	:	待删除结点的位置
返回值
	返回待删除结点的数据域
功能
	删除链表list中prevNode结点之后的指针个指针
*/
ElemType DeleteNode(LinkList *list, int position)
{
	assert(list != NULL);
	assert(position >=0 && position < list->m_length);
	LinkListNode *prevNode = FindPosNode(list, position - 1);			// 找到第position - 1个结点

	// 删除pNode的后一个结点
	LinkListNode *delNode = prevNode->m_next;
	ElemType delElem = delNode->m_data;
	prevNode->m_next = delNode->m_next;
	free(delNode);

	list->m_length--;				// 结点数目减少一个
	list->m_head->m_data--;			// 头结点的数据域同样存储着结点总数

	return delNode;
}

/**
ElemType SubNode(LinkList *list, LinkListNode *prevNode)
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

	// 删除pNode的后一个结点
	LinkListNode *delNode = prevNode->m_next;
	ElemType delElem = delNode->m_data;
	prevNode->m_next = delNode->m_next;
	free(delNode);

	list->m_length--;				// 结点数目减少一个
	list->m_head->m_data--;			// 头结点的数据域同样存储着结点总数

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
	list->m_length--;				// 结点数目减少一个
	list->m_head->m_data--;			// 头结点的数据域同样存储着结点总数

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
// assert(list->m_head != NULL)
	if(list->m_head ==  NULL)			//  单链表可能没有被初始化
	{
		fprintf(stderr, "you can't SHOW the list without the list INITLINKLIST...\n");
		return ;
	}


	printf("there are %d data in list\n", list->m_length);
	if(list->m_length == 0)
	{
		return ;
	}

	LinkListNode *pNode = list->m_head->m_next;			// 从头指针开始遍历

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
	positon :	待查询的结点的位置
返回值
	获取到的结点数据
功能
	获取单链表list的长度[即元素个数]
*/
int LengthLinkList(LinkList *list)
{
	return list->m_length;
}


/**
bool IsEmptyLinkList(LinkList *list)
参数
	list	:	指向一个链表指针，此处传入表头地址
返回值
	如果单链表是空表，返回true
	否则返回false
功能
	判断当前链表是否是空链表
*/
bool IsEmptyLinkList(LinkList *list)
{
	return (list->m_length == 0);
	// return (list->m_head->m_next == NULL);
}




#define LIST_SIZE 7
// 主函数
int main(void)
{
	int pos;

	printf("TEST 1...\n");
	LinkList *plist = CreateLinkList( );				// 创建单链表
	for(int pos = 0; pos < LIST_SIZE; pos++)			// 循环向单链表中插入数据
	{
		InsertNode(plist, pos, pos + 1);
	}
	ShowList(plist);									// 插入结束后显示单链表的信息

	DeleteNode(plist, 0);								// 删除第一个元素
	ShowList(plist);
	DeleteNode(plist, 1);								// 删除第二个元素
	ShowList(plist);

	ClearLinkList(plist);								// 将单链表清空
	ShowList(plist);
	DestroyLinkList(plist);								// 将单链表销毁
	plist = NULL;

	printf("\n\nTEST 2...\n");
	LinkList list;
	InitLinkList(&list);								// 初始化单链表
	for(int pos = 0; pos < LIST_SIZE; pos++)			// 训话向单链表中插入数据
	{
		InsertNode(&list, pos, pos + 1);
	}
	ShowList(&list);									// 显示单链表
	ClearLinkList(&list);								// 清空单链表
//	FinitLinkList(&list);		// ERROR== list->m_head->m_next == NULL
	ShowList(&list);

	printf("\n\nTEST 3...\n");
	LinkListNode *prevNode = list.m_head;
	LinkListNode *addNode = NULL;
	for(int pos = 0; pos < LIST_SIZE; pos++)
	{
		if((addNode = AddNode(&list, prevNode, pos + 1)) != NULL)
		{
            prevNode = addNode;
		}
	}
	ShowList(&list);
	while(IsEmptyLinkList(&list) != true)			// 循环删除单链表中的数据
	{
		DeleteCurrNode(&list, list.m_head->m_next);
	}
	ShowList(&list);									// 显示单链表

	return 	EXIT_SUCCESS;
}


