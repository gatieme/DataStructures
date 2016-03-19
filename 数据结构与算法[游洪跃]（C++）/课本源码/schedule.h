// 文件路径名:my_huffman_tree\my_huffman_tree.h
#ifndef __SCHEDULE_H__
#define __SCHEDULE_H__

#include "adj_list_dir_graph.h"		// 有向图类
#include "lk_queue.h"				// 链队列类
#include "string.h"					// 串类

// 课程结构
struct CourseType 
{
	char courseNo[5];				// 课程编号
	char courseName[100];			// 课程名
    int period;						// 学时数
    int term;						// 开课学期
};	

// 课程表类
template<int termsNum>				// termsNum表示要排课的学期数
class Schedule
{
private:
// 课程表类的数据成员:
	AdjListDirGraph<CourseType> *pGraph;	// 由课程信息所建立的图 
	int *indegree;							// 顶点入度
	ifstream *pInFile;						// 输入流 
    ofstream *pOutFile;						// 输出流
	LinkQueue<int> q[termsNum + 1];			// 入度为0的结点的缓冲队列
	char courseTable[termsNum + 1][11][6][100];
		// 课表,下标分别表示：学期、节次、星期、课程名
    int coursesNumOfPerTerm[termsNum + 1];	// 每学期的课程数

// 辅助函数:
	int LocateVex(char courseNo[]);			// 返回编号为courseNo的课程在图的位置
	void Readln();							// 跳过一行  
	void Range(int num, int term, char courseName[]);			// 排课
	bool RangeOne(int &weekDay, int term, char courseName[]);	// 排一天的1节课
	bool RangeTwo(int &weekDay, int term, char courseName[]);	// 排一天的2节课
	bool RangeThree(int &weekDay, int term, char courseName[]);	// 排一天的3节课
	int FindOne(int weekDay, int term);		// 查找一天1节空课
	int FindTwo(int weekDay, int term);		// 查找一天连续2节空课
	int FindThree(int weekDay, int term);	// 查找一天连续3节空课
	void Write(char s[], int l);			// 输出指定长度的字符串 
	char *DecimalToChineseChar(int n, char *s);		// 用中文表示十进制数

public:
// 抽象数据类型方法声明及重载编译系统默认方法声明:
	Schedule(ifstream *pIFile, ofstream *pOFile);	// 构造函数
	virtual ~Schedule();			// 析构函数
	void Read();					// 从输入流中输入有关信息，以建立一个有向图
	void TopologicalOrder();		// 用拓扑排序方式进行排课
	void Write();					// 输出课表信息 
};

// 课程表类的实现部分
template<int termsNum> 
int Schedule<termsNum>::LocateVex(char courseNo[])
// 操作结果：返回编号为courseNo的课程在图的位置
{
	for (int v = 0; v < pGraph->GetVexNum(); v++)
	{	// 依次查找课程
		CourseType course;			// 临时变量
		pGraph->GetElem(v, course);	// 返回顶点(课程)信息
		if (strcmp(course.courseNo, courseNo) == 0)
		{	// 查找成功
			return v;						// 非负表示查找成功
		}
	}
	
	return -1;								// -1表示查找失败
}

template<int termsNum> 
void Schedule<termsNum>::Readln()
// 操作结果：跳过一行
{	
	char ch;								// 字符
	while ((ch = (*pInFile).peek()) != EOF	// 不为文件结束符
		&& (ch = (*pInFile).get()) != '\n');// 不为换行符
}

template<int termsNum> 
Schedule<termsNum>::Schedule(ifstream *pIFile, ofstream *pOFile)
// 操作结果: 初始化输入文件与输出文件,排课开始的星期几, 清空课表
{
	pInFile = pIFile;						// 输入文件
	pOutFile = pOFile;						// 输出文件
	pGraph = NULL;							// 初始化pGraph为空
	indegree = NULL;							// 初始化indegree为空

	for (int i = 1; i <= termsNum; i++)
	{	// 学期数
		for (int j = 1; j <= 10; j++)
		{	// 节次
			for (int k = 1; k <= 5; k++)
			{	// 星期   
				strcpy(courseTable[i][j][k], "");	// 清空课表
			}
		}
	}
}

template<int termsNum> 
Schedule<termsNum>::~Schedule()
// 操作结果: 释放存储空间
{
	if (pGraph != NULL) delete pGraph;		// 释放pGraph
	if (indegree != NULL) delete []indegree;// 释放indegree
}

