#ifndef COMPOUNDOBJECT
#define COMPOUNDOBJECT

// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 03/27/16.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "GeometricObject.h"
#include <vector>

class CompoundObject:public GeometricObject
{
	public:
		
		std::vector<GeometricObject*> objects;
		BBox boundingBox;

		//Constructors

		CompoundObject(void);												//Default Constructor
		
		//Destructor

		~CompoundObject(void);

		//Member Functions

		bool hit(const Ray& ray, double& tMin, ShadeRecord& sr) const;					//Hit function which checks for ray intersections
		bool ShadowHit(const Ray& ray, double& tMin) const;

		void AddObject(GeometricObject* objectPtr);
		BBox GetBoundingBox(void);
		void SetMaterial(Material* materialPointer);
};

inline void CompoundObject::AddObject(GeometricObject* objectPtr)
{
	objects.push_back(objectPtr);
}

#endif
