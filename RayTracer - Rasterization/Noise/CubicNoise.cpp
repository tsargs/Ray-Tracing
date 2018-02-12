// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 03/20/16.
//  Copyright © 2016 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "CubicNoise.h"

//Default Constructor
CubicNoise::CubicNoise(void)
{

}

//Destructor
CubicNoise::~CubicNoise(void)
{

}

float CubicNoise::GetNoiseValue(const Vector3D& point) const
{
	int intX = floor(point.x); 
	int intY = floor(point.y);
	int intZ = floor(point.z);

	float fX = point.x - intX;
	float fY = point.y - intY;
	float fZ = point.z - intZ;

	float xKnots[4], yKnots[4], zKnots[4];

	for (int i = -1; i <= 2; i++)
	{
		for (int j = -1; j <= 2; j++)
		{
			for (int k = -1; k <= 2; k++)
			{
				xKnots[k + 1] = valueTable[INDEX(intX + k, intY + j, intZ + i)];
			}
			yKnots[j + 1] = FourKnotSpline(fX, xKnots);
		}
		zKnots[i + 1] = FourKnotSpline(fY, yKnots);
	}

	float finalValue = FourKnotSpline(fZ, zKnots);

	if(finalValue < -1 )
		return -1;
	else if (finalValue > 1)
		return 1;
	else
		return finalValue;
}

