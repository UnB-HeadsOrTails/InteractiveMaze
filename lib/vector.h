#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <cmath>

using namespace std;

class Vector{
	public:
		friend ostream& operator<<	(ostream& os,const Vector  vector);
		

		Vector(const float x=0,const float y=0, const float z=0);
		float getX() 	const;
		float getY()	const;
		float getZ()	const;
		float length() const;

		Vector operator=(Vector vector);
		Vector operator+(Vector vector);
		Vector operator-(Vector vector);
		float  operator*( Vector vector);
		Vector operator*=( Vector vector); 
		Vector normalization() ;

	private:
		float x,y,z;	
};

#endif
