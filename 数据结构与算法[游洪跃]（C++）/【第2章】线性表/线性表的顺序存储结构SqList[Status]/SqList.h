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
********************************************************************************/


#ifndef SQLIST_H_INCLUDED
#define SQLIST_H_INCLUDED




#include "MyHeadFile.h"

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
    SqList(int size = DEFAULT_SIZE);            //构造函数模版   //在头文件中DEFAULT_SIZE宏定义为1000

    SqList(const SqList<ElemType> &copy);       //赋值构造函数模版

    virtual ~SqList( );                         //虚析构函数模版
//模版类特征成员函数声明
    int Length( ) const;                       //获取线性表长度

    int Size( ) const;                          //获取线性表的最大长度

    bool Empty( ) const;                       //判断线性表是否为空

    void Clean( );                             //清空线性表

    void Traverse(void(*visit)(const ElemType &)) const;     //遍历线性表


    bool IsExist(const ElemType &elemType) const;   //判断数据elemType在不在当前线性表中

    StatusCode GetElem(int position, ElemType &elemType);  //输出指定位置position的元素

    StatusCode SetElem(int position, const ElemType &elemType);   //设置指定位置position的元素

    StatusCode Delete(int position, const ElemType &elemType);               //删除指定位置position的元素

    StatusCode Insert(int position, const ElemType &elemType);   //在指定位置position插入元素

    StatusCode InList(const ElemType &elemType);       //将数据elemType插在线性表的末尾

//重载函数声明
    SqList<ElemType> &operator=(const SqList<ElemType> &copy);      //赋值运算符重载

    SqList<ElemType> &operator[](const int index);                 //重载下标访问函数

//特殊函数模版[排序Sort]
    StatusCode Swap(int &mPosition, int &nPosition);    //交换线性表第mPosition个元素和第nPosition个元素

    StatusCode BubbleSort(bool minTomax = true);     //冒泡法排序

    StatusCode SelectSort(bool minTomax = true);      //选择法排序

/*===========================[PUBLIC-=>公共接口]===========================*/


/*==========================[PROTECTED-=>保护对象]==========================*/
  protected :
//保护函数对象
    bool Full( ) const;      //判断线性表是否已满
    void Init(int size = DEFAULT_SIZE);     //初始化线性表
