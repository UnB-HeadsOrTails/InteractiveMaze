#ifndef GRAPHIC_DRIVER_H
#define GRAPHIC_DRIVER_H

class GraphicDriver {
public:
	GraphicDriver(int width = 800, int height = 600);
	~GraphicDriver();

	void initGL();
	int setViewPort(int width, int height);

	void initRender();
	void displayRender();

private:
	SDL_Window* window;
    SDL_Renderer* render;
    int flags;
};

#endif