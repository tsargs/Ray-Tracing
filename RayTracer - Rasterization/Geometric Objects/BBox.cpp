// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 03/26/16.
//  Copyright © 2016 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "BBox.h"


//Default Constructor
BBox::BBox(void)
{

}

BBox::BBox(const Point3D& minPointObj, const Point3D& maxPointObj) : minPoint(minPointObj), maxPoint(maxPointObj)
{

}

//Copy Constructor
BBox::BBox(const BBox& cube) : minPoint(cube.minPoint), maxPoint(cube.maxPoint)
{
	
}


//Destructor
BBox::~BBox(void)
{

}


//Definition of Hit function declared in the base class Geometric Object
bool BBox::hit(const Ray& ray, double& tMinimum) const
{
	double t0, t1;

	double txMin, txMax; // upper and lower intersection point(x axis)
	double tyMin, tyMax; // upper and lower intersection point(y axis)
	double tzMin, tzMax; // upper and lower intersection point(z axis)
    
	double a = 1.0 / ray.rayDirection.x;
	double b = 1.0 / ray.rayDirection.y;
	double c = 1.0 / ray.rayDirection.z;

	if (a >= 0)
	{
		txMin = (minPoint.x - ray.origin.x) * a;
		txMax = (maxPoint.x - ray.origin.x) * a;
	}
	else
	{
		txMin = (maxPoint.x - ray.origin.x) * a;
		txMax = (minPoint.x - ray.origin.x) * a;
	}

	if (b >= 0)
	{
		tyMin = (minPoint.y - ray.origin.y) * b;
		tyMax = (maxPoint.y - ray.origin.y) * b;
	}
	else
	{
		tyMin = (maxPoint.y - ray.origin.y) * b;
		tyMax = (minPoint.y - ray.origin.y) * b;
	}

	if (c >= 0)
	{
		tzMin = (minPoint.z - ray.origin.z) * c;
		tzMax = (maxPoint.z - ray.origin.z) * c;
	}
	else
	{
		tzMin = (maxPoint.z - ray.origin.z) * c;
		tzMax = (minPoint.z - ray.origin.z) * c;
	}
    
	//Point of entry for the ray
	//Largest of tMin values

	t0 = (txMin > tyMin) ? txMin : tyMin;
	t0 = (tzMin > t0) ? tzMin : t0;

	//Point of exit for the ray
	//Smallest of tMax values
	t1 = (txMax < tyMax) ? txMax : tyMax;
	t1 = (tzMax < t1) ? tzMax : t1;

	if (t0 < t1 && t1 > kEpsilon)
		return true;
	else
		return false;
}


bool BBox::Inside(Point3D point) const
{
	if (point.x > minPoint.x && point.x < maxPoint.x)
		if (point.y > minPoint.y && point.y < maxPoint.y)
			if (point.z > minPoint.z && point.z < maxPoint.z)
				return true;

	return false;
}