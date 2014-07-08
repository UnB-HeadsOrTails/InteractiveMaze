#ifndef POLIGONO_H
#define POLIGONO_H

#include <map>
#include <vector>
#include <algorithm>
#include "point.h"
#include "vector.h"

using namespace std;

class Poligono {

public:

	Poligono();
	
	Point& operator[](int indice);
	
	double getAngulo(Point pointOrigem, Point pointA, Point pointB);
	double getAngulo(int indicePointOrigem, int indicePointA, int indicePointB);
	
	Vector getVector(Point head, Point tail);
	Vector getVector(int indiceHead, int indiceTail);
	
	void addPoint(float x, float y, float z);
	void removePoint(Point point);
	void removePoint(int indice);
	
	int numPoints();
	
	
	vector<Point> getPoints();

private:

	map< Point, vector<Point> > grafo;
	vector<Point> points;
	
};

Poligono::Poligono()
{
	
}

Point&
Poligono::operator[](int indice)
{
	return points[indice];
}

double
Poligono::getAngulo(Point pointOrigem, Point pointA, Point pointB)
{	
	Vector vectorA, vectorB;
	vectorA = getVector(pointOrigem, pointA);
	vectorB = getVector(pointOrigem, pointB);
	
	return vectorA.scalarProduct(vectorB);
}

double 
Poligono::getAngulo(int indicePointOrigem, int indicePointA, int indicePointB)
{
	return getAngulo(points[indicePointOrigem], points[indicePointA], points[indicePointB]);
}

Vector 
Poligono::getVector(Point head, Point tail)
{
	return Vector(head, tail);
}

Vector 
Poligono::getVector(int indiceHead, int indiceTail)
{
	return getVector(points[indiceHead], points[indiceTail]);
}

void
Poligono::addPoint(float x, float y, float z)
{
	points.push_back(Point(x, y, z));
}

void
Poligono::removePoint(Point point)
{
	for(unsigned int i = 0; i < points.size(); i++)
	{
		if(points[i] == point)
		{
			removePoint(i);
			break;
		}
	}
}

void
Poligono::removePoint(int indice)
{
	points.erase(points.begin() + indice);
}

int
Poligono::numPoints()
{
	return points.size();
}

vector<Point>
Poligono::getPoints()
{
	return points;
}

#endif















