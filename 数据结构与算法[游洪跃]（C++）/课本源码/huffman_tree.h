#ifndef __HUFFMAN_TREE_H__
#define __HUFFMAN_TREE_H__

#include "string.h"								// 串类
#include "huffman_tree_node.h"					// 哈夫曼树结点类

// 哈夫曼树类
template <class CharType, class WeightType>
class HuffmanTree
{
protected:
//  哈夫曼树的数据成员:
	HuffmanTreeNode<WeightType> *nodes;			// 存储结点信息,nodes[0]未用
	CharType *LeafChars;						// 叶结点字符信息,LeafChars[0]未用
	String *LeafCharCodes;						// 叶结点字符编码信息,LeafCharCodes[0]未用
	int curPos;									// 译码时从根结点到叶结点路径的当前结点
	int num;									// 叶结点个数

//	辅助函数:
	void Select(int cur, int &r1, int &r2);		// nodes[1 ~ cur]中选择双亲为0,权值最小的两个结点r1,r2
	void CreatHuffmanTree(CharType ch[], WeightType w[], int n);
		// 由字符,权值和字符个数构造哈夫曼树

public:
//  哈夫曼树方法声明及重载编译系统默认方法声明:
	HuffmanTree(CharType ch[], WeightType w[], int n);	// 由字符,权值和字符个数构造哈夫曼树
	virtual ~HuffmanTree();						// 析构函数
	String Encode(CharType ch);					// 编码
	LinkList<CharType> Decode(String strCode);	// 译码
	HuffmanTree(const HuffmanTree<CharType, WeightType> &copy);	// 复制构造函数
	HuffmanTree<CharType, WeightType> &operator=(const HuffmanTree<CharType, 
		WeightType>& copy);						// 赋值运算符重载
};

// 孩子兄弟表示哈夫曼树类的实现部分
template <class CharType, class WeightType>
void HuffmanTree<CharType, WeightType>::Select(int cur, int &r1, int &r2)
// 操作结果：nodes[1 ~ cur]中选择双亲为0,权值最小的两个结点r1,r2
{
	r1 = r2 = 0;								// 0表示空结点
	for (int pos = 1; pos <= cur; pos++)
	{	// 查找树值最小的两个结点
		if (nodes[pos].parent != 0) continue;	// 只处理双亲不为0的结点
		if (r1 == 0)
		{	// r1为空,将pos赋值给r1
			r1 = pos;
		}
		else if (r2 == 0)
		{	// r2为空,将pos赋值给r2
			r2 = pos;
		}
		else if	(nodes[pos].weight < nodes[r1].weight)
		{	// nodes[pos]权值比nodes[r1]更小,将pos赋为r1
			r1 = pos;
		}
		else if (nodes[pos].weight < nodes[r2].weight)
		{	// nodes[pos]权值比nodes[r2]更小,将pos赋为r2
			r2 = pos;
		}
	}
}

template <class CharType, class WeightType>
void HuffmanTree<CharType, WeightType>::CreatHuffmanTree(CharType ch[], WeightType w[], int n)
// 操作结果：由字符,权值和字符个数构造哈夫曼树
{
	num = n;						// 叶结点个数
	int m = 2 * n - 1;				// 结点个数

	nodes = new HuffmanTreeNode<WeightType>[m + 1];	// nodes[0]未用
	LeafChars = new CharType[n + 1];				// LeafChars[0]未用
	LeafCharCodes = new String[n + 1];				// LeafCharCodes[0]未用

	int pos;										// 临时变量 
	for (pos = 1; pos <= n; pos++)
	{	// 存储叶结点信息
		nodes[pos].weight = w[pos - 1];				// 权值
		LeafChars[pos] = ch[pos - 1];				// 字符
	}

	for (pos = n + 1; pos <= m; pos++)
	{	// 建立哈夫曼树
		int r1, r2;
		Select(pos - 1, r1, r2);	// nodes[1 ~ pos - 1]中选择双亲为0,权值最小的两个结点r1,r2

		// 合并以r1,r2为根的树
		nodes[r1].parent = nodes[r2].parent = pos;	// r1,r2双亲为pos
		nodes[pos].leftChild = r1;					// r1为pos的左孩子
		nodes[pos].rightChild = r2;					// r2为pos的右孩子
		nodes[pos].weight = nodes[r1].weight + nodes[r2].weight;//pos的权为r1,r2的权值之和
	}

	for (pos = 1; pos <= n; pos++)
	{	// 求n个叶结点字符的编码
		LinkList<char> charCode;			// 暂存叶结点字符编码信息
		for (unsigned int child = pos, parent = nodes[child].parent; parent != 0; 
			child = parent, parent = nodes[child].parent)
		{	// 从叶结点到根结点逆向求编码
			if (nodes[parent].leftChild == child) charCode.Insert(1, '0');// 左分支编码为'0'
			else charCode.Insert(1, '1');	// 右分支编码为'1'
		}
		LeafCharCodes[pos] = charCode;		// charCode中存储字符编码
	}
	
	curPos = m;								// 译码时从根结点开始,m为根
}


