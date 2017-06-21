/*! \file scene.cpp
*  \brief base class for visible things in OpenGL
*  \author Gernot Stangl
*/
#ifndef SCENE
#define SCENE
	#include "scene.h"
#endif
#include <qmath.h>

using namespace std;

Scene::Scene() : sceneCount(0)
{
	//m_data.resize(2048 * 2048 * 6); //this will do harm
	sceneData.resize(0);
	sceneData.reserve(2048 * 2048 * 6); //only for memory allocation, not harmful if actual vector size is larger

}

void Scene::add(const QVector3D &v, const QVector3D &n) //The QVector3D class represents a vector or vertex in 3D space
{
	sceneData.append(v.x());
	sceneData.append(v.y());
	sceneData.append(v.z());
	sceneData.append(n.x());
	sceneData.append(n.y());
	sceneData.append(n.z());
	sceneCount += 6;
	//qDebug() << "View::add m_count" << m_count/6 << "v.x" << v.x() << "v.y" << v.y() << "v.z" << v.z() << "n.x" << n.x() << "n.y" << n.y() << "n.z" << n.z();
}

void Scene::clearView()
{
	sceneData.clear(); //Until Qt 5.6, this also released the memory used by the vector. From Qt 5.7, the capacity is preserved.
	sceneCount = 0;
}

void Scene::point(GLfloat x, GLfloat y, GLfloat z)
{
	QVector3D normal;
	normal = QVector3D::normal(QVector3D(1, 0, 0), QVector3D(0, 1, 0)); //This is a dummy function, normal always points in same direction
	add(QVector3D(x, y, z), normal);
}


