#include "CirLinkList.h"


///*////////////////////////////////////////////////////////////////////////////
///
///	创建和初始化单链表
///
///	开辟一个单链表数据结构，并初始化头结点，然后将创建好的单链表指针返回
///	CirLinkList* CreatCirLinkList(void)
///
///	初始化单链表
///	void InitCirLinkList(CirLinkList *tail)
///*///////////////////////////////////////////////////////////////////////////

/**
CirLinkList* CreatCirLinkList(void)
参数
	tail	:	指向一个链表指针，此处传入表头地址
返回值
	若成功返回创建好的单链表的指针
功能
	开辟一个单链表数据结构，并初始化头结点，然后将创建好的单链表指针返回
注意
	使用CreateCirLinkList创建的单链表，需要用DestroyCirLinkList来销毁
	以免发生内存泄漏
*/
CirLinkList* CreateCirLinkList(void)
{
	CirLinkList *tail = NULL;
	if((tail = (CirLinkList *)malloc(sizeof(CirLinkList))) == NULL)		// 开辟单链表尾结点（即头结点）的空间
	{	// 开辟失败
        fprintf(stderr, "not enough memory when CREATE LIST...\n");
        exit(EXIT_FAILURE);
	}

	InitCirLinkList(tail);				// 初始化单链表
#ifdef DEBUG
	printf("循环链表的头结点%p\n", tail);
#endif // DEBUG
	return tail;						// 单链表尾结点
}



/**
void InitCirLinkList(CirLinkList *tail)
参数
	tail	:	指向一个链表指针，此处传入表头地址
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
void InitCirLinkList(CirLinkList *tail)
{
	// 初始化头结点信息
	tail->m_next = tail;					// 初始化只有头结点[空循环链表的特征]
	tail->m_data = 0;						// 数据元素个数为0
}

///*////////////////////////////////////////////////////////////////////////////
///
///	销毁以及后处理单链表
///
///	销毁用CreateCirLinkList创建的单链表
///	void DestroyCirLinkList(CirLinkList *tail)
///
///	后处理单链表，
///	void FinitCirLinkList(CirLinkList *tail)
///
/// 清空单链表中的所有元素
///	void ClearCirLinkList(CirLinkList *tail)
///*////////////////////////////////////////////////////////////////////////////

/**
void DestroyCirLinkList(CirLinkList *tail)
参数
	tail	:	指向一个链表指针，此处传入表头地址
返回值
	无
功能
	销毁用CreateCirLinkList创建的单链表，执行以下操作
	①清空单链表	②释放头结点	③释放单链表
注意
	使用CreateCirLinkList创建的单链表，需要用DestroyCirLinkList来销毁
	以免发生内存泄漏
*/
CirLinkList* DestroyCirLinkList(CirLinkList **tail)
{
	ClearCirLinkList(tail);			// 清空链表
	FinitCirLinkList(*tail);			// 销毁头结点
	if((*tail) != NULL)				// 销毁链表的空间
	{
		free(*tail);
		*tail = NULL;
	}
}





/**
void FinitCirLinkList(CirLinkList *tail)
参数
	tail	:	指向一个链表指针，此处传入表头地址
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
void FinitCirLinkList(CirLinkList *tail)
{

	if(tail != NULL)			// 如果此时头结点空间未被销毁
	{
		free(tail);				// 清空尾结点即头结点

		tail = NULL;
	}
}



/**
void ClearCirLinkList(CirLinkList *tail)
参数
	tail	:	指向一个链表指针，此处传入表头地址
返回值
	无
功能
	清空单链表中的所有元素
*/
void ClearCirLinkList(CirLinkList **tail)
{
	while((*tail)->m_next->m_data != 0)
	//while(IsEmptyCirLinkList(tail) != true)
	{
        DeleteNode(tail, 0);
	}
}

