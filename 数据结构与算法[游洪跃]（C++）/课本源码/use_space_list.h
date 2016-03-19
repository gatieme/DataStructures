#ifndef __USE_SPACE_LIST_H__
#define __USE_SPACE_LIST_H__

#include "node.h"					// 结点类

// 使用空间表类
class UseSpaceList
{
protected:
// 数据成员:
	Node<void *> *head;				// 使用空间表头指针

public:
// 方法:
	UseSpaceList();					// 无参数的构造函数
	~UseSpaceList();				// 析构函数
	void Push(void *nodePtr);		// 将指向结点的指针加入到使用空间表中
};

// 使用空间表类的实现部分
UseSpaceList::UseSpaceList()
// 操作结果：构造使用空间表
{
	head = NULL;
}

UseSpaceList::~UseSpaceList()
// 操作结果：释放结点占用存储空间
{
	while (head != NULL)
	{	// 循环释放结点空间
		delete head->data;			// head->data存储的是指向结点的指针
		Node<void *> *tmpPtr = head;// 暂存head
		head = head->next;			// 新的head
		delete tmpPtr;				// 释放tmpPtr
	}
}

void UseSpaceList::Push(void *nodePtr)
// 操作结果：将指向结点的指针加入到使用空间表中
{
	Node<void *> *tmpPtr = new Node<void *>(nodePtr, head);	// 生成新使用空间表结点
	head = tmpPtr;					// tmpPtr主新表头	
}

#ifndef __GLOBAL_USE_SPACE_LIST__
#define __GLOBAL_USE_SPACE_LIST__
static UseSpaceList gUseSpaceList;	// 全局使用空间表对象
#endif


#endif
