#pragma once
#include <QLabel>
#include <map>

class Block : public QLabel
{
	Q_OBJECT
public:
	Block(int number, QWidget* parent = Q_NULLPTR);
	~Block();

	void SetBlock(int number);
private:
	int number = 0;
	std::map<int, QColor> ColorMap{ 
		{2, QColor(0xeee4da)}, {4, QColor(0xede0c8)}, {8, QColor(0xf2b179)},
		{16, QColor(0xf59563)}, {32, QColor(0xf67c5f)}, {64, QColor(0xf65e3b)},
		{128, QColor(0xedcf72)}, {256, QColor(0xedcc61)}, {512, QColor(0xedc850)},
		{1024, QColor(0xedc53f)}, {2048, QColor(0xedc22e)}};

private:
	void BlockSetColor(int number);
	void BlockSetFont(int number);
	QColor BlockGetColor(int number);
	QPalette palette;
};

