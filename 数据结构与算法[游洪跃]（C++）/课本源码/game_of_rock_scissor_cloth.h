// 文件路径名: game_of_rock_scissor_cloth\game_of_rock_scissor_cloth.h 
#ifndef __GAME_OF_ROCK_SCISSOR_CLOTH_H__
#define __GAME_OF_ROCK_SCISSOR_CLOTH_H__

typedef enum 
{	// 选手可供的选择: ROCK(石头),SCISSOR(剪刀),CLOTH(布),DISPLAY(显示),HELP(帮助)
	// 和QUIT(退出)
	ROCK, SCISSOR, CLOTH, DISPLAY, HELP, QUIT
} SelectType;

typedef enum 
{	// 胜负结果：WIN(胜),LOSE(负)和TIE(平)
	WIN, LOSE, TIE
} ResultType;		

// 石头、剪刀、布游戏类GameOfRockScissorCloth声明
class GameOfRockScissorCloth
{
private:
// 石头、剪刀、布游戏类的数据成员:
	int winCount;								// 真人选手获胜次数
	int loseCount;								// 真人选手失败次数
	int tieCount;								// 真人选手平局次数

// 辅助函数
	ResultType Compare(SelectType playerChoice, SelectType computerChoice); // 比较决定胜负
	void DisplayFinalStatus();					// 显示游戏最后状态
	void DisplayGameStatus();					// 显示游戏状态
	void DisplayHelp();							// 显示帮助信息
	void Report(ResultType result);				// 报告比赛结果，并统计获胜、失败和平局次数
	SelectType SelectByMachine();				// 电脑选手做选择
	SelectType SelectByPlayer();				// 真人选手做选择

public:
// 石头、剪刀、布游戏类方法声明:
	GameOfRockScissorCloth();					// 无参数的构造函数
	virtual ~GameOfRockScissorCloth(){};		// 析构函数
	void Game();								// 运行游戏
};

// 石头、剪刀、布游戏类GameOfRockScissorCloth的实现部分
GameOfRockScissorCloth::GameOfRockScissorCloth()
// 操作结果：初始化数据成员
{
	winCount = 0;								// 真人选手获胜次数
	loseCount = 0;								// 真人选手失败次数
	tieCount = 0;								// 真人选手平局次数
}

ResultType GameOfRockScissorCloth::Compare(SelectType playerChoice, SelectType computerChoice)
// 操作结果：比较决定真人选手的获胜、败失或平局
{
	ResultType result;

	if (playerChoice == computerChoice)
	{	// 选择相同表示平局
		return TIE;
	}

	switch (playerChoice)
	{
	case ROCK:		// 真人选手选择石头
		result = (computerChoice == SCISSOR) ? WIN : LOSE;	// 根据电脑选手的选择得到比较结果
		break;
	case SCISSOR:	// 真人选手选择剪刀
		result = (computerChoice == CLOTH) ? WIN : LOSE;	// 根据电脑选手的选择得到比较结果
		break;
	case CLOTH:		// 真人选手选择布
		result = (computerChoice == ROCK) ? WIN : LOSE;		// 根据电脑选手的选择得到比较结果
		break;
	}

	return result;
}

void GameOfRockScissorCloth::DisplayFinalStatus()
// 操作结果：显示游戏最后状态
{
	if (winCount > loseCount)
	{	// 真人选手获胜次数更多
		cout << "祝贺你，你取得最终胜利了!" << endl << endl;
	}
	else if (winCount < loseCount)
	{	// 真人选手失败次数更多
		cout << "不要失去信心啊，只要努力，将来胜利一定属于你!" << endl << endl;
	}
	else
	{	// 真人选手获胜次数和失败次数相同
		cout << "还不错啊，虽然最终平手，但也没失败啊!" << endl << endl;
	}
}

