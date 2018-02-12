// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 04/17/16.
//  Copyright © 2016 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "GlossyReflective.h"

//Default Constructor
GlossyReflective::GlossyReflective(void)
{
	ambientBRDF = new Lambertian();
	diffuseBRDF = new Lambertian();
	specularBRDF = new GlossySpecular();
	perfectSpecularBRDF = new PerfectSpecular();
}

GlossyReflective::GlossyReflective(Sampler* samplerPtr)
{
	localSampler = samplerPtr;

	ambientBRDF = new Lambertian(samplerPtr);
	diffuseBRDF = new Lambertian(samplerPtr);
	specularBRDF = new GlossySpecular(samplerPtr);
	perfectSpecularBRDF = new PerfectSpecular(samplerPtr);
}

//Destructor
GlossyReflective::~GlossyReflective(void)
{

}

void GlossyReflective::SetAmbientBRDF(const float& ka, const RGBColor& colorObj)
{
	ambientBRDF->kd = ka;
	ambientBRDF->diffuseColor = colorObj;
	std::cout << "AmbientBRDF Set\n";
}

void GlossyReflective::SetDiffuseBRDF(const float& kdVal, const RGBColor& colorObj)
{
	diffuseBRDF->kd = kdVal;
	diffuseBRDF->diffuseColor = colorObj;
	std::cout << "DiffuseBRDF Set\n";
}

void GlossyReflective::SetSpecularBRDF(const float& ksVal, const RGBColor& colorObj, const float& eVal)
{
	specularBRDF->ks = ksVal;
	specularBRDF->specularColor = colorObj;
	specularBRDF->e = eVal;
}


void GlossyReflective::SetPerfectSpecularBRDF(const float& krVal, const RGBColor& colorObj)
{
	perfectSpecularBRDF->kr = krVal;
	perfectSpecularBRDF->reflectiveColor = colorObj;
}

RGBColor GlossyReflective::PhongShade(ShadeRecord& sr)
{
	Vector3D wo = -sr.ray.rayDirection; //Changing the ray direction

	World *localWorldPtr = sr.worldPtr;

	RGBColor currentColor = ambientBRDF->Rho(sr, wo) * localWorldPtr->ambientLightPtr->IncomingRadiance(sr);

	int n = localWorldPtr->lights.size();


	for (int i = 0; i < n; i++)
	{
		Light *light = localWorldPtr->lights[i];
		Vector3D wi = light->GetLightDirection(sr);

		float dotProduct = sr.normal * wi;

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

RGBColor GlossyReflective::Shade(ShadeRecord& sr)
{
	Vector3D wo = -sr.ray.rayDirection; //Changing the ray direction
	Vector3D wi;
	World *localWorldPtr = sr.worldPtr;

	Vector3D tempWo = wo;
	Vector3D r = -tempWo + sr.normal * (sr.normal * wo) * 2;

	Point3D samplePoint = localSampler->FetchHemisPhericalSample();

	w = r;
	u = (up^w).UnitVector();
	v = u^w;

	wi = u*samplePoint.x + v*samplePoint.y + w*samplePoint.z;

	if (wi * sr.normal < 0)
	{
		wi = -(u*samplePoint.x) - (v*samplePoint.y) + w*samplePoint.z;

		//cout << "hitPoint: ";
		//sr.hitPoint.PrintValues();
		//cout << "wi: ";
		//wi.PrintValues();
	}

	float dotProduct = (wi * sr.normal);
	float multiplicand = pow(r*wi, specularBRDF->e);
	float denom = dotProduct * multiplicand;

	//cout << "dotProduct: " << dotProduct << "\n";
	//cout << "r*wi: " << r*wi << "\n";
	//cout << "multiplicand: " << multiplicand << "\n";
	//cout << "color: ";
	//(specularBRDF->specularColor * specularBRDF->ks).PrintValues();

	RGBColor reflectedColor = specularBRDF->specularColor * specularBRDF->ks * multiplicand;
	//reflectedColor.ClampBasedOnMaxValue();
	//reflectedColor.PrintValues();

	RGBColor currentColor = PhongShade(sr);
	RGBColor tempColor = localWorldPtr->tracerPtr->TraceRay(Ray(sr.hitPoint, wi), sr.rayDepth + 1);
	//tempColor.PrintValues();
	currentColor += reflectedColor * tempColor / multiplicand;
		
	currentColor = currentColor.ClampBasedOnMaxValue();
	return currentColor;
}