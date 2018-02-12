// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 03/06/16.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "PlainTexture.h"

//Default Constructor
PlainTexture::PlainTexture(void)
{
	constantColor = RGBColor(0,0,0);
}

PlainTexture::PlainTexture(const RGBColor& colorObj)
{
	constantColor = colorObj;
}

//Destructor
PlainTexture::~PlainTexture(void)
{

}

RGBColor PlainTexture::GetColor(const ShadeRecord& sr) const
{
	return constantColor;
}


