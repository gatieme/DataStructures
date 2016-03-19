// 文件路径名: queen\queen.h
#ifndef __QUEEN_H__
#define __QUEEN_H__

// 皇后问题算法

void BackTrack(int c, int n, bool row[], bool diag[], bool backDiag[], int x[]);	// 回溯求解n皇后问题
void OutSolution(int n, int x[]);// 输出一组解 

void Queen(int n)
// 操作结果: 求解n皇后问题
{
	bool *row = new bool[n + 1];				// 行是否有皇后
	bool *diag = new bool[2 * n];				// 主对角线是否有皇后
	bool *backDiag = new bool[2 * n];			// 反对角线是否有皇后
	int *x = new int[n + 1];					// n皇后问题的解
	int i;										// 临时变量

	// 赋初值
	for (i = 1; i <= n; i++) row[i] = false;
	for (i = 1; i < 2 * n; i++) diag[i] = false;
	for (i = 1; i < 2 * n; i++) backDiag[i] = false;

	BackTrack(1, n, row, diag, backDiag, x);					// 递归求解n皇后问题

	delete []row; delete []diag; delete []backDiag;	delete []x;	// 释放存储空间
}

void BackTrack(int c, int n, bool row[], bool diag[], bool backDiag[], int x[])
// 操作结果: 前i-1个皇后已放置后，为第i个皇后选择合适的位置，row[]用于表示某行
//	是否放置有皇后，backDiag[]表示某条副对角线是否放置有皇后，diag[]表示某条主
//	对角线是否放置有皇后,x[]表示皇后所放置的行
{
	int r;
	if (c > n)
	{	// c>n表示第1~n个皇后已放置好
		OutSolution(n, x);	// 已得到解,输出解
	}
	else
	{
		for (r = 1; r <= n; r++)	
		{	// 第c个皇后所放置的行
			if(!row[r] && !diag[n - c + r] && !backDiag[r + c - 1])
			{	// 位置(r,c)所在的行，对角线没放置有皇后,
				// 则在位置(r, c)放置第c个皇后
				row[r] = diag[n - c + r] = backDiag[r + c - 1] = true;	// 表示位置(r, c)已有皇后
				x[c] = r;					// 表示第c个皇后所放置的行
				BackTrack(c + 1, n, row, diag, backDiag, x);	// 试探第c + 1个皇后所放置的位置
				row[r] = diag[n - c + r] = backDiag[r + c - 1] = false; // 释放位置(r,c)，进行回溯
			}
		}
	}
}

void OutSolution(int n, int x[])
//操作结果: 输出皇后问题的解
{
	int static num = 0;		// num表示当前已求得解的个数
	
	cout << "第" << ++num << "个解:";
	for(int c = 1; c <= n; c++)
	{	// 输出解
		cout << "(" << x[c] << "," << c << ") ";
	}
	cout << endl;
}

#endif