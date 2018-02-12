// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 02/21/15.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "Material.h"

//Default Constructor
Material::Material(void)
{
	
}


//Destructor
Material::~Material(void)
{

}

RGBColor Material::Shade(ShadeRecord& sr)
{
	return RGBColor(0,0,0);
}

RGBColor Material::PathShade(ShadeRecord& sr)
{
	return RGBColor(0, 0, 0);
}

RGBColor Material::GetEmittedRadiance(ShadeRecord& sr)
{
	return RGBColor(0, 0, 0);
}
