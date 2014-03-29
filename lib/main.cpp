
#include <iostream>
#include "vector.h"
#include "dot.h"

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

	Dot d1,d2;

  d1 = Dot(1,2,3);
	d2 = d1;

	cout << "Dot 1 = "<< d1 << endl 
			 <<"Dot 2 = "<< d2 << endl;
}

