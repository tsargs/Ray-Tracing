#ifndef LIGHT
#define LIGHT

// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 02/21/15.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "Vector3D.h"
#include "ShadeRecord.h"
#include <iostream>

class Light
{
	public:
		bool shadows;

		//Constructors
		Light(void);										//Default Constructor

		//Destructor

		~Light(void);

		//Member Functions

		//Returns direction of incoming light at the hit point
		virtual Vector3D GetLightDirection(ShadeRecord &sr) = 0;

		//Returns incoming radiance at hitpoint
		virtual RGBColor IncomingRadiance(ShadeRecord &sr)  = 0;

		virtual bool IsPointInShadow(const ShadeRecord& sr, const Vector3D& lightDirection) const;
};

#endif
