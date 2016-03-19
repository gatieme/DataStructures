#ifndef __FACTORIAL_H__
#define __FACTORIAL_H__

// 阶乘算法

// 文件路径名:power\power.h 
CLargeInt Power(const CLargeInt &base,	const CLargeInt &exp)
// 操作结果: 计算大非负整数数的大非负整数数次方
{
	CLargeInt tmpLargInt(1);
	for (int i = 0; i < exp; i = i + 1)
	{	// 连乘求大非负整数数的大非负整数数次方
		tmpLargInt = tmpLargInt * base;
	}

	return tmpLargInt;
}

#endif