template<int termsNum> 
void Schedule<termsNum>::Range(int num, int term, char courseName[])
// 操作结果: 排课, num为要排课的节数, term为学期, courseName为课程名
{
	static int weekDay=1;					// 要排课的星期
	int i;									// 临时变量
	if (num == 1)
	{	// 对1节课进行排课
		if (!RangeOne(weekDay, term, courseName))
		{	// 排课失败
			throw Error("排课失败!");		// 抛出异常
		}
	}
	else if (num % 3 == 0)
	{	// 排课节数为3的位数
		for ( i =0; i < num / 3; i++)
		{
			if (!RangeThree(weekDay, term, courseName))
			{	// 排课失败
				throw Error("排课失败!");	// 抛出异常
			}
		}
	}
	else if (num % 3 == 1)
	{	// 排课节数被3除余1
		for (i = 0; i < num / 3 - 1; i++)
		{
			if (!RangeThree(weekDay, term, courseName))
			{	// 排课失败
				throw Error("排课失败!");	// 抛出异常
			}
		}
		for (i = 0; i < 2; i++)
		{
			if (!RangeTwo(weekDay, term, courseName))
			{	// 排课失败
				throw Error("排课失败!");	// 抛出异常
			}
		}
	}
	else
	{	// 排课节数被3除余2
		for (i = 0; i < num / 3; i++)
		{
			if (!RangeThree(weekDay, term, courseName))
			{	// 排课失败
				throw Error("排课失败!");	// 抛出异常;
			}
		}
		if (!RangeTwo(weekDay, term, courseName))
		{	// 排课失败
			throw Error("排课失败!");		// 抛出异常
		}
	}
}

template<int termsNum> 
bool Schedule<termsNum>::RangeOne(int &weekDay, int term, char courseName[])
// 操作结果：排一天的1节课
{	
	for(int k = 1; k <= 5; k++)
	{	// 对一个星期的5个工作日进行排课
		int i = FindOne(weekDay,term);			// 查找一天1节空课
		if (i == -1)
		{	// 查找失败
			weekDay = (weekDay +2 > 5) ? (weekDay + 2 - 5) : (weekDay + 2);	
				// 下一次要排课的星期
		}
		else
		{	// 查找成功
			strcpy(courseTable[term][i][weekDay], courseName);	
				// 表示将课程courseName排在第i节课
			return true;						// 排课成功
		}
	}
	return false;								// 排课失败
}


template<int termsNum> 
bool Schedule<termsNum>::RangeTwo(int &weekDay, int term, char courseName[])
// 操作结果：排一天的2节课
{
	for (int k = 1; k <= 5; k++)
	{	// 对一个星期的5个工作日进行排课
		int i = FindTwo(weekDay, term);			// 查找连续2节课空课
		if (i != -1)
		{	// 查找成功
			weekDay = (weekDay +2 > 5) ? (weekDay + 2 - 5) : (weekDay + 2);	
				// 下一次要排课的星期
			strcpy(courseTable[term][i][weekDay], courseName);
				// 表示将课程courseName排在第i节课
			strcpy(courseTable[term][i + 1][weekDay], courseName);
				// 表示将课程courseName排在第i+1节课
			return true;						// 排课成功
		}
	}
	
	// 将2节连续上的课分解为两个单独上的1节课
	if (!RangeOne(weekDay, term, courseName)) return false;
	if (!RangeOne(weekDay, term, courseName)) return false;
	return true;								// 排课成功
}

template<int termsNum> 
bool Schedule<termsNum>::RangeThree(int &weekDay, int term, char courseName[])
// 操作结果：排一天的3节课
{
	for (int k = 0; k <= 5; k++)
	{	// 对一个星期的5个工作日进行排课
		int i = FindThree(weekDay, term);	// 查找连续2节课空课
		if (i != -1)
		{	// 查找成功
			weekDay = (weekDay +2 > 5) ? (weekDay + 2 - 5) : (weekDay + 2);	
				// 下一次要排课的星期
			strcpy(courseTable[term][i][weekDay], courseName);
				// 表示将课程courseName排在第i节课
			strcpy(courseTable[term][i + 1][weekDay], courseName);
				// 表示将课程courseName排在第i+1节课
			strcpy(courseTable[term][i + 2][weekDay], courseName);
				// 表示将课程courseName排在第i+2节课
			return true;					// 排课成功
		}
	}
	// 将3节连续上的课分解为2节连续上的课与单独上的1节课
	if (!RangeTwo(weekDay,term,courseName)) return false;
	if (!RangeOne(weekDay,term,courseName)) return false;
	return true;							// 排课成功
}

