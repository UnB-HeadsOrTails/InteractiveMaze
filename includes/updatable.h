#ifndef UPDATABLE_H
#define UPDATABLE_H

#include "game_object.h"

class Updatable : public GameObject {
public:
	virtual ~Updatable();

	virtual void update() = 0;
};

#endif