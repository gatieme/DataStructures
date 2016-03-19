// 文件路径名: game_of_21_point\card.h 
#ifndef __CARD_H__
#define __CARD_H__

typedef enum 
{	// 扑克牌面值:ACE(A),TWO(2)~TEN(10),JACK(J), QUEEN(Q), KING(K)
	ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING
} RankType;

typedef enum 
{	// 扑克牌花色:CLUBS(梅花), DIAMONDS(方块), HEARTS(红桃)和SPADES(黑桃)
	CLUBS, DIAMONDS, HEARTS, SPADES
} SuitType;

struct Card
{	// 扑克牌结构体
	RankType rank;									// 扑克牌面值
	SuitType suit;									// 扑克牌花色
};

ostream& operator<<(ostream& outStream, const Card &card) 
// 操作结果：重载<<运算符
{
	// 输出花色
	if (card.suit == CLUBS) outStream << " 梅花";		// CLUBS表示梅花
	else if (card.suit == DIAMONDS) outStream << " 方块";// DIAMONDS表示方块
	else if (card.suit == HEARTS) outStream << " 红桃";	// HEARTS表示红桃
	else if (card.suit == SPADES) outStream << " 黑桃";	// SPADES表示黑桃

	// 输出面值
	if (card.rank == ACE) outStream << "A";				// ACE表示A
	else if  (card.rank == JACK) outStream << "J";		// JACK表示J
	else if  (card.rank == QUEEN) outStream << "Q";		// QUEEN表示Q
	else if  (card.rank == KING) outStream << "K";		// KING表示K
	else cout << (int)card.rank;						// (int)card.rank为分值

	return outStream;
}

#endif
