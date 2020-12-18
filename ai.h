#ifndef AI_H
#define AI_H

#include <QThread>
#include <vector>
#include "forbid.h"
#include "config.h"
struct node
{
	bool playerFlag;
	std::vector <node *> children;
	int visit = 0; // 访问次数
	double win = 0; // 获胜次数
	std::pair<int, int> pos; // 下子位置
};

//struct pathNode
//{
//	int r, c;
//	bool playerFlag;
//	pathNode(int _r, int _c, bool _p) :
//	r(_r), c(_c), playerFlag(_p) {}
//};

std::vector <node *> path;
double UCB(const node& x, int total);
class ai : public QThread
{
Q_OBJECT
public:
	explicit ai(std::vector<std::vector<int> > gameMapVec, bool player, QObject *parent = nullptr);

protected:
	void run() override;

private:
	std::vector<std::vector<int> > map;
	bool empty();
	bool check(std::vector<std::vector<int> > mapCheck, int r, int c) const;
	bool playerFlag = true;
	static node *selection(node *root);
	node *expansion(node *&root);
	static bool isWin(std::vector<std::vector<int> > gameMapVec, int row, int col);
	int simulation(node *&root);
	void backPropagation(int score);
signals:
	void pos(int, int);
};

#endif // AI_H