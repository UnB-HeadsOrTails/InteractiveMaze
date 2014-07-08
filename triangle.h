#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "point.h"
#include "drawable.h"

#include <GL/gl.h>

class Triangle : public Drawable {
public:
	Triangle(float x, float y, float z, float height, float width);
	virtual ~Triangle();

	void draw();

	float getX();
	void setX(float x);

	float getY();
	void setY(float y);

	float getZ();
	void setZ(float z);

	void setPosition(float x, float y, float z);

	

	void setDimension(float width, float height);
	void setHeight(float height);
	void setWidth(float width);

private:
	Point pointOne, pointTwo, pointThree;
	float x, y, z, height, width;

	void definePoints();
};

Triangle::Triangle(float x, float y, float z, float width, float height)
{
	setPosition(x, y, z);
	setDimension(width, height);
}

Triangle::~Triangle()
{

}

void
Triangle::draw()
{
	definePoints();
	
	glBegin(GL_TRIANGLES);
		glColor3d(1, 1, 1);
		this->pointOne.drawGlVertex3f();
		glColor3d(1, 0, 0);
		this->pointTwo.drawGlVertex3f();
		glColor3d(0, 1, 0);
		this->pointThree.drawGlVertex3f();
	glEnd();

	// glBegin(GL_LINES);
	// 	glColor3d(1, 1, 1);
	// 	this->pointOne.drawGlVertex3f();
	// 	glColor3d(1, 0, 0);
	// 	this->pointTwo.drawGlVertex3f();
	// glEnd();

	// glBegin(GL_LINES);
	// 	glColor3d(1, 0, 0);
	// 	this->pointTwo.drawGlVertex3f();
	// 	glColor3d(0, 1, 0);
	// 	this->pointThree.drawGlVertex3f();
	// glEnd();

	// glBegin(GL_LINES);
	// 	glColor3d(0, 1, 0);
	// 	this->pointThree.drawGlVertex3f();
	// 	glColor3d(1, 1, 1);
	// 	this->pointOne.drawGlVertex3f();
	// glEnd();

}

void 
Triangle::setPosition(float x, float y, float z)
{
	setX(x);
	setY(y);
	setZ(z);
}

float 
Triangle::getX()
{
	return this->x;
}

void 
Triangle::setX(float x)
{
	this->x = x;
}

float 
Triangle::getY()
{
	return this->y;
}

void 
Triangle::setY(float y)
{
	this->y = y;
}

float 
Triangle::getZ()
{
	return this->z;
}

void 
Triangle::setZ(float z)
{
	this->z = z;
}

void 
Triangle::setDimension(float width, float height)
{
	setHeight(height);
	setWidth(width);
}

void 
Triangle::setHeight(float height)
{
	this->height = height;
}

void 
Triangle::setWidth(float width)
{
	this->width = width;
}

void
Triangle::definePoints()
{
	this->pointOne.x = this->x;
	this->pointOne.y = this->y;
	this->pointOne.z = this->z;

	this->pointTwo = this->pointOne;
	this->pointTwo.y -= this->height;

	this->pointThree = this->pointTwo;

	this->pointTwo.x += this->width/2;
	this->pointThree.x -= this->width/2;
}

#endif