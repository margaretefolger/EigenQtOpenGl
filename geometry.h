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

	/*! \function matrix3dToQString
	*  \brief formatted output of Matrix3dobject values
	*/
	//QString matrix3dToQString(Eigen::Matrix<double,3,3>*);
	QString matrix3dToQString(Matrix3d x);

	/*! \function makeMatrix3dListElement
	*  \brief Create a Matrix3d and push it to the Matrix vector
	*/
	QString makeMatrix3dListElement(double zeroZero, double oneZero, double twoZero,
					double zeroOne, double oneOne, double twoOne,
					double zeroTwo, double oneTwo, double twoTwo);
};

#endif // GEOMETRY_H
