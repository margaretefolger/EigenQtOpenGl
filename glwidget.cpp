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

GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
	isCoreprofile = QCoreApplication::arguments().contains(QStringLiteral("--coreprofile"));
	connect (&timer, SIGNAL(timeout()), this, SLOT(update()));
	timer.start(16);
}

GLWidget::~GLWidget()
{
	//cleanup();
}

void GLWidget::addPoint(GLfloat xCoord, GLfloat yCoord, GLfloat zCoord) {
	elementCollection.point(xCoord, yCoord, zCoord);
	//qDebug() << "GLWidget::addPoint elementCollection.vertexCount()" << elementCollection.vertexCount();
	vertexBufferObject.bind();
	vertexBufferObject.allocate(elementCollection.constData(), elementCollection.count() * sizeof(GLfloat));
	// Store the vertex attribute bindings for the program.
	setupVertexAttribs();
	vertexBufferObject.release();
}

void GLWidget::cleanup()
{
	makeCurrent();
	vertexBufferObject.destroy();
	delete shaderProgram;
	shaderProgram = 0;
	doneCurrent();
}

static const char *vertexShaderSourceCore =
	"#version 150\n"
	"in vec4 vertex;\n"
	"in vec3 normal;\n"
	"out vec3 vert;\n"
	"out vec3 vertNormal;\n"
	"uniform mat4 projMatrix;\n"
	"uniform mat4 mvMatrix;\n"
	"uniform mat3 normalMatrix;\n"
	"void main() {\n"
	"   vert = vertex.xyz;\n"
	"   vertNormal = normalMatrix * normal;\n"
	"   gl_Position = projMatrix * mvMatrix * vertex;\n"
	"}\n";

static const char *fragmentShaderSourceCore =
	"#version 150\n"
	"in highp vec3 vert;\n"
	"in highp vec3 vertNormal;\n"
	"out highp vec4 fragColor;\n"
	"uniform highp vec3 lightPos;\n"
	"void main() {\n"
	"   highp vec3 L = normalize(lightPos - vert);\n"
	"   highp float NL = max(dot(normalize(vertNormal), L), 0.0);\n"
	"   highp vec3 color = vec3(0.99, 1.0, 0.0);\n"
	"   highp vec3 col = clamp(color * 0.2 + color * 0.8 * NL, 0.0, 1.0);\n"
	"   fragColor = vec4(col, 1.0);\n"
	"}\n";

static const char *vertexShaderSource =
	"attribute vec4 vertex;\n"
	"attribute vec3 normal;\n"
	"varying vec3 vert;\n"
	"varying vec3 vertNormal;\n"
	"uniform mat4 projMatrix;\n"
	"uniform mat4 mvMatrix;\n"
	"uniform mat3 normalMatrix;\n"
	"void main() {\n"
	"   vert = vertex.xyz;\n"
	"   vertNormal = normalMatrix * normal;\n"
	"   gl_Position = projMatrix * mvMatrix * vertex;\n"
	"}\n";

static const char *fragmentShaderSource =
	"varying highp vec3 vert;\n"
	"varying highp vec3 vertNormal;\n"
	"uniform highp vec3 lightPos;\n"
	"void main() {\n"
	"   highp vec3 L = normalize(lightPos - vert);\n"
	"   highp float NL = max(dot(normalize(vertNormal), L), 0.0);\n"
	"   highp vec3 color = vec3(0.01, 0.01, 0.9);\n"
	"   highp vec3 col = clamp(color * 0.9 + color * 0.1 * NL, 0.0, 1.0);\n"
	"   gl_FragColor = vec4(col, 1.0);\n"
	"}\n";

