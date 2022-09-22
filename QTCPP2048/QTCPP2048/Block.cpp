#include "Block.h"

Block::Block(int number, QColor color, QWidget *parent) : QLabel(parent)
{
	this->setText(QString::number(number));
	QPalette palette;
	palette.setColor(QPalette::Background, color);
	palette.setColor(QPalette::WindowText, QColor(255, 255, 255));
	this->setAutoFillBackground(true);
	this->setPalette(palette);

	this->setFont(QFont("Arial", 30, true));
	this->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
}

Block::~Block()
{
}
