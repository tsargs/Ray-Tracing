// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 12/30/15.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "Point3D.h"

//Default Constructor
Point3D::Point3D(void) : x(0.0), y(0.0), z(0.0)
{

}


Point3D::Point3D(double xVal, double yVal, double zVal) : x(xVal), y(yVal), z(zVal)
{

}


//Copy constructor
Point3D::Point3D(const Point3D& point): x(point.x), y(point.y), z(point.z)
{
	
}


//Destructor
Point3D::~Point3D(void)
{

}


//Assignment Operator
Point3D& Point3D::operator=(const Point3D& point)
{
	x = point.x;
	y = point.y;
	z = point.z;

	return (*this);
}

float Point3D::Distance(const Point3D& pointB)
{
	return sqrt((pointB.x - x) * (pointB.x - x) + (pointB.y - y) * (pointB.y - y));
}


void Point3D::PrintValues()
{
	std::cout << "x: " << x << ", y: " << y << ", z: " << z << "\n";
}