#ifndef HITABLELISTH
#define HITABLELISTH

#include "hitable.h"


// hitable_list  :  a list of hitables (objects that you can hit)
class hitable_list : public hitable
{
	public :
		hitable **list;
		int list_size;
		hitable_list() {}
		hitable_list(hitable **l, int size) : list(l) , list_size(size) {};
		virtual bool hit (const ray& r, float tmin, float tmax, hit_record& rec) const;
};

bool hitable_list::hit(const ray& r, float tmin, float tmax, hit_record& rec) const
{
	//check if any object in the list of hitables is hit by the ray r
	//look for the object(hitable) that is hit and is the closest
	hit_record temp_rec;
	bool hit_anything = false;
	double closest_so_far = tmax;
	for(int i=0;i<list_size;i++)
	{
		if (list[i]->hit(r, tmin, closest_so_far, temp_rec))
		{
			hit_anything = true;
			closest_so_far = temp_rec.t	;
			rec = temp_rec;	
		}
	}
	return hit_anything;
}


#endif