template<int termsNum> 
int Schedule<termsNum>::FindOne(int weekDay, int term)
// 操作结果：查找一天1节空课,返回有空的节次，返回-1表示课已排满
{
	for(int i = 1; i <= 8; i++)
	{	// 表示第term学期,星期weekDay的第i节课
		if (strlen(courseTable[term][i][weekDay]) == 0)
		{	// 表示第term学期,星期weekDay的第i节课未排
			return i;						// 返回i
		}
	}
	return -1;								// 表示课已排满	
}

template<int termsNum> 
int Schedule<termsNum>::FindTwo(int weekDay,int term)
// 操作结果：查找一天连续2节空课,返回连续2节课有空的第1节课的节次，返回-1表示失败
{
	if (strlen(courseTable[term][1][weekDay]) ==0 && strlen(courseTable[term][2][weekDay]) ==0 )
	{	// 检查第1大节是否有空
		return 1;							// 第1大节是否有空
	}
	if (strlen(courseTable[term][3][weekDay]) == 0 && strlen(courseTable[term][4][weekDay]) == 0)
	{	// 检查第2大节是否有空	
		return 3;							// 第2大节是否有空
	}
	if (strlen(courseTable[term][6][weekDay]) == 0 && strlen(courseTable[term][7][weekDay]) == 0)
	{	// 检查第3大节是否有空
		return 6;							// 查第3大节是否有空
	}
	if (strlen(courseTable[term][8][weekDay]) == 0 && strlen(courseTable[term][9][weekDay]) == 0)
	{	// 检查第4大节是否有空
		return 8;							// 第4大节是否有空
	}
	return -1;								// 表示失败
}


template<int termsNum> 
int Schedule<termsNum>::FindThree(int weekDay,int term)
// 操作结果：查找一天连续3节空课,返回连续3节课有空的第1节课的节次，返回-1表示失败
{
	if (strlen(courseTable[term][3][weekDay]) == 0 && strlen(courseTable[term][4][weekDay]) == 0 && strlen(courseTable[term][5][weekDay]) == 0)
	{	// 检查第2大节是否有空
		return 3;							// 第2大节是否有空
	}
	if (strlen(courseTable[term][8][weekDay]) == 0 && strlen(courseTable[term][9][weekDay]) == 0 && strlen(courseTable[term][10][weekDay]) == 0)
	{	// 检查第3大节是否有空
		return 8;							// 第3大节是否有空
	}
	return -1;								// 表示失败
}


template<int termsNum> 
void Schedule<termsNum>::Write(char s[], int l)
// 操作结果：输出指定长度的字符串(假设s长度小于等于l)
{
	(*pOutFile) << s;						// 输出s
	for(unsigned int i = 0; i < l - strlen(s); i++) (*pOutFile) << " ";
		// 输入空格, 使其输出宽度为l
}

template<int termsNum> 
char *Schedule<termsNum>::DecimalToChineseChar(int n, char *s)
// 操作结果：用中文表示十进制数 
{	
	char digital[11][3] = {"〇", "一", "二", "三", "四", "五", "六", "七", 
		"八", "九", "十"};					// 中文表示的十进制数字

	strcpy(s, "");							// 将s赋为空串= '\0'
	if (n < 0)
	{	// n为负
		strcat(s, "负");					// 以串s以"负"表始
		n = -n;								// 去掉n的负号
	}
	n = n % 100;							// 假设n最多是一个两位数
	if (n / 10 > 1)
	{	// 十位数大于1
		strcat(s, digital[n / 10]);			// 将十位数的中文表示连到s的后面
		strcat(s, digital[10]);				// 在s后面接"十"
		if (n %10 >0)
		{	// 个位数非0
			strcat(s, digital[n % 10]);		// 将个位数的中文表示连到s的后面
		}
	}
	else if (n /10 == 1)
	{	// 十位数为1
		strcat(s, digital[10]);				// 将s后面接"十"
		if (n %10 >0)
		{	// 个位数非0
			strcat(s, digital[n % 10]);		// 将个位数的中文表示连到s的后面
		}
	}
	else
	{	// 十位数为0
		strcpy(s, digital[n % 10]);			// 将个位数的中文表示连到s的后面
	}

	return s;
}

