// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 02/21/15.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "Lambertian.h"

//Default Constructor
Lambertian::Lambertian(void) : kd(0), diffuseColor(black)
{
	
}

Lambertian::Lambertian(Sampler* samplerPointer)
{
	samplerPtr = samplerPointer;
}

Lambertian::Lambertian(const float& kdVal, const RGBColor colorObj) : kd(kdVal), diffuseColor(colorObj)
{

}

Lambertian::Lambertian(const Lambertian& lambertian) : kd(lambertian.kd), diffuseColor(lambertian.diffuseColor)
{

}

//Destructor
Lambertian::~Lambertian(void)
{

}

Lambertian& Lambertian::operator=(const Lambertian& lambertian)
{
	kd = lambertian.kd;
	diffuseColor = lambertian.diffuseColor;
	return (*this);
}

RGBColor Lambertian::GetBRDF(const ShadeRecord& sr, const Vector3D& wi, const Vector3D& wo) const
{
	return diffuseColor*kd*invPi;
}

RGBColor Lambertian::SampleBRDF(const ShadeRecord& sr, Vector3D& wi, const Vector3D& wo) const
{
	//std::cout << "samplerPtr: " << samplerPtr << "\n";
	Point3D samplePoint = samplerPtr->FetchHemisPhericalSample();
	Vector3D up(0.0072, 1, 0.0034);

	Vector3D w = sr.normal;
	Vector3D v = (up^w).UnitVector();
	Vector3D u = v^w;

	wi = (u*samplePoint.x + v*samplePoint.y + w*samplePoint.z).UnitVector();

	return (diffuseColor*kd*invPi);
}

RGBColor Lambertian::Rho(const ShadeRecord &sr, const Vector3D& wo) const
{
	return diffuseColor*kd;
}

