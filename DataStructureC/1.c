#include <stdio.h>
#include <stdlib.h>


// 函数中修改一个变量的值
void Modify1(int value);		// 变量作为参数
void Modify2(int *value);		// 变量指针作为参数

int main(void)
{
	int value = 0;
	Modify1(value);
	printf("value = %d after func\n\n", value);		// modify failed

	Modify2(&value);
	printf("value = %d after func\n\n", value);		// modify success

	return EXIT_SUCCESS;
}


// 变量作为参数
void Modify1(int value)
{
	value = 10;
	printf("value = %d in %s\n", value, __func__);
}

// 变量指针作为参数
void Modify2(int *value)
{
	*value = 10;
	printf("value = %d in %s\n", *value, __func__);
}