// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 12/30/15.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "ViewPlane.h"

//Default Constructor
ViewPlane::ViewPlane(void) : width(500), height(300), pixelSize(1)
{

}

ViewPlane::ViewPlane(const int& widthVal, const int& heightVal, const float& sizeVal) : width(widthVal), height(heightVal), pixelSize(sizeVal)
{

}

//Destructor
ViewPlane::~ViewPlane(void)
{

}

void ViewPlane::SetSampler(int type, int noOfSamples)
{
	samplesPerPixel = noOfSamples;

	if (type == 0)
	{
		samplerPtr = new RegularSampler(noOfSamples);
	}
	else if (type == 1)
	{
		samplerPtr = new JitteredSampler(noOfSamples);
	}

}
