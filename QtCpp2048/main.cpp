#include <QtWidgets/QApplication>
#include "ui/MainWindow.h"

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	
	MainWindow w;
	w.show();
	w.start();
	return a.exec();
}