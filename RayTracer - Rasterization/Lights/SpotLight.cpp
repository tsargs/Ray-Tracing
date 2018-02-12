// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 02/26/15.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "SpotLight.h"

//Default Constructor
SpotLight::SpotLight(void)
{
	
}

SpotLight::SpotLight(const RGBColor& colorObj, const float& iVal, const Point3D pointObj, const Point3D& lookAtPos, const bool& shadowState):color(colorObj), intensity(iVal), position(pointObj), lookAtPosition(lookAtPos)
{
	shadows = shadowState;
	direction = (lookAtPos - position).UnitVector();
	std::cout << "direction: " << direction.x << ", " << direction.y << ", " << direction.z << "\n";
}

//Destructor
SpotLight::~SpotLight(void)
{

}

//Returns direction of incoming light at the hit point
Vector3D SpotLight::GetLightDirection(ShadeRecord &sr)
{
	Vector3D dirVector = (sr.hitPoint - position).UnitVector();
	Vector3D dirVector2 = -sr.normal;
	//std::cout << "Dot Product: " << dirVector * direction << "\n";
	//if (dirVector*direction > 0.8 && dirVector2*direction > 0.5)
	//if (dirVector2*direction > 0.5)
	if (dirVector*direction > 0.8)
		return (position - sr.hitPoint).UnitVector();
	else
		return Vector3D(0,0,0);
}

//Returns incoming radiance at hitpoint
RGBColor SpotLight::IncomingRadiance(ShadeRecord &sr)
{
	return color*intensity;
}

bool SpotLight::IsPointInShadow(const ShadeRecord& sr, const Vector3D& LightDirection) const
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