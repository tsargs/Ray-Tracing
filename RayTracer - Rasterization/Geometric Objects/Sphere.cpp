// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 12/30/15.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "Sphere.h"

//Default Constructor
Sphere::Sphere(void) : center(0,0,0), radius(1)
{

}

Sphere::Sphere(const Point3D& centerPoint, const double& radiusVal) : center(centerPoint), radius(radiusVal)
{

}

//Copy Constructor
Sphere::Sphere(const Sphere& sphere) : center(sphere.center), radius(sphere.radius)
{
	
}

//Assignment Operator
Sphere& Sphere::operator=(const Sphere& sphere)
{
	center = sphere.center;
	radius = sphere.radius;

	return (*this);
}

//Destructor
Sphere::~Sphere(void)
{

}

void Sphere::SetBoundingBox(void)
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

BBox Sphere::GetBoundingBox(void)
{
	return bBox;
}

//Definition of Hit function declared in the base class Geometric Object
bool Sphere::hit(const Ray& ray, double& tMin, ShadeRecord& sr) const
{
	double a = ray.rayDirection * ray.rayDirection;	//Dot product of ray's directional vector
	double b = 2 * ((ray.origin - center) * ray.rayDirection);
	double c = ((ray.origin - center) * (ray.origin - center)) - (radius * radius);

	double d = (b * b) - (4 * a * c);

	/*
	if (ray.origin.x > 85.7 && ray.origin.x < 86)
	{
		if (ray.origin.y > 130 && ray.origin.y < 131)
		{
			if (ray.origin.z > -240 && ray.origin.y < -239)
				std::cout << "d: " << d << "\n";
		}
	}
	*/

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
			//sr.normal = ((ray.origin - center) + (ray.rayDirection * t1)) / radius;

			/*
			if (sr.hitPoint.x > 84 && sr.hitPoint.x < 86)
			{
				if (sr.hitPoint.y > 129 && sr.hitPoint.y < 131)
				{
					//Vector3D tempRay = ray.rayDirection;
					//tempRay.PrintValues();
					//if (sr.hitPoint.z == -240)
					if (sr.hitPoint.z > -241 && sr.hitPoint.z < -239)
					{
						Vector3D tempRay = ray.rayDirection;
						tempRay.PrintValues();
					}
				}
			}
			*/
			
					
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
			//sr.normal = ((ray.origin - center) + (ray.rayDirection * t1)) / radius;

			/*
			if (sr.hitPoint.x > 84 && sr.hitPoint.x < 86)
			{
				if (sr.hitPoint.y > 129 && sr.hitPoint.y < 131)
				{
					if (sr.hitPoint.z > -241 && sr.hitPoint.z < -239)
					{
						Vector3D tempRay = ray.rayDirection;
						tempRay.PrintValues();
					}
				}
			}
			*/

			return (true);
		}

		if (sr.rayDepth == 2)
		{
			std::cout << "t1: " << t1 << "\n";
			std::cout << "t2: " << t2 << "\n";
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


bool Sphere::ShadowHit(const Ray& ray, double& tMin) const
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
			return (true);
		}

		//The following code is executed only if the smaller root is lesser than the least possible value of t (which is kEpsilon)
		//Solution # two : sqrt(d) is positive --> yields larger root

		double t2 = (-b + tempRoot) / (2 * a);

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