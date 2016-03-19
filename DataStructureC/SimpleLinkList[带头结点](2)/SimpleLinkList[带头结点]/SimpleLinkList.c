#include "SimpleLinkList.h"





// 创建一个单链表数据结构， 并返回其指针
LinkList* CreateLinkList(void)
{
	LinkList *list = NULL;
	if((list = (LinkList *)malloc(sizeof(LinkList))) == NULL)		// 开辟单链表[即头结点]的空间
	{	// 开辟失败
        fprintf(stderr, "not enough memory when CREATE LIST...\n");
        exit(EXIT_FAILURE);
	}

	InitLinkList(list);				// 初始化单链表

	return list;
}

// 初始化单链表list
void InitLinkList(LinkList *list)
{
	list->m_next = NULL;			// 初始化只有头结点
	list->m_data = 0;				// 数据元素个数为0
}

// 销毁单链表list
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

// 清空单链表
void ClearLinkList(LinkList *list)
{
    while(list->m_next != NULL)
	{
        DeleteNode(list, 0);
	}
}

// 对单链表进行后处理
void FinitLinkList(LinkList *list)
{
	assert(list->m_next == NULL);		// 后处理指针针对空链表
	// assert(list->m_data == 0);
	if(list != NULL)			// 如果此时头结点空间未被销毁
	{
		free(list);
	}
}

// 查找到链表list中第position个结点
LinkListNode* FindPosNode(LinkList *list, int position)
{
	assert(list != NULL);									// 链表不能为空
	assert(position >= -1 && position < list->m_data);	// 插入的w位置只能在[-1~length]

	LinkListNode 	*pNode	= list;
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


// 在链表list中找到currNode的前一个结点
LinkListNode *FindPrevNode(LinkList *list, LinkListNode *currNode)
{
	assert(list != 	NULL);
	assert(currNode != NULL);

	LinkListNode *pNode = list;

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


// 判断结点node指向的区域是不是链表中的结点
int IsNodeInList(LinkList *list, LinkListNode *node)
{
	assert(list != NULL);									// 链表不能为空	assert(Node != NULL);									// 待查找的指针不能为空

	LinkListNode 	*pNode	= list->m_next;
    int 			pos 	= 0;

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

//	找到数据域为data的结点首次出现的位置并返回结点信息
LinkListNode* FindDataNode(LinkList *list, ElemType data, int *position)
{
	LinkListNode *node = list->m_next;
	int pos = 0;
	while(node != NULL && node->m_data != data)
	{
		node = node->m_next;
		pos++;
	}
	*position = pos;				// 将出现的位置传递回去

	return node;					// 返回结点的信息
}


// 将数据data插入链表的pNode结点的下一个位置个位置
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

	list->m_data++;				// 结点数目增加一个
	//}
#ifdef DEBUG
	printf("The new node is inserted after point pointer[%p]\n", pNode);
#endif // DEBUG
	return newNode;
}

// 将数据data插入链表的第position个位置
LinkListNode *InsertNode(LinkList *list, int position, ElemType data)
{
	assert(list != NULL);
	assert(position >=0 && position < list->m_data + 1);

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
//	list->m_data++;				// 结点数目增加一个
//	list->m_head->m_data++;			// 头结点的数据域同样存储着结点总数
//	}
}


// 删除链表list中第position个指针
ElemType DeleteNode(LinkList *list, int position)
{
	assert(list != NULL);
	assert(position >=0 && position < list->m_data);
	LinkListNode *prevNode = FindPosNode(list, position - 1);			// 找到第position - 1个结点

	// 删除pNode的后一个结点
	LinkListNode *delNode = prevNode->m_next;
	ElemType delElem = delNode->m_data;
	prevNode->m_next = delNode->m_next;
	free(delNode);

	list->m_data--;				// 结点数目减少一个

	return delNode;
}

// 删除链表list中prevNode结点之后的指针个指针
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

	list->m_data--;				// 结点数目减少一个

	return delElem;

}


// 删除链表list中currNode指针所指向的那个结点
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
	list->m_data--;				// 结点数目减少一个

	return delElem;
}
// 显示单链表
void ShowList(LinkList *list)
{
// assert(list->m_head != NULL)
	if(list ==  NULL)			//  单链表可能没有被初始化
	{
		fprintf(stderr, "you can't SHOW the list without the list INITLINKLIST...\n");
		return ;
	}


	printf("there are %d data in list\n", list->m_data);
	if(list->m_data == 0)
	{
		return ;
	}

	LinkListNode *pNode = list->m_next;			// 从头指针开始遍历

	while(pNode != NULL)								//开始遍历单链表
	{
		printf("%d  ", pNode->m_data);
        pNode = pNode->m_next;
	}
	printf("\n");

//	ElemType data;
//	for(int pos = 0; pos < list->m_data; pos++)
//	{
//		data = GetNode(list, pos);
//		printf("%d  ", data);
//	}
//	printf("\n");
}

// 修改单链表list第position个结点的数据域为data
void SetNode(LinkList *list, int position, ElemType data)
{
	LinkListNode *pNode = FindPosNode(list, position);		// 找到单链表的第position个结点

	pNode->m_data = data;
}


// 获取单链表list第position个结点的数据域
ElemType GetNode(LinkList *list, int position)
{
	LinkListNode *pNode = FindPosNode(list, position);		// 找到单链表的第position个结点

	return pNode->m_data;
}

// 获取单链表的长度
int LengthLinkList(LinkList *list)
{
	return list->m_data;
}


//	判断单链表是不是空表
bool IsEmptyLinkList(LinkList *list)
{
	return (list->m_data == 0);
	// return (list->m_head->m_next == NULL);
}


