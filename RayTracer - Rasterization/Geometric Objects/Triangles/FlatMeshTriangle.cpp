// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 03/27/16.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "FlatMeshTriangle.h"

//Default Constructor
FlatMeshTriangle::FlatMeshTriangle(void)
{

}

//Destructor
FlatMeshTriangle::~FlatMeshTriangle(void)
{

}


//Definition of Hit function declared in the base class Geometric Object
bool FlatMeshTriangle::hit(const Ray& ray, double& tMin, ShadeRecord& sr) const
{
	Point3D v0 = Point3D(meshPtr->vertices[i0]);
	Point3D v1 = Point3D(meshPtr->vertices[i1]);
	Point3D v2 = Point3D(meshPtr->vertices[i2]);

	double a = v0.x - v1.x,		b = v0.x - v2.x,	c = ray.rayDirection.x,		d = v0.x - ray.origin.x;
	double e = v0.y - v1.y,		f = v0.y - v2.y,	g = ray.rayDirection.y,		h = v0.y - ray.origin.y;
	double i = v0.z - v1.z,		j = v0.z - v2.z,	k = ray.rayDirection.z,		l = v0.z - ray.origin.z;

	double m = f*k - g*j,	 n = g*i - e*k,		o = e*j - f*i;

	double denominator = a*m + b*n + c*o;
	double invDenominator = 1.0 / denominator;

	double p = g*l - h*k,	q = h*j - f*l;
	double r = h*k - g*l,	s = e*l - h*i;
	double t = f*l - h*j,	u = h*i - e*l;

	double beta = (d*m + b*p + c*q) * invDenominator;

	if (beta < 0.0)
		return false;
	
	double gamma = (a*r + d*n + c*s) * invDenominator;

	if (gamma < 0.0 || beta + gamma > 1.0)
		return false;

	double tVal = (a*t + b*u + d*o) * invDenominator;

	if (tVal < kEpsilon)
		return false;

	tMin = tVal;
	sr.normal = normal;
	sr.hitPoint = ray.origin + (ray.rayDirection*tVal);

	return true;
}
