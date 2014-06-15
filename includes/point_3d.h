#ifndef POINT_3D_H		
#define POINT_3D_H

#include <iostream>
using namespace std;

class Point3D{
public:
    friend ostream& operator<<(ostream& os,const Point3D Point3D);

    Point3D(const float x=0,const float y=0, const float z=0);
    float getX() const;
    float getY() const;
    float getZ() const;
		
	Point3D operator=(Point3D dot);
 
private:
    float x,y,z;

};

#endif
