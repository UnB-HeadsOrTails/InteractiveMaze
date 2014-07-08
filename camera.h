#ifndef CAMERA_H
#define CAMERA_H

#include "point3d.h"
#include "vector3d.h"

class Camera {
public:
	Camera();

	void rotate(float x = 0, float y = 0, float z = 0);
	void incPosition(float x = 0, float y = 0, float z = 0);

	void moveFrontAndBack(float velocity);
	void rotateRightAndLeft(float velocity);

	Point3D pointEye;
	Point3D pointReference;
	Point3D pointUp;

private:
	void resetEye();
};

Camera::Camera()
{
	this->pointEye = Point3D(0, 0, 0);
	this->pointReference = Point3D(0, 0, -1);
	this->pointUp = Point3D(0, 1, 0);

	this->pointEye.x = 0;
	this->pointEye.z = 0;
	this->pointEye.y = 0;

	this->pointReference.x = this->pointEye.x;
	this->pointReference.y = this->pointEye.y;
	this->pointReference.z = this->pointEye.z - 0.1;

	this->pointUp.x = this->pointEye.x;
	this->pointUp.y = this->pointEye.y + 1;
	this->pointUp.z = this->pointEye.z;

	gluLookAt(pointEye.x, pointEye.y, pointEye.z, 
		      pointReference.x, pointReference.y, pointReference.z, 
		      pointUp.x, pointUp.y, pointUp.z);
}

void
Camera::moveFrontAndBack(float velocity)
{
	Vector3D vector3d(this->pointEye, this->pointReference);
	vector3d *= 1 / vector3d.magnitude();
	vector3d *= velocity;

	if(velocity != 0)
	{
		// cout << endl << "+-------------moveFrontAndBack--------------+" << endl;
		// cout << "pointEye.x: " << this->pointEye.x << endl;
		// cout << "pointEye.y: " << this->pointEye.y << endl;
		// cout << "pointEye.z: " << this->pointEye.z << endl;
		// cout << "pointReference.x: " << this->pointReference.x << endl;
		// cout << "vector3d.x: " << vector3d.x << endl;
		// cout << "vector3d.y: " << vector3d.y << endl;
		// cout << "vector3d.z: " << vector3d.z << endl;

		this->pointEye.x += vector3d.x;
		this->pointEye.y += vector3d.y;
		this->pointEye.z += vector3d.z;

		this->pointReference.x = this->pointEye.x;
		this->pointReference.y = this->pointEye.y;
		this->pointReference.z = this->pointEye.z - 0.1;
	}

	gluLookAt(vector3d.x, vector3d.y, vector3d.z,
		      vector3d.x, vector3d.y, vector3d.z - 0.1,
		      0, 1, 0);
}

void
Camera::rotateRightAndLeft(float velocity)
{
	this->pointReference.x += velocity;

	if(velocity != 0)
	{
		// cout << endl << "+-------------rotateRightAndLeft--------------+" << endl;
		// cout << "pointEye.x: " << this->pointEye.x << endl;
		// cout << "pointEye.y: " << this->pointEye.y << endl;
		// cout << "pointEye.z: " << this->pointEye.z << endl;
		// cout << "pointReference.x: " << this->pointReference.x << endl;
	}

	this->pointUp.x = 0;
	this->pointUp.y = 1;
	this->pointUp.z = 0;

	gluLookAt(0, 0, 0, 
		      velocity, 0, -0.1, 
		      0, 1, 0);
}

void
Camera::incPosition(float x, float y, float)
{
	this->pointEye.x = 0;
	this->pointEye.z = -y;
	this->pointEye.y = 0;

	this->pointReference.x = this->pointEye.x + x;
	this->pointReference.y = this->pointEye.y;
	this->pointReference.z = this->pointEye.z - 0.1;

	this->pointUp.x = 0;
	this->pointUp.y = 1;
	this->pointUp.z = 0;

	gluLookAt(pointEye.x, pointEye.y, pointEye.z, 
		      pointReference.x, pointReference.y, pointReference.z, 
		      pointUp.x, pointUp.y, pointUp.z);

	// gluLookAt(0, x, y, 0, 0, -1, 0, 1, 0);
}

void
Camera::rotate(float x, float y, float z)
{
	pointEye.x = y;
	pointEye.y = x;
	pointEye.z = z;
	gluLookAt(pointEye.x, pointEye.y, pointEye.z, 
		      pointReference.x, pointReference.y, pointReference.z, 
		      pointUp.x, pointUp.y, pointUp.z);
	// gluLookAt(y, x, z, 0, 0, -1, z, 1, 0);
}

void
Camera::resetEye()
{
	this->pointEye.x = 0;
	this->pointEye.y = 0;
	this->pointEye.z = 0;
}

#endif