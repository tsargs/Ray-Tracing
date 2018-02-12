// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 02/08/15.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "Cube.h"
#include <Math.h>

//Default Constructor
Cube::Cube(void)
{
	SetNormals();
}

Cube::Cube(const Point3D& minPointObj, const Point3D& maxPointObj) : minPoint(minPointObj), maxPoint(maxPointObj)
{
	SetNormals();
}

//Copy Constructor
Cube::Cube(const Cube& cube) : minPoint(cube.minPoint), maxPoint(cube.maxPoint)
{
	SetNormals();
}


//Destructor
Cube::~Cube(void)
{

}

void Cube::SetBoundingBox(void)
{
	double x0 = minPoint.x - kEpsilon;
	double x1 = maxPoint.x + kEpsilon;

	double y0 = minPoint.y - kEpsilon;
	double y1 = maxPoint.y + kEpsilon;

	double z0 = minPoint.z - kEpsilon;
	double z1 = maxPoint.z + kEpsilon;

	bBox.minPoint = Point3D(x0, y0, z0);
	bBox.maxPoint = Point3D(x1, y1, z1);
}

//Definition of Hit function declared in the base class Geometric Object
bool Cube::hit(const Ray& ray, double& tMinimum, ShadeRecord& sr) const
{
	double t0, t1;
	int entryFace;
	int exitFace;

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

	if (txMin > tyMin)
	{
		t0 = txMin;
		entryFace = (a >= 0) ? 0 : 3;
	}
	else
	{
		t0 = tyMin;
		entryFace = (b >= 0) ? 1 : 4;
	}

	if (tzMin > t0)
	{
		t0 = tzMin;
		entryFace = (c >= 0) ? 2 : 5;
	}

	//Point of exit for the ray
	//Smallest of tMax values
	if (txMax < tyMax)
	{
		t1 = txMax;
		exitFace = (a >= 0) ? 3 : 0;
	}
	else
	{
		t1 = tyMax;
		exitFace = (b >= 0) ? 4 : 1;
	}

	if (tzMax < t1)
	{
		t1 = tzMax;
		exitFace = (c >= 0) ? 5 : 2;
	}

	if (t0 < t1 && t1 > kEpsilon)
	{
		if (t0 > kEpsilon)
		{
			//Camera outside cube
			tMinimum = t0;
			sr.normal = normals[entryFace];
		}
		else
		{
			//Camera inside cube
			tMinimum = t1;
			sr.normal = normals[exitFace];
		}

		sr.hitPoint = ray.origin + (ray.rayDirection * tMinimum);
		return true;
	}
	else
		return false;
}

bool Cube::ShadowHit(const Ray& ray, double& tMin) const
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
	{
		if (t0 > kEpsilon)
		{
			//Camera outside cube
			tMin = t0;
		}
		else
		{
			//Camera inside cube
			tMin = t1;
		}
		return true;
	}
	else
		return false;
}