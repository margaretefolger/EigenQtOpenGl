/*! \file scene.h
*  \brief base class for visible things in OpenGL
*  \author Gernot Stangl
*/

#ifndef SCENE_H
#define SCENE_H

#include <qopengl.h>
#include <QVector>
#include <QVector3D>
#include <QDebug>

class Scene {
public:
	Scene();
	const GLfloat *constData() const { return sceneData.constData(); }
	void clearView();
	int count() const { return sceneCount; }
	void point(GLfloat x, GLfloat y, GLfloat z);
	int vertexCount() const { return sceneCount / 6; }

private:
	QPoint m_lastPos;
	void add(const QVector3D &v, const QVector3D &n);

	QVector<GLfloat> sceneData;
	int sceneCount;
};

#endif // SCENE_H
