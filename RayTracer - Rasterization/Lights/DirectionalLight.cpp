// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 02/21/15.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "DirectionalLight.h"

//Default Constructor
DirectionalLight::DirectionalLight(void)
{
	
}

DirectionalLight::DirectionalLight(const RGBColor& colorObj, const float& iVal, const Point3D pointObj, const Vector3D& directionVector, const bool& shadowState):color(colorObj), intensity(iVal), position(pointObj)
{
	Vector3D tempVector = directionVector;
	direction = -tempVector.UnitVector();
	shadows = shadowState;
}

//Destructor
DirectionalLight::~DirectionalLight(void)
{

}

//Returns direction of incoming light at the hit point
Vector3D DirectionalLight::GetLightDirection(ShadeRecord &sr)
{
	return direction;
}

//Returns incoming radiance at hitpoint
RGBColor DirectionalLight::IncomingRadiance(ShadeRecord &sr)
{
	return color*intensity;
}

bool DirectionalLight::IsPointInShadow(const ShadeRecord& sr, const Vector3D& LightDirection) const
{

	Ray shadowRay;
	shadowRay.origin = sr.hitPoint;
	shadowRay.rayDirection = LightDirection;

	int n = sr.worldPtr->objectsInScene.size();
	int i = 0;
	bool obstructionFound = false;
	double t = 0;
	double tMin = shadowRay.origin.Distance(position);  //Distance from hit point (shadow ray origin) to the light location
	//double tMin = kMaxValue;

	//cout << "tMin: " << tMin << "\n";
	while (i < n && obstructionFound == false)
	{
		if (sr.worldPtr->objectsInScene[i]->ShadowHit(shadowRay, t) && t < tMin)
			obstructionFound = true;

		++i;
	}

	return obstructionFound;
}