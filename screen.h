#ifndef SCREEN_H
#define SCREEN_H

#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <list>

#include "drawable.h"

using namespace std;

class Screen {
public:
	Screen();

	void render();

	void addDrawable(Drawable *drawable);
	void removeDrawable(Drawable *drawable);

private:
	void initGL();
	int setViewport(int width, int height);
	void setAttributesSDL_GL();

	SDL_Renderer *displayRenderer;
	SDL_Window* displayWindow;
	int flags;

	list<Drawable *> drawableList;
};

Screen::Screen()
{
	SDL_Init(SDL_INIT_VIDEO);
	this->flags = SDL_WINDOW_OPENGL;
	atexit(SDL_Quit);

	setAttributesSDL_GL();

    SDL_CreateWindowAndRenderer(800, 600, flags, &displayWindow, &displayRenderer);

    SDL_GL_CreateContext(displayWindow);

    initGL();

    setViewport(800, 600);
}

void
Screen::render()
{
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
 
    //glLoadIdentity();
    //glTranslatef( 0.0f, 0.0f, -6.0f );
 
    list<Drawable *>::iterator it;
    for(it = drawableList.begin(); it != drawableList.end(); it++)
    {
    	(*it)->draw();
    }

	SDL_GL_SwapWindow(displayWindow);
}

void
Screen::addDrawable(Drawable *drawable)
{
	drawableList.push_back(drawable);
}

void
Screen::removeDrawable(Drawable *drawable)
{
	drawableList.remove(drawable);
}

void
Screen::initGL()
{
	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
}

int
Screen::setViewport( int width, int height )
{

    GLfloat ratio;
 
    if ( height == 0 ) {
        height = 1;
    }
 
    ratio = ( GLfloat )width / ( GLfloat )height;
 
    glViewport( 0, 0, ( GLsizei )width, ( GLsizei )height );
 
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );
 
    gluPerspective( 45.0f, ratio, 0.1f, 100.0f );
 
    glMatrixMode( GL_MODELVIEW );
 
    glLoadIdentity( );
 
    return 1;
}

void
Screen::setAttributesSDL_GL()
{
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
}

#endif