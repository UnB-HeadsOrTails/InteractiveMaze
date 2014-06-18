#ifndef DRAW_MANAGER_H
#define DRAW_MANAGER_H

#include <GL/glew.h>
#include <list>

#include "drawable.h"

class DrawableManager {
public:
	DrawableManager();

	void addDrawable(Drawable *drawable);
	void removeDrawable(Drawable *drawable);

	void run();

	GLuint initShader();

private:
    void criarVertexArray();
    
	Shader shaders[2];
	GLuint VBO, IBO, vertexArrayID;
	list<Drawable *> drawableList;
};

#endif