#include "point_3d.h"

    
ostream&
operator<<(ostream& os,const Point3D point3d)
{
 os << "Point3D ["<<point3d.getX() <<","<<point3d.getY()<<","<<point3d.getZ()<<"]";
  return  os ;
}

Point3D::Point3D(const float x,const float y, const float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

float 
Point3D::getX()  const
{
	return this->x;
}
   
float
Point3D::getY()  const
{
	return this->y;
}

float 
Point3D::getZ()  const
{
	return this->z;
}

Point3D
Point3D::operator=(Point3D point3d)
{
	this->x = point3d.getX();
	this->y = point3d.getY();
	this->z = point3d.getZ();
	return *this; 	
}
