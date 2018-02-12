// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 03/20/16.
//  Copyright © 2016 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "FBMTexture.h"

//Default Constructor
FBMTexture::FBMTexture(void) : noisePtr(nullptr)
{
}

FBMTexture::FBMTexture( LatticeNoise* noisePointer) : noisePtr(noisePointer)
{
}

//Destructor
FBMTexture::~FBMTexture(void)
{
}

void FBMTexture::SetColor(const RGBColor& colorVal)
{
	color = colorVal;
}

void FBMTexture::SetMinMaxValues(const float& minVal, const float& maxVal)
{
	minValue = minVal;
	maxValue = maxVal;
}

RGBColor FBMTexture::GetColor(const ShadeRecord& sr) const
{
	//float noiseValue = noisePtr->GetFractalSumValue(sr.localHitPoint);
	float noiseValue = noisePtr->GetFBMValue(sr.localHitPoint);

	noiseValue = minValue + (maxValue - minValue) * noiseValue;	
	return color * noiseValue;
}


