// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 02/21/16.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "Matte.h"

//Default Constructor
Matte::Matte(void)
{
	ambientBRDF = new Lambertian;
	diffuseBRDF = new Lambertian;
}

Matte::Matte(Sampler* samplerPtr)
{
	samplerPtr->MapSamplesToHemiSphere(1);
	ambientBRDF = new Lambertian(samplerPtr);
	diffuseBRDF = new Lambertian(samplerPtr);
}

//Destructor
Matte::~Matte(void)
{

}

//Matte& Matte::operator= (Matte matte)
//{
//	return *this;
//}

void Matte::SetAmbientBRDF(const float& ka, const RGBColor& colorObj)
{
	ambientBRDF->kd = ka;
	ambientBRDF->diffuseColor = colorObj;
}

void Matte::SetDiffuseBRDF(const float& kdVal, const RGBColor& colorObj)
{
	diffuseBRDF->kd = kdVal;
	diffuseBRDF->diffuseColor = colorObj;
}

RGBColor Matte::Shade(ShadeRecord& sr)
{

	Vector3D d = sr.ray.rayDirection;

	Vector3D wo(-d.x, -d.y, -d.z); //Changing the ray direction

	World *localWorldPtr = sr.worldPtr;

	RGBColor currentColor = ambientBRDF->Rho(sr, wo) * localWorldPtr->ambientLightPtr->IncomingRadiance(sr);

	int n = localWorldPtr->lights.size();

	for (int i = 0; i < n; i++)
	{
		Light *light = localWorldPtr->lights[i];
		Vector3D wi = light->GetLightDirection(sr);
		
		float dotProduct = sr.normal * wi;

		if (dotProduct > 0)	//Surface (normal) is facing the light
		{
			bool pointInShadow = false;
			if (light->shadows == true)
			{
				if (light->IsPointInShadow(sr, wi))
				{
					pointInShadow = true;
				}
			}

			if (!pointInShadow)
				currentColor += (diffuseBRDF->GetBRDF(sr, wo, wi) * localWorldPtr->lights[i]->IncomingRadiance(sr) * dotProduct);
		}
		currentColor = currentColor.ClampBasedOnMaxValue();
	}

	return currentColor;
}

RGBColor Matte::PathShade(ShadeRecord& sr)
{

	Vector3D d = sr.ray.rayDirection;

	Vector3D wo(-d.x, -d.y, -d.z); //Changing the ray direction
	Vector3D wi;

	World *localWorldPtr = sr.worldPtr;

	RGBColor currentColor = diffuseBRDF->SampleBRDF(sr, wi, wo);

	float dotProduct = sr.normal * wi;

	float dividend = dotProduct * invPi;

	Ray newRay = Ray(sr.hitPoint, wi);

	//if(sr.normal.x == 0 && sr.normal.y == 1 && sr.normal.z == 0)
	//	newRay.rayDirection.PrintValues();

	return (currentColor * localWorldPtr->tracerPtr->TraceRay(newRay, sr.rayDepth + 1) * (dotProduct/ dividend) );
}

