#ifndef MESH_H
#define MESH_H

#include <sstream>
#include <fstream>
#include <cstdio>
#include <cctype>
#include "point3d.h"
#include "vector3d.h"

#include <iostream>

using namespace std;

class Mesh : public Drawable {
public:
	const static int TRIANGLES = 0;
	const static int LINES = 1;

	Mesh();							//mesh *New_Mesh()
	virtual ~Mesh();				//int Del_Mesh(mesh *pmesh)

	void draw();					//int Render_Mesh(mesh *pmesh);
	void resize(float scalar);		//int Resize_Mesh(mesh *pmesh);
	void loadFile(string fileName);	//int Load_Mesh(mesh *pmesh, char *File_Name);

	void rotateX(float angleX);
	void rotateY(float angleY);
	void rotateZ(float angleZ);

	void setPosition(float x = 0, float y = 0, float z = 0);
	void incPosition(float x = 0, float y = 0, float z = 0);

	Point3D getMidPoint();
	Point3D getMinPoint();
	Point3D getMaxPoint();

	float getDeltaX();
	float getDeltaY();
	float getDeltaZ();

	void showPosition();
	void showDimensions();

	void resizeToScreen();

	void clear();

	void setType(int drawType);
private:
	vector<Point3D> vectorPoint;
	vector< vector<int> > vectorIndexFaces;

	bool haveColor;

	void (Mesh::*drawType)() = NULL;

	void drawLines();
	void drawTriangles();
	void resizePoints(Point3D *head, Point3D *tail, float scalar);

	void loadFileToStringStream(string fileName, stringstream &stringCin);
	void loadPoints(float x, float y, float z, int r = 255, int g = 255, int b = 255, int a = 255);
	void loadFaces(int v1, int v2, int v3);
};

Mesh::Mesh()
{
	this->haveColor = false;
	this->drawType = &Mesh::drawLines;
}

Mesh::~Mesh()
{
	
}
void
Mesh::draw()
{
	(this->*drawType)();
}

void
Mesh::resize(float scalar)
{
	Point3D midPoint;

	midPoint = getMidPoint();

	for(unsigned int i = 0; i < vectorPoint.size(); i++)
	{
		resizePoints(&midPoint, &vectorPoint[i], scalar);
	}
}

void
Mesh::loadFile(string fileName)
{
	ifstream file(fileName.c_str());

	if(!file.is_open())
	{
		cout << "Não foi possível abrir o aquivo!!!" << endl;
		exit(-1);
	}

	float x, y, z;

	string line;
	string trash;

	bool haveV = false, haveVN = false, haveVT = false;

	while(getline(file, line))
	{
		stringstream stream(line);

		if(line.substr(0, 2) == "v ")
		{
			stream >> trash >> x >> y >> z;
			loadPoints(x, y, z);
			haveV = true;
		}

		else if(line.substr(0,2) == "vn")
		{
			haveVN = true;
		}

		else if(line.substr(0,2) == "vt")
		{
			haveVT = true;
		}

		else if(line.substr(0,2) == "f ")
		{
			int v[3], n, t;
			char c_trash;

			stream >> trash;
			for(int i = 0; i < 3; i++)
			{
				if(haveV)
				{
					v[i] = 1;
					stream >> v[i];
					v[i]--;
				}

				stream >> c_trash;

				if(haveVN)
				{
					n = 1;
					stream >> n;
				}

				stream >> c_trash;

				if(haveVT)
				{
					t = 1;
					stream >> t;
				}
			}
			loadFaces(v[0], v[1], v[2]);
		}
	}
}

void
Mesh::rotateX(float angleX)
{
	float pi = 3.141592653589793;
	float radAngleX = angleX*pi/180.0;
	vector<Point3D> a = vectorPoint;
	vector<Point3D> b = vectorPoint;

	Point3D midPoint = getMidPoint();
	float midY = midPoint.y;
	float midZ = midPoint.z;

	for(unsigned int i = 0; i < a.size(); i++)
	{
		b[i].y = (a[i].y - midY) * cos(radAngleX) - (a[i].z - midZ) * sin(radAngleX) + midY;
		b[i].z = (a[i].z - midZ) * cos(radAngleX) + (a[i].y - midY) * sin(radAngleX) + midZ;
	}

	this->vectorPoint = b;
}

