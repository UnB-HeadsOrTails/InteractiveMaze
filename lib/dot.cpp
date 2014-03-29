#include "dot.h"

    
ostream&
operator<<(ostream& os,const Dot dot)
{
 os << "Dot ["<<dot.getX() <<","<<dot.getY()<<","<<dot.getZ()<<"]";
  return  os ;
}

Dot::Dot(const float x,const float y, const float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

float 
Dot::getX()  const
{
	return this->x;
}
   
float
Dot::getY()  const
{
	return this->y;
}

float 
Dot::getZ()  const
{
	return this->z;
}

Dot
Dot::operator=(Dot dot)
{
	this->x = dot.getX();
	this->y = dot.getY();
	this->z = dot.getZ();
	return *this; 	
}
