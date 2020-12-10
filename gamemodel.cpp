#include "gamemodel.h"
#include <QMessageBox>
const int kBoardSizeNum = 15;

gamemodel::gamemodel()
{
	fb = new forbid();
}

bool gamemodel::isWin(int row, int col)
{
	// 横竖斜四种大情况，每种情况都根据当前落子往后遍历5个棋子，有一种符合就算赢
	// 水平方向
	for (int i = 0; i < 5; i++)
	{
		// 左右延申4个
		if (col - i >= 0 &&
			col - i + 4 < kBoardSizeNum &&
			gameMapVec[row][col - i] == gameMapVec[row][col - i + 1] &&
			gameMapVec[row][col - i] == gameMapVec[row][col - i + 2] &&
			gameMapVec[row][col - i] == gameMapVec[row][col - i + 3] &&
			gameMapVec[row][col - i] == gameMapVec[row][col - i + 4])
			return true;
	}

	// 竖直方向(上下延伸4个)
	for (int i = 0; i < 5; i++)
	{
		if (row - i >= 0 &&
			row - i + 4 < kBoardSizeNum &&
			gameMapVec[row - i][col] == gameMapVec[row - i + 1][col] &&
			gameMapVec[row - i][col] == gameMapVec[row - i + 2][col] &&
			gameMapVec[row - i][col] == gameMapVec[row - i + 3][col] &&
			gameMapVec[row - i][col] == gameMapVec[row - i + 4][col])
			return true;
	}

	// 左斜方向
	for (int i = 0; i < 5; i++)
	{
		if (row + i < kBoardSizeNum &&
			row + i - 4 >= 0 &&
			col - i >= 0 &&
			col - i + 4 < kBoardSizeNum &&
			gameMapVec[row + i][col - i] == gameMapVec[row + i - 1][col - i + 1] &&
			gameMapVec[row + i][col - i] == gameMapVec[row + i - 2][col - i + 2] &&
			gameMapVec[row + i][col - i] == gameMapVec[row + i - 3][col - i + 3] &&
			gameMapVec[row + i][col - i] == gameMapVec[row + i - 4][col - i + 4])
			return true;
	}

	// 右斜方向
	for (int i = 0; i < 5; i++)
	{
		if (row - i >= 0 &&
			row - i + 4 < kBoardSizeNum &&
			col - i >= 0 &&
			col - i + 4 < kBoardSizeNum &&
			gameMapVec[row - i][col - i] == gameMapVec[row - i + 1][col - i + 1] &&
			gameMapVec[row - i][col - i] == gameMapVec[row - i + 2][col - i + 2] &&
			gameMapVec[row - i][col - i] == gameMapVec[row - i + 3][col - i + 3] &&
			gameMapVec[row - i][col - i] == gameMapVec[row - i + 4][col - i + 4])
			return true;
	}

	return false;
}

bool gamemodel::isDeadGame()
{
	// 所有空格全部填满
	for (int i = 0; i < kBoardSizeNum; i++)
		for (int j = 0; j < kBoardSizeNum; j++)
		{
			if (!(gameMapVec[i][j] == 1 || gameMapVec[i][j] == -1))
				return false;
		}
	return true;
}

void gamemodel::startGame(GameType type)
{
	gameType = type;
	// 初始棋盘
	gameMapVec.clear();
	for (int i = 0; i < kBoardSizeNum; i++)
	{
		std::vector<int> lineBoard;
		for (int j = 0; j < kBoardSizeNum; j++)
			lineBoard.push_back(0);
		gameMapVec.push_back(lineBoard);
	}

	// AI模式

	// 黑方下为true,白方下为false
	playerFlag = true;
}

void gamemodel::updateGameMap(int row, int col)
{
	if (playerFlag)
		gameMapVec[row][col] = 1;
	else
		gameMapVec[row][col] = -1;

	// 换手
	playerFlag = !playerFlag;
}

int gamemodel::actionByPerson(int row, int col)
{
	if (playerFlag)
	{
		gameMapVec[row][col] = 1;
		int check = fb->check(gameMapVec, row, col);
		if (check == 3)
		{
			gameMapVec[row][col] = 0;
			return check;
		}
		if (isWin(row, col) == false && check != 0)
		{
			gameMapVec[row][col] = 0;
			return check;
		}
	}
	updateGameMap(row, col);
	return 0;
}

gamemodel::~gamemodel()
{
	if (fb)
	{
		delete fb;
		fb = nullptr;
	}
}
