#include "MainWindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget* parent)
{
	ui.setupUi(this);
	ui.PreviousButton->setFocusPolicy(Qt::FocusPolicy::NoFocus);
	ui.NewGameButton->setFocusPolicy(Qt::FocusPolicy::NoFocus);
	this->setAttribute(Qt::WA_StyledBackground);
	//start();
}

MainWindow::~MainWindow()
= default;

void MainWindow::start()
{
	//TODO 初始化游戏，计分
	_start = true;
	auto *b1 = new Block(2048);
	b1->SetBlock(2);
	ui.block_0->addWidget(b1);
}

void MainWindow::end()
{
	//TODO 判断游戏是否结束
}

void MainWindow::moveLeft()
{
	//TODO 向左移动逻辑
	std::cout << "Move Left!" << std::endl;
	end();
}

void MainWindow::moveRight()
{
	//TODO 向右移动逻辑
	std::cout << "Move Right!"<< std::endl;
	end();
}

void MainWindow::moveUp()
{
	//TODO 向上移动逻辑
	std::cout << "Move Up!"<< std::endl;
	end();
}

void MainWindow::movedown()
{
	//TODO 向下移动逻辑
	//作业
	std::cout << "Move Down!"<< std::endl;
	Qt::red;
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
	switch (event->key()) {
	case Qt::Key_Left:
		moveLeft();
		break;
	case Qt::Key_Right:
		moveRight();
		break;
	case Qt::Key_Up:
		moveUp();
		break;
	case Qt::Key_Down:
		movedown();
		break;
	default:
		break;
	}
}

