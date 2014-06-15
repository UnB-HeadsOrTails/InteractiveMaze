#include  <iostream>
#include "vector.h"
#include "point_3d.h"

using namespace std;

int main(){
	Vector v1(1,2,3),v2,v3;
	Vector v4;

	v2 = v1;
	cout <<	"V1 = " << v1 << endl;
	cout <<	"V2 = " <<	v2 << endl;
	
	v3 = v1 + v2;
	cout << "v3 = "	<<	v3 << endl;
	cout << "v3.length = " << v3.length()<<endl;

	v4 = v3 - v1;
	cout << "v4 = "<< v4 << endl;
	

	v3 = v3.normalization();
	cout <<	"V3 normal = "	<< v3 << endl;
	cout << "v3 normal.length =  "<< v3.length() << endl;
  
	cout << "Scalar product: v3 * v1 =  " << v3*v1 << endl;


  v4 = Vector(1,2,3);
  Vector v5 = Vector(3,1,2);
  Vector v6 = v4 *= v5;
	
	cout << "Vectorial Product:"<<endl;
  cout  << "V4 = "<< v4 << endl
        << "V5 = "<< v5 << endl
        << "V6 = "<< v6 << endl;

	Point3D p1, p2;

  p1 = Point3D(1,2,3);
	 p2 = p1;

	cout << "Point3D 1 = "<< p1 << endl 
			 <<"Point3D 2 = "<<  p2 << endl;
}

