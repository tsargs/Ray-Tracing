// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 05/02/16.
//  Copyright © 2016 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "Emissive.h"

//Default Constructor
Emissive::Emissive(void)
{

}

Emissive::Emissive(const float& rVal, const RGBColor& colorObj)
{
	radianceFactor = rVal;
	emissiveColor = colorObj;
	colorProduct = emissiveColor * radianceFactor;
}

//Destructor
Emissive::~Emissive(void)
{

}

RGBColor Emissive::GetEmittedRadiance(ShadeRecord &sr)
{
	return colorProduct;
}


RGBColor Emissive::Shade(ShadeRecord& sr)
{
	Vector3D normalVector = sr.normal;
	Vector3D d = sr.ray.rayDirection;

	float dotProduct = d * normalVector;

	if (dotProduct > 0)
		return colorProduct;
	else
		return RGBColor(0, 0, 0);
}

RGBColor Emissive::PathShade(ShadeRecord& sr)
{
	Vector3D normalVector = sr.normal;
	Vector3D d = sr.ray.rayDirection;

	float dotProduct = d * normalVector;

	if (dotProduct > 0)
		return colorProduct;
	else
		return RGBColor(0, 0, 0);
}
