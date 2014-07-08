#ifndef GRAPH_POINT_H
#define GRAPH_POINT_H


#include <vector>
#include <bitset>
#include <queue>
#include <map>
#include "point3d.h"
#include "vector3d.h"

using namespace std;

class GraphPoint {
public:
	GraphPoint();

	Point3D* operator[](int index);

	void add(float x = 0, float y = 0, float z = 0, int r = 255, int g = 255, int b = 255, int a = 255);

	void addAdjacent(int indexA, int indexB);

	void resize(float scalar);

private:

	vector<Point3D *> vectorPoint;
	map< Point3D*, vector<Point3D *> > graph;

	void resizePoints(Point3D *head, Point3D *tail, float scalar);
	bool existAdjacent(int indexA, int indexB);
};

GraphPoint::GraphPoint()
{

}

Point3D*
GraphPoint::operator[](int index)
{
	return this->vectorPoint[index];
}

void
GraphPoint::add(float x, float y, float z, int r, int g, int b, int a)
{
	Point3D *point = new Point3D(x, y, z);
	point->setColor(r, g, b, a);

	this->vectorPoint.push_back(point);
	this->graph[point] = vector<Point3D *>();
}

void
GraphPoint::addAdjacent(int indexA, int indexB)
{
	if(!existAdjacent(indexA, indexB))
	{
		this->graph[vectorPoint[indexA]].push_back(vectorPoint[indexB]);
		this->graph[vectorPoint[indexB]].push_back(vectorPoint[indexA]);
	}
}

void 
GraphPoint::resize(float scalar)
{
	float minX, minY, minZ;
	float maxX, maxY, maxZ;
	float midX, midY, midZ;
	Point3D midPoint;

	for(unsigned int i = 0; i < vectorPoint.size(); i++)
	{
		if(i == 0)
		{
			minX = vectorPoint[i]->x;
			minY = vectorPoint[i]->y;
			minZ = vectorPoint[i]->z;

			maxX = vectorPoint[i]->x;
			maxY = vectorPoint[i]->y;
			maxZ = vectorPoint[i]->z;
		}

		if(vectorPoint[i]->x < minX)
			minX = vectorPoint[i]->x;

		if(vectorPoint[i]->x > maxX)
			maxX = vectorPoint[i]->x;

		if(vectorPoint[i]->y < minY)
			minY = vectorPoint[i]->y;

		if(vectorPoint[i]->y > maxY)
			maxY = vectorPoint[i]->y;

		if(vectorPoint[i]->z < minZ)
			minZ = vectorPoint[i]->z;

		if(vectorPoint[i]->z > maxZ)
			maxZ = vectorPoint[i]->z;
	}

	midX = (maxX + minX) / 2;
	midY = (maxY + minY) / 2;
	midZ = (maxZ + minZ) / 2;

	midPoint = Point3D(midX, midY, midZ);

	for(unsigned int i = 0; i < vectorPoint.size(); i++)
	{
		resizePoints(&midPoint, vectorPoint[i], scalar);
	}

	// map<Point3D *, bool> mapVisited;
	// map<Point3D *, bool> mapEnqueued;
	// queue<Point3D *> queuePoint;

	// Point3D *actualPoint;
	// queuePoint.push(vectorPoint[0]);
	// mapEnqueued[vectorPoint[0]] = true;

	// while(!queuePoint.empty())
	// {
	// 	actualPoint = queuePoint.front();
	// 	queuePoint.pop();

	// 	mapVisited[actualPoint] = true;

	// 	for(unsigned int i = 0; i < graph[actualPoint].size(); i++)
	// 	{
	// 		if(mapVisited[graph[actualPoint][i]] == false)
	// 		{
	// 			mapVisited[graph[actualPoint][i]] = true;

	// 			if(mapEnqueued[graph[actualPoint][i]] == false)
	// 			{
	// 				mapEnqueued[graph[actualPoint][i]] = true;
	// 				queuePoint.push(graph[actualPoint][i]);

	// 				resizePoints(actualPoint, graph[actualPoint][i], scalar);
	// 			}
	// 		}
	// 	}
	// }

	// for(unsigned int i = 0; i < vectorPoint.size(); i++)
	// {
	// 	cout << "i = " << i << ": ";
	// 	cout << "x: " << vectorPoint[i]->x << ", ";
	// 	cout << "y: " << vectorPoint[i]->y << ", ";
	// 	cout << "z: " << vectorPoint[i]->z << ", ";
	// 	cout << endl;
	// }
}

void
GraphPoint::resizePoints(Point3D *head, Point3D *tail, float scalar)
{
	Vector3D vector3d(*head, *tail);

	tail->x = (vector3d.x * scalar) + head->x;
	tail->y = (vector3d.y * scalar) + head->y;
	tail->z = (vector3d.z * scalar) + head->z;

	// tail->x = (vector3d.x + head->x) * scalar;
	// tail->y = (vector3d.y + head->y) * scalar;
	// tail->z = (vector3d.z + head->z) * scalar;
}

bool
GraphPoint::existAdjacent(int indexA, int indexB)
{
	for(unsigned int i = 0; i < graph[vectorPoint[indexA]].size(); i++)
	{
		if(graph[vectorPoint[indexA]][i] == vectorPoint[indexB])
		{
			return true;
		}
	}

	return false;
}

#endif