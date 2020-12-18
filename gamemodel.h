#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <vector>
#include <forbid.h>
#include "config.h"
enum GameType
{
	PVP,
	PVE,
	EVE
};

// 游戏状态

class gamemodel
{
public:
	std::vector<std::vector<int> > gameMapVec; // 存储当前游戏棋盘和棋子的情况,空白为0，白子1，黑子-1
	bool isWin(int row, int col);
	bool isDeadGame();
	bool playerFlag = true; // 标示下棋方
	//GameStatus gameStatus = PLAYING; // 游戏状态
	void startGame();
	int action(int row, int col); // 人执行下棋
	void updateGameMap(int row, int col);
};

#endif // GAMEMODEL_H
