#include "include/Block.h"

#include <QtCore/qstringliteral.h>
#include <QtGui/qfont.h>

Block::Block(int moveNumber, QWidget *parent) : QLabel(parent) {
  this->setAutoFillBackground(true);
  BlockSetColor(moveNumber);
  BlockSetFont(moveNumber);
}

Block::~Block() = default;

void Block::SetBlock(int moveNumber) {
  QPalette palette = this->palette();
  this->setStyleSheet(QString("background-color: %1").arg(QString::fromStdString(BlockGetColor(moveNumber))));

  if (moveNumber == 2 || moveNumber == 4) {
    palette.setColor(QPalette::WindowText, QColor(0x776e65));
  } else {
    palette.setColor(QPalette::WindowText, QColor(0xf9f6f2));
  }
  this->setPalette(palette);
  this->setText(QString::number(moveNumber));
  _blockNumber = moveNumber;
}

void Block::BlockSetColor(int moveNumber) {
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

void Block::BlockSetFont(int moveNumber) {
  this->setText(QString::number(moveNumber));
  this->setFont(QFont("Arial", 40, 75));
  this->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
}

auto Block::BlockGetColor(int number) -> std::string {
  for (BlockColor bc : _colorMap) {
    if (bc.GetNumber() == number) return bc.GetColor();
  }

  return "";
}
