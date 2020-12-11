#include "forbid.h"
#include <QDebug>
const int kMapSizeNum = 15;
int forbid::check(const std::vector <std::vector<int> >& map, int x, int y)
{
	if (fb33(map, x, y))
	{
		qDebug("33");
		return 1;
	}
	if (fb44(map, x, y))
	{
		qDebug("44");
		return 2;
	}
	if (fbol(map, x, y))
	{
		qDebug("ol");
		return 3;
	}
	return 0;
}

bool forbid::fb33(std::vector <std::vector<int> > map, int x, int y)
{
	//三三禁手，活三
	int fb33_1 = 0;
	int i;
	int j;
	for (j = 0; j <= 9; j++)
	{
		if (map[x][j] == 0 && map[x][j + 5] == 0)
		{
			if (map[x][j + 1] == 1 && map[x][j + 2] == 1 && map[x][j + 3] == 1 &&
				map[x][j + 4] == 0 && (y == j + 1 || y == j + 2 || y == j + 3))
				fb33_1 = 1;
			if (map[x][j + 1] == 1 && map[x][j + 2] == 1 && map[x][j + 4] == 1 &&
				map[x][j + 3] == 0 && (y == j + 1 || y == j + 2 || y == j + 4))
				fb33_1 = 1;
			if (map[x][j + 1] == 1 && map[x][j + 3] == 1 && map[x][j + 4] == 1 &&
				map[x][j + 2] == 0 && (y == j + 1 || y == j + 3 || y == j + 4))
				fb33_1 = 1;
			if (map[x][j + 2] == 1 && map[x][j + 3] == 1 && map[x][j + 4] == 1 &&
				map[x][j + 1] == 0 && (y == j + 2 || y == j + 3 || y == j + 4))
				fb33_1 = 1;
		}
	}

	//竖活三
	int fb33_2 = 0;
    for (i = 0; i <= 9; i++)
	{
		if (map[i][y] == 0 && map[i + 5][y] == 0)
		{
			if (map[i + 1][y] == 1 && map[i + 2][y] == 1 && map[i + 3][y] == 1 &&
				map[i + 4][y] == 0 && (x == i + 1 || x == i + 2 || x == i + 3))
				fb33_2 = 1;
			if (map[i + 1][y] == 1 && map[i + 2][y] == 1 && map[i + 4][y] == 1 &&
				map[i + 3][y] == 0 && (x == i + 1 || x == i + 2 || x == i + 4))
				fb33_2 = 1;
			if (map[i + 1][y] == 1 && map[i + 3][y] == 1 && map[i + 4][y] == 1 &&
				map[i + 2][y] == 0 && (x == i + 1 || x == i + 3 || x == i + 4))
				fb33_2 = 1;
			if (map[i + 2][y] == 1 && map[i + 3][y] == 1 && map[i + 4][y] == 1 &&
				map[i + 1][y] == 0 && (x == i + 2 || x == i + 3 || x == i + 4))
				fb33_2 = 1;
		}
	}

	//左斜活3
	int fb33_3 = 0;
	i = x - std::min(x,y);
	j = y - std::min(x,y);
	while (i <= 9 && j <= 9)
	{
		if (map[i][j] == 0 && map[i + 5][j + 5] == 0)
		{
			if (map[i + 1][j + 1] == 1 && map[i + 2][j + 2] == 1 && map[i + 3][j + 3] == 1 &&
				map[i + 4][j + 4] == 0 &&
				((x == i + 1 && y == j + 1) || (x == i + 2 && y == j + 2) || (x == i + 3 && y == j + 3)))
				fb33_3 = 1;
			if (map[i + 1][j + 1] == 1 && map[i + 2][j + 2] == 1 && map[i + 4][j + 4] == 1 &&
				map[i + 3][j + 3] == 0 &&
				((x == i + 1 && y == j + 1) || (x == i + 2 && y == j + 2) || (x == i + 4 && y == j + 4)))
				fb33_3 = 1;
			if (map[i + 1][j + 1] == 1 && map[i + 3][j + 3] == 1 && map[i + 4][j + 4] == 1 &&
				map[i + 2][j + 2] == 0 &&
				((x == i + 1 && y == j + 1) || (x == i + 3 && y == j + 3) || (x == i + 4 && y == j + 4)))
				fb33_3 = 1;
			if (map[i + 2][j + 2] == 1 && map[i + 3][j + 3] == 1 && map[i + 4][j + 4] == 1 &&
				map[i + 1][j + 1] == 0 &&
				((x == i + 2 && y == j + 2) || (x == i + 3 && y == j + 3) || (x == i + 4 && y == j + 4)))
				fb33_3 = 1;
		}
		i++;
		j++;
	}

	//右斜活3
	int fb33_4 = 0;
	i = x - std::min(x,14 - y);
	j = y + std::min(x,14 - y);
	while (i <= 9 && j >= 5)
	{
		if (map[i][j] == 0 && map[i + 5][j - 5] == 0)
		{
			if (map[i + 1][j - 1] == 1 && map[i + 2][j - 2] == 1 && map[i + 3][j - 3] == 1 &&
				map[i + 4][j - 4] == 0 &&
				((x == i + 1 && y == j - 1) || (x == i + 2 && y == j - 2) || (x == i + 3 && y == j - 3)))
				fb33_4 = 1;
			if (map[i + 1][j - 1] == 1 && map[i + 2][j - 2] == 1 && map[i + 4][j - 4] == 1 &&
				map[i + 3][j - 3] == 0 &&
				((x == i + 1 && y == j - 1) || (x == i + 2 && y == j - 2) || (x == i + 4 && y == j - 4)))
				fb33_4 = 1;
			if (map[i + 1][j - 1] == 1 && map[i + 3][j - 3] == 1 && map[i + 4][j - 4] == 1 &&
				map[i + 2][j - 2] == 0 &&
				((x == i + 1 && y == j - 1) || (x == i + 3 && y == j - 3) || (x == i + 4 && y == j - 4)))
				fb33_4 = 1;
			if (map[i + 2][j - 2] == 1 && map[i + 3][j - 3] == 1 && map[i + 4][j - 4] == 1 &&
				map[i + 1][j - 1] == 0 &&
				((x == i + 2 && y == j - 2) || (x == i + 3 && y == j - 3) || (x == i + 4 && y == j - 4)))
				fb33_4 = 1;
		}
		i++;
		j--;
	}
	if (fb33_1 + fb33_2 + fb33_3 + fb33_4 <= 1) return false;
	else return true;
}

