#ifndef DISK
#define DISK

// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 03/27/16.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "GeometricObject.h"

class Disk:public GeometricObject
{
	public:
		
		Point3D center;
		double radius;
		Vector3D normal;

		//Constructors

		Disk(void);												//Default Constructor
		Disk(const Point3D& centerVal, const double& radiusVal, const Vector3D& normalVal);
		Disk(const Disk& disk);								//Copy constructor
		
		//Destructor

		~Disk(void);

		//Member Functions

		bool hit(const Ray& ray, double& tMin, ShadeRecord& sr) const;					//Hit function which checks for ray intersections
		bool ShadowHit(const Ray& ray, double& tMin) const;
};

#endif
