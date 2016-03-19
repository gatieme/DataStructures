#include "SimpleLinkList.h"



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
		InsertNode(&list, pos, pos + 1);
	}
	ShowList(&list);									// 显示单链表
	ClearLinkList(&list);								// 清空单链表
	FinitLinkList(&list);		// ERROR== list->m_head->m_next == NULL
	ShowList(&list);

	return 	EXIT_SUCCESS;
}

