#include "include/MainWindow.h"

#include <QtCore/qdebug.h>
#include <QtCore/qlogging.h>
#include <QtCore/qobject.h>
#include <QtCore/qstring.h>
#include <QtGui/qvalidator.h>
#include <QtWidgets/qlayout.h>
#include <QtWidgets/qmessagebox.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qtablewidget.h>

#include <QDebug>
#include <QMap>
#include <QString>
#include <cstdlib>
#include <iostream>
#include <random>

#include "include/Block.h"

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

  CreateBlock();
}

void MainWindow::CreateBlock() {
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

    _saveFreeBlock.erase(std::find(_saveFreeBlock.begin(), _saveFreeBlock.end(), randomwidget));
  }
}

void MainWindow::End() {
  // TODO 判断游戏是否结束
  bool row_move_able = false;
  bool column_move_able = false;
  row_move_able = CheckRowValid();
  column_move_able = CheckColumnValid();

  if (!row_move_able && !column_move_able) {
    // 游戏结束
    QMessageBox::information(this, "Game Over", "This game is over!");
    start();
    return;
  }

  // 如果还有0, 在这些格子中随机在生成一个按钮
  ClearAllBlock();
  SetAllBlock();
  CalculateFreeBlockList();
  CreateBlock();
}

void MainWindow::CalculateFreeBlockList() {
  _saveFreeBlock.clear();
  _saveFreeBlock.resize(16);
  std::iota(_saveFreeBlock.begin(), _saveFreeBlock.end(), 0);

  for (int i = 0; i < _saveBlockIndex.size(); i++) {
    if (_saveBlockIndex[i] != 0) {
      _saveFreeBlock.erase(std::find(_saveFreeBlock.begin(), _saveFreeBlock.end(), i));
    }
  }
}

bool MainWindow::CheckColumnValid() {
  bool column_move_able = false;

  // 纵向查看是否还有活动空间
  for (int i = 0; i < _saveBlockIndex.size() - 4; i++) {
    if (_saveBlockIndex[i] == _saveBlockIndex[i + 4] || _saveBlockIndex[i + 4] == 0) {
      column_move_able = true;
      break;
    }
  }

  return column_move_able;
}

bool MainWindow::CheckRowValid() {
  bool row_move_able = false;

  // 横向查看是否游戏结束
  for (int i = 0; i < _saveBlockIndex.size() - 1; i++) {
    if (_saveBlockIndex[i] == _saveBlockIndex[i + 1] || _saveBlockIndex[i + 1] == 0) {
      row_move_able = true;
      break;
    }
  }

  return row_move_able;
}

void MainWindow::slotClickedNewGame() {
  ClearAllBlock();
  start();
}

void MainWindow::slotClickedPrevious() {}

void MainWindow::ClearAllBlock() {
  // 清除所有格子
  for (int x = 0; x < GAMEROW * GAMECOL; x++) {
    auto layout_widget = ui.centralwidget->findChild<QGridLayout *>("block_" + QString::number(x));
    if (layout_widget != nullptr) {
      auto box = this->findChild<Block *>("numbox" + QString::number(x));
      if (box != nullptr) {
        layout_widget->removeWidget(box);
        box->deleteLater();
      }
    }
  }
}

void MainWindow::SetAllBlock() {
  // 将已有的格子放回来
  for (int i = 0; i < _saveBlockIndex.size(); i++) {
    if (_saveBlockIndex[i] != 0) {
      auto *b1 = new Block(2048);
      b1->SetBlock(_saveBlockIndex[i]);
      auto layout_widget = ui.centralwidget->findChild<QGridLayout *>("block_" + QString::number(i));
      if (layout_widget != nullptr) {
        b1->setObjectName("numbox" + QString::number(i));
        layout_widget->addWidget(b1);
      }
    }
  }
}

void MainWindow::CalculateRowBlock(Qt::Key key) {
  // TODO 计算横排
  if (key == Qt::Key_Left) {
    for (int i = 0; i < GAMEROW; i++) {
      int index = i * GAMEROW;
      auto list = ListCalculate(std::vector<int>{_saveBlockIndex[index], _saveBlockIndex[index + 1],
                                                 _saveBlockIndex[index + 2], _saveBlockIndex[index + 3]});

      if (list.empty()) {
        continue;
      }

      list.resize(4);
      std::copy(list.begin(), list.end(), _saveBlockIndex.begin() + index);
    }
  } else if (key == Qt::Key_Right) {
    for (int i = 0; i < GAMEROW; i++) {
      int index = i * GAMEROW;
      auto list = ListCalculate(std::vector<int>{_saveBlockIndex[index], _saveBlockIndex[index + 1],
                                                 _saveBlockIndex[index + 2], _saveBlockIndex[index + 3]});

      if (list.empty()) {
        continue;
      }

      list.resize(4);
      std::copy(list.begin(), list.end(), _saveBlockIndex.begin() + index);
    }
  }
}

void MainWindow::CalculateColumnBlock(Qt::Key key) {
  // TODO 计算竖排
  if (key == Qt::Key_Up) {
  } else if (key == Qt::Key_Down) {
  }
}

std::vector<int> MainWindow::ListCalculate(std::vector<int> numList) {
  for (int i = 0; i < numList.size() - 1; i++) {
    if (numList[i] == numList[i + 1] && numList[i] != 0) {
      numList[i] = numList[i] * 2;
      numList[i + 1] = 0;
    }
  }

  for (auto i = numList.begin(); i != numList.end();) {
    if (*i == 0) {
      i = numList.erase(i);
      continue;
    }

    ++i;
  }

  return numList;
}

void MainWindow::MoveLeft() {
  std::cout << "Move Right!" << std::endl;
  // TODO 向左移动计算
  CalculateRowBlock(Qt::Key_Left);
  End();
}

void MainWindow::MoveRight() {
  std::cout << "Move Right!" << std::endl;
  // TODO 向右移动计算
  CalculateRowBlock(Qt::Key_Right);
  End();
}

void MainWindow::MoveUp() {
  std::cout << "Move Up!" << std::endl;
  // TODO 向上移动计算
  CalculateColumnBlock(Qt::Key_Up);
  End();
}

void MainWindow::MoveDown() {
  std::cout << "Move Down!" << std::endl;
  // TODO 向下移动计算
  CalculateColumnBlock(Qt::Key_Down);
  End();
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
  switch (event->key()) {
    case Qt::Key_Left:
    case Qt::Key_A:
      MoveLeft();
      break;
    case Qt::Key_Right:
    case Qt::Key_D:
      MoveRight();
      break;
    case Qt::Key_Up:
    case Qt::Key_W:
      MoveUp();
      break;
    case Qt::Key_Down:
    case Qt::Key_S:
      MoveDown();
      break;
    default:
      break;
  }
}
