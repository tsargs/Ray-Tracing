// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 03/27/16.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "OpenCylinder.h"

//Default Constructor
OpenCylinder::OpenCylinder(void)
{
}

OpenCylinder::OpenCylinder(const double& radiusVal, const double& minYVal, const double& maxYVal) : radius(radiusVal), minY(minYVal), maxY(maxYVal)
{
}

//Copy Constructor
OpenCylinder::OpenCylinder(const OpenCylinder& openCylinder) : radius(openCylinder.radius), minY(openCylinder.minY), maxY(openCylinder.maxY)
{
}


//Destructor
OpenCylinder::~OpenCylinder(void)
{

}


//Definition of Hit function declared in the base class Geometric Object
bool OpenCylinder::hit(const Ray& ray, double& tMinimum, ShadeRecord& sr) const
{
	double a = ray.rayDirection.x * ray.rayDirection.x + ray.rayDirection.z * ray.rayDirection.z;
	double b = 2 * ((ray.origin.x * ray.rayDirection.x) + (ray.origin.z * ray.rayDirection.z));
	double c = ray.origin.x * ray.origin.x + ray.origin.z * ray.origin.z - (radius * radius);

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
			Point3D hitPoint = ray.origin + (ray.rayDirection*t1);
			if (hitPoint.y <= maxY && hitPoint.y >= minY && hitPoint.z > 5)
			{
				tMinimum = t1;
				sr.hitPoint = hitPoint;
				sr.normal = Vector3D(hitPoint.x/radius, 0, hitPoint.z/radius);
				sr.normal = -sr.normal;
				return (true);
			}
		}

		//The following code is executed only if the smaller root is lesser than the least possible value of t (which is kEpsilon)
		//Solution # two : sqrt(d) is positive --> yields larger root

		double t2 = (-b + tempRoot) / (2 * a);

		if (t2 > kEpsilon)
		{
			Point3D hitPoint = ray.origin + (ray.rayDirection*t2);
			if (hitPoint.y <= maxY && hitPoint.y >= minY && hitPoint.z > 5)
			{
				tMinimum = t2;
				sr.hitPoint = hitPoint;
				sr.normal = Vector3D(hitPoint.x / radius, 0, hitPoint.z / radius);
				sr.normal = -sr.normal;
				return (true);
			}
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

bool OpenCylinder::ShadowHit(const Ray& ray, double& tMin) const
{
	double a = ray.rayDirection.x * ray.rayDirection.x + ray.rayDirection.z * ray.rayDirection.z;
	double b = 2 * ((ray.origin.x * ray.rayDirection.x) + (ray.origin.z * ray.rayDirection.z));
	double c = ray.origin.x * ray.origin.x + ray.origin.z * ray.origin.z - (radius * radius);

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
			Point3D hitPoint = ray.origin + (ray.rayDirection*t1);
			if (hitPoint.y <= maxY && hitPoint.y >= minY)
			{
				tMin = t1;
				return (true);
			}
		}

		//The following code is executed only if the smaller root is lesser than the least possible value of t (which is kEpsilon)
		//Solution # two : sqrt(d) is positive --> yields larger root

		double t2 = (-b + tempRoot) / (2 * a);

		if (t2 > kEpsilon)
		{
			Point3D hitPoint = ray.origin + (ray.rayDirection*t2);
			if (hitPoint.y <= maxY && hitPoint.y >= minY)
			{
				tMin = t2;
				return (true);
			}
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