// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 04/03/16.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "WhittedTracer.h"

//Default Constructor
WhittedTracer::WhittedTracer(void)
{

}

WhittedTracer::WhittedTracer(World* world): Tracer(world)
{
	
}


//Destructor
WhittedTracer::~WhittedTracer(void)
{

}


//BuildWorld Function
RGBColor WhittedTracer::TraceRay(const Ray ray, const int& currentDepth) const
{
	//cout << "currentDepth: " << currentDepth << "\n";
	if (currentDepth > worldPtr->reflectionDepth)
	{
		return black;	//So that zero is added to r, g and b components of the color at hitpoint
	}
	else
	{
		//if(currentDepth > 0)
		//	cout << "CurrentDepth: " << currentDepth << "\n";
		
		ShadeRecord sr = worldPtr->MultipleObjectsHitFunction(ray);

		if (sr.objectHit == true)
		{
			sr.ray = ray;
			sr.rayDepth = currentDepth;

			RGBColor color = sr.materialPtr->Shade(sr);
//			if (sr.rayDepth == 2)
//				color.PrintValues();
			return color;
		}
		else
		{
			return worldPtr->bgColor;
		}
	}
}

