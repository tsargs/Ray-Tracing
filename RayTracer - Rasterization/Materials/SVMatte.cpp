// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 03/06/16.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "SVMatte.h"

//Default Constructor
SVMatte::SVMatte(void)
{
	ambientBRDF = new SVLambertian;
	diffuseBRDF = new SVLambertian;
}

SVMatte::SVMatte(Sampler* samplerPtr)
{
	ambientBRDF = new SVLambertian(samplerPtr);
	diffuseBRDF = new SVLambertian(samplerPtr);
}

//Destructor
SVMatte::~SVMatte(void)
{

}

void SVMatte::SetAmbientBRDF(const float& ka, Texture* texturePointer)
{
	ambientBRDF->kd = ka;
	ambientBRDF->texturePtr = texturePointer;
	std::cout << "AmbientBRDF Set in SVMatte\n";
}

void SVMatte::SetDiffuseBRDF(const float& kdVal, Texture* texturePointer)
{
	diffuseBRDF->kd = kdVal;
	diffuseBRDF->texturePtr = texturePointer;
	std::cout << "DiffuseBRDF Set in SVMatte\n";
}

void SVMatte::SetNormalMap(Texture* texturePointer)
{
	diffuseBRDF->normalTexPtr = texturePointer;
}

RGBColor SVMatte::Shade(ShadeRecord& sr)
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
		
		float dotProduct;

		dotProduct = diffuseBRDF->GetNormal(sr) * wi;

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

