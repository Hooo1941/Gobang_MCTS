#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "game.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = nullptr);
	~MainWindow() override;

private slots:
	void on_exit_clicked();

	void on_pvp_clicked();

	void on_pve_clicked();

	void on_eve_clicked();

private:
	Ui::MainWindow *ui;
	game *g{};
};
#endif // MAINWINDOW_H
