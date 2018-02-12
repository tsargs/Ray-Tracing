#ifndef TRACER
#define TRACER

// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 12/30/15.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "constants.h"
#include "Ray.h"
//#include "World.h"

class World;

class Tracer
{
	public:
		
		World* worldPtr;
		
		//Constructors

		Tracer(void);												//Default Constructor
		Tracer(World* worldPtrArg);
		
		//Destructor

		~Tracer(void);

		//Member Functions

		virtual RGBColor TraceRay(const Ray& ray) const;
		virtual RGBColor TraceRay(const Ray ray, const int& rayDepth) const;
};

#endif
