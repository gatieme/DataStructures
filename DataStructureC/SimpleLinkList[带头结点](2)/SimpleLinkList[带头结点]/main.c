#include "SimpleLinkList.h"



#define LIST_SIZE 7
// Ö÷º¯Êý
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
	LinkListNode *prevNode = &list;			// 带头结点的单链表头指针是list->m_next
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
		DeleteCurrNode(&list, list.m_next);
	}
	ShowList(&list);									// 显示单链表

	return 	EXIT_SUCCESS;
}

