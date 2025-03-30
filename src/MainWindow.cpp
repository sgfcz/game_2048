#include "MainWindow.h"

#include <QtCore/qdebug.h>
#include <QtCore/qobject.h>
#include <QtCore/qstring.h>
#include <QtGui/qvalidator.h>
#include <QtWidgets/qlayout.h>
#include <QtWidgets/qmessagebox.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qtablewidget.h>

#include <iostream>

#include "Block.h"

#define GAME_ROW 4
#define GAME_COLUMN 4

MainWindow::MainWindow(QWidget *) {
  ui_.setupUi(this);
  this->setAttribute(Qt::WA_StyledBackground);
  ui_.BlockWidget->setFocusPolicy(Qt::StrongFocus);
  ui_.NewGameButton->setFocusPolicy(Qt::NoFocus);
  ui_.PreviousButton->setFocusPolicy(Qt::NoFocus);

  connect(ui_.NewGameButton, &QPushButton::clicked, this, &MainWindow::slotClickedNewGame);
  connect(ui_.PreviousButton, &QPushButton::clicked, this, &MainWindow::slotClickedPrevious);

  start();
}

MainWindow::~MainWindow() = default;

void MainWindow::start() {
  saveHistoryIndex_.clear();
  saveBlockIndex_.clear();
  saveFreeBlock_.clear();

  saveBlockIndex_.resize(16);
  saveFreeBlock_.resize(16);

  std::iota(saveFreeBlock_.begin(), saveFreeBlock_.end(), 0);

  ui_.BestNumber->setText("BEST\n0");
  ui_.ScoreNumber->setText("ScoreNumber\n0");

  // TODO 初始化游戏，计分
  start_ = true;

  CreateBlock();
}

void MainWindow::CreateBlock() {
  auto *b1 = new Block(kTwoThousandFortyEight);

  // 设置方块数字
  auto set_number = RandomGenerateNumber();
  b1->SetBlock(set_number);

  int random_widget = RandomGenerateBlock();
  std::cout << "random_widget: " << random_widget << '\n';

  if (auto *layout_widget = ui_.centralwidget->findChild<QGridLayout *>("block_" + QString::number(random_widget));
      layout_widget != nullptr) {
    b1->setObjectName("numbox" + QString::number(random_widget));
    layout_widget->addWidget(b1);
    saveBlockIndex_[random_widget] = set_number;
    saveFreeBlock_.erase(std::find(saveFreeBlock_.begin(), saveFreeBlock_.end(), random_widget));
  }
}

auto MainWindow::RandomGenerateBlock() -> int {
  // 设置随机格子
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> dist6(0, saveFreeBlock_.size() - 1);

  int block_widget_index = saveFreeBlock_[dist6(rng)];
  return block_widget_index;
}

auto MainWindow::RandomGenerateNumber() -> int {
  std::mt19937 engine(std::random_device{}());
  std::uniform_real_distribution<double> distribution(0.0, 1.0);
  double random_number = distribution(engine);
  int set_number = random_number < 0.9 ? 2 : 4;
  return set_number;
}

void MainWindow::End(const bool moved) {
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
  if (moved) {
    CreateBlock();
  }
}

void MainWindow::CalculateFreeBlockList() {
  saveFreeBlock_.clear();
  saveFreeBlock_.resize(16);
  std::iota(saveFreeBlock_.begin(), saveFreeBlock_.end(), 0);

  for (int i = 0; i < saveBlockIndex_.size(); i++) {
    if (saveBlockIndex_[i] != 0) {
      saveFreeBlock_.erase(std::find(saveFreeBlock_.begin(), saveFreeBlock_.end(), i));
    }
  }
}

auto MainWindow::CheckColumnValid() -> bool {
  bool column_move_able = false;

  // 纵向查看是否还有活动空间
  for (int i = 0; i < saveBlockIndex_.size() - 4; i++) {
    if (saveBlockIndex_[i] == saveBlockIndex_[i + 4] || saveBlockIndex_[i + 4] == 0) {
      column_move_able = true;
      break;
    }
  }

  return column_move_able;
}

