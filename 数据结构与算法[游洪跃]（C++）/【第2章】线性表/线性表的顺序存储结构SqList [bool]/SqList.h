/********************************************************************************
CopyRight  : 2012-2013, HerBinUnversity, GatieMe
File Name  : SqList.h
Description: 线性表顺序存储结构
Author     : Gatie_Me
Version    : Copyright 2012
Data_Time  : 20112-8-29 10:28:43
Content    : 数据结构与算法（C++）版书上源码
********************************************************************************/


/********************************************************************************
History    :C++线性顺序表模版的实现

版本1.0.0   完成与2012/9/4 20:25增添外部函数文件Other
            基本实现SqList.h文件的基本功能, 并且编译通过...
********************************************************************************/


#ifndef SQLIST_H_INCLUDED
#define SQLIST_H_INCLUDED



#include <cstdio>
//#include <iostream>
//using namespace std;


//#define DEBUG                     // 如果进行调试请将此注释打开
///顺序模版类SqList定义部分======================================================================
template <class ElemType>   //数据成员ElemType
class SqList
{
/*===========================[Friend-=>友元声明]===========================*/
    //friend std::istream &operator>>(std::istream &in, const SqList<ElemType> &inList);

    //friend std::ostream &operator<<(std::ostream &out, const SqList<ElemType> &outList);

    friend SqList<ElemType> Difference(const SqList<ElemType> &listA, const SqList<ElemType> &listB);  //求集合listA与集合listB的差集

    friend SqList<ElemType> Comon(const SqList<ElemType> &listA, const SqList<ElemType> &listB);

    friend SqList<ElemType> ComOrDiff(const SqList<ElemType> &listA, const SqList<ElemType> &listB, bool isExist = false);
/*===========================[Friend-=>友元声明]===========================*/



/*===========================[PUBLIC-=>公共接口]===========================*/
//抽象数据类型方法声明及重载编译系统默认方法声明：
  public :
//模版类基本成员函数声明
    SqList(int size = 100);            //构造函数模版   //在头文件中DEFAULT_SIZE宏定义为1000

    SqList(const SqList<ElemType> &copy);       //赋值构造函数模版

    virtual ~SqList( );                         //虚析构函数模版
//模版类特征成员函数声明
    int Length( ) const;                       //获取线性表长度

    int Size( ) const;                          //获取线性表的最大长度

    bool Empty( ) const;                       //判断线性表是否为空

    void Clean( );                             //清空线性表

    bool SetLength(int len);                    // 重新设置线性表的表长

    bool Reset(int size);                              // 重置线性表单元

    bool Traverse(void(*visit)(const ElemType &));     //遍历线性表

    bool IsExist(const ElemType &elemType) const;   //判断数据elemType在不在当前线性表中

    bool GetElem(int position, ElemType &elemType);  //输出指定位置position的元素

    bool SetElem(int position, const ElemType &elemType);   //设置指定位置position的元素

    bool Delete(int position, ElemType &elemType);               //删除指定位置position的元素

    bool Insert(int position, const ElemType &elemType);   //在指定位置position插入元素

    bool InList(const ElemType &elemType);       //将数据elemType插在线性表的末尾

//重载函数声明
    SqList<ElemType> &operator=(const SqList<ElemType> &copy);      //赋值运算符重载

    SqList<ElemType> &operator[](const int index);                 //重载下标访问函数

//特殊函数模版[排序Sort]
    bool Swap(int mPosition, int nPosition);    //交换线性表第mPosition个元素和第nPosition个元素

    bool BubbleSort(bool minTomax = true);     //冒泡法排序

    bool SelectSort(bool minTomax = true);      //选择法排序

/*===========================[PUBLIC-=>公共接口]===========================*/


/*==========================[PROTECTED-=>保护对象]==========================*/
  protected :
//保护函数对象
    /// 用户无法查看到此线性表是否为满
    bool Full( ) const;      //判断线性表是否已满
    /// 函数中bool Reset( )和SqList( )中均使用了Init函数所以物品保留了此接口
    void Init(int size = 100);      //初始化线性表
//保护数据成员
    int length;                                 //线性表元素个数
    int maxSize;                                //顺序表最大元素个数
    ElemType *elems;                           //元素存储空间
   // enum bool = {RANGE_ERROR, EMPTY_ERROE, true, FULL_lIST};
/*==========================[PROTECTED-=>保护对象]==========================*/

};


