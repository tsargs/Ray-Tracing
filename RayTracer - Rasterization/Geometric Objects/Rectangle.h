#ifndef RECTANGLE
#define RECTANGLE

// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 03/07/16.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "GeometricObject.h"

class Rectangle:public GeometricObject
{
	public:
		
		Point3D p0;
		Vector3D a, b;
		float aLengthSquared, bLengthSquared;
		float aLength, bLength;
		Vector3D normal;

		//Constructors

		Rectangle(void);												//Default Constructor
		Rectangle(const Point3D& point0, const Vector3D& aVector, const Vector3D& bVector);
		
		//Destructor

		~Rectangle(void);

		//Member Functions

		bool hit(const Ray& ray, double& tMin, ShadeRecord& sr) const;									//Hit function which checks for ray intersections
		bool ShadowHit(const Ray& ray, double& tMin) const;
		void SetColor(float rVal, float gVal, float bVal);								//Function to set the color of sphere
};


inline void Rectangle::SetColor(float rVal, float gVal, float bVal)
{
	color.r = rVal;
	color.g = gVal;
	color.b = bVal;
}

#endif
