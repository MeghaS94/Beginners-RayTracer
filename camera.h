#ifndef CAMERAH
#define CAMERAH

#include "ray.h"

class camera {
	public :
		vec3 lower_left_corner; //establish a point of reference
		vec3 horizontal;		//positive x -> double it because you will be multiplying it with a floating point number
		vec3 vertical;			//positive y 
		vec3 origin;			//camera postion
		
		camera()
		{
			lower_left_corner = vec3(-2.0, -1.0, -1.0); 
			horizontal = vec3(4.0, 0.0, 0.0);			  
			vertical = vec3(0.0, 2.0, 0.0);			   
			origin = vec3(0.0, 0.0, 0.0);				  
		}
		ray getRayAtPoint(float u, float v) 
			{ return ray(origin, lower_left_corner + u*horizontal + v*vertical - origin /*in case origin is no zero*/); }
};

#endif