///顺序模版类SqList实现部分===============================================================
/**友元函数【实现】*****************************************************************
   // friend std::istream &operator>>(std::istream &in, const SqList<ElemType> &inList);//重载提取操作符
  //  friend std::ostream &operator<<(std::ostream &out, const SqList<ElemType> &outList);//重载插入操作符
    friend SqList<ElemType> Difference(const SqList<ElemType> &listA, const Sqlist<ElemType>listB);//求集合listA与集合listB的差集
    friend SqList<ElemType> Comon(const SqList<ElemType> &listA, const Sqlist<ElemType> &listB);
    friend SqList<ElemType> ComOrDiff(const SqList<ElemType> &listA, const Sqlist<ElemType> &listB, bool isExist = false);
*****************************************************************【实现】友元函数**/
//函数名称：istream &operator>>(istream &in, const SqList<ElemType>inList)
//初始条件：线性表已经建立, 且元素类型ElemType可以使用>>(提取), <<()
////操作结果：将线性表的数据提取到输入流中
//template <class ElemType>
//std::istream &operator>>(std::istream &in, const SqList<ElemType>inList)
//{
//
//    return in;
//}

//函数名称：ostream &operator<<(ostream &out, const SqList<ElemType> &outList)
//初始条件：线性表已经建立
//操作结果：将线性表的数.据插入到输出流中
//template <class ElemType>
//std::ostream &operator<<(std::ostream &out, const SqList<ElemType> &outList)
//{
//    return out;
//}


//函数名称：SqList<ElemType> Difference(const Sqlist<ElemType> &listA, const SqList<ElemType> &listB)
//初始条件：参数线性表listA和listB均存在,
//操作结束：返回listA和listB集合的差集
//操作方法：在listA中取出元素在listB中进行查找, 如果未在listB中出现, 将其查到listC中
template <class ElemType>
SqList<ElemType> Difference(const SqList<ElemType> &listA, const SqList<ElemType> &listB)
{
    ElemType temp;
    SqList<ElemType> listC;

//listC.Clean( );     //将结果串清空
    for(int aPosition = 1; aPosition < listA.length; aPosition++)   //循环线性表A每个个元素
    {
        listA.GetElem(aPosition, temp);     //取出线性表A的当前位置的元素
        if(listB.IsExist(temp) == false)     //如果listA中取出的数据temo不在listB中
        {
            listC.InList(temp);    //将数据temp插入listC的末尾
        }
    }
    return listC;
}


//函数名称：SqList<ElemType> Difference(const Sqlist<ElemType> &listA, const SqList<ElemType> &listB)
//初始条件：参数线性表listA和listB均存在,
//操作结束：返回listA和listB集合的交集
//操作方法：在listA中取出元素在listB中进行查找, 如果未在listB中出现, 将其查到listC中
template <class ElemType>
SqList<ElemType> Comon(const SqList<ElemType> &listA, const SqList<ElemType> &listB)
{
    ElemType temp;
    SqList<ElemType> listC;

//listC.Clean( );     //将结果串清空
    for(int aPosition = 1; aPosition < listA.length; aPosition++)   //循环线性表A每个个元素
    {
        listA.GetElem(aPosition, temp);     //取出线性表A的当前位置的元素
        if(listB.IsExist(temp) == true)     //如果listA中取出的数据temp在listB中
        {
            listC.InList(temp);    //将数据temp插入listC的末尾
        }
    }
    return listC;
}


//函数名称：SqList<ElemType> Difference(const Sqlist<ElemType> &listA, const SqList<ElemType> &listB)
//初始条件：参数线性表listA和listB均存在,
//操作结束：isExist = false求差集, isExist = true求交集
template <class ElemType>
SqList<ElemType> Difference(const SqList<ElemType> &listA, const SqList<ElemType> &listB, bool isExist/* = false*/)
{
    ElemType temp;
    SqList<ElemType> listC;

//listC.Clean( );     //将结果串清空
    for(int aPosition = 1; aPosition < listA.length; aPosition++)   //循环线性表A每个个元素
    {
        listA.GetElem(aPosition, temp);     //取出线性表A的当前位置的元素
        if(listB.IsExist(temp) == isExist)     //如果listA中取出的数据temo不在listB中
        {
            listC.InList(temp);    //将数据temp插入listC的末尾
        }
    }
    return listC;
}

