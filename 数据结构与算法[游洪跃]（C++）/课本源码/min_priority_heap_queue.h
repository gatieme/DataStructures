#ifndef __MIN_PRIORITY_HEAP_QUEUE__H__
#define __MIN_PRIORITY_HEAP_QUEUE__H__

// 最小优先堆队列类
template<class ElemType>
class MinPriorityHeapQueue 
{
protected:
//  最小优先堆队列实现的数据成员:
	ElemType *elem;									// 存储堆的数组
	int size;										// 堆最大元素个数
	int count;										// 堆元素个数

// 辅助函数:
	void Init(int sz);								// 初始化优先队列
	void SiftAdjust(int low, int high);
		// 调整elem[low]使其elem[low .. high]按关键字成为一个小顶堆
	void BuildHeap();								// 建立堆

public:
//  抽象数据类型方法声明及重载编译系统默认方法声明:
	MinPriorityHeapQueue(int sz = DEFAULT_SIZE);	// 构造最大元素个数为sz的堆
	MinPriorityHeapQueue(ElemType e[], int cnt = 0, int sz = DEFAULT_SIZE);	
		// 构造堆元素为e[0] ...e[cnt - 1], 最大元素个为sz的堆
	virtual ~MinPriorityHeapQueue();				// 析构函数
	int Length() const;								// 求优先队列长度			 
	bool Empty() const;								// 判断优先队列是否为空
	void Clear();									// 将优先队列清空
	void Traverse(void (*Visit)(ElemType &)) ;		// 遍历优先队列
	StatusCode OutQueue(ElemType &e);				// 出队操作
	StatusCode GetHead(ElemType &e) const;			// 取队头操作
	StatusCode InQueue(const ElemType &e);			// 入队操作
	MinPriorityHeapQueue(const MinPriorityHeapQueue<ElemType> &copy);		// 复制构造函数
	MinPriorityHeapQueue<ElemType> &operator =(const MinPriorityHeapQueue<ElemType> &copy);
		// 赋值语句重载
};

// 最小优先堆队列类的实现部分
template <class ElemType>
void MinPriorityHeapQueue<ElemType>::Init(int sz)
// 操作结果：初始化最大元素个数为sz优先队列
{
	elem = new ElemType[sz];						// 为堆分配存储空间
	size = sz;										// 堆最大元素个数
	count = 0;										// 堆元素个数
}

template <class ElemType>
void MinPriorityHeapQueue<ElemType>::SiftAdjust(int low, int high)
// 操作结果:elem[low .. high]中记录的关键字除elem[low]以外都满足堆定义,调
//	整elem[low]使其elem[low .. high]按关键字成为一个小顶堆
{
	for (int f = low, i = 2 * low + 1; i <= high; i = 2 * i + 1)
	{	// f为被调整结点,i为f的最小关键字孩子
		if (i < high && elem[i] > elem[i + 1])
		{	// 右孩子关键字更小, i指向右孩子
			i++;
		}
		if (elem[f] <= elem[i])
		{	// 已成为小顶堆
			break;
		}
		Swap(elem[f], elem[i]);						// 交换elem[f], elem[i]
		f = i;										// 成为新的调整结点		
	}
}

template<class ElemType>
void MinPriorityHeapQueue<ElemType>::BuildHeap()
// 操作结果:建立小顶堆
{
	int i;
	for (i = (count - 2) / 2; i >= 0; --i) 
	{	// 将elem[0 .. count - 1]调整成小顶堆
		SiftAdjust(elem, i, count - 1);
	};
}

template<class ElemType>
MinPriorityHeapQueue<ElemType>::MinPriorityHeapQueue(int sz)
// 操作结果：构造一个最大元素个数为sz的空优先队列
{
	Init(sz);										// 初始化堆
}

template<class ElemType>
MinPriorityHeapQueue<ElemType>::MinPriorityHeapQueue(ElemType e[], int cnt, int sz)	
// 操作结果：构造堆元素为e[0] ...e[cnt - 1], 最大元素个数为sz的堆
{
	Init(sz);										// 初始化堆
	for (int pos = 0; pos < cnt; pos++)
	{	// 将e[]赋值给elem[]
		elem[pos] = e[pos];
	}
	BuildHeap();									// 建立堆
}

template<class ElemType>
MinPriorityHeapQueue<ElemType>::~MinPriorityHeapQueue()
// 操作结果：销毁优先队列
{
	delete []elem;									// 释放堆所占用存储空间
}

