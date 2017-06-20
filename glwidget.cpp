/*! \file glwidget.cpp
*  \brief dynamic viewer for elements in space, uses openGL
*  \similar to a typical glwidget class in Qt
*  \author Gernot Stangl
*/

#ifndef GLWIDGET
	#define GLWIDGET
	#include "glwidget.h"
#endif

#include <QCoreApplication>

GLWidget::GLWidget(QObject *parent) : QObject(parent)
{
	isCoreprofile = QCoreApplication::arguments().contains(QStringLiteral("--coreprofile"));
}

GLWidget::~GLWidget() {
	//cleanup();
}
