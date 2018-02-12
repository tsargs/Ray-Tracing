// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 01/14/16.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "ShadeRecord.h"

ShadeRecord::ShadeRecord(void):objectHit(false)
{

}

//Destructor
ShadeRecord::~ShadeRecord(void)
{

}


//Assignment Operator
ShadeRecord& ShadeRecord::operator=(const ShadeRecord& srObject)
{
	color = srObject.color;
	ray = srObject.ray;
	t = srObject.t;
	hitPoint = srObject.hitPoint;
	localHitPoint = srObject.localHitPoint;
	worldPtr = srObject.worldPtr;
	materialPtr = srObject.materialPtr;
	objectHit = srObject.objectHit;
	normal = srObject.normal;
	rayDepth = srObject.rayDepth;

	return (*this);
}


