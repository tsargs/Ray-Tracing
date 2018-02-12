// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 03/27/16.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "Disk.h"
#include <Math.h>

//Default Constructor
Disk::Disk(void)
{
}

Disk::Disk(const Point3D& centerVal, const double& radiusVal, const Vector3D& normalVal) : center(centerVal), radius(radiusVal), normal(normalVal)
{
}

//Copy Constructor
Disk::Disk(const Disk& disk) : center(disk.center), radius(disk.radius), normal(disk.normal)
{
}


//Destructor
Disk::~Disk(void)
{

}


//Definition of Hit function declared in the base class Geometric Object
bool Disk::hit(const Ray& ray, double& tMinimum, ShadeRecord& sr) const
{
	double t = ((center - ray.origin) * normal) / (ray.rayDirection * normal);

	if (t < kEpsilon)
		return false;

	Point3D hitPoint = ray.origin + (ray.rayDirection * t);
	float tempDistance = hitPoint.Distance(center);

	if (tempDistance < radius)
	{
		//std::cout << "dist: " << tempDistance << "\n";
		//std::cout << "radius: " << radius << "\n";

		tMinimum = t;
		sr.hitPoint = hitPoint;
		sr.normal = normal;
		return true;
	}
	return false;
}

bool Disk::ShadowHit(const Ray& ray, double& tMin) const
{
	double t = ((center - ray.origin) * normal) / (ray.rayDirection * normal);

	if (t < kEpsilon)
		return false;

	Point3D hitPoint = ray.origin + (ray.rayDirection * t);
	float tempDistance = hitPoint.Distance(center);

	if (tempDistance < radius)
	{
		tMin = t;
		return true;
	}

	return false;
}