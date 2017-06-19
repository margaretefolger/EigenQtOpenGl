#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#ifndef GEOMETRY
	#define GEOMETRY
	#include "geometry.h"
#endif

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	Geometry * myGeometry;
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private slots:
	void on_pushButtonShowMessage_released();

	void on_actionNew_Window_triggered();

private:
	Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
