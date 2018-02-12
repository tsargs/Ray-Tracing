#ifndef PATHTRACER
#define PATHTRACER

// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 05/02/16.
//  Copyright © 2016 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "Tracer.h"
#include "World.h"

class PathTracer:public Tracer
{
	public:
	
		//Constructors

		PathTracer(void);												//Default Constructor
		
		PathTracer(World* world);

		//Destructor

		~PathTracer(void);

		//Member Functions

		RGBColor TraceRay(const Ray ray, const int& currentDepth) const;
};

#endif
