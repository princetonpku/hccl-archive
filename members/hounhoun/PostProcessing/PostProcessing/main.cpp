#include "PostProcessing.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	PostProcessing w;
	w.show();
	return a.exec();
}
