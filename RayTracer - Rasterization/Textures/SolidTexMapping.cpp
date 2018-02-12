// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 03/21/16.
//  Copyright © 2016 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "SolidTexMapping.h"

//Default Constructor
SolidTexMapping::SolidTexMapping(void)
{
	ComputeNormals();
}

//Destructor
SolidTexMapping::~SolidTexMapping(void)
{

}

void SolidTexMapping::ComputeNormals(void)
{
	n2 = Vector3D(0.5,-0.5,1).UnitVector();
	Vector3D up(0,1,0);

	n0 = (up^n2).UnitVector();
	n1 = (n2^n0).UnitVector();

	std::cout << "n0: ";
	n0.PrintValues();
	std::cout << "n1: ";
	n1.PrintValues();
	std::cout << "n2: ";
	n2.PrintValues();

	distance = 120;
	projectionCenter = Point3D(230, 40, -240);
}

RGBColor SolidTexMapping::MapToImage(const ShadeRecord& sr, Image* imagePtr) const
{
	Vector3D tempVector = sr.hitPoint - projectionCenter;

	float x = (n0 / -160)*(tempVector);
	float y = (n1 / 50)*(tempVector);

	float u = x - (int)x;

	if (u < 0)
		u = 1 - u;

	float v = y - (int)y;

	if (v < 0)
		v = 1 - v;

	int i = (int)((imagePtr->width - 1) * u);
	int j = (int)((imagePtr->height - 1) * v);

	int tempIndex = j*(imagePtr->width) + i;

	/*
	if(u < 0 || u > 1)
	std::cout << "u: " << u << "\n";
	if (v < 0 || v > 1)
	std::cout << "v: " << v << "\n";
	*/

	if (u < 0 || u > 1)
		return RGBColor(0.6, 0.8, 0.5);

	if (v < 0 || v > 1)
		return RGBColor(0.6, 0.8, 0.5);


	if (tempIndex >= 0 && tempIndex <= imagePtr->width * imagePtr->height)
		return imagePtr->pixmap[tempIndex];
	else
		return RGBColor(0.6,0.7,0.5);
}

