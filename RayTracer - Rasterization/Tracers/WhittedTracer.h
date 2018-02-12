#ifndef WHITTEDTRACER
#define WHITTEDTRACER

// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 04/03/16.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "Tracer.h"
#include "World.h"

class WhittedTracer:public Tracer
{
	public:
	
		//Constructors

		WhittedTracer(void);												//Default Constructor
		
		WhittedTracer(World* world);

		//Destructor

		~WhittedTracer(void);

		//Member Functions

		RGBColor TraceRay(const Ray ray, const int& currentDepth) const;
};

#endif