///*////////////////////////////////////////////////////////////////////////////
///
///	查找函数
///
///	查找到链表tail中第position个结点
///	CirLinkListNode* FindPosNode(CirLinkList *tail, int position)
///
///	在链表tail中找到currNode的前一个结点
///	CirLinkListNode *FindPrevNode(CirLinkList *tail, CirLinkListNode *currNode)
///
/// 判断结点node指向的区域是不是链表中的结点
///	int IsNodeInList(CirLinkList *tail, CirLinkListNode *node)
///
///	找到数据域为data的结点首次出现的位置并返回结点信息
///	CirLinkListNode* FindDataNode(CirLinkList *tail, ElemType data, int *position)
///*////////////////////////////////////////////////////////////////////////////
/**
CirLinkListNode* FindPosNode(CirLinkList *tail, int position)

参数
	tail	:	指向一个链表指针，此处传入表头地址
	positon	:	带查找的链表指针的位置
返回值
	若成功返回指向待查找结点的指针
	若失败返回NULL
功能
	该函数的功能是:	查找到链表tail中第position个结点
*/
CirLinkListNode* FindPosNode(CirLinkList *tail, int position)
{
	assert(tail != NULL);									// 链表不能为空
	assert(position >= -1 && position < tail->m_next->m_data);	// 插入的w位置只能在[-1~length]

	CirLinkListNode 	*pNode	= tail->m_next->m_next;		// 尾结点的下一个位置是头结点, 头结点的下一个是

	if(position == -1)											// -1表示寻找头指针的前驱
	{
		return tail->m_next;									// 直接返回前驱[即头结点]
	}

    int pos 	= 0;

    while(pNode != tail && pos < position)		// 遍历单链表，找到第position个结点的位置
	{
		pNode = pNode->m_next;
		pos++;
	}

	if(pos < position)		// 如果找到链表尾部还没有找到
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
CirLinkListNode *FindPrevNode(CirLinkList *tail, CirLinkListNode *currNode);

参数
	tail		:	指向一个链表指针，此处传入表头地址
	currNode	:	待查找的链表指针的位置
返回值
	若成功返回指向待查找结点的指针
	若失败返回NULL
功能
	在链表tail中找到currNode的前一个结点
*/

CirLinkListNode *FindPrevNode(CirLinkList *tail, CirLinkListNode *currNode)
{
	assert(tail != 	NULL);
	assert(currNode != NULL);

	CirLinkListNode *pNode = tail->m_next->m_next;
//	CirLinkListNode *pNode = tail->m_tail->m_next;			// 当循环链表只设尾指针时采用此代码

	while(pNode != tail 							// 如果未查找到链表尾部
	   && pNode->m_next != currNode)				// 查找到下一个指针正好是currNode是说明查找成功
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
int IsNodeInList(CirLinkList *tail, CirLinkListNode *node)

参数
	tail	:	指向一个链表指针，此处传入表头地址
	node	:	指向待查找的结点的指针
返回值
	若成功 返回结点node在链表中的位置
	若失败 返回-1
功能
	判断结点node指向的区域是不是链表中的结点
*/
int IsNodeInList(CirLinkList *tail, CirLinkListNode *node)
{
	assert(tail != NULL);									// 链表不能为空	assert(Node != NULL);									// 待查找的指针不能为空

	CirLinkListNode 	*pNode	= tail->m_next->m_next;
//	CirLinkListNode *pNode = tail->m_tail->m_next;			// 当循环链表只设尾指针时采用此代码
    int 			pos 	= 0;

    while(pNode != tail->m_next && pNode != node)		// 遍历单链表，找到第position个结点的位置
	{
		pNode = pNode->m_next;
		pos++;
	}

	if(pNode != node)
	{	// 查找成功
		return -1;
	}
	else
	{	// 查找失败
#ifdef DEBUG
		printf("Find the [%p] point in the first %d pointer of the tail...\n", node, pos);
#endif // DEBUG
		return pos;
	}
}


/**
CirLinkListNode* FindDataNode(CirLinkList *tail, ElemType data, int *position

参数
	tail	:	指向一个链表指针，此处传入表头地址
	data	:	待查找的结点的数据信息
返回值
	若成功 返回结点node在链表中的位置
	若失败 返回-1
功能
	找到数据域为data的结点首次出现的位置并返回结点信息
*/
CirLinkListNode* FindDataNode(CirLinkList *tail, ElemType data, int *position)
{
	CirLinkListNode *node = tail->m_next->m_next;
//	CirLinkListNode *pNode = tail->m_tail->m_next;			// 当循环链表只设尾指针时采用此代码

	int pos = 0;
	while(node != tail->m_next && node->m_data != data)
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
///	CirLinkListNode *AddNode(CirLinkList *tail, CirLinkListNode *prevNode, ElemType data)
///
///	将数据data插入链表的第position个位置
///	CirLinkListNode *InsertNode(CirLinkList *tail, int position, ElemType data)
///*////////////////////////////////////////////////////////////////////////////


/**
CirLinkListNode* AddNode(CirLinkList *tail, CirLinkListNode *prevNode, ElemType data);
参数
	tail		:	指向一个链表指针，此处传入表头地址
	prevNode	:	待插入位置的前一个结点
	data		:	待插入结点的数据
返回值
	无
功能
	该函数的功能是:	将数据data插入链表的prevNode结点的下一个位置个位置
*/
CirLinkListNode* AddNode(CirLinkList **tail, CirLinkListNode *prevNode, ElemType data)
{
	assert(prevNode != NULL);						// 插入点不能是空指针

	CirLinkListNode *newNode = NULL;

	if((newNode = (CirLinkListNode *)malloc(sizeof(CirLinkListNode))) == NULL)	// 为新结点开辟空间
	{	// 开辟新结点失败
		fprintf(stderr, "not enough memeory\n");
        exit(EXIT_FAILURE);
	}
	else
	{
		// 开辟新结点成功
		newNode->m_data = data;
		newNode->m_next = NULL;
	}

	// 将指针newNode连接在pNode的后面
	newNode->m_next = prevNode->m_next;
	prevNode->m_next = newNode;

	if(prevNode == *tail)
	{
		*tail = newNode;
		printf("修改尾指针%p\n", *tail);
	}
	(*tail)->m_next->m_data++;			// 头结点的数据域存储着结点总数

#ifdef DEBUG
	printf("新开辟的链表结点地址%p, 数据域%d, 指针域%p\n", newNode, newNode->m_data, newNode->m_next);
#endif // DEBUG
	return newNode;
}


/**
void InsertNode(CirLinkList *tail, int position, ElemType data)
参数
	tail	:	指向一个链表指针，此处传入表头地址
	positon	:	待插入结点的位置
	data	:	待插入结点的数据
返回值
	无
功能
	该函数的功能是:	将数据data插入链表的第position个位置
*/
CirLinkListNode* InsertNode(CirLinkList **tail, int position, ElemType data)
{
	assert(*tail != NULL);
	assert(position >=0 && position < (*tail)->m_next->m_data + 1);

	CirLinkListNode *prevNode = FindPosNode(*tail, position - 1);			// 找到待插入位置的前一个结点
	CirLinkListNode *newNode = NULL;

	// 下面调用InsertPointNode直接将结点插入到pNode结点后面
	if((newNode = AddNode(tail, prevNode, data)) != NULL)	// 将新的结点插入到待插入前一个指针的后面
	{	// 插入成功

		return newNode;								// 返回新插入的结点
#ifdef DEBUG
		printf("Insert the value %d into tail at position %d...\n", data, position);
#endif // DEBUG
	}
	else
	{
		return NULL;								// 插入失败返回NULL
	}
}


///*////////////////////////////////////////////////////////////////////////////
///
///	删除函数
///
///	删除链表tail中prevNode结点之后的指针个指针
///	void DeleteNode(CirLinkList *tail, int position)
///
///	删除链表tail中prevNode结点之后的指针个指针
///	ElemType SubNode(CirLinkList *tail, CirLinkListNode *prevNode)
///
///	删除链表tail中prevNode结点之后的指针个指针
///	ElemType DeleteCurrNode(CirLinkList *tail, CirLinkListNode *currNode)
///*////////////////////////////////////////////////////////////////////////////

/**
void DeleteNode(CirLinkList *tail, int position)
参数
	tail	:	指向一个链表指针，此处传入表头地址
	positon	:	待删除结点的位置
返回值
	返回待删除结点的数据域
功能
	将单链表的第position个结点删除
*/
ElemType DeleteNode(CirLinkList **tail, int position)
{
	assert(*tail != NULL);
	assert(position >= 0 && position < (*tail)->m_next->m_data);

	CirLinkListNode *prevNode = FindPosNode((*tail), position - 1);			// 找到第position - 1个结点

	// 删除pNode的后一个结点
	CirLinkListNode *delNode = prevNode->m_next;
	ElemType delElem = delNode->m_data;
	prevNode->m_next = delNode->m_next;
	free(delNode);

	if(position == (*tail)->m_next->m_data)
	{
		printf("修改尾指针%p\n", prevNode);
		(*tail) = prevNode;
	}

	(*tail)->m_next->m_data--;			// 头结点的数据域同样存储着结点总数

	return delNode;
}


/**
ElemType SubNode(CirLinkList *tail, CirLinkListNode *prevNode)
参数
	tail	:	指向一个链表指针，此处传入表头地址
	positon	:	待删除结点的位置
返回值
	返回待删除结点的数据域
功能
	删除链表tail中prevNode结点之后的指针个指针
*/
ElemType SubNode(CirLinkList *tail, CirLinkListNode *prevNode)
{
	assert(tail != NULL);						// 链表不能为空
	assert(prevNode != NULL);						// 待删除结点的前一个位置不能为空
	assert(IsNodeInList(tail, prevNode) != -1);	// 待删除位置的前一个结点必须在链表中

	// 删除pNode的后一个结点
	CirLinkListNode *delNode = prevNode->m_next;
	ElemType delElem = delNode->m_data;
	prevNode->m_next = delNode->m_next;

	free(delNode);

	tail->m_next->m_data--;			// 头结点的数据域同样存储着结点总数

	return delElem;
}



/**
ElemType DeleteCurrNode(CirLinkList *tail, CirLinkListNode *currNode);
参数
	tail	:	指向一个链表指针，此处传入表头地址
	positon	:	待删除结点的位置
返回值
	返回待删除结点的数据域
功能
	删除链表tail中prevNode结点之后的指针个指针
*/
ElemType DeleteCurrNode(CirLinkList **tail, CirLinkListNode *currNode)
{
	assert(*tail != NULL);							// 链表不能为空
	assert(currNode != NULL);							// 待删除结点的前一个位置不能为空
	assert(IsNodeInList(*tail, currNode) != -1);	// 待删除的结点必须在链表中

	ElemType 			delElem = -1;							// 待删除结点的数据域
	CirLinkListNode 	*delNode = NULL;					// 指向将要删除的结点的指针


	// 直接将最后一个结点删除即可， 应该把其前一个结点的指针域赋值为空
	delNode = currNode;
	// 下面应该将currnNode的前一个结点的指针域赋值为空[时间复杂度O(n)]
	CirLinkListNode *prevNode = FindPrevNode((*tail), currNode);
	prevNode->m_next = (*tail)->m_next;			/// BUG1  最后一个结点的后一个结点


	if(currNode != (*tail))					// 如果待删除结点不是最后一个结点
	{
		(*tail) = prevNode;
	}

	free(delNode);

	(*tail)->m_next->m_data--;			// 头结点的数据域同样存储着结点总数

	return delElem;
}




///*////////////////////////////////////////////////////////////////////////////
///
///	其他函数
///
///	显示单链表的信息
///	void ShowList(CirLinkList *tail
///
///	删除链表tail中prevNode结点之后的指针个指针
///	void SetNode(CirLinkList *tail, int position, ElemType data)
///
///	获取单链表tail第position个结点的数据域
/// ElemType GetNode(CirLinkList *tail, int position)
///
///	获取单链表tail的长度[即元素个数]
///	int LengthCirLinkList(CirLinkList *tail)
///
///	判断当前链表是否是空链表
///	bool IsEmptyCirLinkList(CirLinkList *tail)
///*////////////////////////////////////////////////////////////////////////////

/**
void ShowCirLinkList(CirLinkList *tail)
参数
	tail	:	指向一个链表指针，此处传入表头地址
返回值
	无
功能
	显示单链表的信息
*/
void ShowList(CirLinkList *tail)
{
// assert(tail->m_next != NULL)
	if(tail->m_next ==  NULL)			//  单链表可能没有被初始化
	{
		fprintf(stderr, "you can't SHOW the tail without the tail INITLINKLIST...\n");
		return ;
	}


	printf("there are %d data in tail\n", tail->m_next->m_data);
	if(tail->m_next->m_data == 0)
	{
		return ;
	}

	CirLinkListNode *pNode = tail->m_next->m_next;			// 从头指针开始遍历

	while(pNode != tail->m_next)								//开始遍历单链表
	{
		printf("%d  ", pNode->m_data);
        pNode = pNode->m_next;
	}
	printf("\n");

//	ElemType data;
//	for(int pos = 0; pos < tail->m_next->m_data; pos++)
//	{
//		data = GetNode(tail, pos);
//		printf("%d  ", data);
//	}
//	printf("\n");
}

/**
void SetNode(CirLinkList *tail, int position, ElemType data)
参数
	tail	:	指向一个链表指针，此处传入表头地址
	positon :	待修改的结点的数据
	data	:	待更正的新数据域
返回值
	无
功能
	修改单链表tail第position个结点的数据域为data
*/
void SetNode(CirLinkList *tail, int position, ElemType data)
{
	CirLinkListNode *pNode = FindPosNode(tail, position);		// 找到单链表的第position个结点

	pNode->m_data = data;
}

/**
ElemType GetNode(CirLinkList *tail, int position
参数
	tail	:	指向一个链表指针，此处传入表头地址
	positon :	待查询的结点的位置
返回值
	获取到的结点数据
功能
	获取单链表tail第position个结点的数据域
*/
ElemType GetNode(CirLinkList *tail, int position)
{
	CirLinkListNode *pNode = FindPosNode(tail, position);		// 找到单链表的第position个结点

	return pNode->m_data;
}


/**
int LengthCirLinkList(CirLinkList *tail)
参数
	tail	:	指向一个链表指针，此处传入表头地址
返回值
	单链表的长度
功能
	获取单链表的长度
*/
int LengthCirLinkList(CirLinkList *tail)
{
	return tail->m_next->m_data;
}


/**
bool IsEmptyCirLinkList(CirLinkList *tail)
参数
	tail	:	指向一个链表指针，此处传入表头地址
返回值
	如果单链表是空表，返回true
	否则返回false
功能
	获取单链表的长度
*/
bool IsEmptyCirLinkList(CirLinkList *tail)
{
    return (tail->m_next->m_next == tail->m_next);
//	return (tail->m_tail == this->m_head);
}


/**
CirLinkListNode* GetFisrtNode(CirLinkList *tail)
参数
	tail	:	指向一个链表指针，此处传入表头地址
返回值
	返回头指针
功能
	获取循环链表的头指针
*/
CirLinkListNode* GetFisrtNode(CirLinkList *tail)
{
	return tail->m_next->m_next;
//	return tail->m_tail->m_next->m_next;			// 只设尾指针的时候使用此代码
}


/**
CirLinkListNode* GetHeadNode(CirLinkList *tail)
参数
	tail	:	指向一个链表指针，此处传入表头地址
返回值
	返回头结点的地址
功能
	获取指向头结点的指针
*/
CirLinkListNode* GetHeadNode(CirLinkList *tail)
{
	return tail->m_next;
//	return tail->m_tail->m_next;			// 只设尾指针的时候使用此代码
}
