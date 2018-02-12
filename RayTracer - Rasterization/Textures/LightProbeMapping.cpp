// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 03/06/16.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "LightProbeMapping.h"

//Default Constructor
LightProbeMapping::LightProbeMapping(void)
{
	
}

//Destructor
LightProbeMapping::~LightProbeMapping(void)
{

}

RGBColor LightProbeMapping::MapToImage(const ShadeRecord& sr, Image* imagePtr) const
{
	Vector3D localHitPoint = sr.localHitPoint;

	float alpha = acos(localHitPoint.z);
	float invDenominaotr = 1/sqrt(localHitPoint.x*localHitPoint.x + localHitPoint.y*localHitPoint.y);
	float sinBeta = localHitPoint.y * invDenominaotr;
	float cosBeta = localHitPoint.x * invDenominaotr;

	float u = (1 + (alpha * invPi)*cosBeta) * 0.5;
	float v = (1 + (alpha * invPi)*sinBeta) * 0.5;

	int i = (int)((imagePtr->width - 1) * u);
	int j = (int)((imagePtr->height - 1) * v);

	int tempIndex = j*(imagePtr->width) + i;

	if (tempIndex >= 0 && tempIndex <= imagePtr->width * imagePtr->height)
		return imagePtr->pixmap[tempIndex];
	else
		return RGBColor(1.0,0.0,0.0);
}

