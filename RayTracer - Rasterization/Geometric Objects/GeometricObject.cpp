// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 12/30/15.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "GeometricObject.h"

//Default Constructor
GeometricObject::GeometricObject(void) : color(black)
{
	
}

//Copy constructor
GeometricObject::GeometricObject(const GeometricObject& geometricObject): color(geometricObject.color)
{
	
}

//Destructor
GeometricObject::~GeometricObject(void)
{

}

//Assignment Operator
GeometricObject& GeometricObject::operator=(const GeometricObject& geometricObject)
{
	color = geometricObject.color;

	return (*this);
}

bool GeometricObject::hit(const Ray & ray, double & tMin, ShadeRecord& sr) const
{
	return false;
}

bool GeometricObject::ShadowHit(const Ray & ray, double & tMin) const
{
	return false;
}

BBox GeometricObject::GetBoundingBox(void)
{
	return BBox();
}


void GeometricObject::AddObject(GeometricObject* objectPtr)
{
}