/**保护函数对象【实现】*******************************************************
    bool Full( ) const;      //判断线性表是否已满
    void Init(int size);     //初始化线性表
********************************************************【实现】保护函数对象*/

//函数名称：Full( ) const
//初始条件：线性表已经存在
//操作结果：如果线性表已满，则返回True，否则返回False
template <class ElemType>
bool SqList<ElemType>::Full( ) const              //判断线性表是否已满
{
    return length == maxSize;
}


//函数名称：void Init( ) const
//初始条件：初始化线性表
//操作结果：初始化线性表为最大元素个数为size的空线性表
template <class ElemType>
void SqList<ElemType>::Init(int size/**/)
{
    maxSize = size;    //初始化线性表大小为size
    if(elems != NULL) delete elems;  //如果线性表空间被占用，则立即清空
    elems = new ElemType[maxSize];   //开辟空间
    length = 0;   //当前元素个数为0
}


/**模版类基本成员函数【实现】**********************************************
    SqList(int size = DEFAULT_SIZE);            //构造函数模版
    SqList(const SqList<ElemType> &copy);       //赋值构造函数
    virtual ~SqList( );                         //虚析构函数模版
*********************************************【实现】模版类基本成员函数**/

//函数名称：SqList(int size = DEFAULT_SIZE);
//初始条件：无重名类对象
//操作结果：构造一个最大元素个数为size的空顺序表
template <class ElemType>
SqList<ElemType>::SqList(int size)     //构造函数模版
{
   // elems = NULL;     //顺序空间指向空
   // Init(size);       //初始化线性表
	maxSize = size;						// 最大元素个数
	//if (elems != NULL) delete []elems;	// 释放存储空间
	elems = new ElemType[maxSize];		// 分配存储空间
	length = 0;							// 空线性表元素个数为0
}

//函数名称：SqList(const SqList<ElemType> &copy);
//初始操作：参数对象存在
//操作结果：由参数线性表构造出相同的新线性表
template <class ElemType>
SqList<ElemType>::SqList(const SqList<ElemType> &copy)    //赋值构造函数
{
    maxSize = copy.maxSize;     //[复制]参数线性表的最大元素个数
    length = copy.length;       //[复制]参数线性表的元素个数

    ElemType elem;
    Init(copy.maxSize);     //以参数线性表的最大元素个数初始化目的线性表

    for(int curPosition = 1; curPosition <= copy.length; curPosition++)   //循环控制复制线性表的数据元素
    {
        //下面的操作等价与this->elems[position-1] = copy.elems[position-1];
        copy.GetElem(curPosition, elem);            //取出参数线性表的第curPosition个元素, 存储在elems中
        this->SetElem(curPosition, elem);           //将数据elems存在目的线性表的第curPosition个位置
        //this->Insert(curPosition, elems);         //也可以将数据elems插入线性表的第curPosition个位置

        //this->InList(elem);                       //但是不可以将元素直接填入线性表
    }
}


//函数名称：virtual ~SqList( );
//初始条件：已建立类对象
//操作结果：销毁线性表
template <class ElemType>
SqList<ElemType>::~SqList( )    //虚析构函数模版
{
    if(elems != NULL)
    {
        delete elems;   //释放存储空间
    }
}

/**模版类特征成员函数【实现】*************************************************************
    int Length( ) const;             //获取线性表长度
    int Size( ) const;             //获取线性表的最大长度
    bool Empty( ) const;          //判断线性表是否为空
    void Clean( );                             //清空线性表
    bool Reset( );                              // 重置线性表单元
    bool Acquire(void(*visit)(const ElemType &))
    bool Traverse(void(*visit)(const ElemType &)) const;//遍历线性表
    bool IsExist(const ElemType &elemType) const;   //判断数据elemType在不在当前线性表中
    bool GetElem(int position, const ElemType &elemType);//获取指定位置position的元素
    bool SetElem(int position, const ElemType &elemType);//设置指定位置position的元素
    bool Delete(int position);    //删除指定位置position的元素
    bool Insert(int position, const ElemType &elemType);//在指定位置position插入元素
    bool InList(const ElemType &elemType);       //将数据elemType插在线性表的末尾
模版类特征成员函数【实现】***************************************************************/

//函数名称：int Length( ) const;
//初始条件：线性表已经存在
//操作结果：返回线性表元素个数
template <class ElemType>
int SqList<ElemType>::Length( ) const         //获取线性表长度
{
    return length;
}