auto MainWindow::CheckRowValid() -> bool {
  bool row_move_able = false;

  // 横向查看是否游戏结束
  for (int i = 0; i < saveBlockIndex_.size() - 1; i++) {
    if (saveBlockIndex_[i] == saveBlockIndex_[i + 1] || saveBlockIndex_[i + 1] == 0) {
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
  for (int x = 0; x < GAME_ROW * GAME_COLUMN; x++) {
    if (auto *layout_widget = ui_.centralwidget->findChild<QGridLayout *>("block_" + QString::number(x));
        layout_widget != nullptr) {
      if (auto *box = this->findChild<Block *>("numbox" + QString::number(x)); box != nullptr) {
        layout_widget->removeWidget(box);
        box->deleteLater();
      }
    }
  }
}

void MainWindow::SetAllBlock() {
  // 将已有的格子放回来
  for (int i = 0; i < saveBlockIndex_.size(); i++) {
    if (saveBlockIndex_[i] != 0) {
      auto *b1 = new Block(2048);
      b1->SetBlock(saveBlockIndex_[i]);
      if (auto *layout_widget = ui_.centralwidget->findChild<QGridLayout *>("block_" + QString::number(i));
          layout_widget != nullptr) {
        b1->setObjectName("numbox" + QString::number(i));
        layout_widget->addWidget(b1);
      }
    }
  }
}

auto MainWindow::CalculateRowBlock(const Qt::Key key) -> bool {
  // TODO 计算横排
  bool move_action = false;
  if (key == Qt::Key_Left) {
    for (int i = 0; i < GAME_ROW; i++) {
      int index = i * GAME_ROW;
      auto list = ListCalculate(std::vector<int>{saveBlockIndex_[index], saveBlockIndex_[index + 1],
                                                 saveBlockIndex_[index + 2], saveBlockIndex_[index + 3]});

      if (list.empty()) {
        continue;
      }

      list.resize(4);
      move_action = true;
      std::copy(list.begin(), list.end(), saveBlockIndex_.begin() + index);
    }
  } else if (key == Qt::Key_Right) {
    for (int i = 0; i < GAME_ROW; i++) {
      int index = i * GAME_ROW;
      auto list = ListCalculate(std::vector<int>{saveBlockIndex_[index], saveBlockIndex_[index + 1],
                                                 saveBlockIndex_[index + 2], saveBlockIndex_[index + 3]});

      if (list.empty()) {
        continue;
      }

      list.resize(4);
      move_action = true;
      std::copy(list.begin(), list.end(), saveBlockIndex_.begin() + index);
    }
  }

  return move_action;
}

auto MainWindow::CalculateColumnBlock(const Qt::Key key) -> bool {
  // TODO 计算竖排
  bool move_action = false;

  if (key == Qt::Key_Up) {
    // TODO 计算竖排
  } else if (key == Qt::Key_Down) {
    // TODO 计算竖排
  }

  return move_action;
}

auto MainWindow::ListCalculate(std::vector<int> numList) -> std::vector<int> {
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
  std::cout << "Move Right!" << '\n';
  // TODO 向左移动计算
  auto move_action = CalculateRowBlock(Qt::Key_Left);
  End(move_action);
}

void MainWindow::MoveRight() {
  std::cout << "Move Right!" << '\n';
  // TODO 向右移动计算
  auto move_action = CalculateRowBlock(Qt::Key_Right);
  End(move_action);
}

void MainWindow::MoveUp() {
  std::cout << "Move Up!" << '\n';
  // TODO 向上移动计算
  auto move_action = CalculateColumnBlock(Qt::Key_Up);
  End(move_action);
}

void MainWindow::MoveDown() {
  std::cout << "Move Down!" << '\n';
  // TODO 向下移动计算
  auto move_action = CalculateColumnBlock(Qt::Key_Down);
  End(move_action);
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
