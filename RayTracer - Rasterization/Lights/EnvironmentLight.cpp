// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 05/02/16.
//  Copyright © 2016 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "EnvironmentLight.h"

//Default Constructor
EnvironmentLight::EnvironmentLight(void)
{
	
}

EnvironmentLight::EnvironmentLight(Sampler *samplerPtr, Material *materialPtr, const bool& shadowState):localSampler(samplerPtr), localMaterial(materialPtr)
{
	shadows = shadowState;
}

//Destructor
EnvironmentLight::~EnvironmentLight(void)
{

}

void EnvironmentLight::SetupOrthonormalBase(Vector3D normalVector)
{
	w = normalVector;
	v = (up^w).UnitVector();
	u = v^w;
}

//Returns direction of incoming light at the hit point
Vector3D EnvironmentLight::GetLightDirection(ShadeRecord &sr)
{
	//	cout << "GetLightDirection\n";
	SetupOrthonormalBase(sr.normal);
	
	Point3D samplePoint = localSampler->FetchHemisPhericalSample();
	lightDirection = u * samplePoint.x + v * samplePoint.y + w * samplePoint.z;

	return lightDirection;
}

//Returns incoming radiance at hitpoint
RGBColor EnvironmentLight::IncomingRadiance(ShadeRecord &sr)
{
	return localMaterial->GetEmittedRadiance(sr);
}


bool EnvironmentLight::IsPointInShadow(const ShadeRecord& sr, const Vector3D& LightDirection) const
{
	Ray shadowRay;

	//cout << "EnvironmentLight::IsPointInShadow\n";

	//Vector3D su, sv, sw;

	//sw = sr.normal;
	//sv = (w^up).UnitVector();
	//su = v^w;

	////Point3D samplePoint = localSampler->FetchHemisPhericalSample();

	//shadowRay.origin = sr.hitPoint;
	//shadowRay.rayDirection = (su*samplePoint.x + sv*samplePoint.y + sw*samplePoint.z);

	shadowRay.origin = sr.hitPoint;
	shadowRay.rayDirection = lightDirection;

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