void GLWidget::initializeGL()
{
	connect(context(), &QOpenGLContext::aboutToBeDestroyed, this, &GLWidget::cleanup);
	initializeOpenGLFunctions(); //function of QOpenGLFunctions

	//for testing purposes
	elementCollection.point(0.0, 0.0, -0.0);
	elementCollection.point(0.1, 0.1, -0.1);
	elementCollection.point(0.1, 0.1, 0.1);
	elementCollection.point(-0.1, 0.1, -0.1);
	elementCollection.point(-0.1, 0.1, 0.1);
	elementCollection.point(-0.1, -0.1, -0.1);
	elementCollection.point(-0.1, -0.1, 0.1);
	elementCollection.point(0.1, -0.1, -0.1);
	elementCollection.point(0.1, -0.1, 0.1);

	glClearColor(0.1, 0.9, 0.9, 1);
	shaderProgram = new QOpenGLShaderProgram; //in other examples this is m_program. The QOpenGLShaderProgram class allows OpenGL shader programs to be linked and used.
	shaderProgram->addShaderFromSourceCode(QOpenGLShader::Vertex, isCoreprofile ? vertexShaderSourceCore : vertexShaderSource);
	shaderProgram->addShaderFromSourceCode(QOpenGLShader::Fragment, isCoreprofile ? fragmentShaderSourceCore : fragmentShaderSource);
	shaderProgram->bindAttributeLocation("vertex", 0);
	shaderProgram->bindAttributeLocation("normal", 1);
	shaderProgram->link();
	shaderProgram->bind();
	shaderProjMatrixLoc = shaderProgram->uniformLocation("projMatrix");
	shaderMvMatrixLoc = shaderProgram->uniformLocation("mvMatrix");
	shaderNormalMatrixLoc = shaderProgram->uniformLocation("normalMatrix");
	shaderLightPosLoc = shaderProgram->uniformLocation("lightPos");
	//////// Vertex Array Object and Vertex Buffer Object ///////
	// Create a vertex array object. In OpenGL ES 2.0 and OpenGL 2.x
	// implementations this is optional and support may not be present
	// at all. Nonetheless the below code works in all cases and makes
	// sure there is a VAO when one is needed.
	vertexArrayObject.create(); //QOpenGLVertexArrayObject
	QOpenGLVertexArrayObject::Binder vaoBinder(&vertexArrayObject); //http://www.trentreed.net/blog/qt5-opengl-part-1-basic-rendering/
	// Setup our vertex buffer object.
	// Vertex Array Object and Vertex Buffer Object ///////https://www.kdab.com/opengl-in-qt-5-1-part-2/
	vertexBufferObject.create();
	vertexBufferObject.bind();
	//set size of vertex buffer object
	vertexBufferObject.allocate(elementCollection.constData(), elementCollection.count() * sizeof(GLfloat));
	// Store the vertex attribute bindings for the program.
	setupVertexAttribs();
	///////// End of Vertex Array Object and Vertex Buffer Object ///////

	// Our camera never changes in this example.
	cameraMatrix.setToIdentity(); //Sets this matrix to the identity.
	cameraMatrix.translate(0, 0, -1);
	// Light position is fixed.
	shaderProgram->setUniformValue(shaderLightPosLoc, QVector3D(0, 0, 70)); //light vector
	shaderProgram->release();

	//for testing purposes
	addPoint(0.2, 0.2, 0.2);

}

void GLWidget::paintGL() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST); //stores depth values in extra buffer, can be used in initializeGL https://open.gl/depthstencils
	glEnable(GL_CULL_FACE);
	//glMatrixMode(GL_MODELVIEW); //GL_PROJECTION, GL_MODELVIEW, from QT_OpenGL.pro example, TODO: try
	//glLoadIdentity(); from QT_OpenGL.pro example, TODO: try

	//somerotationangle += 0.5;

	//qDebug() << "GLWidget::paintGL somerotationangle" << somerotationangle;
	worldMatrix.setToIdentity();
	//Rotation functionality, not needed as of now
	//worldMatrix.rotate(180.0f - (somerotationangle + m_xRot / 16.0f), 1, 0, 0);
	//worldMatrix.rotate(m_yRot / 16.0f, 0, 1, 0);
	//worldMatrix.rotate(m_zRot / 16.0f, 0, 0, 1);

	QOpenGLVertexArrayObject::Binder vaoBinder(&vertexArrayObject); //The QOpenGLVertexArrayObject::Binder class is a convenience class to help with the binding and releasing of OpenGL Vertex Array Objects.
	shaderProgram->bind();
	shaderProgram->setUniformValue(shaderProjMatrixLoc, projectionMatrix);
	shaderProgram->setUniformValue(shaderMvMatrixLoc, cameraMatrix * worldMatrix);
	QMatrix3x3 normalMatrix = worldMatrix.normalMatrix();
	shaderProgram->setUniformValue(shaderNormalMatrixLoc, normalMatrix);
	glDrawArrays(GL_POINTS, 0, elementCollection.vertexCount()); //original
}

void GLWidget::setupVertexAttribs() {
	//qDebug() << "GLWidget::setupVertexAttribs function called";
	vertexBufferObject.bind();
	QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
	f->glEnableVertexAttribArray(0);
	f->glEnableVertexAttribArray(1);
	f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
	f->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<void *>(3 * sizeof(GLfloat)));
	vertexBufferObject.release();
}
