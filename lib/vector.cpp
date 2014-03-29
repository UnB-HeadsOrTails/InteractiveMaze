#include "vector.h"
#include <cmath>


ostream& 
operator<< (ostream& os,const Vector  vector)
{
	os << "Vector["<<vector.getX() <<","<<vector.getY()<<","<<vector.getZ()<<"]";
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

float 
Vector::length() const
{
	return sqrt( this->getX()*this->getX() + this->getY()*this->getY() + this->getZ()*this->getZ()   ); 
}

Vector
Vector::operator=(Vector vector){
	this->x = vector.getX();
	this->y = vector.getY();
	this->z = vector.getZ();
	return *this;
}

Vector 
Vector::operator+(Vector vector){
	return Vector(this->getX()+vector.getX(),this->getY()+vector.getY(),this->getZ()+vector.getZ());
}
Vector
Vector::operator-(Vector vector){
	return Vector(this->getX()-vector.getX(),this->getY()-vector.getY(),this->getZ()-vector.getZ()); 
}

Vector 
Vector::normalization()
{
	float length = this->length();
	return  Vector(this->getX()/length,this->getY()/length,this->getZ()/length);
}



//scalar product
float
Vector::operator*( Vector vector)
{
  return (this->getX()*vector.getX()) + (this->getY()*vector.getY()) + (this->getZ()*vector.getZ());
}


//vectorial product
Vector
Vector::operator*=( Vector vector) 
{
  return Vector(
            ( this->getZ() * vector.getY() - this->getY()*vector.getZ()),
            ( this->getX() * vector.getZ() - this->getZ()*vector.getX()),
            ( this->getY() * vector.getX() - this->getX()*vector.getY()));
}

