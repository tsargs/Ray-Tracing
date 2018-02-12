// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 03/06/16.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "SVLambertian.h"

//Default Constructor
SVLambertian::SVLambertian(void) : kd(0), texturePtr(nullptr), normalTexPtr(nullptr)
{
	
}

SVLambertian::SVLambertian(Sampler* samplerPointer)
{
	samplerPtr = samplerPointer;
}

SVLambertian::SVLambertian(const float& kdVal, Texture* texturePointer) : kd(kdVal), texturePtr(texturePointer)
{

}

SVLambertian::SVLambertian(const SVLambertian& svLambertian) : kd(svLambertian.kd), texturePtr(svLambertian.texturePtr), normalTexPtr(svLambertian.normalTexPtr)
{

}

//Destructor
SVLambertian::~SVLambertian(void)
{

}

SVLambertian& SVLambertian::operator=(const SVLambertian& svLambertian)
{
	kd = svLambertian.kd;
	texturePtr = svLambertian.texturePtr;
	normalTexPtr = svLambertian.normalTexPtr;
	return (*this);
}

RGBColor SVLambertian::GetBRDF(const ShadeRecord& sr, const Vector3D& wi, const Vector3D& wo) const
{
	return texturePtr->GetColor(sr)*kd*invPi;
}

Vector3D SVLambertian::GetNormal(const ShadeRecord& sr) const
{
	//std::cout << "GetNormal\n";
	if (normalTexPtr == nullptr)
		return sr.normal;
	else
	{
		RGBColor texColor = normalTexPtr->GetColor(sr);
		double x = (texColor.r - 0.5) * 2;
		double y = (texColor.g - 0.5) * 2;
		double z = (texColor.b - 0.5) * 2;
		Vector3D newNormal(x, y, z);
		return (newNormal + sr.normal).UnitVector();
	}
}

float SVLambertian::GetEta(const ShadeRecord& sr, const float& normalizedVal) const
{
		RGBColor texColor = normalTexPtr->GetColor(sr);
		double x = (texColor.r - 0.5) * 2;
		double y = (texColor.g - 0.5) * 2;
		double z = (texColor.b - 0.5) * 2;
		double svEta = (x + y + z) / 3;
		
		float actualEta = svEta + 1;
		float originalEta = 1;

		float returnVal = originalEta*(1 - normalizedVal) + actualEta*(normalizedVal);

		//if(returnVal > 1)
		//	std::cout << "eta: " << returnVal << "\n";

		return returnVal;
		//return 1;
}

RGBColor SVLambertian::SampleBRDF(const ShadeRecord& sr, Vector3D& wi, const Vector3D& wo) const
{
	//std::cout << "samplerPtr: " << samplerPtr << "\n";
	Point3D samplePoint = samplerPtr->FetchHemisPhericalSample();
	Vector3D up(0, 1, 0);

	//Vector3D w = sr.normal;
	Vector3D w = GetNormal(sr);
	Vector3D v = (up^w).UnitVector();
	Vector3D u = v^w;

	wi = (u*samplePoint.x + v*samplePoint.y + w*samplePoint.z).UnitVector();

	return (texturePtr->GetColor(sr)*kd*invPi);
}

RGBColor SVLambertian::Rho(const ShadeRecord &sr, const Vector3D& wo) const
{
	return texturePtr->GetColor(sr)*kd;
}