template<int termsNum> 
void Schedule<termsNum>::Read()
// 操作结果：从输入流中输入有关信息，以建立一个有向图
{ 
	char ch;									// 字符
	int i, n, v, u;								// 临时变量
	int courseTotalNum = 0;						// 课程总数
	CourseType course;							// 课程信息
	char prioCourseNo[5];						// 先决课程号

	//下面为从输入流中输入各学期所开的课程数
	(*pInFile).seekg(0);						// 定位到文件开始处
	ch = GetChar(*pInFile);						// 读字符
	while (ch < '0' || ch > '9')
	{	// 查找数字开始的行
		if (ch != '\n') Readln();				// 跳行
		ch = GetChar(*pInFile);					// 读入字符
	}
	(*pInFile).putback(ch);						// 将ch回送输入流
	for (i = 1; i <= termsNum; i++)
	{	// 查找每学期所开设的课程数
		(*pInFile) >> n;						// 课程数
		coursesNumOfPerTerm[i] = n;				// 第i学期所开设的课程数
		courseTotalNum += n;				 	// 累加求总课程数
	}

	CourseType *vex = new CourseType[courseTotalNum];		// 图的顶点信息
	indegree = new int[courseTotalNum];						// 图的顶点入度
	for (i = 0; i < courseTotalNum; i++) indegree[i] = 0;	// 初始化顶点入度
	
	// 下面为从输入流中输入各课程信息(建立图的顶点信息)
	(*pInFile).seekg(0);						// 定位到文件开始处
	ch = GetChar(*pInFile);						// 读字符
	int count = 0;								// 顶点数
	while (ch != EOF)
	{	// 文件束结束
		while (ch != EOF && ch != 'c')
		{	// 查找以'c'开始的行
			if(ch != '\n') Readln();			// 跳过不以'c'开始的行
			ch = GetChar(*pInFile);				// 读字符
		}
		if (ch != EOF)
		{	// 处理以'c'开始的行
			(*pInFile).putback(ch);				// 将ch回送回输入流
			(*pInFile) >> course.courseNo;		// 读入课程号
			(*pInFile) >> course.courseName;	// 读入姓名
			(*pInFile) >> course.period;		// 读入学时数
			(*pInFile) >> course.term;			// 读入学期

			vex[count++] = course;					// 将课程信息存入vex
			Readln();							// 换行
		}
		ch = GetChar(*pInFile);					// 读入字符
	}
	if (count != courseTotalNum) throw Error("课程数与设置的课程总数不等!");	// 抛出异常
	pGraph = new AdjListDirGraph<CourseType>(vex, courseTotalNum);	// 生成图pGraph

	// 下面为从输入流中输入各课程先修课程信息(建立图的边信息)
	(*pInFile).seekg(0);
	ch = GetChar(*pInFile);
	while (ch != EOF)
	{	// 文件束结束
		while (ch != EOF && ch != 'c')
		{	//查找以'c'开始的行
			if (ch != '\n') Readln();			// 跳行
			ch = GetChar(*pInFile);				// 读入字符
		}
		if (ch != EOF)
		{	// 处理以'c'开始的行
			(*pInFile).putback(ch);				// 将ch回送回输入流
			(*pInFile) >> course.courseNo;		// 读入课程号
			(*pInFile) >> course.courseName;	// 读入姓名
			(*pInFile) >> course.period;		// 读入学时数
			(*pInFile) >> course.term;			// 读入学期	
			v = LocateVex(course.courseNo);		// 查找顶点的位置
			if (v == -1) throw Error("非法顶点!");	// 抛出异常
  
			ch = GetChar(*pInFile);				// 读入字符
			while (ch == 'c')
			{	// 先修课号
				(*pInFile).putback(ch);			// 将ch回送回输入流
				(*pInFile) >> prioCourseNo;		// 读入课程号
				u = LocateVex(prioCourseNo);	// 查找顶点的位置
				if (u == -1)  throw Error("非法先修课号!");	// 抛出异常
				pGraph->InsertEdge(u, v);		// 插入边<u,v>
				indegree[v]++;					// 顶点v入度加1  
				ch = GetChar(*pInFile);
			}
		}
		if (ch != '\n') Readln();				// 跳过当前行
		ch = GetChar(*pInFile);					// 读入字符
	}
}