template<class ElemType>
int MinPriorityHeapQueue<ElemType>::Length() const
// 操作结果：返回优先队列长度			 
{
	return count;
}

template<class ElemType>
bool MinPriorityHeapQueue<ElemType>::Empty() const
// 操作结果：如优先队列为空，则返回true，否则返回false
{
   return count == 0;
}

template<class ElemType>
void MinPriorityHeapQueue<ElemType>::Clear() 
// 操作结果：清空优先队列
{
	count = 0;										// 空优先队列元素个数为0 
}

template <class ElemType>
void MinPriorityHeapQueue<ElemType>::Traverse(void (*Visit)(ElemType &))
// 操作结果：依次对优先队列的每个元素调用函数(*visit)
{
	for (int pos = 0; pos < count; pos++)
	{	// 对优先队列每个元素调用函数(*visit)
		(*Visit)(elem[pos]);
	}
}


template<class ElemType>
StatusCode MinPriorityHeapQueue<ElemType>::OutQueue(ElemType &e)
// 操作结果：如果优先队列非空，那么删除堆顶元素，并用e返回其值，函数返回SUCCESS,
//	否则函数返回UNDER_FLOW，
{
	if (!Empty()) 
	{	// 优先队列非空
		e = elem[0];								// 用e返回堆顶元素值
		Swap(elem[0], elem[count - 1]);				// 将堆顶元素和最后一个元素交换
		SiftAdjust(0, count - 2);					// 将elem[0 .. count - 2]重新调整为小顶堆
		count--;									// 删除堆顶元素后, 元素个数自减1
		return SUCCESS;								// 操作成功
	}
	else
	{	// 优先队列为空
		return UNDER_FLOW;							// 操作失败
	}
}

template<class ElemType>
StatusCode MinPriorityHeapQueue<ElemType>::GetHead(ElemType &e) const
// 操作结果：如果队列非空，那么用e返回堆顶元素，函数返回SUCCESS,
//	否则函数返回UNDER_FLOW，
{
	if (!Empty()) 
	{	// 优先队列非空
		e = elem[0];								// 用e返回堆顶元素
		return SUCCESS;
	}
	else
	{	// 队列为空
		return UNDER_FLOW;
	}
}

template<class ElemType>
StatusCode MinPriorityHeapQueue<ElemType>::InQueue(const ElemType &e)
// 操作结果：插入元素e，操作成功返回SUCCESS,则否返回OVER_FLOW
{
	if (count >= size)
	{	// 堆已港, 溢出
		return OVER_FLOW;
	}
	else
	{	// 堆未港, 可插入元素e
		int curPos = count++;						// 当前位置
		int parent = (curPos - 1) / 2;				// 当前的双亲	
		elem[curPos] = e;							// 初始时将元素e插入在堆的末端
		while (curPos > 0 && elem[curPos] < elem[parent])
		{	// elem[curPos]小于双亲, 与双亲交换
			Swap(elem[curPos], elem[parent]);		// 交换elem[curPos]与双亲元素elem[parent]
			curPos = parent;						// 以双亲作为新当前位置
			parent = (curPos - 1) / 2;				// 当前双亲	
		}
		return SUCCESS;								// 操作成功
	}
}

template<class ElemType>
MinPriorityHeapQueue<ElemType>::MinPriorityHeapQueue(const MinPriorityHeapQueue<ElemType> &copy)
// 操作结果：由优先队列copy构造新优先队列--复制构造函数
{
	Init(copy.count);								// 初始化当前优先队列
	count = copy.count;								// 新优先队列的元素个数
	for (int pos = 0; pos < count; pos++)
	{	// 将copy优先队列每个元素赋值给当前优先队
		elem[pos] = copy.elem[pos];
	}
}

template<class ElemType>
MinPriorityHeapQueue<ElemType> &MinPriorityHeapQueue<ElemType>::operator =(const MinPriorityHeapQueue<ElemType> &copy)
// 操作结果：将优先队列copy赋值给当前优先队列--赋值语句重载
{
	if (&copy != this)
	{
		delete []elem;								// 释放空间
		Init(copy.count);							// 初始化当前优先队列
		count = copy.count;							// 新优先队列的元素个数
		for (int pos = 0; pos < count; pos++)
		{	// 将copy优先队列每个元素赋值给当前优先队
			elem[pos] = copy.elem[pos];
		}
	}
	return *this;
}

#endif