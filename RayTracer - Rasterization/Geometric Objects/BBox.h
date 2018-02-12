#ifndef BBOX
#define BBOX

// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 03/26/16.
//  Copyright © 2016 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include <Math.h>
#include "Point3D.h"
#include "Ray.h"
#include "Constants.h"

class BBox
{
	public:
		
		Point3D minPoint;
		Point3D maxPoint;     

		//Constructors

		BBox(void);												//Default Constructor
		BBox(const Point3D& minPointObj, const Point3D& maxPointObj);
		BBox(const BBox& cube);								//Copy constructor
		
		//Destructor

		~BBox(void);

		//Member Functions

		//Cube& operator=(const Cube& cube);										//Assignment Operator
		bool hit(const Ray& ray, double& tMin) const;									//Hit function which checks for ray intersections

		bool Inside(Point3D point) const;
};

#endif
