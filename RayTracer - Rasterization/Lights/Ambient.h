#ifndef AMBIENT
#define AMBIENT

// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 02/21/15.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "Light.h"

class Ambient:public Light
{
	public:

		RGBColor color;
		float intensity;

		//Constructors
		Ambient(void);										//Default Constructor
		Ambient(const RGBColor& colorObj, const float& iVal);

		//Destructor

		~Ambient(void);

		//Member Functions

		//Returns direction of incoming light at the hit point
		Vector3D GetLightDirection(ShadeRecord &sr);

		//Returns incoming radiance at hitpoint
		RGBColor IncomingRadiance(ShadeRecord &sr);
};

#endif
