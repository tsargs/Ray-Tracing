#ifndef FLATMESHTRIANGLE
#define FLATMESHTRIANGLE

// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 03/27/16.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "MeshTriangle.h"

class FlatMeshTriangle:public MeshTriangle
{
	public:
		
		//Constructors

		FlatMeshTriangle(void);												//Default Constructor
		
		//Destructor

		~FlatMeshTriangle(void);

		//Member Functions

		bool hit(const Ray& ray, double& tMin, ShadeRecord& sr) const;					//Hit function which checks for ray intersections
};

#endif
