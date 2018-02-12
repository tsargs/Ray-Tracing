#ifndef GEOMETRIC_OBJECT
#define GEOMETRIC_OBJECT

// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 12/29/15.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "Ray.h"
#include "RGBColor.h"
#include "Constants.h"
#include "Normal.h"
#include "Material.h"
#include "BBox.h"

#include <Math.h>

class GeometricObject
{
	public:
		
		RGBColor color;
		mutable Material* materialPtr;

		//Constructors

		GeometricObject(void);										//Default Constructor
		GeometricObject(const GeometricObject& geometricObject);	//Copy constructor
		
		//Destructor

		~GeometricObject(void);

		//Member Functions

		GeometricObject& GeometricObject::operator=(const GeometricObject& geometricObject);		//Assignment Operator
		virtual bool hit(const Ray& ray, double& tMin, ShadeRecord& sr) const;				//Hit function which checks for ray intersections
		virtual bool ShadowHit(const Ray& ray, double& tMin) const;

		virtual BBox GetBoundingBox(void);
		virtual void AddObject(GeometricObject* objectPtr);

	//protected:
	//	RGBColor color;
};

#endif
