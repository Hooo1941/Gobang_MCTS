#include <QPainter>
#include <QSound>
#include <QMouseEvent>
#include <QMessageBox>
#include <QMenuBar>
#include <cmath>
#include "game.h"

#define CHESS_ONE_SOUND ":/res/sound/chessone.wav"
#define WIN_SOUND ":/res/sound/win.wav"
#define LOSE_SOUND ":/res/sound/lose.wav"
#define BG_IMG ":/res/image/board.jpg"
game::game(QWidget *parent, GameType type) :
	QMainWindow(parent)
{
	setFixedSize(kBoardSize, kBoardSize);
	// 开启鼠标hover功能
	setMouseTracking(true);
	model = new gamemodel;
	model->startGame();
	game_type = type;
	if (game_type == EVE)
	    chessByAI();
	update();
}

void game::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	// 绘制棋盘
	painter.setRenderHint(QPainter::Antialiasing, true); // 抗锯齿
	// 绘制背景
	painter.drawPixmap(0,0,this->width(),this->height(),QPixmap(BG_IMG));
	QBrush brush;
	brush.setStyle(Qt::SolidPattern);
	// 绘制落子标记
	if (clickPosRow >= 0 && clickPosRow < kBoardSizeNum &&
		clickPosCol >= 0 && clickPosCol < kBoardSizeNum &&
		model->gameMapVec[clickPosRow][clickPosCol] == 0)
	{
		if (model->playerFlag)
			brush.setColor(Qt::black);
		else
			brush.setColor(Qt::white);
		painter.setBrush(brush);
		painter.drawRect(kBoardMargin + kBlockSize * clickPosCol - kMarkSize / 2, kBoardMargin + kBlockSize * clickPosRow - kMarkSize / 2, kMarkSize, kMarkSize);
	}
	// 绘制棋子
	for (int i = 0; i < kBoardSizeNum; i++)
		for (int j = 0; j < kBoardSizeNum; j++)
		{
			if (model->gameMapVec[i][j] == 1)
			{
				brush.setColor(Qt::black);
				painter.setBrush(brush);
				painter.drawEllipse(kBoardMargin + kBlockSize * j - kRadius, kBoardMargin + kBlockSize * i - kRadius, kRadius * 2, kRadius * 2);
			}
			else if (model->gameMapVec[i][j] == -1)
			{
				brush.setColor(Qt::white);
				painter.setBrush(brush);
				painter.drawEllipse(kBoardMargin + kBlockSize * j - kRadius, kBoardMargin + kBlockSize * i - kRadius, kRadius * 2, kRadius * 2);
			}
		}

	// 判断输赢
	if (lastRow >= 0)
	{
		brush.setColor(Qt::red);
		painter.setBrush(brush);
		painter.drawEllipse(kBoardMargin + kBlockSize * lastCol - kPointR, kBoardMargin + kBlockSize * lastRow - kPointR, kPointR * 2, kPointR * 2);
		if (model->isWin(lastRow, lastCol))
		{
			qDebug("win");
			QSound::play(WIN_SOUND);
			QString str;
			if (model->gameMapVec[clickPosRow][clickPosCol] == 1)
				str = "black player";
			else if (model->gameMapVec[clickPosRow][clickPosCol] == -1)
				str = "white player";
			QMessageBox::information(this, "congratulations", str + " win!");
			// 重置游戏状态
			lastRow = -1;
			lastCol = -1;
			model->startGame();
		}
	}
	// 判断死局
	if (model->isDeadGame())
	{
		QSound::play(LOSE_SOUND);
		QMessageBox::information(this, "oops", "dead game!");
		model->startGame();
	}
}

void game::mouseMoveEvent(QMouseEvent *event)
{
	// 通过鼠标的hover确定落子的标记
	int x = event->x();
	int y = event->y();

	// 棋盘边缘不能落子
	if (x >= kBoardMargin / 2 &&x < size().width() - kBoardMargin / 2 &&
		y >= kBoardMargin / 2 &&y < size().height()- kBoardMargin / 2)
	{
		// 获取最近的左上角的点
		int col = x / kBlockSize;
		int row = y / kBlockSize;
		int leftTopPosX = kBoardMargin + kBlockSize * col;
		int leftTopPosY = kBoardMargin + kBlockSize * row;

		// 根据距离算出合适的点击位置,一共四个点，根据半径距离选最近的
		clickPosRow = -1; // 初始化最终的值
		clickPosCol = -1;
		int len = (int)sqrt((x - leftTopPosX) * (x - leftTopPosX) + (y - leftTopPosY) * (y - leftTopPosY));
		if (len < kPosDelta)
		{
			clickPosRow = row;
			clickPosCol = col;
		}
		len = (int)sqrt((x - leftTopPosX - kBlockSize) * (x - leftTopPosX - kBlockSize) + (y - leftTopPosY) * (y - leftTopPosY));
		if (len < kPosDelta)
		{
			clickPosRow = row;
			clickPosCol = col + 1;
		}
		len = (int)sqrt((x - leftTopPosX) * (x - leftTopPosX) + (y - leftTopPosY - kBlockSize) * (y - leftTopPosY - kBlockSize));
		if (len < kPosDelta)
		{
			clickPosRow = row + 1;
			clickPosCol = col;
		}
		len = (int)sqrt((x - leftTopPosX - kBlockSize) * (x - leftTopPosX - kBlockSize) + (y - leftTopPosY - kBlockSize) * (y - leftTopPosY - kBlockSize));
		if (len < kPosDelta)
		{
			clickPosRow = row + 1;
			clickPosCol = col + 1;
		}
	}
	// 重绘
	update();
}

void game::mouseReleaseEvent(QMouseEvent *event)
{
	if (game_type == PVE && model->playerFlag)
	{
		if (chessOneByPerson())
			chessOneByAI();
	}
	if (game_type == PVP)
		chessOneByPerson();
}

void game::chessSlot(int row, int col)
{
	model->action(row, col);
	QSound::play(CHESS_ONE_SOUND);
}

void game::chessOneByAI()
{
	ai *t;
	t = new ai(model->gameMapVec, model->playerFlag, this);
	connect(t, SIGNAL(pos(int, int)), this, SLOT(chessSlot(int, int)));
	connect(t, SIGNAL(finished()), t, SLOT(deleteLater()));
	//执行子线程
	t->start();
}

void game::chessByAI()
{
	chessOneByAI();
}

bool game::chessOneByPerson()
{
	// 根据当前存储的坐标下子
	// 只有有效点击才下子，并且该处没有子
	if (clickPosRow >= 0 && clickPosCol >= 0 && clickPosRow < kBoardSizeNum && clickPosCol < kBoardSizeNum && model->gameMapVec[clickPosRow][clickPosCol] == 0)
	{
		int res = model->action(clickPosRow, clickPosCol);
		if (res == 0)
		{
			lastRow = clickPosRow;
			lastCol = clickPosCol;
			QSound::play(CHESS_ONE_SOUND);
			update();
			return true;
		}
		else
		{
			QString str;
			if (res == 1)
				str = "Double three";
			if (res == 2)
				str = "Double four";
			if (res == 3)
				str = "Overline";
			QMessageBox::information(this, "Oops", str + " Forbidden moves");
			return false;
		}
	}
	return false;
}

game::~game()
{
	if (model)
	{
		delete model;
		model = nullptr;
	}
}
