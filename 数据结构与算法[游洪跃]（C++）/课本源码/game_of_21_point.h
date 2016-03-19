// 文件路径名: game_of_21_point\game_of_21_point.h 
#ifndef __GAME_OF_21_POINT_H__
#define __GAME_OF_21_POINT_H__

#include "card.h"			// 扑克牌

#define LEN_OF_MAX_NAME 21	// 最大姓名长度

// 21点游戏类GameOf21Point声明
class GameOf21Point
{
private:
// 21点游戏类的数据成员:
	Card deck[52];		// 一副扑克牌
	int dealPos;		// 发牌位置
	Card hands[8][21];	// hand[0]存储庄家手中的扑克牌, hand[1~7]存储各位玩家手中的扑克牌
	int numOfCard[8];	// 庄家(numOfCard[0])及玩家(numOfCard[1~7])手中的扑克牌数
	char name[8][LEN_OF_MAX_NAME];	// 庄家与玩家姓名
	int numOfPlayer;	// 玩家人数

// 辅助函数
	void Shuffle();		// 洗牌, 将扑克牌混在一起以便产生一种随机的排列组合
	int GetTotalScore(Card hand[21], int n);// 返回一手扑克牌的总分值
	void ShowStatus(int num, bool hideFirstCardAndTotalScore = false);	
		// 显示庄家(对应num=0)或玩家(对应num>0)的当前状态
	Card DealOneCard();	// 发一张扑克牌

public:
// 21点游戏类方法声明:
	GameOf21Point();			// 无参数的构造函数
	virtual ~GameOf21Point(){};	// 析构函数
	void Game();				// 运行游戏
};

// 21点游戏类GameOf21Point的实现部分
GameOf21Point::GameOf21Point()
// 操作结果：初始化扑克牌,发牌位置,庄家与各玩家手中的扑克牌数
{
	int curPos = 0;				// 当前扑克牌位置		
	for (int suitPos = 0; suitPos < 4; suitPos++)
	{	// 花色
		for (int rankPos = 1; rankPos <= 13; rankPos++)
		{	// 面值
			deck[curPos].suit = (SuitType)suitPos;	// 花色
			deck[curPos].rank = (RankType)rankPos;	// 面值
			curPos++;								// 下一个位置
		}
	}
	cout << "多少人加入游戏?(1~7):"; 
	cin >> numOfPlayer;			// 玩家人数 
	dealPos = 0;				// 发牌位置
	int i;						// 临时变量
	for (i = 0; i <= numOfPlayer; i++) numOfCard[i] = 0;	
		//  庄家(numOfCard[0])及玩家(numOfCard[1~7])手中的扑克牌数
	strcpy(name[0], "庄家");	// 庄家
	for (i = 1; i <= numOfPlayer; i++)
	{	// 玩家姓名
		cout << "输入第" << i << "位玩家的姓名:";
		cin >> name[i];
	}
	cout << "游戏开始" << endl;
}

void GameOf21Point::Shuffle()
// 操作结果：洗牌, 将扑克牌混在一起以便产生一种随机的排列组合
{
	for (int curPos = 51; curPos > 0; curPos--)
	{	// 产生随机的位置为curPos的扑克牌
		int pos = GetRand(curPos + 1);	// 生成0~curPos之间的随机数
		Swap(deck[pos], deck[curPos]);	// 交换deck[pos]与deck[curPos]
	}
}

int GameOf21Point::GetTotalScore(Card hand[21], int n)
// 操作结果：返回一手扑克牌的总分值
{
	int pos;							// 临时变量
	int totalScore = 0;					// 总分值
	for (pos = 0; pos < n; pos++)
	{	// 循环求最大分值(A的分值为11)
		if (hand[pos].rank == ACE) totalScore += 11;	// A的分值为11
		else if (hand[pos].rank > TEN) totalScore += 10;// J,Q,K的分值为10
		else totalScore += (int)hand[pos].rank;			// TWO~TEN的分值为2~10
	}
	
	for (pos = 0; totalScore > 21 && pos < n; pos++)
	{	// 分值大于21时, 将A的分值改为1
		if (hand[pos].rank == ACE) totalScore -= 10;	// A的分值由11分改为1分
	}

	return totalScore;					// 返回总分
}

