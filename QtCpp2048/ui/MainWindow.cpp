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
	//TODO ��ʼ����Ϸ���Ʒ�
	_start = true;
	auto *b1 = new Block(2048);
	b1->SetBlock(2);
	ui.block_0->addWidget(b1);
}

void MainWindow::end()
{
	//TODO �ж���Ϸ�Ƿ����
}

void MainWindow::moveLeft()
{
	//TODO �����ƶ��߼�
	std::cout << "Move Left!" << std::endl;
	end();
}

void MainWindow::moveRight()
{
	//TODO �����ƶ��߼�
	std::cout << "Move Right!"<< std::endl;
	end();
}

void MainWindow::moveUp()
{
	//TODO �����ƶ��߼�
	std::cout << "Move Up!"<< std::endl;
	end();
}

void MainWindow::movedown()
{
	//TODO �����ƶ��߼�
	//��ҵ
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

