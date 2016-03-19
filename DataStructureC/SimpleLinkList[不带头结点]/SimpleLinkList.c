#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>



///*////////////////////////////////////////////////////////////////////////////
///
///	创建和初始化单链表
///
///	创建		LinkList* CreatLinkList(void)
///	初始化	void InitLinkList(LinkList *list)
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
///*///////////////////////////////////////////////////////////////////////////

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
	list->m_head = NULL;			// 初始化只有头结点
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
	assert(list->m_head == NULL);		// 后处理指针针对空链表
	// list->m_head = NULL;
	list->m_length = -1;			// 未经初始化的单链表元素个数记为-1
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
    while(list->m_head != NULL)
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
	assert(list != NULL);									// 链表不能为空
	assert(position >= 0 && position < list->m_length);		// 查找的位置只能在[0, length)

	LinkListNode 	*pNode	= list->m_head;
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
    int 			pos 	= 0;

    while(pNode != NULL && pNode != node)		// 遍历单链表，找到第position个结点的位置
	{
		pNode = pNode->m_next;
		pos++;
	}

	if(pNode != node)
	{	// 查找失败
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
	assert(list != NULL);									// 链表不能为空
	assert(position >=0 && position < list->m_length + 1);	// 插入的位置应该在[0-length]

	LinkListNode *prevNode = NULL;
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
	if(position == 0)			// 如果当前链表是空链表
	{	/// 插入链表中第一个结点， 不带头结点的单链表，插入删除第一个元素时需要进行特殊判断
		if(list->m_head == NULL)	// 如果插入之前单链表是空表
		{
			list->m_head = newNode;		// 空表直接将新结点插入即可
		}
		else						// 否则单链表不是空表
		{
			//prevNode = list->m_head;
			newNode->m_next = list->m_head;		// 将新结点插入头指针的前面即可
			list->m_head = newNode;
		}
	}
	else								// 否则当前链表不是空链表
	{
		prevNode = FindPosNode(list, position - 1);		// 找到待插入点的前一个指针
		// 将指针newNode连接在pNode的后面
		newNode->m_next = prevNode->m_next;
		prevNode->m_next = newNode;
	}

	list->m_length++;				// 结点数目增加一个

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
	if(prevNode == (LinkListNode *)list)
	{	/// 插入链表中第一个结点， 不带头结点的单链表，插入删除第一个元素时需要进行特殊判断
		if(list->m_head == NULL)	// 如果插入之前单链表是空表
		{
			list->m_head = newNode;		// 空表直接将新结点插入即可
		}
		else						// 否则单链表不是空表
		{
			//prevNode = list->m_head;
			newNode->m_next = list->m_head;		// 将新结点插入头指针的前面即可
			list->m_head = newNode;
		}
	}
	else
	{
		// 将指针newNode连接在pNode的后面
		newNode->m_next = prevNode->m_next;
		prevNode->m_next = newNode;
	}
	list->m_length++;				// 结点数目增加一个
	//}
#ifdef DEBUG
	printf("The new node is inserted after point pointer[%p]\n", pNode);
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
ElemType DeleteNode(LinkList *list, int position)
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
	assert(list != NULL);									// 删除不能为空
	assert(position >=0 && position < list->m_length);		// 待删除的指针位置仅限于链表中存在的位置

	LinkListNode	*delNode = NULL;
	ElemType		delElem = -1;
	if(position == 0)					// 如果待删除的是链表中第一个指针， 第一个元素没有前驱结点
	{	// 删除链表中第一个结点
		delNode = list->m_head;

		if(list->m_head->m_next == NULL)	// 如果链表中只剩下一个元素
		{
			list->m_head = NULL;
		}
		else								// 否则链表中剩下多个元素
		{
			list->m_head = delNode->m_next;
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
	list->m_length--;				// 结点数目减少一个
#ifdef DEBUG
	printf("Delete the list in the first %d node...\n", position);
#endif // DEBUG
	return delElem;
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

	LinkListNode	*delNode = NULL;
	ElemType		delElem = -1;

	if(prevNode == list)		// 如果待删除的是链表中第一个指针， 第一个元素没有前驱结点[穿参数时默认为list]
	{	// 删除链表中第一个结点
		delNode = list->m_head;			// 待删除的元素为头指针指向的元素

		if(list->m_head->m_next == NULL)	// 如果链表中只剩下一个元素
		{
			list->m_head = NULL;
		}
		else								// 否则链表中剩下多个元素
		{
			list->m_head = delNode->m_next;
		}
	}
	else								// 否则待删除的是其他结点
	{
		// 删除pNode的后一个结点
		delNode = prevNode->m_next;
		prevNode->m_next = delNode->m_next;
	}
	delElem = delNode->m_data;
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
	assert(currNode != NULL);						// 待删除结点的前一个位置不能为空
	assert(IsNodeInList(list, currNode) != -1);		// 待删除的结点必须在链表中

	ElemType delElem = -1;							// 待删除结点的数据域
	LinkListNode *delNode = NULL;					// 指向将要删除的结点的指针

	if(currNode == list->m_head)					// 如果待删除的是第一个结点
	{	// 删除链表中第一个结点， 不带头结点的单链表，插入删除第一个元素时需要进行特殊判断
		delNode = list->m_head;			// 待删除的元素为头指针指向的元素

		if(list->m_head->m_next == NULL)	// 如果链表中只剩下一个元素
		{
			list->m_head = NULL;
		}
		else								// 否则链表中剩下多个元素
		{
			list->m_head = delNode->m_next;
		}
	}
	else									// 否则删除的不是第一个结点
	{
		if(currNode->m_next != NULL)					// 如果待删除结点不是最后一个结点
		{	// 删除链表中最后一个结点时，需要将其前驱的指针域置空
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
	}
	free(delNode);
	list->m_length--;				// 结点数目减少一个
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
	printf("there are %d data in list\n", list->m_length);

	LinkListNode *pNode = list->m_head;			// 从头指针开始遍历

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
	获取单链表的长度
*/
bool IsEmptyLinkList(LinkList *list)
{
	return (list->m_length == 0);
	// return (list->m_head == NULL);
}




#define LIST_SIZE 7
// main
int main(void)
{
	int pos;

	printf("TEST 1...\n");
	LinkList *plist = CreateLinkList( );				// 创建单链表
	for(int pos = 0; pos < LIST_SIZE; pos++)			// 循环向单链表中插入数据
	{
		InsertNode(plist, pos, pos + 1);
		printf("HEAD = %p\n", plist->m_head);
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
	LinkListNode *prevNode = NULL;
	LinkListNode *addNode = NULL;
	prevNode = InsertNode(&list, 0, 1);					// 由于不带头结点所以进行插入第一个元素时第一个元素没有前驱结点
														// 但是也可以使用下面注视掉的代码
	for(int pos = 1; pos < LIST_SIZE; pos++)
	{
		if((addNode = AddNode(&list, prevNode, pos + 1)) != NULL)
		{
            prevNode = addNode;
		}
	}
//	LinkListNode *prevNode = (LinkListNode*)&list;
//	LinkListNode *addNode = NULL;
//	for(int pos = 0; pos < LIST_SIZE; pos++)
//	{
//		if((addNode = AddNode(&list, prevNode, pos + 1)) != NULL)
//		{
//            prevNode = addNode;
//		}
//	}
	ShowList(&list);
	while(IsEmptyLinkList(&list) != true)			// 循环删除单链表中的数据
	{
		DeleteCurrNode(&list, list.m_head);			// 删除第一个元素
	}
	ShowList(&list);									// 显示单链表

	return 	EXIT_SUCCESS;
}