void GameOf21Point::ShowStatus(int num, bool hideFirstCardAndTotalScore)
// 操作结果：当num=0时,显示庄家当前状态,当num>0时,显示第num个玩家的当前状态,
//	当hideFirstCardAndTotalScore为真时,将隐藏首张扑克牌与总分, 否则将显示
//	首张扑克牌与总分
{
	cout << name[num] << ":";			// 显示庄家或玩家姓名 
	if (hideFirstCardAndTotalScore) cout << " <隐藏>";	// 隐藏首张扑克牌
	else cout << hands[num][0];							// 显示首张扑克牌
	for (int i = 1; i < numOfCard[num]; i++)
		cout << hands[num][i];			// 显示庄家或玩家手中的扑克牌
	if (!hideFirstCardAndTotalScore)
		cout << " 总分值" << GetTotalScore(hands[num], numOfCard[num]); // 显示庄家或玩家总分
	cout << endl;
	if (GetTotalScore(hands[num], numOfCard[num]) > 21)
		cout << name[num] << "引爆!" << endl;
}

Card GameOf21Point::DealOneCard()
// 操作结果：发一张扑克牌
{
	return deck[dealPos++];	
}

void GameOf21Point::Game()
// 操作结果：运行游戏
{
//	SetRandSeed();										// 设置随机数种子
	Shuffle();		// 洗牌, 将扑克牌混在一起以便产生一种随机的排列组合
	int i, j;		// 临时变量

	for (i = 0; i < 2; i++) 
		hands[0][numOfCard[0]++] = DealOneCard();		// 为庄家发两张扑克牌
	ShowStatus(0, true);								// 显示庄家状态,隐藏首张扑克牌与总分
	
	for (i = 1; i <= numOfPlayer; i++)
	{	// 向各玩家发扑克牌,显示各玩家手中的扑克牌
		for (j = 0; j < 2; j++) 
			hands[i][numOfCard[i]++] = DealOneCard();	// 为玩家i发两张扑克牌
		ShowStatus(i);									// 显示玩家i
	}
	cout << endl;

	for (i = 1; i <= numOfPlayer; i++)
	{	// 依次向玩家发额外的牌
		cout << name[i] << ", 你想再要一张牌吗";
		if (UserSaysYes())
		{	// 玩家再要一张牌
			hands[i][numOfCard[i]++] = DealOneCard();	// 为玩家i发1张扑克牌
			ShowStatus(i);								// 显示玩家i
		}
	}	

	ShowStatus(0);										// 显示庄家
	while (GetTotalScore(hands[0], numOfCard[0]) <= 16)
	{	// 庄家总分小于等于16, 必须再拿牌
		hands[0][numOfCard[0]++] = DealOneCard();		// 为庄家发1张扑克牌
		ShowStatus(0);									// 显示庄家
	}
	cout << endl;

	if (GetTotalScore(hands[0], numOfCard[0]) > 21)
	{	// 庄家引爆, 没有引爆的所有入赢
		for (i = 1; i <= numOfPlayer; i++)
		{	// 依次查看每位玩家
			if (GetTotalScore(hands[i], numOfCard[i]) <= 21)	
			{	// 玩家没有引爆
				cout << name[i] << ", 恭喜你, 你赢了!" << endl; 
			}
		}
	}
	else
	{	// 庄家没有引爆
		for (i = 1; i <= numOfPlayer; i++)
		{	// 依次查看每位玩家
			if (GetTotalScore(hands[i], numOfCard[i]) <= 21 &&	// 未引爆
				GetTotalScore(hands[i], numOfCard[i]) > GetTotalScore(hands[0], numOfCard[0]) 
					// 总分比庄家大
				)	
			{	// 玩家未引爆, 且总分比庄家大, 玩家赢
				cout << name[i] << ", 恭喜你, 你赢了!" << endl;
			}
			else if (GetTotalScore(hands[i], numOfCard[i]) == GetTotalScore(hands[0], numOfCard[0]))
			{	// 玩家总分与庄家相等, 平局
				cout << name[i] << ", 唉, 你打平局了!" << endl;
			}
			else
			{	// 玩家引爆或总分比庄家小, 玩家输
				cout << name[i] << ", 对不起, 你输了!" << endl;
			}
		}
	}
}

#endif


