#include "SimpleLinkList.h"





// 创建一个单链表数据结构， 并返回其指针
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

// 初始化单链表list
void InitLinkList(LinkList *list)
{
	list->m_head = NULL;			// 初始化只有头结点
	list->m_length = 0;						// 数据元素个数为0
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
    while(list->m_head != NULL)
	{
        DeleteNode(list, 0);
	}
}

// 对单链表进行后处理
void FinitLinkList(LinkList *list)
{
	assert(list->m_head == NULL);		// 后处理指针针对空链表
	// list->m_head = NULL;
	list->m_length = -1;			// 未经初始化的单链表元素个数记为-1
}

// 查找到链表list中第position个结点
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


// 在链表list中找到currNode的前一个结点
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

// 判断结点node指向的区域是不是链表中的结点
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

// 将数据data插入链表的第position个位置
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


// 删除链表list中第position个指针
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


// 删除链表list中prevNode结点之后的指针个指针
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

// 删除链表list中currNode指针所指向的那个结点
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

// 显示单链表
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
	return list->m_length;
}


//	判断单链表是不是空表
bool IsEmptyLinkList(LinkList *list)
{
	return (list->m_length == 0);
	// return (list->m_head == NULL);
}


