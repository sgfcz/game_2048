#include "Block.h"

Block::Block(int number, QWidget *parent) : QLabel(parent)
{
	this->setAutoFillBackground(true);
	BlockSetColor(number);
	BlockSetFont(number);
}

Block::~Block()
= default;

void Block::SetBlock(int number)
{
	QPalette palette = this->palette();
	this->setStyleSheet(QString("background-color: %1").arg(QString::fromStdString(BlockGetColor(number))));
	if (number == 2 || number == 4)
		palette.setColor(QPalette::WindowText, QColor(0x776e65));
	else
		palette.setColor(QPalette::WindowText, QColor(0xf9f6f2));
	this->setPalette(palette);
	this->setText(QString::number(number));
}

void Block::BlockSetColor(int number)
{
	QPalette palette;
	if (number == 2 || number == 4)
		palette.setColor(QPalette::WindowText, QColor(0x776e65));
	else 
		palette.setColor(QPalette::WindowText, QColor(0xf9f6f2));
	this->setStyleSheet(QString("background-color: %1").arg(QString::fromStdString(BlockGetColor(number))));
	//palette的优先级小于setStyleSheet，只要父窗口设置了此函数，其他palette就会失效
	this->setPalette(palette);
}

void Block::BlockSetFont(int number)
{
	this->setText(QString::number(number));
	this->setFont(QFont("Arial", 30, 75));
	this->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
}

std::string Block::BlockGetColor(int number)
{
	for (BlockColor bc : _colorMap) {
		if (bc.getnumber() == number)
			return bc.getcolor();
	}
}