template<int termsNum> 
void Schedule<termsNum>::TopologicalOrder()
// 操作结果：用拓扑排序方式进行排课
{
	CourseType courseV, courseW;				// 顶点相应课程信息
	int i, size0, sizeTerm, term, v, w;			// 临时变量		
	for (v = 0; v < pGraph->GetVexNum(); v++)
	{	// 建立入度为0顶点的队列q[0..termsNum]	
		if (indegree[v] == 0)   
		{	// 入度为0者进入相应学期的队列
			pGraph->GetElem(v, courseV);		// 取出顶点v的数据信息
			q[courseV.term].InQueue(v);
		}
	}

	//生成课表
	for (term = 1; term <= termsNum; term++)
	{	// 第term学期
		size0 = q[0].Length();					// 无特别要求在哪学期开课的课程
		sizeTerm = q[term].Length();			// 要求在第term学期开课的课程
		

		if (size0 + sizeTerm < coursesNumOfPerTerm[term] || sizeTerm > coursesNumOfPerTerm[term])
		{	// 表示排课时出现冲突
		cout << "term:" << term << endl;
		cout << "size0:" << size0 << endl;
		cout << "sizeTerm:" << sizeTerm << endl;
		cout << "coursesNumOfPerTerm[term]:" << coursesNumOfPerTerm[term] << endl << endl;

		throw Error("排课时出现冲突!");			// 抛出异常
		}
		for (i = 1; i <= sizeTerm; i++)
		{	// 排要求第term学期开的课程
			q[term].OutQueue(v);				// 出队
			pGraph->GetElem(v, courseV);		// 取出顶点v的数据信息
			Range(courseV.period, term, courseV.courseName);	// 排课
			for (w = pGraph->FirstAdjVex(v); w != -1; w = pGraph->NextAdjVex(v, w))
			{	// w为v的邻接点
				indegree[w]--;					// w的入度自减1
				pGraph->GetElem(w, courseW);	// 取出顶点w的数据信息
				if (indegree[w] == 0 && (courseW.term == 0 || courseW.term > term))
				{	// 顶点w入度为0 
					q[courseW.term].InQueue(w);	// w入相应队列
				}
				else if (indegree[w] == 0 && (courseW.term > 0 && courseW.term <= term))
				{	// 表示排课时出现冲突
					throw Error("排课时出现冲突!");		// 抛出异常
				}
			}
		}
		for (i = 1; i <= coursesNumOfPerTerm[term] - sizeTerm; i++)
		{	// 排无特别要求在哪学期开课的课程
			q[0].OutQueue(v);					// 出队
			pGraph->GetElem(v, courseV);		// 取出顶点v的数据信息
			Range(courseV.period,term,courseV.courseName);
			for (w = pGraph->FirstAdjVex(v); w != -1; w = pGraph->NextAdjVex(v, w))
			{	// w为v的邻接点
				indegree[w]--;					// w的入度自减1
				pGraph->GetElem(w, courseW);	// 取出顶点w的数据信息
				if (indegree[w] == 0 && (courseW.term == 0 || courseW.term > term))
				{	// 顶点w入度为0 
					q[courseW.term].InQueue(w);	// w入相应队列
				}
				else if (indegree[w] == 0 && (courseW.term > 0 && courseW.term <= term))
				{	// 表示排课时出现冲突
					throw Error("排课时出现冲突!");		// 抛出异常
				}
			}
		}
	}
}

template<int termsNum> 
void Schedule<termsNum>::Write()
// 操作结果：输出课表信息
{
	int term, i, weekDay;					// 临时变量
	char s[20], strTem[20];					// 临时变量
	for (term = 1; term <= termsNum; term++)
	{	// 输出第term学期课程表
		(*pOutFile) << "第" << DecimalToChineseChar(term, strTem) << "学期课表" << endl;	// 输出表头
		(*pOutFile) << endl;				// 换行
		
		//显示标题
		Write("节次", 8);
		for (i = 1; i <= 5; i++)
		{	// 星期1~星期5
			DecimalToChineseChar(i, strTem);				// 将数字变为中文
			Write(strcat(strcpy(s, "星期"), strTem), 16);	// 输出星期i
		}
		(*pOutFile) << endl << endl;		// 换行
		
		// 显示课程表内容
		for (i = 1; i <= 10; i++)
		{	// 显第第1节到第10节课
			DecimalToChineseChar(i, strTem);				// 将数字变为中文
			Write(strcat(strcat(strcpy(s, "第"), strTem), "节"), 8);	// 输出第i节
			for (weekDay = 1; weekDay <= 5; weekDay++)
			{	// 显示课程
				Write(courseTable[term][i][weekDay], 16);	// 第term学期,星期weekDay,第i节课课程名
			}
			(*pOutFile)<<endl;				// 换行

			if (i==2 || i == 7)
			{	// 第1大节与第3大节后的课间休息
				(*pOutFile) << endl << "课间休息" << endl << endl;
			}
			if (i == 5)
			{	// 第2大节后的午间休息
				(*pOutFile) << endl << endl << "午间休息" << endl << endl << endl;
			}
			if (i == 10)
			{	// 第4大节后的晚自习
				(*pOutFile) << endl << "晚自习" << endl << endl;
			}
		}

		(*pOutFile) << endl << endl << endl;
			// 各课表之间以较多空行相隔
	}
}

#endif