bool forbid::fb44(std::vector <std::vector<int> > map, int x, int y)
{
	//44禁手，活四或者冲四
	int fb44_1 = 0;
	int i;
	int j;
	//横四
	for (j = 0; j <= 10; j++)
	{
		if (y == j || y == j + 1 || y == j + 2 || y == j + 3 || y == j + 4)
		{
			if (map[x][j] == 1 && map[x][j + 1] == 1 &&
				map[x][j + 2] == 1 && map[x][j + 3] == 1 && map[x][j + 4] == 0)
				fb44_1 = 1;
			if (map[x][j] == 1 &&
				map[x][j + 1] == 0 && map[x][j + 2] == 1 &&
				map[x][j + 3] == 1 && map[x][j + 4] == 1)
				fb44_1 = 1;
			if (map[x][j] == 1 &&
				map[x][j + 1] == 1 && map[x][j + 2] == 0 &&
				map[x][j + 3] == 1 && map[x][j + 4] == 1)
				fb44_1 = 1;
			if (map[x][j] == 1 &&
				map[x][j + 1] == 1 && map[x][j + 2] == 1 &&
				map[x][j + 3] == 0 && map[x][j + 4] == 1)
				fb44_1 = 1;
			if (map[x][j] == 0 && map[x][j + 1] == 1 && map[x][j + 2] == 1 &&
				map[x][j + 3] == 1 && map[x][j + 4] == 1)
				fb44_1 = 1;
		}
	}

	//竖四
	int fb44_2 = 0;
    for (i = 0; i <= 10; i++)
	{
		if (x == i || x == i + 1 || x == i + 2 || x == i + 3 || x == i + 4)
		{
			if (map[i][y] == 1 && map[i + 1][y] == 1 &&
				map[i + 2][y] == 1 && map[i + 3][y] == 1 && map[i + 4][y] == 0)
				fb44_2 = 1;
			if (map[i][y] == 1 &&
				map[i + 1][y] == 0 && map[i + 2][y] == 1 &&
				map[i + 3][y] == 1 && map[i + 4][y] == 1)
				fb44_2 = 1;
			if (map[i][y] == 1 &&
				map[i + 1][y] == 1 && map[i + 2][y] == 0 &&
				map[i + 3][y] == 1 && map[i + 4][y] == 1)
				fb44_2 = 1;
			if (map[i][y] == 1 &&
				map[i + 1][y] == 1 && map[i + 2][y] == 1 &&
				map[i + 3][y] == 0 && map[i + 4][y] == 1)
				fb44_2 = 1;
			if (map[i][y] == 0 && map[i + 1][y] == 1 && map[i + 2][y] == 1 &&
				map[i + 3][y] == 1 && map[i + 4][y] == 1)
				fb44_2 = 1;
		}
	}

	//左斜四
	int fb44_3 = 0;
	i = x - std::min(x,y);
	j = y - std::min(x,y);
	while (i <= 10 && j <= 10)
	{
		if ((x == i && y == j) || (x == i + 1 && y == j + 1) || (x == i + 2 && y == j + 2) ||
			(x == i + 3 && y == j + 3) || (x == i + 4 && y == j + 4))
		{
			if (map[i][j] == 1 && map[i + 1][j + 1] == 1 &&
				map[i + 2][j + 2] == 1 && map[i + 3][j + 3] == 1 && map[i + 4][j + 4] == 0)
				fb44_3 = 1;
			if (map[i][j] == 1 &&
				map[i + 1][j + 1] == 0 && map[i + 2][j + 2] == 1 &&
				map[i + 3][j + 3] == 1 && map[i + 4][j + 4] == 1)
				fb44_3 = 1;
			if (map[i][j] == 1 &&
				map[i + 1][j + 1] == 1 && map[i + 2][j + 2] == 0 &&
				map[i + 3][j + 3] == 1 && map[i + 4][j + 4] == 1)
				fb44_3 = 1;
			if (map[i][j] == 1 &&
				map[i + 1][j + 1] == 1 && map[i + 2][j + 2] == 1 &&
				map[i + 3][j + 3] == 0 && map[i + 4][j + 4] == 1)
				fb44_3 = 1;
			if (map[i][j] == 0 && map[i + 1][j + 1] == 1 && map[i + 2][j + 2] == 1 &&
				map[i + 3][j + 3] == 1 && map[i + 4][j + 4] == 1)
				fb44_3 = 1;
		}
		i++;
		j++;
	}

	//右斜四
	int fb44_4 = 0;
	i = x - std::min(x,14 - y);
	j = y + std::min(x,14 - y);
	while (i <= 10 && j >= 4)
	{
		if ((x == i && y == j) || (x == i + 1 && y == j - 1) || (x == i + 2 && y == j - 2) |
			(x == i + 3 && y == j - 3) || (x == i + 4 && y == j - 4))
		{
			if (map[i][j] == 1 && map[i + 1][j - 1] == 1 &&
				map[i + 2][j - 2] == 1 && map[i + 3][j - 3] == 1 && map[i + 4][j - 4] == 0)
				fb44_4 = 1;
			if (map[i][j] == 1 &&
				map[i + 1][j - 1] == 0 && map[i + 2][j - 2] == 1 &&
				map[i + 3][j - 3] == 1 && map[i + 4][j - 4] == 1)
				fb44_4 = 1;
			if (map[i][j] == 1 &&
				map[i + 1][j - 1] == 1 && map[i + 2][j - 2] == 0 &&
				map[i + 3][j - 3] == 1 && map[i + 4][j - 4] == 1)
				fb44_4 = 1;
			if (map[i][j] == 1 &&
				map[i + 1][j - 1] == 1 && map[i + 2][j - 2] == 1 &&
				map[i + 3][j - 3] == 0 && map[i + 4][j - 4] == 1)
				fb44_4 = 1;
			if (map[i][j] == 0 && map[i + 1][j - 1] == 1 && map[i + 2][j - 2] == 1 &&
				map[i + 3][j - 3] == 1 && map[i + 4][j - 4] == 1)
				fb44_4 = 1;
		}
		i++;
		j--;
	}
	if (fb44_1 + fb44_2 + fb44_3 + fb44_4 >= 2) return true;
	return false; 
}

