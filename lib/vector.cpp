#include "vector.h"
#include <cmath>
ostream& 
operator<< (ostream& os,const Vector  *vector)
{
	os << "Vector["<<vector->getX() <<","<<vector->getY()<<","<<vector->getZ()<<"]";
	return 	os ;
}

Vector::Vector(const float x,const float y, const float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

float
Vector::getX() const 
{
	return this->x;
}

float
Vector::getY() const 
{
	return this->y;
}

float
Vector::getZ() const 
{
	return this->z;
}


Vector*
Vector::operator=(Vector * vector){
	return vector;
}

Vector* 
Vector::add_vector(const Vector *vector) const
{
	return new Vector(this->getX()+vector->getX(),this->getY()+vector->getY(),this->getZ()+vector->getZ());
}

Vector* 
Vector::subtract_vector(const Vector *vector) const
{

	return new Vector(this->getX()-vector->getX(),this->getY()-vector->getY(),this->getZ()-vector->getZ());
}

float 
Vector::length() const
{
	return sqrt( this->getX()*this->getX() + this->getY()*this->getY() + this->getZ()*this->getZ()   ); 
}

Vector* 
Vector::normalization() const
{
	float length = this->length();
	return new Vector(this->getX()/length,this->getY()/length,this->getZ()/length);
}

float
Vector::scalar_product(const Vector *vector) const
{
  return (this->getX()*vector->getX()) + (this->getY()*vector->getY()) + (this->getZ()*vector->getZ());
}


