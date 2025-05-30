#include "MainWindow.h"

#include <QtCore/qdebug.h>
#include <QtCore/qobject.h>
#include <QtCore/qstring.h>
#include <QtWidgets/qlayout.h>
#include <QtWidgets/qmessagebox.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qtablewidget.h>

#include <iostream>

#include "Block.h"
#include "CalculationBlock.h"

MainWindow::MainWindow(QWidget *) {
  ui_.setupUi(this);
  this->setAttribute(Qt::WA_StyledBackground);
  ui_.BlockWidget->setFocusPolicy(Qt::StrongFocus);
  ui_.NewGameButton->setFocusPolicy(Qt::NoFocus);
  ui_.PreviousButton->setFocusPolicy(Qt::NoFocus);

  connect(ui_.NewGameButton, &QPushButton::clicked, this, &MainWindow::slotClickedNewGame);
  connect(ui_.PreviousButton, &QPushButton::clicked, this, &MainWindow::slotClickedPrevious);

  calculationBlock_ = std::make_shared<CalculationBlock>();

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
  auto set_number = calculationBlock_->RandomGenerateNumber();
  b1->SetBlock(set_number);

  uint32_t randow_index = calculationBlock_->RandomGenerateBlock(saveFreeBlock_.size());
  int random_widget = saveFreeBlock_[randow_index];
  std::cout << "random_widget: " << random_widget << '\n';

  if (auto *layout_widget = ui_.centralwidget->findChild<QGridLayout *>("block_" + QString::number(random_widget));
      layout_widget != nullptr) {
    b1->setObjectName("numbox" + QString::number(random_widget));
    layout_widget->addWidget(b1);
    saveBlockIndex_[random_widget] = set_number;
    saveFreeBlock_.erase(std::find(saveFreeBlock_.begin(), saveFreeBlock_.end(), random_widget));
  }
}

void MainWindow::End(const bool moved) {
  // TODO 判断游戏是否结束
  bool row_move_able = false;
  bool column_move_able = false;
  row_move_able = calculationBlock_->CheckRowValid(saveBlockIndex_);
  column_move_able = calculationBlock_->CheckColumnValid(saveBlockIndex_);

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

void MainWindow::slotClickedNewGame() {
  ClearAllBlock();
  start();
}

void MainWindow::slotClickedPrevious() {}

void MainWindow::ClearAllBlock() {
  // 清除所有格子
  for (int x = 0; x < kGameRow * kGameColumn; x++) {
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

void MainWindow::MoveLeft() {
  std::cout << "Move Right!" << '\n';
  auto move_action = calculationBlock_->CalculateLeftMove(saveBlockIndex_);
  End(move_action);
}

void MainWindow::MoveRight() {
  std::cout << "Move Right!" << '\n';
  auto move_action = calculationBlock_->CalculateRightMove(saveBlockIndex_);
  End(move_action);
}

void MainWindow::MoveUp() {
  std::cout << "Move Up!" << '\n';
  auto move_action = calculationBlock_->CalculateUpMove(saveBlockIndex_);
  End(move_action);
}

void MainWindow::MoveDown() {
  std::cout << "Move Down!" << '\n';
  auto move_action = calculationBlock_->CalculateDownMove(saveBlockIndex_);
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
