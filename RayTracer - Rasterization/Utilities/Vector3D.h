#ifndef VECTOR_3D
#define VECTOR_3D

// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 12/29/15.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "Normal.h"
#include <iostream>
//#include "Point3D.h"

class Point3D;

class Vector3D
{
	public:
		double x, y, z;

		//Constructors

		Vector3D(void);										//Default Constructor
		Vector3D(double xVal, double yVal, double zVal);
		Vector3D(const Vector3D& vector);					//Copy constructor
		
		//Destructor

		~Vector3D(void);

		//Member Functions

		double Length(void);								//Returns length of the vector
		double LengthSquared(void);
		Vector3D& UnitVector(void);							//Returns unit vector

		Vector3D operator-(void); //Unary minus operator

		Vector3D& operator=(const Vector3D& vector);		//Assignment Operator
		Vector3D operator+(const Vector3D& vector) const;	//Addition operator - Vector addition
		Vector3D operator-(const Vector3D& vector) const;	//Subtraction operator - Vector subtraction
		//Vector3D operator-(const Point3D& point) const;		//Subtraction operator - Subtraction of a point
		double operator*(const Vector3D& vector) const;		//Multiplication operator - Dot product
		double operator*(const Normal& normal) const;		//Multiplication operator - Dot product
		Vector3D operator^(const Vector3D& vector) const;	//Vector cross product
		Vector3D operator*(const double& a) const;			//Multiplication operator - Multiplication with scalar
		Vector3D operator/(const double& a) const;			//Division operator - Division by a scalar
	
		void PrintValues(void);
};

//Addition operator - Vector addition
inline Vector3D Vector3D::operator+(const Vector3D& vector) const
{
	return Vector3D(x + vector.x, y + vector.y, z + vector.z);
}

//Subtraction operator - Vector subtraction
inline Vector3D Vector3D::operator-(const Vector3D& vector) const
{
	return Vector3D(x - vector.x, y - vector.y, z - vector.z);
}

/*
//Subtraction operator - Subtraction of a point
inline Vector3D Vector3D::operator-(const Point3D& point) const
{
	return Vector3D(x - point.x, y - point.y, z - point.z);
}
*/

//Multiplication operator - Dot product
inline double Vector3D::operator*(const Vector3D& vector) const
{
	return (x*vector.x + y * vector.y + z*vector.z);
}

//Multiplication operator - Dot product
inline double Vector3D::operator*(const Normal& normal) const
{
	return (x*normal.x + y * normal.y + z*normal.z);
}

//Vector cross product
inline Vector3D Vector3D::operator^(const Vector3D& vector) const
{
	return Vector3D((y*vector.z - z*vector.y), (z*vector.x - x*vector.z), (x*vector.y - y*vector.x));
}

//Multiplication operator - Multiplication with scalar
inline Vector3D Vector3D::operator*(const double& a) const
{
	return Vector3D(a*x, a*y, a*z);
}

//Division operator - Division by a scalar
inline Vector3D Vector3D::operator/(const double& a) const	
{
	return Vector3D(x/a, y/a, z/a);
}

#endif