void
Mesh::rotateY(float angleY)
{
	float pi = 3.141592653589793;
	float radAngleY = angleY*pi/180.0;
	vector<Point3D> b = vectorPoint;
	vector<Point3D> c = vectorPoint;

	Point3D midPoint = getMidPoint();
	float midX = midPoint.x;
	float midZ = midPoint.z;

	for(unsigned int i = 0; i < b.size(); i++)
	{
		c[i].x = (b[i].x - midX) * cos(radAngleY) - (b[i].z - midZ) * sin(radAngleY) + midX;
		c[i].z = (b[i].z - midZ) * cos(radAngleY) + (b[i].x - midX) * sin(radAngleY) + midZ;
	}

	this->vectorPoint = c;
}

void
Mesh::rotateZ(float angleZ)
{
	float pi = 3.141592653589793;
	float radAngleZ = angleZ*pi/180.0;
	vector<Point3D> c = vectorPoint;
	vector<Point3D> d = vectorPoint;

	Point3D midPoint = getMidPoint();
	float midX = midPoint.x;
	float midY = midPoint.y;

	for(unsigned int i = 0; i < c.size(); i++)
	{
		d[i].x = (c[i].x - midX) * cos(radAngleZ) - (c[i].y - midY) * sin(radAngleZ) + midX;
		d[i].y = (c[i].y - midY) * cos(radAngleZ) + (c[i].x - midX) * sin(radAngleZ) + midY;
	}

	this->vectorPoint = d;
}

void
Mesh::setPosition(float x, float y, float z)
{
	Point3D midPoint, newPoint;
	Vector3D vector3d;

	midPoint = getMidPoint();
	newPoint = Point3D(x, y, z);
	vector3d = Vector3D(midPoint, newPoint);

	for(unsigned int i = 0; i < vectorPoint.size(); i++)
	{
		vectorPoint[i] = vector3d + vectorPoint[i];
	}
}

void
Mesh::incPosition(float x, float y, float z)
{
	Point3D midPoint, newPoint;
	Vector3D vector3d;

	newPoint = Point3D(x, y, z);
	midPoint = getMidPoint();
	newPoint = newPoint + midPoint;
	vector3d = Vector3D(midPoint, newPoint);

	for(unsigned int i = 0; i < vectorPoint.size(); i++)
	{
		vectorPoint[i] = vector3d + vectorPoint[i];
	}
}

float
Mesh::getDeltaX()
{
	Point3D maxPoint = getMaxPoint();
	Point3D minPoint = getMinPoint();

	return maxPoint.x - minPoint.x;
}

float
Mesh::getDeltaY()
{
	Point3D maxPoint = getMaxPoint();
	Point3D minPoint = getMinPoint();

	return maxPoint.y - minPoint.y;
}

float
Mesh::getDeltaZ()
{
	Point3D maxPoint = getMaxPoint();
	Point3D minPoint = getMinPoint();

	return maxPoint.z - minPoint.z;
}

void
Mesh::showPosition()
{
	Point3D midPoint = getMidPoint();
	cout << endl << "+----------showPosition----------+" << endl;
	cout << "midX: " << midPoint.x << endl;
	cout << "midY: " << midPoint.y << endl;
	cout << "midZ: " << midPoint.z << endl;
}

void
Mesh::showDimensions()
{
	cout << endl << "+----------showDimensions----------+" << endl;
	cout << "deltaX: " << getDeltaX() << endl;
	cout << "deltaY: " << getDeltaY() << endl;
	cout << "deltaZ: " << getDeltaZ() << endl;
}

void
Mesh::resizeToScreen()
{
	float dx, dy, dz, maior;

	dx = getDeltaX();
	dy = getDeltaY();
	dz = getDeltaZ();

	maior = dx > dy ? dx : dy;
	maior = maior > dz ? maior : dz;

	resize(2/maior);
}

void
Mesh::clear()
{
	this->vectorPoint.clear();
	this->vectorIndexFaces.clear();
}

void
Mesh::setType(int drawType)
{
	switch(drawType)
	{
		case TRIANGLES:
			this->drawType = &Mesh::drawTriangles;
			break;
		case LINES:
			this->drawType = &Mesh::drawLines;
			break;
	}
}

