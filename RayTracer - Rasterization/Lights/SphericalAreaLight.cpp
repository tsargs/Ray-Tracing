// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 04/17/16.
//  Copyright © 2016 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "SphericalAreaLight.h"

//Default Constructor
SphericalAreaLight::SphericalAreaLight(void)
{
	
}

SphericalAreaLight::SphericalAreaLight(const RGBColor& colorObj, const float& iVal, const Point3D pointObj, const float& rVal, const bool& shadowState):color(colorObj), intensity(iVal), position(pointObj), radius(rVal)
{
	shadows = shadowState;
}

//Destructor
SphericalAreaLight::~SphericalAreaLight(void)
{

}

//Returns direction of incoming light at the hit point
Vector3D SphericalAreaLight::GetLightDirection(ShadeRecord &sr)
{
	Point3D samplePosition = position;
	samplePosition.x += (2 * (float)(rand()*inverseRandMax) - 1) * radius;
	samplePosition.y += (2 * (float)(rand()*inverseRandMax) - 1) * radius;
	samplePosition.z += (2 * (float)(rand()*inverseRandMax) - 1) * radius;
	return (samplePosition - sr.hitPoint).UnitVector();
}

//Returns incoming radiance at hitpoint
RGBColor SphericalAreaLight::IncomingRadiance(ShadeRecord &sr)
{
	return color*intensity;
}

bool SphericalAreaLight::IsPointInShadow(const ShadeRecord& sr, const Vector3D& LightDirection) const
{
	Ray shadowRay;
	shadowRay.origin = sr.hitPoint;
	shadowRay.rayDirection = LightDirection;

	int n = sr.worldPtr->objectsInScene.size();
	int i = 0;
	bool obstructionFound = false;
	double t = 0;
	double tMin = shadowRay.origin.Distance(position);  //Distance from hit point (shadow ray origin) to the light location
	//cout << "tMin: " << tMin << "\n";
	while (i < n && obstructionFound == false)
	{
		if (sr.worldPtr->objectsInScene[i]->ShadowHit(shadowRay, t) && t < tMin)
			obstructionFound = true;

		++i;
	}

	return obstructionFound;
}