#ifndef SPHERE
#define SPHERE

// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 12/30/15.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "GeometricObject.h"

class Sphere:public GeometricObject
{
	public:
		
		Point3D center;
		double radius;

		BBox bBox;

		//Constructors

		Sphere(void);												//Default Constructor
		Sphere(const Point3D& centerPoint, const double& radiusVal);
		Sphere(const Sphere& sphere);								//Copy constructor
		
		//Destructor

		~Sphere(void);

		//Member Functions

		Sphere& operator=(const Sphere& sphere);										//Assignment Operator
		bool hit(const Ray& ray, double& tMin, ShadeRecord& sr) const;					//Hit function which checks for ray intersections
		bool ShadowHit(const Ray& ray, double& tMin) const;
		void SetCenter(const Point3D& centerPoint);										//Function to set the center of sphere
		void SetCenter(const double& xVal, const double& yVal, const double& zVal);		//Function to set the center of sphere
		void SetRadius(const double& radiusVal);										//Function to set the radius of sphere
		void SetColor(float rVal, float gVal, float bVal);								//Function to set the color of sphere
		void SetBoundingBox(void);
		BBox GetBoundingBox(void);
};

inline void Sphere::SetCenter(const Point3D& centerPoint)
{
	center = centerPoint;
}

inline void Sphere::SetCenter(const double& xVal, const double& yVal, const double& zVal)
{
	center.x = xVal;
	center.y = yVal;
	center.z = zVal;
}

inline void Sphere::SetRadius(const double& radiusVal)
{
	radius = radiusVal;
}

inline void Sphere::SetColor(float rVal, float gVal, float bVal)
{
	color.r = rVal;
	color.g = gVal;
	color.b = bVal;
}

#endif
