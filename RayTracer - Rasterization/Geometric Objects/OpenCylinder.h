#ifndef OPENCYLINDER
#define OPENCYLINDER

// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 03/27/16.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "GeometricObject.h"

class OpenCylinder:public GeometricObject
{
	public:
		
		double minY, maxY;
		double radius;

		//Constructors

		OpenCylinder(void);												//Default Constructor
		OpenCylinder(const double& radiusVal, const double& minYVal, const double& maxYVal);
		OpenCylinder(const OpenCylinder& disk);								//Copy constructor
		
		//Destructor

		~OpenCylinder(void);

		//Member Functions

		bool hit(const Ray& ray, double& tMin, ShadeRecord& sr) const;					//Hit function which checks for ray intersections
		bool ShadowHit(const Ray& ray, double& tMin) const;
};

#endif
