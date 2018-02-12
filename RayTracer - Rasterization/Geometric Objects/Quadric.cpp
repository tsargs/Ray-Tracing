// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 02/14/16.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "Quadric.h"
#include <Math.h>

//Default Constructor
Quadric::Quadric(void)
{

}

Quadric::Quadric(const int& a02, const int& a12, const int& a22, const int& a21Param, const int& a00Param)
{
	ai2[0] = a02;
	ai2[1] = a12;
	ai2[2] = a22;

	a21 = a21Param;
	a00 = a00Param;
}

//Copy Constructor
Quadric::Quadric(const Quadric& quadric)
{
	ai2[0] = quadric.ai2[0];
	ai2[1] = quadric.ai2[1];
	ai2[2] = quadric.ai2[2];
	a21 = quadric.a21;
	a00 = quadric.a00;

	n[0] = quadric.n[0];
	n[1] = quadric.n[1];
	n[2] = quadric.n[2];

	Pe = quadric.Pe;
	Pc = quadric.Pc;
}

//Assignment Operator
Quadric& Quadric::operator=(const Quadric& quadric)
{
	ai2[0] = quadric.ai2[0];
	ai2[1] = quadric.ai2[1];
	ai2[2] = quadric.ai2[2];
	a21 = quadric.a21;
	a00 = quadric.a00;

	n[0] = quadric.n[0];
	n[1] = quadric.n[1];
	n[2] = quadric.n[2];

	Pe = quadric.Pe;
	Pc = quadric.Pc;

	return (*this);
}

//Destructor
Quadric::~Quadric(void)
{

}


//Definition of Hit function declared in the base class Geometric Object
bool Quadric::hit(const Ray& ray, double& tMin) const
{
	double a = 0;
	double b = 0;
	double c = 0;

	float dummy;

	Vector3D npe = ray.rayDirection;

	for (int i = 0; i < 3; i++)
	{
		dummy = ((n[i]*npe) / s[i]);
		a += ai2[i] * dummy * dummy;
	}

	for (int i = 0; i < 3; i++)
	{
		b += ai2[i] * ((2 * (n[i] * npe) * (n[i] * PCE))) / (s[i] * s[i]) + (a21 * ((n[2] * npe) / s[2]));
	}

	for (int i = 0; i < 3; i++)
	{
		dummy = (n[i] * PCE) / s[i];
		c += ai2[i] * dummy * dummy + (a21 * ((n[2] * PCE) / s[2])) + a00;
	}
	
	double d = (b * b) - (4 * a * c);
	
	if (d > 0)
	{
		//Two solutions are available
		//Solution # One : sqrt(d) is negative --> yields smaller root
		double tempRoot = sqrt(d);
		double t1 = (-b - tempRoot) / (2 * a);
		
		//Additional check to ensure that the smaller root is greater than the least possible value of t (which is kEpsilon)
		if (t1 > kEpsilon)
		{
			tMin = t1;
			return (true);
		}

		//The following code is executed only if the smaller root is lesser than the least possible value of t (which is kEpsilon)
		//Solution # two : sqrt(d) is positive --> yields larger root

		double t2 = (-b + tempRoot) / (2 * a);
		//std::cout << "t2: " << t2 << "\n";

		if (t2 > kEpsilon)
		{
			tMin = t2;
			return (true);
		}
	}
	else
	{
		//No solution if d < 0
		//If d = 0, then it means that the ray has intersected with the sphere tangentially this is very rare and we can ignore this in our code
		return false;
	}

	return false;
}