// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 03/06/16.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "RectangularMapping.h"

//Default Constructor
RectangularMapping::RectangularMapping(void)
{
	
}

//Destructor
RectangularMapping::~RectangularMapping(void)
{

}

RGBColor RectangularMapping::MapToImage(const ShadeRecord& sr, Image* imagePtr) const
{
	Vector3D localHitPoint = sr.localHitPoint;

	float u = localHitPoint.x;
	float v = localHitPoint.y;

	int i = (int)((imagePtr->width - 1) * u);
	int j = (int)((imagePtr->height - 1) * v);

	int tempIndex = j*(imagePtr->width) + i;

	if (tempIndex >= 0 && tempIndex <= imagePtr->width * imagePtr->height)
		return imagePtr->pixmap[tempIndex];
	else
		return RGBColor(1.0,0.0,0.0);
}

