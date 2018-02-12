#ifndef PLANE
#define PLANE

// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 01/15/16.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "GeometricObject.h"

class Plane:public GeometricObject
{
	public:
		
		Point3D pointOnPlane;
		Normal normal;

		//Constructors

		Plane(void);												//Default Constructor
		Plane(const Point3D& point, const Normal& normal);
		Plane(const Plane& plane);								//Copy constructor
		
		//Destructor

		~Plane(void);

		//Member Functions

		Plane& operator=(const Plane& plane);										//Assignment Operator
		bool hit(const Ray& ray, double& tMin, ShadeRecord& sr) const;									//Hit function which checks for ray intersections
		bool ShadowHit(const Ray& ray, double& tMin) const;
		void SetPoint(const Point3D& point);										//Function to set the center of sphere
		void SetNormal(const double& xVal, const double& yVal, const double& zVal);		//Function to set the center of sphere
		void SetColor(float rVal, float gVal, float bVal);								//Function to set the color of sphere
};

inline void Plane::SetPoint(const Point3D& point)
{
	pointOnPlane = point;
}

inline void Plane::SetNormal(const double& xVal, const double& yVal, const double& zVal)
{
	normal.x = xVal;
	normal.y = yVal;
	normal.z = zVal;
}

inline void Plane::SetColor(float rVal, float gVal, float bVal)
{
	color.r = rVal;
	color.g = gVal;
	color.b = bVal;
}

#endif
