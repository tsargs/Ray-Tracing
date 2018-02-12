// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 12/29/15.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include <math.h>
#include "Vector3D.h"

//Default Constructor
Vector3D::Vector3D(void) : x(0.0), y(0.0), z(0.0)
{

}


Vector3D::Vector3D(double xVal, double yVal, double zVal) : x(xVal), y(yVal), z(zVal)
{

}


//Copy constructor
Vector3D::Vector3D(const Vector3D& vector): x(vector.x), y(vector.y), z(vector.z)
{
	
}


//Destructor
Vector3D::~Vector3D(void)
{

}


//Returns length of the vector
double Vector3D::Length(void)
{
	return sqrt(x*x + y*y + z*z);
}

//Returns length of the vector
double Vector3D::LengthSquared(void)
{
	return (x*x + y*y + z*z);
}

//Returns the unit vector
Vector3D& Vector3D::UnitVector(void)
{
	double length = sqrt(x*x + y*y + z*z);
	return Vector3D(x/length, y/length, z/length);
}

Vector3D Vector3D::operator-(void) //Unary minus operator
{
	return Vector3D(-x, -y, -z);
}

//Assignment Operator
Vector3D& Vector3D::operator=(const Vector3D& vector) 
{
	x = vector.x;
	y = vector.y;
	z = vector.z;

	return (*this);
}

void Vector3D::PrintValues(void)
{
	std::cout << "x: " << x << ", y: " << y << ", z: " << z << "\n";
}