//函数名称：int Size( ) const;
//初始条件：线性表已经存在
//操作结果：返回线性表最大元素的个数
template <class ElemType>
int SqList<ElemType>::Size( ) const  //获取线性表的最大长度
{
    return maxSize;
}

//函数名称：bool Empty( ) const;
//初始条件：线性表已经存在
//操作结果：如果线性表为空, 返回True，否则返回False
template <class ElemType>
bool SqList<ElemType>::Empty( ) const     //判断线性表是否为空
{
    return (length == 0);
//    if(length == 0)
//    {
//        return true;
//    }
//    else
//    {
//        return false;
//    }
}

//函数名称：void Clean( );
//初始条件：线性表存在
//操作结果；清空线性表
template <class ElemType>
void SqList<ElemType>::Clean( ) // 清空线性表
{
    length = 0;    //只需将元素个数置为空即可, 无需删除线性表内存空间
}


//函数名称：bool SetLength(int len);
//初始条件：线性表存在, len值复合要求
//操作结果；重新设置线性表表长
template <class ElemType>
bool SqList<ElemType>::SetLength(int len)		                 // 更改线性表的表长
{
    if(len > this->maxSize)
	{
	    std::cout <<"超过线性表的最大长度" <<std::endl;
	    return false;
	}
	else if(len < this->length)
	{
		char answer;
	    std::cout <<"您要更改的表长小于当前线性表的表长" <<std::endl;
        std::cout <<"继续更改可能会损失数据, 是否继续?(y/n)" <<std::endl;
		while( 1 )
		{
			answer = getchar();
			if(answer == 'y' || answer == 'Y')
			{
			    std::cout <<"用户确认, 更改成功" <<std::endl;
				length = len;
				return true;
			}
			else if(answer == 'n' || answer == 'N')
			{
			    std::cout <<"用户取消, 成功退出"  <<std::endl;
			    return  false;
			}
		}
	}
	this->length = len;
	std::cout <<"数据域合法, 成功修改线性表长为" <<this->length <<std::endl;

	return true;
}


//函数名称：bool Reset(int size)
//初始条件：线性表存在
//操作结果；如果用户回答是, 将删除原来的单元而重置新的单元
template <class ElemType>
bool SqList<ElemType>::Reset(int size/*= maxSize*/)                              // 重置线性表单元
{
    std::cout <<"当前线性表宽度域为" <<this->maxSize <<"已经存储了" <<this->length <<"个数据" <<std::endl <<std::endl;
    if(size == this->maxSize)   // 如果当前的线性表最大的宽度域是当前的参数
    {
        std::cout <<"重置单元大小与原单元大小相同, 不需要重置." <<std::endl;
        return false;
    }
    else
    {
        std::cout <<"请问你真的需要重置此单元么?" <<std::endl;

        char ch;
        bool answer = true;      // 初始化继续单元为false
        do
        {	// 循环直到用户输入恰当的回答为止
            if (answer)
            {	// 初始回答
                std::cout << "(y, n)?";
            }
            else
            {	// 非初始回答
                std::cout << "用y或n回答:";
            }

            while ((ch = getchar( )) == '\n');	// 跳过空格,制表符及换行符获取一字符
            answer = false;
        }while (ch != 'y' && ch != 'Y' && ch != 'n' && ch != 'N');

        if(ch == 'n' || ch == 'N')
        {
            std::cout <<"用户取消重置..." <<std::endl;
            return false;
        }
        else
        {
            std::cout <<"重置开始..." <<std::endl;
            this->Init(size);   // 初始化单元

//            if(this->elems != NULL)
//            {
//                delete[] elems;     // 删除原有的内存单元
//            }
//            elems = new elems[size];  // 开辟新单元
//            this->maxSize = size;     // 跟新
//            this->length = 0;
        }
    }
}


//函数名称：void Traverse(void(*visit)(const ElemType &));
//初始条件：线性表已经存在
//操作结果：依次对线性表的么个元素调用（* visit）

template <class ElemType>
bool SqList<ElemType>::Traverse(void (*visit)(const ElemType &))
{
    if(this->length == 0)
    {
        std::cout <<"当前线性表为空, 无法实现遍历..." <<std::endl;   // 错误信息提示
        return false;
    }
	for (int curPosition = 1; curPosition <= Length(); curPosition++)
	{	// 对线性表的每个元素调用函数(*visit)
		(*visit)(elems[curPosition - 1]);
        return true;
    }
}


