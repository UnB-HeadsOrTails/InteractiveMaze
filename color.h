#ifndef COLOR_H
#define COLOR_H

class Color {
public:
	Color(int r = 255, int g = 255, int b = 255, int a = 255);

	int r, g, b, a;
};

Color::Color(int r, int g, int b, int a)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}


#endif