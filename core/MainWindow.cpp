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
  ui.BlockWidget->setFocusPolicy(Qt::StrongFocus);
  ui.NewGameButton->setFocusPolicy(Qt::NoFocus);
  ui.PreviousButton->setFocusPolicy(Qt::NoFocus);

  connect(ui.NewGameButton, &QPushButton::clicked, this, &MainWindow::slotClickedNewGame);
  connect(ui.PreviousButton, &QPushButton::clicked, this, &MainWindow::slotClickedPrevious);

  start();
}

MainWindow::~MainWindow() = default;

void MainWindow::start() {
  _saveHistoryIndex.clear();
  _saveBlockIndex.clear();
  _saveFreeBlock.clear();

  _saveBlockIndex.resize(16);
  _saveFreeBlock.resize(16);

  std::iota(_saveFreeBlock.begin(), _saveFreeBlock.end(), 0);

  ui.BestNumber->setText("BEST\n0");
  ui.ScoreNumber->setText("ScoreNumber\n0");

  // TODO 初始化游戏，计分
  _start = true;

  createblock();
}

void MainWindow::createblock() {
  auto *b1 = new Block(2048);

  // 设置方块数字
  std::mt19937 engine(std::random_device{}());
  std::uniform_real_distribution<double> distribution(0.0, 1.0);
  double random_number = distribution(engine);
  int setNumber = random_number < 0.9 ? 2 : 4;
  b1->SetBlock(setNumber);

  // 设置随机格子
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> dist6(0, _saveFreeBlock.size() - 1);

  int randomwidget = _saveFreeBlock[dist6(rng)];
  std::cout << "randomwidget: " << randomwidget << std::endl;

  auto layoutw = ui.centralwidget->findChild<QGridLayout *>("block_" + QString::number(randomwidget));

  if (layoutw != nullptr) {
    b1->setObjectName("numbox" + QString::number(randomwidget));
    layoutw->addWidget(b1);
    _saveBlockIndex[randomwidget] = setNumber;

    _saveFreeBlock.erase(std::find(_saveFreeBlock.begin(),  _saveFreeBlock.end(),  randomwidget));
  }
}

void MainWindow::end() {
  // TODO 判断游戏是否结束
  bool rowmoveable = false;
  bool colmoveable = false;
  rowmoveable = checkRowValid();
  colmoveable = checkColValid();

  if (!rowmoveable && !colmoveable) {
    // 游戏结束
    QMessageBox::information(this, "Game Over", "This game is over!");
    start();
    return;
  }

  // 如果还有0, 在这些格子中随机在生成一个按钮
  clearAllBlock();
  setAllBlock();
  calFreeBlockList();
  createblock();
}

void MainWindow::calFreeBlockList() {
  _saveFreeBlock.clear();
  _saveFreeBlock.resize(16);
  std::iota(_saveFreeBlock.begin(), _saveFreeBlock.end(), 0);

  for (int i = 0; i < _saveBlockIndex.size(); i++) {
    if (_saveBlockIndex[i] !=  0) {
      _saveFreeBlock.erase(std::find(_saveFreeBlock.begin(),  _saveFreeBlock.end(),  i));
    }
  }
}

bool MainWindow::checkColValid() {
  bool colmoveable;
  colmoveable = false;

  // 纵向查看是否还有活动空间
  for (int i = 0; i < _saveBlockIndex.size() - 4; i++) {
    if (_saveBlockIndex[i] == _saveBlockIndex[i + 4] ||
        _saveBlockIndex[i + 4] == 0) {
      colmoveable = true;
      break;
    }
  }

  return colmoveable;
}

bool MainWindow::checkRowValid() {
  bool rowmoveable = false;

  // 横向查看是否游戏结束
  for (int i = 0; i < _saveBlockIndex.size() - 1; i++) {
    if (_saveBlockIndex[i] == _saveBlockIndex[i + 1] ||
        _saveBlockIndex[i + 1] == 0) {
      rowmoveable = true;
      break;
    }
  }

  return rowmoveable;
}

void MainWindow::slotClickedNewGame() {
  clearAllBlock();
  start();
}

void MainWindow::slotClickedPrevious() {}

void MainWindow::clearAllBlock() {
  //清除所有格子
  for (int x = 0; x < GAMEROW * GAMECOL; x++) {
    auto layoutw = ui.centralwidget->findChild<QGridLayout *>("block_" + QString::number(x));
    if (layoutw != nullptr) {
      auto box = this->findChild<Block *>("numbox" + QString::number(x));
      if (box != nullptr) {
        layoutw->removeWidget(box);
        box->deleteLater();
      }
    }
  }
}

void MainWindow::setAllBlock()
{
  //将已有的格子放回来
  for (int i = 0; i < _saveBlockIndex.size(); i++) {
    if (_saveBlockIndex[i] != 0) {
      auto *b1 = new Block(2048);
      b1->SetBlock(_saveBlockIndex[i]);
      auto layoutw = ui.centralwidget->findChild<QGridLayout *>("block_" + QString::number(i));
      if (layoutw != nullptr) {
        b1->setObjectName("numbox" + QString::number(i));
        layoutw->addWidget(b1);
      }
    }
  }
}

void MainWindow::calRowBlock(Qt::Key key)
{
  //TODO 计算横排
  if (key == Qt::Key_Left) {
    for (int i = 0; i < GAMEROW; i++) {
      int index = i * GAMEROW;
      auto list = listCal(std::vector<int>{_saveBlockIndex[index], _saveBlockIndex[index + 1],
      _saveBlockIndex[index + 2], _saveBlockIndex[index + 3]});

      if (list.empty()) {
        continue;
      }

      list.resize(4);
      std::copy(list.begin(),  list.end(),  _saveBlockIndex.begin() + index);
    }
  }
  else if (key == Qt::Key_Right) {
  }
}

void MainWindow::calColBlock(Qt::Key key)
{
  //TODO 计算竖排
  if (key == Qt::Key_Up) {
  }
  else if (key == Qt::Key_Down) {

  }
}

std::vector<int> MainWindow::listCal(std::vector<int> numList) {
  for (int i = 0; i < numList.size() - 1; i++) {
    if (numList[i] ==  numList[i+1] && numList[i] !=  0) {
      numList[i] = numList[i] * 2;
      numList[i + 1] = 0;
    }
  }

  for (auto i = numList.begin(); i != numList.end();) {
    if (*i ==  0) {
      i = numList.erase(i);
      continue;
    }

    ++i;
  }

  return numList;
}

void MainWindow::moveLeft() {
  std::cout << "Move Right!" << std::endl;
  // TODO 向左移动计算
  calRowBlock(Qt::Key_Left);
  end();
}

void MainWindow::moveRight() {
  std::cout << "Move Right!" << std::endl;
  // TODO 向右移动计算
  calRowBlock(Qt::Key_Right);
  end();
}

void MainWindow::moveUp() {
  std::cout << "Move Up!" << std::endl;
  // TODO 向上移动计算
  calColBlock(Qt::Key_Up);
  end();
}

void MainWindow::movedown() {
  std::cout << "Move Down!" << std::endl;
  // TODO 向下移动计算
  calColBlock(Qt::Key_Down);
  end();
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
  switch (event->key()) {
  case Qt::Key_Left:
  case Qt::Key_A:
    moveLeft();
    break;
  case Qt::Key_Right:
  case Qt::Key_D:
    moveRight();
    break;
  case Qt::Key_Up:
  case Qt::Key_W:
    moveUp();
    break;
  case Qt::Key_Down:
  case Qt::Key_S:
    movedown();
    break;
  default:
    break;
  }
}
