#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include "screen.h"
#include "triangle.h"
#include "pyramid.h"

using namespace std;

void pressArrowKey(SDL_Event event, float &velocityX, float &velocityY);
void moveTriangle(Triangle *triangle, float velocityX, float velocityY);

const float VELOCITY = 0.05;

int main()
{
	bool finish;
	Screen screen;
	SDL_Event sdlEvent;

	float velocityX = 0, velocityY = 0;

	Triangle *triangle = new Triangle(2, 0.5, 0.5, 0.25, 0.25);

	screen.addDrawable(triangle);

	screen.render();

	finish = false;
	while(!finish)
	{
		while(SDL_PollEvent(&sdlEvent))
		{
			if(sdlEvent.type == SDL_QUIT)
			{
				finish = true;
				break;
			}

			pressArrowKey(sdlEvent, velocityX, velocityY);
		}

		moveTriangle(triangle, velocityX, velocityY);

		screen.render();
		SDL_Delay(36);
	}

	delete triangle;

	return 0;
}


void moveTriangle(Triangle *triangle, float velocityX, float velocityY)
{
	triangle->setX(triangle->getX() + velocityX);
	triangle->setY(triangle->getY() + velocityY);
}

void pressArrowKey(SDL_Event sdlEvent, float &velocityX, float &velocityY)
{
	if(sdlEvent.key.keysym.sym == SDLK_UP)
	{
		if(sdlEvent.key.state == SDL_PRESSED)
			velocityY = VELOCITY;
		else
			velocityY = 0;
	}

	if(sdlEvent.key.keysym.sym == SDLK_DOWN)
	{
		if(sdlEvent.key.state == SDL_PRESSED)
			velocityY = -VELOCITY;
		else
			velocityY = 0;
	}

	if(sdlEvent.key.keysym.sym == SDLK_LEFT)
	{
		if(sdlEvent.key.state == SDL_PRESSED)
			velocityX = -VELOCITY;
		else
			velocityX = 0;
	}

	if(sdlEvent.key.keysym.sym == SDLK_RIGHT)
	{
		if(sdlEvent.key.state == SDL_PRESSED)
			velocityX = VELOCITY;
		else
			velocityX = 0;
	}
}