#include "include/MainWindow.h"
#include "include/Block.h"

#include <QMap>
#include <QString>
#include <QtCore/qdebug.h>
#include <QtCore/qlogging.h>
#include <QtCore/qobject.h>
#include <QtCore/qstring.h>
#include <QtGui/qvalidator.h>
#include <QtWidgets/qlayout.h>

#include <QDebug>
#include <QtWidgets/qmessagebox.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qtablewidget.h>
#include <cstdlib>
#include <iostream>
#include <random>

#define GAMEROW 4
#define GAMECOL 4

MainWindow::MainWindow(QWidget *parent) {
  ui.setupUi(this);
  this->setAttribute(Qt::WA_StyledBackground);

  connect(ui.NewGameButton, &QPushButton::clicked, this, &MainWindow::slotClickedNewGame);
  connect(ui.PreviousButton, &QPushButton::clicked, this,&MainWindow::slotClickedPrevious);

  start();
}

MainWindow::~MainWindow() = default;

void MainWindow::start() {
  _saveBlockIndex.clear();
  _saveBlockIndex.resize(16);
  // TODO 初始化游戏，计分
  _start = true;
  auto *b1 = new Block(2048);
  b1->SetBlock(2);

  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> dist6(0, 15);
  int randomwidget = dist6(rng);

  auto layoutw = ui.centralwidget->findChild<QGridLayout *>(
      "block_" + QString::number(randomwidget));

  if (layoutw != nullptr) {
    layoutw->addWidget(b1);
    qDebug() << layoutw->objectName();

    _saveBlockIndex[randomwidget] = 2;
  }
}

void MainWindow::makeblock() {}

void MainWindow::end() {
  // TODO 判断游戏是否结束
  bool rowmoveable, colmoveable;
  rowmoveable = colmoveable = false;

  // 横向查看是否游戏结束
  for (int i = 0; i < _saveBlockIndex.size() - 1; i++) {
    if (_saveBlockIndex[i] == _saveBlockIndex[i + 1] ||
        _saveBlockIndex[i + 1] == 0) {
      rowmoveable = true;
      break;
    }
  }

  // 纵向查看是否还有活动空间
  for (int i = 0; i < _saveBlockIndex.size() - 4; i++) {
    if (_saveBlockIndex[i] == _saveBlockIndex[i + 4] ||
        _saveBlockIndex[i + 4] == 0) {
      colmoveable = true;
      break;
    }
  }

  if (!rowmoveable && !colmoveable) {
    // 游戏结束
    QMessageBox::information(this, "Game Over", "This game is over!");
    start();
    return;
  }

  // 如果还有0, 在这些格子中随机在生成一个按钮
}

void MainWindow::slotClickedNewGame() {}

void MainWindow::slotClickedPrevious() {

}

void MainWindow::moveLeft() {
  // TODO 向左移动逻辑
  std::cout << "Move Left!" << std::endl;
  end();
}

void MainWindow::moveRight() {
  // TODO 向右移动逻辑
  std::cout << "Move Right!" << std::endl;
  end();
}

void MainWindow::moveUp() {
  // TODO 向上移动逻辑
  std::cout << "Move Up!" << std::endl;
  end();
}

void MainWindow::movedown() {
  // TODO 向下移动逻辑
  // 作业
  std::cout << "Move Down!" << std::endl;
  end();
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
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
