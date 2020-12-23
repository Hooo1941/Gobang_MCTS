#ifndef GAME_H
#define GAME_H

#include <QMainWindow>
#include "gamemodel.h"
#include "ai.h"
#include "config.h"
class game : public QMainWindow
{
	Q_OBJECT

public:
	explicit game(QWidget *parent = nullptr, GameType type = PVP);
	~game() override;
protected:
	// 绘制
	void paintEvent(QPaintEvent *event) override;
	// 监听鼠标移动情况，方便落子
	void mouseMoveEvent(QMouseEvent *event) override;
	// 实际落子
	void mouseReleaseEvent(QMouseEvent *event) override;
private:
	gamemodel *model; // 游戏指针
	GameType game_type; // 存储游戏类型
	int clickPosRow = 0, clickPosCol = 0; // 存储将点击的位置
	int lastCol = -1, lastRow = -1;
	bool chessOneByPerson(); // 人执行
	void chessOneByAI();
	bool AIWorking = false;
private slots:
	void chessSlot(int row, int col);
};

#endif // GAME_H
