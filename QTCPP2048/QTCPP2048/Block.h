#pragma once
#include <QLabel>

class Block : public QLabel
{
	Q_OBJECT
public:
	Block(int number, QColor color, QWidget* parent = Q_NULLPTR);
	~Block();
private:
	QColor color;
	int number;
};

