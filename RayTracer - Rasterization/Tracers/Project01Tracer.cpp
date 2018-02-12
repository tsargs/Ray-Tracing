// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 12/30/15.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "Project01Tracer.h"

//Default Constructor
Project01Tracer::Project01Tracer(void)
{

}

Project01Tracer::Project01Tracer(World* world): Tracer(world)
{
	
}


//Destructor
Project01Tracer::~Project01Tracer(void)
{

}


//BuildWorld Function
RGBColor Project01Tracer::TraceRay(const Ray& ray) const
{
	ShadeRecord sr = worldPtr->MultipleObjectsHitFunction(ray);
	
	if (sr.objectHit == true)
	{
		sr.ray = ray;
		return sr.materialPtr->Shade(sr);
	}
	else
	{
		return worldPtr->bgColor;
	}
}

