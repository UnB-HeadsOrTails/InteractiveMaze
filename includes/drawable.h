#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "game_object.h"

class Drawable : public GameObject {
public:
	virtual ~Drawable();

	virtual void draw() = 0;
};

#endif