/*! \file  geometry.h
*  \brief geometric elements and calculations, using Eigen
*  \author Gernot Stangl
*/

#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <QObject>
#include <QDebug>
#include <Eigen/Dense>
#include <vector>

using namespace Eigen;

/*! \class Geometry
* \brief Geometric manipulations
*/
class Geometry : public QObject {
	Q_OBJECT
public:
	Matrix3d myMatrix;
	std::vector<Matrix3d> matrix3dList;
	std::vector<Vector3d> vector3dList;
	//TODO: write vector that uses template for all Eigen::Matrix subclasses

	/*! \function Geometry
	*  \brief Geometry constructor
	*/
	Geometry(QObject *_parent);

	//TODO: write destructor

	/*! \function matrixBaseToQString
	*  \brief formatted output of MatrixBase object values
	*/
	template<typename Derived>
	QString matrixBaseToQString(const Eigen::MatrixBase<Derived>& x);

	/*! \function makeMatrix3dListElement
	*  \brief Create a Matrix3d and push it to the Matrix vector
	*/
	QString makeMatrix3dListElement(double zeroZero, double oneZero, double twoZero,
					double zeroOne, double oneOne, double twoOne,
					double zeroTwo, double oneTwo, double twoTwo);

	/*! \function matrix3dToQString
	*  \brief formatted output of Matrix3dobject values
	*/
	//QString matrix3dToQString(Eigen::Matrix<double,3,3>*);
	QString matrix3dToQString(Matrix3d x);

	/*! \function makeVector3dListElement
	*  \brief Create a Vector3d and push it to the Vector(class in Eigen) vector(container in c++)
	*/
	QString makeVector3dListElement(double zeroZero, double oneZero, double twoZero);

	/*! \function vector3dAngleCosine
	*  \brief Take two vectors, return the cosine of angle between vectors
	*/
	double vector3dAngleCosine(Vector3d theFirst, Vector3d theSecond);

	/*! \function vector3dProjection
	*  \brief Take a line vector and a projection vector, return the result vector
	*  \brief that is orthogonal to the line vector
	*/
	Vector3d vector3dProjection(Vector3d theLine, Vector3d theProj);

};

#endif // GEOMETRY_H
