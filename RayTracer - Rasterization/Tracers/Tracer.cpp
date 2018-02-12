// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 12/30/15.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "Tracer.h"

//Default Constructor
Tracer::Tracer(void) : worldPtr(nullptr)
{

}

Tracer::Tracer(World* worldPtrArg) : worldPtr(worldPtrArg)
{

}

//Destructor
Tracer::~Tracer(void)
{

}

//TraceRay Function

 RGBColor Tracer::TraceRay(const Ray& ray) const
{
	return black;
}

 RGBColor Tracer::TraceRay(const Ray ray, const int& rayDepth) const
 {
	 return black;
 }