void
Mesh::drawLines()
{
	for(unsigned int i = 0; i < vectorIndexFaces.size(); i++)
	{
		glBegin(GL_LINES);
			this->vectorPoint[vectorIndexFaces[i][0]].drawGl();
			this->vectorPoint[vectorIndexFaces[i][1]].drawGl();
		glEnd();

		glBegin(GL_LINES);
			this->vectorPoint[vectorIndexFaces[i][0]].drawGl();
			this->vectorPoint[vectorIndexFaces[i][2]].drawGl();
		glEnd();

		glBegin(GL_LINES);
			this->vectorPoint[vectorIndexFaces[i][1]].drawGl();
			this->vectorPoint[vectorIndexFaces[i][2]].drawGl();
		glEnd();
	}
}

void
Mesh::drawTriangles()
{
	for(unsigned int i = 0; i < vectorIndexFaces.size(); i++)
	{
		glBegin(GL_TRIANGLES);
			this->vectorPoint[vectorIndexFaces[i][0]].drawGl();
			this->vectorPoint[vectorIndexFaces[i][1]].drawGl();
			this->vectorPoint[vectorIndexFaces[i][2]].drawGl();
		glEnd();
	}
}

void
Mesh::resizePoints(Point3D *head, Point3D *tail, float scalar)
{
	Vector3D vector3d(*head, *tail);

	vector3d *= scalar;
	*tail = vector3d + *head;
}

void
Mesh::loadFileToStringStream(string fileName, stringstream &stringCin)
{
	ifstream file(fileName.c_str());

	copy(istreambuf_iterator<char>(file),
	     istreambuf_iterator<char>(),
	     ostreambuf_iterator<char>(stringCin));
	file.close();
}

void
Mesh::loadPoints(float x, float y, float z, int r, int g, int b, int a)
{
	Point3D point(x, y, z);

	point.setColor(r, g, b, a);

	this->vectorPoint.push_back(point);
}

void
Mesh::loadFaces(int v1, int v2, int v3)
{
		vectorIndexFaces.push_back(vector<int>());
		vectorIndexFaces.back().push_back(v1);
		vectorIndexFaces.back().push_back(v2);
		vectorIndexFaces.back().push_back(v3);
}

Point3D
Mesh::getMidPoint()
{
	float minX, minY, minZ;
	float maxX, maxY, maxZ;
	float midX, midY, midZ;
	Point3D midPoint;

	for(unsigned int i = 0; i < vectorPoint.size(); i++)
	{
		if(i == 0)
		{
			minX = vectorPoint[i].x;
			minY = vectorPoint[i].y;
			minZ = vectorPoint[i].z;

			maxX = vectorPoint[i].x;
			maxY = vectorPoint[i].y;
			maxZ = vectorPoint[i].z;
		}

		if(vectorPoint[i].x < minX)
			minX = vectorPoint[i].x;

		if(vectorPoint[i].y < minY)
			minY = vectorPoint[i].y;

		if(vectorPoint[i].z < minZ)
			minZ = vectorPoint[i].z;

		if(vectorPoint[i].x > maxX)
			maxX = vectorPoint[i].x;
		if(vectorPoint[i].y > maxY)
			maxY = vectorPoint[i].y;
		if(vectorPoint[i].z > maxZ)
			maxZ = vectorPoint[i].z;
	}

	midX = (maxX + minX) / 2;
	midY = (maxY + minY) / 2;
	midZ = (maxZ + minZ) / 2;

	midPoint = Point3D(midX, midY, midZ);
	return midPoint;
}

Point3D
Mesh::getMinPoint()
{
	float minX, minY, minZ;
	Point3D minPoint;

	for(unsigned int i = 0; i < vectorPoint.size(); i++)
	{
		if(i == 0)
		{
			minX = vectorPoint[i].x;
			minY = vectorPoint[i].y;
			minZ = vectorPoint[i].z;
		}

		if(vectorPoint[i].x < minX)
			minX = vectorPoint[i].x;

		if(vectorPoint[i].y < minY)
			minY = vectorPoint[i].y;

		if(vectorPoint[i].z < minZ)
			minZ = vectorPoint[i].z;
	}

	minPoint = Point3D(minX, minY, minZ);
	return minPoint;
}


Point3D
Mesh::getMaxPoint()
{
	float maxX, maxY, maxZ;
	Point3D maxPoint;

	for(unsigned int i = 0; i < vectorPoint.size(); i++)
	{
		if(i == 0)
		{
			maxX = vectorPoint[i].x;
			maxY = vectorPoint[i].y;
			maxZ = vectorPoint[i].z;
		}
	}

	maxPoint = Point3D(maxX, maxY, maxZ);
	return maxPoint;
}

#endif