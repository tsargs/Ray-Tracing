// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 02/21/15.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "GlossySpecular.h"

//Default Constructor
GlossySpecular::GlossySpecular(void) : ks(0), specularColor(black), e(0)
{
	
}

GlossySpecular::GlossySpecular(Sampler* samplerPointer)
{
	samplerPtr = samplerPointer;
}

GlossySpecular::GlossySpecular(const float& ksVal, const RGBColor colorObj, const float& eVal) : ks(ksVal), specularColor(colorObj), e(eVal)
{

}

GlossySpecular::GlossySpecular(const GlossySpecular& glossySpecular) : ks(glossySpecular.ks), specularColor(glossySpecular.specularColor), e(glossySpecular.e)
{

}

//Destructor
GlossySpecular::~GlossySpecular(void)
{

}

GlossySpecular& GlossySpecular::operator=(const GlossySpecular& glossySpecular)
{
	ks = glossySpecular.ks;
	specularColor = glossySpecular.specularColor;
	e = glossySpecular.e;
	return (*this);
}

RGBColor GlossySpecular::GetBRDF(const ShadeRecord& sr, const Vector3D& wi, const Vector3D& wo) const
{
	RGBColor tempColor;
	
	Vector3D tempWi = wi;
	Vector3D r = -tempWi + sr.normal * (sr.normal * wi) * 2;

	float dotProduct = r * wo;

	if (dotProduct > 0.0) //Check to clamp the reflection lobe that goes beneath the surface
	{
		tempColor = specularColor * pow(dotProduct, e);
	}

	return tempColor;
}

RGBColor GlossySpecular::SampleBRDF(const ShadeRecord& sr, Vector3D& wi, const Vector3D& wo) const
{
	/*
	//std::cout << "samplerPtr: " << samplerPtr << "\n";
	Point3D samplePoint = samplerPtr->FetchHemisPhericalSample();
	Vector3D up(0, 1, 0);

	Vector3D w = sr.normal;
	Vector3D v = (up^w).UnitVector();
	Vector3D u = v^w;

	wi = (u*samplePoint.x + v*samplePoint.y + w*samplePoint.z).UnitVector();

	return (diffuseColor*kd*invPi);
	*/
	return black;
}

RGBColor GlossySpecular::Rho(const ShadeRecord &sr, const Vector3D& wo) const
{
	return black;
}

