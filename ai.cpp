#include "ai.h"
#include <utility>
#include <cmath>
#include <random>
double UCB(const node *x, int total)
{
	if (x->playerFlag)
		return x->win / (double)x->visit + kConfidence * std::sqrt(std::log((double)total) / (double)x->visit);
	return 1.0 - x->win / (double)x->visit + kConfidence * std::sqrt(std::log((double)total) / (double)x->visit);
}

bool ai::isWin(std::vector<std::vector<int> > gameMapVec, int row, int col)
{
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

ai::ai(std::vector<std::vector<int> > gameMapVec, bool player, QObject *parent) :
		QThread(parent)
{
	map = std::move(gameMapVec);
	playerFlag = player;
}

bool ai::empty()
{
	for (int i=0; i<kBoardSizeNum; i++)
		for (int j=0; j<kBoardSizeNum; j++)
			if (map[i][j] != 0) return false;
	return true;
}

bool ai::check(std::vector<std::vector<int> > mapCheck, int r, int c) const
{
	if (mapCheck[r][c] != 0) return false;
	if (playerFlag)
	{
		mapCheck[r][c] = 1;
		int check = forbid::check(mapCheck, r, c);
		mapCheck[r][c] = 0;
		if (check != 0) return false;
	}
	if (r - 2 >= 0)
	{
		if (c - 2 >= 0)
			if (mapCheck[r - 2][c - 2] != 0) return true;
		if (c - 1 >= 0)
			if (mapCheck[r - 2][c - 1] != 0) return true;
		if (mapCheck[r - 2][c] != 0) return true;
		if (c + 1 < kBoardSizeNum)
			if (mapCheck[r - 2][c + 1] != 0) return true;
		if (c + 2 < kBoardSizeNum)
			if (mapCheck[r - 2][c + 2] != 0) return true;
	}
	if (r - 1 >= 0)
	{
		if (c - 2 >= 0)
			if (mapCheck[r - 1][c - 2] != 0) return true;
		if (c - 1 >= 0)
			if (mapCheck[r - 1][c - 1] != 0) return true;
		if (mapCheck[r - 1][c] != 0) return true;
		if (c + 1 < kBoardSizeNum)
			if (mapCheck[r - 1][c + 1] != 0) return true;
		if (c + 2 < kBoardSizeNum)
			if (mapCheck[r - 1][c + 2] != 0) return true;
	}
	if (c - 2 >= 0)
		if (mapCheck[r][c - 2] != 0) return true;
	if (c - 1 >= 0)
		if (mapCheck[r][c - 1] != 0) return true;
	if (c + 1 < kBoardSizeNum)
		if (mapCheck[r][c + 1] != 0) return true;
	if (c + 2 < kBoardSizeNum)
		if (mapCheck[r][c + 2] != 0) return true;
	if (r + 2 < kBoardSizeNum)
	{
		if (c - 2 >= 0)
			if (mapCheck[r + 2][c - 2] != 0) return true;
		if (c - 1 >= 0)
			if (mapCheck[r + 2][c - 1] != 0) return true;
		if (mapCheck[r + 2][c] != 0) return true;
		if (c + 1 < kBoardSizeNum)
			if (mapCheck[r + 2][c + 1] != 0) return true;
		if (c + 2 < kBoardSizeNum)
			if (mapCheck[r + 2][c + 2] != 0) return true;
	}
	if (r + 1 < kBoardSizeNum)
	{
		if (c - 2 >= 0)
			if (mapCheck[r + 1][c - 2] != 0) return true;
		if (c - 1 >= 0)
			if (mapCheck[r + 1][c - 1] != 0) return true;
		if (mapCheck[r + 1][c] != 0) return true;
		if (c + 1 < kBoardSizeNum)
			if (mapCheck[r + 1][c + 1] != 0) return true;
		if (c + 2 < kBoardSizeNum)
			if (mapCheck[r + 1][c + 2] != 0) return true;
	}
	return false;
}

void ai::run()
{
	//触发信号
	//emit pos(8, 8);
	//如果棋盘空，下在中心
	time_t start = time(nullptr);
	if (empty())
	{
		emit pos(7, 7);
		return;
	}
	// 记录所有判断的下子点
	// 周围两圈有棋子即为可考虑点
	std::vector<std::pair<int, int> > available;
	for (int i=0; i<kBoardSizeNum; i++)
		for (int j=0; j<kBoardSizeNum; j++)
			if (check(map, i, j))
			{
				available.emplace_back(std::make_pair(i, j));
			}
	if (available.size() == 1)
	{
		emit pos(available[0].first, available[0].second);
		return;
	}
	node *root = new node;
	root->playerFlag = playerFlag;
	root->pos = std::make_pair(-1, -1);

	while (time(nullptr) - start < kAIDelay)
	{
		path.clear();
		node *leaf = selection(root);
		if (leaf->visit > 0 && leaf->children.empty())
			leaf = expansion(leaf);
		int score = simulation(leaf);
		backPropagation(score);
	}
	node *pNode;
	pNode = *std::max_element(
			root->children.begin(),
			root->children.end(),
			// UCB实现选择
			[root](const node *a, const node *b)
			{
				double x = UCB(a, root->visit);
				double y = UCB(b, root->visit);
				return x < y;
			}
	);
	emit pos(pNode->pos.first, pNode->pos.second);
	delete root;
}

node *ai::selection(node *root)
{
	node *pNode;
	pNode = root;
	path.push_back(root);
	while (pNode->visit > 0 && !pNode->children.empty())
	{
		pNode = *std::max_element(
				pNode->children.begin(),
				pNode->children.end(),
				// UCB实现选择
				[pNode](const node *a, const node *b)
				{
					double x = UCB(a, pNode->visit);
					double y = UCB(b, pNode->visit);
					return x < y;
				}
		);
		path.push_back(pNode);
	}
	return pNode;
}

node *ai::expansion(node *&root)
{
	std::vector<std::vector<int> > newMap = map;
	int size = path.size();
	for (int i=0; i<size; i++)
	{
		if (path[i]->playerFlag)
			newMap[path[i]->pos.first][path[i]->pos.second] = 1;
		else
			newMap[path[i]->pos.first][path[i]->pos.second] = -1;
	}
	if (isWin(newMap, root->pos.first, root->pos.second))
		return root;
	std::vector<std::pair<int, int> > available;
	for (int i=0; i<kBoardSizeNum; i++)
		for (int j=0; j<kBoardSizeNum; j++)
			if (check(newMap, i, j))
				available.emplace_back(std::make_pair(i, j));
	if (available.empty())
		return root;
	bool playerNow = !root->playerFlag;
	size = available.size();
	// 创建子节点
	for (int i=0; i<size; i++)
	{
		node *newNode = new node;
		newNode->playerFlag = playerNow;
		root->children.emplace_back(newNode);
	}
	// 随机选择一个子节点
	std::uniform_int_distribution<unsigned> dis(0, size);
	std::random_device rd;
	std::mt19937 gen(rd());
	return root->children[dis(gen)];
}

int ai::simulation(node *&root)
{

}

void ai::backPropagation(int score)
{

}