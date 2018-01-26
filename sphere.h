#ifndef SPHEREH
#define SPHEREH

#include "hitable.h"
class material;

class sphere : public hitable
{
	public :
		vec3 center;
		float radius;
		material *mat_ptr;
		sphere() {}
		sphere(vec3 cen, float r, material *m) : center(cen), radius(r), mat_ptr(m) {};
		//hit_record : record the position where it(object) was hit.
		virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec ) const;
};

bool sphere::hit(const ray& r, float t_min, float t_max, hit_record& rec ) const
{
	//check if a ray r hit a sphere with center c and radius r
	//any point on the ray from A to B --> A + tB
	//to check if the ray intersects the sphere with center C --> dot( (A+tB - C)(A+tB - C) ) = R*R
	//simplifying that, quadratic eq : t*t*dot(B,B) + 2*t*dot(A-C,A-C) + dot(C,C) = R*R
	vec3 oc = r.origin() - center;
	float a = dot(r.direction(), r.direction());
	float b = dot(r.origin()-center, r.direction()); //
	float c = dot(oc, oc) - radius*radius;
	float discriminant = b*b - a*c;
	//if you hit the sphre, it returns the value of t on the ray from camera to the hit point on the sphere.
	if (discriminant > 0)
	{
		float temp = (-b - sqrt( discriminant) ) / a;  //the smallest t -> closest hit point, that is why this needs to be checked first
		if(temp < t_max && temp > t_min)
		{
			rec.t        = temp;
			rec.position = r.pointAtParameter(rec.t);
			rec.normal   = (rec.position - center )/radius;
			//rec.normal.make_unit_vector();
			//std::cout <<"values from inside: " << rec.normal.x() << ", " << rec.normal.y() << ", " << rec.normal.z() << std::endl; 
			rec.mat_ptr = mat_ptr;
			return true;
		} 
		temp = (-b + sqrt(discriminant) ) / a;
		if(temp < t_max && temp > t_min)
		{
			rec.t        = temp;
			rec.position = r.pointAtParameter(rec.t);
			rec.normal   = (rec.position - center )/radius;
			//rec.normal.make_unit_vector();
			rec.mat_ptr = mat_ptr;
			return true;
		} 
	}
	return false;
}

#endif
