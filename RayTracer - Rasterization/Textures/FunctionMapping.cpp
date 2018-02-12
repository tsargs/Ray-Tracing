// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 03/06/16.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "FunctionMapping.h"

//Default Constructor
FunctionMapping::FunctionMapping(void)
{
	
}

//Destructor
FunctionMapping::~FunctionMapping(void)
{

}

RGBColor FunctionMapping::MapToImage(const ShadeRecord& sr, Image* imagePtr) const
{
	Vector3D localHitPoint = sr.localHitPoint;

	float theta = acos(localHitPoint.y); //acos(0.7);
	float solidAngle = atan2(localHitPoint.x, localHitPoint.z); //Returns atan(x/z)

	if (solidAngle < 0)
		solidAngle += (2 * pi);

	float u = solidAngle * inv2Pi;
	float v = 1.0 - (theta * invPi);

	//RGBColor tempColor = red * cos(localHitPoint.x) + green * sin(localHitPoint.y) + blue * tan(localHitPoint.z);

	RGBColor tempColor = red* (1/tan(localHitPoint.y)) + red * (1/tan(localHitPoint.z));

	return tempColor;

	/*
	int i = (int)((imagePtr->width - 1) * cos(u));
	int j = (int)((imagePtr->height - 1) * sin(v));

	int tempIndex = j*(imagePtr->width) + i;

	if (tempIndex >= 0 && tempIndex <= imagePtr->width * imagePtr->height)
		return imagePtr->pixmap[tempIndex];
	else
		return RGBColor(1.0,0.0,0.0);
		*/
}

