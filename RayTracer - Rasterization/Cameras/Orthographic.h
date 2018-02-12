#ifndef ORTHOGRAPHIC
#define ORTHOGRAPHIC

// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 02/05/15.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "Camera.h"
#include "World.h"

class Orthographic:public Camera
{
	public:
		
		//Constructors
		Orthographic(void);										//Default Constructor
		Orthographic(World* worldPointer);
		
		//Destructor

		~Orthographic(void);

		//Member Functions

		void RenderScene();
};

#endif
