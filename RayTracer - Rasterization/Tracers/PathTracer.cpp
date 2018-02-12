// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 05/02/16.
//  Copyright © 2016 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "PathTracer.h"

//Default Constructor
PathTracer::PathTracer(void)
{

}

PathTracer::PathTracer(World* world): Tracer(world)
{
	
}


//Destructor
PathTracer::~PathTracer(void)
{

}


//BuildWorld Function
RGBColor PathTracer::TraceRay(const Ray ray, const int& currentDepth) const
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

			RGBColor color = sr.materialPtr->PathShade(sr);
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

