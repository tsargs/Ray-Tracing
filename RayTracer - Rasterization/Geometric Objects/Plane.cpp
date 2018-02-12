// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 01/15/16.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "Plane.h"
#include <Math.h>

//Default Constructor
Plane::Plane(void) : pointOnPlane(0,0,0), normal(0,1,0)
{

}

Plane::Plane(const Point3D& point, const Normal& normalObject) : pointOnPlane(point), normal(normalObject)
{

}

//Copy Constructor
Plane::Plane(const Plane& plane) : pointOnPlane(plane.pointOnPlane), normal(plane.normal)
{
	
}

//Assignment Operator
Plane& Plane::operator=(const Plane& plane)
{
	pointOnPlane = plane.pointOnPlane;
	normal = plane.normal;

	return (*this);
}

//Destructor
Plane::~Plane(void)
{

}


//Definition of Hit function declared in the base class Geometric Object
bool Plane::hit(const Ray& ray, double& tMin, ShadeRecord& sr) const
{
	double t = ((pointOnPlane - ray.origin) * normal) / (ray.rayDirection * normal);
	if (t > kEpsilon)
	{
		tMin = t;
		sr.hitPoint = ray.origin + (ray.rayDirection * tMin);
		sr.normal = Vector3D(normal.x, normal.y, normal.z);

		return true;
	}
	return false;
}

//Definition of ShadowHit function declared in the base class Geometric Object
bool Plane::ShadowHit(const Ray& ray, double& tMin) const
{
	double t = ((pointOnPlane - ray.origin) * normal) / (ray.rayDirection * normal);
	if (t > kEpsilon)
	{
		tMin = t;
		//std::cout << "t: " << tMin <<"\n";
		return true;
	}
	return false;
}