// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 04/04/16.
//  Copyright © 2016 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "SVReflective.h"

//Default Constructor
SVReflective::SVReflective(void)
{
	ambientBRDF = new SVLambertian();
	diffuseBRDF = new SVLambertian();
	specularBRDF = new GlossySpecular();
	svPerfectSpecularBRDF = new SVPerfectSpecular();
}

SVReflective::SVReflective(Sampler* samplerPtr)
{
	ambientBRDF = new SVLambertian(samplerPtr);
	diffuseBRDF = new SVLambertian(samplerPtr);
	specularBRDF = new GlossySpecular(samplerPtr);
	svPerfectSpecularBRDF = new SVPerfectSpecular(samplerPtr);
}

//Destructor
SVReflective::~SVReflective(void)
{

}

void SVReflective::SetAmbientBRDF(const float& ka, Texture* texturePointer)
{
	ambientBRDF->kd = ka;
	ambientBRDF->texturePtr = texturePointer;
}

void SVReflective::SetDiffuseBRDF(const float& kdVal, Texture* texturePointer)
{
	diffuseBRDF->kd = kdVal;
	diffuseBRDF->texturePtr = texturePointer;
}

void SVReflective::SetNormalMap(Texture* texturePointer)
{
	diffuseBRDF->normalTexPtr = texturePointer;
	svPerfectSpecularBRDF->normalTexPtr = texturePointer;
}

void SVReflective::SetSpecularBRDF(const float& ksVal, const RGBColor& colorObj, const float& eVal)
{
	specularBRDF->ks = ksVal;
	specularBRDF->specularColor = colorObj;
	specularBRDF->e = eVal;
}

void SVReflective::SetPerfectSpecularBRDF(const float& krVal, const RGBColor& colorObj)
{
	svPerfectSpecularBRDF->kr = krVal;
	svPerfectSpecularBRDF->reflectiveColor = colorObj;
}

RGBColor SVReflective::PhongShade(ShadeRecord& sr)
{
	Vector3D wo = -sr.ray.rayDirection; //Changing the ray direction

	World *localWorldPtr = sr.worldPtr;

	RGBColor currentColor = ambientBRDF->Rho(sr, wo) * localWorldPtr->ambientLightPtr->IncomingRadiance(sr);

	int n = localWorldPtr->lights.size();


	for (int i = 0; i < n; i++)
	{
		Light *light = localWorldPtr->lights[i];
		Vector3D wi = light->GetLightDirection(sr);

		float dotProduct = diffuseBRDF->GetNormal(sr) * wi;

		if (dotProduct > 0) //Surface (normal) is facing the light
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
				currentColor += ((diffuseBRDF->GetBRDF(sr, wo, wi) + specularBRDF->GetBRDF(sr, wo, wi)) * localWorldPtr->lights[i]->IncomingRadiance(sr) * dotProduct);
		}
		currentColor = currentColor.ClampBasedOnMaxValue();
	}
	return currentColor;
}

RGBColor SVReflective::Shade(ShadeRecord& sr)
{
	Vector3D wo = -sr.ray.rayDirection; //Changing the ray direction
	Vector3D wi;
	World *localWorldPtr = sr.worldPtr;

	RGBColor reflectedColor = svPerfectSpecularBRDF->SampleBRDF(sr, wi, wo);

	float dotProduct = sr.normal * wi;
	RGBColor currentColor = PhongShade(sr);
	currentColor += reflectedColor * localWorldPtr->tracerPtr->TraceRay(Ray(sr.hitPoint, wi), sr.rayDepth + 1) * dotProduct;

	currentColor = currentColor.ClampBasedOnMaxValue();
	return currentColor;
}

