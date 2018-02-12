// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 12/30/15.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "Ray.h"

//Default Constructor
Ray::Ray(void) : origin(0.0, 0.0, 0.0), rayDirection(0.0, 0.0, 0.0)
{

}


Ray::Ray(const Point3D& point, const Vector3D& vector): origin(point), rayDirection(vector)
{

}


//Copy constructor
Ray::Ray(const Ray& ray): origin(ray.origin), rayDirection(ray.rayDirection)
{
	
}


//Destructor
Ray::~Ray(void)
{

}


//Assignment Operator
Ray& Ray::operator=(const Ray& ray)
{
	origin = ray.origin;
	rayDirection = ray.rayDirection;

	return (*this);
}


