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
	explicit MainWindow(QWidget* parent = Q_NULLPTR);
	~MainWindow() override;

	void start();
private:
	Ui::MainWindow ui{};
	bool _start = false;

private:
	void end();
	void moveLeft();
	void moveRight();
	void moveUp();
	void movedown();

	void keyPressEvent(QKeyEvent* event) override;
};

