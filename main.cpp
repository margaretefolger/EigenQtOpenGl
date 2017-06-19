#include "mainwindow.h"
#include <QApplication>

#ifndef GEOMETRY
	#define GEOMETRY
	#include "geometry.h"
#endif

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;
	w.show();

	return a.exec();
}
