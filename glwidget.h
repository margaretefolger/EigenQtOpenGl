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

#ifndef VIEW
	#define VIEW
	#include "scene.h"
#endif

QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram) //the forward declaration will still work if someone configures Qt with -qtnamespace

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
	Q_OBJECT

public:
	explicit GLWidget(QWidget *parent = 0); //adding the explicit keyword suppresses implicit conversions
	~GLWidget();
	Scene elementCollection;

signals:

public slots:
	void addPoint(GLfloat xCoord, GLfloat yCoord, GLfloat zCoord);
	void cleanup();

protected:
	void initializeGL();
	void paintGL();

private:
	bool isCoreprofile;
	QTimer timer;
	QOpenGLShaderProgram * shaderProgram;
	int shaderProjMatrixLoc;
	int shaderMvMatrixLoc;
	int shaderNormalMatrixLoc;
	int shaderLightPosLoc;
	QOpenGLVertexArrayObject vertexArrayObject;
	QOpenGLBuffer vertexBufferObject; //The QOpenGLBuffer class provides functions for creating and managing OpenGL buffer objects.
	QMatrix4x4 projectionMatrix;
	QMatrix4x4 cameraMatrix;
	QMatrix4x4 worldMatrix;
	void setupVertexAttribs();
};

#endif // GLWIDGET_H
