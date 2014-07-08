#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <cmath>
#include "point3d.h"

#include <iostream>
#include <cstdio>
using namespace std;

class Vector3D : public Point3D {

public:

	Vector3D(float x = 0, float y = 0, float z = 0);
	Vector3D(Point3D point);
	Vector3D(Point3D head, Point3D tail);
	
	void operator*=(float scalar);
	float operator*(const Vector3D& vector) const;
	
	double magnitude();

	Vector3D vectorProduct(Vector3D vector);
	Vector3D vectorProduct(Point3D point);
	
	double scalarProduct(Vector3D vector);
};

Vector3D::Vector3D(float x, float y, float z) : Point3D(x, y, z)
{

}

Vector3D::Vector3D(Point3D point) : Point3D(point.x, point.y, point.z)
{

}

Vector3D::Vector3D(Point3D head, Point3D tail) : Point3D(tail.x - head.x, tail.y - head.y, tail.z - head.z)
{

}

void
Vector3D::operator*=(float scalar)
{
	this->x *= scalar;
	this->y *= scalar;
	this->z *= scalar;
}

float
Vector3D::operator*(const Vector3D& vector) const
{
	return (this->x * vector.x) + (this->y * vector.y) + (this->z * vector.z);
}

double
Vector3D::magnitude()
{
	return sqrt( (this->x * this->x) + (this->y * this->y) + (this->z * this->z) );
}

Vector3D
Vector3D::vectorProduct(Vector3D vector)
{
	Vector3D vectorial;
		
	vectorial.x = (this->y * vector.z) - (this->z * vector.y);
	vectorial.y = (this->x * vector.z) - (this->z * vector.x);
	vectorial.z = (this->x * vector.y) - (this->y * vector.x);
	
	return vectorial;
}

Vector3D
Vector3D::vectorProduct(Point3D point)
{
	Vector3D vector(point);
	return vectorProduct(vector);
}

double
Vector3D::scalarProduct(Vector3D vector)
{
	double cosTeta;
	
	cosTeta = (double)((*this) * vector) / (double)(this->magnitude() * vector.magnitude());
	
	return acos(cosTeta) * 180.0 / 3.14159265;
}

#endif
















