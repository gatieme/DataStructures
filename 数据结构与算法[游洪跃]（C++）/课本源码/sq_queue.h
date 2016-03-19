#ifndef __SQ_QUEUE_H__
#define __SQ_QUEUE_H__


// 循环队列类

template<class ElemType>
class SqQueue 
{
protected:
	int front, rear;									// 队头队尾
	int maxSize;										// 队列最大元素个数
	ElemType *elems;									// 元素存储空间

// 辅助函数:
	bool Full() const;									// 判断栈是否已满
	void Init(int size);								// 初始化队列

public:
//  抽象数据类型方法声明及重载编译系统默认方法声明:
	SqQueue(int size = DEFAULT_SIZE);					// 构造函数
	virtual ~SqQueue();									// 析构函数
	int Length() const;									// 求队列长度			 
	bool Empty() const;									// 判断队列是否为空
	void Clear();										// 将队列清空
	void Traverse(void (*Visit)(const ElemType &)) const;	// 遍历队列
	StatusCode OutQueue(ElemType &e);					// 出队操作
	StatusCode GetHead(ElemType &e) const;				// 取队头操作
	StatusCode InQueue(const ElemType &e);				// 入队操作
	SqQueue(const SqQueue<ElemType> &copy);				// 复制构造函数
	SqQueue<ElemType> &operator =(const SqQueue<ElemType> &copy);// 赋值语句重载
};



// 循环队列类的实现部分


template <class ElemType>
bool SqQueue<ElemType>::Full() const
// 操作结果：如队列已满，则返回true，否则返回false
{
	return Length() == maxSize - 1;
}

template <class ElemType>
void SqQueue<ElemType>::Init(int size)
// 操作结果：初始化队列为最大元素个数为size的空队列
{
	maxSize = size;							// 最大元素个数
	if (elems != NULL) delete []elems;		// 释放存储空间
	elems = new ElemType[maxSize];			// 分配存储空间
	rear = front = 0;						// 空队列队头与队尾相等
}

template<class ElemType>
SqQueue<ElemType>::SqQueue(int size)
// 操作结果：构造一个最大元素个数为size的空循环队列
{
	elems = NULL;							// 未分配存储空间前,elems为空
	Init(size);								// 初始化队列
}

template <class ElemType>
SqQueue<ElemType>::~SqQueue()
// 操作结果：销毁队列
{
	delete []elems;							// 释放存储空间
}

template<class ElemType>
int SqQueue<ElemType>::Length() const
// 操作结果：返回队列长度			 
{
	return (rear - front + maxSize) % maxSize;
}

template<class ElemType>
bool SqQueue<ElemType>::Empty() const
// 操作结果：如队列为空，则返回true，否则返回false
{
   return rear == front;
}

template<class ElemType>
void SqQueue<ElemType>::Clear() 
// 操作结果：清空队列
{
	rear = front = 0;
}

template <class ElemType>
void SqQueue<ElemType>::Traverse(void (*Visit)(const ElemType &)) const
// 操作结果：依次对队列的每个元素调用函数(*visit)
{
	for (int curPosition = front; curPosition != rear; 
		curPosition = (curPosition + 1) % maxSize)
	{	// 对队列每个元素调用函数(*visit)
		(*Visit)(elems[curPosition]);
	}
}


template<class ElemType>
StatusCode SqQueue<ElemType>::OutQueue(ElemType &e)
// 操作结果：如果队列非空，那么删除队头元素，并用e返回其值，函数返回SUCCESS,
//	否则函数返回UNDER_FLOW，
{
	if (!Empty()) 
	{	// 队列非空
		e = elems[front];					// 用e返回队头元素
		front = (front + 1) % maxSize;		// front指向下一元素
		return SUCCESS;
	}
	else
	{	// 队列为空
		return UNDER_FLOW;
	}
}

template<class ElemType>
StatusCode SqQueue<ElemType>::GetHead(ElemType &e) const
// 操作结果：如果队列非空，那么用e返回队头元素，函数返回SUCCESS,
//	否则函数返回UNDER_FLOW，
{
	if (!Empty()) 
	{	// 队列非空
		e = elems[front];					// 用e返回队头元素
		return SUCCESS;
	}
	else
	{	// 队列为空
		return UNDER_FLOW;
	}
}

template<class ElemType>
StatusCode SqQueue<ElemType>::InQueue(const ElemType &e)
// 操作结果：如果队列已满，返回OVER_FLOW,
//	否则插入元素e为新的队尾，返回SUCCESS
{
	if (Full())
	{	// 队列已满
		return OVER_FLOW;
	}
	else
	{	// 队列未满，入队成功
		elems[rear] = e;					// 插入e为新队尾
		rear = (rear + 1) % maxSize;		// rear指向新队尾
		return SUCCESS;
	}
}

template<class ElemType>
SqQueue<ElemType>::SqQueue(const SqQueue<ElemType> &copy)
// 操作结果：由队列copy构造新队列--复制构造函数
{
	elems = NULL;							// 未分配存储空间前,elems为空
	Init(copy.maxSize);						// 初始化新队列
	front = copy.front;						// 复制队头位置	
	rear = copy.rear;						// 复制队尾位置
	for (int curPosition = front; curPosition != rear; 
		curPosition = (curPosition + 1) % maxSize)
	{	// 复制循环队列元素
		elems[curPosition] = copy.elems[curPosition];
	}
}

template<class ElemType>
SqQueue<ElemType> &SqQueue<ElemType>::operator =(const SqQueue<ElemType> &copy)
// 操作结果：将队列copy赋值给当前队列--赋值语句重载
{
	if (&copy != this)
	{
		Init(copy.maxSize);			 		// 初始化当前队列
		front = copy.front;					// 复制队头位置	
		rear = copy.rear;					// 复制队尾位置
		for (int curPosition = front; curPosition != rear; 
			curPosition = (curPosition + 1) % maxSize)
		{	// 复制循环队列元素
			elems[curPosition] = copy.elems[curPosition];
		}
	}
	return *this;
}

#endif