bool forbid::fbol(std::vector <std::vector<int> > map,int x,int y)
{
	// 横竖斜四种大情况，每种情况都根据当前落子往后遍历6个棋子，有一种符合就算长连禁手
	int ol = 0, win = 0;
	for (int i = 0; i < 6; i++)
	{
		if (y - i >= 0 &&y - i + 5 < kMapSizeNum &&
			map[x][y - i] == map[x][y - i + 1] &&
			map[x][y - i] == map[x][y - i + 2] &&
			map[x][y - i] == map[x][y - i + 3] &&
			map[x][y - i] == map[x][y - i + 4] &&
			map[x][y - i] == map[x][y - i + 5])
			ol++;
	}
	for (int i = 0; i < 6; i++)
	{
		if (x - i >= 0 &&x - i + 5 < kMapSizeNum &&
			map[x - i][y] == map[x - i + 1][y] &&
			map[x - i][y] == map[x - i + 2][y] &&
			map[x - i][y] == map[x - i + 3][y] &&
			map[x - i][y] == map[x - i + 4][y] &&
			map[x - i][y] == map[x - i + 5][y])
			ol++;
	}
	for (int i = 0; i < 6; i++)
	{
		if (x + i < kMapSizeNum && x + i - 5 >= 0 &&
			y - i >= 0 && y - i + 5 < kMapSizeNum &&
			map[x + i][y - i] == map[x + i - 1][y - i + 1] &&
			map[x + i][y - i] == map[x + i - 2][y - i + 2] &&
			map[x + i][y - i] == map[x + i - 3][y - i + 3] &&
			map[x + i][y - i] == map[x + i - 4][y - i + 4] &&
			map[x + i][y - i] == map[x + i - 5][y - i + 5])
			ol++;
	}
	for (int i = 0; i < 6; i++)
	{
		if (x - i >= 0 && x - i + 5 < kMapSizeNum &&
			y - i >= 0 && y - i + 5 < kMapSizeNum &&
			map[x - i][y - i] == map[x - i + 1][y - i + 1] &&
			map[x - i][y - i] == map[x - i + 2][y - i + 2] &&
			map[x - i][y - i] == map[x - i + 3][y - i + 3] &&
			map[x - i][y - i] == map[x - i + 4][y - i + 4] &&
			map[x - i][y - i] == map[x - i + 5][y - i + 5])
			ol++;
	}
	//判五连
	for (int i = 0; i < 5; i++)
	{
		// 左右延申4个
		if (y - i >= 0 &&
			y - i + 4 < kMapSizeNum &&
			map[x][y - i] == map[x][y - i + 1] &&
			map[x][y - i] == map[x][y - i + 2] &&
			map[x][y - i] == map[x][y - i + 3] &&
			map[x][y - i] == map[x][y - i + 4])
		{
			win++;
			break;
		}
	}

	// 竖直方向(上下延伸4个)
	for (int i = 0; i < 5; i++)
	{
		if (x - i >= 0 &&
			x - i + 4 < kMapSizeNum &&
			map[x - i][y] == map[x - i + 1][y] &&
			map[x - i][y] == map[x - i + 2][y] &&
			map[x - i][y] == map[x - i + 3][y] &&
			map[x - i][y] == map[x - i + 4][y])
		{
			win++;
			break;
		}
	}

	// 左斜方向
	for (int i = 0; i < 5; i++)
	{
		if (x + i < kMapSizeNum &&
			x + i - 4 >= 0 &&
			y - i >= 0 &&
			y - i + 4 < kMapSizeNum &&
			map[x + i][y - i] == map[x + i - 1][y - i + 1] &&
			map[x + i][y - i] == map[x + i - 2][y - i + 2] &&
			map[x + i][y - i] == map[x + i - 3][y - i + 3] &&
			map[x + i][y - i] == map[x + i - 4][y - i + 4])
		{
			win++;
			break;
		}
	}

	// 右斜方向
	for (int i = 0; i < 5; i++)
	{
		if (x - i >= 0 &&
			x - i + 4 < kMapSizeNum &&
			y - i >= 0 &&
			y - i + 4 < kMapSizeNum &&
			map[x - i][y - i] == map[x - i + 1][y - i + 1] &&
			map[x - i][y - i] == map[x - i + 2][y - i + 2] &&
			map[x - i][y - i] == map[x - i + 3][y - i + 3] &&
			map[x - i][y - i] == map[x - i + 4][y - i + 4])
		{
			win++;
			break;
		}
	}
	if (win == 0) return false;
	if (ol == win) return true;
	else return false;
}
