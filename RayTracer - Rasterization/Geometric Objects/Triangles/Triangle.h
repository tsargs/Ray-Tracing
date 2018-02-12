#ifndef TRIANGLE
#define TRIANGLE

// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 03/27/16.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "GeometricObject.h"

class Triangle:public GeometricObject
{
	public:
		
		Point3D v0, v1, v2;
		Vector3D normal;

		//Constructors

		Triangle(void);												//Default Constructor
		Triangle(const Point3D& pointOne, const Point3D& pointTwo, const Point3D& pointThree);
		Triangle(const Triangle& triangle);								//Copy constructor
		
		//Destructor

		~Triangle(void);

		//Member Functions

		Triangle& operator=(const Triangle& triangle);										//Assignment Operator
		bool hit(const Ray& ray, double& tMin, ShadeRecord& sr) const;					//Hit function which checks for ray intersections
		bool ShadowHit(const Ray& ray, double& tMin) const;
};

#endif
