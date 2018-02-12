// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 03/07/16.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "Rectangle.h"
#include <Math.h>

//Default Constructor
Rectangle::Rectangle(void)
{

}

Rectangle::Rectangle(const Point3D& point0, const Vector3D& aVector, const Vector3D& bVector)
{
	p0 = point0;
	a = aVector;
	b = bVector;
	aLengthSquared = a.LengthSquared();
	bLengthSquared = b.LengthSquared();
	aLength = a.Length();
	bLength = b.Length();
	normal = (a^b).UnitVector();
}



//Destructor
Rectangle::~Rectangle(void)
{

}


//Definition of Hit function declared in the base class Geometric Object
bool Rectangle::hit(const Ray& ray, double& tMin, ShadeRecord& sr) const
{
	double t = ((p0 - ray.origin) * normal) / (ray.rayDirection * normal);

	if (t <= kEpsilon)
		return false;

	Point3D tempHitPoint = ray.origin + (ray.rayDirection * t);
	Vector3D tempVector = tempHitPoint - p0;

	float dotProduct1 = tempVector * a;

	if (dotProduct1 < 0 || dotProduct1 > aLengthSquared)
		return false;

	float dotProduct2 = tempVector * b;

	if (dotProduct2 < 0 || dotProduct2 > bLengthSquared)
		return false;

	tMin = t;
	sr.normal = normal;
	sr.hitPoint = tempHitPoint;
	sr.localHitPoint.x  = (tempHitPoint.x - p0.x) / aLength;
	sr.localHitPoint.y = (tempHitPoint.y - p0.y) / bLength;
	sr.localHitPoint.z = tempHitPoint.z;

	//std::cout << "Hit\n";

	return true;
}

//Definition of ShadowHit function declared in the base class Geometric Object
bool Rectangle::ShadowHit(const Ray& ray, double& tMin) const
{
	double t = (p0 - ray.origin) * normal / (ray.rayDirection * normal);

	if (t <= kEpsilon)
		return false;

	Point3D tempHitPoint = ray.origin + (ray.rayDirection * t);
	Vector3D tempVector = tempHitPoint - p0;

	float dotProduct1 = tempVector * a;

	if (dotProduct1 < 0 || dotProduct1 > aLengthSquared)
		return false;

	float dotProduct2 = tempVector * b;

	if (dotProduct2 < 0 || dotProduct2 > bLengthSquared)
		return false;

	tMin = t;
	return true;
}