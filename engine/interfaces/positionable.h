#ifndef POSITIONABLE_H
#define POSITIONABLE_H

#include "game_object.h"
#include ""

class Positionable : public GameObject {
public:
	virtual Point3D getPoint3D() = 0;
	virtual int getWidth() = 0;
	virtual int getHeith() = 0;
};

#endif