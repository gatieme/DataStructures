#include "SimpleLinkList.h"



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

