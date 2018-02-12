#ifndef PROJECT01TRACER
#define PROJECT01TRACER

// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 12/30/15.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "Tracer.h"
#include "World.h"

class Project01Tracer:public Tracer
{
	public:
	
		//Constructors

		Project01Tracer(void);												//Default Constructor
		
		Project01Tracer(World* world);

		//Destructor

		~Project01Tracer(void);

		//Member Functions

		RGBColor TraceRay(const Ray& ray) const;

};

#endif
