#include "include/Block.h"

#include <QtGui/qfont.h>

Block::Block(const int number, QWidget *parent) : QLabel(parent) {
  this->setAutoFillBackground(true);
  BlockSetColor(number);
  BlockSetFont(number);
}

Block::~Block() = default;

void Block::SetBlock(const int number) {
  QPalette palette = this->palette();
  this->setStyleSheet(QString("background-color: %1").arg(QString::fromStdString(BlockGetColor(number))));

  if (number == 2 || number == 4) {
    palette.setColor(QPalette::WindowText, QColor(0x776e65));
  } else {
    palette.setColor(QPalette::WindowText, QColor(0xf9f6f2));
  }
  this->setPalette(palette);
  this->setText(QString::number(number));
  blockNumber_ = number;
}

void Block::BlockSetColor(const int moveNumber) {
  QPalette palette;
  if (moveNumber == 2 || moveNumber == 4) {
    palette.setColor(QPalette::WindowText, QColor(0x776e65));
  } else {
    palette.setColor(QPalette::WindowText, QColor(0xf9f6f2));
  }
  this->setStyleSheet(QString("background-color: %1").arg(QString::fromStdString(BlockGetColor(moveNumber))));
  // palette的优先级小于setStyleSheet，只要父窗口设置了此函数，其他palette就会失效
  this->setPalette(palette);
}

void Block::BlockSetFont(const int number) {
  this->setText(QString::number(number));
  this->setFont(QFont("Arial", 40, 75));
  this->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
}

auto Block::BlockGetColor(const int number) -> std::string {
  for (BlockColor bc : colorMap_) {
    if (bc.GetNumber() == number) return bc.GetColor();
  }

  return "";
}
