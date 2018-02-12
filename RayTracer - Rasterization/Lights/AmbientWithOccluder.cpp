// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 04/16/16.
//  Copyright © 2016 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "AmbientWithOccluder.h"

//Default Constructor
AmbientWithOccluder::AmbientWithOccluder(void)
{
	
}

AmbientWithOccluder::AmbientWithOccluder(const RGBColor& colorObj, const float& iVal, const float& baseShade, Sampler *samplerPtr):color(colorObj), intensity(iVal), baseShadeFactor(baseShade), localSampler(samplerPtr)
{

}

//Destructor
AmbientWithOccluder::~AmbientWithOccluder(void)
{

}

//Returns direction of incoming light at the hit point
Vector3D AmbientWithOccluder::GetLightDirection(ShadeRecord &sr)
{
	return Vector3D(0,0,0);
}

//Returns incoming radiance at hitpoint
RGBColor AmbientWithOccluder::IncomingRadiance(ShadeRecord &sr)
{
	SetupOrthonormalBase(sr.normal);

	if (IsPointInShadow(sr, Vector3D(0, 0, 0)))
	{
		/*
		if (sr.normal.x == 0 && sr.normal.y == 1 && sr.normal.z == 0)
		{
			if(sr.hitPoint.x < 120)
				if(sr.hitPoint.z > 39 && sr.hitPoint.z < 41)
					cout << "hit\n";
		}
		*/
		return color*intensity*baseShadeFactor;
	}
	else
		return color*intensity;
}

void AmbientWithOccluder::SetupOrthonormalBase(Vector3D normalVector)
{
	w = normalVector;
	v = (w^up).UnitVector();
	u = v^w;
}

bool AmbientWithOccluder::IsPointInShadow(const ShadeRecord& sr, const Vector3D& LightDirection) const
{
	Ray shadowRay;

	Point3D samplePoint = localSampler->FetchHemisPhericalSample();

	shadowRay.origin = sr.hitPoint;
	shadowRay.rayDirection = (u*samplePoint.x + v*samplePoint.y + w*samplePoint.z);

	int n = sr.worldPtr->objectsInScene.size();
	int i = 0;
	bool obstructionFound = false;
	double t = 0;
	double tMin = kMaxValue;  //Distance from hit point (shadow ray origin) to the light location

	while (i < n && obstructionFound == false)
	{
		if (sr.worldPtr->objectsInScene[i]->ShadowHit(shadowRay, t) && t < tMin)
			obstructionFound = true;

		++i;
	}

	return obstructionFound;
}