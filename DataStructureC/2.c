#include <stdio.h>
#include <stdlib.h>


// 函数中修改一个变量的值
typedef struct
{
	int *value;
	int length
}List;

int gloValue1 = 0;
int gloValue2 = 10;						// 全局变量

void Modify1(List list);		// 变量作为参数
void Modify2(List *list);		// 变量的指针作为参数


int main(void)
{

	List list = {&gloValue1, 0};
	printf("&gloValue1 = %p, &gloValue = %p\n", &gloValue1, &gloValue2);
	printf("value = %d, addr = %p, length = %d after func\n\n", *(list.value), list.value, list.length);

	Modify1(list);
	printf("value = %d, addr = %p, length = %d after Modify1\n\n", *(list.value), list.value, list.length);

	Modify2(&list);
	printf("value = %d, addr = %p, length = %d after Modify2\n\n", *(list.value), list.value, list.length);
	return EXIT_SUCCESS;
}


// 变量作为参数
void Modify1(List list)
{
	list.value = &gloValue2;								// 修改指针的值(即指针的指向)  failed
	list.length = 10;										// failed
	printf("value = %d, addr = %p, length = %d in %s\n", *(list.value), list.value, list.length, __func__);
}


// 变量作为参数
void Modify2(List *list)
{
	list->value = &gloValue2;								// 修改指针的值(即指针的指向) success
	list->length = 10;										//						  success
	printf("value = %d, addr = %p, length = %d in %s\n", *(list->value), list->value, list->length, __func__);
}

// 不带头结点的单链表插入首元时，需要修改头指针的指向
(*list) = newNode;					// 此时修改指针本身的指向需要传入LinkListNode **
// 不带头结点的单项链表声明
typedef struct LinkListNode*  LinkList;
//函数声明	
LinkListNode* InsertNode(LinkList *list,	// LinkList * == LinkListNode**	 
						 int position, 
						 ElemType data)

// 将newNode插入pNode之后时，需要修改newNode和pNode指针域的指向
newNode->m_next = pNode->m_next;	// 此时只需要传入LinkListNode *即可, 因为指针域m_next是node的数据成员, 已经是个指针成员变量
pNode->m_next = newNode;			// 传入LinkListNode *, m_next就成为一个指针的指针
// 函数声明
LinkListNode *AddNode(LinkList *list,							
					  LinkListNode *prevNode,				// 传入LinkListNode *, 即可修改prevNode->m_next = @@@@@
					  ElemType data)

// 不带头结点的单项链表
typedef struct LinkListNode*  LinkList;
// 带头结点的单链表
typedef struct LinkListNode LinkList;