template <class CharType, class WeightType>
HuffmanTree<CharType, WeightType>::HuffmanTree(CharType ch[], WeightType w[], int n)
// 操作结果：由字符,权值和字符个数构造哈夫曼树
{
	CreatHuffmanTree(ch, w, n);				// 由字符,权值和字符个数构造哈夫曼树
}

template <class CharType, class WeightType>
HuffmanTree<CharType, WeightType>::~HuffmanTree()
// 操作结果：销毁哈夫曼树
{	
	if (nodes != NULL) delete []nodes;					// 释放结点信息
	if (LeafChars != NULL) delete []LeafChars;			// 释放叶结点字符信息
	if (LeafCharCodes != NULL) delete []LeafCharCodes;	// 释放叶结点字符编码信息
}

template <class CharType, class WeightType>
String HuffmanTree<CharType, WeightType>::Encode(CharType ch)
// 操作结果：返回字符编码
{
	for (int pos = 1; pos <= num; pos++)
	{	// 查找字符的位置
		if (LeafChars[pos] == ch) return LeafCharCodes[pos];// 找到字符,得到编码
	}
	throw Error("非法字符,无法编码!");					// 抛出异常
}

template <class CharType, class WeightType>
LinkList<CharType> HuffmanTree<CharType, WeightType>::Decode(String strCode)
// 操作结果：对编码串strCode进行译码,返回编码前的字符序列
{
	LinkList<CharType> charList;						// 编码前的字符序列
	
	for (int pos = 0; pos < strCode.Length(); pos++)
	{	// 处理每位编码
		if (strCode[pos] == '0') curPos = nodes[curPos].leftChild;	// '0'表示左分支	
		else curPos = nodes[curPos].rightChild;			// '1'表示左分支	

		if (nodes[curPos].leftChild == 0 && nodes[curPos].rightChild == 0)
		{	// 译码时从根结点到叶结点路径的当前结点为叶结点
			charList.Insert(charList.Length() + 1, LeafChars[curPos]);
			curPos = 2 * num - 1;						// curPos回归根结点
		}
	}
	return charList;									// 返回编码前的字符序列
}

template <class CharType, class WeightType>
HuffmanTree<CharType, WeightType>::HuffmanTree(const HuffmanTree<CharType, WeightType> &copy)
// 操作结果：由哈夫曼树copy构造新哈夫曼树——复制构造函数
{
	num = copy.num;									// 叶结点个数
	curPos = copy.curPos;							// 译码时从根结点到叶结点路径的当前结点
	int m = 2 * num - 1;							// 结点总数 
	nodes = new HuffmanTreeNode<WeightType>[m + 1];	// nodes[0]未用
	LeafChars = new CharType[num + 1];				// LeafChars[0]未用
	LeafCharCodes = new String[num + 1];			// LeafCharCodes[0]未用

	int pos;										// 临时变量 
	for (pos = 1; pos <= m; pos++)
	{	// 复制结点信息
		nodes[pos] = copy.nodes[pos];				// 结点信息
	}
	
	for (pos = 1; pos <= num; pos++)
	{	// 复制叶结点字符信息与叶结点字符编码信息
		LeafChars[pos] = copy.LeafChars[pos];		// 叶结点字符信息
		LeafCharCodes[pos] = copy.LeafCharCodes[pos];// 叶结点字符编码信息
	}
}

template <class CharType, class WeightType>
HuffmanTree<CharType, WeightType> &HuffmanTree<CharType, WeightType>::operator=(const HuffmanTree<CharType, WeightType>& copy)	
// 操作结果：将哈夫曼树copy赋值给当前哈夫曼树——赋值运算符重载
{
	if (&copy != this)
	{
		if (nodes != NULL) delete []nodes;					// 释放结点信息
		if (LeafChars != NULL) delete []LeafChars;			// 释放叶结点字符信息
		if (LeafCharCodes != NULL) delete []LeafCharCodes;	// 释放叶结点字符编码信息

		num = copy.num;						// 叶结点个数
		curPos = copy.curPos;				// 译码时从根结点到叶结点路径的当前结点
		int m = 2 * num - 1;				// 结点总数 
		nodes = new HuffmanTreeNode<WeightType>[m + 1];	// nodes[0]未用
		LeafChars = new CharType[num + 1];				// LeafChars[0]未用
		LeafCharCodes = new String[num + 1];			// LeafCharCodes[0]未用

		int pos;										// 临时变量 
		for (pos = 1; pos <= m; pos++)
		{	// 复制结点信息
			nodes[pos] = copy.nodes[pos];				// 结点信息
		}
		
		for (pos = 1; pos <= num; pos++)
		{	// 复制叶结点字符信息与叶结点字符编码信息
			LeafChars[pos] = copy.LeafChars[pos];		// 叶结点字符信息
			LeafCharCodes[pos] = copy.LeafCharCodes[pos];// 叶结点字符编码信息
		}	
	}
	return *this;
}

#endif
