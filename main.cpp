#include <iostream>
#include <fstream>
#include "vec3.h"
#include "ray.h"
#include "sphere.h"
#include "hitable_list.h"
#include "float.h"
#include "camera.h"
#include "material.h"

#include <random>
#include <chrono>
#include "utils.h"

int random (int lim);
vec3 random_in_unit_sphere();

using namespace std;

//second color function
vec3 color(const ray& r, hitable *world)
{
	hit_record rec;
	if (world->hit(r, 0.0, FLT_MAX, rec))
	{
		vec3 targetDir = rec.normal + random_in_unit_sphere();
		//targetDir.make_unit_vector();
		return 0.5*color(ray(rec.position, targetDir), world);

		//normalise the normal to lie in between 0,1 . before it could be between -1,1
		//return 0.5*vec3(rec.normal.x()+1.0, rec.normal.y()+1.0, rec.normal.z()+1.0);
	}
	else
	{
		// find the color at point B (the point that intersects the screen) on the ray.
		vec3 unit_direction = unit_vector(r.direction());
		float t = 0.5*(unit_direction.y()+ 1.0);	//normalise the value of v.y (-1 < v.y < 1) to lie between [0,1]
		vec3 c = (1.0-t)*vec3(1.0,1.0,1.0) + t *vec3(0.5, 0.7, 1.0); //linear interpolation
		return c;
	}
}

//first color function
vec3 color1(const ray& r, hitable *world)
{
	hit_record rec;
	if (world->hit(r, 0.0, FLT_MAX, rec))
	{
		//normalise the normal to lie in between 0,1 . before it could be between -1,1
		return 0.5*vec3(rec.normal.x()+1.0, rec.normal.y()+1.0, rec.normal.z()+1.0);
	}
	else
	{
		// find the color at point B (the point that intersects the screen) on the ray.
		vec3 unit_direction = unit_vector(r.direction());
		float t = 0.5*(unit_direction.y()+ 1.0);	//normalise the value of v.y (-1 < v.y < 1) to lie between [0,1]
		vec3 c = (1.0-t)*vec3(1.0,1.0,1.0) + t *vec3(0.5, 0.7, 1.0); //linear interpolation
		return c;
	}
}	

//third color function
vec3 color2(const ray& r, hitable *world, int depth)
{
	hit_record rec;
	if (world->hit(r,0.001 ,FLT_MAX ,rec))
	{
		ray scattered;
		vec3 attenuation;
		//based on material, apply attenuation etc
		if ( depth < 5 && rec.mat_ptr->scatter(r, rec, attenuation, scattered))
		{
			return attenuation*color2(scattered, world, depth+1);	
		}
		else
		{
			return vec3(0.0,0.0,0.0);
		}
	}
	else
	{
		// find the color at point B (the point that intersects the screen) on the ray.
		vec3 unit_direction = unit_vector(r.direction());
		float t = 0.5*(unit_direction.y()+ 1.0);	//normalise the value of v.y (-1 < v.y < 1) to lie between [0,1]
		vec3 c = (1.0-t)*vec3(1.0,1.0,1.0) + t *vec3(0.5, 0.7, 1.0); //linear interpolation
		return c;
	}
}

int main()
{
	//Keep nx and ny unequal so that you will know when some matrix is transposed , easily
	int nx = 200;
	int ny = 100;
	int ns = 100; // number of samples

	ofstream fout("metal_material_applied.ppm");
	fout << "P3\n" << nx << " " << ny << "\n255\n";
	/*for (int j=ny-1; j>=0; j--){
		for(int i=0; i<nx; i++){
			float r = float(i)/float(nx);
			float g = float(j)/float(ny);
			float b = 0.2;
			int ir = int(255.99*r);
			int ig = int(255.99*g);
			int ib = int(255.99*b);
			fout << ir << " " << ig << " " << ib << "\n";
		}
	}*/
	//there is no stratification of the pixels during anti-aliasing.
		
	vec3 lower_left_corner(-2.0, -1.0, -1.0); //establish a point of reference
	vec3 horizontal(4.0, 0.0, 0.0);			  //positive x -> double it because you will be multiplying it with a floating point number
	vec3 vertical(0.0, 2.0, 0.0);			  //positive y 
	vec3 origin(0.0, 0.0, 0.0);				  //camera postion
	camera *cam  =  new camera();
	hitable *list[4];
	list[0] = new sphere(vec3(0,0,-1), 0.5, new lambertian(vec3(0.8, 0.3, 0.3)));
	list[1] = new sphere(vec3(0, -100.5, -1), 100.0, new lambertian(vec3(0.8, 0.8, 0.0)));
	list[2] = new sphere(vec3(1,0, -1), 0.5, new metal(vec3(0.8, 0.6, 0.2), 0.5));
	list[3] = new sphere(vec3(-1,0, -1), 0.5, new metal(vec3(0.8, 0.8, 0.8), 0.5));

	hitable_list *world = new hitable_list(list,4);

	for (int j=ny-1; j>=0; j--){
		for(int i=0; i<nx; i++){
			vec3 col(0,0,0);
			for(int s=0; s<ns; s++)
			{
				//cout<<random(10)/float(10) <<" ";
				float randomNum = random(10)/float(11); //(double)rand()/((double)RAND_MAX + 1); //needs to be < 1 strictly
				//cout << randomNum << endl;
				float u = float (i + randomNum) /float (nx);
				float v = float (j + randomNum) /float (ny);
				ray r = cam->getRayAtPoint(u, v);	
				//ray r(origin, lower_left_corner + u*horizontal + v*vertical);
				col += color2(r, world, 0);
			}
			
			col /= float(ns);
			col = vec3 (sqrt(col[0]) , sqrt(col[1]) , sqrt(col[2]));
			int ir = int(255.99*col[0]);
			int ig = int(255.99*col[1]);
			int ib = int(255.99*col[2]);
			fout << ir << " " << ig << " " << ib << "\n";			

		}
	}

}	