// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 02/21/15.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "Light.h"

//Default Constructor
Light::Light(void) 
{
	
}


//Destructor
Light::~Light(void)
{

}

bool Light::IsPointInShadow(const ShadeRecord & sr, const Vector3D & lightDirection) const
{
	return false;
}


