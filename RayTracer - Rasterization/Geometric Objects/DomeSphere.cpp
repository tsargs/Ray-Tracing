// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 05/02/16.
//  Copyright © 2016 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "DomeSphere.h"

//Default Constructor
DomeSphere::DomeSphere(void) : center(0,0,0), radius(1)
{

}

DomeSphere::DomeSphere(const Point3D& centerPoint, const double& radiusVal) : center(centerPoint), radius(radiusVal)
{

}


//Destructor
DomeSphere::~DomeSphere(void)
{

}

void DomeSphere::SetBoundingBox(void)
{
	double x0 = center.x - radius;
	double x1 = center.x + radius;

	double y0 = center.y - radius;
	double y1 = center.y + radius;

	double z0 = center.z - radius;
	double z1 = center.z + radius;

	bBox.minPoint = Point3D(x0, y0, z0);
	bBox.maxPoint = Point3D(x1, y1, z1);
}

BBox DomeSphere::GetBoundingBox(void)
{
	return bBox;
}

//Definition of Hit function declared in the base class Geometric Object
bool DomeSphere::hit(const Ray& ray, double& tMin, ShadeRecord& sr) const
{
	double a = ray.rayDirection * ray.rayDirection;	//Dot product of ray's directional vector
	double b = 2 * ((ray.origin - center) * ray.rayDirection);
	double c = ((ray.origin - center) * (ray.origin - center)) - (radius * radius);

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
			sr.hitPoint = ray.origin + (ray.rayDirection*t1);
			sr.localHitPoint = (sr.hitPoint - center).UnitVector();
			sr.normal = ((sr.hitPoint - center) / radius).UnitVector();
			sr.normal = -sr.normal;
					
			return (true);
		}

		//The following code is executed only if the smaller root is lesser than the least possible value of t (which is kEpsilon)
		//Solution # two : sqrt(d) is positive --> yields larger root

		double t2 = (-b + tempRoot) / (2 * a);

		if (t2 > kEpsilon)
		{
			tMin = t2;
			sr.hitPoint = ray.origin + (ray.rayDirection*t1);
			sr.localHitPoint = (sr.hitPoint - center).UnitVector();
			sr.normal = ((sr.hitPoint - center) / radius).UnitVector();
			sr.normal = -sr.normal;

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


bool DomeSphere::ShadowHit(const Ray& ray, double& tMin) const
{
	return false;
}