#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <cmath>

using namespace std;

class Vector{
	public:
		friend ostream& operator<<	(ostream& os,const Vector * vector);
		

		Vector(const float x=0,const float y=0, const float z=0);
		float getX() 	const;
		float getY()	const;
		float getZ()	const;
		float length() const;

		Vector* operator=(Vector *vector);
		Vector* add_vector(const Vector *vector) const ;
		Vector* subtract_vector(const Vector *vector) const;
    float scalar_product(const Vector *vector) const;
		Vector* vector_product(const Vector * vector)const ;
		Vector* normalization() const ;


	private:
		float x,y,z;	
};

#endif
