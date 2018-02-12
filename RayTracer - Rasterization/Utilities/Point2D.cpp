// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 01/19/16.
//  Copyright © 2016 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "Point2D.h"

//Default Constructor
Point2D::Point2D(void) : x(0.0), y(0.0)
{

}


Point2D::Point2D(double xVal, double yVal) : x(xVal), y(yVal)
{

}


//Copy constructor
Point2D::Point2D(const Point2D& point): x(point.x), y(point.y)
{
	
}


//Destructor
Point2D::~Point2D(void)
{

}


//Assignment Operator
Point2D& Point2D::operator=(const Point2D& point)
{
	x = point.x;
	y = point.y;

	return (*this);
}

Point2D Point2D::operator*(const float& floatVal) const
{
	return Point2D(x * floatVal, y * floatVal);
}

void Point2D::PrintValues()
{
	std::cout << "x: " << x << ", y: " << y << "\n";
}