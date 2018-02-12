// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 03/06/16.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "SphericalMapping.h"

//Default Constructor
SphericalMapping::SphericalMapping(void)
{
	
}

//Destructor
SphericalMapping::~SphericalMapping(void)
{

}

RGBColor SphericalMapping::MapToImage(const ShadeRecord& sr, Image* imagePtr) const
{
	Vector3D localHitPoint = sr.localHitPoint;

	float theta = acos(localHitPoint.y); //acos(0.7);
	float solidAngle = atan2(localHitPoint.x, localHitPoint.z); //Returns atan(x/z)

	if (solidAngle < 0)
		solidAngle += (2 * pi);

	float u = solidAngle * inv2Pi;
	float v = 1.0 - (theta * invPi);

	int i = (int)((imagePtr->width - 1) * u);
	int j = (int)((imagePtr->height - 1) * v);

	int tempIndex = j*(imagePtr->width) + i;

	if (tempIndex >= 0 && tempIndex <= imagePtr->width * imagePtr->height)
		return imagePtr->pixmap[tempIndex];
	else
		return RGBColor(1.0,0.0,0.0);
}

