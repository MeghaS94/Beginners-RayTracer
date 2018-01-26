#ifndef HITABLEH
#define HITABLEH

#include "ray.h"

class material;

struct hit_record{
	float t;
	vec3 position;
	vec3 normal;
	material *mat_ptr;
};

//hitable - an object in the scene that you can hit.
// abstract class
class hitable {
	public :
		virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0;
};

#endif