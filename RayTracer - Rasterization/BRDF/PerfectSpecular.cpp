// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 04/03/16.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "PerfectSpecular.h"

//Default Constructor
PerfectSpecular::PerfectSpecular(void) : kr(0), reflectiveColor(black)
{
	
}

PerfectSpecular::PerfectSpecular(Sampler* samplerPointer)
{
	samplerPtr = samplerPointer;
}

PerfectSpecular::PerfectSpecular(const float& krVal, const RGBColor colorObj) : kr(krVal), reflectiveColor(colorObj)
{

}

PerfectSpecular::PerfectSpecular(const PerfectSpecular& perfectSpecular) : kr(perfectSpecular.kr), reflectiveColor(perfectSpecular.reflectiveColor)
{

}

//Destructor
PerfectSpecular::~PerfectSpecular(void)
{

}

PerfectSpecular& PerfectSpecular::operator=(const PerfectSpecular& perfectSpecular)
{
	kr = perfectSpecular.kr;
	reflectiveColor = perfectSpecular.reflectiveColor;
	return (*this);
}

RGBColor PerfectSpecular::GetBRDF(const ShadeRecord& sr, const Vector3D& wi, const Vector3D& wo) const
{
	return black;
}

RGBColor PerfectSpecular::SampleBRDF(const ShadeRecord& sr, Vector3D& wi, const Vector3D& wo) const
{
	Vector3D tempWO = wo;
	float dotProduct = sr.normal * wo;
	wi = -tempWO + (sr.normal * 2) * dotProduct;

	//return (reflectiveColor * (kr / (sr.normal * wi)));
	return (reflectiveColor * kr);
}

RGBColor PerfectSpecular::Rho(const ShadeRecord &sr, const Vector3D& wo) const
{
	return black;
}

