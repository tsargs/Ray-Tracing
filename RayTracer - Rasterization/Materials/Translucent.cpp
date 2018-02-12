// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 04/10/16.
//  Copyright © 2016 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "Translucent.h"

//Default Constructor
Translucent::Translucent(void)
{
	ambientBRDF = new Lambertian();
	diffuseBRDF = new Lambertian();
	specularBRDF = new GlossySpecular();
	perfectSpecularBRDF = new PerfectSpecular();
}

Translucent::Translucent(Sampler* samplerPtr)
{
	localSampler = samplerPtr;
	ambientBRDF = new Lambertian(samplerPtr);
	diffuseBRDF = new Lambertian(samplerPtr);
	specularBRDF = new GlossySpecular(samplerPtr);
	perfectSpecularBRDF = new PerfectSpecular(samplerPtr);
}

//Destructor
Translucent::~Translucent(void)
{

}

void Translucent::SetAmbientBRDF(const float& ka, const RGBColor& colorObj)
{
	ambientBRDF->kd = ka;
	ambientBRDF->diffuseColor = colorObj;
	std::cout << "AmbientBRDF Set\n";
}

void Translucent::SetDiffuseBRDF(const float& kdVal, const RGBColor& colorObj)
{
	diffuseBRDF->kd = kdVal;
	diffuseBRDF->diffuseColor = colorObj;
	std::cout << "DiffuseBRDF Set\n";
}

void Translucent::SetSpecularBRDF(const float& ksVal, const RGBColor& colorObj, const float& eVal)
{
	specularBRDF->ks = ksVal;
	specularBRDF->specularColor = colorObj;
	specularBRDF->e = eVal;
}

void Translucent::SetPerfectSpecularBRDF(const float& krVal, const RGBColor& colorObj)
{
	perfectSpecularBRDF->kr = krVal;
	perfectSpecularBRDF->reflectiveColor = colorObj;
}

void Translucent::SetTransparentProperties(const float& ktVal, const float& etaVal)
{
	kt = ktVal;
	eta = etaVal;
	invEta = 1 / eta;
	etaSquared = eta * eta;
	invEtaSquared = 1 / etaSquared;
}

RGBColor Translucent::PhongShade(ShadeRecord& sr)
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

RGBColor Translucent::Shade(ShadeRecord& sr)
{
	Vector3D wo = -sr.ray.rayDirection; //Changing the ray direction
	Vector3D wi;
	World *localWorldPtr = sr.worldPtr;

	RGBColor reflectiveColor = perfectSpecularBRDF->SampleBRDF(sr, wi, wo);
	RGBColor currentColor = PhongShade(sr);

	bool noTransmittedRay = CheckForTotalInternalReflection(sr.ray, sr.normal);

	if (noTransmittedRay)
	{
		currentColor += localWorldPtr->tracerPtr->TraceRay(Ray(sr.hitPoint, wi), sr.rayDepth + 1);
	}
	else
	{
		float dotProduct = fabs(sr.normal * wi);
		Vector3D wt;
		RGBColor transmittedColor = CalculateTransmittedColor(sr.ray, sr.normal, wt);

		float dotProduct2 = fabs(sr.normal * wt);

		currentColor += reflectiveColor * localWorldPtr->tracerPtr->TraceRay(Ray(sr.hitPoint, wi), sr.rayDepth + 1) * dotProduct;
		currentColor += transmittedColor * localWorldPtr->tracerPtr->TraceRay(Ray(sr.hitPoint, wt), sr.rayDepth + 1) * dotProduct2;
	}

	currentColor = currentColor.ClampBasedOnMaxValue();
	return currentColor;
}

bool Translucent::CheckForTotalInternalReflection(const Ray& ray, const Vector3D& normal)
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

RGBColor Translucent::CalculateTransmittedColor(const Ray& ray, const Vector3D& normal, Vector3D& wt)
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

	Point3D samplePoint = localSampler->FetchHemisPhericalSample();

	/*w = localNormal;*/
	w = wt;
	v = (w^up).UnitVector();
	u = v^w;

	//cout << "Actual wt: ";
	//wt.PrintValues();

	Vector3D sampleDirection = u*samplePoint.x + v*samplePoint.y + w;// *samplePoint.z;
	wt = sampleDirection;
	//wt = (wt + sampleDirection).UnitVector();

	//cout << "Modified wt: ";
	//wt.PrintValues();

	RGBColor tempColor = (RGBColor(1, 1, 1) / fabs(normal * wt)) * kt * multiplicand;
	return tempColor;
}