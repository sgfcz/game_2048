#include "Block.h"

Block::Block(int number, QWidget *parent) : QLabel(parent)
{
	BlockSetColor(number);
	BlockSetFont(number);
}

Block::~Block()
{
}

void Block::SetBlock(int number)
{
	palette.setColor(QPalette::Background, BlockGetColor(number));
	this->setText(QString::number(number));
}

void Block::BlockSetColor(int number)
{
	palette.setColor(QPalette::Background, BlockGetColor(number));
	if (number == 2 || number == 4)
		palette.setColor(QPalette::WindowText, QColor(0x776e65));
	else 
		palette.setColor(QPalette::WindowText, QColor(0xf9f6f2));
	this->setAutoFillBackground(true);
	this->setPalette(palette);
}

void Block::BlockSetFont(int number)
{
	this->setText(QString::number(number));
	this->setFont(QFont("Arial", 30, true));
	this->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
}

QColor Block::BlockGetColor(int number)
{
	return ColorMap[number];
}
