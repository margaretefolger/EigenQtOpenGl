/*! \file  geometry.h
*  \brief geometric elements and calculations, using Eigen
*  \author Gernot Stangl
*/

#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <QObject>
#include <Eigen/Dense>

/*! \class Geometry
* \brief Geometric manipulations
*/
class Geometry : public QObject {
	Q_OBJECT
public:
	/*! \function Geometry
	*  \brief Geometry constructor
	*/
	Geometry(QObject *_parent);

	void testGeometry();
};

#endif // GEOMETRY_H
