// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 04/11/16.
//  Copyright © 2016 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "SVTransparent.h"

//Default Constructor
SVTransparent::SVTransparent(void)
{
	ambientBRDF = new SVLambertian();
	diffuseBRDF = new SVLambertian();
	specularBRDF = new GlossySpecular();
	perfectSpecularBRDF = new SVPerfectSpecular();
	rimColor = black;
}

SVTransparent::SVTransparent(Sampler* samplerPtr)
{
	ambientBRDF = new SVLambertian(samplerPtr);
	diffuseBRDF = new SVLambertian(samplerPtr);
	specularBRDF = new GlossySpecular(samplerPtr);
	perfectSpecularBRDF = new SVPerfectSpecular(samplerPtr);
	rimColor = black;
}

//Destructor
SVTransparent::~SVTransparent(void)
{

}

void SVTransparent::SetAmbientBRDF(const float& ka, Texture* texturePointer)
{
	ambientBRDF->kd = ka;
	ambientBRDF->texturePtr = texturePointer;
}

void SVTransparent::SetDiffuseBRDF(const float& kdVal, Texture* texturePointer)
{
	diffuseBRDF->kd = kdVal;
	diffuseBRDF->texturePtr = texturePointer;
}

void SVTransparent::SetSpecularBRDF(const float& ksVal, const RGBColor& colorObj, const float& eVal)
{
	specularBRDF->ks = ksVal;
	specularBRDF->specularColor = colorObj;
	specularBRDF->e = eVal;
}

void SVTransparent::SetPerfectSpecularBRDF(const float& krVal, const RGBColor& colorObj)
{
	perfectSpecularBRDF->kr = krVal;
	perfectSpecularBRDF->reflectiveColor = colorObj;
}

void SVTransparent::SetTransparentProperties(const float& ktVal, const float& etaVal)
{
	kt = ktVal;
	eta = etaVal;
	invEta = 1 / eta;
	etaSquared = eta * eta;
	invEtaSquared = 1 / etaSquared;
}

void SVTransparent::SetNormalMap(Texture* texturePointer)
{
	diffuseBRDF->normalTexPtr = texturePointer;
	perfectSpecularBRDF->normalTexPtr = texturePointer;
}

RGBColor SVTransparent::PhongShade(ShadeRecord& sr)
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

RGBColor SVTransparent::Shade(ShadeRecord& sr)
{
	Vector3D wo = -sr.ray.rayDirection; //Changing the ray direction
	Vector3D wi;
	World *localWorldPtr = sr.worldPtr;
	
	Vector3D mappedNormal = diffuseBRDF->GetNormal(sr);

	RGBColor reflectiveColor = perfectSpecularBRDF->SampleBRDF(sr, wi, wo);
	RGBColor currentColor = PhongShade(sr);

	bool noTransmittedRay = CheckForTotalInternalReflection(sr.ray, mappedNormal);

	if (noTransmittedRay)
	{
		currentColor += localWorldPtr->tracerPtr->TraceRay(Ray(sr.hitPoint, wi), sr.rayDepth + 1);
	}
	else
	{
		float dotProduct = fabs(mappedNormal * wi);
		Vector3D wt;
		RGBColor transmittedColor = CalculateTransmittedColor(sr.ray, mappedNormal, wt);

		float dotProduct2 = fabs(mappedNormal * wt);

		currentColor += reflectiveColor * localWorldPtr->tracerPtr->TraceRay(Ray(sr.hitPoint, wi), sr.rayDepth + 1) * dotProduct;
		currentColor += transmittedColor * localWorldPtr->tracerPtr->TraceRay(Ray(sr.hitPoint, wt), sr.rayDepth + 1) * dotProduct2;
	}

	currentColor = currentColor.ClampBasedOnMaxValue();
	return currentColor;
}

bool SVTransparent::CheckForTotalInternalReflection(const Ray& ray, const Vector3D& normal)
{
	Vector3D rayDirection = ray.rayDirection;
	float cosAngleOfIncidence = -rayDirection * normal;

	float multiplicand;

	if (cosAngleOfIncidence < 0)
		multiplicand = etaSquared;
	else
		multiplicand = invEtaSquared;

	float determinant = 1 - (multiplicand * (1 - cosAngleOfIncidence * cosAngleOfIncidence));

	if (determinant < 0)
		return true;
	else
		return false;
}

RGBColor SVTransparent::CalculateTransmittedColor(const Ray& ray, const Vector3D& normal, Vector3D& wt)
{
	Vector3D rayDirection = ray.rayDirection;
	Vector3D localNormal = normal;
	float cosAngleOfIncidence = -rayDirection * normal;

	float multiplicand, actualEta;

	if (cosAngleOfIncidence < 0)
	{
		multiplicand = etaSquared;
		cosAngleOfIncidence = -cosAngleOfIncidence;
		localNormal = -localNormal;
		actualEta = invEta;
	}
	else
	{
		actualEta = eta;
		multiplicand = invEtaSquared;
	}

	float determinant = 1 - (multiplicand * (1 - cosAngleOfIncidence * cosAngleOfIncidence));
	float cosAngleOfTransmission = sqrt(determinant);

	wt = (ray.rayDirection / actualEta) - localNormal * (cosAngleOfTransmission - (cosAngleOfIncidence / actualEta));

	RGBColor tempColor = (RGBColor(1, 1, 1) / fabs(normal * wt)) * kt * multiplicand;
	return tempColor;
}