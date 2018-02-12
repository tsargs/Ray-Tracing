// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 01/15/16.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include <math.h>
#include "Normal.h"

//Default Constructor
Normal::Normal(void) : x(0.0), y(0.0), z(0.0)
{

}


Normal::Normal(double xVal, double yVal, double zVal) : x(xVal), y(yVal), z(zVal)
{

}


//Copy constructor
Normal::Normal(const Normal& normal): x(normal.x), y(normal.y), z(normal.z)
{
	
}


//Destructor
Normal::~Normal(void)
{

}


//Returns the unit vector
Normal& Normal::UnitVector(void)
{
	double length = sqrt(x*x + y*y + z*z);
	return Normal(x/length, y/length, z/length);
}

//Assignment Operator
Normal& Normal::operator=(const Normal& normal)
{
	x = normal.x;
	y = normal.y;
	z = normal.z;

	return (*this);
}


