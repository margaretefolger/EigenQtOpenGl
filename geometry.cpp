/*! \file  geometry.cpp
*  \brief geometric elements and calculations, using Eigen
*  \author Gernot Stangl
*/

#ifndef GEOMETRY
	#define GEOMETRY
	#include "geometry.h"
#endif

Geometry::Geometry(QObject *_parent) {

}
template<typename Derived>
QString Geometry::matrixBaseToQString(const Eigen::MatrixBase<Derived> &x) {
	QString theString;
	for (int j = 0; j < x.cols(); j++) {
		for (int i = 0; i < x.rows(); i++) {
			//qDebug() << "Matrix["<< j << "," << i <<"] =" << x.coeff(j,i);
			//theString += x.coeff(j,i);
			QTextStream(&theString) << x.coeff(i,j) << " ";
		}
		QTextStream(&theString) << "\n";
	}
	return theString;
}

//QString Geometry::matrix3dToQString(Eigen::Matrix<double,3,3>*) {
QString Geometry::matrix3dToQString(Matrix3d x) {
	QString theString;
	for (int j = 0; j < x.cols(); j++) {
		for (int i = 0; i < x.rows(); i++) {
			//qDebug() << "Matrix["<< j << "," << i <<"] =" << x.coeff(j,i);
			//theString += x.coeff(j,i);
			QTextStream(&theString) << x.coeff(i,j) << " ";
		}
		QTextStream(&theString) << "\n";
	}
	return theString;
}

QString Geometry::makeMatrix3dListElement(double zeroZero, double oneZero, double twoZero,
					  double zeroOne, double oneOne, double twoOne,
					  double zeroTwo, double oneTwo, double twoTwo) {
	Matrix3d theMatrix;
	//myMatrix.resize(3,3);
	theMatrix(0,0) = zeroZero;
	theMatrix(1,0) = oneZero;
	theMatrix(2,0) = twoZero;
	theMatrix(0,1) = zeroOne;
	theMatrix(1,1) = oneOne;
	theMatrix(2,1) = twoOne;
	theMatrix(0,2) = zeroTwo;
	theMatrix(1,2) = oneTwo;
	theMatrix(2,2) = twoTwo;
	matrix3dList.push_back(theMatrix);
	QString theString = matrixBaseToQString(theMatrix);

	/* //write current matrix3dList
	for(std::vector<Matrix3d>::const_iterator iter = matrix3dList.begin(); iter != matrix3dList.end(); ++iter) {
		QString someString = matrix3dToQString(*iter);
		qDebug() << someString << "makeMatrix3dListElement";
	}
	*/


	//std::vector<Matrix3d *>::const_iterator iter = matrix3dList.begin();
	//Eigen::Matrix<double,3,3>* iterMatrix = *iter; //this works!
	//qDebug() << (*iter)->coeff(0,0);
	//double theDouble = (*iter)->coeff(0,0);
	//QString someString = matrix3dToQString(iterMatrix);
	//qDebug() << someString << "makeMatrix3dListElement";
	/*
	someString = matrix3dToQString(*iter);
	someString = matrix3dToQString(matrix3dList.at(0));
	someString = matrix3dToQString(matrix3dList[0]);
	qDebug() << "Size" << matrix3dList.size();
	qDebug() << matrix3dList[0]->coeff(0,0);
	*/
	return theString;
}

QString Geometry::makeVector3dListElement(double zeroZero, double oneZero, double twoZero) {
	Vector3d theVector;
	theVector[0] = zeroZero;
	theVector[1] = oneZero;
	theVector[2] = twoZero;
	vector3dList.push_back(theVector);
	QString theString = matrixBaseToQString(theVector);
	return theString;
}

double Geometry::vector3dAngleCosine(Vector3d theFirst, Vector3d theSecond) {
	double cosTheta = (theFirst.dot(theSecond))/(sqrt(theFirst.dot(theFirst)) * sqrt(theSecond.dot(theSecond)));
	return cosTheta;
}

Vector3d Geometry::vector3dProjection(Vector3d theLine, Vector3d theProj) {
	double tempScalar3d;
	Vector3d theResult;
	tempScalar3d = theProj.dot(theLine)/theLine.dot(theLine);
	theResult = theLine * tempScalar3d;
	return theResult;
}


