#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include <vector>

#ifndef GEOMETRY
	#define GEOMETRY
	#include "geometry.h"
#endif

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	ui->messageLabel->setText("Hello World");
	myGeometry = new Geometry(this);

//	QString someString = myGeometry->matrixBaseToQString(theMatrix);
//	qDebug() << someString;

	QString theString = myGeometry->makeMatrix3dListElement(3, 2.5, 2, -1, 1.5, 2, 2, 3, 2);
	//qDebug() << theString << "MainWindow";
	theString = myGeometry->makeMatrix3dListElement(4, 2.5, 2, -1, 1.5, 2, 2, 3, 2);
	//qDebug() << theString << "MainWindow";
	theString = myGeometry->makeMatrix3dListElement(5, 2.5, 2, -1, 1.5, 2, 2, 3, 2);
	//qDebug() << theString << "MainWindow";

	for(std::vector<Matrix3d>::const_iterator iter = myGeometry->matrix3dList.begin(); iter != myGeometry->matrix3dList.end(); ++iter) {
		QString someString = myGeometry->matrix3dToQString(*iter);
		qDebug() << someString << "MainWindow";
	}

	//std::vector<Matrix3d *>::const_iterator iter = myGeometry->matrix3dList.begin();
	//Eigen::Matrix<double,3,3>* iterMatrix = *iter; //this works!
	//QString someString = myGeometry->matrix3dToQString(*iter);
	//QString someString = myGeometry->matrix3dToQString(*iter);
	//qDebug() << someString << "MainWindow";

	//std::vector<Matrix3d*>::const_iterator iter = myGeometry->matrix3dList.begin();
	//QString someString = myGeometry->matrix3dToQString(myGeometry->matrix3dList[0]);
	//QString someString = myGeometry->matrix3dToQString(*iter);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_pushButtonShowMessage_released()
{
	//void 				about
	//void 				aboutQt
	//StandardButton 	critical
	//StandardButton 	information
	//StandardButton 	question
	//StandardButton 	warning
	QMessageBox::about(this, "My Title", "My message");
	QMessageBox::StandardButton reply = QMessageBox::question(this, "Quit Application", "Do you want to quit the application?", QMessageBox::Yes | QMessageBox::No);
	if(reply == QMessageBox::Yes) {
		QApplication::quit();
	} else {
//		QString theString = myGeometry->testGeometry();
//		ui->messageLabel->setText(theString);
		ui->messageLabel->setText("Quit was not \nconfirmed.");
		qDebug() << "Quit was not confirmed";
	}

}

void MainWindow::on_actionNew_Window_triggered()
{

}
