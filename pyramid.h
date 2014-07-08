#ifndef PYRAMID_H
#define PYRAMID_H

#include <GL/gl.h>

#include "point.h"
#include "drawable.h"

class Pyramid : public Drawable {
public:
	Pyramid(Point top, Point baseLeftBottom, Point baseLeftTop, Point baseRightBottom, Point baseRightTop)
	{
		this->top = top;
		this->baseLeftBottom = baseLeftBottom;
		this->baseLeftTop = baseLeftTop;
		this->baseRightBottom = baseRightBottom;
		this->baseRightTop = baseRightTop;
	}

	virtual ~Pyramid()
	{

	}

	void draw()
	{
		glBegin(GL_TRIANGLES);
			glColor3d(1, 1, 1);
			top.drawGlVertex3f();
			glColor3d(1, 0, 0);
			baseLeftBottom.drawGlVertex3f();
			glColor3d(0, 1, 0);
			baseRightBottom.drawGlVertex3f();
    	glEnd();

    	glBegin(GL_TRIANGLES);
			glColor3d(1, 1, 1);
			top.drawGlVertex3f();
			glColor3d(1, 0, 0);
			baseLeftBottom.drawGlVertex3f();
			glColor3d(0, 1, 0);
			baseLeftTop.drawGlVertex3f();
    	glEnd();

    	glBegin(GL_TRIANGLES);
			glColor3d(1, 1, 1);
			top.drawGlVertex3f();
			glColor3d(1, 0, 0);
			baseRightTop.drawGlVertex3f();
			glColor3d(0, 1, 0);
			baseLeftTop.drawGlVertex3f();
    	glEnd();
	}

	Point top, baseLeftBottom, baseLeftTop, baseRightBottom, baseRightTop;
};

#endif