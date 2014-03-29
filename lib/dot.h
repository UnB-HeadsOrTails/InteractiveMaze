#ifndef DOT_H		
#define DOT_H

#include <iostream>
using namespace std;

class Dot{
	public:
    friend ostream& operator<<  (ostream& os,const Dot dot);

    Dot(const float x=0,const float y=0, const float z=0);
    float getX()  const;
    float getY()  const;
    float getZ()  const;
		
		Dot operator=(Dot dot);
  private:
    float x,y,z;

};

#endif