//函数名称：bool IsExist(const ElemType &elemType) const;
//初始条件：线性表已存在
//操作结果：如果数据elemType在线性表中, 返回True, 否则返回False
template <class ElemType>
bool SqList<ElemType>::IsExist(const ElemType &elemType) const   //判断数据elemType在不在当前线性表中
{
    if(length == 0)
    {
        return false;
    }
    //ElemType temp;
    for(int curPosition = 1; curPosition < length; curPosition++)   //循环每个元素
    {
        if(elems[curPosition-1] == elemType)
        {
            return true;   //数据elemType在线性表中
        }
//        this->GetElem(position, temp)
//        if(temp == elemType)
//        {
//            return true;
//        }
    }
    return false;
}

//函数名称：bool GetElem(int position, const ElemType &elemType);
//初始条件：线性表已存在, 1<=position<=length
//操作条件：先检查线性表是否已经置空, 如果是空的，返回EMPTY_LIST,
//          然后如果下标position不合法返回NOT_PRESENT,
//          否则用elemType返回线性表第position个元素，返回ENTRY_FOUND
template <class ElemType>
bool SqList<ElemType>::GetElem(int position, ElemType &elemType)  //获取指定位置position的元素
{
//写法Ⅰ
    if(length == 0)
    {
        std::cout <<"当前线性表为空, 无法获取第" <<position <<"个元素的信息" <<std::endl;
        return false;     //线性表为空
    }

    if(position < 1 || position > length)    //如果索引不合法
    {
        if(position < 1)
        {
            std::cout <<"索引" <<position <<"为负..." <<std::endl;
        }
        else
        {
            std::cout <<"当前线性表长" <<this->length <<", 索引" <<position <<"越界..." <<std::endl;
        }
        return false;
    }
    else      //否则索引position是合法的
    {
        elemType = elems[position-1];    //用elemType返回线性表的第position个元素, 该元素下标为position-1

        return true;    //元素存在
    }
////写法Ⅱ
//    if(position >= 1 && position <= length)
//    {
//        elems = elems[position-1];
//        return ENTEY_FOUND;
//    }
//    else
//    {
//        return NOT_PRESENT;
//    }
}

//函数名称：bool SetElem(int position, const ElemType &elemType);
//初始条件：线性表已存在, 1<=position<=length
//操作结果: 将线性表第position个元素修改为elemType，
//实现方法：先检查线性表是否已经置空, 如果是空的，返回false,
//          然后如果position合法时，将线性表第position个元素修改为elemType，
//          并返回true, 否则返回false
template <class ElemType>
bool SqList<ElemType>::SetElem(int position, const ElemType &elemType)
{
#if defined DEBUG           // 如果宏定义了DEBUG, 执行一下语句
std::cout <<"函数SetElem..." <<std::endl;
#endif
///因为下面注释掉的代码, 我的程序出现了一个非常巨大的错误
//    if(length = 0)
//    {
//        std::cout <<"当前线性表为空,无法修改第" <<position <<"个元素的信息" <<std::endl;
//        return false;   //线性表为空
//    }
    if(position < 1 || position > length+1)    //如果索引不合法
    {
        if(position < 1)
        {
            std::cout <<"索引" <<position <<"为负..." <<std::endl;
        }
        else
        {
            std::cout <<"当前线性表长" <<this->Length( ) <<", 索引" <<position <<"越界..." <<std::endl;
        }
        return false;   //索引不合法
    }
    else      //否则position合法
    {
        elems[position-1] = elemType;    //将索引对应的数据值修改为elemType
        return true;
    }
}

