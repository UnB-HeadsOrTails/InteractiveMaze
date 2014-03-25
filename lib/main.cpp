#include "vector.h"

int main(){
	Vector *v1,*v2,*v3;

	v1 =  new Vector(1,2,3);
	v2 = v1;
	cout <<	"V1 =" << 	v1 << endl;
	cout <<	"V2 =" <<	v2 << endl;

	v3 = v1->add_vector(v2);
	
	cout << "length: v1 +v2 ="	<<	v3->length() << endl;
 
	v3 = v1->subtract_vector(v2);

	cout <<	"lenght: v1 - v2 ="	<<	v3->length() << endl;

	v3 = new Vector(4,4,4);
	cout << "V3 = "	<< v3 << endl;

	v3 = v3->normalization();

	cout <<	"V3 normal = "	<< v3 << endl;

  cout << "Scalar product: " << v3->scalar_product(v1) << endl;
}
