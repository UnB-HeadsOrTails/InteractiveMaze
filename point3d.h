#ifndef POINT3D_H
#define POINT3D_H

#include <GL/gl.h>
#include <GL/glu.h>

#include "color.h"

class Point3D {

public:

	Point3D(float x = 0, float y = 0, float z = 0);

	void operator=(const Point3D& p);
	bool operator==(const Point3D& p) const;
	
	Point3D operator+(const Point3D& p) const;
	Point3D operator-(const Point3D& p) const;
	
	void drawGl();
	void drawGlColor3d();
	void drawGlVertex3f();

	void setColor(int r, int g, int b, int a);
	Color getColor();


	float x, y, z;

private:
	Color color;
};

Point3D::Point3D(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

void
Point3D::operator=(const Point3D& p)
{
	this->x = p.x;
	this->y = p.y;
	this->z = p.z;
}

bool
Point3D::operator==(const Point3D& p) const
{
	return ( (this->x == p.x) && (this->y == p.y) && (this->z == p.z) );
}

Point3D
Point3D::operator+(const Point3D& p) const
{
	return Point3D(this->x + p.x, this->y + p.y, this->z + p.z);
}

Point3D
Point3D::operator-(const Point3D& p) const
{
	return Point3D(this->x - p.x, this->y - p.y, this->z - p.z);
}

void
Point3D::drawGl()
{
	drawGlColor3d();
	drawGlVertex3f();
}

void
Point3D::drawGlColor3d()
{
	glColor3d(this->color.r, this->color.g, this->color.b);
}

void
Point3D::drawGlVertex3f()
{
	glVertex3f(this->x, this->y, this->z);
}

void
Point3D::setColor(int r, int g, int b, int a)
{
	this->color.r = r;
	this->color.g = g;
	this->color.b = b;
	this->color.a = a;
}

Color
Point3D::getColor()
{
	return this->color;
}

#endif