//函数名称：bool Delete(int position);
//初始条件：线性表存在, 1<=position<=length
//操作结果：删除当前线性表中索引对应的元素
//实现方法：假如线性表为空，返回EMPTY_LIST,
//          然后如果索引position不合法返回RANGE_ERROR,
//          否则删除当前线性表中索引对应的元素, 并用elemType返回其值, 同时返回true
template <class ElemType>
bool SqList<ElemType>::Delete(int position, ElemType &elemType)   //删除指定位置position的元素
{
    if(length == 0)
    {
        std::cout <<"线性表为空, 无法删除第" <<position <<"个元素的信息" <<std::endl;
        return false;      //线性表为空
    }
    if(position < 1 || position > length)
    {
        if(position < 1)
        {
            std::cout <<"索引" <<position <<"为零为负..." <<std::endl;
        }
        else
        {
            std::cout <<"当前线性表长" <<this->length <<", 索引" <<position <<"越界..." <<std::endl;
        }
        return false;
    }
    else
    {
        ElemType temp;
        //elemType = elems[position-1];   //用elemType返回索引position对应的值
        this->GetElem(position, elemType);
        for(int curPosition = position+1; curPosition <= length; curPosition++)  //依次将索引position后面的数据前移一位
        {
            this->GetElem(curPosition, temp);    //保存当前位置的数据
            this->SetElem(curPosition-1, temp);    //将当前的数据插入到前一个位置
        }
        length--;           //删除position的元素后，线性表的元素个数减少1

        return true;     //删除成功

//    //与上面的循环等价的代码段Ⅰ
//        for(int curPosition = position, curPosition <= length-1; curPosition++)
//        {
//            this->GetElem(curPosition+1, temp);    //保存当前位置下一位的数据
//            this->SetElem(curPosition, temp);    //将下一位的数据插入到当前位置
//        }
//    //与上面的循环等价的代码段Ⅱ
//        for(int curPosition = length; curPosition > position; curPosition--)
//        {
//            this->GetElem(curPosition, temp);    //保存当前位置的数据
//            this->SetElem(curPosition-1, temp);    //将当前的数据插入到前一个位置
//        }
//    //与上面的循环等价的代码段Ⅲ
//        for(int curPosition = length-1; curPosition >= position; curPosition--)
//        {
//            this->GetElem(curPosition+1, temp);    //保存当前位置的数据
//            this->SetElem(curPosition, temp);    //将当前的数据插入到前一个位置
//        }
    }
}

//函数名称：bool Insert(int position, const ElemType &elemType);
//初始条件：线性表已存在, 1<=position<=length+1
//操作结果：将数据elemType插入线性表的第position个位置
//实现方法: 先检查线性表是否已经置空, 如果是空的，返回EMPTY_LIST,
//          然后如果position合法时，将数据elemType插入线性表的第position个位置
//          并返回true, 否则如果检查线性表不合法返回RANGE_ERROR
template <class ElemType>
bool SqList<ElemType>::Insert(int position, const ElemType &elemType)
{
#if defined DEBUG           // 如果宏定义了DEBUG, 执行一下语句
std::cout <<"函数Insert..." <<std::endl;
#endif

    if(this->Full())
    {
        std::cout <<"线性表已满, 无法继续插入元素" <<std::endl;
        return false;
    }
    else if(position < 1 || position > this->length+1)
    {
        if(position < 1)
        {
            std::cout <<"索引" <<position <<"为零或者负..." <<std::endl;
        }
        else
        {
            std::cout <<"当前线性表长" <<this->Length() <<", 索引" <<position <<"越界..." <<std::endl;
        }
        return false;
    }
    else
    {

        ElemType temp;
        if(length == 0)
        {
            this->SetElem(1, elemType);
            length++;
            return true;
        }

        for(int curPosition = this->length; curPosition >= position; curPosition--)   //将插入目标点以后的数据依次后移
        {
            this->GetElem(curPosition, temp);   //保存当前位置的数据
            this->SetElem(curPosition+1, temp); //将保存的数据添加在
        }
//     //上面的循环等价与
//        for(int curPosition = length+1; curPosition > position; curPosition++)
//        {
//            this->GetElem(position-1, temp);   //保存当前位置的数据
//            this->SetElem(position, temp); //将保存的数据添加在
//        }
       // elems[position-1] = elemType;   //将数据elemType存储到线性表的第position个位置
        this->SetElem(position, elemType);  //同上-将数据elemType存储到线性表的第position个位置
        this->length++;    //所有操作完成后, 已经插入一个数据, 这时线性表的元素个数进1
        return true;     //插入成功
    }
}

//函数名称：bool InList(const ElemType &elemType);
//初始条件：线性表已存在, 且未满，[lenght < maxSize]
//操作条件：首先判断线性表是否已满, 如果满了, 返回FULL_LIST,
//          然后将元素插入在线性表的末尾， 并返回true;
template <class ElemType>
bool SqList<ElemType>::InList(const ElemType &elemType)       //将数据elemType插在线性表的末尾
{
    //if(lenth == maxSize)
    if(this->Full() == true)
    {
        std::cout <<"当前线性表已满, 无法将数据插入尾端.." <<std::endl;
        return false;    //线性表已满
    }

    elems[length] = elemType;   //将数据elemType插在线性表的末尾
    this->length++;
   // this->SetElem(++length, elemType);


    return true;
}

