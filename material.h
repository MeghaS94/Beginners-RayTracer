#ifndef MATERIALH
#define MATERIALH

#include "ray.h"
#include "utils.h"

int random (int lim);
vec3 random_in_unit_sphere();

class material {
	public :
		virtual bool scatter(const ray& rIn, const hit_record& rec, vec3& attenuation, ray& scattered) = 0;
};

class lambertian : public material {
	public :
		vec3 albedo; //The proportion of the incident light or radiation that is reflected by a surface

		lambertian (const vec3& a) : albedo(a) {}

		virtual bool scatter(const ray& rIn, const hit_record& rec, vec3& attenuation, ray& scattered)
		{
			vec3 targetDir = rec.normal + random_in_unit_sphere();
			//targetDir.make_unit_vector();
			scattered = ray(rec.position, targetDir); //the scattered ray
			//We can scatter with a probobility p and then attenuation will be albedo/p
			attenuation = albedo;	//why do I need to do this!?
			return true;
		}
};

class metal : public material {
	public :
		vec3 albedo;
		float fuzz;
		metal(const vec3& a, float f) : albedo(a) {if (f < 1) fuzz =f; else fuzz =1; } //const because albedo doesn't change

		//Metals reflect the incoming ray
		vec3 reflect(const vec3& v, const vec3& n)
		{
			return v - 2*dot(v,n)*n;	//v- 2(B) | B = -vcos(theta) , multiply both sides by n.n to get the result that we use
		}

		//Use this reflected ray to calculate the final scatter of the incoming ray.
		virtual bool scatter(const ray& rIn, const hit_record& rec, vec3& attenuation, ray& scattered)
		{
			vec3 reflected = reflect(unit_vector(rIn.direction()), rec.normal);
			scattered = ray(rec.position, reflected + fuzz*random_in_unit_sphere());
			attenuation = albedo;
			return (dot(rec.normal, scattered.direction() /*- scattered.origin()*/) > 0); //angle between the normal and the scattred ray should
																					  // be less than 90.
		} 
};

#endif
