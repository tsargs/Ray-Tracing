// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 02/21/15.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "PointLight.h"

//Default Constructor
PointLight::PointLight(void)
{
	
}

PointLight::PointLight(const RGBColor& colorObj, const float& iVal, const Point3D pointObj, const bool& shadowState):color(colorObj), intensity(iVal), position(pointObj)
{
	shadows = shadowState;
}

//Destructor
PointLight::~PointLight(void)
{

}

//Returns direction of incoming light at the hit point
Vector3D PointLight::GetLightDirection(ShadeRecord &sr)
{
	return (position - sr.hitPoint).UnitVector();
}

//Returns incoming radiance at hitpoint
RGBColor PointLight::IncomingRadiance(ShadeRecord &sr)
{
	return color*intensity;
}

bool PointLight::IsPointInShadow(const ShadeRecord& sr, const Vector3D& LightDirection) const
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