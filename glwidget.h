/*! \file glwidget.h
*  \brief dynamic viewer for elements in space, uses openGL
*  \ similar to a typical glwidget class in Qt
*  \author Gernot Stangl
*/

#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QObject>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QMatrix4x4>
#include <QTimer> //timer for gui checkbox interaction

QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram) //the forward declaration will still work if someone configures Qt with -qtnamespace

class GLWidget : public QObject
{
	Q_OBJECT
public:
	explicit GLWidget(QObject *parent = 0); //adding the explicit keyword suppresses implicit conversions
	~GLWidget();

signals:

public slots:

private:
	bool isCoreprofile;
};

#endif // GLWIDGET_H