/**重载函数声明【实现】***************************************************************************
    SqList<ElemType> &operator=(const SqList<ElemType> &copy);      //赋值运算符重载
    SqList<ElemType> &operator[](const int index);                 //重载下标访问函数
***************************************************************************【实现】重载函数声明**/

//函数名称：SqList<ElemType> &operator=(const SqList<ElemType> &copy);      //赋值运算符重载
//初始条件：被赋值串this和赋值串copy均已存在
//操作结果：将线性表赋值给当前目的线性表
template <class ElemType>
SqList<ElemType>& SqList<ElemType>::operator=(const SqList<ElemType> &copy)
{
    if(copy == this)                // 如果被赋值的线性表copy与目的线性表是同一对象
    {
        return *this;               //  直接返回当前线性表
    }

    if(copy.Empty( ) == true)       // 如果参数赋值串copy是个空串
    {
        this->Clean( );             //直接把目的线性表清空
        return *this;               //返回当前目的线性表对象
    }

    this->Init(copy.maxSize);       // 以赋值线性表的信息初始化当前目的线性表
//    ElemType temp;
    for(int position = 1; position <= copy.length; position++)  // 循环参数赋值线性copy的每个数据元素
    {
        this->elems[position-1] = copy.elems[position-1];       // 将线性表copy的第position个元素赋值给目的线性表*this的第position个字符串
//        copy.GetElem(position, temp);   // 取出赋值线性表的第position个元素
//        this->SetElem(position, temp);   // 将取出的元素填入目的线性表的第position个位置
    }

   // this->maxSize = copy.maxSize;       // 确定目的线性表的最大元素个数标记信息
    this->length = copy.length;         // 确定目的线性表的元素个数

    return *this;            // 返回当前目的线性表
}

//函数名称：SqList<ElemType> &operator[](const SqList<ElemType> &copy);      //赋值运算符重载
//初始条件：被赋值串this和赋值串copy均已存在
//操作结果：将线性表赋值给当前目的线性表
/**特殊函数模版[排序Sort]【实现】*****************************************************************
    bool Swap(int mPosition, int nPosition);//交换线性表第mPosition个元素和第nPosition个元素
    bool BubbleSort(bool minTomax = true);     //冒泡法排序
    bool SelectSort(boolminTomax = true);      //选择法排序
*****************************************************************【实现】特殊函数模版[排序Sort]**/
//函数名称：bool Swqp(int &mPosition, int &nPosition)
//初始条件：线性表存在, 且mPosition和nPosition满足要求
//操作结果：交换线性表中第mPosition个和第nPosition个元素
template <class ElemType>
bool SqList<ElemType>::Swap(int mPosition, int nPosition)
{
    if((mPosition < 0 || mPosition > length)
     || (nPosition < 0 || nPosition > length))
    {
        std::cout <<"参数下标不合法" <<std::endl;
        return false;
    }
    ElemType temp;
    temp = elems[mPosition-1];
    elems[mPosition-1] = elems[nPosition-1];
    elems[nPosition-1] = temp;

    return true;
}
//bool SqList<ElemType>::Swqp(int mPosition, int nPosition)
//{
//    ElemType temp;
//    temp = elems[mPosition];
//    elems[mPosition] = elems[nPosition];
//    elems[nPosition] = temp;
//}
//bool SqList<ElemType>::Swqp(int *mPosition, int *nPosition)
//{
//    ElemType temp;
//    temp = elems[*mPosition];
//    elems[*mPosition] = elems[*nPosition];
//    elems[*nPosition] = temp;
//}


