#ifndef POINT_3D
#define POINT_3D

// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 12/29/15.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "Vector3D.h"
#include <math.h>

class Point3D
{
	public:
		double x, y, z;

	//Constructors
		Point3D(void);										//Default Constructor
		Point3D(double xVal, double yVal, double zVal);
		Point3D(const Point3D& point);						//Copy constructor

		~Point3D(void);										//Destructor

	//Member Functions
		Point3D& operator=(const Point3D& point);					//Assignment operator
		Vector3D operator-(const Point3D& point2) const;			//Subtraction operator --> (a - b) returns vector from b to a
		Point3D operator+(const Vector3D& vector) const;			//Addition with vector
		Point3D operator-(const Vector3D& vector) const;			//Subtraction with vector
		Point3D operator*(const float& floatVal) const;				//Multiplication with float

		float Distance(const Point3D& pointB);		//Returns distance between the points
		void PrintValues(void);
};


inline Vector3D Point3D::operator-(const Point3D& point2) const
{
	return Vector3D(x - point2.x, y - point2.y, z - point2.z);
}

inline Point3D Point3D::operator+(const Vector3D& vector) const
{
	return Point3D(x + vector.x, y + vector.y, z + vector.z);
}

inline Point3D Point3D::operator-(const Vector3D& vector) const
{
	return Point3D(x - vector.x, y - vector.y, z - vector.z);
}

inline Point3D Point3D::operator*(const float& floatVal) const
{
	return Point3D(x * floatVal, y * floatVal, z * floatVal);
}

#endif