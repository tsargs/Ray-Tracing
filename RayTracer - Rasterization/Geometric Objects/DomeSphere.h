#ifndef DOMESPHERE
#define DOMESPHERE

// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 05/02/16.
//  Copyright © 2016 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "GeometricObject.h"

class DomeSphere:public GeometricObject
{
	public:
		
		Point3D center;
		double radius;

		BBox bBox;

		//Constructors

		DomeSphere(void);												//Default Constructor
		DomeSphere(const Point3D& centerPoint, const double& radiusVal);
		
		//Destructor

		~DomeSphere(void);

		//Member Functions

		bool hit(const Ray& ray, double& tMin, ShadeRecord& sr) const;					//Hit function which checks for ray intersections
		bool ShadowHit(const Ray& ray, double& tMin) const;
		void SetCenter(const Point3D& centerPoint);										//Function to set the center of sphere
		void SetCenter(const double& xVal, const double& yVal, const double& zVal);		//Function to set the center of sphere
		void SetRadius(const double& radiusVal);										//Function to set the radius of sphere
		void SetColor(float rVal, float gVal, float bVal);								//Function to set the color of sphere
		void SetBoundingBox(void);
		BBox GetBoundingBox(void);
};

inline void DomeSphere::SetCenter(const Point3D& centerPoint)
{
	center = centerPoint;
}

inline void DomeSphere::SetCenter(const double& xVal, const double& yVal, const double& zVal)
{
	center.x = xVal;
	center.y = yVal;
	center.z = zVal;
}

inline void DomeSphere::SetRadius(const double& radiusVal)
{
	radius = radiusVal;
}

inline void DomeSphere::SetColor(float rVal, float gVal, float bVal)
{
	color.r = rVal;
	color.g = gVal;
	color.b = bVal;
}

#endif
