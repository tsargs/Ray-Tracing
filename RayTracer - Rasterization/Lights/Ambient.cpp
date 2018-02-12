// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 02/21/15.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "Ambient.h"

//Default Constructor
Ambient::Ambient(void)
{
	
}

Ambient::Ambient(const RGBColor& colorObj, const float& iVal):color(colorObj), intensity(iVal)
{

}

//Destructor
Ambient::~Ambient(void)
{

}

//Returns direction of incoming light at the hit point
Vector3D Ambient::GetLightDirection(ShadeRecord &sr)
{
	return Vector3D(0,0,0);
}

//Returns incoming radiance at hitpoint
RGBColor Ambient::IncomingRadiance(ShadeRecord &sr)
{
	return color*intensity;
}