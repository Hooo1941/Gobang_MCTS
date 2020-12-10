#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <vector>
#include <forbid.h>
enum GameType
{
	PVP,
	PVE,
	EVE
};

// 游戏状态
enum GameStatus
{
	PLAYING,
	WIN,
	DEAD
};


class gamemodel
{
public:
	std::vector<std::vector<int> > gameMapVec; // 存储当前游戏棋盘和棋子的情况,空白为0，白子1，黑子-1
	bool isWin(int row, int col);
	bool isDeadGame();
	bool playerFlag; // 标示下棋方
	GameType gameType; // 游戏模式
	GameStatus gameStatus; // 游戏状态
	void startGame(GameType type);
	int actionByPerson(int row, int col); // 人执行下棋
	void updateGameMap(int row, int col);
	gamemodel();
	~gamemodel();
private:
	forbid *fb;
};

#endif // GAMEMODEL_H