//保护数据成员
    int length;                                 //线性表元素个数
    int maxSize;                                //顺序表最大元素个数
    ElemType *elems;                           //元素存储空间
   // enum StatusCode = {RANGE_ERROR, EMPTY_ERROE, SUCCESS, FULL_lIST};
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
void SqList<ElemType>::Init(int size)
{
    maxSize = size;    //初始化线性表大小为size
    if(elems != NULL) delete elems;  //如果线性表空间被占用，则立即清空
    elems = new ElemType(maxSize);   //开辟空间
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
    elems = NULL;     //顺序空间指向空
    Init(size);       //初始化线性表
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
    void Traverse(void(*visit)(const ElemType &)) const;//遍历线性表
    bool IsExist(const ElemType &elemType) const;   //判断数据elemType在不在当前线性表中
    StatusCode GetElem(int position, const ElemType &elemType);//获取指定位置position的元素
    StatusCode SetElem(int position, const ElemType &elemType);//设置指定位置position的元素
    StatusCode Delete(int position);    //删除指定位置position的元素
    StatusCode Insert(int position, const ElemType &elemType);//在指定位置position插入元素
    StatusCode InList(const ElemType &elemType);       //将数据elemType插在线性表的末尾
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
void SqList<ElemType>::Clean( ) //清空线性表
{
    length = 0;    //只需将元素个数置为空即可, 无需删除线性表内存空间
}

//函数名称：void Traverse(void(*visit)(const ElemType &)) const;
//初始条件：线性表已经存在
//操作结果：依次对线性表的么个元素调用（* visit）
template <class ElemType>
void SqList<ElemType>::Traverse(void(*visit)(const ElemType &)) const  //遍历线性表
{
    for(int position = 1; position <= length; position++)   //循环控制
    {
        (* visit)(this->elems[position-1]);    //对线性表的每个元素调用函数（* visit）
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

//函数名称：StatusCode GetElem(int position, const ElemType &elemType);
//初始条件：线性表已存在, 1<=position<=length
//操作条件：先检查线性表是否已经置空, 如果是空的，返回EMPTY_LIST,
//          然后如果下标position不合法返回NOT_PRESENT,
//          否则用elemType返回线性表第position个元素，返回ENTRY_FOUND
template <class ElemType>
StatusCode SqList<ElemType>::GetElem(int position, ElemType &elemType)  //获取指定位置position的元素
{
//写法Ⅰ
    if(length == 0)
    {
        return NOT_STRUCT;     //线性表为空
    }

    if(position < 0 || position > length)    //如果索引不合法
    {
        return NOT_PRESENT;
    }
    else      //否则索引position是合法的
    {
        elemType = elems[position-1];    //用elemType返回线性表的第position个元素, 该元素下标为position-1

        return ENTRY_FUOND;    //元素存在
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

//函数名称：StatusCode SetElem(int position, const ElemType &elemType);
//初始条件：线性表已存在, 1<=position<=length
//操作条件: 先检查线性表是否已经置空, 如果是空的，返回EMPTY_LIST,
//          然后如果position合法时，将线性表第position个元素修改为elemType，
//          并返回SUCCESS, 否则返回RANGE_ERROR
template <class ElemType>
StatusCode SqList<ElemType>::SetElem(int position, const ElemType &elemType)
{
    if(length = 0)
    {
        return NOT_STRUCT;   //线性表为空
    }

    if(position < 0 || position > length)    //如果索引不合法
    {
        return RANGE_ERROR;   //索引不合法
    }
    else      //否则position合法
    {
        elems[position-1] = elemType;    //将索引对应的数据值修改为elemType
        return SUCCESS;
    }
}

//函数名称：StatusCode Delete(int position);
//初始条件：线性表存在, 1<=position<=length
//操作结果：假如线性表为空，返回EMPTY_LIST,
//          然后如果索引position不合法返回RANGE_ERROR,
//          否则删除当前线性表中索引对应的元素, 并用elemType返回其值, 同时返回SUCCESS
template <class ElemType>
StatusCode SqList<ElemType>::Delete(int position, const ElemType &elemType)   //删除指定位置position的元素
{
    if(length == 0)
    {
        return NOT_STRUCT;      //线性表为空
    }

    if(position < 0 || position > length)
    {
        return RANGE_ERROR;
    }
    else
    {
        ElemType temp;
        elemType = elems[position-1];   //用elemType返回索引position对应的值
        for(int curPosition = position+1; curPosition <= length; curPosition++)  //依次将索引position后面的数据前移一位
        {
            this->GetElem(curPosition, temp);    //保存当前位置的数据
            this->SetElem(curPosition-1, temp);    //将当前的数据插入到前一个位置
        }
        length--;           //删除position的元素后，线性表的元素个数减少1

        return SUCCESS;     //删除成功

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

//函数名称：StatusCode Insert(int position, const ElemType &elemType);
//初始条件：线性表已存在, 1<=position<=length+1
//操作结果：将数据elemType插入线性表的第position个位置
//实现方法: 先检查线性表是否已经置空, 如果是空的，返回EMPTY_LIST,
//          然后如果position合法时，将数据elemType插入线性表的第position个位置
//          并返回SUCCESS, 否则如果检查线性表不合法返回RANGE_ERROR
template <class ElemType>
StatusCode SqList<ElemType>::Insert(int position, const ElemType &elemType)
{
    if(length == 0)
    {
        return NOT_STRUCT;    //线性表是空的
    }

    if(position < 0 || position >length+1)
    {
        return RANGE_ERROR;
    }
    else
    {
        ElemType temp;

        for(int curPosition = length; curPosition >= position; curPosition--)   //将插入目标点以后的数据依次后移
        {
            this->GetElem(position, temp);   //保存当前位置的数据
            this->SetElem(position+1, temp); //将保存的数据添加在
        }
//     //上面的循环等价与
//        for(int curPosition = length+1; curPosition > position; curPosition++)
//        {
//            this->GetElem(position-1, temp);   //保存当前位置的数据
//            this->SetElem(position, temp); //将保存的数据添加在
//        }
       // elems[position-1] = elemType;   //将数据elemType存储到线性表的第position个位置
        this->SetElem(position, elemType);  //同上-将数据elemType存储到线性表的第position个位置

        length++;    //所有操作完成后, 已经插入一个数据, 这时线性表的元素个数进1

        return SUCCESS;     //插入成功
    }
}

//函数名称：StatusCode InList(const ElemType &elemType);
//初始条件：线性表已存在, 且未满，[lenght < maxSize]
//操作条件：首先判断线性表是否已满, 如果满了, 返回FULL_LIST,
//          然后将元素插入在线性表的末尾， 并返回SUCCESS;
template <class ElemType>
StatusCode SqList<ElemType>::InList(const ElemType &elemType)       //将数据elemType插在线性表的末尾
{
    //if(lenth == maxSize)
    if(this->Full() == true)
    {
        return NOT_STRUCT;    //线性表已满
    }

    elems[length] = elemType;   //将数据elemType插在线性表的末尾

    return SUCCESS;
}

/**重载函数声明【实现】***************************************************************************
    SqList<ElemType> &operator=(const SqList<ElemType> &copy);      //赋值运算符重载
    SqList<ElemType> &operator[](const int index);                 //重载下标访问函数
***************************************************************************【实现】重载函数声明**/

//函数名称：SqList<ElemType> &operator=(const SqList<ElemType> &copy);      //赋值运算符重载
//初始条件：被赋值串this和赋值串copy均已存在
//操作结果：将线性表赋值给当前目的线性表
template <class ElemType>
SqList<ElemType> Sqlist<ElemType>::&operator=(const SqList<ElemType> &copy)
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
    StatusCode Swap(int mPosition, int nPosition);//交换线性表第mPosition个元素和第nPosition个元素
    StatusCode BubbleSort(bool minTomax = true);     //冒泡法排序
    StatusCode SelectSort(boolminTomax = true);      //选择法排序
*****************************************************************【实现】特殊函数模版[排序Sort]**/
//函数名称：StatusCode SqList<ElemType>::Swqp(int &mPosition, int &nPosition)
//初始条件：线性表存在, 且mPosition和nPosition满足要求
//操作结果：交换线性表中第mPosition个和第nPosition个元素
template <class ElemType>
StatusCode SqList<ElemType>::Swap(int &mPosition, int &nPosition)
{
    if((mPosition < 0 || mPosition > length)
     || (nPosition < 0 || nPosition > length))
    {
        return NOT_STRUCT;
    }
    ElemType temp;
    temp = elems[mPosition];
    elems[mPosition] = elems[nPosition];
    elems[nPosition] = temp;
}
//StatusCode SqList<ElemType>::Swqp(int mPosition, int nPosition)
//{
//    ElemType temp;
//    temp = elems[mPosition];
//    elems[mPosition] = elems[nPosition];
//    elems[nPosition] = temp;
//}
//StatusCode SqList<ElemType>::Swqp(int *mPosition, int *nPosition)
//{
//    ElemType temp;
//    temp = elems[*mPosition];
//    elems[*mPosition] = elems[*nPosition];
//    elems[*nPosition] = temp;
//}


//函数名称：StatusCode SqList<ElemType>::BubbleSort(bool minTomax = true)
//初始条件：线性表已经存在, 并且不是空串
//操作结果：线性表的数据会由无序变成有序[从小到大OR从大到小]
template <class ElemType>
StatusCode SqList<ElemType>::BubbleSort(bool minTomax/*= true*/)
{
    if(length == 0)
    {
        return NOT_STRUCT;     //对空串不能执行排序操作
    }
    //【冒泡发写法Ⅰ】下面是冒泡法的下沉
    for(int j = 1; j < this->length; j++)     //共计进行lengh-1次比较
    {
        for(int i = 1; i < this->length-j; i++)     //从第一个数开始一直比较到第
        {
            if(((elems[i] > elems[i+1]) && (minTomax == true))    //此时从小到达排序
              || ((elems[i] < elems[i+1]) && (minTomax == false)))   //此时从大到小排序
            {
                this->Swap(i, i+1);   //操作:交换第i个数据和第i+1个数据, 结果：第i个数就下沉一位成为第i+1个数
            }
            //然后i++, 当前就到了第i+1个数[也就是原来第i个数], 然后继续依次往后判断
            //一直到最后最大的数就放在了当前循环最后一个位置, 也就是第length-1-j的位置
        }
    }

    return SUCCESS;


//    //【冒泡发写法Ⅱ】下面是冒泡法的上升
//    for(int j = 1; j < this->length; j++)
//    {
//        for(int i = length; i > j+1; i--)
//        {
//            if(((elems[i] < elems[i-1]) && (minTomax == true))     //此时从小到大
//              || ((elems[i] > elems[i-1]) && (minTomax == false)))  //此时从大到小
//            {
//                this->Swap(i, i-1);     //操作：交换第i个数与第i-1个数, 结果：这时候第i个数就上升了一位, 成为第i-1个数
//
//            }
//            //然后i--, 当前就到了第i个数[也就是原来第i个数], 然后继续依次往后判断
//            //一直到最后最大的数就放在了当前循环最后一个位置, 也就是第length-1-j的位置
//        }
//    }
}


//函数名称：StatusCode SqList<ElemType>::SelectSort(bool minTomax = true)
//初始条件：线性表已经存在, 并且不是空串
//操作结果：线性表的数据会由无序变成有序[从小到大OR从大到小]
template <class ElemType>
StatusCode SqList<ElemType>::SelectSort(bool minTomax/*= true*/)      //选择法排序
{
    if(length == 0)
    {
        return NOT_STRUCT;      //对空串不能执行排序操作
    }
    for(int i = 1; i < this->length; i++)    //循环线性表的每个前数据
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
            this->Swap(k , i);
        }
    }
    return SUCCESS;           // 排序成功
}




#endif // SQLIST_H_INCLUDED


