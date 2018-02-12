// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 03/27/16.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "CompoundObject.h"

//Default Constructor
CompoundObject::CompoundObject(void)
{
}

//Destructor
CompoundObject::~CompoundObject(void)
{

}

BBox CompoundObject::GetBoundingBox(void)
{
	return boundingBox;
}


void CompoundObject::SetMaterial(Material* materialPointer)
{
	int objectCount = objects.size();

	for (int i = 0; i < objectCount; i++)
	{
		objects[i]->materialPtr = materialPointer;
	}
}

//Definition of Hit function declared in the base class Geometric Object
bool CompoundObject::hit(const Ray& ray, double& tMin, ShadeRecord& sr) const
{
	double t;
	tMin = kMaxValue;
	int objectCount = objects.size();
	Vector3D tempNormal;
	Point3D tempPoint;
	bool objectHit = false;

	for (int i = 0; i < objectCount; i++)
	{
		if (objects[i]->hit(ray, t, sr) == true && t < tMin)
		{
			materialPtr = objects[i]->materialPtr;
			//Backup of values of object with least t - so that we can add this to the shade record eventually after all the objects are checked for intersection
			tMin = t;
			tempNormal = sr.normal;
			tempPoint = sr.hitPoint;

			objectHit = true;
		}
	}

	if (objectHit == true)
	{
		sr.t = tMin;
		sr.normal = tempNormal;
		sr.hitPoint = tempPoint;
	}

	return objectHit;
}

bool CompoundObject::ShadowHit(const Ray& ray, double& tMin) const
{
	double t;
	tMin = kMaxValue;
	int objectCount = objects.size();
	Vector3D tempNormal;
	Point3D tempPoint;
	bool objectHit = false;

	for (int i = 0; i < objectCount; i++)
	{
		if (objects[i]-> ShadowHit(ray, t) == true && t < tMin)
		{
			materialPtr = objects[i]->materialPtr;
			//Backup of values of object with least t - so that we can add this to the shade record eventually after all the objects are checked for intersection
			tMin = t;

			objectHit = true;
		}
	}

	return objectHit;
}