void GameOfRockScissorCloth::DisplayGameStatus()
// 操作结果：显示游戏状态
{
	cout << "游戏状态:" << endl;
	cout << "获胜次数:" << winCount << endl;
	cout << "失败次数:" << loseCount << endl;
	cout << "平局次数:" << tieCount << endl;
}

void GameOfRockScissorCloth::DisplayHelp()
// 操作结果：显示帮助信息
{
	cout << "下面是选手可供输入的字符:" << endl;
	cout << "  r	表示选择石头(rock)" << endl;
	cout << "  s	表示选择剪刀(scissor)" << endl;
	cout << "  c	表示选择布(cloth)" << endl;
	cout << "  d	表示选择显示(display)游戏当前状态" << endl;
	cout << "  h	表示选择获得帮助(help)" << endl;
	cout << "  q	表示选择退出(quit)" << endl << endl;
	cout << "游戏规则:" << endl;
	cout << "  石头砸坏剪刀" << endl;
	cout << "  剪刀剪碎布" << endl;
	cout << "  布覆盖石头" << endl;
}


void GameOfRockScissorCloth::Report(ResultType result)
// 操作结果：报告比赛结果，并统计获胜、失败和平局次数
{
	switch (result)
	{
	case WIN:	// 真人选手获胜
		winCount = winCount + 1;		// 获胜次数加1
		cout << "                            你获胜了啊!" << endl;
		break;
	case LOSE:	// 真人选手失败
		loseCount = loseCount + 1;		// 失败次数加1
		cout << "                            对不起，你失败了啊!" << endl;
		break;
	case TIE:	// 平局
		tieCount = tieCount + 1;		// 平局次数加1
		cout << "                            唉，是平局啊!" << endl;
		break;
	}
}

SelectType GameOfRockScissorCloth::SelectByMachine()
// 操作结果：电脑选手做选择
{
	return (SelectType) (GetRand(3));
}

SelectType GameOfRockScissorCloth::SelectByPlayer()
// 操作结果：真人选手做选择
{
	char select;
	SelectType playerChoice;

	printf("请选择(r,s,c,d,h,q)");
	do
	{	// 真人选手作选择
		cin >> select;
		select = tolower(select);	// 大写字母转化为小写字母
	} while (select != 'r' && select != 's' && select != 'c' 
		&& select != 'd' &&  select != 'h' &&  select != 'q');
	
	switch (select)
	{
	case 'r':	// 选择石头
		playerChoice = ROCK;
		break;
	case 's':	// 选择剪刀
		playerChoice = SCISSOR;
		break;
	case 'c':	// 选择布
		playerChoice = CLOTH;
		break;
	case 'd':	// 选择显示游戏状态
		playerChoice = DISPLAY;
		break;
	case 'h':	// 选择帮助
		playerChoice = HELP;
		break;
	case 'q':	// 选择退出
		playerChoice = QUIT;
		break;
	}

	return playerChoice;
}

void GameOfRockScissorCloth::Game()
// 操作结果：运行游戏
{
	ResultType result;						// 真人选手的胜负平结果
	SelectType playerChoice, machineChoice;	// 选手做的选择

	SetRandSeed();							// 设置随机数种子
	DisplayHelp();							// 显示帮助信息

	while ((playerChoice = SelectByPlayer()) != QUIT)
	{
		switch (playerChoice)
		{
		case ROCK:
		case SCISSOR:
		case CLOTH:							// 选手选择了石头、剪刀和布
			machineChoice = SelectByMachine();
			result = Compare(playerChoice, machineChoice);// 比较决定真人选手胜负平结果
			Report(result);					// 报告比赛结果，并统计获胜、失败和平局次数
			break;
		case DISPLAY:						// 选手选择显示游戏当前状态
			DisplayGameStatus();			// 显示游戏状态
			break;
		case HELP:							// 选手选择获得帮助
			DisplayHelp();					// 显示帮助信息
			break;
		}
	}
	
	DisplayGameStatus();					// 显示游戏状态
	DisplayFinalStatus();					// 显示游戏最后状态
}

#endif



