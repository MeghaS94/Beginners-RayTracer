#ifndef UTILSH
#define UTILSH

#include <iostream>
#include <fstream>
#include <random>
#include <chrono>

using namespace std;
// random number generation 
default_random_engine dre (chrono::steady_clock::now().time_since_epoch().count());     // provide seed

/*class utils
{
};*/
int random (int lim)
{
	uniform_int_distribution<int> uid {0,lim};   // help dre to generate nos from 0 to lim (lim included);
	return uid(dre);    // pass dre as an argument to uid to generate the random no
}

vec3 random_in_unit_sphere()
{
	vec3 p;
	do {
		p = 2.0*vec3(random(10)/float(10), random(10)/float(10), random(10)/float(10)) - vec3(1,1,1); //* random num not strictly < 1
	} while (dot(p,p) >= 1.0);
	//dot(p, p) = 1 is the equation of the sphere, when dot(p,p) <= 1, then p is either inside or on the sphere.
	return p;
}

#endif