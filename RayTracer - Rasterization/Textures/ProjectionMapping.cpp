// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 03/20/16.
//  Copyright © 2016 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "ProjectionMapping.h"

//Default Constructor
ProjectionMapping::ProjectionMapping(void)
{
	ComputeNormals();
}

//Destructor
ProjectionMapping::~ProjectionMapping(void)
{

}

void ProjectionMapping::ComputeNormals(void)
{
	n2 = Vector3D(0.15,-0.2,1).UnitVector();
	Vector3D up(0,1,0);

	n0 = (up^n2).UnitVector();
	n1 = (n2^n0).UnitVector();

	std::cout << "n0: ";
	n0.PrintValues();
	std::cout << "n1: ";
	n1.PrintValues();
	std::cout << "n2: ";
	n2.PrintValues();

	distance = 100;
	projectionCenter = Point3D(160, 150, -100);
}

RGBColor ProjectionMapping::MapToImage(const ShadeRecord& sr, Image* imagePtr) const
{
	Vector3D localHitPoint = sr.localHitPoint;

	Vector3D tempVector = sr.hitPoint - projectionCenter;
	Vector3D tempVector2 = n2*distance;
	Vector3D projCenter(projectionCenter.x, projectionCenter.y, projectionCenter.z);
	Vector3D tempVector3 = (tempVector * distance) / (n2*tempVector) - projCenter - tempVector2;

	float x = (n0 / -300)*(tempVector3);
	float y = (n1 / 94)*(tempVector3);

	//float u = localHitPoint.x;
	//float v = localHitPoint.y;

	float u = (x + 1.0) / 2.0;
	float v = (y + 1.0) / 2.0;

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

