#pragma once
#include <QtWidgets>
#include <QtWidgets/QMainWindow>
#include <QKeyEvent>
#include "ui_MainWindow.h"
#include "Block.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	MainWindow(QWidget* parent = Q_NULLPTR);
	~MainWindow();

private:
	Ui::MainWindow ui;
	bool _start = false;

private:
	void start();
	void end();
	void moveLeft();
	void moveRight();
	void moveUp();
	void movedown();

	void keyPressEvent(QKeyEvent* event);
};

