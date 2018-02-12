// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 02/21/15.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "Phong.h"

//Default Constructor
Phong::Phong(void)
{
	ambientBRDF = new Lambertian;
	diffuseBRDF = new Lambertian;
	specularBRDF = new GlossySpecular;
	rimColor = black;
}

Phong::Phong(Sampler* samplerPtr)
{
	ambientBRDF = new Lambertian(samplerPtr);
	diffuseBRDF = new Lambertian(samplerPtr);
	specularBRDF = new GlossySpecular(samplerPtr);
	rimColor = black;
}

//Destructor
Phong::~Phong(void)
{

}

//Matte& Matte::operator= (Matte matte)
//{
//	return *this;
//}

void Phong::SetAmbientBRDF(const float& ka, const RGBColor& colorObj)
{
	ambientBRDF->kd = ka;
	ambientBRDF->diffuseColor = colorObj;
	std::cout << "AmbientBRDF Set\n";
}

void Phong::SetDiffuseBRDF(const float& kdVal, const RGBColor& colorObj)
{
	diffuseBRDF->kd = kdVal;
	diffuseBRDF->diffuseColor = colorObj;
	std::cout << "DiffuseBRDF Set\n";
}

void Phong::SetSpecularBRDF(const float& ksVal, const RGBColor& colorObj, const float& eVal)
{
	specularBRDF->ks = ksVal;
	specularBRDF->specularColor = colorObj;
	specularBRDF->e = eVal;
}

void Phong::SetRimColor(const RGBColor& colorObj)
{
	rimColor = colorObj;
}

RGBColor Phong::Shade(ShadeRecord& sr)
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

		if (rimColor.r != 0 || rimColor.g != 0 || rimColor.b != 0)
		{
			float b = 1 - (wo*sr.normal);

			if (b > 0.85)
				currentColor = currentColor*(1 - b) + rimColor*b;
		}

		currentColor = currentColor.ClampBasedOnMaxValue();
	}

	return currentColor;
}