//函数名称：bool SqList<ElemType>::BubbleSort(bool minTomax = true)
//初始条件：线性表已经存在, 并且不是空串
//操作结果：线性表的数据会由无序变成有序[从小到大OR从大到小]
template <class ElemType>
bool SqList<ElemType>::BubbleSort(bool minTomax/*= true*/)
{
    if(length == 0)
    {
        std::cout <<"当前线性表为空, 无法进行排序操作..." <<std::endl;
        return false;     //对空串不能执行排序操作
    }
    //【冒泡发写法Ⅰ】下面是冒泡法的下沉
    for(int j = 0; j < this->length-1; j++)     //共计进行lengh-1次比较
    {
        for(int i = 0; i < this->length-j-1; i++)     //从第一个数开始一直比较到第
        {
            if(((elems[i] > elems[i+1]) && (minTomax == true))    //此时从小到达排序
              || ((elems[i] < elems[i+1]) && (minTomax == false)))   //此时从大到小排序
            {
                this->Swap(i+1, i+2);   //操作:交换第i个数据和第i+1个数据, 结果：第i个数就下沉一位成为第i+1个数
            }
            //然后i++, 当前就到了第i+1个数[也就是原来第i个数], 然后继续依次往后判断
            //一直到最后最大的数就放在了当前循环最后一个位置, 也就是第length-1-j的位置
        }
    }
//    ElemType lastItem, nextItem;
//    for(int j = 1; j < this->length; j++)     //共计进行lengh-1次比较
//    {
//        for(int i = 1; i < this->length-j; i++)     //从第一个数开始一直比较到第
//        {
//            this->GetElem(i, lastItem);
//            this->GetElem(i+1, nextItem);
//            if(((lastItem > nextItem) && (minTomax == true))    //此时从小到达排序
//              || ((lastItem < nextItem) && (minTomax == false)))   //此时从大到小排序
//            {
//                this->Swap(i, i+1);   //操作:交换第i个数据和第i+1个数据, 结果：第i个数就下沉一位成为第i+1个数
//            }
//            //然后i++, 当前就到了第i+1个数[也就是原来第i个数], 然后继续依次往后判断
//            //一直到最后最大的数就放在了当前循环最后一个位置, 也就是第length-1-j的位置
//        }
//    }
    return true;


//    //【冒泡发写法Ⅱ】下面是冒泡法的上升
//    for(int j = 0; j < this->length-1; j++)
//    {
//        for(int i = length-1; i > j; i--)
//        {
//            if(((elems[i-1] < elems[i]) && (minTomax == true))     //此时从小到大
//              || ((elems[i-1] > elems[i]) && (minTomax == false)))  //此时从大到小
//            {
//                this->Swap(i+1, i);     //操作：交换第i个数与第i-1个数, 结果：这时候第i个数就上升了一位, 成为第i-1个数
//
//            }
//            //然后i--, 当前就到了第i个数[也就是原来第i个数], 然后继续依次往后判断
//            //一直到最后最大的数就放在了当前循环最后一个位置, 也就是第length-1-j的位置
//        }
//    }
}


//函数名称：bool SqList<ElemType>::SelectSort(bool minTomax = true)
//初始条件：线性表已经存在, 并且不是空串
//操作结果：线性表的数据会由无序变成有序[从小到大OR从大到小]
template <class ElemType>
bool SqList<ElemType>::SelectSort(bool minTomax/*= true*/)      //选择法排序
{
    if(length == 0)
    {
        std::cout <<"当前线性表为空, 无法进行排序操作" <<std::endl;
        return false;      //对空串不能执行排序操作
    }

    for(int i = 0; i < this->length-1; i++)    //循环线性表的每个前数据
    {
        int k = i;        //保存当前循环的这个位置
        for(int j = i+1; j < this->length; j++)   //循环线性表的每一个后元素
        {

            if(((elems[j] < elems[k]) && (minTomax == true))  //从小到大
              || ((elems[j] > elems[k]) && (minTomax == false))) //从大到小
            {
                k = j;    //保存当前最值拥有者下标
            }
        }      //这样循环一趟以后, k就保存了当前最值的下标
        if(k != i)
        {
            this->Swap(k+1 , i+1);
        }
    }

//    ElemType itemJ, itemK;
//    for(int i = 1; i < this->length; i++)    //循环线性表的每个前数据
//    {
//        int k = i;        //保存当前循环的这个位置
//        for(int j = i+1; j < this->length; j++)   //循环线性表的每一个后元素
//        {
//            this->GetElem(j, itemJ);
//            this->GetElem(k, itemK);
//            if(((itemJ < itemK) && (minTomax == true))  //从小到大
//              || ((itemJ > itemK) && (minTomax == false))) //从大到小
//            {
//                k = j;    //保存当前最值拥有者下标
//            }
//        }      //这样循环一趟以后, k就保存了当前最值的下标
//        if(k != i)
//        {
//            this->Swap(k , i);
//        }
//    }
    return true;           // 排序成功
}




#endif // SQLIST_H_INCLUDED


