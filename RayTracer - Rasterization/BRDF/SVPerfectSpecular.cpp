// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 04/04/16.
//  Copyright © 2016 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "SVPerfectSpecular.h"

//Default Constructor
SVPerfectSpecular::SVPerfectSpecular(void) : kr(0), texturePtr(nullptr), normalTexPtr(nullptr)
{
	
}

SVPerfectSpecular::SVPerfectSpecular(Sampler* samplerPointer)
{
	samplerPtr = samplerPointer;
}

SVPerfectSpecular::SVPerfectSpecular(const float& krVal, const RGBColor& colorObj) : kr(krVal), reflectiveColor(colorObj)
{

}

SVPerfectSpecular::SVPerfectSpecular(const SVPerfectSpecular& svPerfectSpecular) : kr(svPerfectSpecular.kr), texturePtr(svPerfectSpecular.texturePtr), normalTexPtr(svPerfectSpecular.normalTexPtr)
{

}

//Destructor
SVPerfectSpecular::~SVPerfectSpecular(void)
{

}

SVPerfectSpecular& SVPerfectSpecular::operator=(const SVPerfectSpecular& svPerfectSpecular)
{
	kr = svPerfectSpecular.kr;
	texturePtr = svPerfectSpecular.texturePtr;
	normalTexPtr = svPerfectSpecular.normalTexPtr;
	return (*this);
}

RGBColor SVPerfectSpecular::GetBRDF(const ShadeRecord& sr, const Vector3D& wi, const Vector3D& wo) const
{
	return black;
}

Vector3D SVPerfectSpecular::GetNormal(const ShadeRecord& sr) const
{
	if (normalTexPtr == nullptr)
		return sr.normal;
	else
	{
		RGBColor texColor = normalTexPtr->GetColor(sr);
		double x = -(texColor.r - 0.5) * 2;
		double y = -(texColor.g - 0.5) * 2;
		double z = -(texColor.b - 0.5) * 2;
		Vector3D newNormal(x, y, z);
		return (newNormal + sr.normal).UnitVector();
	}
}

RGBColor SVPerfectSpecular::SampleBRDF(const ShadeRecord& sr, Vector3D& wi, const Vector3D& wo) const
{
	Vector3D tempWO = wo;
	float dotProduct = GetNormal(sr) * wo;
	wi = -tempWO + (GetNormal(sr) * 2) * dotProduct;

	return (reflectiveColor * (kr / (GetNormal(sr) * wi)));
}

RGBColor SVPerfectSpecular::Rho(const ShadeRecord &sr, const Vector3D& wo) const
{
	return black;
}

