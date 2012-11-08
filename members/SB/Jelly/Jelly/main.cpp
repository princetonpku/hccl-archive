#include "Jelly.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Jelly w;
	w.show();
	return a.exec();
}
