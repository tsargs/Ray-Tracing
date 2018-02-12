// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 03/20/16.
//  Copyright © 2016 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "TurbulenceTexture.h"

//Default Constructor
TurbulenceTexture::TurbulenceTexture(void) : noisePtr(nullptr)
{
}

TurbulenceTexture::TurbulenceTexture( LatticeNoise* noisePointer) : noisePtr(noisePointer)
{
}

//Destructor
TurbulenceTexture::~TurbulenceTexture(void)
{
}

void TurbulenceTexture::SetColor(const RGBColor& colorVal)
{
	color = colorVal;
}

void TurbulenceTexture::SetMinMaxValues(const float& minVal, const float& maxVal)
{
	minValue = minVal;
	maxValue = maxVal;
}

RGBColor TurbulenceTexture::GetColor(const ShadeRecord& sr) const
{
	float noiseValue = noisePtr->GetTurbulence(sr.localHitPoint);
	if (noiseValue < 0)
		std::cout << "Below Zero\n";
	if (noiseValue > 4)
		std::cout << "Above 8\n";
	noiseValue = minValue + (maxValue - minValue) * noiseValue;
	return color * noiseValue;
}


