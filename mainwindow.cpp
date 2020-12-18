#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_exit_clicked()
{
	MainWindow::close();
}

void MainWindow::on_pvp_clicked()
{
	//game g;
	//g.show();
	g = new game(this, PVP);
	g->setAttribute(Qt::WA_DeleteOnClose);
	g->show();
}

void MainWindow::on_pve_clicked()
{
	g = new game(this, PVE);
	g->setAttribute(Qt::WA_DeleteOnClose);
	g->show();
}

void MainWindow::on_eve_clicked()
{
	g = new game(this, EVE);
	g->setAttribute(Qt::WA_DeleteOnClose);
	g->show();

}
