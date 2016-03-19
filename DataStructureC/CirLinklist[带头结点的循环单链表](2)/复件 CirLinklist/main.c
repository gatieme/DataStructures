#include "CirLinklist.h"




#define LIST_SIZE 7
// 主函数
int main(void)
{
	int pos;

	printf("TEST 1...\n");
	CirLinkList plist = NULL;				// 创建单链表
	InitCirLinkList(&plist);
	for(int pos = 0; pos < LIST_SIZE; pos++)			// 循环向单链表中插入数据
	{
		InsertNode(&plist, pos, pos + 1);
	}
	ShowList(&plist);									// 插入结束后显示单链表的信息

	DeleteNode(&plist, 0);								// 删除第一个元素
	ShowList(&plist);
	DeleteNode(&plist, 1);								// 删除第二个元素
	ShowList(&plist);

	ClearCirLinkList(&plist);								// 将单链表清空
	ShowList(&plist);
	FinitCirLinkList(&plist);								// 将单链表销毁
	plist = NULL;


	return 	EXIT_SUCCESS;
}
